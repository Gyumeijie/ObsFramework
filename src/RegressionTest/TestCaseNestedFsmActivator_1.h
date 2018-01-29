//
//
// TestCaseNestedFsmActivator_1.h
//


#ifndef TESTCASENESTEDFSMACTIVATOR_1_H
#define TESTCASENESTEDFSMACTIVATOR_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Verify the services of conditional punctual actions. One
 * <code>DC_NestedFsmActivator</code> object is created and the following
 * procedure is performed upon it: <ol>
 * <li>A FSM, its states and a corresponding number of events are created. The
 * FSM and the events are configured and initialized. These objects will be
 * used to test the <code>DC_NestedFsmActivator</code> implementation.</li>
 * <li>It is verified that the object under test returns the correct class id.</li>
 * <li>It is verified that a newly created object is not configured.</li>
 * <li>The previously created <code>CC_FSM</code> is attached to the object. It is
 * verified that <code>getTargetFsm(void)</code> returns the right value and that the
 * object is configured.</li>
 * <li>The FSM is advanced to a non-zero state and <code>doInit(void)</code> is invoked.
 * It is verified that the nested FSM is reset and brought back to the initial state.</li>
 * <li>An event is raised and <code>doContinue(void)</code> is called. It is verified that
 * the nested FSm performs a transition to the target state of the event previously raised.</li>
 * </ol>
 * @see DC_NestedFsmActivator
 * @see CC_FSM
 * @see FsmState
 * @see DC_DummyFsmState
 * @see DC_FsmEvent
 * @author Roberto Totaro
 * @version 1.0
 */
#define TYPE_TESTCASENESTEDFSMACTIVATOR_1 "testcasenestedfsmactivator_1"

void TestCaseNestedFsmActivator_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseNestedFsmActivator_1 {
    TestCaseGenericSetUp parent;
} TestCaseNestedFsmActivator_1;


typedef struct TestCaseNestedFsmActivator_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseNestedFsmActivator_1Class;


#define TESTCASENESTEDFSMACTIVATOR_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseNestedFsmActivator_1Class,\
                                         obj, TYPE_TESTCASENESTEDFSMACTIVATOR_1)

#define TESTCASENESTEDFSMACTIVATOR_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseNestedFsmActivator_1Class,\
                                       klass, TYPE_TESTCASENESTEDFSMACTIVATOR_1)

#define TESTCASENESTEDFSMACTIVATOR_1(obj) \
        OBJECT_CHECK(TestCaseNestedFsmActivator_1,\
                                         obj, TYPE_TESTCASENESTEDFSMACTIVATOR_1)


TestCaseNestedFsmActivator_1* TestCaseNestedFsmActivator_1_new(void);

#endif
