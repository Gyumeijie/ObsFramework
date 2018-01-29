//
//
// DC_FdirCheck.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "DC_FdirCheck.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_FdirCheck_setFdiCheck(DC_FdirCheck *This, PunctualAction *pFdiCheck)
{
	assert(pFdiCheck);
	This->pFdiCheck = pFdiCheck;
}

PunctualAction* DC_FdirCheck_getFdiCheck(DC_FdirCheck *This)
{
	assert(This->pFdiCheck);
	return This->pFdiCheck;
}

void DC_FdirCheck_setRecoveryAction(DC_FdirCheck *This,
                                    RecoveryAction *pRecoveryAction)
{
	assert(pRecoveryAction);
	This->pRecoveryAction = pRecoveryAction;
}

RecoveryAction* DC_FdirCheck_getRecoveryAction(DC_FdirCheck *This)
{
	assert(This->pRecoveryAction);
	return This->pRecoveryAction;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Execute the FDI check and, if this returns a failure code, execute
 * the recovery action.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *   outcome = pFdiCheck->execute(void);
 *   if( outcome == ACTION_FAILURE )
 *      outcome = pRecoveryAction->execute(void);
 *   return outcome; </PRE>
 * Note that the outcome code returned by this punctual action is either
 * the return code of the FDI check or of the recovery action, whichever
 * is executed last.
 * @see TD_ActionOutcome
 * @return the outcome code of the last recovery action to be executed
 * or ACTION_CANNOT_EXECUTE if no action can be executed
 */
static TD_ActionOutcome doAction(void *obj)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    DC_FdirCheck *This = DC_FDIRCHECK(obj);

	assert(cc_roc->isObjectConfigured(obj));

	TD_ActionOutcome outcome = PunctualAction_execute(This->pFdiCheck);
	if (outcome == ACTION_FAILURE){
		outcome = PunctualAction_execute((PunctualAction*)This->pRecoveryAction);
    }

	return outcome;
}

/**
 * Perform a class-specific configuration check on the FDIR check:
 * verify that the recovery action and FDI check have been set.
 * @return true if the FDIR check is configured, false otherwise.
 */
static bool isObjectConfigured(void *obj)
{
    PunctualActionClass *pac = GET_CLASS(TYPE_PUNCTUALACTION);
    DC_FdirCheck *This = DC_FDIRCHECK(obj);

	return ((CC_ROOTOBJECT_CLASS(pac)->isObjectConfigured(obj)) &&
            (This->pRecoveryAction != pNULL) && 
            (This->pFdiCheck != pNULL));
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    DC_FdirCheck *This = DC_FDIRCHECK(obj);
	This->pRecoveryAction = pNULL;
	This->pFdiCheck = pNULL;

	CC_RootObject_setClassId((CC_RootObject*)obj, ID_FDIRCHECK);
}

DC_FdirCheck* DC_FdirCheck_new(void)
{
    Object *obj = object_new(TYPE_DC_FDIRCHECK);
    return (DC_FdirCheck*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    PunctualActionClass *pac = PUNCTUALACTION_CLASS(oc);
    pac->doAction = doAction;

    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_FDIRCHECK,
    .parent = TYPE_PUNCTUALACTION,
    .instance_size = sizeof(DC_FdirCheck),
    .abstract = false,
    .class_size = sizeof(DC_FdirCheckClass),
    .instance_init = instance_init,
    .class_init = class_init
};

void DC_FdirCheck_register(void)
{
    type_register_static(&type_info);
}
