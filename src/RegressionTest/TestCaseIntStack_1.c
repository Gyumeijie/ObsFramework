//
//
// TestCaseIntStack_1.h
//
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../System/CC_IntStack.h"
#include "TestCaseIntStack_1.h"
#include "../Utilities/TestCaseWithEvtCheck.h"

#include <math.h>
#include <float.h>



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
   unsigned int size = 2;
   unsigned int nEvt = TestCaseWithEvtCheck_getNumberOfEvents(obj);
   int pItem1 = (int)1;

   CC_IntStack *pStack = CC_IntStack_new();
   CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pStack);
     
   // Check the value of the class identifier
   if (CC_RootObject_getClassId((CC_RootObject*)pStack) != ID_INTSTACK)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong class identifier");
        return;
   }

   // Check configuration status
   if (cc_roc->isObjectConfigured(pStack))
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong configuration status");
        return;
   }

   // Set the stack size
   CC_IntStack_setStackSize(pStack, size);
   if (CC_IntStack_getStackSize(pStack) != size)
   {     
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong stack size value");
        return;
   }

   // Check configuration status
   if (!cc_roc->isObjectConfigured(pStack))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong configuration status");
        return;
   }

   // Push one item on stack and check correctness
   CC_IntStack_push(pStack, pItem1);
   if (CC_IntStack_getNumberOfItems(pStack) != 1)
   {     
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong number of items on stack");
        return;
   }
   
   if (fabs((float)(CC_IntStack_pop(pStack)-pItem1)) > FLT_EPSILON)
   {     
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong item on stack");
        return;
   } 

   // Check that a pop operation returns pNULL and generates correct event
   if (CC_IntStack_pop(pStack) != pNULL)
   {     
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong item on stack");
        return;
   }
   if (!verifyLatestEvent(obj, nEvt+1, EVT_STACK_EMPTY))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong event");
        return;
   }

   // Perform three push operations and verify event generation
   CC_IntStack_push(pStack, pItem1);
   CC_IntStack_push(pStack, pItem1);
   if (!CC_IntStack_isFull(pStack))
   { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Stack should be full");
        return;
   }
   CC_IntStack_push(pStack, pItem1);
   if (!verifyLatestEvent(obj, nEvt+2, EVT_STACK_FULL))
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong event");
        return;
   }

   // Check that there are only two items on the stack
   if (CC_IntStack_getNumberOfItems(pStack) != 2)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "wrong number of items in stack");
        return;
   }

   // Perform a stack reset and check success
   CC_IntStack_reset(pStack);
   if (CC_IntStack_getNumberOfItems(pStack) != 0)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Reset operation failed");
        return;
   }
   if (!CC_IntStack_isEmpty(pStack))
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Reset operation failed");
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

TestCaseIntStack_1* TestCaseIntStack_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEINTSTACK_1);

    TESTCASEWITHEVTCHECK_GET_CLASS(obj)->post_init((TestCaseWithEvtCheck*)obj,
                                                             ID_INTSTACK*10+1,
                                                        "TestCaseIntStack_1"); 
    return (TestCaseIntStack_1*)obj;
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
    .name = TYPE_TESTCASEINTSTACK_1,
    .parent = TYPE_TESTCASEWITHEVTCHECK,
    .instance_size = sizeof(TestCaseIntStack_1),
    .abstract = false,
    .class_size = sizeof(TestCaseIntStack_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseIntStack_1_register(void)
{
    type_register_static(&type_info);
}
