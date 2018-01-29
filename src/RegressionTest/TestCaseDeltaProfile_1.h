//
//
// TestCaseStuckDeltaProfile_1.h
//


#ifndef TESTCASEDELTAPROFILE_1_H
#define TESTCASEDELTAPROFILE_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Check the functionality of the <code>DeltaProfile</code> class.
 * One instance of the class is created and
 * the following specific tests are performed: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified that the configuration check service of the
 * simple change profile initially reports "not configured".</li>
 * <li>A delta threshold is loaded in the profile component
 * and it is verified that the load operation is correctly performed.</li>
 * <li>It is verified that the configuration check service of the
 * profile component reports "configured".</li>
 * <li>A sequence of test values of double type that should not
 * trigger the profile are
 * passed through its monitoring check service it is verified that the
 * check service reports "no deviation from profile detected".</li>
 * <li>A sequence of test values of double type that should trigger
 * the monitoring
 * check are passed through the profile component and it is verified that
 * the check service reports "deviation from profile detected".</li>
 * <li>A reset operation is performed and it is verified that
 * this interrupts the execution of the monitoring check.</li>
 * <li>A sequence of test values of integer type that should not
 * trigger the profile are
 * passed through its monitoring check service it is verified that the
 * check service reports "no deviation from profile detected".</li>
 * <li>A sequence of test values of integer type that should trigger
 * the monitoring
 * check are passed through the profile component and it is verified that
 * the check service reports "deviation from profile detected".</li>
 * </ol>
 * @see DC_DeltaProfile
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEDELTAPROFILE_1 "testcasedeltaprofile_1"

void TestCaseDeltaProfile_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseDeltaProfile_1 {
    TestCaseGenericSetUp parent;
} TestCaseDeltaProfile_1;


typedef struct TestCaseDeltaProfile_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseDeltaProfile_1Class;


#define TESTCASEDELTAPROFILE_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseDeltaProfile_1Class,\
                                              obj, TYPE_TESTCASEDELTAPROFILE_1)

#define TESTCASEDELTAPROFILE_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseDeltaProfile_1Class,\
                                            klass, TYPE_TESTCASEDELTAPROFILE_1)

#define TESTCASEDELTAPROFILE_1(obj) \
        OBJECT_CHECK(TestCaseDeltaProfile_1,\
                                             obj, TYPE_TESTCASEDELTAPROFILE_1)


TestCaseDeltaProfile_1* TestCaseDeltaProfile_1_new(void);

#endif
