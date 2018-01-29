//
//
// TestCaseFSM_3.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "../FSM/CC_FSM.h"
#include "../FSM/DC_DummyConfigurableFsmState.h"
#include "../FSM/DC_FsmEvent.h"
#include "../FSM/FsmState.h"
#include "../Base/CC_RootObject.h"
#include "../Event/DC_EventRepository.h"
#include "TestCaseFSM_3.h"



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

   DC_DummyConfigurableFsmState *pState[4];
   const int nStates = CC_FSM_getNumberOfStates(pFsm);

   for (TD_FsmStateIndex i=0; i<nStates; i++) {
      pState[i] = DC_DummyConfigurableFsmState_new();
   }

   FsmState_setNextState((FsmState*)pState[0], (FsmState*)pState[1]);
   FsmState_setNextState((FsmState*)pState[1], (FsmState*)pState[2]);
   FsmState_setNextState((FsmState*)pState[2], (FsmState*)pState[3]);
   FsmState_setNextState((FsmState*)pState[3], (FsmState*)pState[0]);

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

   // Check the correctness of the class identifier
   if ((CC_RootObject_getClassId((CC_RootObject*)pState[0]) != ID_DUMMYCONFIGURABLEFSMSTATE)) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
        "Wrong class identifier for the dummy configurable FsmState class");
	   return;
	}

   // Activate FSM twice and check that state 0 is executed
   CC_FSM_activate(pFsm);
   CC_FSM_activate(pFsm);
   if (DC_DummyConfigurableFsmState_getActivationCounter(pState[0]) != 2) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
        "Wrong value of activation counter for state 0");
		return;
	}

   // Verify value of initialization counter
   if (DC_DummyConfigurableFsmState_getInitializationCounter(pState[0]) != 1) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
        "Wrong value of initialization counter for state 0");
		return;
	}

   // Force and check state transition to state 1
   DC_DummyConfigurableFsmState_setTerminationCheckValue(pState[0], true);
   CC_FSM_activate(pFsm);
   if (CC_FSM_getCurrentState(pFsm) != 1) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
        "State transition to state 1 failed to take place");
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

   // Check exit, initialization and activation counters
   if (DC_DummyConfigurableFsmState_getExitCounter(pState[0]) != 1) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
        "Wrong value of exit counter for state 0");
		return;
   }
   if (DC_DummyConfigurableFsmState_getInitializationCounter(pState[1]) != 1) {	
        TestCase_setTestResult((TestCase*)obj,TEST_FAILURE,
        "Wrong value of initialization counter for state 1");
		return;
   }
   if (DC_DummyConfigurableFsmState_getActivationCounter(pState[1]) != 1) {	
        TestCase_setTestResult((TestCase*)obj,TEST_FAILURE,
        "Wrong value of activation counter for state 1");
		return;
   }

   // Disable autonomous transition by disabling exit check and verify that
   // no transition takes place
   DC_DummyConfigurableFsmState_setExitCheckValue(pState[1], false);
   DC_DummyConfigurableFsmState_setTerminationCheckValue(pState[1], true);
   CC_FSM_activate(pFsm);
   if (CC_FSM_getCurrentState(pFsm) != 1) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
        "Illegal state transition out of state 1 took place");
		return;
	}

   // Check that the correct event was created
   pRep = CC_RootObject_getEventRepository();
   DC_EventRepository_latest(pRep);
   if (DC_EventRepository_getEventType(pRep) != EVT_FSM_EXIT_FAILED) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
        "Wrong event after failure of exit check");
		return;
	}

    // Check that the last FSM activation caused the execution of state 1
   if (DC_DummyConfigurableFsmState_getActivationCounter(pState[1]) != 2) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
        "Wrong value of activation counter for state 1");
		return;
	}

   // Disable autonomous transition by disabling entry check and verify that
   // no transition takes place
   DC_DummyConfigurableFsmState_setExitCheckValue(pState[1], true);
   DC_DummyConfigurableFsmState_setInitializationCheckValue(pState[2], false);
   CC_FSM_activate(pFsm);
   if (CC_FSM_getCurrentState(pFsm) != 1) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
        "Illegal state transition out of state 1 took place");
		return;
	}

   // Check that the correct event was created
   pRep = CC_RootObject_getEventRepository();
   DC_EventRepository_latest(pRep);
   if (DC_EventRepository_getEventType(pRep) != EVT_FSM_ENTRY_FAILED) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
        "Wrong event after failure of exit check");
		return;
	}

   // Disable autonomous transitions by disabling FSM transitions into state 2
   // and verify that no transition takes place
   DC_DummyConfigurableFsmState_setInitializationCheckValue(pState[2], true);
   CC_FSM_setTransitionEnableStatusToState(pFsm, 2, DISABLED);
   CC_FSM_activate(pFsm);
   if (CC_FSM_getCurrentState(pFsm) != 1) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
        "Illegal state transition out of state 1 took place");
		return;
	}

   // Check that the correct event was created
   pRep = CC_RootObject_getEventRepository();
   DC_EventRepository_latest(pRep);
   if (DC_EventRepository_getEventType(pRep) != EVT_FSM_TRANSITION_DISABLED) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
        "Wrong event after failure of exit check");
		return;
	}

   // Disable autonomous transitions by disabling all FSM transitions
   // and verify that no transition takes place
   CC_FSM_setTransitionEnableStatusToState(pFsm, 2, ENABLED);
   CC_FSM_setTransitionEnableStatus(pFsm, DISABLED);
   CC_FSM_activate(pFsm);
   if (CC_FSM_getCurrentState(pFsm) != 1) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
        "Illegal state transition out of state 1 took place");
		return;
	}

   // Check that the correct event was created
   pRep = CC_RootObject_getEventRepository();
   DC_EventRepository_latest(pRep);
   if (DC_EventRepository_getEventType(pRep) != EVT_FSM_ALL_TRANSITION_DISABLED) {
        TestCase_setTestResult((TestCase*)obj,TEST_FAILURE,
        "Wrong event after failure of exit check");
		return;
	}

   // Enable autonomous transitions and verify that transition takes place
   CC_FSM_setTransitionEnableStatus(pFsm, ENABLED);
   CC_FSM_activate(pFsm);
   if (CC_FSM_getCurrentState(pFsm) != 2)
	{	TestCase_setTestResult((TestCase*)obj,TEST_FAILURE,
             "State transition to state 2 failed to take place");
		return;
	}

   // Check exit, initialization and activation counters
   if (DC_DummyConfigurableFsmState_getExitCounter(pState[1]) != 1) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
        "Wrong value of exit counter for state 1");
		return;
	}
   if (DC_DummyConfigurableFsmState_getInitializationCounter(pState[2]) != 1) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
        "Wrong value of initialization counter for state 2");
		return;
	}
   if (DC_DummyConfigurableFsmState_getActivationCounter(pState[2]) != 1) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
        "Wrong value of activation counter for state 2");
		return;
	}

    // Attempt to commands transition into non-existent state
    if (TestCase_isNonNominalCheckAllowed(obj)) {
        CC_FSM_makeTransitionRequest(pFsm, 4);
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

static void instance_init(Object *obj){}

TestCaseFSM_3* TestCaseFSM_3_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEFSM_3);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                    ID_FSM*10+3,
                                                    "TestCaseFSM_3"); 

    return (TestCaseFSM_3*)obj;
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
    .name = TYPE_TESTCASEFSM_3,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseFSM_3),
    .abstract = false,
    .class_size = sizeof(TestCaseFSM_3Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseFSM_3_register(void)
{
    type_register_static(&type_info);
}
