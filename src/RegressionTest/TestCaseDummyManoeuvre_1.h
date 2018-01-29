//
//
// TestCaseDummyManoeuvre_1.h
//


#ifndef TESTCASEDUMMYMANOEUVRE_1_H
#define TESTCASEDUMMYMANOEUVRE_1_H


#include "../Utilities/TestCaseWithEvtCheck.h"
#include "../Qom/object.h"


/*
 * Verify the services implemented by the <code>Manoeuvre</code> class.
 * Since this class is abstract, the verification is performed upon
 * its concrete subclass <code>DC_DummyManoeuvre</code>. One instance
 * of this class is created and the following tests are performed upon it: <ol>
 * <li>The correctness of the class identified is verified.</li>
 * <li>It is verified that the manoeuvre is enabled at creation.</li>
 * <li>It is verified that the continuation check code is equal to zero.</li>
 * <li>It is verified that the inUse flag at creation has value:
 * "not in use".</li>
 * <li>It is verified that the isExecuting flag at creation has value:
 * "not executing".</li>
 * <li>It is verified that the isSuspended flag at creation has value:
 * "not suspended".</li>
 * <li>The manoeuvre is disabled and it is verified that the change in
 * enable status is correctly reported by the manoeuvre.</li>
 * <li>The inUse status of the manoeuvre is changed to "manoeuvre
 * in use" and it is verified that the status change is correctly
 * reported.</li>
 * <li>The isSuspended status of the manoeuvre is changed to "manoeuvre
 * is suspended" and it is verified that the status change is correctly
 * reported.</li>
 * <li>It is verified that the correct event is generated to record
 * the supension of the manoeuvre.</li>
 * <li>The isSuspended status is changed back to "not suspended" and it is
 * verified that the correct event is generated to record
 * the resumption of the manoeuvre.</li>
 * <li>It is verified that its start check reports:
 * "manoeuvre cannot start" (the manoeuvre is still disabled).</li>
 * <li>The manoeuvre is enabled and it is verified that its start
 * check now reports: "manoeuvre can start".</li>
 * <li>The initialization and continuation actions are executed
 * once and it is verified that the isExecuting flag changes its
 * value to: "manoeuvre is executing".</li>
 * <li>It is verified that the correct event is generated to record
 * the start of the execution of the manoeuvre.</li>
 * <li>It is verified that the continuation check of the manoeuvre
 * reports: "manoeuvre can continue".</li>
 * <li>It is verified that the termination check of the manoeuvre reports
 * "manoeuvre has terminated execution".</li>
 * <li>An abort request is issued to the manoeuvre and it is
 * verified that its isExecuting flag changes its
 * value to: "manoeuvre is not executing".</li>
 * <li>It is verified that the correct event is generated to record
 * the abort of the nanoeuvre.</li>
 * <li>The manoeuvre is again brought into "executing" status by
 * executing its initialization and continuation actions. The
 * termination action is then executed and it is verified that
 * the isExecuting flag changes its value to: "manoeuvre is
 * not executing".</li>
 * <li>It is verified that the correct event is generated to record
 * the termination of the manoeuvre.</li>
 * </ol>
 * @see DC_DummyManoeuvre
 * @see Manoeuvre
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @author Roberto Totaro
 * @version 1.1
 */
#define TYPE_TESTCASEDUMMYMANOEUVRE_1 "testcasedummymanoeuvre_1"

void TestCaseDummyManoeuvre_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseDummyManoeuvre_1 {
    TestCaseWithEvtCheck parent;
} TestCaseDummyManoeuvre_1;


typedef struct TestCaseDummyManoeuvre_1Class {
    TestCaseWithEvtCheckClass parent_class;
} TestCaseDummyManoeuvre_1Class;


#define TESTCASEDUMMYMANOEUVRE_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseDummyManoeuvre_1Class, \
                                            obj, TYPE_TESTCASEDUMMYMANOEUVRE_1)

#define TESTCASEDUMMYMANOEUVRE_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseDummyManoeuvre_1Class, \
                                          klass, TYPE_TESTCASEDUMMYMANOEUVRE_1)

#define TESTCASEDUMMYMANOEUVRE_1(obj) \
        OBJECT_CHECK(TestCaseDummyManoeuvre_1, \
                                            obj, TYPE_TESTCASEDUMMYMANOEUVRE_1)


TestCaseDummyManoeuvre_1* TestCaseDummyManoeuvre_1_new(void);

#endif
