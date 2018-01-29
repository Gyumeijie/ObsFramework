//
//
// DC_DummyRecoveryAction.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "DC_DummyRecoveryAction.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_DummyRecoveryAction_setActionOutcome
(
    DC_DummyRecoveryAction *This,
    TD_ActionOutcome nextOutcome
)
{
    This->actionOutcome = nextOutcome;
}

void DC_DummyRecoveryAction_setExecutionFlag
(
    DC_DummyRecoveryAction *This,
    bool canExecute
)
{
	This->actionCanExecute = canExecute;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Return <code>actionOutcome</code> without taking any action.
 * @see #setActionOutcome
 * @see RecoveryAction#doAction
 * @return return the outcome code set by the caller
 */
static TD_ActionOutcome doRecoveryAction(void *obj)
{
    DC_DummyRecoveryAction *This = DC_DUMMYRECOVERYACTION(obj);
	return This->actionOutcome;
}

/**
 * Return <code>actionCanExecute</code>.
 * @see #setExecutionFlag
 * @see RecoveryAction#doAction
 * @return true if the action can be executed, false if the action cannot
 * be executed. 
 */
static bool canExecute(void *obj)
{
    DC_DummyRecoveryAction *This = DC_DUMMYRECOVERYACTION(obj);
	return This->actionCanExecute;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    DC_DummyRecoveryAction *This = DC_DUMMYRECOVERYACTION(obj);
	This->actionCanExecute = true;
	This->actionOutcome = ACTION_SUCCESS;

	CC_RootObject_setClassId((CC_RootObject*)obj, ID_DUMMYRECOVERYACTION);
}

DC_DummyRecoveryAction* DC_DummyRecoveryAction_new(void)
{
    Object *obj = object_new(TYPE_DC_DUMMYRECOVERYACTION);
    return (DC_DummyRecoveryAction*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    RecoveryActionClass *rac = RECOVERYACTION_CLASS(oc);
    rac->doRecoveryAction = doRecoveryAction;
    rac->canExecute = canExecute;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_DUMMYRECOVERYACTION,
    .parent = TYPE_RECOVERYACTION,
    .instance_size = sizeof(DC_DummyRecoveryAction),
    .abstract = false,
    .class_size = sizeof(DC_DummyRecoveryActionClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_DummyRecoveryAction_register(void)
{
    type_register_static(&type_info);
}
