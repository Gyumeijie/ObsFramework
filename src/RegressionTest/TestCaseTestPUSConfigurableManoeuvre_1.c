//
//
// TestCaseTestPUSConfigurableManoeuvre_1.c
//

#include "TestCaseTestPUSConfigurableManoeuvre_1.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../Utilities/TestCaseWithEvtCheck.h"
#include "../Manoeuvre/DC_TestPUSConfigurableManoeuvre.h"



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
    DC_TestPUSConfigurableManoeuvre *pDCM = DC_TestPUSConfigurableManoeuvre_new();
    PUSTcManoeuvreClass *pustmc = PUSTCMANOEUVRE_GET_CLASS(pDCM); 
    ManoeuvreClass *mc = MANOEUVRE_GET_CLASS(pDCM);

    // Verify correctness of class identifier
    if (CC_RootObject_getClassId((CC_RootObject*)pDCM) != ID_TESTPUSCONFIGURABLEMANOEUVRE) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong class identifier");
		return;
	}

	// Check that the action counters are set to zero
	if ((DC_TestPUSConfigurableManoeuvre_getInitializationActionCounter(pDCM) != 0) ||
		(DC_TestPUSConfigurableManoeuvre_getContinuationActionCounter(pDCM) != 0) ||
		(DC_TestPUSConfigurableManoeuvre_getTerminationActionCounter(pDCM) !=0))
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Action counter(s) not equal to zero");
		return;
	}

    // Check completion and progress acknowledge flag values
    if (PUSTcManoeuvre_isCompletionAckRequired((PUSTcManoeuvre*)pDCM) ||
        PUSTcManoeuvre_isProgressAckRequired((PUSTcManoeuvre*)pDCM) || 
        PUSTcManoeuvre_isStartAckRequired((PUSTcManoeuvre*)pDCM)) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                              "Incorrect acknowledge flag default values");
		return;
	}

    // Set and read back start, completion and progress acknowledge flag values
    PUSTcManoeuvre_setStartAckFlag((PUSTcManoeuvre*)pDCM, true);
    PUSTcManoeuvre_setCompletionAckFlag((PUSTcManoeuvre*)pDCM, true);
    PUSTcManoeuvre_setProgressAckFlag((PUSTcManoeuvre*)pDCM, true);
    if (!PUSTcManoeuvre_isCompletionAckRequired((PUSTcManoeuvre*)pDCM) || 
        !PUSTcManoeuvre_isProgressAckRequired((PUSTcManoeuvre*)pDCM)) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Incorrect acknowledge flag default values");
		return;
	}

    // Set and read back telecommand identifier value
    pustmc->setTelecommandId(pDCM, 13);
    if (pustmc->getTelecommandId(pDCM) != 13) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Incorrect telecommand ID value");
		return;
	}

	// Verify the canStart() return value
	Manoeuvre_setInUse((Manoeuvre*)pDCM, true);
	if (mc->canStart(pDCM) != MAN_CANNOT_START) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Incorrect canStart() return value");
		return;
	}

	// Verify that the initializationActionCounter is incremented
	mc->initialize(pDCM);
	if (DC_TestPUSConfigurableManoeuvre_getInitializationActionCounter(pDCM) != 1)
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "initializationActionCounter not incremented");
		return;
	}

	// Verify that the continuationActionCounter is incremented 
	Manoeuvre_doContinue((Manoeuvre*)pDCM);
	if (DC_TestPUSConfigurableManoeuvre_getContinuationActionCounter(pDCM) != 1)
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "continuationActionCounter not incremented");
		return;
	}

	// Verify a "manoeuvre progress event" is generated when the manoeuvre advances
    unsigned int nEvt = TestCaseWithEvtCheck_getNumberOfEvents(obj);
	Manoeuvre_doContinue((Manoeuvre*)pDCM);
	if (DC_TestPUSConfigurableManoeuvre_getContinuationActionCounter(pDCM) != 2) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "continuationActionCounter not incremented");
		return;
	}
    if (!verifyLatestEvent(obj, nEvt+1, EVT_MAN_PROGRESS)) return;

	// Check that the continuation flag is properly set
	if (mc->canContinue(pDCM) != MAN_CANNOT_CONTINUE) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Incorrect canContinue() return value");
		return;
	}

	// Check that the termination flag is properly set
	if (mc->isFinished(pDCM) != MAN_HAS_NOT_TERMINATED) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Incorrect isFinished() return value");
		return;
	}

	// Verify that the terminationActionCounter is incremented
	Manoeuvre_terminate((Manoeuvre*)pDCM);
	if (DC_TestPUSConfigurableManoeuvre_getTerminationActionCounter(pDCM) != 1) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "terminationActionCounter not incremented");
		return;
	}

	// Check that the status flags can be modified
    DC_TestPUSConfigurableManoeuvre_setStartCheckStatus(pDCM, MAN_CAN_START);
    DC_TestPUSConfigurableManoeuvre_setContinuationCheckStatus(pDCM, MAN_CAN_CONTINUE);
    DC_TestPUSConfigurableManoeuvre_setTerminationCheckStatus(pDCM, MAN_HAS_TERMINATED);

	mc->initialize(pDCM);

	if (mc->canStart(pDCM) != MAN_CAN_START) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Incorrect canStart() return value");
		return;
	}

	Manoeuvre_doContinue((Manoeuvre*)pDCM);

	if (mc->canContinue(pDCM) != MAN_CAN_CONTINUE) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Incorrect canContinue() return value");
		return;
	}

	if (mc->isFinished(pDCM) != MAN_HAS_TERMINATED) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Incorrect isFinished() return value");
		return;
	}

	Manoeuvre_terminate((Manoeuvre*)pDCM);

	TestCase_setTestResult((TestCase*)obj, TEST_SUCCESS, "Test Successful");
	return;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj){}

TestCaseTestPUSConfigurableManoeuvre_1* TestCaseTestPUSConfigurableManoeuvre_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASETESTPUSCONFIGURABLEMANOEUVRE_1);

    TESTCASEWITHEVTCHECK_GET_CLASS(obj)->post_init((TestCaseWithEvtCheck*)obj,
                                         ID_TESTPUSCONFIGURABLEMANOEUVRE*10+1,
						             "TestCaseTestPUSConfigurableManoeuvre_1"); 

    return (TestCaseTestPUSConfigurableManoeuvre_1*)obj;
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
    .name = TYPE_TESTCASETESTPUSCONFIGURABLEMANOEUVRE_1,
    .parent = TYPE_TESTCASEWITHEVTCHECK,
    .instance_size = sizeof(TestCaseTestPUSConfigurableManoeuvre_1),
    .abstract = false,
    .class_size = sizeof(TestCaseTestPUSConfigurableManoeuvre_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseTestPUSConfigurableManoeuvre_1_register(void)
{
    type_register_static(&type_info);
}
