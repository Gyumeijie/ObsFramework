//
//
// DC_PUSTmLogger.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../Event/DC_EventRepository.h"
#include "../Telemetry/TelemetryPacket.h"
#include "../Telemetry/PUSTelemetryPacket.h"
#include "DC_PUSTmLogger.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_PUSTmLogger_setBufferCapacity(DC_PUSTmLogger *This, unsigned int n)
{
    assert(n > 0);
    assert(This->tmBuffer == pNULL);

    This->capacity = n;
    This->tmBuffer = g_malloc(sizeof(TmPacket)*n);

    // In order access tmBuffer concisely below.
    TmPacket* const tmBuffer = This->tmBuffer;
    for (unsigned int i=0; i<n; i++) {
        tmBuffer[i].data = pNULL;
        tmBuffer[i].nData = 0;
        tmBuffer[i].subType = 0;
        tmBuffer[i].timeTag = 0;
        tmBuffer[i].type = 0;
    }
}

unsigned int DC_PUSTmLogger_getBufferCapacity(const DC_PUSTmLogger *This)
{
    return This->capacity;
}

void DC_PUSTmLogger_setMaxPacketLength(DC_PUSTmLogger *This, unsigned int n)
{

    assert(n > 0);
    assert(This->tmBuffer != pNULL);
    assert(This->maxData == 0); 

    This->maxData = n;

    // In order access tmBuffer concisely below.
    TmPacket* const tmBuffer = This->tmBuffer;
    for (unsigned int i=0; i<This->capacity; i++) {
        tmBuffer[i].data = g_malloc(sizeof(unsigned char)*n);
        for (unsigned int j=0; j<n; j++) {
            tmBuffer[i].data[j] = 0;
        }
    }
}

unsigned int DC_PUSTmLogger_getMaxPacketLength(const DC_PUSTmLogger *This)
{
    return This->maxData;
}

unsigned int DC_PUSTmLogger_getPacketCounter(const DC_PUSTmLogger *This)
{
    return This->counter;
}

TD_TelemetryType DC_PUSTmLogger_getType
(
    const DC_PUSTmLogger *This, 
    unsigned int i
)
{
    // this is automate genenrated by converter
}

TD_TelemetrySubType DC_PUSTmLogger_getSubType
(
    const DC_PUSTmLogger *This, 
    unsigned int i
)
{
    // this is automate genenrated by converter
}

TD_ObsTime DC_PUSTmLogger_getTimeTag
(
    const DC_PUSTmLogger *This, 
    unsigned int i
)
{
    // this is automate genenrated by converter
}

unsigned int DC_PUSTmLogger_getLength
(
    const DC_PUSTmLogger *This, 
    unsigned int i
)
{
    // this is automate genenrated by converter
}

unsigned char DC_PUSTmLogger_getData
(
    const DC_PUSTmLogger *This, 
    unsigned int i,
    unsigned int j
)
{
    // this is automate genenrated by converter
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Return true if the argument packet fits in the telemetry logger.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *      if(pItem->getNumberOfBytes(void)<getMaxPacketLength(void))
 *          return true;
 *	    else
 *          return false; </PRE>
 * @param pPacket the telemetry packet to be written to the telemetry stream
 * @return true if the telemetry packet fits in the telemetry logger, 
 * false otherwise
 */
static bool doesPacketFit(void *obj, TelemetryPacket *pItem)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    TelemetryPacketClass *tpc = TELEMETRYPACKET_GET_CLASS(pItem);
    DC_PUSTmLogger *This = DC_PUSTMLOGGER(obj);

    assert(cc_roc->isObjectConfigured(obj));
    
    const unsigned int nBytes = tpc->getNumberOfBytes(pItem);
    if (nBytes < This->maxData) {
        return true;
    } else {
        return false;
    }
}

/**
 * Write one telemetry packet to the telemetry logger.
 * When the telemetry logger is full, its oldest entry is overwritten.
 * If the length of the packet exceeds M(the maximum length set with method
 * <code>setMaxPacketLength</code>), then only the first M application
 * data bytes are written to the telemetry logger.
 * The telemetry packet data are extracted from the telemetry packet 
 * component through its <i>data acquisition service</i>. If the packet
 * provides it, then the <i>fast version</i> of the service is used.
 * Otherwise the <i>safe version</i> is used. Method 
 *<code>isFastAcquisitionImplemented</code> is used to determine 
 * whether the fast version is provided.
 * @param pItem the telemetry packet to be written to the telemetry stream
 */
static void write(void *obj, TelemetryPacket *pItem)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    TelemetryPacketClass *tpc = TELEMETRYPACKET_GET_CLASS(pItem);
    DC_PUSTmLogger *This = DC_PUSTMLOGGER(obj);
    
    assert(cc_roc->isObjectConfigured(obj));

    unsigned int pos = (This->counter % This->capacity);

    // Check packet length
    unsigned int n = This->maxData;
    const unsigned int nBytes = tpc->getNumberOfBytes(pItem);
    if (nBytes < This->maxData) {
        n = nBytes;
    }

    // In order access tmBuffer concisely below.
    TmPacket* const tmBuffer = This->tmBuffer;

    tmBuffer[pos].type = tpc->getType(pItem);
    tmBuffer[pos].subType = tpc->getSubType(pItem);
    tmBuffer[pos].nData = tpc->getNumberOfBytes(pItem);
    tmBuffer[pos].timeTag = tpc->getTimeTag(pItem);
    
    if (tpc->isFastAcquisitionImplemented(pItem)) {
        unsigned char *s = tpc->getStartAddress(pItem);
        for (unsigned int j=0; j<n; j++) {
            tmBuffer[pos].data[j] = s[j];
        }
    } else {
        for (unsigned int i=0; i<n; i++)  {
            tmBuffer[pos].data[i] = tpc->getUnsignedByte(pItem, i);
        }
    }
        
    // Update the packet counter
    This->counter++;
}

/**
 * Perform a class-specific configuration check on the telemetry logger stream:
 * verify that the maximum length of the telemetry packets and the maximum
 * number of telemetry packets have been set.
 * @return true if the telemetry logger stream is configured, false otherwise.
 */
static bool isObjectConfigured(void *obj)
{
    TelemetryStreamClass *tsc = GET_CLASS(TYPE_TELEMETRYSTREAM);
    DC_PUSTmLogger *This = DC_PUSTMLOGGER(obj);

    return ((CC_ROOTOBJECT_CLASS(tsc)->isObjectConfigured(obj)) && 
            (This->maxData > 0) && 
            (This->tmBuffer != pNULL));
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    DC_PUSTmLogger *This = DC_PUSTMLOGGER(obj);
    This->tmBuffer = pNULL;
    This->maxData = 0;
    This->counter = 0;
    This->capacity = 0;

    CC_RootObject_setClassId((CC_RootObject*)obj, ID_PUSTMLOGGER);
}

DC_PUSTmLogger* DC_PUSTmLogger_new(void)
{
    Object *obj = object_new(TYPE_DC_PUSTMLOGGER);
    return (DC_PUSTmLogger*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    TelemetryStreamClass *tsc = TELEMETRYSTREAM_CLASS(oc);
    tsc->doesPacketFit = doesPacketFit;
    tsc->write = write;

    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_PUSTMLOGGER,
    .parent = TYPE_TELEMETRYSTREAM,
    .instance_size = sizeof(DC_PUSTmLogger),
    .abstract = false,
    .class_size = sizeof(DC_PUSTmLoggerClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_PUSTmLogger_register(void)
{
    type_register_static(&type_info);
}
