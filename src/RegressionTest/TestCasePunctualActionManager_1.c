//
//
// TestCasePunctualActionManager_1.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../Base/DC_DummyPunctualAction.h"
#include "../Base/DC_SimplePunctualActionModeManager.h"
#include "../Base/CC_PunctualActionManager.h"
#include "TestCasePunctualActionManager_1.h"



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
    const unsigned int numberOfActions=4;

    CC_PunctualActionManager *pPAM = CC_PunctualActionManager_new();
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pPAM);

    DC_SimplePunctualActionModeManager *pPAMM;
    PunctualActionModeManagerClass *pammc;
    pPAMM = DC_SimplePunctualActionModeManager_new();
    ModeManagerClass *mmc = MODEMANAGER_GET_CLASS(pPAMM);

    // Configure the mode manager and the add a newly created
    // punctual actions to its only list
    PunctualActionListModeManager_setListLength((void*)pPAMM, 0, numberOfActions);

    for (unsigned int i=0; i<numberOfActions; i++) {
        PunctualActionListModeManager_setListItem((void*)pPAMM, 0, i, 
                                  (PunctualAction*)DC_DummyPunctualAction_new());
    }

    mmc->reset(pPAMM);

	// Verify the correctness of the class id
	if (CC_RootObject_getClassId((CC_RootObject*)pPAM) != ID_PUNCTUALACTIONMANAGER) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong class id");
		return;
	}

    // A newly created action manager shall not be configured
    if (cc_roc->isObjectConfigured(pPAM)) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong configuration status at creation");
		return;
    }

    // The mode manager pointer shall be null
    if (CC_PunctualActionManager_getPunctualActionModeManager(pPAM))
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Non NULL mode manager pointer at creation");
		return;
    }

    // Now we set the mode manager pointer and we verify that it is properly
    // stored and that the object is configured
    CC_PunctualActionManager_setPunctualActionModeManager(pPAM, (void*)pPAMM);
    if (CC_PunctualActionManager_getPunctualActionModeManager(pPAM) != (void*)pPAMM) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "setPunctualActionModeManager() failed");
		return;
    }

    if (!cc_roc->isObjectConfigured(pPAM)) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong configuration status");
		return;
    }

    // The activate() method is invoked twice and it is verified that
    // the punctual actions' activation counters reflect this fact
    CC_PunctualActionManager_activate(pPAM);
    CC_PunctualActionManager_activate(pPAM);

    pammc = PUNCTUALACTIONMODEMANAGER_GET_CLASS(pPAMM);
    for (pammc->first(pPAMM);
             pammc->isIterationFinished(pPAMM);
                  pammc->next(pPAMM)) 
    {
        DC_DummyPunctualAction *pDPA;

        pDPA = (DC_DummyPunctualAction*)pammc->getIterationPunctualAction(pPAMM);
        if (DC_DummyPunctualAction_getActivationCounter(pDPA) != 2)
        {
            TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                    "activate() failed");
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

TestCasePunctualActionManager_1* TestCasePunctualActionManager_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEPUNCTUALACTIONMANAGER_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                ID_PUNCTUALACTIONMANAGER*10+1,
                                           "TestCasePunctualActionManager_1"); 

    return (TestCasePunctualActionManager_1*)obj;
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
    .name = TYPE_TESTCASEPUNCTUALACTIONMANAGER_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCasePunctualActionManager_1),
    .abstract = false,
    .class_size = sizeof(TestCasePunctualActionManager_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCasePunctualActionManager_1_register(void)
{
    type_register_static(&type_info);
}
