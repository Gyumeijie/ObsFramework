//
//
// TestCaseManoeuvreManager_1.c
//

#include "TestCaseManoeuvreManager_1.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../Manoeuvre/CC_ManoeuvreManager.h"
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
	const unsigned int nMan = 8;

    CC_ManoeuvreManager *pMM = CC_ManoeuvreManager_new();
    CC_ManoeuvreManagerClass *cc_mmc = CC_MANOEUVREMANAGER_GET_CLASS(pMM);
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pMM);

    // Verify correctness of class identifier
    if (CC_RootObject_getClassId((CC_RootObject*)pMM) != ID_MANOEUVREMANAGER) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong class identifier");
		return;
	}

	// A newly created ManoeuvreManager shall not be configured
	if (cc_roc->isObjectConfigured(pMM)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Newly created ManoeuvreManager already configured");
		return;
	}

	// Configure the ManoeuvreManager and verify the operation
	CC_ManoeuvreManager_setPendingManoeuvreListSize(pMM, nMan);
	if (CC_ManoeuvreManager_getPendingManoeuvreListSize(pMM) != nMan) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong getPendingManoeuvreListSize return value");
		return;
	}

	// Now it should be configured
	if (!cc_roc->isObjectConfigured(pMM)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "ManoeuvreManager not configured");
		return;
	}

	// Clearly, there shall be no pending manoeuvres
	if (CC_ManoeuvreManager_getPendingManoeuvres(pMM) != 0) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong getPendingManoeuvres return value");
		return;
	}

	// The following steps check the load(), unload() and abort() methods.
	// Let's create an array of DC_DummyManoeuvre pointers to be used in the
	// subsequent tests.
	Manoeuvre *pM[nMan+1];

	for (unsigned int i=0; i<=nMan; i++) {
        pM[i] = (Manoeuvre*)DC_DummyManoeuvre_new();
    }

	for (unsigned int i=0; i<nMan; i++) {
		// Load the manouvre
		cc_mmc->load(pMM, pM[i]);

		// Verify that manCounter is incremented
		if (CC_ManoeuvreManager_getPendingManoeuvres(pMM) != (i+1)) {
			TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                   "manCounter was not incremented");
			return;
		}

		// Set the "in use" flag
        Manoeuvre_setInUse(pM[i], true);
	}

	// A manoeuvre is aborted and the effect of the operation verified
	cc_mmc->abort(pMM, pM[nMan-1]);
	if (CC_ManoeuvreManager_getPendingManoeuvres(pMM) != (nMan-1)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "manCounter was not decremented");
		return;
	}

	// Check that the manouvre is no longer in use
	if (Manoeuvre_isInUse(pM[nMan-1])) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Aborted manoeuvre still in use");
		return;
	}

	// Load the previously aborted manoeuvre
	cc_mmc->load(pMM, pM[nMan-1]);

	// Try loading more manoeuvres that the allocated space and verify
	// that the event is reported.
	cc_mmc->load(pMM, pM[nMan]);
	if (!verifyLatestEvent(obj, (nEvt+nMan+3), EVT_MAN_LIST_FULL))
		return;

	// Finally, let's reset the manoeuvre manager and verify that all
	// the pending manoeuvres are aborted.
	CC_ManoeuvreManager_reset(pMM);
	for (unsigned int i=0; i<nMan; i++) {
		if (Manoeuvre_isInUse(pM[i])) {
			TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                    "Reset failed to abort a manoeuvre");
			return;
		}
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

TestCaseManoeuvreManager_1* TestCaseManoeuvreManager_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEMANOEUVREMANAGER_1);

    TESTCASEWITHEVTCHECK_GET_CLASS(obj)->post_init((TestCaseWithEvtCheck*)obj,
                                                     ID_MANOEUVREMANAGER*10+1,
                                                 "TestCaseManoeuvreManager_1"); 

    return (TestCaseManoeuvreManager_1*)obj;
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
    .name = TYPE_TESTCASEMANOEUVREMANAGER_1,
    .parent = TYPE_TESTCASEWITHEVTCHECK,
    .instance_size = sizeof(TestCaseManoeuvreManager_1),
    .abstract = false,
    .class_size = sizeof(TestCaseManoeuvreManager_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseManoeuvreManager_1_register(void)
{
    type_register_static(&type_info);
}
