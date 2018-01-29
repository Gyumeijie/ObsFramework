//
//
// TestCaseDummyPunctualAction_1.h
//
//
// Change Record:


#ifndef TESTCASEDUMMYPUNCTUALACTION_1_H
#define TESTCASEDUMMYPUNCTUALACTION_1_H


#include "../Utilities/TestCaseWithEvtCheck.h"
#include "../Qom/object.h"


/*
 * Verify the enable service and the event registration service
 * of punctual actions.
 * One <code>DC_DummyPunctualAction</code> is created and the following tests
 * are performed upon it: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified that the punctual action is enabled at creation.</li>
 * <li>It is verified that <code>getLastOutcome</code> returns <code>ACTION_RESET</code>.</li>
 * <li>An <code>execute</code> request is made on the punctual action and it is verified
 * that the punctual action returns a "action successful" outcome and
 * that an event recording the correct execution status is created.</li>
 * <li>The punctual action is disabled and it is verified that the disabled
 * status is correctly reported by the punctual action.</li>
 * <li>An <code>execute</code> request is made on the disabled punctual action
 * and it is verified that an event recording the correct execution status is created.</li>
 * <li>It is verified that <code>getLastOutcome</code> correctly reports the latest event.</li>
 * <li><code>resetLastOutcome</code> is invoked and it is verified that
 * <code>getLastOutcome</code> returns <code>ACTION_RESET</code>.</li>
 * </ol>
 * @see DC_DummyPunctualAction
 * @see PunctualAction
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @author Roberto Totaro
 * @version 1.3
 */
#define TYPE_TESTCASEDUMMYPUNCTUALACTION_1 "testcasedummypunctualaction_1"

void TestCaseDummyPunctualAction_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseDummyPunctualAction_1 {
    TestCaseWithEvtCheck parent;
} TestCaseDummyPunctualAction_1;


typedef struct TestCaseDummyPunctualAction_1Class {
    TestCaseWithEvtCheckClass parent_class;
} TestCaseDummyPunctualAction_1Class;


#define TESTCASEDUMMYPUNCTUALACTION_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseDummyPunctualAction_1Class,\
                                       obj, TYPE_TESTCASEDUMMYPUNCTUALACTION_1)

#define TESTCASEDUMMYPUNCTUALACTION_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseDummyPunctualAction_1Class,\
                                     klass, TYPE_TESTCASEDUMMYPUNCTUALACTION_1)

#define TESTCASEDUMMYPUNCTUALACTION_1(obj) \
        OBJECT_CHECK(TestCaseDummyPunctualAction_1,\
                                       obj, TYPE_TESTCASEDUMMYPUNCTUALACTION_1)


TestCaseDummyPunctualAction_1* TestCaseDummyPunctualAction_1_new(void);

#endif
