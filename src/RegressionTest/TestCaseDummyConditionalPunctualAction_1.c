//
//
// TestCaseDummyConditionalPunctualAction_1.c
//

#include "TestCaseDummyConditionalPunctualAction_1.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/DC_DummyConditionalPunctualAction.h"



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
	DC_DummyConditionalPunctualAction *dc_dcpa = DC_DummyConditionalPunctualAction_new();

	// Verify correctness of the class identifier
	if (CC_RootObject_getClassId((CC_RootObject*)dc_dcpa) != ID_DUMMYCONDITIONALPUNCTUALACTION) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong class identifier");
		return;
	}

	// Let's set the execution flag to false and verify that the
	// action does not execute
    DC_DummyConditionalPunctualAction_setExecutionFlag(dc_dcpa, false);
	if (PunctualAction_execute((PunctualAction*)dc_dcpa) != ACTION_CANNOT_EXECUTE) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Action could be executed");
		return;
	}

	// Now we perform the opposite test
    DC_DummyConditionalPunctualAction_setExecutionFlag(dc_dcpa, true);
	if (PunctualAction_execute((PunctualAction*)dc_dcpa) != ACTION_SUCCESS) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                              "Action could not be executed");
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

TestCaseDummyConditionalPunctualAction_1* TestCaseDummyConditionalPunctualAction_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEDUMMYCONDITIONALPUNCTUALACTION_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
	                                    ID_DUMMYCONDITIONALPUNCTUALACTION*10+1,
						           "TestCaseDummyConditionalPunctualAction_1");

    return (TestCaseDummyConditionalPunctualAction_1*)obj;
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
    .name = TYPE_TESTCASEDUMMYCONDITIONALPUNCTUALACTION_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseDummyConditionalPunctualAction_1),
    .abstract = false,
    .class_size = sizeof(TestCaseDummyConditionalPunctualAction_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseDummyConditionalPunctualAction_1_register(void)
{
    type_register_static(&type_info);
}
