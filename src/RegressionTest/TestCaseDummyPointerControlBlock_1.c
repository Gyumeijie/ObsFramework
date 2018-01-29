//
//
// TestCaseDummyPointerControlBlock_1.c
//
//
// Change Record:

#include <math.h>
#include <float.h>

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "../Data/ControlBlock.h"
#include "../Data/DC_DummyPointerControlBlock.h"
#include "TestCaseDummyPointerControlBlock_1.h"



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
    TD_Float inputs[numInputs];
    TD_Float outputs[numOutputs];
    const TD_Float testInputs[] ={(TD_Float)0.3, (TD_Float)0.04, (TD_Float)0.005};

	DC_DummyPointerControlBlock *pDCB = DC_DummyPointerControlBlock_new();
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pDCB); 
    ControlBlockClass *cbc = CONTROLBLOCK_GET_CLASS(pDCB);


	// Verify the correctness of the class identifier
    if (CC_RootObject_getClassId((CC_RootObject*)pDCB) != ID_DUMMYPOINTERCONTROLBLOCK) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong class identifier");
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

    // Link inputs and outputs and verify its configuration status
    int i;
    for (i=0; i<numInputs; i++) {
        if (cc_roc->isObjectConfigured(pDCB)) {
            TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                    "Wrong configuration status");
            return;
        }

        PointerControlBlock_setInputLink((PointerControlBlock*)pDCB, i, &inputs[i]);
    }

    for (i=0; i<numOutputs; i++) {
        if (cc_roc->isObjectConfigured(pDCB)) {
            TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                   "Wrong configuration status");
            return;
        }

        PointerControlBlock_setOutputLink((PointerControlBlock*)pDCB, i, &outputs[i]);
    }

    if (!cc_roc->isObjectConfigured(pDCB)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong configuration status");
        return;
    }

    // Reset the control block
    cbc->reset(pDCB);

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
        inputs[i] = testInputs[i];
    }

	cbc->propagate(pDCB);

    state = ControlBlock_getState((ControlBlock*)pDCB, 0);
	if (fabsf((float)(state-(TD_Float)2.345)) >= FLT_EPSILON) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Error in state update");
		return;		
	}

	if (fabsf((float)(outputs[0]-(TD_Float)2.345)) >= FLT_EPSILON ||
		fabsf((float)(outputs[1]-(TD_Float)4.690)) >= FLT_EPSILON) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Error in output update");
		return;
	}

    // Set the state and verify its value
    ControlBlock_setState((ControlBlock*)pDCB, 0, (TD_Float)4.0);

    state = ControlBlock_getState((ControlBlock*)pDCB, 0);
    if (fabsf((float)(state-(TD_Float)4.0)) >= FLT_EPSILON) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong state value");
        return;
    }

    if (TestCase_isNonNominalCheckAllowed(obj)) {
        // Try to link input and output with an out-of-range
        // index and verify that the correct event is generated
        PointerControlBlock_setInputLink((PointerControlBlock*)pDCB, 
                                          numInputs, &inputs[0]);
	    if (!verifyLatestEvent(obj, nEvt+1, EVT_ILLEGAL_CB)) return;

        PointerControlBlock_setOutputLink((PointerControlBlock*)pDCB, 
                                           numOutputs, &outputs[0]);
	    if (!verifyLatestEvent(obj, nEvt+2, EVT_ILLEGAL_CB)) return;

        // Try to set state and parameter values with an out-of-range
        // index and verify that the correct event is generated
        ControlBlock_setState((ControlBlock*)pDCB, numStates, (TD_Float)0.0);
	    if (!verifyLatestEvent(obj, nEvt+3, EVT_ILLEGAL_CB)) return;

        ControlBlock_setParameter((ControlBlock*)pDCB, numParameters, (TD_Float)0.0);
	    if (!verifyLatestEvent(obj, nEvt+4, EVT_ILLEGAL_CB)) return;
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

TestCaseDummyPointerControlBlock_1* TestCaseDummyPointerControlBlock_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEDUMMYPOINTERCONTROLBLOCK_1);

    TESTCASEWITHEVTCHECK_GET_CLASS(obj)->post_init((TestCaseWithEvtCheck*)obj,
                                             ID_DUMMYPOINTERCONTROLBLOCK*10+1,
                                        "TestCaseDummyPointerControlBlock_1"); 

    return (TestCaseDummyPointerControlBlock_1*)obj;
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
    .name = TYPE_TESTCASEDUMMYPOINTERCONTROLBLOCK_1,
    .parent = TYPE_TESTCASEWITHEVTCHECK,
    .instance_size = sizeof(TestCaseDummyPointerControlBlock_1),
    .abstract = false,
    .class_size = sizeof(TestCaseDummyPointerControlBlock_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseDummyPointerControlBlock_1_register(void)
{
    type_register_static(&type_info);
}
