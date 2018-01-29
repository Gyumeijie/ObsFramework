//
//
// TestCaseFromFsmEvent_1.c
//

#include "TestCaseFromFsmEvent_1.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "../FSM/CC_FSM.h"
#include "../FSM/DC_DummyFsmState.h"
#include "../FSM/DC_FromFsmEvent.h"



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
   CC_RootObjectClass *cc_roc1 = CC_ROOTOBJECT_GET_CLASS(pFsm);
   if ((cc_roc1->isObjectConfigured(pFsm) == NOT_CONFIGURED)) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
        "Wrong FSM configuration status after configuration was completed");
		return;
	}

   // Create one FromFsmEvents
   DC_FromFsmEvent *pFsmEvt_1 = DC_FromFsmEvent_new();

   // Check the correctness of the class identifier
   if ((CC_RootObject_getClassId((CC_RootObject*)pFsmEvt_1) != ID_FROMFSMEVENT)) {	
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong class identifier");
	   return;
	}

   // Check that FromFsmEvent is not configured
   CC_RootObjectClass *cc_roc2 = CC_ROOTOBJECT_GET_CLASS(pFsmEvt_1);
   if ((cc_roc2->isObjectConfigured(pFsmEvt_1) == CONFIGURED)) {	
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong configuration status");
		return;
   }

   // Configure the FromFsmEvent object and check the success of the
   // class-specific configuration action
   TD_FsmStateIndex evtStartingState = 2;
   TD_FsmStateIndex evtTargetState = 3;
   DC_FsmEvent_setTargetFsm((DC_FsmEvent*)pFsmEvt_1, pFsm);
   DC_FsmEvent_setTargetState((DC_FsmEvent*)pFsmEvt_1, evtTargetState);
   DC_FromFsmEvent_setStartingState(pFsmEvt_1, evtStartingState);
   if (DC_FromFsmEvent_getStartingState(pFsmEvt_1) != evtStartingState) {	
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong starting state");
		return;
   }

   // Check that the FromFsmEvent is configured
   if ((cc_roc2->isObjectConfigured(pFsmEvt_1) != CONFIGURED)) {	
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong configuration status");
		return;
   }

   // Fire the FromFsmEvent from an FSM state other than its starting space
   TD_FsmStateIndex fsmState_1 = 1;
   CC_FSM_makeTransitionRequest(pFsm, fsmState_1);
   CC_FSM_activate(pFsm);
   if (PunctualAction_execute((PunctualAction*)pFsmEvt_1) != ACTION_FAILURE) {	
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong execution return value");
		return;
   }

   CC_FSM_activate(pFsm);
   if (CC_FSM_getCurrentState(pFsm) != fsmState_1) {	
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, "Wrong FSM state");
		return;
   }

   // Fire the FromFsmEvent from an FSM state equal to its starting space
   TD_FsmStateIndex fsmState_2 = evtStartingState;
   CC_FSM_makeTransitionRequest(pFsm, fsmState_2);
   CC_FSM_activate(pFsm);
   if (PunctualAction_execute((PunctualAction*)pFsmEvt_1) != ACTION_SUCCESS) {	
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong execution return value");
		return;
   }

   CC_FSM_activate(pFsm);
   if (CC_FSM_getCurrentState(pFsm) != evtTargetState) {	
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, "Wrong FSM state");
		return;
   }

	TestCase_setTestResult((TestCase*)obj, TEST_SUCCESS, "Test Successful");
	return;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj){}

TestCaseFromFsmEvent_1* TestCaseFromFsmEvent_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEFROMFSMEVENT_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                    ID_FROMFSMEVENT*10+1,
                                                    "TestCaseFromFsmEvent_1"); 

    return (TestCaseFromFsmEvent_1*)obj;
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
    .name = TYPE_TESTCASEFROMFSMEVENT_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseFromFsmEvent_1),
    .abstract = false,
    .class_size = sizeof(TestCaseFromFsmEvent_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseFromFsmEvent_1_register(void)
{
    type_register_static(&type_info);
}
