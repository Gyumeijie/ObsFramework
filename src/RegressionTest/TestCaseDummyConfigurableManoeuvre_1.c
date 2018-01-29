//
//
// TestCaseDummyConfigurableManoeuvre_1.c
//

#include "TestCaseDummyConfigurableManoeuvre_1.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../Manoeuvre/DC_DummyConfigurableManoeuvre.h"



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
    DC_DummyConfigurableManoeuvre *pDCM = DC_DummyConfigurableManoeuvre_new();
    ManoeuvreClass *mc = MANOEUVRE_GET_CLASS(pDCM);

    // Verify correctness of class identifier
    if (CC_RootObject_getClassId((CC_RootObject*)pDCM) != ID_DUMMYCONFIGURABLEMANOEUVRE) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong class identifier");
		return;
	}

	// Check that the action counters are set to zero
	if ((DC_DummyConfigurableManoeuvre_getInitializationActionCounter(pDCM) != 0) ||
		(DC_DummyConfigurableManoeuvre_getContinuationActionCounter(pDCM) != 0) ||
		(DC_DummyConfigurableManoeuvre_getTerminationActionCounter(pDCM) != 0)) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Action counter(s) not equal to zero");
		return;
	}

	// Verify the canStart() return value
	Manoeuvre_setInUse((Manoeuvre*)pDCM, true);
	if (mc->canStart(pDCM) != MAN_CANNOT_START) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Incorrect canStart() return value");
		return;
	}

	// Verify that the initializationActionCounter is incremented
	mc->initialize(pDCM);
	if (DC_DummyConfigurableManoeuvre_getInitializationActionCounter(pDCM) != 1)
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "initializationActionCounter not incremented");
		return;
	}

	// Verify that the continuationActionCounter is incremented
	Manoeuvre_doContinue((Manoeuvre*)pDCM);
	if (DC_DummyConfigurableManoeuvre_getContinuationActionCounter(pDCM) != 1) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "continuationActionCounter not incremented");
		return;
	}

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
	if (DC_DummyConfigurableManoeuvre_getTerminationActionCounter(pDCM)!=1) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "terminationActionCounter not incremented");
		return;
	}

	// Check that the status flags can be modified
    DC_DummyConfigurableManoeuvre_setStartCheckStatus(pDCM, MAN_CAN_START);
    DC_DummyConfigurableManoeuvre_setContinuationCheckStatus(pDCM, MAN_CAN_CONTINUE);
    DC_DummyConfigurableManoeuvre_setTerminationCheckStatus(pDCM, MAN_HAS_TERMINATED);

	mc->initialize(pDCM);

	if (mc->canStart(pDCM)!=MAN_CAN_START) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Incorrect canStart() return value");
		return;
	}

	Manoeuvre_doContinue((Manoeuvre*)pDCM);

	if (mc->canContinue(pDCM)!=MAN_CAN_CONTINUE) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Incorrect canContinue() return value");
		return;
	}

	if (mc->isFinished(pDCM)!=MAN_HAS_TERMINATED) 
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

TestCaseDummyConfigurableManoeuvre_1* TestCaseDummyConfigurableManoeuvre_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEDUMMYCONFIGURABLEMANOEUVRE_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                           ID_DUMMYCONFIGURABLEMANOEUVRE*10+1,
                                      "TestCaseDummyConfigurableManoeuvre_1"); 

    return (TestCaseDummyConfigurableManoeuvre_1*)obj;
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
    .name = TYPE_TESTCASEDUMMYCONFIGURABLEMANOEUVRE_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseDummyConfigurableManoeuvre_1),
    .abstract = false,
    .class_size = sizeof(TestCaseDummyConfigurableManoeuvre_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseDummyConfigurableManoeuvre_1_register(void)
{
    type_register_static(&type_info);
}
