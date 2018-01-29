//
//
// TestCaseRootObject_2.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../Base/CC_RootObject.h"
#include "TestCaseRootObject_2.h"



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
    CC_RootObject* cc_ro1 = CC_RootObject_new();
    CC_RootObject* cc_ro2 = CC_RootObject_new();
    CC_RootObject* cc_ro3 = CC_RootObject_new();

	if (CC_RootObject_getClassId(cc_ro1) != ID_ROOTOBJECT) {	
        TestCase_setTestResult((TestCase*)obj, 
                                TEST_FAILURE, 
                                "Incorrect setting of class identifier");
		return;
	}

	if (CC_RootObject_getClassId(cc_ro1) != CC_RootObject_getClassId(cc_ro2)) {
        TestCase_setTestResult((TestCase*)obj,
                               TEST_FAILURE, 
                               "Incorrect setting of class identifier");
		return;
	}

	if (CC_RootObject_getClassId(cc_ro2) != CC_RootObject_getClassId(cc_ro2)) {
        TestCase_setTestResult((TestCase*)obj,
                               TEST_FAILURE, 
                               "Incorrect setting of class identifier");
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

TestCaseRootObject_2* TestCaseRootObject_2_new(void)
{
   Object *obj = object_new(TYPE_TESTCASEROOTOBJECT_2);

   TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                   ID_ROOTOBJECT*10+2, 
                                                   "TestCaseRootObject_2");
   return (TestCaseRootObject_2*)obj;
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
    .name = TYPE_TESTCASEROOTOBJECT_2,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseRootObject_2),
    .abstract = false,
    .class_size = sizeof(TestCaseRootObject_2Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseRootObject_2_register(void)
{
    type_register_static(&type_info);
}
