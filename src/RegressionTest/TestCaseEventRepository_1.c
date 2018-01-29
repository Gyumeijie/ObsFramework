//
//
// TestCaseEventRepository_1.c
//

#include "TestCaseEventRepository_1.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../System/DC_DummyObsClock.h"
#include "../Event/DC_EventRepository.h"



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

   DC_EventRepository* dc_er = DC_EventRepository_new();

   // Check the correctness of the class identifier
   if ((CC_RootObject_getClassId((CC_RootObject*)dc_er) != ID_EVENTREPOSITORY)){

        TestCase_setTestResult((TestCase*)obj,
                                TEST_FAILURE, 
                                "Wrong class identifier for the event repository class");
	   return;
	}

   // Event repository objects are not configured upon creation
   CC_RootObjectClass* cc_roc = CC_ROOTOBJECT_GET_CLASS(dc_er);
   if ((cc_roc->isObjectConfigured(dc_er) == CONFIGURED)) {	
        TestCase_setTestResult((TestCase*)obj,
                                TEST_FAILURE, 
                                "Wrong event repository configuration status\
                                upon repository creation");
	   return;
	}

   // Check the default values of the event repository attributes
   if (!(DC_EventRepository_isEnabled(dc_er)) ||
        (DC_EventRepository_getCounter(dc_er) != 0) ||
        (DC_EventRepository_getRepositorySize(dc_er) != 0)) {
        TestCase_setTestResult((TestCase*)obj,
                                TEST_FAILURE, 
                                "Wrong default value of event repository attribute");
		return;
	}

    // Check default selective enable status (NB: event types are positive)
    unsigned int i;
    for (i=1; i<=(unsigned int)LAST_EVENT_TYPE; i++)
        if (!DC_EventRepository_isEnabledWithEventType(dc_er, (TD_EventType)i)) {
        TestCase_setTestResult((TestCase*)obj,
                                TEST_FAILURE, 
                                "Wrong default value of selective enable status");
		    return;
	   }

   // Load an OBS Clock component
   DC_DummyObsClock* dc_doc = DC_DummyObsClock_new();
   DC_EventRepository_setObsClock(dc_er, (ObsClock*)dc_doc);

   // Verify that the OBS Clock was properly loaded
   if ((DC_DummyObsClock*)DC_EventRepository_getObsClock(dc_er) != dc_doc) {
        TestCase_setTestResult((TestCase*)obj,
                                TEST_FAILURE, 
                                "setObsClock() failed.");
        return;
   }

   // Initialize the repository size
   DC_EventRepository_setRepositorySize(dc_er, 4);

   // Event repository should now be configured
   if ((cc_roc->isObjectConfigured(dc_er) == NOT_CONFIGURED) ){
        TestCase_setTestResult((TestCase*)obj,
                                TEST_FAILURE, 
                                "Wrong event repository configuration status\
                                after configuration");
		return;
	}

   // Check repository size
   if ( DC_EventRepository_getRepositorySize(dc_er) != 4) {
        TestCase_setTestResult((TestCase*)obj,
                                TEST_FAILURE, 
                                "Wrong value of event repository size");
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

TestCaseEventRepository_1* TestCaseEventRepository_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEEVENTREPOSITORY_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                    ID_EVENTREPOSITORY*10+1,
                                                    "TestCaseEventRepository_1"); 
    return (TestCaseEventRepository_1*)obj;
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
    .name = TYPE_TESTCASEEVENTREPOSITORY_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseEventRepository_1),
    .abstract = false,
    .class_size = sizeof(TestCaseEventRepository_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseEventRepository_1_register(void)
{
    type_register_static(&type_info);
}
