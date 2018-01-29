//
//
// TestCaseEvent_1.h
//


#ifndef TESTCASEEVENT_1_H
#define TESTCASEEVENT_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Verify the attribute setting and object configuration services of class
 * <code>DC_Event</code>.
 * The following specific tests are performed: <ol>
 * <li>The event type attribute of an event object is set
 * and then read out
 * and the correctness of its values is verified.</li>
 * <li>The time stamp attribute of an event object is set
 * and then read out
 * and the correctness of its values is verified.</li>
 * </ol>
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEEVENT_1 "testcaseevent_1"

void TestCaseEvent_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseEvent_1 {
    TestCaseGenericSetUp parent;
} TestCaseEvent_1;


typedef struct TestCaseEvent_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseEvent_1Class;


#define TESTCASEEVENT_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseEvent_1Class, obj, TYPE_TESTCASEEVENT_1)

#define TESTCASEEVENT_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseEvent_1Class, klass, TYPE_TESTCASEEVENT_1)

#define TESTCASEEVENT_1(obj) \
        OBJECT_CHECK(TestCaseEvent_1, obj, TYPE_TESTCASEEVENT_1)


TestCaseEvent_1* TestCaseEvent_1_new(void);

#endif
