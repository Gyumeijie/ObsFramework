//
//
// TestCaseOutOfRangeProfile_1.c
//
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/TestConstants.h"
#include "../GeneralInclude/Constants.h"
#include "../FDIR/DC_OutOfRangeProfile.h"
#include "../FDIR/RangeProfile.h"
#include "TestCaseOutOfRangeProfile_1.h"



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

   DC_OutOfRangeProfile* dc_oorp = DC_OutOfRangeProfile_new();

   // Check the value of the class identifier
   if (CC_RootObject_getClassId((CC_RootObject*)dc_oorp) != ID_OUTOFRANGEPROFILE) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong class identifier");
        return;
   }

   // Configure the monitoring profile
   TD_Float lb = 10.0;
   TD_Float ub = 13.0;
   RangeProfile_setLowerBound((RangeProfile*)dc_oorp, lb);
   RangeProfile_setUpperBound((RangeProfile*)dc_oorp, ub);

   // Check monitoring check for a case with "no deviation from profile"
   if (MonitoringProfile_floatDeviatesFromProfile((void*)dc_oorp, ((lb+ub)/2.0))) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                 "Wrong monitoring check result");
        return;
   }

   // Check monitoring check for a case with "deviation from profile"
   if (!MonitoringProfile_floatDeviatesFromProfile((void*)dc_oorp, (ub+1.0))) {
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

TestCaseOutOfRangeProfile_1* TestCaseOutOfRangeProfile_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEOUTOFRANGEPROFILE_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                    ID_OUTOFRANGEPROFILE*10+1,
                                                "TestCaseOutOfRangeProfile_1");

    return (TestCaseOutOfRangeProfile_1*)obj;
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
    .name = TYPE_TESTCASEOUTOFRANGEPROFILE_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseOutOfRangeProfile_1),
    .abstract = false,
    .class_size = sizeof(TestCaseOutOfRangeProfile_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseOutOfRangeProfile_1_register(void)
{
    type_register_static(&type_info);
}
