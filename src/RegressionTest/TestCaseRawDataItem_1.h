//
//
// TestCaseRawDataItem_1.h
//
//
// Change Record:


#ifndef TESTCASERAWDATAITEM_1_H
#define TESTCASERAWDATAITEM_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Check the setter and getter services for class <code>DC_RawDataItem</code>.
 * An instance of class <code>DC_RawDataItem</code> is created and the following
 * specific checks are performed:
 * <ol>
 * <li>The value of the variable encapsulated in the raw data item is set and then
 * read back through the data item accessor methods. It is checked that the read-back
 * value is correct. This operation is repeated for all types supported by the
 * <code>DC_RawDataItem</code>.</li>
 * <li>The value of the variable encapsulated by the raw data item is modified
 * using the data item setter methods and the modified value is then read back from
 * the variable itself. This operation is repeated for all types supported by the
 * <code>DC_RawDataItem</code>.</li>
 * </ol>
 * @author Roberto Totaro, Alessandro Pasetti
 * @version 1.0
 */
#define TYPE_TESTCASERAWDATAITEM_1 "testcaserawdataitem_1"

void TestCaseRawDataItem_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseRawDataItem_1 {
    TestCaseGenericSetUp parent;
} TestCaseRawDataItem_1;


typedef struct TestCaseRawDataItem_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseRawDataItem_1Class;


#define TESTCASERAWDATAITEM_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseRawDataItem_1Class,\
                                               obj, TYPE_TESTCASERAWDATAITEM_1)

#define TESTCASERAWDATAITEM_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseRawDataItem_1Class,\
                                             klass, TYPE_TESTCASERAWDATAITEM_1)

#define TESTCASERAWDATAITEM_1(obj) \
        OBJECT_CHECK(TestCaseRawDataItem_1, obj, TYPE_TESTCASERAWDATAITEM_1)


TestCaseRawDataItem_1* TestCaseRawDataItem_1_new(void);

#endif
