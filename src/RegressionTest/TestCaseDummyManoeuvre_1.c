//
//
// TestCaseDummyManoeuvre_1.c
//

#include "TestCaseDummyManoeuvre_1.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../Manoeuvre/DC_DummyManoeuvre.h"



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
    const unsigned int nEvt = TestCaseWithEvtCheck_getNumberOfEvents(obj);
    DC_DummyManoeuvre *pDM = DC_DummyManoeuvre_new();
    ManoeuvreClass *mc = MANOEUVRE_GET_CLASS(pDM);

    // Verify correctness of class identifier
    if (CC_RootObject_getClassId((CC_RootObject*)pDM) != ID_DUMMYMANOEUVRE) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong class identifier");
		return;
	}

    // Newly created manoeuvres should be enabled
    if (!Manoeuvre_isEnabled((Manoeuvre*)pDM)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Manoeuvre not enabled");
		return;
	}

    // Check value of continuation check code
    if (mc->getContinuationCheckCode(pDM) != 0) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Continuation check code is incorrect");
		return;
	}

    // Newly created manoeuvres should not be in use
    if (Manoeuvre_isInUse((Manoeuvre*)pDM)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong value of inUse flag (true)");
		return;
	}

    // Newly created manoeuvres should not be executing
    if (Manoeuvre_isExecuting((Manoeuvre*)pDM)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong value of isExecuting flag (true)");
		return;
	}

    // Newly created manoeuvres should not be suspended
    if (Manoeuvre_isSuspended((Manoeuvre*)pDM)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong value of isSuspended flag (true)");
		return;
	}

	// Verify that the enable flag can be modified
	Manoeuvre_setEnabled((Manoeuvre*)pDM, false);
    if (Manoeuvre_isEnabled((Manoeuvre*)pDM)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Failed to disable the manoeuvre");
		return;
	}

	// Verify that the inUse flag can be modified
	Manoeuvre_setInUse((Manoeuvre*)pDM, true);
    if (!Manoeuvre_isInUse((Manoeuvre*)pDM)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Failed to change the inUse flag");
		return;
	}

	// Verify that the isSuspended flag can be modified
    Manoeuvre_setIsSuspended((Manoeuvre*)pDM, true);
    if (!Manoeuvre_isSuspended((Manoeuvre*)pDM)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Failed to change the isSuspended flag");
		return;
	}

	// Verify the event reporting
	if (!verifyLatestEvent(obj, nEvt+1, EVT_MAN_SUSPENDED)) return;

	// Resume manoeuvre and check correct event reporting
    Manoeuvre_setIsSuspended((Manoeuvre*)pDM, false);
	if (!verifyLatestEvent(obj, nEvt+2, EVT_MAN_RESUMED)) return;

	// Verify that a disable manoeuvre cannot be started
	if (mc->canStart(pDM) != MAN_CANNOT_START) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Disabled manoeuvre can be started");
		return;
	}

	// Now, let's check the opposite situation
	Manoeuvre_setEnabled((Manoeuvre*)pDM, true);
	if (mc->canStart(pDM)!=MAN_CAN_START) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Enabled manoeuvre cannot be started");
		return;
	}

	// Let's start the manoeuvre
	mc->initialize(pDM);
	Manoeuvre_doContinue((Manoeuvre*)pDM);

	// Verify that the manoeuvre is executing
	if (!Manoeuvre_isExecuting((Manoeuvre*)pDM)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Manoeuvre cannot be started");
		return;
	}

	// Verify the event reporting
	if (!verifyLatestEvent(obj, nEvt+3, EVT_MAN_STARTED)) return;

	// Check that the manoeuvre can continue
	if (!mc->canContinue(pDM)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "canContinue() reports wrong status");
		return;
	}

	// Verify the termination check
    if (!mc->isFinished(pDM)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Failed termination check");
		return;
	}

	// The manoeuvre is aborted and the execution status and event report are verified
	Manoeuvre_abort((Manoeuvre*)pDM);
	if (Manoeuvre_isExecuting((Manoeuvre*)pDM)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Manoeuvre cannot be aborted");
		return;
	}

	if (!verifyLatestEvent(obj, nEvt+4, EVT_MAN_ABORTED)) return;

	// Let's now do a full initialization/execution/termination cycle
	mc->initialize(pDM);
	Manoeuvre_doContinue((Manoeuvre*)pDM);
	Manoeuvre_terminate((Manoeuvre*)pDM);
	if (Manoeuvre_isExecuting((Manoeuvre*)pDM)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Failed to terminate the manoeuvre");
		return;
	}

	// Verify the event reporting
	// The initialize()/doContinue() pair generates an event.
	if (!verifyLatestEvent(obj, nEvt+6, EVT_MAN_TERMINATED)) return;

	TestCase_setTestResult((TestCase*)obj, TEST_SUCCESS, "Test Successful");
	return;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj){}

TestCaseDummyManoeuvre_1* TestCaseDummyManoeuvre_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEDUMMYMANOEUVRE_1);

    TESTCASEWITHEVTCHECK_GET_CLASS(obj)->post_init((TestCaseWithEvtCheck*)obj,
                                                       ID_DUMMYMANOEUVRE*10+1,
                                                  "TestCaseDummyManoeuvre_1");

    return (TestCaseDummyManoeuvre_1*)obj;
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
    .name = TYPE_TESTCASEDUMMYMANOEUVRE_1,
    .parent = TYPE_TESTCASEWITHEVTCHECK,
    .instance_size = sizeof(TestCaseDummyManoeuvre_1),
    .abstract = false,
    .class_size = sizeof(TestCaseDummyManoeuvre_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseDummyManoeuvre_1_register(void)
{
    type_register_static(&type_info);
}
