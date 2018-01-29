//
//
// TestCaseDataPoolMonitor_1.h
//
//
// Change Record:


#ifndef TESTCASEDATAPOOLMONITOR_1_H
#define TESTCASEDATAPOOLMONITOR_1_H


#include "../Utilities/TestCaseWithEvtCheck.h"
#include "../Qom/object.h"


/*
 * Verify the services provided by the <code>DC_DataPoolMonitor</code> class.
 * A <code>DC_SampleFullDataPool</code> is created and configured with
 * a <code>DC_NullRecoveryAction</code> and a <code>DC_OutOfRangeProfile</code>
 * for each of the values it contains. The data pool is then linked to the
 * <code>CC_RootObject</code>. A <code>DC_DataPoolMonitor</code> object
 * is then created and the following tests are performed upon it: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>The <code>execute(void)</code> method is called and it is verified that the
 * validity status of the data items is left unchanged and no recovery action
 * was invoked.</li>
 * <li>The values in the data pool are set outside the range defined by the
 * monitoring profiles and <code>DC_DataPoolMonitor::execute(void)</code> is
 * invoked once again. It is then checked that the validity status of all the
 * values in the data pool is set to <code>NOT_VALID</code> and that the
 * recovery actions were invoked.</li>
 * </ol>
 * @author Roberto Totaro
 * @version 1.0
 */
#define TYPE_TESTCASEDATAPOOLMONITOR_1 "testcasedatapoolmonitor_1"

void TestCaseDataPoolMonitor_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseDataPoolMonitor_1 {
    TestCaseWithEvtCheck parent;
} TestCaseDataPoolMonitor_1;


typedef struct TestCaseDataPoolMonitor_1Class {
    TestCaseWithEvtCheckClass parent_class;
} TestCaseDataPoolMonitor_1Class;


#define TESTCASEDATAPOOLMONITOR_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseDataPoolMonitor_1Class, \
                                           obj, TYPE_TESTCASEDATAPOOLMONITOR_1)

#define TESTCASEDATAPOOLMONITOR_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseDataPoolMonitor_1Class, \
                                         klass, TYPE_TESTCASEDATAPOOLMONITOR_1)

#define TESTCASEDATAPOOLMONITOR_1(obj) \
        OBJECT_CHECK(TestCaseDataPoolMonitor_1, \
                                           obj, TYPE_TESTCASEDATAPOOLMONITOR_1)


TestCaseDataPoolMonitor_1* TestCaseDataPoolMonitor_1_new(void);

#endif
