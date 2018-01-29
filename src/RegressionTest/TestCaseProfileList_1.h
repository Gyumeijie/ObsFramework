//
//
// TestCaseProfileList_1.h
//
//
// Change Record:


#ifndef TESTCASEPROFILELIST_1_H
#define TESTCASEPROFILELIST_1_H


#include "../Utilities/TestCaseWithEvtCheck.h"
#include "../Qom/object.h"


/*
 * Verify the <code>DC_ProfileList</code> class.
 * An instance of this class is created and the following  tests are
 * performed on it: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified that the newly created object is not configured.</li>
 * <li>The profile list size is set. It is then verified that <code>getListSize(void)</code>
 * returns the correct value.</li>
 * <li>A number of pre-configured monitoring profiles is loaded and it is verified that
 * <code>getMonitoringProfile(void)</code> returns the correct values.</li>
 * <li>During the loading of the monitoring profiles, it is verified that the object
 * stays in the unconfigured status until the last profile is loaded.</li>
 * <li>Non-nominal behaviour check: it is verified that an invokation of <code>loadMonitoringProfile(void)</code> with
 * an illegal index generates an error report.</li>
 * <li>The functionality of both implementations of <code>deviatesFromProfile(void)</code> is
 * verified.</li>
 * </ol>
 * @see DC_ProfileList
 * @see DC_InRangeProfile
 * @author Roberto Totaro
 * @version 1.2
 */
#define TYPE_TESTCASEPROFILELIST_1 "testcaseprofilelist_1"

void TestCaseProfileList_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseProfileList_1 {
    TestCaseWithEvtCheck parent;
} TestCaseProfileList_1;


typedef struct TestCaseProfileList_1Class {
    TestCaseWithEvtCheckClass parent_class;
} TestCaseProfileList_1Class;


#define TESTCASEPROFILELIST_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseProfileList_1Class,\
                                               obj, TYPE_TESTCASEPROFILELIST_1)

#define TESTCASEPROFILELIST_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseProfileList_1Class,\
                                             klass, TYPE_TESTCASEPROFILELIST_1)

#define TESTCASEPROFILELIST_1(obj) \
        OBJECT_CHECK(TestCaseProfileList_1, obj, TYPE_TESTCASEPROFILELIST_1)


TestCaseProfileList_1* TestCaseProfileList_1_new(void);

#endif
