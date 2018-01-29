//
//
// TestCaseFsmEvent_1.c
//
//
// Change Record:

#include "TestCaseFsmEvent_1.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../FSM/DC_FsmEvent.h"
#include "../FSM/CC_FSM.h"
#include "../FSM/DC_DummyFsmState.h"



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
   DC_FsmEvent *pFsmEvt = DC_FsmEvent_new();
   CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pFsmEvt);

   // Verify correctness of class ID
   if (CC_RootObject_getClassId((CC_RootObject*)pFsmEvt) != ID_FSMEVENT) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, "Wrong class ID");
		return;
	}

   // FsmEvent object should not be configured
   if ((cc_roc->isObjectConfigured(pFsmEvt) != NOT_CONFIGURED)) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
        "FsmEvent component should not be configured at creation");
		return;
	}

   // Load a target FsmState and check correctness
   TD_FsmStateIndex state = 1;
   DC_FsmEvent_setTargetState(pFsmEvt, state);
   if (DC_FsmEvent_getTargetState(pFsmEvt) != state) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Incorrect loading of target state");
		return;
	}

   // Create and configure an FSM
   CC_FSM *pFsm = CC_FSM_new();
   CC_FSM_setNumberOfStates(pFsm, 4);

   DC_DummyFsmState *pState[4];
   const int nStates = CC_FSM_getNumberOfStates(pFsm);
   for (TD_FsmStateIndex i=0; i<nStates; i++) {
      pState[i] = DC_DummyFsmState_new();
   }
   for (TD_FsmStateIndex i=0; i<nStates; i++) {
      CC_FSM_setState(pFsm, i, (FsmState*)pState[i]);
   }

   CC_FSM_reset(pFsm);

   // Load the newly created FSM as the "target FSM" and check correctness
   DC_FsmEvent_setTargetFsm(pFsmEvt, pFsm);
   if (DC_FsmEvent_getTargetFsm(pFsmEvt) != pFsm) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Incorrect loading of target FSM");
		return;
	}

   // FsmEvent object should now be configured
   if ((cc_roc->isObjectConfigured(pFsmEvt) != CONFIGURED)) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "FsmEvent component should be configured");
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

TestCaseFsmEvent_1* TestCaseFsmEvent_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEFSMEVENT_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                    ID_FSMEVENT*10+1,
                                                    "TestCaseFsmEvent_1"); 
    return (TestCaseFsmEvent_1*)obj;
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
    .name = TYPE_TESTCASEFSMEVENT_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseFsmEvent_1),
    .abstract = false,
    .class_size = sizeof(TestCaseFsmEvent_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseFsmEvent_1_register(void)
{
    type_register_static(&type_info);
}
