//
//
// TestCaseDummyConfigurableManoeuvre_1.h
//


#ifndef TESTCASEDUMMYCONFIGURABLEMANOEUVRE_1_H
#define TESTCASEDUMMYCONFIGURABLEMANOEUVRE_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Verify the services implemented by the
 * <code>DC_DummyConfigurableManoeuvre</code>. One instance
 * of this class is created and the following tests are performed
 * upon it: <ol>
 * <li>The correctness of the class identified is verified.</li>
 * <li>It is verified that the action counters are equal to zero at
 * creation.</li>
 * <li>The manoeuvre is put in use it is verified that its
 * start check returns "manoeuvre cannot start".</li>
 * <li>The initialization action is performed and it is verified that
 * the initialization action counter is incremented by one.</li>
 * <li>The continuation action is performed and it is verified that
 * the continuation action counter is incremented by one.</li>
 * <li>It is verified that the continuaion check returns "manoeuvre
 * cannot continue".</li>
 * <li>It is verified that the termination check returns "manoeuvre
 * cannot terminate".</li>
 * <li>The termination action is executed and it is verfied that the
 * termination action counter is incremented by one.</li>
 * <li>The configurable return values of the manoeuvre checks are
 * inverted through method <code>setCheckStatus</code>. A complete
 * execution cycle for the manoeuvre is executed again(initialization,
 * one continuation action, termination) and it is verified that the
 * return values of the manoeuvre checks reflect the new settings.</li>
 * </ol>
 * @see DC_DummyConfigurableManoeuvre
 * @see Manoeuvre
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEDUMMYCONFIGURABLEMANOEUVRE_1 "testcasedummyconfigurablemanoeuvre_1"

void TestCaseDummyConfigurableManoeuvre_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseDummyConfigurableManoeuvre_1 {
    TestCaseGenericSetUp parent;
} TestCaseDummyConfigurableManoeuvre_1;


typedef struct TestCaseDummyConfigurableManoeuvre_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseDummyConfigurableManoeuvre_1Class;


#define TESTCASEDUMMYCONFIGURABLEMANOEUVRE_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseDummyConfigurableManoeuvre_1Class, \
                                obj, TYPE_TESTCASEDUMMYCONFIGURABLEMANOEUVRE_1)

#define TESTCASEDUMMYCONFIGURABLEMANOEUVRE_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseDummyConfigurableManoeuvre_1Class, \
                              klass, TYPE_TESTCASEDUMMYCONFIGURABLEMANOEUVRE_1)

#define TESTCASEDUMMYCONFIGURABLEMANOEUVRE_1(obj) \
        OBJECT_CHECK(TestCaseDummyConfigurableManoeuvre_1, \
                                obj, TYPE_TESTCASEDUMMYCONFIGURABLEMANOEUVRE_1)


TestCaseDummyConfigurableManoeuvre_1* TestCaseDummyConfigurableManoeuvre_1_new(void);

#endif
