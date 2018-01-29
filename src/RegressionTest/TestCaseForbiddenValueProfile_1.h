//
//
// TestCaseForbiddenValueProfile_1.h
//


#ifndef TESTCASEFORBIDDENVALUEPROFILE_1_H
#define TESTCASEFORBIDDENVALUEPROFILE_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Check the functionality of the <code>DC_ForbiddenValueProfile</code>
 * class. One instance of the class is created and
 * the following specific tests are performed: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>A forbidden value is loaded in the monitoring profile
 * and it is verified that the load operation is correctly performed.</li>
 * <li>A test value different from the forbidden value is passed through
 * the monitoring profile and it is verified that the monitoring
 * check service reports "no deviation from profile detected".</li>
 * <li>A test value equal to the forbidden value is passed through
 * the monitoring profile and it is verified that the monitoring
 * check service reports "deviation from profile detected".</li>
 * <li>The monitoring profile is disabled and the test value is again passed through
 * the monitoring profile. It is checked that the monitoring
 * check service reports "no deviation from profile detected".</li>
 * <li>Non-nominal behaviour check: it is checked that the monitoring check with a real-valued argument
 * reports "deviation from profile detected".</li>
 * </ol>
 * @see DC_ForbiddenValueProfile
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEFORBIDDENVALUEPROFILE_1 "testcaseforbiddenvalueprofile_1"

void TestCaseForbiddenValueProfile_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseForbiddenValueProfile_1 {
    TestCaseGenericSetUp parent;
} TestCaseForbiddenValueProfile_1;


typedef struct TestCaseForbiddenValueProfile_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseForbiddenValueProfile_1Class;


#define TESTCASEFORBIDDENVALUEPROFILE_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseForbiddenValueProfile_1Class,\
                                     obj, TYPE_TESTCASEFORBIDDENVALUEPROFILE_1)

#define TESTCASEFORBIDDENVALUEPROFILE_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseForbiddenValueProfile_1Class,\
                                   klass, TYPE_TESTCASEFORBIDDENVALUEPROFILE_1)

#define TESTCASEFORBIDDENVALUEPROFILE_1(obj) \
        OBJECT_CHECK(TestCaseForbiddenValueProfile_1,\
                                     obj, TYPE_TESTCASEFORBIDDENVALUEPROFILE_1)


TestCaseForbiddenValueProfile_1* TestCaseForbiddenValueProfile_1_new(void);

#endif
