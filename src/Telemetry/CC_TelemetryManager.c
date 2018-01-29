//
//
// CC_TelemetryManager.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "../Base/CC_RootObject.h"
#include "../Event/DC_EventRepository.h"
#include "CC_TelemetryManager.h"
#include "TelemetryStream.h"
#include "TelemetryPacket.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void CC_TelemetryManager_setTelemetryModeManager
(
    CC_TelemetryManager *This, 
    TelemetryModeManager *pTmModeManager
)
{
    assert(pTmModeManager != pNULL);
    This->pTmModeManager = pTmModeManager;
}

TelemetryModeManager* CC_TelemetryManager_getTelemetryModeManager
(
    const CC_TelemetryManager *This
)
{
    assert(This->pTmModeManager != pNULL);
    return This->pTmModeManager;
}

void CC_TelemetryManager_setTelemetryStream
(
    CC_TelemetryManager *This, 
    TelemetryStream *pTmStream
)
{
    assert(pTmStream != pNULL);
    This->pTmStream = pTmStream;
}

TelemetryStream* CC_TelemetryManager_getTelemetryStream
(
    const CC_TelemetryManager *This
)
{
    assert(This->pTmStream != pNULL);
    return This->pTmStream;
}

void CC_TelemetryManager_setImmediateQueueSize(CC_TelemetryManager *This, 
                                               unsigned int size)
{
    assert(This->packetQueueSize == -1);        // must be called only once

    This->packetQueueSize = size;
    This->pPacketQueue = g_malloc(size*sizeof(TelemetryPacket*));
    for (unsigned int i=0; i<size; i++) {
        This->pPacketQueue[i] = pNULL;
    }
}

unsigned int CC_TelemetryManager_getImmediateQueueSize(CC_TelemetryManager *This)
{
    return (unsigned int)This->packetQueueSize;
}

TelemetryPacket* CC_TelemetryManager_getImmediateQueueEntry
(
    CC_TelemetryManager *This, 
    unsigned int i
)
{
    assert(This->pPacketQueue != pNULL);
    assert((int)i < This->packetQueueSize);
    return This->pPacketQueue[i];
}

bool CC_TelemetryManager_isImmediateQueueFull(CC_TelemetryManager *This)
{
    if (This->packetQueueSize == 0) {
        return true;
    } else {
        return (This->pPacketQueue[This->packetQueueSize-1] != pNULL);
    }
}

void CC_TelemetryManager_sendTelemetryPacket(CC_TelemetryManager *This, 
                                             TelemetryPacket *pTmPacket)
{
    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);

    assert(This->pPacketQueue != pNULL);

    for (int i=0; i<This->packetQueueSize; i++) {
        if (This->pPacketQueue[i] == pNULL) {
            This->pPacketQueue[i] = pTmPacket;
            return;
        }
    }

    dc_erc->create(dc_er, (CC_RootObject*)This, EVT_TM_QUEUE_FULL);
    return;
}

void CC_TelemetryManager_unloadTelemetryPacket(CC_TelemetryManager *This, 
                                               TelemetryPacket *pTmPacket)
{
    assert(This->pPacketQueue != pNULL);
    assert(pTmPacket != pNULL);

    for (int i=0; i<This->packetQueueSize; i++) {
        if (This->pPacketQueue[i] == pTmPacket) {
            This->pPacketQueue[i] = pNULL;
            return;
        }
    }

    return;
}

unsigned int CC_TelemetryManager_getImmediateQueueLoaded(CC_TelemetryManager *This)
{
    assert(This->pPacketQueue != pNULL);

    unsigned int counter = 0;
    for (int i=0; i<This->packetQueueSize; i++) {
        if (This->pPacketQueue[i] != pNULL) {
            counter++;
        }
    }
    return counter;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Dispatch the telemetry packets to the telemetry stream.
 * Both the telemetry packets provided by the telemetry mode manager and those
 * loaded for immediate dispatch since the last activation are written to the
 * telemetry stream.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *      for(all pTmPacket items in the immediate dispatch queue) {
 *          pTmPacket->update(void);
 *          if(!pTmPacket->isValid(void)) {
 *              createEventReport(EVT_TM_WORD_NOT_VALID);
 *              pTmPacket->setInUse(false);
 *          }
 *          if(!pTmPacket fits in telemetry stream)
 *              createEventReport(EVT_TOO_MANY_TM_BYTES);
 *              pTmPacket->setInUse(false);
 *          }
 *          pTmStream->write(pTmPacket)
 *          pTmPacket->setInUse(false);
 *      }
 *      . . .   // clear immediate dispatch queue
 *      for(all pTmPacket items provided by the telemetry mode manager) {
 *          pTmPacket->update(void);
 *          if(!pTmPacket->isValid(void)) {
 *              createEventReport(EVT_TM_WORD_NOT_VALID);
 *          }
 *          if(!pTmPacket fits in telemetry stream)
 *              createEventReport(EVT_TOO_MANY_TM_BYTES);
 *          }
 *          pTmStream->write(pTmPacket)
 *      }
 *      pTmStream->flush(void); </PRE>
 * In the above pseudo-code, <code>pTmStream</code> is the telemetry stream where
 * the telemetry packets are written and <code>pTmFactory</code> is the telemetry
 * packet factory.
 * <p>
 * Each telemetry packet is first <i>updated</i> and its <i>validity</i> is then
 * checked. If validity is confirmed, it is checked that the packet fits in the telemetry stream.
 * If it does, it is written to the telemetry stream. In the case of telemetry packets
 * from the immediate dispatch queue, the packets are marked as "no longer in use"
 * after being processed.
 * If the telemetry packet is not valid or if it does not
 * fit in the telemetry channel, event reports are generated.
 * After all telemetry packets have been processed, the telemetry stream is flushed.
 * @see TD_EventType
 */
static void activate(void *obj)
{
    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
    CC_TelemetryManager *This = CC_TELEMETRYMANAGER(obj);

    // For the sake of simplicity for accessing pTmStream without 'This'.
    TelemetryStream* const pTmStream = This->pTmStream;
    TelemetryStreamClass *tsc = TELEMETRYSTREAM_GET_CLASS(pTmStream);

    assert(This->pTmModeManager != pNULL);
    assert(This->pTmStream != pNULL);
    assert(This->packetQueueSize >= 0);
    
    for (int i=0; i<This->packetQueueSize; i++) {
    
        TelemetryPacket *pTmPacket;
        TelemetryPacketClass *tpc;

        if (This->pPacketQueue[i] != pNULL) {
            pTmPacket = This->pPacketQueue[i];
            // We need to update tpc to get real TelemetryStreamClass struct.
            tpc = TELEMETRYPACKET_GET_CLASS(pTmPacket);
            This->pPacketQueue[i] = pNULL;
        } else {
            break;
        }

        tpc->update(pTmPacket);

        if (!tpc->isValid(pTmPacket)) {
            dc_erc->create(dc_er, (CC_RootObject*)This, EVT_TM_ITEM_NOT_VALID);
            TelemetryPacket_setInUse(pTmPacket, false);
            continue;
        }

        if (!tsc->doesPacketFit(pTmStream, pTmPacket)) {
            dc_erc->create(dc_er, (CC_RootObject*)This, EVT_TOO_MANY_TM_BYTES);
            TelemetryPacket_setInUse(pTmPacket, false);
            break;
        }

        tsc->write(pTmStream, pTmPacket);
        TelemetryPacket_setInUse(pTmPacket, false);
    }


    // For the sake of simplicity for accessing pTmModeManager without 'This'.
    TelemetryModeManager* const pTmModeManager = This->pTmModeManager;
    TelemetryModeManagerClass *tmmc = TELEMETRYMODEMANAGER_GET_CLASS(pTmModeManager);
    for (tmmc->first(pTmModeManager); 
            !tmmc->isIterationFinished(pTmModeManager);
                tmmc->next(pTmModeManager)) {

        TelemetryPacket *pTmPacket;
        TelemetryPacketClass *tpc;

        pTmPacket = tmmc->getIterationTelemetryPacket(pTmModeManager);
        /**
         * For the kind of packect to which pTmPacket points may be different,
         * So it is safe to use macro TELEMETRYPACKET_GET_CLASS to get real
         * TelemetryPacketClass struct.
         */
        tpc = TELEMETRYPACKET_GET_CLASS(pTmPacket);
        tpc->update(pTmPacket);

        if (!tpc->isValid(pTmPacket)) {
            dc_erc->create(dc_er, (CC_RootObject*)This, EVT_TM_ITEM_NOT_VALID);
            continue;
        }

        if (!tsc->doesPacketFit(pTmStream, pTmPacket)) {
            dc_erc->create(dc_er, (CC_RootObject*)This, EVT_TOO_MANY_TM_BYTES);
            break;
        }

        tsc->write(pTmStream, pTmPacket);
    }

    tsc->flush(pTmStream);
}

/**
 * Perform a class-specific configuration check on the telemetry
 * manager: verify that the telemetry stream and telemetry mode manager
 * have been loaded and that the size of the immediate load packet queue
 * has been set.
 * @return true if the telemetry manager is configured, false otherwise.
 */
static bool isObjectConfigured(void *obj)
{
    CC_RootObjectClass *cc_roc = GET_CLASS(TYPE_CC_ROOTOBJECT);
    CC_TelemetryManager *This = CC_TELEMETRYMANAGER(obj);

    return (cc_roc->isObjectConfigured(obj) &&
            (This->pTmModeManager != pNULL) && 
            (This->pTmStream != pNULL) &&
            (This->packetQueueSize != -1));
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    CC_TelemetryManager *This = CC_TELEMETRYMANAGER(obj);
    This->pTmStream = pNULL;
    This->pTmModeManager = pNULL;
    This->packetQueueSize = -1;
    This->pPacketQueue = pNULL;

    CC_RootObject_setClassId((CC_RootObject*)obj, ID_TELEMETRYMANAGER);
}

CC_TelemetryManager* CC_TelemetryManager_new(void)
{
    return (CC_TelemetryManager*)object_new(TYPE_CC_TELEMETRYMANAGER);
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    CC_TelemetryManagerClass *cc_tmc = CC_TELEMETRYMANAGER_CLASS(oc);
    cc_tmc->activate = activate;

    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_CC_TELEMETRYMANAGER,
    .parent = TYPE_CC_ROOTOBJECT,
    .instance_size = sizeof(CC_TelemetryManager),
    .abstract = false,
    .class_size = sizeof(CC_TelemetryManagerClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void CC_TelemetryManager_register(void)
{
    type_register_static(&type_info);
}
