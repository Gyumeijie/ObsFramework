//
//
// DC_PUSEventRepository.c
//
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../System/ObsClock.h"
#include "../Telecommand/PUSTelecommand.h"
#include "../Telemetry/DC_PUSTcVerificationPacket.h"
#include "../Telemetry/CC_TelemetryManager.h"
#include "../Telemetry/CC_TelemetryPacketFactory.h"
#include "../Manoeuvre/PUSTcManoeuvre.h"
#include "../Base/PunctualAction.h"
#include "DC_EventRepository.h"
#include "DC_PUSEventRepository.h"
#include <string.h>



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_PUSEventRepository_create
(
    DC_PUSEventRepository *This, 
    Object *originator, 
    TD_EventType eventId
)
{
    assert(originator != pNULL);
    assert(eventId > 0);

    const char *typeName = object_get_typename((Object*)originator);

    if (is_compatible_type(typeName, TYPE_PUSTELECOMMAND)) {
       createPUSTelecommand(This, (PUSTelecommand*)originator, eventId); 
    } else if (is_compatible_type(typeName, TYPE_PUSTCMANOEUVRE)) {
       createPUSTcManoeuvre(This, (PUSTcManoeuvre*)originator, eventId); 
    } else {
       // Unknown originator type
       assert(false);
    }
}

static void createPUSTelecommand
(
    DC_PUSEventRepository *This, 
    PUSTelecommand *originator, 
    TD_EventType eventId
)
{
    DC_EventRepositoryClass *dc_erc = GET_CLASS(TYPE_DC_EVENTREPOSITORY);

    // Only process event if event creation is enabled
    if (!DC_EventRepository_isEnabled((DC_EventRepository*)This) || 
        !DC_EventRepository_isEnabledWithEventType((DC_EventRepository*)This, eventId)) 
    {
        return;
    }

    DC_PUSTcVerificationPacket *pTcVerificationPacket;
    CC_TelemetryPacketFactory *pFct = CC_TelemetryPacketFactory_getInstance();
    pTcVerificationPacket = CC_TelemetryPacketFactory_allocatePUSTcVerificationPacket(pFct);
    if (pTcVerificationPacket == pNULL) {
        dc_erc->create(This, (CC_RootObject*)originator, EVT_TM_PCK_ALLOC_FAILURE);
        dc_erc->create(This, (CC_RootObject*)originator, eventId);
        return;
    }

    TD_CheckCode errCode = 0;


    TelemetryPacketClass *tpc = TELEMETRYPACKET_GET_CLASS(pTcVerificationPacket);
    TelecommandClass *tc = TELECOMMAND_GET_CLASS(originator); 
    TD_TelecommandId tid = tc->getTelecommandId(originator);
    ObsClock *clock = PUSTelemetryPacket_getObsClock();
    ObsClockClass *occ = OBSCLOCK_GET_CLASS(clock);


    switch (eventId) {

        case EVT_TC_LOADED:       // telecommand acceptance -- success
            if (PUSTelecommand_isAcceptanceAckRequired(originator)) {
                DC_PUSTcVerificationPacket_setTelecommandId(pTcVerificationPacket, tid);
                tpc->setSubType(pTcVerificationPacket, PUS_ST_TC_VER_ACC_SC);
                tpc->setTimeTag(pTcVerificationPacket, occ->getTime(clock));
                CC_TelemetryManager_sendTelemetryPacket(This->pTmManager, 
                                      (TelemetryPacket*)pTcVerificationPacket);
            } else {
                TelemetryPacket_setInUse((TelemetryPacket*)pTcVerificationPacket, NOT_IN_USE);
            }
            break;

        case EVT_TC_NOT_VALID:       // telecommand acceptance -- failure
            DC_PUSTcVerificationPacket_setTelecommandId(pTcVerificationPacket, tid);
            tpc->setSubType(pTcVerificationPacket, PUS_ST_TC_VER_ACC_FL);
            tpc->setTimeTag(pTcVerificationPacket, occ->getTime(clock));
            errCode = tc->getValidityCheckCode(originator);
            if (errCode != 0) {
                DC_PUSTcVerificationPacket_setErrorCode(pTcVerificationPacket, errCode);
            } else {
                DC_PUSTcVerificationPacket_setErrorCode(pTcVerificationPacket, EVT_TC_NOT_VALID);
            }
            CC_TelemetryManager_sendTelemetryPacket(This->pTmManager, 
                                  (TelemetryPacket*)pTcVerificationPacket);
            break;

        case EVT_TC_LIST_FULL:       // telecommand acceptance -- failure
            DC_PUSTcVerificationPacket_setTelecommandId(pTcVerificationPacket, tid);
            tpc->setSubType(pTcVerificationPacket, PUS_ST_TC_VER_ACC_FL);
            DC_PUSTcVerificationPacket_setErrorCode(pTcVerificationPacket, EVT_TC_LIST_FULL);
            tpc->setTimeTag(pTcVerificationPacket, occ->getTime(clock));
            CC_TelemetryManager_sendTelemetryPacket(This->pTmManager, 
                                  (TelemetryPacket*)pTcVerificationPacket);
            break;

        case EVT_TC_EXEC_CHECK_FAIL:       // telecommand execution start -- failure
            DC_PUSTcVerificationPacket_setTelecommandId(pTcVerificationPacket, tid);
            tpc->setSubType(pTcVerificationPacket, PUS_ST_TC_EXE_STR_FL);
            tpc->setTimeTag(pTcVerificationPacket, occ->getTime(clock));
            errCode = tc->getExecutionCheckCode(originator);
            if (errCode != 0) {
                DC_PUSTcVerificationPacket_setErrorCode(pTcVerificationPacket, errCode);
            } else {
                DC_PUSTcVerificationPacket_setErrorCode(pTcVerificationPacket, EVT_TC_EXEC_CHECK_FAIL);
            }
            CC_TelemetryManager_sendTelemetryPacket(This->pTmManager, 
                                  (TelemetryPacket*)pTcVerificationPacket);
            break;

        case EVT_TC_ABORTED:       // telecommand execution start -- failure
            DC_PUSTcVerificationPacket_setTelecommandId(pTcVerificationPacket, tid);
            tpc->setSubType(pTcVerificationPacket, PUS_ST_TC_EXE_STR_FL);
            DC_PUSTcVerificationPacket_setErrorCode(pTcVerificationPacket, EVT_TC_ABORTED);
            tpc->setTimeTag(pTcVerificationPacket, occ->getTime(clock));
            CC_TelemetryManager_sendTelemetryPacket(This->pTmManager, 
                                  (TelemetryPacket*)pTcVerificationPacket);
            break;

        case EVT_TC_EXEC_FAIL:       // telecommand completion -- failure
            DC_PUSTcVerificationPacket_setTelecommandId(pTcVerificationPacket, tid);
            tpc->setSubType(pTcVerificationPacket, PUS_ST_TC_EXE_END_FL);
            tpc->setTimeTag(pTcVerificationPacket, occ->getTime(clock));
            errCode = (TD_CheckCode)PunctualAction_getLastOutcome((PunctualAction*)originator);
            DC_PUSTcVerificationPacket_setErrorCode(pTcVerificationPacket, errCode);
            CC_TelemetryManager_sendTelemetryPacket(This->pTmManager, 
                                  (TelemetryPacket*)pTcVerificationPacket);
            break;

        case EVT_TC_EXEC_SUCC:       // telecommand completion -- success
            if (PUSTelecommand_isCompletionAckRequired(originator)) {
                DC_PUSTcVerificationPacket_setTelecommandId(pTcVerificationPacket, tid);
                tpc->setSubType(pTcVerificationPacket, PUS_ST_TC_EXE_END_SC);
                tpc->setTimeTag(pTcVerificationPacket, occ->getTime(clock));
                CC_TelemetryManager_sendTelemetryPacket(This->pTmManager, 
                                      (TelemetryPacket*)pTcVerificationPacket);
            } else {
                TelemetryPacket_setInUse((TelemetryPacket*)pTcVerificationPacket, NOT_IN_USE);
            }
            break;

        default:
            assert(false);  // should never be reached
    }

    dc_erc->create(This, (CC_RootObject*)originator, eventId);
}

static void createPUSTcManoeuvre
(
    DC_PUSEventRepository *This, 
    PUSTcManoeuvre *originator, 
    TD_EventType eventId
)
{

   DC_EventRepositoryClass *dc_erc = GET_CLASS(TYPE_DC_EVENTREPOSITORY);
   TD_CheckCode errCode = 0;

   // Only process event if event creation is enabled
   if (!DC_EventRepository_isEnabled((DC_EventRepository*)This) || 
       !DC_EventRepository_isEnabledWithEventType((DC_EventRepository*)This, eventId)) 
   {
       return;
   }

   DC_PUSTcVerificationPacket *pTcVerificationPacket;
   CC_TelemetryPacketFactory *pFct = CC_TelemetryPacketFactory_getInstance();
   pTcVerificationPacket = CC_TelemetryPacketFactory_allocatePUSTcVerificationPacket(pFct);
   if (pTcVerificationPacket == pNULL) {
       dc_erc->create(This, (CC_RootObject*)originator, EVT_TM_PCK_ALLOC_FAILURE);
       dc_erc->create(This, (CC_RootObject*)originator, eventId);
       return;
   }

   TelemetryPacketClass *tpc = TELEMETRYPACKET_GET_CLASS(pTcVerificationPacket);
   ObsClock *clock = PUSTelemetryPacket_getObsClock();
   PUSTcManoeuvreClass *pmc = PUSTCMANOEUVRE_GET_CLASS(originator);  
   ManoeuvreClass *mc = MANOEUVRE_GET_CLASS(originator);
   TD_TelecommandId tid = pmc->getTelecommandId(originator);
   ObsClockClass *occ = OBSCLOCK_GET_CLASS(clock);


   switch (eventId) {

       case EVT_MAN_STARTED:       // telecommand execution start -- success
           if (PUSTcManoeuvre_isStartAckRequired(originator)) {
               DC_PUSTcVerificationPacket_setTelecommandId(pTcVerificationPacket, tid);
               tpc->setSubType(pTcVerificationPacket, PUS_ST_TC_EXE_STR_SC);
               tpc->setTimeTag(pTcVerificationPacket, occ->getTime(clock));
               CC_TelemetryManager_sendTelemetryPacket(This->pTmManager, 
                                     (TelemetryPacket*)pTcVerificationPacket);
           } else {
               TelemetryPacket_setInUse((TelemetryPacket*)pTcVerificationPacket, NOT_IN_USE);
           }
           break;

       case EVT_MAN_LIST_FULL:       // telecommand execution start -- failure
           DC_PUSTcVerificationPacket_setTelecommandId(pTcVerificationPacket, tid);
           tpc->setSubType(pTcVerificationPacket, PUS_ST_TC_EXE_STR_FL);
           DC_PUSTcVerificationPacket_setErrorCode(pTcVerificationPacket, EVT_MAN_LIST_FULL);
           tpc->setTimeTag(pTcVerificationPacket, occ->getTime(clock));
           CC_TelemetryManager_sendTelemetryPacket(This->pTmManager, 
                                 (TelemetryPacket*)pTcVerificationPacket);
           break;

       case EVT_MAN_PROGRESS:       // telecommand execution progress -- success
           if (PUSTcManoeuvre_isProgressAckRequired(originator)) {
               DC_PUSTcVerificationPacket_setTelecommandId(pTcVerificationPacket, tid);
               tpc->setSubType(pTcVerificationPacket, PUS_ST_TC_EXE_PRO_SC);
               tpc->setTimeTag(pTcVerificationPacket, occ->getTime(clock));
               CC_TelemetryManager_sendTelemetryPacket(This->pTmManager, 
                                     (TelemetryPacket*)pTcVerificationPacket);
           } else {
               TelemetryPacket_setInUse((TelemetryPacket*)pTcVerificationPacket, NOT_IN_USE);
           }
           break;

       case EVT_MAN_ABORTED:       // telecommand execution progress -- failure
           DC_PUSTcVerificationPacket_setTelecommandId(pTcVerificationPacket, tid);
           tpc->setSubType(pTcVerificationPacket, PUS_ST_TC_EXE_PRO_FL);
           tpc->setTimeTag(pTcVerificationPacket, occ->getTime(clock));
           errCode = mc->getContinuationCheckCode(originator);
           if (errCode != 0) {
               DC_PUSTcVerificationPacket_setErrorCode(pTcVerificationPacket, errCode);
           }
           else {
               DC_PUSTcVerificationPacket_setErrorCode(pTcVerificationPacket, EVT_MAN_ABORTED);
           }
           CC_TelemetryManager_sendTelemetryPacket(This->pTmManager, 
                                 (TelemetryPacket*)pTcVerificationPacket);
           break;

       case EVT_MAN_TERMINATED:       // telecommand execution completion -- success
           if (PUSTcManoeuvre_isCompletionAckRequired(originator)) {
               DC_PUSTcVerificationPacket_setTelecommandId(pTcVerificationPacket, tid);
               tpc->setSubType(pTcVerificationPacket, PUS_ST_TC_EXE_END_SC);
               tpc->setTimeTag(pTcVerificationPacket, occ->getTime(clock));
               CC_TelemetryManager_sendTelemetryPacket(This->pTmManager, 
                                     (TelemetryPacket*)pTcVerificationPacket);
           } else {
               TelemetryPacket_setInUse((TelemetryPacket*)pTcVerificationPacket, NOT_IN_USE);
           }
           break;

       default:
           assert(false);  // should never be reached
   }

   dc_erc->create(This, (CC_RootObject*)originator, eventId);
}

void DC_PUSEventRepository_setTelemetryManager
(
    DC_PUSEventRepository *This, 
    CC_TelemetryManager *pTmManager
)
{
    assert(pTmManager != pNULL);
    This->pTmManager = pTmManager;
}

CC_TelemetryManager* DC_PUSEventRepository_getTelemetryManager
(
    const DC_PUSEventRepository *This
)
{
    assert(This->pTmManager != pNULL);
    return This->pTmManager;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Implement the event creation service for event originators of type
 * other than <code>PUSTcManoeuvre</code> or <code>PUSTelecommand</code>. 
 * This method simply calls the implementation of the create method in the 
 * super class.
 * <p>
 * <i>Implementation Note</i>: this method is strictly speaking unnecessary because
 * it simply calls the same virtual method in the superclass. However its absence 
 * causes a warning(C4264) in the Microsoft Visual Studio compiler.
 * @param originator the originator of the event
 * @param eventId the event type identifier
 */
static void create(void *obj, CC_RootObject *originator, TD_EventType eventId)
{
    DC_EventRepositoryClass *dc_erc = GET_CLASS(TYPE_DC_EVENTREPOSITORY);
    dc_erc->create(obj, originator, eventId);
}

/**
 * Perform a class-specific configuration check on a repository object:
 * verify that the telemetry manager plug-in component has been loaded.
 * @return true if the object is configured, false otherwise
 */
static bool isObjectConfigured(void *obj)
{
   DC_EventRepositoryClass *dc_erc = GET_CLASS(TYPE_DC_EVENTREPOSITORY);
   DC_PUSEventRepository *This = DC_PUSEVENTREPOSITORY(obj);

   return ((CC_ROOTOBJECT_CLASS(dc_erc)->isObjectConfigured(obj)) && 
           (This->pTmManager != pNULL));
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    CC_RootObject_setClassId((CC_RootObject*)obj, ID_PUSEVENTREPOSITORY);
}

DC_PUSEventRepository* DC_PUSEventRepository_new(void)
{
    Object *obj = object_new(TYPE_DC_PUSEVENTREPOSITORY);
    return (DC_PUSEventRepository*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_CLASS(oc);
    dc_erc->create = create;

    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_PUSEVENTREPOSITORY,
    .parent = TYPE_DC_EVENTREPOSITORY,
    .instance_size = sizeof(DC_PUSEventRepository),
    .abstract = false,
    .class_size = sizeof(DC_PUSEventRepositoryClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_PUSEventRepository_register(void)
{
    type_register_static(&type_info);
}
