//
//
// TestCaseCyclingPunctualActionModeManager_1.c
//

#include "TestCaseCyclingPunctualActionModeManager_1.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/DC_CyclingPunctualActionModeManager.h"
#include "../Base/DC_DummyPunctualAction.h"
#include "../Base/ModeManager.h"
#include "../Event/DC_EventRepository.h"



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
    unsigned int nEvt = TestCaseWithEvtCheck_getNumberOfEvents(obj);
    DC_CyclingPunctualActionModeManager *pMM = DC_CyclingPunctualActionModeManager_new();
    ModeManagerClass *mmc = MODEMANAGER_GET_CLASS(pMM);
    PunctualActionModeManagerClass *pammc = PUNCTUALACTIONMODEMANAGER_GET_CLASS(pMM);
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pMM);

    // Verify correctness of class identifier
    if (CC_RootObject_getClassId((CC_RootObject*)pMM) != ID_CYCLINGPUNCTUALACTIONMODEMANAGER) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong class identifier");
		return;
	}

    // Mode managers should not be configured at creation
    if (cc_roc->isObjectConfigured(pMM) == CONFIGURED) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong configuration status at creation");
		return;
	}

	// Create the items to be loaded in the list mode manager
	DC_DummyPunctualAction *list1 = g_malloc(sizeof(DC_DummyPunctualAction)*3);
	DC_DummyPunctualAction *list2 = g_malloc(sizeof(DC_DummyPunctualAction)*2);
	DC_DummyPunctualAction *list3 = g_malloc(sizeof(DC_DummyPunctualAction)*3);

    // Configure the dummy mode manager
    TD_Mode n = 3;
    TD_Mode def = 1;
    ModeManager_setNumberOfModes((ModeManager*)pMM, n);
    ModeManager_setDefaultMode((ModeManager*)pMM, def);
    PunctualActionListModeManager_setListLength((void*)pMM, 0, 3);
    
    PunctualActionListModeManager_setListItem((void*)pMM, 0, 0, (PunctualAction*)&list1[0]);
    PunctualActionListModeManager_setListItem((void*)pMM, 0, 1, (PunctualAction*)&list1[1]);
    PunctualActionListModeManager_setListItem((void*)pMM, 0, 2, (PunctualAction*)&list1[2]);

    PunctualActionListModeManager_setListLength((void*)pMM, 1, 2);
    PunctualActionListModeManager_setListItem((void*)pMM, 1, 0, (PunctualAction*)&list2[0]);
    PunctualActionListModeManager_setListItem((void*)pMM, 1, 1, (PunctualAction*)&list2[1]);

    PunctualActionListModeManager_setListLength((void*)pMM, 2, 3);
    PunctualActionListModeManager_setListItem((void*)pMM, 2, 0, (PunctualAction*)&list3[0]);
    PunctualActionListModeManager_setListItem((void*)pMM, 2, 1, (PunctualAction*)&list3[1]);
    PunctualActionListModeManager_setListItem((void*)pMM, 2, 2, (PunctualAction*)&list3[2]);

    mmc->reset(pMM);

    // Verify that the component is now configured
    if (cc_roc->isObjectConfigured(pMM) != CONFIGURED) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong configuration status");
		return;
	}

    // Iterate through the list items and verify correctness
    int i = 0;
    for (pammc->first(pMM); !pammc->isIterationFinished(pMM); pammc->next(pMM)) {
        PunctualAction *a = pammc->getIterationPunctualAction(pMM);
        if ((a) != (PunctualAction*)&list2[i]) {	
            TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                   "Error during iteration");
		    return;
	    }
        i++;
    }
    if (i != 2) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong number of iteration cycles");
		return;
	}

    // Check effect of non-nominal call to next()
    pammc->next(pMM);
    if ((PunctualAction*)&list2[1] != (pammc->getIterationPunctualAction(pMM))) {   
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Error after non-nominal call to nextInt()");
	    return;
	}

    // Check iterators with an intermediate call to update()
    mmc->update(pMM);  // active list should now be a3[]
    if (ModeManager_getCurrentMode((ModeManager*)pMM) != def+1) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong mode");
	    return;
    }

    pammc->first(pMM);     // iteration list should now be a3[]
    PunctualAction *item = pammc->getIterationPunctualAction(pMM);
    if ((item) != (PunctualAction*)&list3[0]) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Error during iteration");
	    return;
    }

    // active list should now be a1[] but iteration list should still be a3[]
    mmc->update(pMM);  
    if (ModeManager_getCurrentMode((ModeManager*)pMM) != 0) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong mode");
	    return;
    }

    pammc->next(pMM);
    item = pammc->getIterationPunctualAction(pMM);
    if ((item) != (PunctualAction*)&list3[1]) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Error during iteration");
	    return;
    }

    // Attempt illegal reconfiguration of list and check correctness of event
    if (TestCase_isNonNominalCheckAllowed(obj)) {
        PunctualActionListModeManager_setListItem((void*)pMM, 1, 2, (PunctualAction*)&list2[1]);
        if (verifyLatestEvent(obj, nEvt+1, EVT_ILLEGAL_MM)) return;
        nEvt++;
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

TestCaseCyclingPunctualActionModeManager_1* TestCaseCyclingPunctualActionModeManager_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASECYCLINGPUNCTUALACTIONMODEMANAGER_1);

    TESTCASEWITHEVTCHECK_GET_CLASS(obj)->post_init((TestCaseWithEvtCheck*)obj,
                                     ID_CYCLINGPUNCTUALACTIONMODEMANAGER*10+1,
                                "TestCaseCyclingPunctualActionModeManager_1");

    return (TestCaseCyclingPunctualActionModeManager_1*)obj;
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
    .name = TYPE_TESTCASECYCLINGPUNCTUALACTIONMODEMANAGER_1,
    .parent = TYPE_TESTCASEWITHEVTCHECK,
    .instance_size = sizeof(TestCaseCyclingPunctualActionModeManager_1),
    .abstract = false,
    .class_size = sizeof(TestCaseCyclingPunctualActionModeManager_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseCyclingPunctualActionModeManager_1_register(void)
{
    type_register_static(&type_info);
}
