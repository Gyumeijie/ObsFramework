//
//
// TestCaseUnstableFsmState_1.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/TestConstants.h"
#include "../FSM/DC_UnstableFsmState.h"
#include "TestCaseUnstableFsmState_1.h"



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
	DC_UnstableFsmState *pUFS = DC_UnstableFsmState_new();
    FsmStateClass *fsc = FSMSTATE_GET_CLASS(pUFS);

	// Verify the correctness of the class id
	if (CC_RootObject_getClassId((CC_RootObject*)pUFS) != ID_UNSTABLEFSMSTATE) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong class id");
		return;
	}

    // Verify that isFinished() returns true
    if (!fsc->isFinished(pUFS)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "isFinished() failed.");
		return;
    }

    // Dummy call to doContinue()
    fsc->doContinue(pUFS);

	TestCase_setTestResult((TestCase*)obj, TEST_SUCCESS, "Test Successful");
	return;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj){}

TestCaseUnstableFsmState_1* TestCaseUnstableFsmState_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEUNSTABLEFSMSTATE_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                    ID_UNSTABLEFSMSTATE*10+1,
                                                    "TestCaseUnstableFsmState_1"); 

    return (TestCaseUnstableFsmState_1*)obj;
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
    .name = TYPE_TESTCASEUNSTABLEFSMSTATE_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseUnstableFsmState_1),
    .abstract = false,
    .class_size = sizeof(TestCaseUnstableFsmState_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseUnstableFsmState_1_register(void)
{
    type_register_static(&type_info);
}
