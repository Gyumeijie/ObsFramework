//
//
// TestCaseNestedFsmActivatorWithExitCheck_1.h
//


#ifndef TESTCASENESTEDFSMACTIVATORWITHEXITCHECK_1_H
#define TESTCASENESTEDFSMACTIVATORWITHEXITCHECK_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Verify the services of nested FSM states. One
 * <code>DC_NestedFsmActivatorWithExitCheck</code> object is created and the following
 * procedure is performed upon it: <ol>
 * <li>A FSM, its states and a corresponding number of events are created. The
 * FSM and the events are configured and initialized. These objects will be
 * used to test the <code>DC_NestedFsmActivatorWithExitCheck</code> implementation.</li>
 * <li>It is verified that the object under test returns the correct class id.</li>
 * <li>It is verified that a newly created object is not configured.</li>
 * <li>The previously created <code>CC_FSM</code> is attached to the object. It is
 * verified that the object is not yet configured.</li>
 * <li>The target state is set by calling <code>setTargetState(void)</code>. It is verified
 * that <code>getTargetState(void)</code> returns the proper value and that the object is
 * conofigured.</li>
 * <li>The FSM is advanced through all its states and it is verified that
 * <code>canExit(void)</code> returns true only when the FSM state is equal to the
 * target state.</li>
 * </ol>
 * @see DC_NestedFsmActivatorWithExitCheck
 * @see CC_FSM
 * @see FsmState
 * @see DC_DummyFsmState
 * @see DC_FsmEvent
 * @author Roberto Totaro
 * @version 1.0
 */
#define TYPE_TESTCASENESTEDFSMACTIVATORWITHEXITCHECK_1 "testcasenestedfsmactivatorwithexitcheck_1"

void TestCaseNestedFsmActivatorWithExitCheck_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseNestedFsmActivatorWithExitCheck_1 {
    TestCaseGenericSetUp parent;
} TestCaseNestedFsmActivatorWithExitCheck_1;


typedef struct TestCaseNestedFsmActivatorWithExitCheck_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseNestedFsmActivatorWithExitCheck_1Class;


#define TESTCASENESTEDFSMACTIVATORWITHEXITCHECK_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseNestedFsmActivatorWithExitCheck_1Class,\
                           obj, TYPE_TESTCASENESTEDFSMACTIVATORWITHEXITCHECK_1) 

#define TESTCASENESTEDFSMACTIVATORWITHEXITCHECK_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseNestedFsmActivatorWithExitCheck_1Class,\
                         klass, TYPE_TESTCASENESTEDFSMACTIVATORWITHEXITCHECK_1)

#define TESTCASENESTEDFSMACTIVATORWITHEXITCHECK_1(obj) \
        OBJECT_CHECK(TestCaseNestedFsmActivatorWithExitCheck_1,\
                           obj, TYPE_TESTCASENESTEDFSMACTIVATORWITHEXITCHECK_1)


TestCaseNestedFsmActivatorWithExitCheck_1* TestCaseNestedFsmActivatorWithExitCheck_1_new(void);

#endif
