//
//
// TestCaseInRangeProfile_1.h
//


#ifndef TESTCASEINRANGEPROFILE_1_H
#define TESTCASEINRANGEPROFILE_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Check the functionalities implemented by the abstract class
 * <code>RangeProfile</code>. The checks are performed on the concrete
 * class <code>DC_InRangeProfile</code>. The specific functionalities
 * implemented by class <code>DC_InRangeProfile</code> are also checked.
 * One instance of this class is created and
 * the following specific tests are performed: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified that the configuration check service of the
 * in range profile initially reports "not configured".</li>
 * <li>A lower bound value is loaded in the monitoring profile
 * and it is verified that the load operation is correctly performed.</li>
 * <li>An upper bound value is loaded in the monitoring profile
 * and it is verified that the load operation is correctly performed.</li>
 * <li>It is verified that the configuration check service of the
 * in range profile now reports "configured".</li>
 * <li>A test value of type <code>double</code> lying outside the
 * range is passed through
 * the monitoring profile and it is verified that the monitoring
 * check service reports "no deviation from profile detected".</li>
 * <li>A test value type <code>double</code> lying within the
 * range is passed through
 * the monitoring profile and it is verified that the monitoring
 * check service reports "deviation from profile detected".</li>
 * <li>The monitoring profile is disabled and the same test valued
 * is again passed through the profile. It is checked that the monitoring
 * check service now reports "no deviation from profile detected".</li>
 * <li>The monitoring profile is enabled. A test value of type <code>int</code> lying outside the
 * range is passed through
 * the monitoring profile and it is verified that the monitoring
 * check service reports "no deviation from profile detected".</li>
 * <li>A test value type <code>int</code> lying within the
 * range is passed through
 * the monitoring profile and it is verified that the monitoring
 * check service reports "deviation from profile detected".</li>
 * </ol>
 * @see RangeProfile
 * @see DC_InRangeProfile
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEINRANGEPROFILE_1 "testcaseinrangeprofile_1"

void TestCaseInRangeProfile_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseInRangeProfile_1 {
    TestCaseGenericSetUp parent;
} TestCaseInRangeProfile_1;


typedef struct TestCaseInRangeProfile_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseInRangeProfile_1Class;


#define TESTCASEINRANGEPROFILE_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseInRangeProfile_1Class,\
                                            obj, TYPE_TESTCASEINRANGEPROFILE_1)

#define TESTCASEINRANGEPROFILE_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseInRangeProfile_1Class,\
                                          klass, TYPE_TESTCASEINRANGEPROFILE_1)

#define TESTCASEINRANGEPROFILE_1(obj) \
        OBJECT_CHECK(TestCaseInRangeProfile_1,\
                                            obj, TYPE_TESTCASEINRANGEPROFILE_1)


TestCaseInRangeProfile_1* TestCaseInRangeProfile_1_new(void);

#endif
