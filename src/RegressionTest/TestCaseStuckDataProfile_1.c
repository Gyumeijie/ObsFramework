//
//
// TestCaseStuckDataProfile_1.c
//
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/TestConstants.h"
#include "../GeneralInclude/Constants.h"
#include "../FDIR/MonitoringProfile.h"
#include "../FDIR/DC_StuckDataProfile.h"
#include "../Event/DC_EventRepository.h"
#include "TestCaseStuckDataProfile_1.h"



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

   DC_StuckDataProfile* dc_sdp = DC_StuckDataProfile_new();
   MonitoringProfileClass *mpc = MONITORINGPROFILE_GET_CLASS(dc_sdp);

   unsigned int stuckThreshold = 2;
   TD_Integer sv = 10;

   // Check the value of the class identifier
   if (CC_RootObject_getClassId((CC_RootObject*)dc_sdp) != ID_STUCKDATAPROFILE) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong class identifier");
        return;
   }

   // Check configuration status
   CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(dc_sdp);
   if (cc_roc->isObjectConfigured(dc_sdp)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong configuration status");
        return;
   }

   // Set the stuck threshold
   DC_StuckDataProfile_setStuckThreshold(dc_sdp, stuckThreshold);
   if (DC_StuckDataProfile_getStuckThreshold(dc_sdp) != stuckThreshold) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong stuck threshold value");
        return;
   }

   // Check configuration status
   if (!cc_roc->isObjectConfigured(dc_sdp)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong configuration status");
        return;
   }

   // Check monitoring check for a case with "no deviation from profile"
   if (MonitoringProfile_integerDeviatesFromProfile((void*)dc_sdp, sv)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong monitoring check result");
        return;
   }
   if (MonitoringProfile_integerDeviatesFromProfile((void*)dc_sdp, sv)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong monitoring check result");
        return;
   }
   if (MonitoringProfile_integerDeviatesFromProfile((void*)dc_sdp, sv+1)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong monitoring check result");
        return;
   }

   // Check monitoring check for a case with "deviation from profile"
   if (MonitoringProfile_integerDeviatesFromProfile((void*)dc_sdp, sv)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong monitoring check result");
        return;
   }
   if (MonitoringProfile_integerDeviatesFromProfile((void*)dc_sdp, sv)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong monitoring check result");
        return;
   }
   if (!MonitoringProfile_integerDeviatesFromProfile((void*)dc_sdp, sv)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong monitoring check result");
        return;
   }

   // Check the effect of resetting the monitoring check
   if (MonitoringProfile_integerDeviatesFromProfile((void*)dc_sdp, sv+1)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong monitoring check result");
        return;
   }
   if (MonitoringProfile_integerDeviatesFromProfile((void*)dc_sdp, sv+1)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong monitoring check result");
        return;
   }
   mpc->reset(dc_sdp);
   if (MonitoringProfile_integerDeviatesFromProfile((void*)dc_sdp, sv+1)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong monitoring check result");
        return;
   }
   if (MonitoringProfile_integerDeviatesFromProfile((void*)dc_sdp, sv+1)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong monitoring check result");
        return;
   }
   if (!MonitoringProfile_integerDeviatesFromProfile((void*)dc_sdp, sv+1)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong monitoring check result");
        return;
   }

   // Check monitoring check for real-valued argument
   if (TestCase_isNonNominalCheckAllowed((TestCase*)obj)) {
        if (!MonitoringProfile_floatDeviatesFromProfile((void*)dc_sdp, 1.0)) {
             TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                     "Wrong monitoring check result for real-valued argument");
             return;
        }
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

TestCaseStuckDataProfile_1* TestCaseStuckDataProfile_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASESTUCKDATAPROFILE_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
	                                                  ID_STUCKDATAPROFILE*10+1,
                                                 "TestCaseStuckDataProfile_1");
    return (TestCaseStuckDataProfile_1*)obj;
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
    .name = TYPE_TESTCASESTUCKDATAPROFILE_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseStuckDataProfile_1),
    .abstract = false,
    .class_size = sizeof(TestCaseStuckDataProfile_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseStuckDataProfile_1_register(void)
{
    type_register_static(&type_info);
}
