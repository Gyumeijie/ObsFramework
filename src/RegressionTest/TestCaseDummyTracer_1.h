//
//
// TestCaseDummyTracer_1.h
//


#ifndef TESTCASEDUMMYTRACER_1_H
#define TESTCASEDUMMYTRACER_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Verify the functionality of the
 * <code>DC_DummyTracer</code> component.
 * The following specific tests are performed: <ol>
 * <li>A <code>DC_DummyTracer</code> instance is created and it is verified
 * that it enable status is "disabled".</li>
 * <li>A synch trace signal is sent through the dummy tracer component.
 * This operation should have no effect.</li>
 * <li>A packet trace signal is sent through the dummy tracer component.
 * This operation should have no effect.</li>
 * </ol>
 * @see DC_DummyTracer
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEDUMMYTRACER_1 "testcasedummytracer_1"

void TestCaseDummyTracer_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseDummyTracer_1 {
    TestCaseGenericSetUp parent;
} TestCaseDummyTracer_1;


typedef struct TestCaseDummyTracer_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseDummyTracer_1Class;


#define TESTCASEDUMMYTRACER_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseDummyTracer_1Class, obj, TYPE_TESTCASEDUMMYTRACER_1)

#define TESTCASEDUMMYTRACER_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseDummyTracer_1Class, klass, TYPE_TESTCASEDUMMYTRACER_1)

#define TESTCASEDUMMYTRACER_1(obj) \
        OBJECT_CHECK(TestCaseDummyTracer_1, obj, TYPE_TESTCASEDUMMYTRACER_1)


TestCaseDummyTracer_1* TestCaseDummyTracer_1_new(void);

#endif
