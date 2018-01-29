//
//
// TestCaseRootObject_1.h
//


#ifndef TESTCASEROOTOBJECT_1_H
#define TESTCASEROOTOBJECT_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Verify setting of instance ID's in class <code>CC_RootObject</code>.
 * The following specific tests are performed: <ol>
 * <li>It is checked that the value of the instance identifier is incremented
 * by 1 every time a new insance of class <code>CC_RootObject</code>
 * is created.</li>
 * </ol>
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEROOTOBJECT_1 "testcaserootobject_1"

void TestCaseRootObject_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseRootObject_1 {
    TestCaseGenericSetUp parent;
} TestCaseRootObject_1;


typedef struct TestCaseRootObject_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseRootObject_1Class;


#define TESTCASEROOTOBJECT_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseRootObject_1Class, obj, TYPE_TESTCASEROOTOBJECT_1)

#define TESTCASEROOTOBJECT_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseRootObject_1Class, klass, TYPE_TESTCASEROOTOBJECT_1)

#define TESTCASEROOTOBJECT_1(obj) \
        OBJECT_CHECK(TestCaseRootObject_1, obj, TYPE_TESTCASEROOTOBJECT_1)


TestCaseRootObject_1* TestCaseRootObject_1_new(void);


#endif
