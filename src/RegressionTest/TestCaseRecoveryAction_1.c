//
//
// TestCaseRecoveryAction_1.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/TestConstants.h"
#include "../FDIR/DC_NullRecoveryAction.h"
#include "../FDIR/DC_DummyRecoveryAction.h"
#include "TestCaseRecoveryAction_1.h"



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
	DC_NullRecoveryAction  *dc_nra = DC_NullRecoveryAction_new();
	DC_DummyRecoveryAction *dc_dra = DC_DummyRecoveryAction_new();

	// Verify the correctness of the class ids
	if (CC_RootObject_getClassId((CC_RootObject*)dc_nra) != ID_NULLRECOVERYACTION) {
		 TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, "Wrong class id");
		 return;
	}

	if (CC_RootObject_getClassId((CC_RootObject*)dc_dra) != ID_DUMMYRECOVERYACTION) {
		 TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, "Wrong class id");
		 return;
	}

	// Initially there shall be no next recovery action
	if (RecoveryAction_getNextRecoveryAction((RecoveryAction*)dc_dra)) {
		 TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Initialization failure");
		 return;
	}

	// The execution flag shall be true: calling execute() shall return
	// ACTION_SUCCESS.
	if (PunctualAction_execute((PunctualAction*)dc_dra) != ACTION_SUCCESS) {
		 TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                 "Execution flag wrongly set");
		 return;
	}

	// We set the execution flag to false. A call to execute()
	// shall now return ACTION_CANNOT_EXECUTE.
	DC_DummyRecoveryAction_setExecutionFlag(dc_dra, false);
	if (PunctualAction_execute((PunctualAction*)dc_dra) != ACTION_CANNOT_EXECUTE) {
		 TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                 "setExecutionFlag() failed");
		 return;
	}

	// Invoking dc_nra->execute() shall return ACTION_SUCCESS
	if (PunctualAction_execute((PunctualAction*)dc_nra) != ACTION_SUCCESS) {
		 TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                 "Execution flag wrongly set");
		 return;
	}

	// We now set dc_dra as dc_nra's next recovery action and verify
	// it worked.
	RecoveryAction_setNextRecoveryAction((RecoveryAction*)dc_nra,
                                         (RecoveryAction*)dc_dra);

	if (RecoveryAction_getNextRecoveryAction((void*)dc_nra) != (void*)dc_dra) {
	    TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                 "setNextRecoveryAction() failed");
		 return;
	}

	// We set dc_dra's outcome to ACTION_FAILURE and its execution
	// flag to true.
	DC_DummyRecoveryAction_setActionOutcome(dc_dra, ACTION_FAILURE);
	DC_DummyRecoveryAction_setExecutionFlag(dc_dra, true);

	// Calling dc_nra->execute() shall now return dc_dra's outcome
	// (that is ACTION_FAILURE).
	if (PunctualAction_execute((PunctualAction*)dc_nra) != ACTION_FAILURE) {
		 TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, "Wrong outcome");
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

TestCaseRecoveryAction_1* TestCaseRecoveryAction_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASERECOVERYACTION_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                    ID_DUMMYRECOVERYACTION*10+1,
						                            "TestCaseRecoveryAction_1");

    return (TestCaseRecoveryAction_1*)obj;
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
    .name = TYPE_TESTCASERECOVERYACTION_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseRecoveryAction_1),
    .abstract = false,
    .class_size = sizeof(TestCaseRecoveryAction_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseRecoveryAction_1_register(void)
{
    type_register_static(&type_info);
}
