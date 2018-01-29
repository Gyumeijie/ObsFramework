//
//
// TestCaseDummyCriticalTelecommand_1.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/TestConstants.h"
#include "../System/DC_DummyObsClock.h"
#include "../Telecommand/DC_DummyCriticalTelecommand.h"
#include "TestCaseDummyCriticalTelecommand_1.h"



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
	const TD_ObsTime timeTag = 0;
	const TD_ObsTime maxArmedDuration = 10;
	ObsClock *pObsClk = (ObsClock*)DC_DummyObsClock_new();
	DC_DummyCriticalTelecommand *pTc = DC_DummyCriticalTelecommand_new();
    CriticalTelecommandClass *ctc = CRITICALTELECOMMAND_GET_CLASS(pTc);
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pTc);

	// Verify the correctness of the class id
	if (CC_RootObject_getClassId((CC_RootObject*)pTc) != ID_DUMMYCRITICALTELECOMMAND) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong class id");
		return;
	}

	// The following will configure CriticalTelecommand's base class...
	Telecommand_setTimeTag((Telecommand*)pTc, timeTag);

	// ...however CriticalTelecommand shall still be unconfigured
	if (cc_roc->isObjectConfigured(pTc)) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Newly created object is configured");
		return;
	}

	// Let's set the armed duration and verify that the TC is not yet configured
	CriticalTelecommand_setMaxArmedDuration((void*)pTc, maxArmedDuration);
	if (cc_roc->isObjectConfigured(pTc)) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong configuration status");
		return;
	}

	// Verify that the max armed duration was properly set
	if (CriticalTelecommand_getMaxArmedDuration((void*)pTc) != maxArmedDuration)
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "getMaxArmedDuration() failed");
		return;
	}

	// After this the TC shall be configured
	CriticalTelecommand_setObsClock((void*)pTc, pObsClk);
	if (!cc_roc->isObjectConfigured(pTc)) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong configuration status");
		return;
	}

	// Verify that the ObsClock pointer was properly set
	if (CriticalTelecommand_getObsClock((void*)pTc) != pObsClk) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "getObsClock() failed");
		return;
	}

	// A newly created TC shall be critical...
	if (!CriticalTelecommand_isCritical((void*)pTc)) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Newly created TC is critical");
		return;
	}

	// ...and should not be armed
	if (CriticalTelecommand_isArmed((void*)pTc)) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Newly created TC is armed");
		return;
	}

	// Let's verify that we can change the criticality level
	CriticalTelecommand_setCriticalityLevel((void*)pTc, false);
	if (CriticalTelecommand_isCritical((void*)pTc)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "setCriticalityLevel() failed");
		return;
	}

	// Verify that isImageValid() and setImageValidity() work as expected
	if (ctc->isImageValid(pTc)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "The image of a newly created TC is valid");
		return;
	}

	DC_DummyCriticalTelecommand_setImageValidity(pTc, true);
	if (!ctc->isImageValid(pTc)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "setImageValidity() failed");
		return;
	}

	// Verify that the "time when armed" is invalid
	if (CriticalTelecommand_getTimeWhenArmed((void*)pTc) >= 0) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong initial \"time when armed\"");
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

TestCaseDummyCriticalTelecommand_1* TestCaseDummyCriticalTelecommand_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEDUMMYCRITICALTELECOMMAND_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                             ID_DUMMYCRITICALTELECOMMAND*10+1,
                                        "TestCaseDummyCriticalTelecommand_1");

    return (TestCaseDummyCriticalTelecommand_1*)obj;
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
    .name = TYPE_TESTCASEDUMMYCRITICALTELECOMMAND_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseDummyCriticalTelecommand_1),
    .abstract = false,
    .class_size = sizeof(TestCaseDummyCriticalTelecommand_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseDummyCriticalTelecommand_1_register(void)
{
    type_register_static(&type_info);
}
