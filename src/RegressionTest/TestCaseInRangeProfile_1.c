//
//
// TestCaseInRangeProfile_1.c
//
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/TestConstants.h"
#include "../GeneralInclude/Constants.h"
#include "../FDIR/DC_InRangeProfile.h"
#include "../FDIR/RangeProfile.h"
#include "TestCaseInRangeProfile_1.h"



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

   DC_InRangeProfile* dc_irp = DC_InRangeProfile_new();

   // Check the value of the class identifier
   if (CC_RootObject_getClassId((CC_RootObject*)dc_irp) != ID_INRANGEPROFILE) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong class identifier");
        return;
   }

   // Check configuration status
   CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(dc_irp);
   if (cc_roc->isObjectConfigured(dc_irp)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong configuration status");
        return;
   }

   // Set the lower bound
   TD_Float lb = 10.0;
   RangeProfile_setLowerBound((RangeProfile*)dc_irp, lb);
   TD_Float ret = RangeProfile_getLowerBound((RangeProfile*)dc_irp);
   TD_Float eps = (TD_Float)0.00001;
   if (((ret-lb)>eps) || ((lb-ret)>eps)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong lower bound value");
        return;
   }

   // Set the upper bound
   TD_Float ub = (TD_Float)12.0;
   RangeProfile_setUpperBound((RangeProfile*)dc_irp, ub);
   ret = RangeProfile_getUpperBound((RangeProfile*)dc_irp);
   if (((ret-ub)>eps) || ((ub-ret)>eps)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong lower bound value");
        return;
   }

   // Check configuration status
   if (!cc_roc->isObjectConfigured(dc_irp)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong configuration status");
        return;
   }

   // Check monitoring check for a case with "no deviation from profile"
   if (MonitoringProfile_floatDeviatesFromProfile((void*)dc_irp, lb-1)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong monitoring check result");
        return;
   }

   // Check monitoring check for a case with "deviation from profile"
   if (!MonitoringProfile_floatDeviatesFromProfile((void*)dc_irp, (lb+ub)/2)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong monitoring check result");
        return;
   }

   // Disable monitoring profile and repeat check
   MonitoringProfile_setEnabled((MonitoringProfile*)dc_irp, DISABLED);
   if (MonitoringProfile_floatDeviatesFromProfile((void*)dc_irp, (lb+ub)/2)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong monitoring check result");
        return;
   }

   // Enabble and check monitoring check for a case with "no deviation from profile"
   MonitoringProfile_setEnabled((MonitoringProfile*)dc_irp, ENABLED);
   if (MonitoringProfile_floatDeviatesFromProfile((void*)dc_irp, (lb-1))) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong monitoring check result");
        return;
   }

   // Check monitoring check for a case with "deviation from profile"
   if (!MonitoringProfile_floatDeviatesFromProfile((void*)dc_irp, (lb+ub)/2)) {
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

TestCaseInRangeProfile_1* TestCaseInRangeProfile_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEINRANGEPROFILE_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                    ID_INRANGEPROFILE*10+1,
                                                    "TestCaseInRangeProfile_1");
    return (TestCaseInRangeProfile_1*)obj;
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
    .name = TYPE_TESTCASEINRANGEPROFILE_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseInRangeProfile_1),
    .abstract = false,
    .class_size = sizeof(TestCaseInRangeProfile_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseInRangeProfile_1_register(void)
{
    type_register_static(&type_info);
}
