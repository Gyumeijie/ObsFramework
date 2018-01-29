//
//
// TestCaseRootObject_3.h
//


#ifndef TESTCASEROOTOBJECT_3_H
#define TESTCASEROOTOBJECT_3_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Check the object and system configuration check services.
 * The following specific checks are performed: <ol>
 * <li>Two <code>CC_RootObject</code> instances are created and it is checked
 * that their object configuration services report "object configured".</li>
 * <li>It is checked
 * that the system configuration check service reports "system configured".</li>
 * <li>An event object is created but not fully configured and it is checked
 * that the system configuration check service reports "system not configured".</li>
 * </ol>
 * Since it checks the system configuration service, this test case should be
 * the first test case to be executed in a test run.
 * If it is not, it might fail unpredictably.
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEROOTOBJECT_3 "testcaserootobject_3"

void TestCaseRootObject_3_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseRootObject_3 {
    TestCaseGenericSetUp parent;
} TestCaseRootObject_3;


typedef struct TestCaseRootObject_3Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseRootObject_3Class;


#define TESTCASEROOTOBJECT_3_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseRootObject_3Class, obj, TYPE_TESTCASEROOTOBJECT_3)

#define TESTCASEROOTOBJECT_3_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseRootObject_3Class, klass, TYPE_TESTCASEROOTOBJECT_3)

#define TESTCASEROOTOBJECT_3(obj) \
        OBJECT_CHECK(TestCaseRootObject_3, obj, TYPE_TESTCASEROOTOBJECT_3)


TestCaseRootObject_3* TestCaseRootObject_3_new(void);

#endif
