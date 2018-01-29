//
//
// TestCaseTelemetryManager_1.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/TestConstants.h"
#include "../Telemetry/DC_SimpleTelemetryModeManager.h"
#include "../Telemetry/DC_CycleDataItem16TmStream.h"
#include "../Telemetry/CC_TelemetryManager.h"
#include "TestCaseTelemetryManager_1.h"



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

   // Create the telemetry manager
   CC_TelemetryManager *pTm = CC_TelemetryManager_new();
   CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pTm);

   // Check the value of the class identifier
   if (CC_RootObject_getClassId((CC_RootObject*)pTm) != ID_TELEMETRYMANAGER)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong class identifier");
        return;
   }

   // Check that the telemetry manager is not configured
   if (cc_roc->isObjectConfigured(pTm))
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong configuration status");
        return;
   }

   // Create and load a telemetry mode manager and verify that it is loaded
   DC_SimpleTelemetryModeManager *pTmMm = DC_SimpleTelemetryModeManager_new();
   CC_TelemetryManager_setTelemetryModeManager(pTm, (void*)pTmMm);
   if (CC_TelemetryManager_getTelemetryModeManager(pTm) != (void*)pTmMm)
   { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong telemetry mode manager");
        return;
   }

   // Create and load a telemetry stream and verify that it is loaded
   DC_CycleDataItem16TmStream *pTmSt = DC_CycleDataItem16TmStream_new();
   CC_TelemetryManager_setTelemetryStream(pTm, (void*)pTmSt);
   if (CC_TelemetryManager_getTelemetryStream(pTm) != (void*)pTmSt)
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong telemetry stream");
        return;
   }

   // Set the size of the immediate dispatch queue
   CC_TelemetryManager_setImmediateQueueSize(pTm, 0);
   if (CC_TelemetryManager_getImmediateQueueSize(pTm) != 0)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong immediate dispatch queue size");
        return;
   }

   // Check status of the immediate dispatch queue
   if (CC_TelemetryManager_getImmediateQueueSize(pTm) != 0)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
        "Wrong size of the immediate dispatch queue size");
        return;
   }
   if (!CC_TelemetryManager_isImmediateQueueFull(pTm))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
        "Wrong status of the immediate dispatch queue size");
        return;
   }

   // Check that the telemetry manager is now configured
   if (!cc_roc->isObjectConfigured(pTm))
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong configuration status");
        return;
   }

   TestCase_setTestResult((TestCase*)obj,TEST_SUCCESS, "Test Successful");
   return;

}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj){}

TestCaseTelemetryManager_1* TestCaseTelemetryManager_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASETELEMETRYMANAGER_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                     ID_TELEMETRYMANAGER*10+1,
                                                "TestCaseTelemetryManager_1");

    return (TestCaseTelemetryManager_1*)obj;
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
    .name = TYPE_TESTCASETELEMETRYMANAGER_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseTelemetryManager_1),
    .abstract = false,
    .class_size = sizeof(TestCaseTelemetryManager_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseTelemetryManager_1_register(void)
{
    type_register_static(&type_info);
}
