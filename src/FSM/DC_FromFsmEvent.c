//
//
// DC_FromFsmEvent.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "DC_FromFsmEvent.h"
#include "CC_FSM.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_FromFsmEvent_setStartingState(DC_FromFsmEvent *This, 
                                      TD_FsmStateIndex startingState)
{
    assert(startingState >= 0);
    This->startingState = startingState;
}

TD_FsmStateIndex DC_FromFsmEvent_getStartingState(const DC_FromFsmEvent *This)
{
    assert(This->startingState >= 0);
    return This->startingState;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Perform a class-specific configuration check on a repository object:
 * verify that the starting state has been
 * loaded and that it has a legal value.
 * The legality of the starting state is checked by verifying that its
 * value lies in the range [0, N-1] where N is the total
 * number of states in the target FSM.
 * <p>
 */
static bool isObjectConfigured(void *obj)
{
    DC_FsmEventClass *dc_fec = GET_CLASS(TYPE_DC_FSMEVENT);
    DC_FromFsmEvent *This = DC_FROMFSMEVENT(obj);

    /**
     * There is no need to check whether targetFsm is NULL or not, If 
     * DC_FromFsmEvent's isObjectConfigured return true.
     */ 
    if (CC_ROOTOBJECT_CLASS(dc_fec)->isObjectConfigured(obj)) {
        CC_FSM *targetFsm = DC_FsmEvent_getTargetFsm(obj);
        return ((This->startingState >= 0) &&
                (This->startingState < CC_FSM_getNumberOfStates(targetFsm)));
    }
}

/**
 * Execute the FsmEvent: lodge a request to the target FSM to perform a
 * state transition from the
 * starting state to the target state.
 * The request is only lodged if the FSM is in the starting state.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *   if(targetFsm.getCurrentState(void) eq startingState)
 *       targetFsm.makeTransitionRequest(targetState);
 *       return ACTION_SUCCESS;
 *   else
 *       return ACTION_FAILURE; </PRE>
 * <p>
 * @return the ACTION_SUCCESS code if the transition request was lodged, 
 * the ACTION_FAILURE code if it was not
 */
static TD_ActionOutcome doAction(void *obj)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    DC_FromFsmEvent *This = DC_FROMFSMEVENT(obj);

    assert(cc_roc->isObjectConfigured(obj));

    CC_FSM *TargetFsm = DC_FsmEvent_getTargetFsm(obj);
    if (CC_FSM_getCurrentState(TargetFsm) == This->startingState) {
        DC_FsmEventClass *dc_fec = GET_CLASS(TYPE_DC_FSMEVENT);
        return PUNCTUALACTION_CLASS(dc_fec)->doAction(obj);
    } else {
        return ACTION_FAILURE;
    }
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
   DC_FromFsmEvent *This = DC_FROMFSMEVENT(obj);
   This->startingState = -1;

   CC_RootObject_setClassId((CC_RootObject*)obj, ID_FROMFSMEVENT);
}

DC_FromFsmEvent* DC_FromFsmEvent_new(void)
{
    Object *obj = object_new(TYPE_DC_FROMFSMEVENT);
    return (DC_FromFsmEvent*)obj;
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
    .name = TYPE_DC_FROMFSMEVENT,
    .parent = TYPE_DC_FSMEVENT,
    .instance_size = sizeof(DC_FromFsmEvent),
    .abstract = false,
    .class_size = sizeof(DC_FromFsmEventClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_FromFsmEvent_register(void)
{
    type_register_static(&type_info);
}
