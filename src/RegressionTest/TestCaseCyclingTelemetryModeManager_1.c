//
//
// TestCaseCyclingTelemetryModeManager_1.c
//

#include "TestCaseCyclingTelemetryModeManager_1.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Telemetry/DC_CyclingTelemetryModeManager.h"
#include "../Telemetry/DC_DummyTelemetryPacket.h"
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
    DC_CyclingTelemetryModeManager *pMM = DC_CyclingTelemetryModeManager_new();
    ModeManagerClass *mmc = MODEMANAGER_GET_CLASS(pMM);
    TelemetryModeManagerClass *tmmc = TELEMETRYMODEMANAGER_GET_CLASS(pMM);
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pMM);

    // Verify correctness of class identifier
    if (CC_RootObject_getClassId((CC_RootObject*)pMM) != ID_CYCLINGTELEMETRYMODEMANAGER)
	{	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong class identifier");
		return;
	}

    // Mode managers should not be configured at creation
    if (cc_roc->isObjectConfigured(pMM) == CONFIGURED)
	{	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong configuration status at creation");
		return;
	}

	// Create the items to be loaded in the list mode manager
	DC_DummyTelemetryPacket *list1 = g_malloc(sizeof(DC_DummyTelemetryPacket)*3);
	DC_DummyTelemetryPacket *list2 = g_malloc(sizeof(DC_DummyTelemetryPacket)*2);
	DC_DummyTelemetryPacket *list3 = g_malloc(sizeof(DC_DummyTelemetryPacket)*3);

    // Configure the dummy mode manager
    TD_Mode n = 3;
    TD_Mode def = 1;
    ModeManager_setNumberOfModes((ModeManager*)pMM, n);
    ModeManager_setDefaultMode((ModeManager*)pMM, def);
    TelemetryListModeManager_setListLength((void*)pMM, 0, 3);
    TelemetryListModeManager_setListLength((void*)pMM, 1, 2);
    TelemetryListModeManager_setListLength((void*)pMM, 2, 3);
    TelemetryListModeManager_setListItem((void*)pMM, 0, 0, (void*)&list1[0]);
    TelemetryListModeManager_setListItem((void*)pMM, 0, 1, (void*)&list1[1]);
    TelemetryListModeManager_setListItem((void*)pMM, 0, 2, (void*)&list1[2]);
    TelemetryListModeManager_setListItem((void*)pMM, 1, 0, (void*)&list2[0]);
    TelemetryListModeManager_setListItem((void*)pMM, 1, 1, (void*)&list2[1]);
    TelemetryListModeManager_setListItem((void*)pMM, 2, 0, (void*)&list3[0]);
    TelemetryListModeManager_setListItem((void*)pMM, 2, 1, (void*)&list3[1]);
    TelemetryListModeManager_setListItem((void*)pMM, 2, 2, (void*)&list3[2]);
    mmc->reset(pMM);

    // Verify that the component is now configured
    if (cc_roc->isObjectConfigured(pMM) != CONFIGURED)
	{	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong configuration status");
		return;
	}

    // Iterate through the list items and verify correctness
    int i = 0;
    for (tmmc->first(pMM); !tmmc->isIterationFinished(pMM); tmmc->next(pMM)) {
        TelemetryPacket *item = tmmc->getIterationTelemetryPacket(pMM);
        if ((item) != (TelemetryPacket*)&list2[i])
	    {	
            TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                    "Error during iteration");
		    return;
	    }
        i++;
    }
    if (i != 2)
	{	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong number of iteration cycles");
		return;
	}

    // Check effect of non-nominal call to next()
    tmmc->next(pMM);
    if ((TelemetryPacket*)&list2[1] != (tmmc->getIterationTelemetryPacket(pMM)))
    {   
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Error after non-nominal call to nextInt()");
	    return;
	}

    // Check iterators with an intermediate call to update()
    mmc->update(pMM);  // active list should now be a3[]
    if (ModeManager_getCurrentMode((ModeManager*)pMM) != def+1)
    {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong mode");
	    return;
    }

    tmmc->first(pMM);                   // iteration list should now be a3[]
    TelemetryPacket *item = tmmc->getIterationTelemetryPacket(pMM);
    if ((item) != (TelemetryPacket*)&list3[0])
    {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Error during iteration");
	    return;
    }

    mmc->update(pMM);  // active list should now be a1[] but iteration list should still be a3[]
    if (ModeManager_getCurrentMode((ModeManager*)pMM) != 0)
    {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong mode");
	    return;
    }

    tmmc->next(pMM);
    item = tmmc->getIterationTelemetryPacket(pMM);
    if ((item) != (TelemetryPacket*)&list3[1])
    {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Error during iteration");
	    return;
    }

    // Attempt illegal reconfiguration of list and check correctness of event
    if (TestCase_isNonNominalCheckAllowed(obj)) {
        TelemetryListModeManager_setListItem((void*)pMM, 1, 2, (void*)&list2[1]);
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

TestCaseCyclingTelemetryModeManager_1* TestCaseCyclingTelemetryModeManager_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASECYCLINGTELEMETRYMODEMANAGER_1);

    TESTCASEWITHEVTCHECK_GET_CLASS(obj)->post_init((TestCaseWithEvtCheck*)obj,
                                          ID_CYCLINGTELEMETRYMODEMANAGER*10+1,
                                     "TestCaseCyclingTelemetryModeManager_1"); 

    return (TestCaseCyclingTelemetryModeManager_1*)obj;
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
    .name = TYPE_TESTCASECYCLINGTELEMETRYMODEMANAGER_1,
    .parent = TYPE_TESTCASEWITHEVTCHECK,
    .instance_size = sizeof(TestCaseCyclingTelemetryModeManager_1),
    .abstract = false,
    .class_size = sizeof(TestCaseCyclingTelemetryModeManager_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseCyclingTelemetryModeManager_1_register(void)
{
    type_register_static(&type_info);
}
