//
//
// TestCaseDummyDatabase_1.h
//


#ifndef TESTCASEDUMMYDATABASE_1_H
#define TESTCASEDUMMYDATABASE_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Check the functionalities implemented by the
 * <code>DC_DummyDatabase</code> component.
 * An instance of the component is created and the following
 * specific checks are performed upon it: <ol>
 * <li>It is checked that the class ID of the component has the correct value.</li>
 * <li>It is verified that the size of the database has the correct value.</li>
 * <li>It is verified that the single item in the database has the correct value.</li>
 * </ol>
 * @see DC_BasicDatabase
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEDUMMYDATABASE_1 "testcasedummydatabase_1"

void TestCaseDummyDatabase_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseDummyDatabase_1 {
    TestCaseGenericSetUp parent;
} TestCaseDummyDatabase_1;


typedef struct TestCaseDummyDatabase_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseDummyDatabase_1Class;


#define TESTCASEDUMMYDATABASE_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseDummyDatabase_1Class,\
                                              obj, TYPE_TESTCASEDUMMYDATABASE_1)

#define TESTCASEDUMMYDATABASE_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseDummyDatabase_1Class,\
                                            klass, TYPE_TESTCASEDUMMYDATABASE_1)

#define TESTCASEDUMMYDATABASE_1(obj) \
        OBJECT_CHECK(TestCaseDummyDatabase_1, obj, TYPE_TESTCASEDUMMYDATABASE_1)


TestCaseDummyDatabase_1* TestCaseDummyDatabase_1_new(void);

#endif
