//
//
// TestCaseNullProfile_1.h
//


#ifndef TESTCASENULLPROFILE_1_H
#define TESTCASENULLPROFILE_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Check the functionalities implemented by <code>DC_NullProfile</code>.
 * One instance of this class is created and
 * the following specific tests are performed: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>The <code>deviatesFromProfile(void)</code> method(both the <code>TD_Float</code>
 * and the <code>TD_Integer</code> implementation) is invoked with 100 
 * different values and it is verified that it alwayas returns false.</li>
 * <li>A call to <code>reset</code> is performed. This is a dummy check that required to have full statement
 * coverage of the super class.<li>
 * </ol>
 * @see MonitoringProfile
 * @see DC_NullProfile
 * @author Roberto Totaro
 * @version 1.0
 */
#define TYPE_TESTCASENULLPROFILE_1 "testcasenullprofile_1"

void TestCaseNullProfile_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseNullProfile_1 {
    TestCaseGenericSetUp parent;
} TestCaseNullProfile_1;


typedef struct TestCaseNullProfile_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseNullProfile_1Class;


#define TESTCASENULLPROFILE_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseNullProfile_1Class,\
                                               obj, TYPE_TESTCASENULLPROFILE_1)

#define TESTCASENULLPROFILE_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseNullProfile_1Class,\
                                             klass, TYPE_TESTCASENULLPROFILE_1)

#define TESTCASENULLPROFILE_1(obj) \
        OBJECT_CHECK(TestCaseNullProfile_1, obj, TYPE_TESTCASENULLPROFILE_1)


TestCaseNullProfile_1* TestCaseNullProfile_1_new(void);

#endif
