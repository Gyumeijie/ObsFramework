//
//
// TestCaseEventRepository_2.c
//

#include "TestCaseEventRepository_2.h"
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

   TD_EventType type1 = (TD_EventType)1;
   TD_EventType type2 = (TD_EventType)2;
   TD_EventType type3 = (TD_EventType)3;

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

   // Create two events in the repository
   DC_EventRepositoryClass* dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
   DC_DummyObsClock_setTime(dc_doc, 1);
   DC_DummyObsClock_setCycle(dc_doc, 1);
   dc_erc->create(dc_er, (CC_RootObject*)dc_er, type1);
   DC_DummyObsClock_setTime(dc_doc, 2);
   DC_DummyObsClock_setCycle(dc_doc, 1);
   dc_erc->create(dc_er, (CC_RootObject*)dc_er, type2);

   // Check value of event counter
   if ((DC_EventRepository_getCounter(dc_er) != 2)){
        TestCase_setTestResult((TestCase*)obj,
                                TEST_FAILURE, 
                                "Wrong number of events in event repository");
		return;
	}

   // Iterate through the events in the repository and verify their types
   DC_EventRepository_latest(dc_er);     // position event pointer on latest event
   if ( DC_EventRepository_getEventType(dc_er) != type2 ) {	
        TestCase_setTestResult((TestCase*)obj,
                                TEST_FAILURE, 
                                "Wrong event type for latest event");
		return;
	}

    if (DC_EventRepository_getTimeStamp(dc_er) != 2) {
        TestCase_setTestResult((TestCase*)obj,
                                TEST_FAILURE, 
                                "getTimeStamp() failed");
		return;
    }

   DC_EventRepository_previous(dc_er);
   if (DC_EventRepository_isIterationFinished(dc_er)) {
        TestCase_setTestResult((TestCase*)obj,
                                TEST_FAILURE, 
             "Error in repository iteration service");
		return;
	}

   if (DC_EventRepository_getEventType(dc_er) != type1) {
        TestCase_setTestResult((TestCase*)obj,
                                TEST_FAILURE, 
                                "Wrong event type for first event");
		return;
	}

    if (DC_EventRepository_getTimeStamp(dc_er) != 1) {
        TestCase_setTestResult((TestCase*)obj,
                                TEST_FAILURE, 
                                "getTimeStamp() failed");
		return;
    }

   DC_EventRepository_previous(dc_er);
   if (!(DC_EventRepository_isIterationFinished(dc_er))) {
        TestCase_setTestResult((TestCase*)obj,
                                TEST_FAILURE, 
                                "Error in repository iteration service");
		return;
	}

   // Add events to the repository until one is overwritten
   unsigned int loopCounter = 0;
   unsigned int i;
   for (i=DC_EventRepository_getCounter(dc_er); 
        i<DC_EventRepository_getRepositorySize(dc_er)+1; i++) {
        dc_erc->create(dc_er, (CC_RootObject*)dc_er, (TD_EventType)(type3+loopCounter));
        loopCounter++;
   }

   // Check value of event counter
   if ((DC_EventRepository_getCounter(dc_er) != DC_EventRepository_getRepositorySize(dc_er)+1)) {
        TestCase_setTestResult((TestCase*)obj,
                                TEST_FAILURE, 
                                "Wrong number of events in event repository");
		return;
	}

   // Check correctness of latest event
   DC_EventRepository_latest(dc_er);     // position event pointer on latest event
   if (DC_EventRepository_getEventType(dc_er) != (TD_EventType)(type3+loopCounter-1)) {
        TestCase_setTestResult((TestCase*)obj,
                                TEST_FAILURE, 
                                "Wrong event type for latest event");
		return;
	}

   // Iterate through the events in the repository and check that iteration
   // service returns a number of events equal to the repository size
   unsigned int counter = 0;
   for (DC_EventRepository_latest(dc_er); 
       !DC_EventRepository_isIterationFinished(dc_er); 
       DC_EventRepository_previous(dc_er)) {
       counter++;
   }
   
   if (counter != DC_EventRepository_getRepositorySize(dc_er)) {
       TestCase_setTestResult((TestCase*)obj,
                              TEST_FAILURE, 
                              "Wrong number of events in repository");
		return;
	}

    // Verify that reset doesn't clear the event counter
    counter = DC_EventRepository_getCounter(dc_er);
    DC_EventRepository_reset(dc_er);
    if (counter!=DC_EventRepository_getCounter(dc_er)) {
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

TestCaseEventRepository_2* TestCaseEventRepository_2_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEEVENTREPOSITORY_2);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                    ID_EVENTREPOSITORY*10+2,
                                                    "TestCaseEventRepository_2"); 
    return (TestCaseEventRepository_2*)obj;
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
    .name = TYPE_TESTCASEEVENTREPOSITORY_2,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseEventRepository_2),
    .abstract = false,
    .class_size = sizeof(TestCaseEventRepository_2Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseEventRepository_2_register(void)
{
    type_register_static(&type_info);
}
