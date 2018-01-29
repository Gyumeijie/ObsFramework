//
//
// TestCaseDummyTelecommandLoader_1.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/TestConstants.h"
#include "../Telecommand/DC_DummyTelecommand.h"
#include "../Telecommand/DC_DummyTelecommandLoader.h"
#include "../Telecommand/CC_TelecommandManager.h"
#include "../System/DC_DummyObsClock.h"
#include "../Telecommand/TelecommandLoader.h"
#include "TestCaseDummyTelecommandLoader_1.h"



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

   // Create the dummy telecommand loader
   DC_DummyTelecommandLoader *pTcl = DC_DummyTelecommandLoader_new();
   CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pTcl);
   TelecommandLoaderClass *tlc = TELECOMMANDLOADER_GET_CLASS(pTcl);

   // Create and configure a telecommand manager
   CC_TelecommandManager *pTcm = CC_TelecommandManager_new();
   DC_DummyObsClock *pClk = DC_DummyObsClock_new();
   CC_TelecommandManager_setPendingTelecommandListSize(pTcm, 10);
   CC_TelecommandManager_setObsClock(pTcm, (ObsClock*)pClk);
   CC_TelecommandManager_setTelecommandLoader(pTcm, (TelecommandLoader*)pTcl);
   TelecommandLoader_setTelecommandManager((TelecommandLoader*)pTcl, pTcm);

   // Check the value of the class identifier
   if (CC_RootObject_getClassId((CC_RootObject*)pTcl) != ID_DUMMYTELECOMMANDLOADER)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong class identifier");
        return;
   }

   // Check that the telecommand loader is not configured
   if (cc_roc->isObjectConfigured(pTcl))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong configuration status");
        return;
   }

   // Create, configure and load three sample telecommands
   // and verify that the telecommand loader becomes configured
   DC_DummyTelecommand *pSampleTc1 = DC_DummyTelecommand_new();
   DC_DummyTelecommand *pSampleTc2 = DC_DummyTelecommand_new();
   DC_DummyTelecommand *pSampleTc3 = DC_DummyTelecommand_new();
   Telecommand_setTimeTag((Telecommand*)pSampleTc1, 0);
   Telecommand_setTimeTag((Telecommand*)pSampleTc2, 0);
   Telecommand_setTimeTag((Telecommand*)pSampleTc3, 0);
   DC_DummyTelecommandLoader_setSampleTelecommand(pTcl, 0, (Telecommand*)pSampleTc1);
   DC_DummyTelecommandLoader_setSampleTelecommand(pTcl, 1, (Telecommand*)pSampleTc2);
   DC_DummyTelecommandLoader_setSampleTelecommand(pTcl, 2, (Telecommand*)pSampleTc3);
   if (!cc_roc->isObjectConfigured(pTcl))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong configuration status");
        return;
   }

   // Send two activation requests to the telecommand loader and verify
   // increment of allocation counter
   tlc->activate(pTcl);
   tlc->activate(pTcl);
   if (DC_DummyTelecommandLoader_getAllocationCounter(pTcl) != 2)
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong value of allocation counter");
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

TestCaseDummyTelecommandLoader_1* TestCaseDummyTelecommandLoader_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEDUMMYTELECOMMANDLOADER_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                               ID_DUMMYTELECOMMANDLOADER*10+1,
                                          "TestCaseDummyTelecommandLoader_1");

    return (TestCaseDummyTelecommandLoader_1*)obj;
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
    .name = TYPE_TESTCASEDUMMYTELECOMMANDLOADER_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseDummyTelecommandLoader_1),
    .abstract = false,
    .class_size = sizeof(TestCaseDummyTelecommandLoader_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseDummyTelecommandLoader_1_register(void)
{
    type_register_static(&type_info);
}
