//
//
// TestCaseDummyFsmState_1.h
//


#ifndef TESTCASEDUMMYFSMSTATE_1_H
#define TESTCASEDUMMYFSMSTATE_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Verify the functionalities implemented by the
 * <code>DC_FsmEvent</code> component.
 * An instance of the <code>DC_DummyFsmState</code> is created and the following
 * specific tests are performed upon it: <ol>
 * <li>It is verified that the class ID of the component has the correct value.</li>
 * <li>It is verified that the "next state" at creation is pNULL.</li>
 * <li>A "next state" is loaded in the component and it is verified that
 * the load operation is correctly executed.</li>
 * <li>It is verified that the initialization, exit and termination checks report
 * the correct results.</li>
 * <li>The initialization, continued and exit actions are executed and then it is
 * verified that the initialization, exit and termination checks still report
 * the correct results.</li>
 * </ol>
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEDUMMYFSMSTATE_1 "testcasedummyfsmstate_1"

void TestCaseDummyFsmState_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseDummyFsmState_1 {
    TestCaseGenericSetUp parent;
} TestCaseDummyFsmState_1;


typedef struct TestCaseDummyFsmState_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseDummyFsmState_1Class;


#define TESTCASEDUMMYFSMSTATE_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseDummyFsmState_1Class,\
                                              obj, TYPE_TESTCASEDUMMYFSMSTATE_1)

#define TESTCASEDUMMYFSMSTATE_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseDummyFsmState_1Class,\
                                            klass, TYPE_TESTCASEDUMMYFSMSTATE_1)

#define TESTCASEDUMMYFSMSTATE_1(obj) \
        OBJECT_CHECK(TestCaseDummyFsmState_1, obj, TYPE_TESTCASEDUMMYFSMSTATE_1)


TestCaseDummyFsmState_1* TestCaseDummyFsmState_1_new(void);

#endif
