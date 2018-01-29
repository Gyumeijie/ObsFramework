//
//
// TestCaseNullProfile_1.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../FDIR/DC_NullProfile.h"
#include "TestCaseNullProfile_1.h"



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
    DC_NullProfile *dc_np = DC_NullProfile_new(); 
    
    const unsigned int iterations = 100;

    // Check the value of the class identifier
    if (CC_RootObject_getClassId((CC_RootObject*)dc_np) != ID_NULLPROFILE) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                 "Wrong class identifier");
        return;
    }

    unsigned int i;
    for (i=0; i<iterations; i++) {
        TD_Float   fVal = (TD_Float)0.1*i;
        TD_Integer iVal = (TD_Integer)12*i;

        // Should no NO_MON_PROFILE_DEVIATION(false)
        if (MonitoringProfile_floatDeviatesFromProfile((MonitoringProfile*)dc_np, fVal)) {
             TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                     "deviatesFromProfile(TD_Float) failed");
            return;
        }

        // Should no NO_MON_PROFILE_DEVIATION(false)
        if (MonitoringProfile_integerDeviatesFromProfile((MonitoringProfile*)dc_np, iVal)) {
             TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                     "deviatesFromProfile(TD_Integer) failed");
            return;
        }
    }

    // Do dummy call to reset
    MONITORINGPROFILE_GET_CLASS(dc_np)->reset(dc_np);

     TestCase_setTestResult((TestCase*)obj, TEST_SUCCESS, "Test Successful");
    return;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj) {}

TestCaseNullProfile_1* TestCaseNullProfile_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASENULLPROFILE_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                    ID_NULLPROFILE*10+1,
                                                    "TestCaseNullProfile_1"); 
    return (TestCaseNullProfile_1*)obj;
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
    .name = TYPE_TESTCASENULLPROFILE_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseNullProfile_1),
    .abstract = false,
    .class_size = sizeof(TestCaseNullProfile_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseNullProfile_1_register(void)
{
    type_register_static(&type_info);
}
