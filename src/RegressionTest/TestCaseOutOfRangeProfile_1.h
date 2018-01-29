//
//
// TestCaseOutOfRangeProfile_1.h
//


#ifndef TESTCASEOUTOFRANGEPROFILE_1_H
#define TESTCASEOUTOFRANGEPROFILE_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Check the functionalities implemented by class
 * <code>DC_OutOfRangeProfile</code>.
 * One instance of this class is created and
 * the following specific tests are performed: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>The monitoring profile is configured, a test value
 * lying within the range is passed through the monitoring profile
 * and it is verified that the monitoring
 * check service reports "no deviation from profile detected".</li>
 * <li>A test value lying outside the range is passed through
 * the monitoring profile and it is verified that the monitoring
 * check service reports "deviation from profile detected".</li>
 * </ol>
 * @see DC_OutOfRangeProfile
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEOUTOFRANGEPROFILE_1 "testcaseoutofrangeprofile_1"

void TestCaseOutOfRangeProfile_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseOutOfRangeProfile_1 {
    TestCaseGenericSetUp parent;
} TestCaseOutOfRangeProfile_1;


typedef struct TestCaseOutOfRangeProfile_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseOutOfRangeProfile_1Class;


#define TESTCASEOUTOFRANGEPROFILE_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseOutOfRangeProfile_1Class,\
                                         obj, TYPE_TESTCASEOUTOFRANGEPROFILE_1)

#define TESTCASEOUTOFRANGEPROFILE_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseOutOfRangeProfile_1Class,\
                                       klass, TYPE_TESTCASEOUTOFRANGEPROFILE_1)

#define TESTCASEOUTOFRANGEPROFILE_1(obj) \
        OBJECT_CHECK(TestCaseOutOfRangeProfile_1,\
                                        obj, TYPE_TESTCASEOUTOFRANGEPROFILE_1)


TestCaseOutOfRangeProfile_1* TestCaseOutOfRangeProfile_1_new(void);

#endif
