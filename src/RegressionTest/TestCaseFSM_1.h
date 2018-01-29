//
//
// TestCaseFSM_1.h
//


#ifndef TESTCASEFSM_1_H
#define TESTCASEFSM_1_H


#include "../Utilities/TestCaseWithEvtCheck.h"
#include "../Qom/object.h"


/*
 * Verify the initialization and configuration of the
 * <code>CC_FSM</code> class. One instance of the class is created
 * and the following tests are performed upon it: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified
 * that the object configuration service immediately after object creation
 * reports "object not configured".</li>
 * <li>The number of states is set and it is verified that this is correctly
 * reported.</li>
 * <li>Four dummy FsmStates are loaded into the FSM and it is verified that
 * the load operation is correctly performed.</li>
 * <li>Non-nominal behaviour check: an attempt is made to load a state at an illegal location and it is
 * verified that the correct event is generated. </li>
 * <li>The FSM is reset and it is checked that all state transitions are
 * initialized to "enabled".</li>
 * <li>The correctness of the default state is verified.</li>
 * <li>Non-nominal behviour check: unload one state and check that the object configuration service
 * reports "object not configured" (this check is inserted to ensure full statement coverage of the
 * class under test).</li>
 * <li>Reload the state and check that the object configuration service
 * now reports "object configured".</li>
 * </ol>
 * @see CC_FSM
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEFSM_1 "testcasefsm_1"

void TestCaseFSM_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseFSM_1 {
    TestCaseWithEvtCheck parent;
} TestCaseFSM_1;


typedef struct TestCaseFSM_1Class {
    TestCaseWithEvtCheckClass parent_class;
} TestCaseFSM_1Class;


#define TESTCASEFSM_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseFSM_1Class, obj, TYPE_TESTCASEFSM_1)

#define TESTCASEFSM_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseFSM_1Class, klass, TYPE_TESTCASEFSM_1)

#define TESTCASEFSM_1(obj) \
        OBJECT_CHECK(TestCaseFSM_1, obj, TYPE_TESTCASEFSM_1)


TestCaseFSM_1* TestCaseFSM_1_new(void);

#endif
