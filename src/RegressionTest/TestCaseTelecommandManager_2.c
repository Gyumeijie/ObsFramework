//
//
// TestCaseTelecommandManager_2.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/TestConstants.h"
#include "../Base/CC_RootObject.h"
#include "../Event/DC_EventRepository.h"
#include "../Telecommand/DC_DummyTelecommandLoader.h"
#include "../Telecommand/CC_TelecommandManager.h"
#include "../System/DC_DummyObsClock.h"
#include "../Telecommand/TelecommandLoader.h"
#include "../Telecommand/DC_DummyTelecommand.h"
#include "TestCaseTelecommandManager_2.h"



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

   // Create the telecommand manager
   CC_TelecommandManager *pTcm = CC_TelecommandManager_new();
   CC_TelecommandManagerClass *cc_tmc = CC_TELECOMMANDMANAGER_GET_CLASS(pTcm);
   CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pTcm);

   // Define the identifiers and time tags for the dummy telecommands
   TD_ObsTime tcTt1 = 3;
   TD_ObsTime tcTt2 = 5;
   TD_ObsTime tcTt3 = 0;
   TD_TelecommandId tcId1 = 1;
   TD_TelecommandId tcId2 = 2;
   TD_TelecommandId tcId3 = 3;

   // Create and load an OBS clock
   DC_DummyObsClock *pClk = DC_DummyObsClock_new();
   DC_DummyObsClock_setTime(pClk, tcTt1-1);
   DC_DummyObsClock_setCycle(pClk, 0);
   CC_TelecommandManager_setObsClock(pTcm, (ObsClock*)pClk);

   // Create and configure the three dummy telecommands
   DC_DummyTelecommand *pTc1 = DC_DummyTelecommand_new();
   DC_DummyTelecommand *pTc2 = DC_DummyTelecommand_new();
   DC_DummyTelecommand *pTc3 = DC_DummyTelecommand_new();
   DC_DummyTelecommandClass *dc_dtc = GET_CLASS(TYPE_DC_DUMMYTELECOMMAND);
   TelecommandClass *tc = TELECOMMAND_CLASS(dc_dtc); 
   tc->setTelecommandId(pTc1, tcId1);
   tc->setTelecommandId(pTc2, tcId2);
   tc->setTelecommandId(pTc3, tcId3);
   Telecommand_setTimeTag((Telecommand*)pTc1, tcTt1);
   Telecommand_setTimeTag((Telecommand*)pTc2, tcTt2);
   Telecommand_setTimeTag((Telecommand*)pTc3, tcTt3);

   // Create, configure and load a dummy telecommand loader
   DC_DummyTelecommandLoader *pTcl = DC_DummyTelecommandLoader_new();
   TelecommandLoaderClass *tlc = TELECOMMANDLOADER_GET_CLASS(pTcl);
   DC_DummyTelecommandLoader_setSampleTelecommand(pTcl, 0, (Telecommand*)pTc1);
   DC_DummyTelecommandLoader_setSampleTelecommand(pTcl, 1, (Telecommand*)pTc2);
   DC_DummyTelecommandLoader_setSampleTelecommand(pTcl, 2, (Telecommand*)pTc3);
   CC_TelecommandManager_setTelecommandLoader(pTcm, (TelecommandLoader*)pTcl);
   TelecommandLoader_setTelecommandManager((TelecommandLoader*)pTcl, pTcm);

   // Set the pending telecommand list size
   CC_TelecommandManager_setPendingTelecommandListSize(pTcm, 10);

   // Check that the telecommand manager is configured
   if (!cc_roc->isObjectConfigured(pTcm))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong configuration status");
        return;
   }

   // Activate the telecommand loader three times and check that dummy
   // telecommands were loaded in telecommand manager
   tlc->activate(pTcl);
   tlc->activate(pTcl);
   tlc->activate(pTcl);
   if (CC_TelecommandManager_getPendingTelecommands(pTcm) != 3)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong number of pending telecommands");
        return;
   }

   // Check allocation counter value
   if (DC_DummyTelecommandLoader_getAllocationCounter(pTcl) != 3)
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong allocation counter value");
        return;
   }

   // Activate the telecommand manager and check that the third
   // telecommand is executed
   cc_tmc->activate(pTcm);
   if (DC_DummyTelecommand_getExecutionCounter(pTc3) != 1)
   { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Third telecommand was not executed");
        return;
   }

   // Check number of pending telecommands
   if (CC_TelecommandManager_getPendingTelecommands(pTcm) != 2)
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong number of pending telecommands");
        return;
   }

   // Check generation of event to record telecommand successful execution and unloading
   DC_EventRepository *pRep = CC_RootObject_getEventRepository();
   DC_EventRepository_latest(pRep);
   if ((DC_EventRepository_getEventType(pRep) != EVT_TC_EXEC_SUCC))
   { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong unload event");
        return;
   }

   // Activate telecommand manager and advance dummy time to the point
   // where the first telecommand should be executed and check execution
   cc_tmc->activate(pTcm);
   cc_tmc->activate(pTcm);
   DC_DummyObsClock_setTime(pClk, tcTt1+1);
   DC_DummyObsClock_setCycle(pClk, 0);
   cc_tmc->activate(pTcm);
   if (DC_DummyTelecommand_getExecutionCounter(pTc1) != 1)
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "First telecommand was not executed");
        return;
   }

   // Check number of pending telecommands
   if (CC_TelecommandManager_getPendingTelecommands(pTcm) != 1)
   { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong number of pending telecommands");
        return;
   }

   // Activate telecommand manager and advance dummy time to the point
   // where the second telecommand should be executed and check execution
   cc_tmc->activate(pTcm);
   cc_tmc->activate(pTcm);
   DC_DummyObsClock_setTime(pClk, tcTt2+1);
   DC_DummyObsClock_setCycle(pClk, 0);
   cc_tmc->activate(pTcm);
   if (DC_DummyTelecommand_getExecutionCounter(pTc2) != 1)
   { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Second telecommand was not executed");
        return;
   }

   // Check number of pending telecommands
   if (CC_TelecommandManager_getPendingTelecommands(pTcm) != 0)
   { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong number of pending telecommands");
        return;
   }

   // Check allocation counter value
   if (DC_DummyTelecommandLoader_getAllocationCounter(pTcl) != 0)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong allocation counter value");
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

TestCaseTelecommandManager_2* TestCaseTelecommandManager_2_new(void)
{
    Object *obj = object_new(TYPE_TESTCASETELECOMMANDMANAGER_2);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                   ID_TELECOMMANDMANAGER*10+2,
                                              "TestCaseTelecommandManager_2");

    return (TestCaseTelecommandManager_2*)obj;
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
    .name = TYPE_TESTCASETELECOMMANDMANAGER_2,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseTelecommandManager_2),
    .abstract = false,
    .class_size = sizeof(TestCaseTelecommandManager_2Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseTelecommandManager_2_register(void)
{
    type_register_static(&type_info);
}
