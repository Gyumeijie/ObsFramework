//
//
// TestCaseDummyPUSTelecommand_1.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/TestConstants.h"
#include "../Telecommand/DC_DummyPUSTelecommand.h"
#include "TestCaseDummyPUSTelecommand_1.h"



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
   DC_DummyPUSTelecommand *pTc = DC_DummyPUSTelecommand_new();
   CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pTc);
   TelecommandClass *tc = TELECOMMAND_GET_CLASS(pTc);

   // Check the value of the class identifier
   if (CC_RootObject_getClassId((CC_RootObject*)pTc) != ID_DUMMYPUSTELECOMMAND)
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

   // Set and read back the TC attributes
   if (tc->getTelecommandId(pTc) != TEST_TC_ID)
   {    TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong TC ID value");
        return;
   }
   if (tc->getType(pTc) != TEST_TC_TYPE)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong TC type value");
        return;
   }
   if (tc->getSubType(pTc) != TEST_TC_SUBTYPE)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong TC subtype value");
        return;
   }
   if (tc->getSource(pTc) != TEST_TC_SOURCE)
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong TC source value");
        return;
   }
   Telecommand_setTimeTag((Telecommand*)pTc, 5);
   if (Telecommand_getTimeTag((Telecommand*)pTc) != 5)
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong time tag value");
        return;
   }
   if (tc->getAcknowledgeLevel(pTc) != 0)
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong TC acknowledge level");
        return;
   }
   if (PUSTelecommand_getPacketId() != (2048 + 4096 + TEST_TC_APID))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong packet ID");
        return;
   }

   // Check that the telecommand becomes configured
   if (!cc_roc->isObjectConfigured(pTc))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong configuration status");
        return;
   }

   // Update acknowledge level and check success
   tc->setAcknowledgeLevel(pTc, 10);
   if (PUSTelecommand_isAcceptanceAckRequired((PUSTelecommand*)pTc))
   {   
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong acceptance acknowledge value");
        return;
   }
   if (!PUSTelecommand_isStartAckRequired((PUSTelecommand*)pTc))
   {   
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong start acknowledge value");
        return;
   }
   if (PUSTelecommand_isProgressAckRequired((PUSTelecommand*)pTc))
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong progress acknowledge value");
        return;
   }
   if (!PUSTelecommand_isCompletionAckRequired((PUSTelecommand*)pTc))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong completion acknowledge value");
        return;
   }

   // Make two execute requests and check increment of execution counter
   PunctualAction_execute((PunctualAction*)pTc);
   PunctualAction_execute((PunctualAction*)pTc);
   if (DC_DummyPUSTelecommand_getExecutionCounter(pTc) != 2)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong execution check counter value");
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

TestCaseDummyPUSTelecommand_1* TestCaseDummyPUSTelecommand_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEDUMMYPUSTELECOMMAND_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                  ID_DUMMYPUSTELECOMMAND*10+1,
                                             "TestCaseDummyPUSTelecommand_1"); 

    return (TestCaseDummyPUSTelecommand_1*)obj;
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
    .name = TYPE_TESTCASEDUMMYPUSTELECOMMAND_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseDummyPUSTelecommand_1),
    .abstract = false,
    .class_size = sizeof(TestCaseDummyPUSTelecommand_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseDummyPUSTelecommand_1_register(void)
{
    type_register_static(&type_info);
}
