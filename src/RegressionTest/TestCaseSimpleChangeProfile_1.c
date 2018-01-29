//
//
// TestCaseSimpleChangeProfile_1.c
//
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/TestConstants.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../FDIR/MonitoringProfile.h"
#include "../FDIR/DC_SimpleChangeProfile.h"
#include "../Event/DC_EventRepository.h"
#include "TestCaseSimpleChangeProfile_1.h"



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

   DC_SimpleChangeProfile *mp = DC_SimpleChangeProfile_new();

   // Check the value of the class identifier
   if (CC_RootObject_getClassId((CC_RootObject*)mp) != ID_SIMPLECHANGEPROFILE)
   {
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong class identifier");
       return;
   }

   // Check that monitoring check is enabled
   if (!MonitoringProfile_isEnabled((MonitoringProfile*)mp))
   {
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong enable status");
       return;
   }

   // Set the reference value
   TD_Integer rv = 10;
   DC_SimpleChangeProfile_setReferenceValue(mp, rv);
   if (DC_SimpleChangeProfile_getReferenceValue(mp) != rv)
   {
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong reference value");
       return;
   }

   // Check monitoring check for a case with "no deviation from profile"
   if (MonitoringProfile_integerDeviatesFromProfile((MonitoringProfile*)mp, rv))
   {
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                              "Wrong monitoring check result");
       return;
   }

   // Check monitoring check for real-valued argument
   if (TestCase_isNonNominalCheckAllowed(obj)) {
        if (!MonitoringProfile_floatDeviatesFromProfile((MonitoringProfile*)mp, 1.0))
        {    
            TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                     "Wrong monitoring check result for real-valued argument");
            return;
        }
   }

   // Check monitoring check for a case with "deviation from profile"
   DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
   DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
   unsigned int nEvt = DC_EventRepository_getCounter(dc_er);
   if (!MonitoringProfile_integerDeviatesFromProfile((MonitoringProfile*)mp, (rv+1)))
   {    
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong monitoring check result");
       return;
   }

   // Check generation of event reporting detection of deviation from profile
   if (DC_EventRepository_getCounter(dc_er) != (nEvt+1))
   {    
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                              "Wrong number of events");
       return;
   }
   DC_EventRepository_latest(dc_er);
   if (DC_EventRepository_getEventType(dc_er) != EVT_MON_PROFILE_VIOLATION)
   {
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong event type");
       return;
   }

   // Disable monitoring profile and check new enable status
   MonitoringProfile_setEnabled((MonitoringProfile*)mp, DISABLED);
   if (MonitoringProfile_isEnabled((MonitoringProfile*)mp) != DISABLED)
   { 
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong enable status");
       return;
   }

   // Check monitoring check for a case with "deviation from profile"
   // NB: the monitoring profile component is now disabled
   if (MonitoringProfile_integerDeviatesFromProfile((MonitoringProfile*)mp, (rv+1)))
   {
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                              "Wrong monitoring check result");
       return;
   }

   // Check that no events were generated
   if (DC_EventRepository_getCounter(dc_er) != (nEvt+1))
   {
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                              "Wrong number of events");
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

TestCaseSimpleChangeProfile_1* TestCaseSimpleChangeProfile_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASESIMPLECHANGEPROFILE_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                  ID_SIMPLECHANGEPROFILE*10+1,
                                             "TestCaseSimpleChangeProfile_1");

    return (TestCaseSimpleChangeProfile_1*)obj;
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
    .name = TYPE_TESTCASESIMPLECHANGEPROFILE_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseSimpleChangeProfile_1),
    .abstract = false,
    .class_size = sizeof(TestCaseSimpleChangeProfile_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseSimpleChangeProfile_1_register(void)
{
    type_register_static(&type_info);
}
