//
//
// TestCaseDeltaProfile_1.c
//
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/TestConstants.h"
#include "../GeneralInclude/Constants.h"
#include "../FDIR/DC_DeltaProfile.h"
#include "TestCaseDeltaProfile_1.h"



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

   DC_DeltaProfile* dc_dp = DC_DeltaProfile_new();
   MonitoringProfileClass *mpc = MONITORINGPROFILE_GET_CLASS(dc_dp);

   TD_Float deltaThreshold = 2.0;
   TD_Integer valInt = 10;
   TD_Float valFloat = 5.0;
   // Used for save computed value to be Monitored
   TD_Float computedValue; 

   // Check the value of the class identifier
   if (CC_RootObject_getClassId((CC_RootObject*)dc_dp) != ID_DELTAPROFILE) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong class identifier");
        return;
   }

   // Check configuration status
   CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(dc_dp);
   if (cc_roc->isObjectConfigured(dc_dp)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong configuration status");
        return;
   }

   // Set the delta threshold
   DC_DeltaProfile_setDeltaThreshold(dc_dp, deltaThreshold);
   if (DC_DeltaProfile_getDeltaThreshold(dc_dp) != deltaThreshold) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong delta threshold value");
        return;
   }

   // Check configuration status
   if (!cc_roc->isObjectConfigured(dc_dp)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong configuration status");
        return;
   }

   // Check monitoring check for a case with "no deviation from profile"
   // (argument of type double)
   if (MonitoringProfile_floatDeviatesFromProfile((void*)dc_dp, valFloat)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong monitoring check result");
        return;
   }

   computedValue = valFloat + deltaThreshold - (TD_Float)0.1; 
   if (MonitoringProfile_floatDeviatesFromProfile((void*)dc_dp, computedValue)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong monitoring check result");
        return;
   }

   // Check monitoring check for a case with "deviation from profile"
   // (argument of type double)
   if (MonitoringProfile_floatDeviatesFromProfile((void*)dc_dp, valFloat)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong monitoring check result");
        return;
   }
   
   computedValue = valFloat + deltaThreshold + (TD_Float)0.1;
   if (!MonitoringProfile_floatDeviatesFromProfile((void*)dc_dp, computedValue)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong monitoring check result");
        return;
   }

   // Check the effect of resetting the monitoring check
   computedValue = valFloat + deltaThreshold + (TD_Float)0.1;
   if (MonitoringProfile_floatDeviatesFromProfile((void*)dc_dp, computedValue)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong monitoring check result");
        return;
   }
   mpc->reset(dc_dp);
   if (MonitoringProfile_floatDeviatesFromProfile((void*)dc_dp, valFloat)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong monitoring check result");
        return;
   }

   // Check monitoring check for a case with "no deviation from profile
   // (argument of type int)
   mpc->reset(dc_dp);
   if (MonitoringProfile_integerDeviatesFromProfile((void*)dc_dp, valInt)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong monitoring check result");
        return;
   }
   computedValue = valInt + deltaThreshold - 1;
   if (MonitoringProfile_floatDeviatesFromProfile((void*)dc_dp, computedValue)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong monitoring check result");
        return;
   }

   // Check monitoring check for a case with "deviation from profile"
   // (argument of type int)
   if (MonitoringProfile_integerDeviatesFromProfile((void*)dc_dp, valInt)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong monitoring check result");
        return;
   }
   computedValue = valInt + deltaThreshold + 1;
   if (!MonitoringProfile_floatDeviatesFromProfile((void*)dc_dp, computedValue)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong monitoring check result");
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

TestCaseDeltaProfile_1* TestCaseDeltaProfile_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEDELTAPROFILE_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                    ID_DELTAPROFILE*10+1,
                                                    "TestCaseDeltaProfile_1");

    return (TestCaseDeltaProfile_1*)obj;
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
    .name = TYPE_TESTCASEDELTAPROFILE_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseDeltaProfile_1),
    .abstract = false,
    .class_size = sizeof(TestCaseDeltaProfile_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseDeltaProfile_1_register(void)
{
    type_register_static(&type_info);
}
