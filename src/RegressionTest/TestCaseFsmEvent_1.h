//
//
// TestCaseFsmEvent_1.h
//


#ifndef TESTCASEFSMEVENT_1_H
#define TESTCASEFSMEVENT_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Verify the functionalities implemented by the
 * <code>DC_FsmEvent</code> component.
 * An instance of the <code>DC_FsmEvent</code> is created and the following
 * specific tests are performed upon it: <ol>
 * <li>It is verified that the class ID of the component has the correct value.</li>
 * <li>It is verified that the FsmEvent is not configured at creation(object
 * configuration service reports
 * "not configured").</li>
 * <li>A target state is loaded in the FsmEvent and it is verified that
 * the load operation is correctly executed.</li>
 * <li>A target FSM is loaded in the FsmEvent and it is verified that
 * the load operation is correctly executed.</li>
 * <li>After the target FSM and target states have been loaded, it is verified
 * that the FsmEvent is configured(object configuration service reports
 * "configured").</li>
 * </ol>
 * @see DC_FsmEvent
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEFSMEVENT_1 "testcasefsmevent_1"

void TestCaseFsmEvent_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseFsmEvent_1 {
    TestCaseGenericSetUp parent;
} TestCaseFsmEvent_1;


typedef struct TestCaseFsmEvent_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseFsmEvent_1Class;


#define TESTCASEFSMEVENT_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseFsmEvent_1Class, obj, TYPE_TESTCASEFSMEVENT_1)

#define TESTCASEFSMEVENT_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseFsmEvent_1Class, klass, TYPE_TESTCASEFSMEVENT_1)

#define TESTCASEFSMEVENT_1(obj) \
        OBJECT_CHECK(TestCaseFsmEvent_1, obj, TYPE_TESTCASEFSMEVENT_1)


TestCaseFsmEvent_1* TestCaseFsmEvent_1_new(void);

#endif
