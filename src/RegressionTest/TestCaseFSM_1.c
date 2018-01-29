//
//
// TestCaseFSM_1.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "../FSM/CC_FSM.h"
#include "../FSM/DC_DummyFsmState.h"
#include "../Utilities/TestCaseWithEvtCheck.h"
#include "TestCaseFSM_1.h"



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

   CC_FSM *pFsm = CC_FSM_new();
   unsigned int nEvt = TestCaseWithEvtCheck_getNumberOfEvents(obj);
   CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pFsm);

   // Check the correctness of the class identifier
   if ((CC_RootObject_getClassId((CC_RootObject*)pFsm) != ID_FSM)) {  
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong class identifier for the FSM class");
	   return;
	}

   // FSM should not be configured upon creation
   if ((cc_roc->isObjectConfigured(pFsm) == CONFIGURED)) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
        "Wrong event repository configuration status upon repository creation");
		return;
	}

   // Set the number of states and check correctness
   CC_FSM_setNumberOfStates(pFsm, 4);
   if ((CC_FSM_getNumberOfStates(pFsm) != 4)) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong number of FSM states");
		return;
	}

   DC_DummyFsmState *pState[4];
   TD_FsmStateIndex i;
   const int nStates = CC_FSM_getNumberOfStates(pFsm);

   // Load dummy FsmStates and check that the load operation is correctly executed
   for (i=0; i<nStates; i++) {
       pState[i] = DC_DummyFsmState_new();
   }
   for (i=0; i<nStates; i++) {
       CC_FSM_setState(pFsm, i, (FsmState*)pState[i]);
   }
   for (i=0; i<nStates; i++) {
      if (CC_FSM_getState(pFsm, i) != (FsmState*)pState[i]) {	
         TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                 "Wrong loaded state is reported");
	   	 return;
	  }
   }

   // Attempt non-nominal state load
   if (TestCase_isNonNominalCheckAllowed(obj)) {
      CC_FSM_setState(pFsm, 5, (FsmState*)pState[0]);
      if (!verifyLatestEvent(obj, nEvt+1, EVT_ILLEGAL_FS)) return;
   }

   // Reset the FSM
   CC_FSM_reset(pFsm);

   // Check correctness of default state
   if (CC_FSM_getCurrentState(pFsm) != 0) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong default state");
		return;
	}

   // Check that all state transitions are enabled
   for (i=0; i<nStates; i++) {
      if (!CC_FSM_isTransitionEnabledToState(pFsm, i)) {	
         TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "All state transitions should be enabled");
	   	 return;
	   }
   }

   // Unload one state and check that the object is not configured
   if (TestCase_isNonNominalCheckAllowed(obj)) {
        CC_FSM_setState(pFsm, 0,pNULL);
        if ((cc_roc->isObjectConfigured(pFsm) == CONFIGURED)) {	
             TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                     "Wrong FSM configuration status");
		     return;
        }
   }

   // Reload state and check that FSM object is configured
    CC_FSM_setState(pFsm, 0, (FsmState*)pState[0]);
    if ((cc_roc->isObjectConfigured(pFsm) == NOT_CONFIGURED)) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
        "Wrong FSM configuration status after configuration was completed");
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

TestCaseFSM_1* TestCaseFSM_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEFSM_1);

    TESTCASEWITHEVTCHECK_GET_CLASS(obj)->post_init((TestCaseWithEvtCheck*)obj,
	                                                ID_FSM*10+1,
                                                    "TestCaseFSM_1"); 
    return (TestCaseFSM_1*)obj;
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
    .name = TYPE_TESTCASEFSM_1,
    .parent = TYPE_TESTCASEWITHEVTCHECK,
    .instance_size = sizeof(TestCaseFSM_1),
    .abstract = false,
    .class_size = sizeof(TestCaseFSM_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseFSM_1_register(void)
{
    type_register_static(&type_info);
}
