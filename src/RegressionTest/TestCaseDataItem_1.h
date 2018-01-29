//
//
// TestCaseDataItem_1.h
//
//
// Change Record:


#ifndef TESTCASEDATAITEM_1_H
#define TESTCASEDATAITEM_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Check the data set and get services for class <code>DC_DataItem</code>.
 * Two <code>DC_DataItem</code> objects are created to encapsulate access to,
 * respectively, a <code>TD_Float</code> and <code>TD_Integer</code> variable.
 * The following specific checks are performed:
 * <ol>
 * <li>The values of the encapsulated variables are set and then read back
 * through the data item accessor methods and it is checked that the read-back value
 * is correct.</li>
 * <li>The values of the data item are set through the data item accessor methods
 * and then read back and it is checked that the read-back value
 * is correct.</li>
 * </ol>
 * @author Roberto Totaro
 * @version 1.0
 */
#define TYPE_TESTCASEDATAITEM_1 "testcasedataitem_1"

void TestCaseDataItem_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseDataItem_1 {
    TestCaseGenericSetUp parent;
} TestCaseDataItem_1;


typedef struct TestCaseDataItem_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseDataItem_1Class;


#define TESTCASEDATAITEM_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseDataItem_1Class, obj, TYPE_TESTCASEDATAITEM_1)

#define TESTCASEDATAITEM_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseDataItem_1Class, klass, TYPE_TESTCASEDATAITEM_1)

#define TESTCASEDATAITEM_1(obj) \
        OBJECT_CHECK(TestCaseDataItem_1, obj, TYPE_TESTCASEDATAITEM_1)


TestCaseDataItem_1* TestCaseDataItem_1_new(void);

#endif
