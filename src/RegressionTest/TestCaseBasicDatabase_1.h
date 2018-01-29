//
//
// TestCaseBasicDatabase_1.h
//


#ifndef TESTCASEBASICDATABASE_1_H
#define TESTCASEBASICDATABASE_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Verify the functionalities implemented by the
 * <code>DC_BasicDatabase</code> component.
 * An instance of the component is created and the following
 * specific tests are performed upon it: <ol>
 * <li>It is verified that the class ID of the component has the correct value.</li>
 * <li>It is verified that, after instantiation, the configuration service
 * of the component reports "not configured".</li>
 * <li>The database size is set and then read back and it is checked that the read-back
 * value is correct.</li>
 * <li>The configuration of the database component is completed by loading the default and
 * operational tables and it is verified that the configuration service
 * of the component reports "configured".</li>
 * <li>It is verified that the operational table is initialized to hold a copy
 * of the default table.</li>
 * <li>The setter and getter methods for all parameters types are verified.</li>
 * <li>The pointer getter methods for all parameters types are verified.</li>
 * </ol>
 * @see DC_BasicDatabase
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEBASICDATABASE_1 "testcasebasicdatabase_1"

void TestCaseBasicDatabase_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseBasicDatabase_1 {
    TestCaseGenericSetUp parent;
} TestCaseBasicDatabase_1;


typedef struct TestCaseBasicDatabase_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseBasicDatabase_1Class;


#define TESTCASEBASICDATABASE_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseBasicDatabase_1Class,\
                                              obj, TYPE_TESTCASEBASICDATABASE_1)

#define TESTCASEBASICDATABASE_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseBasicDatabase_1Class,\
                                            klass, TYPE_TESTCASEBASICDATABASE_1)

#define TESTCASEBASICDATABASE_1(obj) \
        OBJECT_CHECK(TestCaseBasicDatabase_1, obj, TYPE_TESTCASEBASICDATABASE_1)


TestCaseBasicDatabase_1* TestCaseBasicDatabase_1_new(void);

#endif
