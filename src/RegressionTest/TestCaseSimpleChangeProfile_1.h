//
//
// TestCaseSimpleChangeProfile_1.h
//


#ifndef TESTCASESIMPLECHANGEPROFILE_1_H
#define TESTCASESIMPLECHANGEPROFILE_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Check the functionality of the <code>MonitoringProfile</code>
 * abstract class as they are implemented in the
 * <code>SimpleChangeProfile</code> concrete class. Additionally, the
 * specific functionalities of the <code>SimpleChangeProfile</code>
 * are also checked.
 * <p>
 * One instance of the <code>SimpleChangeProfile</code> is created and
 * the following specific tests are performed: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified that the monitoring check of the profile component
 * is initially enabled.</li>
 * <li>A reference value is loaded in the simple change profile
 * and it is verified that the load operation is correctly performed.</li>
 * <li>A test value identical to the reference value is passed through
 * the simple change profile and it is verified that the monitoring
 * check service reports "no deviation from profile detected".</li>
 * <li>A test value different from the reference value is passed through
 * the simple change profile and it is verified that the monitoring
 * check service reports "deviation from profile detected" and that
 * an event report has been created to record the profile violation.</li>
 * <li>Non-nominal behaviour check: it is checked that the monitoring check with a real-valued argument
 * reports "deviation from profile detected".</li>
 * <li>The monitoring is disabled and it is verified that
 * the enable status is correctly reported.</li>
 * <li>A test value different from the reference value is passed through
 * the disabled simple change profile and it is verified that the monitoring
 * check service reports "no deviation from profile detected" and that
 * no event reports are created.</li>
 * </ol>
 * @see DC_SimpleChangeProfile
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASESIMPLECHANGEPROFILE_1 "testcasesimplechangeprofile_1"

void TestCaseSimpleChangeProfile_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseSimpleChangeProfile_1 {
    TestCaseGenericSetUp parent;
} TestCaseSimpleChangeProfile_1;


typedef struct TestCaseSimpleChangeProfile_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseSimpleChangeProfile_1Class;


#define TESTCASESIMPLECHANGEPROFILE_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseSimpleChangeProfile_1Class, \
                                       obj, TYPE_TESTCASESIMPLECHANGEPROFILE_1)

#define TESTCASESIMPLECHANGEPROFILE_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseSimpleChangeProfile_1Class, \
                                     klass, TYPE_TESTCASESIMPLECHANGEPROFILE_1)

#define TESTCASESIMPLECHANGEPROFILE_1(obj) \
        OBJECT_CHECK(TestCaseSimpleChangeProfile_1, \
                                       obj, TYPE_TESTCASESIMPLECHANGEPROFILE_1)


TestCaseSimpleChangeProfile_1* TestCaseSimpleChangeProfile_1_new(void);

#endif
