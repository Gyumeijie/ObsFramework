//
//
// TestCaseRecoveryAction_1.h
//


#ifndef TESTCASERECOVERYACTION_1_H
#define TESTCASERECOVERYACTION_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Verify the services of recovery actions. One <code>DC_NullRecoveryAction</code> object
 * (from now on referred to as "pNRA") and one <code>DC_DummyRecoveryAction</code>
 * object(from now on referred to as "pDRA") are created and the following
 * tests are performed upon them:<ol>
 * <li>The correctness of both class ids is verified.</li>
 * <li>It is verified that <code>pDRA->getNextRecoveryAction(void)</code>
 * returns <code>NULL</code>.</li>
 * <li>It is verified that a call to <code>pDRA->execute(void)</code> returns
 * <code>ACTION_SUCCESS</code>.</li>
 * <li><code>pDRA</code>'s execution flag is set to <code>false</code> and
 * <code>pDRA->execute(void)</code> is invoked. It is verified that it returns
 * <code>ACTION_CANNOT_EXECUTE</code>.</li>
 * <li>It is verified that <code>pNRA->execute(void)</code> returns
 * <code>ACTION_SUCCESS</code>.</li>
 * <li><code>pDRA</code> is set as <code>pNRA</code>'s "next recovery action". It is
 * verified that <code>NRA->getNextRecoveryAction(void)</code> returns the correct value.</li>
 * <li>The action outcome of <code>pDRA</code> is set to <code>ACTION_FAILURE</code> and its
 * execution flag to <code>true</code>. It is verified that <code>pNRA->execute(void)</code>
 * returns <code>ACTION_FAILURE</code>.</li>
 * </ol>
 * @see RecoveryAction
 * @see DC_NullRecoveryAction
 * @see DC_DummyRecoveryAction
 * @author Roberto Totaro
 * @version 1.0
 */
#define TYPE_TESTCASERECOVERYACTION_1 "testcaserecoveryaction_1"

void TestCaseRecoveryAction_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseRecoveryAction_1 {
    TestCaseGenericSetUp parent;
} TestCaseRecoveryAction_1;


typedef struct TestCaseRecoveryAction_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseRecoveryAction_1Class;


#define TESTCASERECOVERYACTION_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseRecoveryAction_1Class,\
                                            obj, TYPE_TESTCASERECOVERYACTION_1)

#define TESTCASERECOVERYACTION_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseRecoveryAction_1Class,\
                                          klass, TYPE_TESTCASERECOVERYACTION_1)

#define TESTCASERECOVERYACTION_1(obj) \
        OBJECT_CHECK(TestCaseRecoveryAction_1,\
                                            obj, TYPE_TESTCASERECOVERYACTION_1)


TestCaseRecoveryAction_1* TestCaseRecoveryAction_1_new(void);

#endif
