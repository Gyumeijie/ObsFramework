//
//
// TestCaseRootObject_3.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../Event/DC_EventRepository.h"
#include "TestCaseRootObject_3.h"



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

   CC_RootObjectClass *cc_roc = GET_CLASS(TYPE_CC_ROOTOBJECT);
   if ((cc_roc->isObjectConfigured(cc_ro1) == NOT_CONFIGURED) ||
       (cc_roc->isObjectConfigured(cc_ro2) == NOT_CONFIGURED)) {
        TestCase_setTestResult((TestCase*)obj,
                               TEST_FAILURE, 
                               "Failure to report correct object configuration status");
		return;
	}

	if (CC_RootObject_isSystemConfigured() == NOT_CONFIGURED) {
        TestCase_setTestResult((TestCase*)obj,
                                TEST_FAILURE,
                                "Failure to report correct system configuration status");
		return;
	}

   // Create but do not configure an event repository. This should cause the
   // system configuration check to fail.
   DC_EventRepository* dc_er = DC_EventRepository_new();
   if (CC_RootObject_isSystemConfigured() != NOT_CONFIGURED) {
        TestCase_setTestResult((TestCase*)obj,
                               TEST_FAILURE,
                               "Failure to report correct system configuration status");
		return;
	}

   // Make use of the dc_er variable. This is necessary to avoid
   // a compiler warning
   CC_ROOTOBJECT_GET_CLASS(dc_er)->isObjectConfigured(dc_er);

   TestCase_setTestResult((TestCase*)obj, TEST_SUCCESS, "Test Successful");
   return;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj){}

TestCaseRootObject_3* TestCaseRootObject_3_new(void)
{
   Object *obj = object_new(TYPE_TESTCASEROOTOBJECT_3);
   TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                   ID_ROOTOBJECT*10+3, 
                                                   "TestCaseRootObject_3");
   return (TestCaseRootObject_3*)obj;
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
    .name = TYPE_TESTCASEROOTOBJECT_3,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseRootObject_3),
    .abstract = false,
    .class_size = sizeof(TestCaseRootObject_3Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseRootObject_3_register(void)
{
    type_register_static(&type_info);
}
