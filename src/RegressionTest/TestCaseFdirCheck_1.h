//
//
// TestCaseFdirCheck_1.h
//


#ifndef TESTCASEFDIRCHECK_1_H
#define TESTCASEFDIRCHECK_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Verify the services of the <code>DC_FdirCheck</code> object. One object
 * (<code>pFDIR</code>) is created and the following tests are performed upon it:<ol>
 * <li>The correctness of both class ids is verified.</li>
 * <li>It is verified that a newly created object is not configured.</li>
 * <li>A previously created <code>DC_DummyRecoveryAction</code> (<code>pFDI</code>) is
 * attached to the object as its FDI check. It is verified that the pointer
 * is correctly set and that the object is not yet configured.</li>
 * <li>A previously created <code>DC_DummyRecoveryAction</code> (<code>pDRA</code>) is
 * attached to the object as its recovery action. It is verified that the
 * pointer is correctly set and that the object is configured.</li>
 * <li>The outcome of the FDI check is set to <code>ACTION_CANNOT_EXECUTE</code>,
 * <code>pFDIR->execute(void)</code> is invoked and it is verified that its return code
 * is <code>ACTION_CANNOT_EXECUTE</code>.</li>
 * <li>Now the FDI check outcome is set to <code>ACTION_FAILURE</code> and the recovery
 * action's to <code>ACTION_CANNOT_EXECUTE</code>. It is tested that
 * <code>pFDIR->execute(void)</code> invokes the recovery action's <code>execute(void)</code>
 * method by verifying that its return code is indeed <code>ACTION_CANNOT_EXECUTE</code>.</li>
 * </ol>
 * @see DC_FdirCheck
 * @see DC_DummyRecoveryAction
 * @author Roberto Totaro
 * @version 1.0
 */
#define TYPE_TESTCASEFDIRCHECK_1 "testcasefdircheck_1"

void TestCaseFdirCheck_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseFdirCheck_1 {
    TestCaseGenericSetUp parent;
} TestCaseFdirCheck_1;


typedef struct TestCaseFdirCheck_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseFdirCheck_1Class;


#define TESTCASEFDIRCHECK_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseFdirCheck_1Class, obj, TYPE_TESTCASEFDIRCHECK_1)

#define TESTCASEFDIRCHECK_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseFdirCheck_1Class, klass, TYPE_TESTCASEFDIRCHECK_1)

#define TESTCASEFDIRCHECK_1(obj) \
        OBJECT_CHECK(TestCaseFdirCheck_1, obj, TYPE_TESTCASEFDIRCHECK_1)


TestCaseFdirCheck_1* TestCaseFdirCheck_1_new(void);

#endif
