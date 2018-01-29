//
//
// TestCaseTelecommandManager_1.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/TestConstants.h"
#include "../Telecommand/DC_DummyTelecommandLoader.h"
#include "../Telecommand/CC_TelecommandManager.h"
#include "../System/DC_DummyObsClock.h"
#include "../Telecommand/TelecommandLoader.h"
#include "TestCaseTelecommandManager_1.h"



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
   CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pTcm);

   // Check the value of the class identifier
   if (CC_RootObject_getClassId((CC_RootObject*)pTcm) != ID_TELECOMMANDMANAGER)
   { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong class identifier");
        return;
   }

   // Check that the telecommand loader is not configured
   if (cc_roc->isObjectConfigured(pTcm))
   { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong configuration status");
        return;
   }

   // Create and load an OBS clock and verify that it is loaded
   DC_DummyObsClock *pClk = DC_DummyObsClock_new();
   CC_TelecommandManager_setObsClock(pTcm, (ObsClock*)pClk);
   if (CC_TelecommandManager_getObsClock(pTcm) != (ObsClock*)pClk)
   { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong OBS clock");
        return;
   }

   // Create and load a telecommand loader and verify that it is loaded
   DC_DummyTelecommandLoader *pTcl = DC_DummyTelecommandLoader_new();
   CC_TelecommandManager_setTelecommandLoader(pTcm, (TelecommandLoader*)pTcl);
   if (CC_TelecommandManager_getTelecommandLoader(pTcm) != (TelecommandLoader*)pTcl)
   { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong telecommand loader");
        return;
   }

   // Set the pending telecommand list size and verify correctness
   CC_TelecommandManager_setPendingTelecommandListSize(pTcm, 10);
   if (CC_TelecommandManager_getPendingTelecommandListSize(pTcm) != 10)
   { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong pending telecommand list size");
        return;
   }

   // Check that the telecommand manager is configured
   if (!cc_roc->isObjectConfigured(pTcm))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong configuration status");
        return;
   }

   // Check the number of pending telecommands
   if (CC_TelecommandManager_getPendingTelecommands(pTcm) != 0)
   { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong number of pending telecommands");
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

TestCaseTelecommandManager_1* TestCaseTelecommandManager_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASETELECOMMANDMANAGER_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                   ID_TELECOMMANDMANAGER*10+1,
                                              "TestCaseTelecommandManager_1"); 

    return (TestCaseTelecommandManager_1*)obj;
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
    .name = TYPE_TESTCASETELECOMMANDMANAGER_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseTelecommandManager_1),
    .abstract = false,
    .class_size = sizeof(TestCaseTelecommandManager_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseTelecommandManager_1_register(void)
{
    type_register_static(&type_info);
}
