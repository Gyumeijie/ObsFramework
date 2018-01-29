//
//
// TestCaseDummyObsClock_1.c
//

#include "TestCaseDummyObsClock_1.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../System/DC_DummyObsClock.h"



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
     DC_DummyObsClock* dc_doc = DC_DummyObsClock_new();

     // Dummy OBS Clock objects should be configured upon creation
     CC_RootObjectClass* cc_roc = CC_ROOTOBJECT_GET_CLASS(dc_doc);
     if ((cc_roc->isObjectConfigured(dc_doc)) != CONFIGURED) {	
         TestCase_setTestResult((TestCase*)obj,
                                 TEST_FAILURE, 
                                 "Dummy OBS clock component should be configured");
		return;
	}

    // Check that the timing data have correct values (they should be zero
    // upon creation)
    ObsClockClass *occ = OBSCLOCK_GET_CLASS(dc_doc);
	if ((occ->getTime(dc_doc) != 0) || (occ->getCycle(dc_doc) != 0)) {
        TestCase_setTestResult((TestCase*)obj,
                                TEST_FAILURE, 
                                "Incorrect timing initial values");
		return;
	}

    // Set the timing data
    DC_DummyObsClock_setTime(dc_doc, 10);
    DC_DummyObsClock_setCycle(dc_doc, 1);

    // Check that the timing data have correct values
	if ((occ->getTime(dc_doc) != 10) || (occ->getCycle(dc_doc) != 1)) {
        TestCase_setTestResult((TestCase*)obj,
                                TEST_FAILURE, 
                                "Incorrect timing values");
		return;
	}

     // Reset clock component and verify that time and cycle are reset to 0
     occ->reset(dc_doc);
	if ((occ->getTime(dc_doc) != 0) || (occ->getCycle(dc_doc) != 0)) {
        TestCase_setTestResult((TestCase*)obj,
                                TEST_FAILURE, 
                                "Timing data have not been correctly reset");
		return;
	}

    // Do dummy method call
    occ->synchronizeWithSystemTime(dc_doc);

   TestCase_setTestResult((TestCase*)obj, TEST_SUCCESS, "Test Successful");
	return;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj){}

TestCaseDummyObsClock_1* TestCaseDummyObsClock_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEDUMMYOBSCLOCK_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                    ID_DUMMYOBSCLOCK*10+1,
                                                    "TestCaseDummyObsClock_1");
    return (TestCaseDummyObsClock_1*)obj;
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
    .name = TYPE_TESTCASEDUMMYOBSCLOCK_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseDummyObsClock_1),
    .abstract = false,
    .class_size = sizeof(TestCaseDummyObsClock_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseDummyObsClock_1_register(void)
{
    type_register_static(&type_info);
}
