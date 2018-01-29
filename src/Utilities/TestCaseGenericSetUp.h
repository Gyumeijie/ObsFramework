//
//
// TestCaseGenericSetUp.h
//


#ifndef TESTCASEGENERICSETUP_H
#define TESTCASEGENERICSETUP_H


#include "../Utilities/TestCase.h"
#include "../Qom/object.h"


/*
 * Base class for generic test cases. This class specializes
 * class <code>TestCase</code> to provide default implementations of
 * the <code>SetUpTestCase</code> and <code>ShutDownTestCase</code>
 * methods that are intended to be suitable for most framework test cases.
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 * @ingroup TestCases
 */
#define TYPE_TESTCASEGENERICSETUP "testcasegenericsetup"

void TestCaseGenericSetup_register(void);



///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct TestCaseGenericSetUp {
    TestCase parent;
};


struct TestCaseGenericSetUpClass {
    TestCaseClass parent_class;

    void (*post_init)(TestCaseGenericSetUp *This, int id, char *name);
};


#define TESTCASEGENERICSETUP_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseGenericSetUpClass, obj, TYPE_TESTCASEGENERICSETUP)

#define TESTCASEGENERICSETUP_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseGenericSetUpClass, klass, TYPE_TESTCASEGENERICSETUP)

#define TESTCASEGENERICSETUP(obj) \
        OBJECT_CHECK(TestCaseGenericSetUp, obj, TYPE_TESTCASEGENERICSETUP)


TestCaseGenericSetUp* TestCaseGenericSetup_new(int id, char *name);

#endif
