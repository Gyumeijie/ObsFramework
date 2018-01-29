//
//
// TestCaseNestedFsmActivator_1.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/TestConstants.h"
#include "../FSM/DC_FsmEvent.h"
#include "../FSM/DC_DummyFsmState.h"
#include "../FSM/DC_NestedFsmActivator.h"
#include "TestCaseNestedFsmActivator_1.h"



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
	DC_NestedFsmActivator *pNFA = DC_NestedFsmActivator_new();
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pNFA);
    FsmStateClass *fsc = FSMSTATE_GET_CLASS(pNFA);

	const TD_FsmStateIndex numStates = 3;
	DC_DummyFsmState      *pFS[numStates];
	DC_FsmEvent           *pFE[numStates];

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
	if (CC_RootObject_getClassId((CC_RootObject*)pNFA) != ID_NESTEDFSMACTIVATOR) {
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
	// the FSM pointer is properly stored and the object is configured
	DC_NestedFsmActivator_setTargetFsm(pNFA, pFSM);

	if (DC_NestedFsmActivator_getTargetFsm(pNFA) != pFSM) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "setTargetFsm() failed");
		return;
	}

	if (!cc_roc->isObjectConfigured(pNFA)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Object is not configured");
		return;
	}

	// Force a FSM transition and verify that doInit() performs
	// a reset of the nested FSM
	PunctualAction_execute((PunctualAction*)pFE[0]);
	CC_FSM_activate(pFSM);

	fsc->doInit(pNFA);
	if (CC_FSM_getCurrentState(pFSM)!=0) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "doInit() failed");
		return;
	}

	// Let's see if doContinue() activates the nested FSM
	PunctualAction_execute((PunctualAction*)pFE[1]);
	fsc->doContinue(pNFA);
	if (CC_FSM_getCurrentState(pFSM) != DC_FsmEvent_getTargetState(pFE[1])) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "doContinue() failed");
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

TestCaseNestedFsmActivator_1* TestCaseNestedFsmActivator_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASENESTEDFSMACTIVATOR_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                    ID_NESTEDFSMACTIVATOR*10+1,
                                                    "TestCaseNestedFsmActivator_1"); 

    return (TestCaseNestedFsmActivator_1*)obj;
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
    .name = TYPE_TESTCASENESTEDFSMACTIVATOR_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseNestedFsmActivator_1),
    .abstract = false,
    .class_size = sizeof(TestCaseNestedFsmActivator_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseNestedFsmActivator_1_register(void)
{
    type_register_static(&type_info);
}
