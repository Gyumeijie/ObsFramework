//
//
// TestCaseEventRepository_3.c
//

#include "TestCaseEventRepository_3.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../System/DC_DummyObsClock.h"
#include "../Event/DC_EventRepository.h"
#include "../Event/DC_Event.h"



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

   TD_EventType type1 = (TD_EventType)0x0001;
   TD_EventType type2 = (TD_EventType)0x0002;
   TD_EventType type3 = (TD_EventType)0x0010;

   // Configure the event repository: load OBS clock and set repository size
   unsigned int size = 4;
   DC_DummyObsClock* dc_doc = DC_DummyObsClock_new();
   DC_EventRepository_setObsClock(dc_er, (ObsClock*)dc_doc);
   DC_EventRepository_setRepositorySize(dc_er, size);

   // Check correct configuration
   CC_RootObjectClass* cc_roc = CC_ROOTOBJECT_GET_CLASS(dc_er);
   if ((cc_roc->isObjectConfigured(dc_er) == NOT_CONFIGURED)) {	
        TestCase_setTestResult((TestCase*)obj,
                                TEST_FAILURE, 
                                "Wrong event repository configurationstatus\
                                after configuration");
 	   return;
	}


   // Fill up the repository with a few events
   DC_EventRepositoryClass* dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
   dc_erc->create(dc_er, (CC_RootObject*)dc_er, type1);
   dc_erc->create(dc_er, (CC_RootObject*)dc_er, type2);
   dc_erc->create(dc_er, (CC_RootObject*)dc_er, type3);
   dc_erc->create(dc_er, (CC_RootObject*)dc_er, type2);
   dc_erc->create(dc_er, (CC_RootObject*)dc_er, type1);

   // Disable repository and check correctness
   DC_EventRepository_setEnabled(dc_er, DISABLED);
   if ((DC_EventRepository_isEnabled(dc_er))) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, "Wrong enable status");
		return;
   }

   // Retrieve status of the repository
   unsigned int counter = DC_EventRepository_getCounter(dc_er);
   DC_EventRepository_latest(dc_er);
   TD_EventType type = DC_EventRepository_getEventType(dc_er);

   // Attempt to create event and check that nothing happens
   dc_erc->create(dc_er, (CC_RootObject*)dc_er, type3);
   if ((DC_EventRepository_getCounter(dc_er) != counter)) {
        TestCase_setTestResult((TestCase*)obj,
 	                            TEST_FAILURE,
                                "Event created in disabled repository");
		return;
   }
   
   DC_EventRepository_latest(dc_er);
   if (DC_EventRepository_getEventType(dc_er) != type) {
        TestCase_setTestResult((TestCase*)obj,
                                TEST_FAILURE, 
                                "Event created in disabled repository");
		return;
	}

   // Enable repositoy and check that events can now be created
   DC_EventRepository_setEnabled(dc_er, ENABLED);
   dc_erc->create(dc_er, (CC_RootObject*)dc_er, type3);
   if ((DC_EventRepository_getCounter(dc_er) != counter+1)) {
        TestCase_setTestResult((TestCase*)obj,
                                TEST_FAILURE, 
	                            "Failure to create event in enabled repository");
		return;
   }

   DC_EventRepository_latest(dc_er);
   if (DC_EventRepository_getEventType(dc_er) != type3) {
        TestCase_setTestResult((TestCase*)obj,
                                TEST_FAILURE, 
                                "Failure to create event in enabled repository");
		return;
	}

   // Set event repository mask and check that the correct mask is loaded
   DC_EventRepository_setEnabledWithEventType(dc_er, type2,DISABLED);
   if ( DC_EventRepository_isEnabledWithEventType(dc_er, type2)) {
        TestCase_setTestResult((TestCase*)obj,
                                TEST_FAILURE, 
                                "Error in setting event repository mask");
		return;
	}

   // Check that creation of masked event is disabled
   dc_erc->create(dc_er, (CC_RootObject*)dc_er, type2);
   if ((DC_EventRepository_getCounter(dc_er) != counter+1)) {
        TestCase_setTestResult((TestCase*)obj,
                                TEST_FAILURE, 
		                        "Failure to selectively disabled event creation");
		return;
	}

   // Check that creation of unmasked events is still ensabled
   dc_erc->create(dc_er, (CC_RootObject*)dc_er, type3);
   if ((DC_EventRepository_getCounter(dc_er) != counter+2)) {
        TestCase_setTestResult((TestCase*)obj,
                                TEST_FAILURE, 
                                 "Failure to selectively enabled event creation");
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

TestCaseEventRepository_3* TestCaseEventRepository_3_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEEVENTREPOSITORY_3);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                    ID_EVENTREPOSITORY*10+3,
                                                    "TestCaseEventRepository_3"); 
    return (TestCaseEventRepository_3*)obj;
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
    .name = TYPE_TESTCASEEVENTREPOSITORY_3,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseEventRepository_3),
    .abstract = false,
    .class_size = sizeof(TestCaseEventRepository_3Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseEventRepository_3_register(void)
{
    type_register_static(&type_info);
}
