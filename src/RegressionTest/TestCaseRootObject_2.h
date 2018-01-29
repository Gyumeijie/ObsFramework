//
//
// TestCaseRootObject_2.h
//


#ifndef TESTCASEROOTOBJECT_2_H
#define TESTCASEROOTOBJECT_2_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Verify setting of class ID's in class <code>CC_RootObject</code>.
 * The following specific tests are performed: <ol>
 * <li>The class ID for class <code>CC_RootObject</code> is read
 * out and its value is verified.</li>
 * <li>The class ID of two different instances of classes <code>CC_RootObject</code>
 * is read out and it is verified that the two values are identical.</li>
 * </ol>
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEROOTOBJECT_2 "testcaserootobject_2"

void TestCaseRootObject_2_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseRootObject_2 {
    TestCaseGenericSetUp parent;
} TestCaseRootObject_2;


typedef struct TestCaseRootObject_2Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseRootObject_2Class;


#define TESTCASEROOTOBJECT_2_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseRootObject_2Class, obj, TYPE_TESTCASEROOTOBJECT_2)

#define TESTCASEROOTOBJECT_2_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseRootObject_2Class, klass, TYPE_TESTCASEROOTOBJECT_2)

#define TESTCASEROOTOBJECT_2(obj) \
        OBJECT_CHECK(TestCaseRootObject_2, obj, TYPE_TESTCASEROOTOBJECT_2)


TestCaseRootObject_2* TestCaseRootObject_2_new(void);

#endif
