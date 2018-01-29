//
//
// TestCaseFSM_2.c
//

#include "TestCaseFSM_2.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "../FSM/CC_FSM.h"
#include "../FSM/DC_DummyFsmState.h"
#include "../FSM/DC_FsmEvent.h"
#include "../Base/CC_RootObject.h"
#include "../Event/DC_EventRepository.h"



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Execute the test case. See class comment for details.
 */
static void runTestCase(void *obj)
{

   CC_FSM *pFsm = CC_FSM_new();
   CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pFsm);

   // Configure the FSM
   CC_FSM_setNumberOfStates(pFsm, 4);

   DC_DummyFsmState *pState[4];
   const int nStates = CC_FSM_getNumberOfStates(pFsm);
   for (TD_FsmStateIndex i=0; i<nStates; i++) {
      pState[i] = DC_DummyFsmState_new();
   }

   for (TD_FsmStateIndex i=0; i<nStates; i++) {
      CC_FSM_setState(pFsm, i, (FsmState*)pState[i]);
   }

   CC_FSM_reset(pFsm);

   // FSM object should now be configured
   if ((cc_roc->isObjectConfigured(pFsm) == NOT_CONFIGURED)) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
        "Wrong FSM configuration status after configuration was completed");
		return;
   }

   // Create and configure the FsmEvents
   DC_FsmEvent *pFsmEvt_1 = DC_FsmEvent_new();
   DC_FsmEvent *pFsmEvt_2 = DC_FsmEvent_new();
   DC_FsmEvent *pFsmEvt_3 = DC_FsmEvent_new();
   DC_FsmEvent_setTargetFsm(pFsmEvt_1, pFsm);
   DC_FsmEvent_setTargetFsm(pFsmEvt_2, pFsm);
   DC_FsmEvent_setTargetFsm(pFsmEvt_3, pFsm);
   DC_FsmEvent_setTargetState(pFsmEvt_1, 1);
   DC_FsmEvent_setTargetState(pFsmEvt_2, 2);
   DC_FsmEvent_setTargetState(pFsmEvt_3, 0);

   // Activate FSM twice (just to exercise the FSM)
   CC_FSM_activate(pFsm);
   CC_FSM_activate(pFsm);

   // Fire FsmEvent 1 and check transition
   PunctualAction_execute((PunctualAction*)pFsmEvt_1);
   if (CC_FSM_getCurrentState(pFsm) != 0) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
        "No state transition should have occurred");
		return;
   }
   CC_FSM_activate(pFsm);
   if (CC_FSM_getCurrentState(pFsm) != 1) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
        "Wrong state after FsmEvt_1 firing");
		return;
   }

   // Check that the correct event was created
   DC_EventRepository *pRep = CC_RootObject_getEventRepository();
   DC_EventRepository_latest(pRep);
   if (DC_EventRepository_getEventType(pRep) != EVT_FSM_TRANSITION) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
        "Wrong event after state transition");
		return;
   }

   // Activate FSM twice and check that no state transition takes place
   CC_FSM_activate(pFsm);
   CC_FSM_activate(pFsm);
   if (CC_FSM_getCurrentState(pFsm) != 1) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
        "Wrong state after activation of FSM");
		return;
   }

   // Fire events 2 and 3 and check that only second firing has an effect
   PunctualAction_execute((PunctualAction*)pFsmEvt_2);
   PunctualAction_execute((PunctualAction*)pFsmEvt_3);
   CC_FSM_activate(pFsm);
   if (CC_FSM_getCurrentState(pFsm) != 0) {	
        TestCase_setTestResult((TestCase*)obj,TEST_FAILURE,
        "Wrong state after FsmEvt_2 and FsmEvt_3 firing");
		return;
   }

   // Activate FSM twice (just to exercise state 0)
   CC_FSM_activate(pFsm);
   CC_FSM_activate(pFsm);

   // Disable transitions into state 2, fire FsmEvt_2 and check that
   // no transition takes place
   CC_FSM_setTransitionEnableStatusToState(pFsm, 2, DISABLED);
   PunctualAction_execute((PunctualAction*)pFsmEvt_2);
   CC_FSM_activate(pFsm);
   if (CC_FSM_getCurrentState(pFsm) != 0) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
        "Wrong state after FsmEvt_2 firing");
		return;
   }

   // Check that the correct event was created
   DC_EventRepository_latest(pRep);
   if (DC_EventRepository_getEventType(pRep) != EVT_FSM_TRANSITION_DISABLED) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
        "Wrong event after state transition");
		return;
   }

    // Attempt to disable transition into non-existent state
    if (TestCase_isNonNominalCheckAllowed(obj)) {
        CC_FSM_setTransitionEnableStatusToState(pFsm, 4, DISABLED);
        DC_EventRepository_latest(pRep);
        if (DC_EventRepository_getEventType(pRep) != EVT_ILLEGAL_FS) {	
            TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
            "Failure of non-nominal behaviour check");
		    return;
	    }
    }

    TestCase_setTestResult((TestCase*)obj, TEST_SUCCESS, "Test Successful");
	return;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj) {} 

TestCaseFSM_2* TestCaseFSM_2_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEFSM_2);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
	                                                ID_FSM*10+2,
                                                    "TestCaseFSM_2"); 
    return (TestCaseFSM_2*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    TestCaseClass *tcc = TESTCASE_CLASS(oc);
    tcc->runTestCase = runTestCase;
}

static const TypeInfo type_info = {
    .name = TYPE_TESTCASEFSM_2,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseFSM_2),
    .abstract = false,
    .class_size = sizeof(TestCaseFSM_2Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseFSM_2_register(void)
{
    type_register_static(&type_info);
}
