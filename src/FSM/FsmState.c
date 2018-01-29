//
//
// FsmState.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/Constants.h"
#include "FsmState.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void FsmState_setNextState(FsmState *This, FsmState *pNextState)
{
    This->pNextState = pNextState; 
}

FsmState* FsmState_getNextState(const FsmState *This)
{
    return This->pNextState;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Perform the entry check and return false if a transition into this
 * state would put the system
 * in an inconsistent or otherwise undesirable condition.
 * Note that the ultimate decision as to whether the state is entered or
 * not lies with the FSM that could
 * decide to ignore the return value of canEnter(void).
 * This class provides a default implementation that returns true(state
 * can be entered).
 * @see CC_FSM#activate
 * @return true if the state can be safely entered.
 */
static bool canEnter(void *obj)
{
   return true;
}

/**
 * Perform the initialization action associated to the FsmState.
 * This method is intended to be called by the FSM immediately after the
 * state has been entered.
 * This class provides a default implementation that returns without
 * doing anything.
 * @see CC_FSM#activate
 */
static void doInit(void *obj)
{
   return;
}

/**
 * Perform the exit check and return false if performing a transition out
 * of the this state would leave
 * the system in an inconsistent or otherwise undesirable condition.
 * Note that the ultimate decision as to whether the state is exited or
 * not lies with the FSM that could
 * decide to ignore the return value of canExit(void).
 * This class provides a default implementation that returns true(state
 * can be exited).
 * @see CC_FSM#activate
 * @return true if the manoeuvre can continue execution
 */
static bool canExit(void *obj)
{
   return true;
}

/**
 * Perform the exit action associated to this state.
 * This method is intended to be called by the FSM object just before it
 * exits this state.
 * This class provides a default implementation that returns without
 * doing anything.
 * @see CC_FSM#activate
 */
static void doExit(void *obj)
{
   return;
}

/**
 * Perform a termination check and return true if the continued action
 * associated to this state has
 * been completed and an autonomous transition to a next state should be
 * performed.
 * This class provides a default implementation that always returns "not
 * terminated".
 * @see CC_FSM#activate
 * @return true if the continued action associated to this state has been
 * terminated, false otherwise
 */
static bool isFinished(void *obj)
{
   return false;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Perform the continued action associated to this state.
 * This method is intended to be called by the FSM every time it is
 * activated when this state is the
 * current state.
 * @see CC_FSM#activate
 */
static void doContinue(void *obj)
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
   FsmState *This = FSMSTATE(obj);
   This->pNextState = pNULL;
}

FsmState* FsmState_new(void)
{
    Object *obj = object_new(TYPE_FSMSTATE);
    return (FsmState*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    FsmStateClass *fsc = FSMSTATE_CLASS(oc);

    fsc->canEnter = canEnter;
    fsc->doInit = doInit;
    fsc->canExit = canExit;
    fsc->doExit = doExit;
    fsc->isFinished = isFinished;

    fsc->doContinue = doContinue;
}

static const TypeInfo type_info = {
    .name = TYPE_FSMSTATE,
    .parent = TYPE_CC_ROOTOBJECT,
    .instance_size = sizeof(FsmState),
    .abstract = true,
    .class_size = sizeof(FsmStateClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void FsmState_register(void)
{
    type_register_static(&type_info);
}
