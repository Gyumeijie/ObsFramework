//
//
// TestCaseFromFsmEvent_1.h
//


#ifndef TESTCASEFROMFSMEVENT_1_H
#define TESTCASEFROMFSMEVENT_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Verify the functionalities offered by the <code>DC_FromFsmEvent</code>
 * class. One FSM instance
 * is created and configured with 4 dummy FsmStates(states 0 to 3). One
 * <code>FromFsmEvents</code> is then instantiated and the following
 * specific tests are then performed: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified
 * that the object configuration service on the <code>FromFsmEvents</code>
 * reports "object not configured".</li>
 * <li>The <code>FromFsmEvents</code> is configured with a target
 * FSM, a starting and target state and it is verified that the configuration
 * operation on the class-specific part of the object(the definition of
 * the starting state) is correctly executed.</li>
 * <li>It is verified
 * that the object configuration service on the <code>FromFsmEvents</code>
 * reports "object configured".</li>
 * <li>The FSM is placed in a state different from the starting state
 * of the <code>FromFsmEvents</code>, the latter is fired and it is verified
 * that the state of the FSM has not changed.</li>
 * <li>The FSM is placed in a state equal to the starting state
 * of the <code>FromFsmEvents</code>, the latter is fired and it is verified
 * that the FSM performs a transition to the target state of the
 * <code>FromFsmEvents</code>.</li>
 * </ol>
 * @see CC_FSM
 * @see DC_FromFsmEvent
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEFROMFSMEVENT_1 "testcasefromfsmevent_1"

void TestCaseFromFsmEvent_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseFromFsmEvent_1 {
    TestCaseGenericSetUp parent;
} TestCaseFromFsmEvent_1;


typedef struct TestCaseFromFsmEvent_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseFromFsmEvent_1Class;


#define TESTCASEFROMFSMEVENT_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseFromFsmEvent_1Class,\
                                             obj, TYPE_TESTCASEFROMFSMEVENT_1)

#define TESTCASEFROMFSMEVENT_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseFromFsmEvent_1Class,\
                                           klass, TYPE_TESTCASEFROMFSMEVENT_1)

#define TESTCASEFROMFSMEVENT_1(obj) \
        OBJECT_CHECK(TestCaseFromFsmEvent_1, obj, TYPE_TESTCASEFROMFSMEVENT_1)


TestCaseFromFsmEvent_1* TestCaseFromFsmEvent_1_new(void);

#endif
