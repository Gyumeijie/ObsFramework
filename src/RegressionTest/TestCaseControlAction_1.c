//
//
// TestCaseControlAction_1.c
//
//
// Change Record:

#include "../Data/ControlBlock.h"
#include "TestCaseControlAction_1.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Data/DC_ControlAction.h"
#include "../Data/DC_DummyCopyControlBlock.h"



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
	DC_ControlAction *pAct= DC_ControlAction_new();
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pAct);

	// Verify correctness of the class identifier
	if (CC_RootObject_getClassId((CC_RootObject*)pAct) != ID_CONTROLACTION) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong class identifier");
		return;
	}

    // Check that component is not configured
    if (cc_roc->isObjectConfigured(pAct)) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong configuration status");
		return;
	}

    // Create and configure a dummy control block
	DC_DummyCopyControlBlock *pDCB = DC_DummyCopyControlBlock_new();
	const unsigned int numInputs = 3;
    const TD_Float inputValues[] = {(TD_Float)0.3,(TD_Float)0.04,(TD_Float)0.05};

    // Set control block inputs
	for (unsigned int i=0; i<numInputs; i++) {
		CopyControlBlock_setInput((CopyControlBlock*)pDCB, i, inputValues[i]);
    }

    // Load the control block and check success of load operations
    DC_ControlAction_setTargetControlBlock(pAct, (ControlBlock*)pDCB);
    if (DC_ControlAction_getTargetControlBlock(pAct) != (ControlBlock*)pDCB)
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Loaded control block is wrong");
		return;
	}

    // Check that component is configured
    if (!cc_roc->isObjectConfigured(pAct)) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong configuration status");
		return;
	}

    // Check the execution request (as a result of an execution request
    // the value of the first element of the state should change)
    TD_Float initialState = ControlBlock_getState((ControlBlock*)pDCB, 0);

    PunctualAction_execute((PunctualAction*)pAct);
    if (ControlBlock_getState((ControlBlock*)pDCB, 0) == initialState) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Execution request failure");
		return;
	}

    // Check the reset request (as a result of a reset request, the 
    // value of the first element of the state should go back to its 
    // old value
    DC_ControlAction_reset(pAct);
    if (ControlBlock_getState((ControlBlock*)pDCB, 0) != initialState)
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Reset request failure");
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

TestCaseControlAction_1* TestCaseControlAction_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASECONTROLACTION_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                        ID_CONTROLACTION*10+1,
		                                            "TestCaseControlAction_1"); 

    return (TestCaseControlAction_1*)obj;
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
    .name = TYPE_TESTCASECONTROLACTION_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseControlAction_1),
    .abstract = false,
    .class_size = sizeof(TestCaseControlAction_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseControlAction_1_register(void)
{
    type_register_static(&type_info);
}
