//
//
// TestCaseDummyCriticalTelecommand_2.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/TestConstants.h"
#include "../System/DC_DummyObsClock.h"
#include "../Telecommand/DC_DummyCriticalTelecommand.h"
#include "TestCaseDummyCriticalTelecommand_2.h"



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
    const unsigned int nEvt = TestCaseWithEvtCheck_getNumberOfEvents(obj);
	DC_DummyObsClock *pObsClk = DC_DummyObsClock_new();
    ObsClockClass *occ = OBSCLOCK_GET_CLASS(pObsClk);
	DC_DummyCriticalTelecommand *pTc = DC_DummyCriticalTelecommand_new();
    TelecommandClass *tc = TELECOMMAND_GET_CLASS(pTc);

	// Initialize the object, including the base class
	Telecommand_setTimeTag((void*)pTc, timeTag);
	CriticalTelecommand_setMaxArmedDuration((void*)pTc, maxArmedDuration);
	CriticalTelecommand_setObsClock((void*)pTc, (ObsClock*)pObsClk);

    // First we test the non-critical behaviour
	CriticalTelecommand_setCriticalityLevel((void*)pTc, false);

	// The TC is not critical: canExecute() shall return true
	if (!tc->canExecute(pTc)) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Non-critical TC can not be executed");
		return;
	}

	// Executing a non-critical TC should always result in a invocation
	// of doCriticalAction().
	if (PunctualAction_execute((PunctualAction*)pTc) != ACTION_SUCCESS) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "TC execute() failed");
		return;
	}

	if (DC_DummyCriticalTelecommand_getNumberOfExecutions(pTc) != 1) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "doCriticalAction() not called");
		return;
	}

	// We now make the TC critical. An invocation of canExecute() shall
	// return true. A subsequent call to execute() shall arm the TC, set the
	// "time when armed" to the current time, add an EVT_CRIT_TC_ARMED to the
	// event log and return ACTION_SUCCESS.
	CriticalTelecommand_setCriticalityLevel((void*)pTc, true);

	if (!tc->canExecute(pTc)) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Disarmed, critical TC cannot be executed");
		return;
	}

	if (PunctualAction_execute((PunctualAction*)pTc) != ACTION_SUCCESS) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "TC execute() failed");
		return;
	}

	if (!CriticalTelecommand_isArmed((void*)pTc)) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Failed to arm TC");
		return;
	}

	if (CriticalTelecommand_getTimeWhenArmed((void*)pTc) != occ->getTime(pObsClk)) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong \"time when armed\"");
		return;
	}

	if (!verifySpecificEvent(obj, (nEvt+2), EVT_CRIT_TC_ARMED)) return;

	// Invoking isImageValid() on a newly created DC_DummyCriticalTelecommand
	// returns false, thus a new call to canExecute() shall return false and add
	// an EVT_CRIT_TC_IMG_INV event to the repository with the TC id as parameter.
	if (tc->canExecute(pTc)) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "TC with invalid image can be executed");
		return;
	}

	if (!verifyLatestEvent(obj, (nEvt+4), EVT_CRIT_TC_IMG_INV)) return;

	// The arm state shall be unmodifief
	if (!CriticalTelecommand_isArmed((void*)pTc)) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Unexpected change in arm state");
		return;
	}

	// Reset the TC in order to perform the next test
	CriticalTelecommand_reset((void*)pTc);

	// Verify that reset() did its job
	if (CriticalTelecommand_getTimeWhenArmed((void*)pTc) >= 0) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "reset() failed (timeWhenArmed)");
		return;
	}

	if (CriticalTelecommand_isArmed((void*)pTc)) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "reset() failed (isTcArmed)");
		return;
	}

	if (CriticalTelecommand_getMaxArmedDuration((void*)pTc) >= 0)
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "reset() failed (maxArmedDuration");
		return;
	}

	// Clearly the TC shall also be re-initialized
	CriticalTelecommand_setObsClock((void*)pTc, (ObsClock*)pObsClk);
	CriticalTelecommand_setMaxArmedDuration((void*)pTc, maxArmedDuration);

	// Now the TC is no longer armed. We call execute() to arm it (we know canExecute()
	// would return true), set the image validity flag to true and call canExecute()
	// a second time. This time it shall return true.
	PunctualAction_execute((PunctualAction*)pTc);
	DC_DummyCriticalTelecommand_setImageValidity(pTc, true);

	if (!tc->canExecute(pTc)) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Valid TC can not be executed");
		return;
	}

	// We now call execute() and verify that doCriticalAction() is invoked
	// and the TC is disarmed.
	PunctualAction_execute((PunctualAction*)pTc);

	if (DC_DummyCriticalTelecommand_getNumberOfExecutions(pTc) != 2) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "doCriticalAction() not called");
		return;
	}

	if (CriticalTelecommand_isArmed((void*)pTc)) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Call to execute() did not disarm TC");
		return;
	}

	if (CriticalTelecommand_getTimeWhenArmed((void*)pTc) >= 0) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "\"Time when armed\" was not reset");
		return;
	}

	// Finally, we see what happens when a timeout occurs. In this case the image
	// validity shall play no role in the test outcome. We test both cases anyway.
	// First of all, the TC shall be reset, initialized and re-armed.
	CriticalTelecommand_reset((void*)pTc);
	CriticalTelecommand_setObsClock((void*)pTc, (ObsClock*)pObsClk);
	CriticalTelecommand_setMaxArmedDuration((void*)pTc, maxArmedDuration);
	PunctualAction_execute((PunctualAction*)pTc);

	// The image validity is set to true
	DC_DummyCriticalTelecommand_setImageValidity(pTc, true);

	// Then the OBS clock is set to a value such that the TC times out
    TD_ObsTime time = CriticalTelecommand_getTimeWhenArmed((void*)pTc) + 
                      maxArmedDuration;
	DC_DummyObsClock_setTime(pObsClk, time);
    DC_DummyObsClock_setCycle(pObsClk, 0);

	// And it is verified that the TC actually times out and an event is
	// reported
	if (tc->canExecute(pTc)) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Timed-out TC can be executed");
		return;
	}

	if (!verifyLatestEvent(obj, (nEvt+10), EVT_CRIT_TC_TIMEOUT)) return;

	// We do the same on a TC with an invalid image
	CriticalTelecommand_reset((void*)pTc);
	CriticalTelecommand_setObsClock((void*)pTc, (void*)pObsClk);
	CriticalTelecommand_setMaxArmedDuration((void*)pTc, maxArmedDuration);
	PunctualAction_execute((PunctualAction*)pTc);

	// The image validity is set to false, this time
	DC_DummyCriticalTelecommand_setImageValidity(pTc, false);

	// The rest is the same as in the previous test
    time = CriticalTelecommand_getTimeWhenArmed((void*)pTc) + 
           maxArmedDuration;
	DC_DummyObsClock_setTime(pObsClk, time);
    DC_DummyObsClock_setCycle(pObsClk, 0);

	if (tc->canExecute(pTc)) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Timed-out TC can be executed");
		return;
	}

	if (!verifyLatestEvent(obj, (nEvt+13), EVT_CRIT_TC_TIMEOUT)) return;

	TestCase_setTestResult((TestCase*)obj, TEST_SUCCESS, "Test Successful");
	return;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj){}

TestCaseDummyCriticalTelecommand_2* TestCaseDummyCriticalTelecommand_2_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEDUMMYCRITICALTELECOMMAND_2);

    TESTCASEWITHEVTCHECK_GET_CLASS(obj)->post_init((TestCaseWithEvtCheck*)obj,
                                             ID_DUMMYCRITICALTELECOMMAND*10+2,
                                        "TestCaseDummyCriticalTelecommand_2"); 

    return (TestCaseDummyCriticalTelecommand_2*)obj;
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
    .name = TYPE_TESTCASEDUMMYCRITICALTELECOMMAND_2,
    .parent = TYPE_TESTCASEWITHEVTCHECK,
    .instance_size = sizeof(TestCaseDummyCriticalTelecommand_2),
    .abstract = false,
    .class_size = sizeof(TestCaseDummyCriticalTelecommand_2Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseDummyCriticalTelecommand_2_register(void)
{
    type_register_static(&type_info);
}
