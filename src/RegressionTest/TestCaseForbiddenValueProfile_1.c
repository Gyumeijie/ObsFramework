//
//
// TestCaseForbiddenValueProfile_1.c
//
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/TestConstants.h"
#include "../GeneralInclude/Constants.h"
#include "../FDIR/MonitoringProfile.h"
#include "../FDIR/DC_ForbiddenValueProfile.h"
#include "TestCaseForbiddenValueProfile_1.h"



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

   DC_ForbiddenValueProfile* dc_fvp = DC_ForbiddenValueProfile_new();

   // Check the value of the class identifier
   if (CC_RootObject_getClassId((CC_RootObject*)dc_fvp) != ID_FORBIDDENVALUEPROFILE) {    
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong class identifier");
       return;
   }

   // Set the forbidden value
   TD_Integer fv = 10;
   DC_ForbiddenValueProfile_setForbiddenValue(dc_fvp, fv);
   if (DC_ForbiddenValueProfile_getForbiddenValue(dc_fvp) != fv){
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong forbidden value");
        return;
   }

   // Check monitoring check for a case with "no deviation from profile"
   if (MonitoringProfile_integerDeviatesFromProfile((void*)dc_fvp, (fv+1))) {
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong monitoring check result");
       return;
   }

   // Check monitoring check for a case with "deviation from profile"
   if (!MonitoringProfile_integerDeviatesFromProfile((void*)dc_fvp, fv)) {
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                              "Wrong monitoring check result");
       return;
   }

   // Disable monitoring profile and repeat check
   MonitoringProfile_setEnabled((MonitoringProfile*)dc_fvp, DISABLED);
   if (MonitoringProfile_integerDeviatesFromProfile((void*)dc_fvp, fv)) {
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong monitoring check result");
       return;
   }

   MonitoringProfile_setEnabled((MonitoringProfile*)dc_fvp, ENABLED);
   // Check monitoring check for real-valued argument
   if (TestCase_isNonNominalCheckAllowed((TestCase*)obj)) {
        if (!MonitoringProfile_floatDeviatesFromProfile((void*)dc_fvp, 1.0)) {
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

TestCaseForbiddenValueProfile_1* TestCaseForbiddenValueProfile_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEFORBIDDENVALUEPROFILE_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                 ID_FORBIDDENVALUEPROFILE*10+1,
                                            "TestCaseForbiddenValueProfile_1"); 

    return (TestCaseForbiddenValueProfile_1*)obj;
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
    .name = TYPE_TESTCASEFORBIDDENVALUEPROFILE_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseForbiddenValueProfile_1),
    .abstract = false,
    .class_size = sizeof(TestCaseForbiddenValueProfile_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseForbiddenValueProfile_1_register(void)
{
    type_register_static(&type_info);
}
