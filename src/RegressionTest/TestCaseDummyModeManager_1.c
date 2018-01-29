//
//
// TestCaseDummyModeManager_1.c
//

#include "TestCaseDummyModeManager_1.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../Base/DC_DummyModeManager.h"
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
    DC_DummyModeManager *pMM = DC_DummyModeManager_new();
    ModeManagerClass *mmc = MODEMANAGER_GET_CLASS(pMM);
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pMM);
    DC_EventRepository *pRep = CC_RootObject_getEventRepository();

    // Verify correctness of class identifier
    if (CC_RootObject_getClassId((CC_RootObject*)pMM) != ID_DUMMYMODEMANAGER) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong class identifier");
		return;
	}

    // Dummy mode managers should not be configured at creation
    if (cc_roc->isObjectConfigured(pMM) == CONFIGURED) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong configuration status at creation");
		return;
	}

    // Load number of modes and check correctness
    TD_Mode n = 3;
    ModeManager_setNumberOfModes((ModeManager*)pMM, n);
    if (ModeManager_getNumberOfModes((ModeManager*)pMM) != n) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong number of modes");
		return;
	}

    // Load default mode and check that component is configured
    TD_Mode def = 1;
    ModeManager_setDefaultMode((ModeManager*)pMM, def);
    if (cc_roc->isObjectConfigured(pMM) != CONFIGURED) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong configuration status");
		return;
	}

    // Attempt to load illegal default mode and check correct event
    if (TestCase_isNonNominalCheckAllowed(obj)) {
        ModeManager_setDefaultMode((ModeManager*)pMM, 3);
        if (!verifyLatestEvent(obj, nEvt+1,EVT_ILLEGAL_MM)) return;
        nEvt++;
    }

    // Reset the component to complete initialization sequence
    // The current mode should be the default mode
    mmc->reset(pMM);
    if (ModeManager_getCurrentMode((ModeManager*)pMM) != def) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Current mode is not default mode");
		return;
	}

    // Check that all mode transitions are enabled
    if (!ModeManager_isTransitionEnabled((ModeManager*)pMM)) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Transitions are not enabled");
		return;
	}
    for (TD_Mode i=0; i<n; i++) {
        if (!ModeManager_isTransitionEnabledToMode((ModeManager*)pMM, i)) {	
            TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                    "Transition is not enabled");
	    	return;
	    }
    }

    // Perform an update and verify correct functioning and event reporting
    mmc->update(pMM);
    if (ModeManager_getCurrentMode((ModeManager*)pMM) != def+1) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Mode transition was not performed");
		return;
	}
    if (DC_EventRepository_getCounter(pRep) != nEvt+1) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong number of events");
		return;
	}
    if (!verifyLatestEvent(obj, nEvt+1, EVT_MOD_TRANS_PERFORMED)) return;
    nEvt++;

    // Disable mode transitions and verify correctness
    ModeManager_setTransitionEnableStatus((ModeManager*)pMM, DISABLED);
    if (ModeManager_isTransitionEnabled((ModeManager*)pMM)) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong transition enable status");
		return;
	}

    // Attempt update and verify that no mode transition occurs and that
    // event report was correctly generated
    mmc->update(pMM);
    if (ModeManager_getCurrentMode((ModeManager*)pMM) != def+1) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong operational mode");
		return;
	}
    if (!verifyLatestEvent(obj, nEvt+1, EVT_MOD_TRANS_INHIBITED)) return;
    nEvt++;

    // Disable transitions to mode and verify correctness
    ModeManager_setTransitionEnableStatus((ModeManager*)pMM, ENABLED);
    ModeManager_setTransitionEnableStatusToMode((ModeManager*)pMM, 1, DISABLED);
    if (ModeManager_isTransitionEnabledToMode((ModeManager*)pMM, 1) != DISABLED) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong enable status");
		return;
	}

    // Make two update requests. The last one should fail
    mmc->update(pMM);  // perform transition from mode 2 to mode 0
    mmc->update(pMM);  // attempt (disabled) transitions from mode 0 to mode 1
    if (ModeManager_getCurrentMode((ModeManager*)pMM) != 0) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong mode");
		return;
	}
    nEvt = nEvt+2; // each call to update() should generate an event

    // Attempt to todisable transition to non-existent mode and check correct event
    if (TestCase_isNonNominalCheckAllowed(obj)) {
        ModeManager_setTransitionEnableStatusToMode((ModeManager*)pMM, 3, false);
        if (!verifyLatestEvent(obj, nEvt+1, EVT_ILLEGAL_MM)) return;
        nEvt++;
    }

    // Perform reset and verify correctness
    mmc->reset(pMM);
    if (ModeManager_getCurrentMode((ModeManager*)pMM) != def) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong mode after reset");
		return;
	}
    if (!ModeManager_isTransitionEnabled((ModeManager*)pMM)) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong transition enable status after reset");
		return;
	}
    for (TD_Mode i=0; i<n; i++) {
        if (!ModeManager_isTransitionEnabledToMode((ModeManager*)pMM, i)) {	
            TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                    "Transition is not enabled after reset");
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

TestCaseDummyModeManager_1* TestCaseDummyModeManager_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEDUMMYMODEMANAGER_1);

    TESTCASEWITHEVTCHECK_GET_CLASS(obj)->post_init((TestCaseWithEvtCheck*)obj,
                                                    ID_DUMMYMODEMANAGER*10+1,
                                                    "TestCaseDummyModeManager_1"); 

    return (TestCaseDummyModeManager_1*)obj;
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
    .name = TYPE_TESTCASEDUMMYMODEMANAGER_1,
    .parent = TYPE_TESTCASEWITHEVTCHECK,
    .instance_size = sizeof(TestCaseDummyModeManager_1),
    .abstract = false,
    .class_size = sizeof(TestCaseDummyModeManager_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseDummyModeManager_1_register(void)
{
    type_register_static(&type_info);
}
