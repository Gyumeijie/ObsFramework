//
//
// TestCaseNestedFsmActivatorWithEndState_1.h
//


#ifndef TESTCASENESTEDFSMACTIVATORWITHENDSTATE_1_H
#define TESTCASENESTEDFSMACTIVATORWITHENDSTATE_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Verify the services of nested FSM states. One
 * <code>DC_NestedFsmActivatorWithEndState</code> object is created and the following
 * procedure is performed upon it: <ol>
 * <li>A FSM, its states and a corresponding number of events are created. The
 * FSM and the events are configured and initialized. These objects will be
 * used to test the <code>DC_NestedFsmActivatorWithEndState</code> implementation.</li>
 * <li>It is verified that the object under test returns the correct class id.</li>
 * <li>It is verified that a newly created object is not configured.</li>
 * <li>The previously created <code>CC_FSM</code> is attached to the object. It is
 * verified that the object is not yet configured.</li>
 * <li>The target state is set by calling <code>setTargetState(void)</code>. It is verified
 * that <code>getTargetState(void)</code> returns the proper value and that the object is
 * conofigured.</li>
 * <li>The FSM is advanced through all its states and it is verified that
 * <code>isFinished(void)</code> returns true only when the FSM state is equal to the
 * target state.</li>
 * </ol>
 * @see DC_NestedFsmActivatorWithEndState
 * @see CC_FSM
 * @see FsmState
 * @see DC_DummyFsmState
 * @see DC_FsmEvent
 * @author Roberto Totaro
 * @version 1.0
 */
#define TYPE_TESTCASENESTEDFSMACTIVATORWITHENDSTATE_1 "testcasenestedfsmactivatorwithendstate_1"

void TestCaseNestedFsmActivatorWithEndState_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseNestedFsmActivatorWithEndState_1 {
    TestCaseGenericSetUp parent;
} TestCaseNestedFsmActivatorWithEndState_1;


typedef struct TestCaseNestedFsmActivatorWithEndState_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseNestedFsmActivatorWithEndState_1Class;


#define TESTCASENESTEDFSMACTIVATORWITHENDSTATE_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseNestedFsmActivatorWithEndState_1Class,\
                            obj, TYPE_TESTCASENESTEDFSMACTIVATORWITHENDSTATE_1)

#define TESTCASENESTEDFSMACTIVATORWITHENDSTATE_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseNestedFsmActivatorWithEndState_1Class,\
                          klass, TYPE_TESTCASENESTEDFSMACTIVATORWITHENDSTATE_1)

#define TESTCASENESTEDFSMACTIVATORWITHENDSTATE_1(obj) \
        OBJECT_CHECK(TestCaseNestedFsmActivatorWithEndState_1,\
                            obj, TYPE_TESTCASENESTEDFSMACTIVATORWITHENDSTATE_1)


TestCaseNestedFsmActivatorWithEndState_1* TestCaseNestedFsmActivatorWithEndState_1_new(void);

#endif
