//
//
// DC_FsmEvent.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "DC_FsmEvent.h"
#include "CC_FSM.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_FsmEvent_setTargetFsm(DC_FsmEvent *This, CC_FSM *pTargetFsm)
{
   assert(pTargetFsm != pNULL);
   This->pTargetFsm = pTargetFsm;
}

void DC_FsmEvent_setTargetState(DC_FsmEvent *This, TD_FsmStateIndex targetState)
{
   assert(targetState >= 0);
   This->targetState = targetState;
}

CC_FSM* DC_FsmEvent_getTargetFsm(const DC_FsmEvent *This)
{
   assert(This->pTargetFsm != pNULL);
   return This->pTargetFsm;
}

TD_FsmStateIndex DC_FsmEvent_getTargetState(const DC_FsmEvent *This)
{
   assert(This->targetState >= 0);
   return This->targetState;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Perform a class-specific configuration check on a FsmEvent object:
 * verify that the target FSM has been
 * loaded, that the target state has been loaded, and that the loaded
 * target state has a legal value.
 * The legality of the target state is checked by verifying that its
 * value lies in the range [0, N-1] where N is the total
 * number of states in the target FSM.
 * <p>
 */
static bool isObjectConfigured(void *obj)
{
    PunctualActionClass *pac = GET_CLASS(TYPE_PUNCTUALACTION); 
    DC_FsmEvent *This = DC_FSMEVENT(obj);

    return ((CC_ROOTOBJECT_CLASS(pac)->isObjectConfigured(obj)) && 
            (This->targetState >= 0) &&
            (This->pTargetFsm != pNULL) &&
            (This->targetState < CC_FSM_getNumberOfStates(This->pTargetFsm)));
}

/**
 * Execute the FsmEvent: lodge a request to the target FSM to perform a
 * state transition to the target state.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *   targetFsm.makeTransitionRequest(targetState);
 *   return ACTION_SUCCESS; </PRE>
 * The method assumes that the FsmEvent is correctly configured and that
 * a target FSM and target state have
 * been loaded.
 * No check is made about the current state of the FSM.
 * Applications that wish to implement a more complex execution logic
 * should override this method.
 * Only one return value can be returned by this implementation
 * signifiying a successful outcome to execution
 * of the puncutal action.
 * <p>
 * @see PunctualAction#execute
 * @return the SUCCESS code for the FsmEvent punctual action
 */
static TD_ActionOutcome doAction(void *obj)
{
   DC_FsmEvent *This = DC_FSMEVENT(obj);

   CC_FSM_makeTransitionRequest(This->pTargetFsm, This->targetState);
   return ACTION_SUCCESS;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
   DC_FsmEvent *This = DC_FSMEVENT(obj);
   This->pTargetFsm = pNULL;
   This->targetState = -1;

   CC_RootObject_setClassId((CC_RootObject*)obj, ID_FSMEVENT);
}

DC_FsmEvent* DC_FsmEvent_new(void)
{
    Object *obj = object_new(TYPE_DC_FSMEVENT);
    return (DC_FsmEvent*)obj;
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
    .name = TYPE_DC_FSMEVENT,
    .parent = TYPE_PUNCTUALACTION,
    .instance_size = sizeof(DC_FsmEvent),
    .abstract = false,
    .class_size = sizeof(DC_FsmEventClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_FsmEvent_register(void)
{
    type_register_static(&type_info);
}
