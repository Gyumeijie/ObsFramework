//
//
// TestCaseFdirCheck_1.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/TestConstants.h"
#include "../FDIR/DC_FdirCheck.h"
#include "../FDIR/DC_DummyRecoveryAction.h"
#include "TestCaseFdirCheck_1.h"



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
	DC_FdirCheck *pFDIR = DC_FdirCheck_new();
	DC_DummyRecoveryAction *pFDI = DC_DummyRecoveryAction_new();
	DC_DummyRecoveryAction *pDRA = DC_DummyRecoveryAction_new();

	// Verify the correctness of the class id
	if (CC_RootObject_getClassId((CC_RootObject*)pFDIR) != ID_FDIRCHECK) {
	     TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, "Wrong class id");
		 return;
	}

	// A newly created FDIR check shall not be configured
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pFDIR);
	if (cc_roc->isObjectConfigured(pFDIR)) {
	    TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Newly created FDIR check is configured");
	    return;
	}

	// Let's set the FDI, verify it is properly set and that the object
	// is not configured
	DC_FdirCheck_setFdiCheck(pFDIR, (PunctualAction*)pFDI);

	if (DC_FdirCheck_getFdiCheck(pFDIR) != (void*)pFDI) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "setFdiCheck() failed");
		return;
	}

	if (cc_roc->isObjectConfigured(pFDIR)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong configuration status");
		return;
	}

	// We now set the recovery action and verify that it is properly
	// set. The object shall now be configured.
	DC_FdirCheck_setRecoveryAction(pFDIR, (RecoveryAction*)pDRA);

	if (DC_FdirCheck_getRecoveryAction(pFDIR) != (void*)pDRA) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "setRecoveryAction() failed");
		return;
	}

	if (!cc_roc->isObjectConfigured(pFDIR)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                 "Wrong configuration status");
		return;
	}

	// The FDI check return code is set to ACTION_CANNOT_EXECUTE. This is what
	// we shall get from a call to pFDIR->execute().
	DC_DummyRecoveryAction_setActionOutcome(pFDI, ACTION_CANNOT_EXECUTE);

	if (PunctualAction_execute((PunctualAction*)pFDIR) != ACTION_CANNOT_EXECUTE) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                 "Wrong FDI check outcome");
		return;
	}

	// Now, the FDI check outcome is set to ACTION_FAILURE. The recovery action
	// shall be executed and its outcome (set to ACTION_CANNOT_EXECUTE) shall
	// be returned to the caller.
	DC_DummyRecoveryAction_setActionOutcome(pFDI, ACTION_FAILURE);
	DC_DummyRecoveryAction_setActionOutcome(pDRA, ACTION_CANNOT_EXECUTE);

	if (PunctualAction_execute((PunctualAction*)pFDIR) != ACTION_CANNOT_EXECUTE) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong recovery action outcome");
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

// the following may be useful if you don't need it, just delete.
// TestCaseFdirCheck_1 *This = TESTCASEFDIRCHECK_1(obj)
static void instance_init(Object *obj){}

TestCaseFdirCheck_1* TestCaseFdirCheck_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEFDIRCHECK_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                    ID_FDIRCHECK*10+1,
                                                    "TestCaseFdirCheck_1");
    return (TestCaseFdirCheck_1*)obj;
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
    .name = TYPE_TESTCASEFDIRCHECK_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseFdirCheck_1),
    .abstract = false,
    .class_size = sizeof(TestCaseFdirCheck_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseFdirCheck_1_register(void)
{
    type_register_static(&type_info);
}
