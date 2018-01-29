//
//
// TestCaseEvent_1.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../Event/DC_Event.h"
#include "TestCaseEvent_1.h"



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

   DC_Event* dc_event1 = DC_Event_new();

   // Set the event attributes
   DC_Event_setTimeStamp(dc_event1, 1);
   DC_Event_setEventType(dc_event1, (TD_EventType)2);

   // Check that the event attributes have correct values
	if ( (DC_Event_getTimeStamp(dc_event1) != 1) ||
         (DC_Event_getEventType(dc_event1) != 2) ){	
        TestCase_setTestResult((TestCase*)obj,
                                TEST_FAILURE, 
                                "Incorrect event attribute values");
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

TestCaseEvent_1* TestCaseEvent_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEEVENT_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                    ID_EVENT*10+1,
                                                    "TestCaseEvent_1"); 
   return (TestCaseEvent_1*)obj;
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
    .name = TYPE_TESTCASEEVENT_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseEvent_1),
    .abstract = false,
    .class_size = sizeof(TestCaseEvent_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseEvent_1_register(void)
{
    type_register_static(&type_info);
}
