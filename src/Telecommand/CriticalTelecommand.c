//
//
// CriticalTelecommand.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../Event/DC_EventRepository.h"
#include "../Base/CC_RootObject.h"
#include "../System/ObsClock.h"
#include "CriticalTelecommand.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void CriticalTelecommand_reset(CriticalTelecommand *This)
{
    This->maxArmedDuration = -1;
    This->timeWhenArmed    = -1;
    This->pObsClock        = pNULL;
    This->isTcCritical     = CRITICAL;
    This->isTcArmed        = NOT_ARMED;
}

bool CriticalTelecommand_isCritical(CriticalTelecommand *This)
{
    return This->isTcCritical;
}

void CriticalTelecommand_setCriticalityLevel(CriticalTelecommand *This, 
                                             bool isCritical)
{
    This->isTcCritical = isCritical;
}

bool CriticalTelecommand_isArmed(CriticalTelecommand *This)
{
    return This->isTcArmed;
}

void CriticalTelecommand_setMaxArmedDuration(CriticalTelecommand *This,  
                                             TD_ObsTime t)
{
    assert(t > 0);
    This->maxArmedDuration = t;
}

TD_ObsTime CriticalTelecommand_getMaxArmedDuration(CriticalTelecommand *This)
{
    return This->maxArmedDuration;
}

TD_ObsTime CriticalTelecommand_getTimeWhenArmed(CriticalTelecommand *This)
{
    return This->timeWhenArmed;
}

void CriticalTelecommand_setObsClock(CriticalTelecommand *This, 
                                     ObsClock *pClock)
{
   assert(pClock);
   This->pObsClock = pClock;
}

ObsClock* CriticalTelecommand_getObsClock(const CriticalTelecommand *This)
{
   assert (This->pObsClock);
   return This->pObsClock;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Encapsulate the implementation of the action associated with this critical
 * telecommand. This method verifies if the telecommand is armed and, if so, 
 * calls <code>doCriticalAction</code>, which implements the actual telecommand
 * functionality. A non-critical telecommand is executed immediately(i.e. the
 * arm-fire mechanism is disabled). A pseudo-code implementation of this method
 * is as follows:
 * <pre>
 *    if(TC is armed or it is not critical) {
 *       Disarm the TC
 *       Set the "time when armed" to an invalid value
 *       return doCriticalAction(void);
 *    }
 *    else {
 *       Arm the TC
 *       Save the current OBS time as "time when armed"
 *       Add an EVT_CRIT_TC_ARMED event to the log
 *       return ACTION_SUCCESS;
 *    }
 * </pre>
 * <p>
 * This method is called by <code>PunctualAction::execute(void)</code>.
 * <p>
 * @see PunctualAction#execute
 * @see #doCriticalAction
 * @return the outcome code of the telecommand action
 */
static TD_ActionOutcome doAction(void *obj)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    CriticalTelecommand *This = CRITICALTELECOMMAND(obj);

	assert(cc_roc->isObjectConfigured(obj));

	if (This->isTcArmed || !This->isTcCritical) {
		This->isTcArmed = NOT_ARMED;
		This->timeWhenArmed = -1;

        CriticalTelecommandClass *ctc = CRITICALTELECOMMAND_GET_CLASS(obj);
		return ctc->doCriticalAction(obj);
	} else {
        ObsClockClass *occ = OBSCLOCK_GET_CLASS(This->pObsClock);
		This->isTcArmed = ARMED;
		This->timeWhenArmed = occ->getTime(This->pObsClock);

        DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
        DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
		dc_erc->create(dc_er, (CC_RootObject*)This, EVT_CRIT_TC_ARMED);

		return ACTION_SUCCESS;
	}
}

/**
 * Execute the image validity check.
 * This class provides a default implementation that returns "image
 * is valid".
 * @see #canExecute
 * @return true if the telecommand is valid, false otherwise
 */
static bool isImageValid(void *obj)
{
    return VALID;
}

/**
 * Implement the image store service.
 * This class provides a default implementation that returns without
 * doing anything.
 * @see #canExecute
 */
static void storeImage(void *obj)
{
    return;
}

/**
 * Perform the execution check on the telecommand.
 * A pseudo-code implementation of this method is as follows:
 * <pre>
 *    if(TC is critical and armed) {
 *       if(TC has timed-out) {
 *          Add an EVT_CRIT_TC_TIMEOUT event to the log
 *          return false;
 *       }
 *
 *       if(TC image is not valid) {
 *          Add an EVT_CRIT_TC_IMG_INV event to the log
 *          return false;
 *       }
 *    }
 *
 *    return true;
 * </pre>
 * @see CC_TelecommandManager#activate
 * @return true if the telecommand can execute, false otherwise
 */
static bool canExecute(void *obj)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
    CriticalTelecommand *This = CRITICALTELECOMMAND(obj);

    assert(cc_roc->isObjectConfigured(obj));

	if (This->isTcCritical && This->isTcArmed) {
        ObsClockClass *occ = OBSCLOCK_GET_CLASS(This->pObsClock);
        TD_ObsTime dur = occ->getTime(This->pObsClock) - This->timeWhenArmed;
		if (dur >= This->maxArmedDuration) {
			dc_erc->create(dc_er, (CC_RootObject*)This, EVT_CRIT_TC_TIMEOUT);
			return TC_CANNOT_EXECUTE;
		}

        CriticalTelecommandClass *ctc = CRITICALTELECOMMAND_GET_CLASS(obj);
		if (!ctc->isImageValid(obj)) {
            dc_erc->create(dc_er, (CC_RootObject*)This, EVT_CRIT_TC_IMG_INV);
			return TC_CANNOT_EXECUTE;
		}
	}

    return TC_CAN_EXECUTE;
}

/**
 * Perform a class-specific configuration check on the telecommand:
 * verify that the maximum armed duration has a legal value and that
 * the on-board clock component has been loaded.
 * @return true if the component is configured, false otherwise.
 */
static bool isObjectConfigured(void *obj)
{
   TelecommandClass *tc = GET_CLASS(TYPE_TELECOMMAND);
   CriticalTelecommand *This = CRITICALTELECOMMAND(obj);

   return ((CC_ROOTOBJECT_CLASS(tc)->isObjectConfigured(obj)) &&
           (This->maxArmedDuration > 0) && 
           (This->pObsClock != pNULL));
}



///////////////////////////////////////////////////////////////////////////////
//
//                    pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * A derived class shall provide a concrete implementation of this
 * method, which performs the actual critical telecommand action.
 * <code>doCriticalAction(void)</code> is invoked only the second time a
 * specific critical telecommand is received(the first time, the telecommand
 * is armed).
 * <p>
 * This method is called by <code>doAction(void)</code>.
 * <p>
 * @see #doAction
 * @return the outcome code of the telecommand action
 */
static TD_ActionOutcome doCriticalAction(void *obj)
{
    // this is automate genenrated by converter
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
	CriticalTelecommand_reset((CriticalTelecommand*)obj);
}

CriticalTelecommand* CriticalTelecommand_new(void)
{
    Object *obj = object_new(TYPE_CRITICALTELECOMMAND);
    return (CriticalTelecommand*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    CriticalTelecommandClass *ctc = CRITICALTELECOMMAND_CLASS(oc);
    ctc->doCriticalAction = doCriticalAction;
    ctc->isImageValid = isImageValid;
    ctc->storeImage = storeImage;

    TelecommandClass *tc = TELECOMMAND_CLASS(oc);
    tc->canExecute = canExecute;

    PunctualActionClass *pac = PUNCTUALACTION_CLASS(oc);
    pac->doAction = doAction;

    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_CRITICALTELECOMMAND,
    .parent = TYPE_TELECOMMAND,
    .instance_size = sizeof(CriticalTelecommand),
    .abstract = true,
    .class_size = sizeof(CriticalTelecommandClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void CriticalTelecommand_register(void)
{
    type_register_static(&type_info);
}
