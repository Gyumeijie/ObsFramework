//
//
// TestCaseDummyCopyControlBlock_1.h
//
//
// Change Record:

#include <math.h>
#include <float.h>

#include "TestCaseDummyCopyControlBlock_1.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../Data/ControlBlock.h"
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
    const int nEvt          = TestCaseWithEvtCheck_getNumberOfEvents(obj);
	const int numStates     = 1;
	const int numInputs     = 3;
	const int numOutputs    = 2;
	const int numParameters = 2;
    const TD_Float testInputs[] = {(TD_Float)0.3, (TD_Float)0.04, (TD_Float)0.005};
	DC_DummyCopyControlBlock *pDCB;

	// Create a new control block and verify the correctness
	// of its class identifier
	pDCB = DC_DummyCopyControlBlock_new();
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pDCB); 
    ControlBlockClass *cbc = CONTROLBLOCK_GET_CLASS(pDCB);


    if (CC_RootObject_getClassId((CC_RootObject*)pDCB) != ID_DUMMYCOPYCONTROLBLOCK) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong class identifier");
		return;
	}

	//  Verify that a newly created control block is configured
	if (!cc_roc->isObjectConfigured(pDCB)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Newly created control block is not configured");
		return;
	}

	// Verify that the numbers of inputs, outputs, states and parameters are correct
	if (ControlBlock_getNumberOfInputs((ControlBlock*)pDCB) != numInputs) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong number of inputs");
		return;
	}

	if (ControlBlock_getNumberOfOutputs((ControlBlock*)pDCB) != numOutputs) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong number of outputs");
		return;
	}

	if (ControlBlock_getNumberOfStates((ControlBlock*)pDCB) != numStates) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong number of states");
		return;
	}

	if (ControlBlock_getNumberOfParameters((ControlBlock*)pDCB) != numParameters) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong number of parameters");
		return;
	}

	// Verify that the default state was correctly set
	// Don't forget to take into account rounding errors:
	// this is not a problem on a Windows PC, but it might
	// be on other platforms.
    TD_Float state = ControlBlock_getState((ControlBlock*)pDCB, 0);
	if (fabsf((float)(state-(TD_Float)1.0)) >= FLT_EPSILON) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong initial state");
		return;
	}

    // Verify that the inputs' initial values are correctly set
    int i;
    for (i=0; i<numInputs; i++) {
        TD_Float input = CopyControlBlock_getInput((CopyControlBlock*)pDCB, i);
        if (fabsf(((float)input-(TD_Float)0.0)) >= FLT_EPSILON) {
            TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                    "Wrong input value");
            return;
        }
    }

    // Set the parameters and verify their values
    for (i=0; i<numParameters; i++) {
        ControlBlock_setParameter((ControlBlock*)pDCB, i, (TD_Float)2.0);
        TD_Float parameter = ControlBlock_getParameter((ControlBlock*)pDCB, i);
        if (fabsf((float)(parameter-(TD_Float)2.0)) >= FLT_EPSILON) {
            TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                    "Wrong parameter value");
            return;
        }
    }

	// Now we propagate the inputs and verify that the state
	// and outputs are properly updated
    for (i=0; i<numInputs; i++) {
        CopyControlBlock_setInput((CopyControlBlock*)pDCB, i, testInputs[i]);
    }

	cbc->propagate(pDCB);

    state = ControlBlock_getState((ControlBlock*)pDCB, 0);
	if (fabsf((float)(state-(TD_Float)2.345)) >= FLT_EPSILON) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Error in state update");
		return;		
	}

    TD_Float output0 = CopyControlBlock_getOutput((CopyControlBlock*)pDCB, 0);
    TD_Float output1 = CopyControlBlock_getOutput((CopyControlBlock*)pDCB, 1);
	if (fabsf((float)(output0-(TD_Float)2.345)) >= FLT_EPSILON ||
		fabsf((float)(output1-(TD_Float)4.690)) >= FLT_EPSILON) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Error in output update");
		return;
	}

    // Set the outputs and verify their values
    for (i=0; i<numOutputs; i++) {
        CopyControlBlock_setOutput((CopyControlBlock*)pDCB, i, (TD_Float)3.0);

        TD_Float output = CopyControlBlock_getOutput((CopyControlBlock*)pDCB, i);
        if (fabsf((float)(output-(TD_Float)3.0)) >= FLT_EPSILON) {
            TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                    "Wrong output value");
            return;
        }
    }

    // Set the state and verify its value
    ControlBlock_setState((ControlBlock*)pDCB, 0, (TD_Float)4.0);

    state = ControlBlock_getState((ControlBlock*)pDCB, 0);
    if (fabsf((float)(state-(TD_Float)4.0)) >= FLT_EPSILON) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong state value");
        return;
    }

    // Try to set state, output, input and parameter values with an out-of-range
    // index and verify that the correct event is generated
    if (TestCase_isNonNominalCheckAllowed(obj)) {
        ControlBlock_setState((ControlBlock*)pDCB, numStates, (TD_Float)0.0);
	    if (!verifyLatestEvent(obj, nEvt+1, EVT_ILLEGAL_CB)) return;

        CopyControlBlock_setOutput((CopyControlBlock*)pDCB, numOutputs, (TD_Float)0.0);
	    if (!verifyLatestEvent(obj, nEvt+2, EVT_ILLEGAL_CB)) return;

        CopyControlBlock_setInput((CopyControlBlock*)pDCB, numInputs, (TD_Float)0.0);
	    if (!verifyLatestEvent(obj, nEvt+3, EVT_ILLEGAL_CB)) return;

        ControlBlock_setParameter((ControlBlock*)pDCB, numParameters, (TD_Float)0.0);
	    if (!verifyLatestEvent(obj, nEvt+4, EVT_ILLEGAL_CB)) return;
    }

    // Reset the control block and verify the the state is
	// set to the default value
	cbc->reset(pDCB);
    state = ControlBlock_getState((ControlBlock*)pDCB, 0);
	if (fabsf((float)(state-(TD_Float)1.0)) >= FLT_EPSILON) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, "Reset failed");
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

TestCaseDummyCopyControlBlock_1* TestCaseDummyCopyControlBlock_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEDUMMYCOPYCONTROLBLOCK_1);

    TESTCASEWITHEVTCHECK_GET_CLASS(obj)->post_init((TestCaseWithEvtCheck*)obj,
                                                ID_DUMMYCOPYCONTROLBLOCK*10+1,
                                           "TestCaseDummyCopyControlBlock_1");


    return (TestCaseDummyCopyControlBlock_1*)obj;
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
    .name = TYPE_TESTCASEDUMMYCOPYCONTROLBLOCK_1,
    .parent = TYPE_TESTCASEWITHEVTCHECK,
    .instance_size = sizeof(TestCaseDummyCopyControlBlock_1),
    .abstract = false,
    .class_size = sizeof(TestCaseDummyCopyControlBlock_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseDummyCopyControlBlock_1_register(void)
{
    type_register_static(&type_info);
}
