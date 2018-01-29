//
//
// TestCaseDummyDatabase_1.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Data/DC_DummyDatabase.h"
#include "TestCaseDummyDatabase_1.h"



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Execute the test case. See class comment for details.
 */
static void runTestCase(void *obj)
{

   // Instantiate basic database
   DC_DummyDatabase *pDB = DC_DummyDatabase_new();

   // Verify correctness of class ID
   if (CC_RootObject_getClassId((CC_RootObject*)pDB) != ID_DUMMYDATABASE) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, "Wrong class ID");
		return;
	}

   // Check that size of the database
   if (DC_BasicDatabase_getTableLength((DC_BasicDatabase*)pDB) != 1) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Incorrect database size");
		return;
	}

   // Check the value of the database item
   ParameterDatabaseClass *pdc = PARAMETERDATABASE_GET_CLASS(pDB); 
   if (pdc->getParameterChar(pDB, 0) != 0) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Incorrect database parameter value");
		return;
	}

	TestCase_setTestResult((TestCase*)obj, TEST_SUCCESS, "Test Successful");
	return;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj){}

TestCaseDummyDatabase_1* TestCaseDummyDatabase_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEDUMMYDATABASE_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                    ID_DUMMYDATABASE*10+1,
                                                    "TestCaseDummyDatabase_1");
    return (TestCaseDummyDatabase_1*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    TestCaseClass *tcc = TESTCASE_CLASS(oc);
    tcc->runTestCase = runTestCase;
}

static const TypeInfo type_info = {
    .name = TYPE_TESTCASEDUMMYDATABASE_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseDummyDatabase_1),
    .abstract = false,
    .class_size = sizeof(TestCaseDummyDatabase_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseDummyDatabase_1_register(void)
{
    type_register_static(&type_info);
}
