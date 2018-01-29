//
//
// TestCaseTestPUSConfigurableManoeuvre_1.h
//


#ifndef TESTCASETESTPUSCONFIGURABLEMANOEUVRE_1_H
#define TESTCASETESTPUSCONFIGURABLEMANOEUVRE_1_H


#include "../Utilities/TestCaseWithEvtCheck.h"
#include "../Qom/object.h"


/*
 * Verify the services implemented by the
 * <code>DC_TestPUSConfigurableManoeuvre</code>. One instance
 * of this class is created and the following tests are performed
 * upon it: <ol>
 * <li>The correctness of the class identified is verified.</li>
 * <li>It is verified that the action counters are equal to zero at
 * creation.</li>
 * <li>The default values of the start, completion and progress acknowledge flags 
 * verified.</li>
 * <li>The values of the start, completion and progress acknowledge flags 
 * are updated and it is verified that the update operation is successful.</li>
 * <li>The value of the telecommand identifier is set and read back and it is
 * verified that the read-back value is correct.</li>
 * <li>The manoeuvre is put in use it is verified that its
 * start check returns "manoeuvre cannot start".</li>
 * <li>The initialization action is performed and it is verified that
 * the initialization action counter is incremented by one and that the
 * correct event is generated.</li>
 * <li>The continuation action is performed and it is verified that
 * the continuation action counter is incremented by one.</li>
 * <li>It is verified that the continuation check returns "manoeuvre
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
 * @see DC_TestPUSConfigurableManoeuvre
 * @see Manoeuvre
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASETESTPUSCONFIGURABLEMANOEUVRE_1 "testcasetestpusconfigurablemanoeuvre_1"

void TestCaseTestPUSConfigurableManoeuvre_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseTestPUSConfigurableManoeuvre_1 {
    TestCaseWithEvtCheck parent;
} TestCaseTestPUSConfigurableManoeuvre_1;


typedef struct TestCaseTestPUSConfigurableManoeuvre_1Class {
    TestCaseWithEvtCheckClass parent_class;
} TestCaseTestPUSConfigurableManoeuvre_1Class;


#define TESTCASETESTPUSCONFIGURABLEMANOEUVRE_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseTestPUSConfigurableManoeuvre_1Class, \
                              obj, TYPE_TESTCASETESTPUSCONFIGURABLEMANOEUVRE_1)

#define TESTCASETESTPUSCONFIGURABLEMANOEUVRE_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseTestPUSConfigurableManoeuvre_1Class, \
                            klass, TYPE_TESTCASETESTPUSCONFIGURABLEMANOEUVRE_1)

#define TESTCASETESTPUSCONFIGURABLEMANOEUVRE_1(obj) \
        OBJECT_CHECK(TestCaseTestPUSConfigurableManoeuvre_1, \
                              obj, TYPE_TESTCASETESTPUSCONFIGURABLEMANOEUVRE_1)


TestCaseTestPUSConfigurableManoeuvre_1* TestCaseTestPUSConfigurableManoeuvre_1_new(void);

#endif
