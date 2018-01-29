//
//
// TestCaseControlAction_1.h
//


#ifndef TESTCASECONTROLACTION_1_H
#define TESTCASECONTROLACTION_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Check the services offered by control actions. One
 * <code>DC_ControlAction</code> component is created and the following
 * tests are performed upon it: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is checked that the configuration check service initially
 * reports: "not configured".</li>
 * <li>A control block is loaded and it is verified that the load operations
 * was successful. The control block that is loaded is an instance of
 * <code>DC_DummyControlBlock</code>.</li>
 * <li>It is checked that the configuration check service now
 * reports: "configured".</li>
 * <li>An execution request is sent to the control action and it is verified
 * that the control block is propagated.</li>
 * <li>A reset request is sent to the control action and it is verified
 * that the control block is reset.</li>
 * </ol>
 * @see DC_ControlAction
 * @see DC_DummyControlBlock
 * @author A. Pasetti
 * @version 1.0
 */
#define TYPE_TESTCASECONTROLACTION_1 "testcasecontrolaction_1"

void TestCaseControlAction_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseControlAction_1 {
    TestCaseGenericSetUp parent;
} TestCaseControlAction_1;


typedef struct TestCaseControlAction_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseControlAction_1Class;


#define TESTCASECONTROLACTION_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseControlAction_1Class, \
                                              obj, TYPE_TESTCASECONTROLACTION_1)

#define TESTCASECONTROLACTION_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseControlAction_1Class, \
                                            klass, TYPE_TESTCASECONTROLACTION_1)

#define TESTCASECONTROLACTION_1(obj) \
        OBJECT_CHECK(TestCaseControlAction_1, obj, TYPE_TESTCASECONTROLACTION_1)


TestCaseControlAction_1* TestCaseControlAction_1_new(void);

#endif
