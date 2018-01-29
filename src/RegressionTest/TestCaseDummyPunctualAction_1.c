//
//
// TestCaseDummyPunctualAction_1.c
//
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/DC_DummyPunctualAction.h"
#include "TestCaseDummyPunctualAction_1.h"



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
	DC_DummyPunctualAction *dc_dpa = DC_DummyPunctualAction_new();

	// Verify correctness of the class identifier
	if (CC_RootObject_getClassId((CC_RootObject*)dc_dpa) != ID_DUMMYPUNCTUALACTION) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong class identifier");
		return;
	}

	// Dummy punctual actions should be enabled at creation
    if (!PunctualAction_isEnabled((PunctualAction*)dc_dpa)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong enable status at creation");
        return;
    }

    // The activation counter shall be equal to zero
    if (DC_DummyPunctualAction_getActivationCounter(dc_dpa)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong activation counter at creation");
        return;
    }

	// The outcome should be set to ACTION_RESET
	if (PunctualAction_getLastOutcome((PunctualAction*)dc_dpa) != ACTION_RESET) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong action outcome at creation");
		return;
	}

	// Send an execute request to the punctual action and check that the
	// correct event is recorded.
	if (PunctualAction_execute((PunctualAction*)dc_dpa) != ACTION_SUCCESS) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong punctual action outcome");
		return;
	}

    // verifyLatestEvent
	if (!verifyLatestEvent(obj, nEvt+1, EVT_PUNCTUAL_ACTION_EXEC)) {
		return;
    }

    // Verify that the activation counter was incremented
    if (DC_DummyPunctualAction_getActivationCounter(dc_dpa) != 1) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Activation counter was not incremented");
        return;
    }

	// Disable the punctual action and verify correct enable status
	PunctualAction_setEnabled((PunctualAction*)(dc_dpa), DISABLED);
    if (PunctualAction_isEnabled((PunctualAction*)dc_dpa)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Punctual action was not disabled");
		return;
	}

	// Send an execute request to the punctual action and check that the
	// correct event is recorded.
	if (PunctualAction_execute((PunctualAction*)dc_dpa) != ACTION_DISABLED) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong punctual action outcome");
		return;
    }

	if (!verifyLatestEvent(obj, nEvt+2, EVT_PUNCTUAL_ACTION_DIS))
		return;

	// Verify the the latest outcome is properly reported
	if (PunctualAction_getLastOutcome((PunctualAction*)dc_dpa) != ACTION_DISABLED) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong punctual action outcome");
		return;
	}

	// Reset the latest outcome and verify that it is now ACTION_RESET
	PunctualAction_resetLastOutcome((PunctualAction*)dc_dpa);
	if (PunctualAction_getLastOutcome((PunctualAction*)dc_dpa) != ACTION_RESET) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "getLastOutcome() failed");
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

static void instance_init(Object *obj) {}

TestCaseDummyPunctualAction_1* TestCaseDummyPunctualAction_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEDUMMYPUNCTUALACTION_1);    

    TESTCASEWITHEVTCHECK_GET_CLASS(obj)->post_init((TestCaseWithEvtCheck*)obj,
                                                    ID_DUMMYPUNCTUALACTION*10+1,
                                                    "TestCaseDummyPunctualAction_1");                    
    return (TestCaseDummyPunctualAction_1*)obj;
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
    .name = TYPE_TESTCASEDUMMYPUNCTUALACTION_1,
    .parent = TYPE_TESTCASEWITHEVTCHECK,
    .instance_size = sizeof(TestCaseDummyPunctualAction_1),
    .abstract = false,
    .class_size = sizeof(TestCaseDummyPunctualAction_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseDummyPunctualAction_1_register(void)
{
    type_register_static(&type_info);
}
