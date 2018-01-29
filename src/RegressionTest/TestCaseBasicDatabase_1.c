//
//
// TestCaseBasicDatabase_1.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Data/DC_BasicDatabase.h"
#include "TestCaseBasicDatabase_1.h"

#include <math.h>
#include <float.h>



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

   // Data structure to simulate the default table
   // NB: In order to avoid alignment problems, make sure that the
   //     table is aligned on a double word boundary
   // NB: The double array is oversized: the intended size of the 
    //    default table is 12 bytes.
   double shadowDefaultTable[3];
   unsigned int *defaultTable = (unsigned int*)shadowDefaultTable;

   // The following data simulate the default table of the basic database.
   // The table is assumed to contain three integer items.
   // NB: this test assumes that the compiler aligns the following three
   //     in continguous memory location.
   defaultTable[0] = 0xAABBCCDD;       // first parameter
   defaultTable[1] = 0x11223344;       // second parameter
   defaultTable[2] = 0x55667788;       // third parameter

   // The following constants represent the parameter identifiers of the
   // three entries in the default table
   const TD_DatabaseId PD_T1 = 0;
   const TD_DatabaseId PD_T2 = 4;
   const TD_DatabaseId PD_T3 = 8;

   // Data structure to simulate the operational table
   // NB: In order to avoid alignment problems, make sure that the
   //     table is aligned on a double word boundary
   double shadowOperationalTable[3];
   int *operationalTable = (int*)shadowOperationalTable;

   // Instantiate basic database
   DC_BasicDatabase *pDB = DC_BasicDatabase_new();
   ParameterDatabaseClass *pdc = PARAMETERDATABASE_GET_CLASS(pDB);
   CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pDB);

   // Verify correctness of class ID
   if (CC_RootObject_getClassId((CC_RootObject*)pDB) != ID_BASICDATABASE) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, "Wrong class ID");
		return;
	}

    // Check that database is not yet configured
    if (cc_roc->isObjectConfigured(pDB) != NOT_CONFIGURED) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Incorrect configuration status at creation");
        return;
    }

    // Set the table length and check correctness
    DC_BasicDatabase_setTableLength(pDB, 12);
    if (DC_BasicDatabase_getTableLength(pDB) != 12) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Incorrect table length");
        return;
    }

   // Complete configuration of the database
   DC_BasicDatabase_setDefaultTable(pDB, (char*)defaultTable);
   DC_BasicDatabase_setOperationalTable(pDB, (char*)operationalTable);
   pdc->reset(pDB);

   // Check that database is configured
	if (cc_roc->isObjectConfigured(pDB) != CONFIGURED) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
            "Incorrect configuration status after configuration was completed");
		return;
	}

   // Check that operational table was correctly initialized
   if (pdc->getParameterUnsignedInt(pDB, PD_T1) != defaultTable[0]) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Incorrect initialization of operational table");
		return;
	}
   if (pdc->getParameterUnsignedInt(pDB, PD_T2) != defaultTable[1]) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Incorrect initialization of operational table");
		return;
	}
   if (pdc->getParameterUnsignedInt(pDB, PD_T3) != defaultTable[2]) {
		 TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Incorrect initialization of operational table");
		return;
	}

   // Check the read/write services for all parameter types
    double d = 0.2;
    pdc->setParameterDouble(pDB, PD_T1, d);
    if (fabs(pdc->getParameterDouble(pDB, PD_T1)-d) > DBL_EPSILON) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                             "Incorrect write/read cycle for double parameter");
		return;
	}
    if (fabs((*(pdc->getParameterPointerDouble(pDB, PD_T1)))-d) > DBL_EPSILON) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                     "Incorrect getter method for pointer to double parameter");
		return;
	}

    float f = (float)0.4;
    pdc->setParameterFloat(pDB, PD_T2, f);
    if (fabs(pdc->getParameterFloat(pDB, PD_T2)-f) > FLT_EPSILON) {
	    TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                              "Incorrect write/read cycle for float parameter");
		return;
	}
    if (fabs((*(pdc->getParameterPointerFloat(pDB, PD_T2)))-f) > FLT_EPSILON) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                      "Incorrect getter method for pointer to float parameter");
		return;
	}

    unsigned int ui = 10;
    pdc->setParameterUnsignedInt(pDB, PD_T2, ui);
    if (pdc->getParameterUnsignedInt(pDB, PD_T2) != ui) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                       "Incorrect write/read cycle for unsigned int parameter");
		return;
	}
    if ((*(pdc->getParameterPointerUnsignedInt(pDB, PD_T2))) != ui) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
               "Incorrect getter method for pointer to unsigned int parameter");
		return;
	}

    int i = 20;
    pdc->setParameterInt(pDB, PD_T2, i);
    if (pdc->getParameterInt(pDB, PD_T2) != i) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Incorrect write/read cycle for int parameter");
		return;
	}
    if ((*(pdc->getParameterPointerInt(pDB, PD_T2))) != i) {
	    TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                        "Incorrect getter method for pointer to int parameter");
		return;
	}

    unsigned short us = 40;
    pdc->setParameterUnsignedShort(pDB, PD_T2, us);
    if (pdc->getParameterUnsignedShort(pDB, PD_T2) != us) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                     "Incorrect write/read cycle for unsigned short parameter");
		return;
	}
    if ((*(pdc->getParameterPointerUnsignedShort(pDB, PD_T2))) != us) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
             "Incorrect getter method for pointer to unsigned short parameter");
		return;
	}

    short s = 30;
    pdc->setParameterShort(pDB, PD_T2, s);
    if (pdc->getParameterShort(pDB, PD_T2) != s) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                              "Incorrect write/read cycle for short parameter");
		return;
	}
    if ((*(pdc->getParameterPointerShort(pDB, PD_T2))) != s) {
	    TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                      "Incorrect getter method for pointer to short parameter");
		return;
	}

    unsigned char uc = 4;
    pdc->setParameterUnsignedChar(pDB, PD_T2, uc);
    if (pdc->getParameterUnsignedChar(pDB, PD_T2) != uc) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                      "Incorrect write/read cycle for unsigned char parameter");
		return;
	}
    if ((*(pdc->getParameterPointerUnsignedChar(pDB, PD_T2))) != uc) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
              "Incorrect getter method for pointer to unsigned char parameter");
		return;
	}

    char c = 2;
    pdc->setParameterChar(pDB, PD_T2, c);
    if (pdc->getParameterUnsignedChar(pDB, PD_T2) != c) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Incorrect write/read cycle for char parameter");
		return;
	}
    if ((*(pdc->getParameterPointerChar(pDB, PD_T2))) != c) {
	    TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                       "Incorrect getter method for pointer to char parameter");
		return;
	}

    bool b = true;
    pdc->setParameterBool(pDB, PD_T2, b);
    if (pdc->getParameterBool(pDB, PD_T2) != b) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                            "Incorrect write/read cycle for boolean parameter");
		return;
	}
    if ((*(pdc->getParameterPointerBool(pDB, PD_T2))) != b) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                    "Incorrect getter method for pointer to boolean parameter");
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

TestCaseBasicDatabase_1* TestCaseBasicDatabase_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEBASICDATABASE_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
	                                                ID_BASICDATABASE*10+1,
                                                    "TestCaseBasicDatabase_1");

    return (TestCaseBasicDatabase_1*)obj;
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
    .name = TYPE_TESTCASEBASICDATABASE_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseBasicDatabase_1),
    .abstract = false,
    .class_size = sizeof(TestCaseBasicDatabase_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseBasicDatabase_1_register(void)
{
    type_register_static(&type_info);
}
