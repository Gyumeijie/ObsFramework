//
//
// TestCaseManoeuvreManager_3.c
//

#include "TestCaseManoeuvreManager_3.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../Manoeuvre/DC_DummyConfigurableManoeuvre.h"
#include "../Manoeuvre/CC_ManoeuvreManager.h"



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
    CC_ManoeuvreManager *pMM = CC_ManoeuvreManager_new();
    CC_ManoeuvreManagerClass *cc_mmc = CC_MANOEUVREMANAGER_GET_CLASS(pMM);

	// Initialize the manoeuvre manager
	CC_ManoeuvreManager_setPendingManoeuvreListSize(pMM, 1);

	// Allocate, load and set the start and continuation flag of the manoeuvre
	DC_DummyConfigurableManoeuvre *pDCM = DC_DummyConfigurableManoeuvre_new();

    Manoeuvre_setInUse((Manoeuvre*)pDCM, true);
	cc_mmc->load(pMM, (Manoeuvre*)pDCM);
    DC_DummyConfigurableManoeuvre_setStartCheckStatus(pDCM, MAN_CAN_START);
    DC_DummyConfigurableManoeuvre_setContinuationCheckStatus(pDCM, MAN_CAN_CONTINUE);
    DC_DummyConfigurableManoeuvre_setTerminationCheckStatus(pDCM, MAN_HAS_NOT_TERMINATED);

	// Verify initial value of activation step counter
    if (Manoeuvre_getActivationStepCounter((Manoeuvre*)pDCM) != 0) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong initial value of activation step counter");
		return;
	}

    // Invoke twice the activate method and verify that the manoeuvre
	// continuation counter has been incremented twice
	cc_mmc->activate(pMM);
	cc_mmc->activate(pMM);
    if (DC_DummyConfigurableManoeuvre_getContinuationActionCounter(pDCM) != 2) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong value of manoeuvre continuation counter");
		return;
	}

	// Verify value of activation step counter
    if (Manoeuvre_getActivationStepCounter((Manoeuvre*)pDCM) != 2) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong value of activation step counter");
		return;
	}

	// Suspend the manoeuvre, invoke the activate method, and verify that the manoeuvre
	// continuation counter has not been incremented
    Manoeuvre_setIsSuspended((Manoeuvre*)pDCM, true);
	cc_mmc->activate(pMM);
	if (DC_DummyConfigurableManoeuvre_getContinuationActionCounter(pDCM) != 2)
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong value of manoeuvre continuation counter");
		return;
	}

	// Verify value of activation step counter
    if (Manoeuvre_getActivationStepCounter((Manoeuvre*)pDCM) != 2) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong value of activation step counter");
		return;
	}

	// Force the termination of the manoeuvre and verify that the manoeuvre status
    // changes to "not suspended"
    DC_DummyConfigurableManoeuvre_setTerminationCheckStatus(pDCM, MAN_HAS_TERMINATED);
    Manoeuvre_setIsSuspended((Manoeuvre*)pDCM, true);
	cc_mmc->activate(pMM);
	if (DC_DummyConfigurableManoeuvre_getContinuationActionCounter(pDCM) != 2)
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong value of manoeuvre continuation counter");
		return;
	}
    if (Manoeuvre_isSuspended((Manoeuvre*)pDCM)) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong manoeuvre suspension status");
		return;
	}

	// Reload the manoeuvre, suspend it, activate it and verify that the
    // activation step counter has been reset to 0
    DC_DummyConfigurableManoeuvre_setTerminationCheckStatus(pDCM, MAN_HAS_NOT_TERMINATED);
    cc_mmc->load(pMM, (Manoeuvre*)pDCM);
    Manoeuvre_setIsSuspended((Manoeuvre*)pDCM, true);
	cc_mmc->activate(pMM);
    if (Manoeuvre_getActivationStepCounter((Manoeuvre*)pDCM) != 0) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong value of activation step counter");
		return;
	}
    if (DC_DummyConfigurableManoeuvre_getInitializationActionCounter(pDCM) != 2) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong value of manoeuvre continuation counter");
		return;
	}

    // Abort the manoeuvre and verify that its status is changed back to "not suspended"
    Manoeuvre_abort((Manoeuvre*)pDCM);
    if (Manoeuvre_isSuspended((Manoeuvre*)pDCM)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong manoeuvre suspension status");
		return;
	}

	// Verify value of activation step counter

	TestCase_setTestResult((TestCase*)obj,TEST_SUCCESS,"Test Successful");
	return;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj){}

TestCaseManoeuvreManager_3* TestCaseManoeuvreManager_3_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEMANOEUVREMANAGER_3);

    TESTCASEWITHEVTCHECK_GET_CLASS(obj)->post_init((TestCaseWithEvtCheck*)obj,
                                                     ID_MANOEUVREMANAGER*10+3,
                                                "TestCaseManoeuvreManager_3"); 

    return (TestCaseManoeuvreManager_3*)obj;
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
    .name = TYPE_TESTCASEMANOEUVREMANAGER_3,
    .parent = TYPE_TESTCASEWITHEVTCHECK,
    .instance_size = sizeof(TestCaseManoeuvreManager_3),
    .abstract = false,
    .class_size = sizeof(TestCaseManoeuvreManager_3Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseManoeuvreManager_3_register(void)
{
    type_register_static(&type_info);
}
