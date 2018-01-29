//
//
// RecoveryAction.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "RecoveryAction.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void RecoveryAction_setNextRecoveryAction
(
    RecoveryAction *This,
    RecoveryAction *pNextRecoveryAction
)
{
	assert(pNextRecoveryAction != pNULL);
	This->pNextRecoveryAction = pNextRecoveryAction;
}

RecoveryAction* RecoveryAction_getNextRecoveryAction(RecoveryAction *This)
{
	return This->pNextRecoveryAction;
}


///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Execute the recovery action if the execution check is satisfied
 * and pass on the execute request to the next recovery action
 * (if one is defined).
 * A pseudo-code implementation for this method is as follows: <PRE>
 *   outcome = ACTION_CANNOT_EXECUTE;
 *   if( canExecute(void) )
 *      outcome = doRecoveryAction(void)
 *   if( nextRecoveryAction != pNULL)
 *      outcome = nextRecoveryAction->execute(void);
 *   return outcome; </PRE>
 * The <CODE>doRecoveryAction(void)</CODE> method is abstract and encapsulates
 * the implementation of the actions associated to this recovery action.
 * Thus, this class enforces the handing over of execution requests
 * from one recovery action
 * to the next but it leaves the definition of the
 * specific recovery actions to concrete subclasses.
 * @see #setNextRecoveryAction
 * @see TD_ActionOutcome
 * @return the outcome code of the last recovery action to be executed
 * or ACTION_CANNOT_EXECUTE if no action can be executed
 */
static TD_ActionOutcome doAction(void *obj)
{
    RecoveryActionClass* rac = RECOVERYACTION_GET_CLASS(obj);
    RecoveryAction *This = RECOVERYACTION(obj);

	TD_ActionOutcome outcome = ACTION_CANNOT_EXECUTE;

	if (rac->canExecute(obj)) {
		outcome = rac->doRecoveryAction(obj);
    }

	if (This->pNextRecoveryAction) {
		outcome = PunctualAction_execute((PunctualAction*)This->pNextRecoveryAction);
    }

	return outcome;
}

/**
 * Encapsulate implementation of the <i>execution check</i>.
 * This method is called by method <CODE>doAction(void)</CODE> in this same
 * class. This class provides a default implementation that always
 * returns "can execute".
 * @see #doAction
 * @return true if the action can be executed, false if the action cannot
 * be executed.
 */
static bool canExecute(void *obj)
{
	return true;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Encapsulate implementation of the concrete recovery actions associated
 * to this component.
 * This method is called by method <CODE>doAction(void)</CODE> in this same
 * class.
 * @see #doAction
 * @return the outcome code of the punctual action
 */
static TD_ActionOutcome doRecoveryAction(void *obj)
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
    RecoveryAction *This = RECOVERYACTION(obj);
	This->pNextRecoveryAction = pNULL;
}

RecoveryAction* RecoveryAction_new(void)
{
    Object *obj = object_new(TYPE_RECOVERYACTION);
    return (RecoveryAction*)obj;
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

    PunctualActionClass *pac = PUNCTUALACTION_CLASS(oc);
    pac->doAction = doAction;
}

static const TypeInfo type_info = {
    .name = TYPE_RECOVERYACTION,
    .parent = TYPE_PUNCTUALACTION,
    .instance_size = sizeof(RecoveryAction),
    .abstract = true,
    .class_size = sizeof(RecoveryActionClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void RecoveryAction_register(void)
{
    type_register_static(&type_info);
}
