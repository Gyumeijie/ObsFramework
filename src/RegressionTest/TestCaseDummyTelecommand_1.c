//
//
// TestCaseDummyTelecommand_1.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/TestConstants.h"
#include "../Telecommand/DC_DummyTelecommand.h"
#include "TestCaseDummyTelecommand_1.h"



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

   // Create the dummy telecommand components
   DC_DummyTelecommand *pTc = DC_DummyTelecommand_new();
   TelecommandClass *tc = TELECOMMAND_GET_CLASS(pTc);
   CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pTc);

   // Check the value of the class identifier
   if (CC_RootObject_getClassId((CC_RootObject*)pTc) != ID_DUMMYTELECOMMAND)
   { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong class identifier");
        return;
   }

   // Check configuration status
   if (cc_roc->isObjectConfigured(pTc))
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong configuration status");
        return;
   }

   // Check default values of TC attributes
   if (tc->getTelecommandId(pTc) != CC_RootObject_getInstanceId((CC_RootObject*)pTc))
   {   
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong TC ID value");
        return;
   }
   if (tc->getType(pTc) != (CC_RootObject_getClassId((CC_RootObject*)pTc)%256))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong TC type value");
        return;
   }
   if (tc->getSubType(pTc) != 0)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong TC subtype value");
        return;
   }
   if (tc->getSource(pTc) != 0)
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong telecommand source attribute");
        return;
   }
   if (tc->getAcknowledgeLevel(pTc) != 0)
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong TC acknowledge value");
        return;
   }
   if (Telecommand_isInUse((Telecommand*)pTc) != false)
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong initial value of InUse attribute");
        return;
   }

   // Set the telecommand time tag and verify that
   // the telecommand becomes configured
   TD_ObsTime tt = 20;
   Telecommand_setTimeTag((Telecommand*)pTc, tt);
   if (Telecommand_getTimeTag((Telecommand*)pTc) != (TD_ObsTime)tt)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong time tag value");
        return;
   }
   if (!cc_roc->isObjectConfigured(pTc))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong configuration status");
        return;
   }

   // Change the value of the "in use" attribute and check success
   Telecommand_setInUse((Telecommand*)pTc, true);
   if (Telecommand_isInUse((Telecommand*)pTc) != true)
   {   
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong value of InUse attribute");
        return;
   }

   // Check the initial value of the execution counter
   if (DC_DummyTelecommand_getExecutionCounter(pTc) != 0)
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong initial value of execution counter");
        return;
   }

   // Check the number of raw data
   if (tc->getNumberOfRawData(pTc) != 0)
   { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong number of raw data");
        return;
   }

   // Check the execution check return value
   if (!tc->canExecute(pTc))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong execution check return value");
        return;
   }

   // Check the validity check return value
   if (!tc->isValid(pTc))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong validity check return value");
        return;
   }

   // Make two execute requests and check increment of execution counter
   PunctualAction_execute((PunctualAction*)pTc);
   PunctualAction_execute((PunctualAction*)pTc);
   if (DC_DummyTelecommand_getExecutionCounter(pTc) != 2)
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong execution check counter value");
        return;
   }

   // Change the execution check return value and check that the change is
   // implemented
   DC_DummyTelecommand_setExecutionCheckValue(pTc, TC_CANNOT_EXECUTE);
   if (tc->canExecute(pTc))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong execution check return value");
        return;
   }

   // Change the validity check return value and check that the change is
   // implemented
   DC_DummyTelecommand_setValidityCheckValue(pTc, NOT_VALID);
   if (tc->isValid(pTc))
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong validity check return value");
        return;
   }

   // Change the execution check code and check that the change is
   // implemented
   DC_DummyTelecommand_setExecutionCheckCode(pTc, 1);
   if (tc->getExecutionCheckCode(pTc) != 1)
   {   
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong execution check code");
        return;
   }

   // Change the validity check code and check that the change is
   // implemented
   DC_DummyTelecommand_setValidityCheckCode(pTc, 1);
   if (tc->getValidityCheckCode(pTc) != 1)
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong validity check code");
        return;
   }

   // Dummy method calls
   tc->setAcknowledgeLevel(pTc, 0);
   tc->setTelecommandId(pTc, 0);
   tc->setSource(pTc, 0);
   tc->setType(pTc, 0);
   tc->setSubType(pTc, 0);

   TestCase_setTestResult((TestCase*)obj, TEST_SUCCESS, "Test Successful");
   return;

}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj){}

TestCaseDummyTelecommand_1* TestCaseDummyTelecommand_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEDUMMYTELECOMMAND_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                     ID_DUMMYTELECOMMAND*10+1,
                                                "TestCaseDummyTelecommand_1");
    return (TestCaseDummyTelecommand_1*)obj;
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
    .name = TYPE_TESTCASEDUMMYTELECOMMAND_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseDummyTelecommand_1),
    .abstract = false,
    .class_size = sizeof(TestCaseDummyTelecommand_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseDummyTelecommand_1_register(void)
{
    type_register_static(&type_info);
}
