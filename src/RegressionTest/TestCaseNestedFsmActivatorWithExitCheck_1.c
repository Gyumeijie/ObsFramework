//
//
// TestCaseNestedFsmActivatorWithExitCheck_1.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/TestConstants.h"
#include "../FSM/DC_FsmEvent.h"
#include "../FSM/DC_DummyFsmState.h"
#include "../FSM/DC_NestedFsmActivatorWithExitCheck.h"
#include "TestCaseNestedFsmActivatorWithExitCheck_1.h"



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
	CC_FSM *pFSM = CC_FSM_new();
	DC_NestedFsmActivatorWithExitCheck *pNFA = DC_NestedFsmActivatorWithExitCheck_new();
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pNFA);
    FsmStateClass *fsc = FSMSTATE_GET_CLASS(pNFA);

	const TD_FsmStateIndex numStates  =8;
	const TD_FsmStateIndex targetState=5;
	DC_DummyFsmState *pFS[numStates];
	DC_FsmEvent *pFE[numStates];

	// Initialize the FSM
	CC_FSM_setNumberOfStates(pFSM, numStates);

	for (TD_FsmStateIndex i=0; i<numStates; i++) {
		// Create and load FSM states
		pFS[i] = DC_DummyFsmState_new();
		CC_FSM_setState(pFSM, i, (FsmState*)pFS[i]);

		// Create and configure FSM events
		pFE[i] = DC_FsmEvent_new();
		DC_FsmEvent_setTargetFsm(pFE[i], pFSM);
		DC_FsmEvent_setTargetState(pFE[i], (i+1)%numStates);
	}

	CC_FSM_reset(pFSM);

	// Verify the correctness of the class id
	if (CC_RootObject_getClassId((CC_RootObject*)pNFA) != ID_NESTEDFSMACTIVATORWITHEXITCHECK) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong class id");
		return;
	}

	// The object shall not be configured yet
	if (cc_roc->isObjectConfigured(pNFA)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Newly created object is configured");
		return;
	}

	// Let's attach the nested FSM to the state and verify that
	// object is not yet configured
	DC_NestedFsmActivator_setTargetFsm((DC_NestedFsmActivator*)pNFA, pFSM);

	if (cc_roc->isObjectConfigured(pNFA)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Object is wrongly configured");
		return;
	}

	// After setting the target state the object should be configured
	DC_NestedFsmActivatorWithExitCheck_setTargetState(pNFA, targetState);

	if (DC_NestedFsmActivatorWithExitCheck_getTargetState(pNFA) != targetState) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "setTargetState() failed");
		return;
	}

	if (!cc_roc->isObjectConfigured(pNFA)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Object is not configured");
		return;
	}

	// Verify that canExit() returns true only when tha machine is
	// in the right state
	for (TD_FsmStateIndex i=0;i<numStates;i++) {
		PunctualAction_execute((PunctualAction*)pFE[i]);
		fsc->doContinue(pNFA);

		if ((fsc->canExit(pNFA) && CC_FSM_getCurrentState(pFSM) != targetState) ||
			(!fsc->canExit(pNFA) && CC_FSM_getCurrentState(pFSM) == targetState)) {
			TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                    "canExit() failed");
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

TestCaseNestedFsmActivatorWithExitCheck_1* TestCaseNestedFsmActivatorWithExitCheck_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASENESTEDFSMACTIVATORWITHEXITCHECK_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                      ID_NESTEDFSMACTIVATORWITHEXITCHECK*10+1,
						         "TestCaseNestedFsmActivatorWithExitCheck_1"); 

    return (TestCaseNestedFsmActivatorWithExitCheck_1*)obj;
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
    .name = TYPE_TESTCASENESTEDFSMACTIVATORWITHEXITCHECK_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseNestedFsmActivatorWithExitCheck_1),
    .abstract = false,
    .class_size = sizeof(TestCaseNestedFsmActivatorWithExitCheck_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseNestedFsmActivatorWithExitCheck_1_register(void)
{
    type_register_static(&type_info);
}
