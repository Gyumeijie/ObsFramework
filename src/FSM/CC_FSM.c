//
//
// CC_FSM.c
//
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Event/DC_EventRepository.h"
#include "../Base/CC_RootObject.h"
#include "FsmState.h"
#include "CC_FSM.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void CC_FSM_tryTransition(CC_FSM *This, TD_FsmStateIndex targetState)
{
   CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(This);
   DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
   DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);

   assert(cc_roc->isObjectConfigured(This));
   assert(targetState >= 0);
   assert(targetState < This->numberOfStates);

   if (!CC_FSM_isTransitionEnabled(This)) {  
      dc_erc->create(dc_er, (CC_RootObject*)This, EVT_FSM_ALL_TRANSITION_DISABLED);
      return;
   }

   if (!CC_FSM_isTransitionEnabledToState(This, targetState)) {  
      dc_erc->create(dc_er, (CC_RootObject*)This, EVT_FSM_TRANSITION_DISABLED);
      return;
   }

   FsmStateClass *fsc1 = FSMSTATE_GET_CLASS(This->pCurrentState);
   if (!fsc1->canExit(This->pCurrentState)) {  
      dc_erc->create(dc_er, (CC_RootObject*)This, EVT_FSM_EXIT_FAILED);
      return;
   }

   FsmState* pTargetState = This->pState[targetState];
   FsmStateClass *fsc2 = FSMSTATE_GET_CLASS(pTargetState);
   if (!fsc2->canEnter(pTargetState)) {  
      dc_erc->create(dc_er, (CC_RootObject*)This, EVT_FSM_ENTRY_FAILED);
      return;
   }

   /**
    * In different subclass of FsmState, the class struct of FsmState may be 
    * different; So it is safe to use subclass-specific FsmState class for 
    * different state object.
    */
   fsc1->doExit(This->pCurrentState);
   This->pCurrentState = pTargetState;
   This->currentState = targetState;
   fsc2->doInit(This->pCurrentState);

   dc_erc->create(dc_er, (CC_RootObject*)This, EVT_FSM_TRANSITION);
   return;
}

void CC_FSM_reset(CC_FSM *This)
{
   assert(This->numberOfStates > 0);
   assert(This->pState[0] != pNULL);

   // Enable all state transitions
   for (TD_FsmStateIndex i=0; i<This->numberOfStates; i++) {
      This->transitionEnabled[i] = ENABLED;
   }

   This->allTransitionEnabled = ENABLED;

   // Compute the nextState indices
   const int nStates = This->numberOfStates;
   for (TD_FsmStateIndex i=0; i<nStates; i++) {  
      FsmState *pNS = FsmState_getNextState(This->pState[i]);
      if (pNS != pNULL) {   
          for (TD_FsmStateIndex j=0; j<nStates; j++) {
              if (pNS == This->pState[j]) {
                  This->pNextState[i] = j;
              }
          }
      }
   }


   /**
    * Warnig: FSMSTATE_GET_CLASS(This->pCurrentState) should be done in if
    * statement, for pCurrentState may be NULL in initai state.
    */
   if (This->currentState >= 0) {
       FsmStateClass *fsc = FSMSTATE_GET_CLASS(This->pCurrentState);
       fsc->doExit(This->pCurrentState);
   }


   This->pCurrentState = This->pState[0];
   This->currentState = 0;

   /**
    * For class FsmStateClass should be subclass-specific, so it is safe to
    * use FSMSTATE_GET_CLASS instead of reusing the previous one if exists.
    */
   FsmStateClass *fsc = FSMSTATE_GET_CLASS(This->pCurrentState);
   fsc->doInit(This->pCurrentState);
}

void CC_FSM_setNumberOfStates(CC_FSM *This, TD_FsmStateIndex numberOfStates)
{
   assert(numberOfStates > 0);
   assert(This->numberOfStates == 0);       // Method should only be called once

   This->numberOfStates = numberOfStates;

   // Create and initialize the array that holds the FSM states and their
   // next states
   This->pState = g_malloc(sizeof(FsmState*)*numberOfStates);
   for (TD_FsmStateIndex i=0; i<numberOfStates; i++) {
      This->pState[i] = pNULL;
   }

   This->pNextState = g_malloc(sizeof(TD_FsmStateIndex)*numberOfStates);
   for (TD_FsmStateIndex i=0; i<numberOfStates; i++) {
      This->pNextState[i] = -1;
   }

   // Create and initialize the array that holds the state transition
   // enable status
   This->transitionEnabled = g_malloc(sizeof(bool)*numberOfStates);
   for (TD_FsmStateIndex i=0; i<numberOfStates; i++) {
      This->transitionEnabled[i] = ENABLED;
   }
}

TD_FsmStateIndex CC_FSM_getNumberOfStates(const CC_FSM *This)
{
   return This->numberOfStates;
}

void CC_FSM_setState(CC_FSM *This, TD_FsmStateIndex i, FsmState *state)
{
   assert(This->numberOfStates > 0);
   assert((i < This->numberOfStates) && (state != pNULL));
   assert(This->pState != pNULL);

   if ((i < This->numberOfStates) && (i >= 0)) {
       This->pState[i] = state;
   } else {
       DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
       DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
       dc_erc->create(dc_er, (CC_RootObject*)This, EVT_ILLEGAL_FS);
   }
}

inline FsmState* CC_FSM_getState(const CC_FSM *This, TD_FsmStateIndex i)
{
	assert(This->numberOfStates > 0);
	assert((i < This->numberOfStates) && (This->pState[i] != pNULL));
	return This->pState[i];
}

inline TD_FsmStateIndex CC_FSM_getCurrentState(const CC_FSM *This)
{
	assert(This->numberOfStates > 0);
	return This->currentState;
}

void CC_FSM_setTransitionEnableStatus(CC_FSM *This, bool enabled)
{
    This->allTransitionEnabled = enabled;
}

void CC_FSM_setTransitionEnableStatusToState(CC_FSM *This, 
                                             TD_FsmStateIndex toState, 
                                             bool enabled)
{
    assert(toState < This->numberOfStates);
    assert(This->transitionEnabled != pNULL);

    if ((toState < This->numberOfStates) && (toState >= 0)) {
       This->transitionEnabled[toState] = enabled;
    } else {
       DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
       DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
       dc_erc->create(dc_er, (CC_RootObject*)This, EVT_ILLEGAL_FS);
    }
}


bool CC_FSM_isTransitionEnabled(const CC_FSM *This)
{
	return This->allTransitionEnabled;
}

bool CC_FSM_isTransitionEnabledToState(const CC_FSM *This, 
                                       TD_FsmStateIndex toState)
{
	assert(toState < This->numberOfStates);
	assert(toState >= 0);
	return This->transitionEnabled[toState];
}

void CC_FSM_makeTransitionRequest(CC_FSM *This, TD_FsmStateIndex targetState)
{
   CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(This);

   assert(cc_roc->isObjectConfigured(This));
   assert(targetState >= 0);
   assert(targetState < This->numberOfStates);

   if ((targetState < This->numberOfStates) && (targetState >= 0)) {
       This->requestedTargetState = targetState;
   } else {
       DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
       DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
       dc_erc->create(dc_er, (CC_RootObject*)This, EVT_ILLEGAL_FS);
   }
}

void CC_FSM_activate(CC_FSM *This)
{
   CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(This);
   FsmStateClass *fsc = FSMSTATE_GET_CLASS(This->pCurrentState);  

   assert(cc_roc->isObjectConfigured(This));

   // a state transition request is pending
   if (This->requestedTargetState >= 0) {  
      CC_FSM_tryTransition(This, This->requestedTargetState);
      This->requestedTargetState = -1;
      fsc->doContinue(This->pCurrentState);
      return;
   }

   if ((fsc->isFinished(This->pCurrentState)) &&
       (FsmState_getNextState(This->pCurrentState) != pNULL)) {
       CC_FSM_tryTransition(This, This->pNextState[This->currentState]);
   }

   fsc->doContinue(This->pCurrentState);

   return;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Perform a class-specific configuration check on an FSM object: verify
 * that the number of states
 * has a legal value and that all FsmState objects have been loaded.
 */
static bool isObjectConfigured(void *obj)
{
   CC_RootObjectClass *cc_roc = GET_CLASS(TYPE_CC_ROOTOBJECT);
   CC_FSM *This = CC_FSM(obj);

   if (!(cc_roc->isObjectConfigured(obj)) || 
        (This->numberOfStates <= 0) || 
        (This->pCurrentState == pNULL)) {
       return NOT_CONFIGURED;
   }

   for (TD_FsmStateIndex i=0; i<This->numberOfStates; i++) {
       if (This->pState[i] == pNULL) return NOT_CONFIGURED;
   }

   return CONFIGURED;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
   CC_FSM *This = CC_FSM(obj);
   This->pCurrentState = pNULL;
   This->numberOfStates = 0;
   This->currentState = -1;
   This->requestedTargetState = -1;

   CC_RootObject_setClassId((CC_RootObject*)obj, ID_FSM);
}

CC_FSM* CC_FSM_new(void)
{
    Object *obj = object_new(TYPE_CC_FSM);
    return (CC_FSM*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_CC_FSM,
    .parent = TYPE_CC_ROOTOBJECT,
    .instance_size = sizeof(CC_FSM),
    .abstract = false,
    .class_size = sizeof(CC_FSMClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void CC_FSM_register(void)
{
    type_register_static(&type_info);
}
