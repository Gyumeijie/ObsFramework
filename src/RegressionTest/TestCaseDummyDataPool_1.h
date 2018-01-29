//
//
// TestCaseDummyDataPool_1.h
//


#ifndef TESTCASEDUMMYDATAPOOL_1_H
#define TESTCASEDUMMYDATAPOOL_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Check the functionalities implemented by the <code>DC_DummyDataPool</code> class.
 * An instance of the component is created and the following
 * specific checks are performed upon it: <ol>
 * <li>It is verified that the class identifier has the correct value.</li>
 * <li>It is verified that the size of the data pool is equal to the size of the type
 * <code>TD_Integer</code>.</li>
 * <li>It is verified that the value of the item in the data pool is zero.</li>
 * </ol>
 * @see DC_BasicDataPool
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEDUMMYDATAPOOL_1 "testcasedummydatapool_1"

void TestCaseDummyDataPool_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseDummyDataPool_1 {
    TestCaseGenericSetUp parent;
} TestCaseDummyDataPool_1;


typedef struct TestCaseDummyDataPool_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseDummyDataPool_1Class;


#define TESTCASEDUMMYDATAPOOL_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseDummyDataPool_1Class,\
                                              obj, TYPE_TESTCASEDUMMYDATAPOOL_1)
 
#define TESTCASEDUMMYDATAPOOL_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseDummyDataPool_1Class,\
                                            klass, TYPE_TESTCASEDUMMYDATAPOOL_1)

#define TESTCASEDUMMYDATAPOOL_1(obj) \
        OBJECT_CHECK(TestCaseDummyDataPool_1, obj, TYPE_TESTCASEDUMMYDATAPOOL_1)


TestCaseDummyDataPool_1* TestCaseDummyDataPool_1_new(void);

#endif
