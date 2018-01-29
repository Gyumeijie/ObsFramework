//
//
// TestCaseTelecommandManager_3.c
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
#include "TestCaseTelecommandManager_3.h"



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

   // Retrieve the event repository
   DC_EventRepository *pRep = CC_RootObject_getEventRepository();

   // Create the telecommand manager
   CC_TelecommandManager *pTcm = CC_TelecommandManager_new();
   CC_TelecommandManagerClass *cc_tmc = CC_TELECOMMANDMANAGER_GET_CLASS(pTcm);
   CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pTcm);

   // Define the identifiers and time tags for the dummy telecommands
   TD_ObsTime tcTt1 = 0;
   TD_ObsTime tcTt2 = 0;
   TD_ObsTime tcTt3 = 0;
   TD_TelecommandId tcId1 = 1;
   TD_TelecommandId tcId2 = 2;
   TD_TelecommandId tcId3 = 3;

   // Create and load an OBS clock
   DC_DummyObsClock *pClk = DC_DummyObsClock_new();
   DC_DummyObsClock_setTime(pClk, tcTt1+1);
   DC_DummyObsClock_setCycle(pClk, 0);
   CC_TelecommandManager_setObsClock(pTcm, (ObsClock*)pClk);

   // Create and configure the dummy telecommands
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

   DC_DummyTelecommand_setExecutionCheckValue(pTc1, TC_CANNOT_EXECUTE);
   DC_DummyTelecommand_setValidityCheckValue(pTc2, NOT_VALID);

   // Create, configure and load a dummy telecommand loader
   DC_DummyTelecommandLoader *pTcl = DC_DummyTelecommandLoader_new();
   TelecommandLoaderClass *tlc = TELECOMMANDLOADER_GET_CLASS(pTcl);
   DC_DummyTelecommandLoader_setSampleTelecommand(pTcl, 0, (Telecommand*)pTc1);
   DC_DummyTelecommandLoader_setSampleTelecommand(pTcl, 1, (Telecommand*)pTc2);
   DC_DummyTelecommandLoader_setSampleTelecommand(pTcl, 2, (Telecommand*)pTc3);
   CC_TelecommandManager_setTelecommandLoader(pTcm, (TelecommandLoader*)pTcl);
   TelecommandLoader_setTelecommandManager((TelecommandLoader*)pTcl, pTcm);

   // Set the pending telecommand list size
   CC_TelecommandManager_setPendingTelecommandListSize(pTcm, 2);

   // Check that the telecommand manager is configured
   if (!cc_roc->isObjectConfigured(pTcm))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong configuration status");
        return;
   }

   // Activate the telecommand loader twice and check that the
   // second telecommand is rejected because its validity check fails
   tlc->activate(pTcl);
   tlc->activate(pTcl);
   DC_EventRepository_latest(pRep);
   if ((DC_EventRepository_getEventType(pRep) != EVT_TC_NOT_VALID))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong event type");
        return;
   }

   // Replace the second telecommand in the telecommand loader,
   // activate the telecommand loader twice and check that the
   // last load attempt is rejected because the pending telecommand
   // list is full
   DC_DummyTelecommandLoader_setSampleTelecommand(pTcl, 1, (Telecommand*)pTc3);
   tlc->activate(pTcl); // load TC3 (second entry in dummy TC Loader
   tlc->activate(pTcl); // load TC3 (third entry in dummy TC Loader
   DC_EventRepository_latest(pRep);
   if ((DC_EventRepository_getEventType(pRep) != EVT_TC_LIST_FULL))
   { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong event type");
        return;
   }

   // Activate the telecommand manager and check that the second
   // telecommand is executed but the first
   // is not executed because its execution check fails
   cc_tmc->activate(pTcm);
   if (DC_DummyTelecommand_getExecutionCounter(pTc3) != 1)
   { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Third telecommand was not executed");
        return;
   }
   if (DC_DummyTelecommand_getExecutionCounter(pTc1) != 0)
   { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "First telecommand was executed");
        return;
   }

   // Check generation of event to record telecommand unloading
   DC_EventRepository_latest(pRep);      // TC 3 punctual action was executed
   DC_EventRepository_previous(pRep);    // TC 3 was successfully executed
   DC_EventRepository_previous(pRep);    // TC 1 execution check failed
   if ((DC_EventRepository_getEventType(pRep) != EVT_TC_EXEC_CHECK_FAIL))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong event type");
        return;
   }

   // Check allocation counter value
   if (DC_DummyTelecommandLoader_getAllocationCounter(pTcl) != 0)
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong allocation counter value");
        return;
   }

   // Activate the telecommand loader three times and verify that two
   // telecommands are loaded
   tlc->activate(pTcl);
   tlc->activate(pTcl);
   tlc->activate(pTcl);
   if (CC_TelecommandManager_getPendingTelecommands(pTcm) != 2)
   { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong number of pending telecommands");
        return;
   }
   if (DC_DummyTelecommandLoader_getAllocationCounter(pTcl) != 2)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong allocation counter value");
        return;
   }

   // Reset telecommand manager and verify number of pending telecommands
   unsigned int nEvt = DC_EventRepository_getCounter(pRep);
   CC_TelecommandManager_reset(pTcm);
   if (CC_TelecommandManager_getPendingTelecommands(pTcm) != 0)
   { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong number of pending telecommands");
        return;
   }

   // Verify events generated as a result of the reset
   if ((DC_EventRepository_getCounter(pRep) != nEvt+2))
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong number of events");
        return;
   }
   DC_EventRepository_latest(pRep);
   if ((DC_EventRepository_getEventType(pRep) != EVT_TC_ABORTED) )
   { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong event type");
        return;
   }
   DC_EventRepository_previous(pRep);
   if ((DC_EventRepository_getEventType(pRep) != EVT_TC_ABORTED) )
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong event type");
        return;
   }

   // Check allocation counter value
   if (DC_DummyTelecommandLoader_getAllocationCounter(pTcl) != 0)
   { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong allocation counter value");
        return;
   }

   // Activate the telecommand loader three times and verify that two
   // telecommands are loaded
   tlc->activate(pTcl);
   tlc->activate(pTcl);
   tlc->activate(pTcl);
   if (CC_TelecommandManager_getPendingTelecommands(pTcm) != 2)
   { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong number of pending telecommands");
        return;
   }
   if (DC_DummyTelecommandLoader_getAllocationCounter(pTcl) != 2)
   { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong allocation counter value");
        return;
   }

   // Abort the first telecommand
   nEvt = DC_EventRepository_getCounter(pRep);
   CC_TelecommandManager_abort(pTcm, tc->getTelecommandId(pTc1));
   if (CC_TelecommandManager_getPendingTelecommands(pTcm) != 1)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong number of pending telecommands");
        return;
   }
   if (DC_DummyTelecommandLoader_getAllocationCounter(pTcl) != 1)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong allocation counter value");
        return;
   }

   // Check abort event
   if ((DC_EventRepository_getCounter(pRep) != nEvt+1) )
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong number of events");
        return;
   }
   DC_EventRepository_latest(pRep);
   if ((DC_EventRepository_getEventType(pRep) != EVT_TC_ABORTED) )
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong event type");
        return;
   }

   // Abort the last telecommand
   cc_tmc->abort(pTcm, (Telecommand*)pTc3);
   if (CC_TelecommandManager_getPendingTelecommands(pTcm) != 0)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong number of pending telecommands");
        return;
   }
   if (DC_DummyTelecommandLoader_getAllocationCounter(pTcl) != 0)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong allocation counter value");
        return;
   }

   // Check abort event
   if ((DC_EventRepository_getCounter(pRep) != nEvt+2) )
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong number of events");
        return;
   }
   DC_EventRepository_latest(pRep);
   if ((DC_EventRepository_getEventType(pRep) != EVT_TC_ABORTED) )
   { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong event type");
        return;
   }

   TestCase_setTestResult((TestCase*)obj,TEST_SUCCESS,"Test Successful");
   return;

}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj){}

TestCaseTelecommandManager_3* TestCaseTelecommandManager_3_new(void)
{
    Object *obj = object_new(TYPE_TESTCASETELECOMMANDMANAGER_3);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                   ID_TELECOMMANDMANAGER*10+3,
                                              "TestCaseTelecommandManager_3"); 

    return (TestCaseTelecommandManager_3*)obj;
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
    .name = TYPE_TESTCASETELECOMMANDMANAGER_3,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseTelecommandManager_3),
    .abstract = false,
    .class_size = sizeof(TestCaseTelecommandManager_3Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseTelecommandManager_3_register(void)
{
    type_register_static(&type_info);
}
