//
//
// TestCaseStuckDataProfile_1.h
//


#ifndef TESTCASESTUCKDATAPROFILE_1_H
#define TESTCASESTUCKDATAPROFILE_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Check the functionality of the <code>StuckDataProfile</code> class.
 * One instance of the class is created and
 * the following specific tests are performed: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified that the configuration check service of the
 * simple change profile initially reports "not configured".</li>
 * <li>A stuck threshold is loaded in the profile component
 * and it is verified that the load operation is correctly performed.</li>
 * <li>It is verified that the configuration check service of the
 * profile component reports "configured".</li>
 * <li>A sequence of test values that should not trigger the profile are
 * passed through its monitoring check service it is verified that the
 * check service reports "no deviation from profile detected".</li>
 * <li>A sequence of test values that should trigger the monitoring
 * check are passed through the profile component and it is verified that
 * the check service reports "deviation from profile detected".</li>
 * <li>A reset operation is performed and it is verified that
 * this interrupts the execution of the monitoring check.</li>
 * <li>Non-nominal behaviour check: it is checked that the monitoring check with a real-valued argument
 * reports "deviation from profile detected".</li>
 * </ol>
 * @see DC_StuckDataProfile
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASESTUCKDATAPROFILE_1 "testcasestuckdataprofile_1"

void TestCaseStuckDataProfile_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseStuckDataProfile_1 {
    TestCaseGenericSetUp parent;
} TestCaseStuckDataProfile_1;


typedef struct TestCaseStuckDataProfile_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseStuckDataProfile_1Class;


#define TESTCASESTUCKDATAPROFILE_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseStuckDataProfile_1Class,\
                                          obj, TYPE_TESTCASESTUCKDATAPROFILE_1)

#define TESTCASESTUCKDATAPROFILE_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseStuckDataProfile_1Class,\
                                        klass, TYPE_TESTCASESTUCKDATAPROFILE_1)

#define TESTCASESTUCKDATAPROFILE_1(obj) \
        OBJECT_CHECK(TestCaseStuckDataProfile_1,\
                                          obj, TYPE_TESTCASESTUCKDATAPROFILE_1)


TestCaseStuckDataProfile_1* TestCaseStuckDataProfile_1_new(void);

#endif
