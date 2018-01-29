//
//
// TestCaseDummyConditionalPunctualAction_1.h
//


#ifndef TESTCASEDUMMYCONDITIONALPUNCTUALACTION_1_H
#define TESTCASEDUMMYCONDITIONALPUNCTUALACTION_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Verify the services of conditional punctual actions. One
 * <code>DC_DummyConditionalPunctualAction</code> object is created and the following
 * tests are performed upon it: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>The execution flag is set to <code>false</code> and an <code>execute</code> request
 * is made on the conditional punctual action. It is verified that the outcome is
 * <code>ACTION_CANNOT_EXECUTE</code>.</li>
 * <li>The execution flag is set to <code>true</code> and an <code>execute</code> request
 * is made on the conditional punctual action. It is verified that the outcome is
 * <code>ACTION_SUCCESS</code>.</li>
 * </ol>
 * @see DC_DummyConditionalPunctualAction
 * @see ConditionalPunctualAction
 * @author Roberto Totaro
 * @version 1.0
 */
#define TYPE_TESTCASEDUMMYCONDITIONALPUNCTUALACTION_1 "testcasedummyconditionalpunctualaction_1"

void TestCaseDummyConditionalPunctualAction_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseDummyConditionalPunctualAction_1 {
    TestCaseGenericSetUp parent;
} TestCaseDummyConditionalPunctualAction_1;


typedef struct TestCaseDummyConditionalPunctualAction_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseDummyConditionalPunctualAction_1Class;


#define TESTCASEDUMMYCONDITIONALPUNCTUALACTION_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseDummyConditionalPunctualAction_1Class,\
                            obj, TYPE_TESTCASEDUMMYCONDITIONALPUNCTUALACTION_1)

#define TESTCASEDUMMYCONDITIONALPUNCTUALACTION_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseDummyConditionalPunctualAction_1Class,\
                          klass, TYPE_TESTCASEDUMMYCONDITIONALPUNCTUALACTION_1)

#define TESTCASEDUMMYCONDITIONALPUNCTUALACTION_1(obj) \
        OBJECT_CHECK(TestCaseDummyConditionalPunctualAction_1,\
                            obj, TYPE_TESTCASEDUMMYCONDITIONALPUNCTUALACTION_1)


TestCaseDummyConditionalPunctualAction_1* TestCaseDummyConditionalPunctualAction_1_new(void);

#endif
