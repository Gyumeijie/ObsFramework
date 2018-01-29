//
//
// TestCaseSimpleTelemetryModeManager_1.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Telemetry/DC_SimpleTelemetryModeManager.h"
#include "../Telemetry/DC_DataItem16TmWord.h"
#include "../Base/ModeManager.h"
#include "TestCaseSimpleTelemetryModeManager_1.h"



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
    DC_SimpleTelemetryModeManager *pMM = DC_SimpleTelemetryModeManager_new();
    ModeManagerClass *mmc = MODEMANAGER_GET_CLASS(pMM);
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pMM);

    // Verify correctness of class identifier
    if (CC_RootObject_getClassId((CC_RootObject*)pMM) != ID_SIMPLETELEMETRYMODEMANAGER)
	{	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong class identifier");
		return;
	}

    // Configure the simple telemetry mode manager with
    // one list of 2 dummy telemetry words
    TelemetryListModeManager_setListLength((void*)pMM, 0, 1);
    DC_DataItem16TmWord *pW = DC_DataItem16TmWord_new();
    TelemetryListModeManager_setListItem((void*)pMM, 0, 0, (TelemetryPacket*)pW);
    mmc->reset(pMM);

    // Check that the telemetry mode managers is configured
    if (cc_roc->isObjectConfigured(pMM) != CONFIGURED)
	{	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong configuration status at creation");
		return;
	}

    // Check current mode and number of modes
    if (ModeManager_getNumberOfModes((ModeManager*)pMM) != 1)
	{	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong number of modes");
		return;
	}
    if (ModeManager_getCurrentMode((ModeManager*)pMM) != 0)
	{	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong current mode");
		return;
	}

    // Make an update request and check that the current mode has not changed
    mmc->update(pMM);
    if (ModeManager_getCurrentMode((ModeManager*)pMM) != 0)
	{	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong current mode");
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

TestCaseSimpleTelemetryModeManager_1* TestCaseSimpleTelemetryModeManager_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASESIMPLETELEMETRYMODEMANAGER_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                           ID_SIMPLETELEMETRYMODEMANAGER*10+1,
                                      "TestCaseSimpleTelemetryModeManager_1"); 

    return (TestCaseSimpleTelemetryModeManager_1*)obj;
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
    .name = TYPE_TESTCASESIMPLETELEMETRYMODEMANAGER_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseSimpleTelemetryModeManager_1),
    .abstract = false,
    .class_size = sizeof(TestCaseSimpleTelemetryModeManager_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseSimpleTelemetryModeManager_1_register(void)
{
    type_register_static(&type_info);
}
