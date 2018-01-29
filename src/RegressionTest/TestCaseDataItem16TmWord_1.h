//
//
// TestCaseDataItem16TmWord_1.h
//
//
// Change Record:


#ifndef TESTCASEDATAITEM16TMWORD_1_H
#define TESTCASEDATAITEM16TMWORD_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Verify the structured telemetry packet services as implemented
 * by class <code>DC_DataItem16TmWord</code>.
 * An instance of this class is created and the following specific
 * tests are performed: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified that the configuration check service of the object
 * initially reports "object not configured".</li>
 * <li>A data item object is loaded into the <code>DC_DataItem16TmWord</code>
 * and it is verified that the configuration check service now reports
 * "object configured".</li>
 * <li>It is verified that the <code>getNumberOfBytes</code> on
 * <code>DC_DataItem16TmWord</code> reports the correct result.</li>
 * <li>It is verified that the <i>validity service</i> on
 * <code>DC_DataItem16TmWord</code> reports "data valid".</li>
 * <li>An <i>update request</i> is made to the <code>DC_DataItem16TmWord</code>.
 * This is followed by a <i>data acquisition request</i>. This is implemented
 * first through the <code>getUnsignedShort</code> and then through the
 * <code>getUnsignedByte</code> services and it is verified that in
 * both cases the correct values are returned.</li>
 * </ol>
 * @see DC_DataItem16TmWord
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.1
 */
#define TYPE_TESTCASEDATAITEM16TMWORD_1 "testcasedataitem16tmword_1"

void TestCaseDataItem16TmWord_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseDataItem16TmWord_1 {
    TestCaseGenericSetUp parent;
} TestCaseDataItem16TmWord_1;


typedef struct TestCaseDataItem16TmWord_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseDataItem16TmWord_1Class;


#define TESTCASEDATAITEM16TMWORD_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseDataItem16TmWord_1Class, \
                                          obj, TYPE_TESTCASEDATAITEM16TMWORD_1)

#define TESTCASEDATAITEM16TMWORD_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseDataItem16TmWord_1Class, \
                                        klass, TYPE_TESTCASEDATAITEM16TMWORD_1)

#define TESTCASEDATAITEM16TMWORD_1(obj) \
        OBJECT_CHECK(TestCaseDataItem16TmWord_1, \
                                          obj, TYPE_TESTCASEDATAITEM16TMWORD_1)


TestCaseDataItem16TmWord_1* TestCaseDataItem16TmWord_1_new(void);

#endif
