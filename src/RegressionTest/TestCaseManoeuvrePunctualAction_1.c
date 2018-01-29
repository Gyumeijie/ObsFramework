//
//
// TestCaseManoeuvrePunctualAction_1.c
//

#include "TestCaseManoeuvrePunctualAction_1.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../Manoeuvre/DC_DummyManoeuvre.h"
#include "../Manoeuvre/CC_ManoeuvreManager.h"
#include "../Manoeuvre/DC_ManoeuvrePunctualAction.h"



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
	Manoeuvre *pDM = (Manoeuvre*)DC_DummyManoeuvre_new();
	CC_ManoeuvreManager *pMM = CC_ManoeuvreManager_new();
    DC_ManoeuvrePunctualAction *pMPA = DC_ManoeuvrePunctualAction_new();
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pMPA);

	// Initialize the manoeuvre manager
	CC_ManoeuvreManager_setPendingManoeuvreListSize(pMM, 1);

    // Verify correctness of class identifier
    if (CC_RootObject_getClassId((CC_RootObject*)pMPA) != ID_MANOEUVREPUNCTUALACTION) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong class identifier");
		return;
	}

	// The newly created object should not be configured
	if (cc_roc->isObjectConfigured(pMPA)) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Newly created object is configured");
		return;
	}

	// We link a manoeuvre manager to the action and verify that
	// it is properly reported and the object is not yet configured
	DC_ManoeuvrePunctualAction_setManoeuvreManager(pMPA, pMM);

	if (DC_ManoeuvrePunctualAction_getManoeuvreManager(pMPA) != pMM)
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Could not set/get the manoeuvre manager");
		return;
	}

	if (cc_roc->isObjectConfigured(pMPA)) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong configuration status");
		return;
	}

	// We link a manoeuvre to the action and verify that it
	// is properly reported and the object is now configured
	DC_ManoeuvrePunctualAction_setManoeuvre(pMPA, pDM);

	if (DC_ManoeuvrePunctualAction_getManoeuvre(pMPA) != pDM) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Could not set/get the manoeuvre");
		return;
	}

	if (!cc_roc->isObjectConfigured(pMPA)) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Object is not configured");
		return;
	}

	// Let's execute the action and verify that the manoeuvre is loaded
	PunctualAction_execute((PunctualAction*)pMPA);

	if (CC_ManoeuvreManager_getPendingManoeuvres(pMM) != 1) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Action failed to execute");
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

TestCaseManoeuvrePunctualAction_1* TestCaseManoeuvrePunctualAction_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEMANOEUVREPUNCTUALACTION_1);
    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                              ID_MANOEUVREPUNCTUALACTION*10+1,
                                          "TestCaseManoeuvrePunctualAction_1"); 

    return (TestCaseManoeuvrePunctualAction_1*)obj;
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
    .name = TYPE_TESTCASEMANOEUVREPUNCTUALACTION_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseManoeuvrePunctualAction_1),
    .abstract = false,
    .class_size = sizeof(TestCaseManoeuvrePunctualAction_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseManoeuvrePunctualAction_1_register(void)
{
    type_register_static(&type_info);
}
