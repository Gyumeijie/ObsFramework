//
//
// TestCaseUnstableFsmState_1.h
//


#ifndef TESTCASEUNSTABLEFSMSTATE_1_H
#define TESTCASEUNSTABLEFSMSTATE_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Verify the services of an unstable FSM state. One
 * <code>DC_UnstableFsmState</code> object is created and the following
 * tests are performed upon it: <ol>
 * <li>It is verified that the object under test returns the correct class id.</li>
 * <li>It is verified that <code>isFinished(void)</code> returns <code>true</code>.</li>
 * <li>A dummy call to <code>doContinue</code> is performed(this is necessary for
 * test coverage reasons).</li>
 * </ol>
 * @see DC_UnstableFsmState
 * @see FsmState
 * @author Roberto Totaro
 * @version 1.0
 */
#define TYPE_TESTCASEUNSTABLEFSMSTATE_1 "testcaseunstablefsmstate_1"

void TestCaseUnstableFsmState_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseUnstableFsmState_1 {
    TestCaseGenericSetUp parent;
} TestCaseUnstableFsmState_1;


typedef struct TestCaseUnstableFsmState_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseUnstableFsmState_1Class;


#define TESTCASEUNSTABLEFSMSTATE_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseUnstableFsmState_1Class,\
                                          obj, TYPE_TESTCASEUNSTABLEFSMSTATE_1)

#define TESTCASEUNSTABLEFSMSTATE_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseUnstableFsmState_1Class,\
                                        klass, TYPE_TESTCASEUNSTABLEFSMSTATE_1)

#define TESTCASEUNSTABLEFSMSTATE_1(obj) \
        OBJECT_CHECK(TestCaseUnstableFsmState_1,\
                                          obj, TYPE_TESTCASEUNSTABLEFSMSTATE_1)


TestCaseUnstableFsmState_1* TestCaseUnstableFsmState_1_new(void);

#endif
