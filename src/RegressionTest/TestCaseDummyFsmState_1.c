//
//
// TestCaseDummyFsmState_1.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../FSM/FsmState.h"
#include "../FSM/DC_DummyFsmState.h"
#include "TestCaseDummyFsmState_1.h"



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

   DC_DummyFsmState *pFsmState = DC_DummyFsmState_new();
   FsmStateClass *fsc = FSMSTATE_GET_CLASS(pFsmState);

   // Verify correctness of class ID
   if (CC_RootObject_getClassId((CC_RootObject*)pFsmState) != ID_DUMMYFSMSTATE) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong class ID");
		return;
	}

   // Check correct value of "next state" at creation
	if (FsmState_getNextState((FsmState*)pFsmState) != pNULL) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Incorrect initial value of next state");
		return;
	}

   // Load a "next state" and check correctness
   DC_DummyFsmState *pNextState = DC_DummyFsmState_new();
   FsmState_setNextState((FsmState*)pFsmState, (FsmState*)pNextState);
   if (FsmState_getNextState((FsmState*)pFsmState) != (FsmState*)pNextState) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Incorrect loading of next state");
		return;
	}

   // Check correctness of exit, termination and initialization checks
   if ((fsc->canExit(pFsmState) != true) ||
       (fsc->isFinished(pFsmState) != false) ||
       (fsc->canEnter(pFsmState) != true)) {	
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Incorrect check return values at creation");
		return;
	}

   // Perform actions
   fsc->doInit(pFsmState);
   fsc->doContinue(pFsmState);
   fsc->doExit(pFsmState);

   // Check correctness of exit, termination and initialization checks
   if ((fsc->canExit(pFsmState) != true) ||
       (fsc->isFinished(pFsmState) != false) ||
       (fsc->canEnter(pFsmState) != true)) {	
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Incorrect check return values after actions");
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

TestCaseDummyFsmState_1* TestCaseDummyFsmState_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEDUMMYFSMSTATE_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                    ID_DUMMYFSMSTATE*10+1,
                                                    "TestCaseDummyFsmState_1"); 

    return (TestCaseDummyFsmState_1*)obj;
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
    .name = TYPE_TESTCASEDUMMYFSMSTATE_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseDummyFsmState_1),
    .abstract = false,
    .class_size = sizeof(TestCaseDummyFsmState_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseDummyFsmState_1_register(void)
{
    type_register_static(&type_info);
}
