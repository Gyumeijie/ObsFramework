//
//
// TestCaseControlList_1.c
//
//
// Change Record:
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Data/ControlBlock.h"
#include "../Data/DC_DummyCopyControlBlock.h"
#include "../Data/DC_ControlList.h"
#include "TestCaseControlList_1.h"

#include <math.h>
#include <float.h>



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
    const unsigned int nEvt = TestCaseWithEvtCheck_getNumberOfEvents(obj);
	const unsigned int listSize = 2;
	const unsigned int numInputs = 3;
	const unsigned int numOutputs = 2;
	const unsigned int numParameters = 2;
	DC_DummyCopyControlBlock *pDCB[listSize];

	DC_ControlList *pCL = DC_ControlList_new();
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pCL);

	// Create and initialize the control blocks needed to
	// test the DC_ControlList class
    for (unsigned int i=0;i<listSize;i++) {
       pDCB[i] = DC_DummyCopyControlBlock_new();

       // Initialize input, output and parameters
       for (unsigned int t=0; t<numInputs; t++) {
          CopyControlBlock_setInput((CopyControlBlock*)pDCB[i], t, (TD_Float)1.0);
       }

       for (unsigned int t=0; t<numOutputs; t++) {
          CopyControlBlock_setOutput((CopyControlBlock*)pDCB[i], t, (TD_Float)0.0);
       }

       for (unsigned int t=0; t<numParameters; t++) {
           ControlBlock_setParameter((ControlBlock*)pDCB[i], t, (TD_Float)1.0);
       }
    }

	// Verify the correctness of the class id
	if (CC_RootObject_getClassId((CC_RootObject*)pCL) != ID_CONTROLLIST) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong class identifier");
		return;
	}

	// A new object shall not be configured
	if (cc_roc->isObjectConfigured(pCL)) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Newly created object already configured");
		return;
	}

	// Set the list size and verify it is reported correctly
    DC_ControlList_setListSize(pCL, listSize);
	if (DC_ControlList_getListSize(pCL) != listSize) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "getListSize() failed");
		return;
	}

	// Load and get the control blocks
	for (unsigned int i=0; i<listSize; i++) {
	    // The object is fully configured only when all the control blocks are loaded!
	    if (cc_roc->isObjectConfigured(pCL)) {
		    TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                    "Wrong configuration status");
		    return;
	    }

		DC_ControlList_setControlBlock(pCL, i, (ControlBlock*)pDCB[i]);

		if (DC_ControlList_getControlBlock(pCL, i) != (ControlBlock*)pDCB[i])
        {
			TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                    "setControlBlock() failed");
			return;
		}
	}

	// Only now it is configured. Let's check it.
	if (!cc_roc->isObjectConfigured(pCL)) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Object not configured");
		return;
	}

    // Verify that setControlBlock() generates an error report
	// when invoked with an invalid index
    if (TestCase_isNonNominalCheckAllowed(obj)) {
    	DC_ControlList_setControlBlock(pCL, listSize, (ControlBlock*)pDCB[0]);
        if (!verifyLatestEvent(obj, nEvt+1, EVT_ILLEGAL_CL)) 
        {
		    TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                    "Failure of non-nominal behaviour check");
		    return;
        }
    }

    // Let's invoke execute() and verify that it returns the correct code
    if (PunctualAction_execute((PunctualAction*)pCL) != ACTION_SUCCESS) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong execution return code");
		return;
    }

    // The control block's outputs should have been updated
    for (unsigned int i=0; i<listSize; i++) {
        TD_Float output = CopyControlBlock_getOutput((CopyControlBlock*)pDCB[i], 0);
        if (fabsf((float)output) <= FLT_EPSILON) 
        {
            TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                   "Control block's propagate() not invoked");
            return;
        }
    }

    // Reset the control list and verify the the control blocks'
    // states are set to their default value
    DC_ControlList_reset(pCL);
    for (unsigned int i=0; i<listSize; i++) {
        ControlBlock *cb = DC_ControlList_getControlBlock(pCL, i);

        if (fabsf((float)(ControlBlock_getState(cb, 0)-1.0f)) >= FLT_EPSILON) 
        {
            TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                    "Reset failed");
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

TestCaseControlList_1* TestCaseControlList_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASECONTROLLIST_1);

    TESTCASEWITHEVTCHECK_GET_CLASS(obj)->post_init((TestCaseWithEvtCheck*)obj,
                                                          ID_CONTROLLIST*10+1,
                                                     "TestCaseControlList_1"); 
    return (TestCaseControlList_1*)obj;
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
    .name = TYPE_TESTCASECONTROLLIST_1,
    .parent = TYPE_TESTCASEWITHEVTCHECK,
    .instance_size = sizeof(TestCaseControlList_1),
    .abstract = false,
    .class_size = sizeof(TestCaseControlList_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseControlList_1_register(void)
{
    type_register_static(&type_info);
}
