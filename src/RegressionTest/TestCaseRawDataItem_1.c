//
//
// TestCaseRawDataItem_1.c
//
//
// Change Record:

#include <math.h>
#include <float.h>

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/TestCompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/TestConstants.h"
#include "../Data/DC_RawDataItem.h"
#include "../Data/DC_DataItem.h"
#include "TestCaseRawDataItem_1.h"



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
	char           charVal;
	unsigned char  uCharVal;
	short          shortVal;
	unsigned short uShortVal;
	int            intVal;
	unsigned int   uIntVal;
	float          floatVal;
	double         doubleVal;
	DC_RawDataItem *pCharData   = DC_RawDataItem_new(&charVal);
	DC_RawDataItem *pUCharData  = DC_RawDataItem_new(&uCharVal);
	DC_RawDataItem *pShortData  = DC_RawDataItem_new(&shortVal);
	DC_RawDataItem *pUShortData = DC_RawDataItem_new(&uShortVal);
	DC_RawDataItem *pIntData    = DC_RawDataItem_new(&intVal);
	DC_RawDataItem *pUIntData   = DC_RawDataItem_new(&uIntVal);
	DC_RawDataItem *pFloatData  = DC_RawDataItem_new(&floatVal);
	DC_RawDataItem *pDoubleData = DC_RawDataItem_new(&doubleVal);

	// Verify the working of the getter methods
	charVal = -41;
	if (DC_RawDataItem_getChar(pCharData) != -41) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, "getChar() failed");
		return;
	}

	uCharVal = 42;
	if (DC_RawDataItem_getUnsignedChar(pUCharData) != 42) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE ,"getUnsignedChar() failed");
		return;
	}

	shortVal = -43;
	if (DC_RawDataItem_getShort(pShortData) != -43) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, "getShort() failed");
		return;
	}

	uShortVal = 44;
	if (DC_RawDataItem_getUnsignedShort(pUShortData) != 44) {
		TestCase_setTestResult((TestCase*)obj,TEST_FAILURE, "getUnsignedShort() failed");
		return;
	}

	intVal = -45;
	if (DC_RawDataItem_getInt(pIntData) != -45) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, "getInt() failed");
		return;
	}

	uIntVal = 46;
	if (DC_RawDataItem_getUnsignedInt(pUIntData) != 46) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, "getUnsignedInt() failed");
		return;
	}
        
    /**
     * Warining: When compiled without --std=c99, the following condition is 
     * false, but with --std=c99 it is true. So to work in c99, we multiply 
     * FLT_EPSILON and DBL_EPSILON with 100, which will make it work and doesn't
     * have much effect on the assertion.
     */
	floatVal = -47.48f;
	if (fabsf(DC_RawDataItem_getFloat(pFloatData)+47.48f) >= 100*FLT_EPSILON) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, "getFloat() failed");
		return;
	}

	doubleVal = 49.50;
	if (fabs(DC_RawDataItem_getDouble(pDoubleData)-49.50) >= 100*DBL_EPSILON) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, "getDouble() failed");
		return;
	}

	// Verify the setter methods
	DC_RawDataItem_setChar(pCharData, -51);
	if (charVal != -51) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, "setChar() failed");
		return;
	}

	DC_RawDataItem_setUnsignedChar(pUCharData, 52);
	if (uCharVal != 52) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, "setUnsignedChar() failed");
		return;
	}

	DC_RawDataItem_setShort(pShortData, -53);
	if (shortVal != -53) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, "setShort() failed");
		return;
	}

	DC_RawDataItem_setUnsignedShort(pUShortData, 54);
	if (uShortVal != 54) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, "setUnsignedShort() failed");
		return;
	}

	DC_RawDataItem_setInt(pIntData, -55);
	if (intVal != -55) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, "setInt() failed");
		return;
	}

	DC_RawDataItem_setUnsignedInt(pUIntData, 56);
	if (uIntVal != 56) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, "setUnsignedInt() failed");
		return;
	}

	DC_RawDataItem_setFloat(pFloatData, -57.58f);
	if (fabsf(floatVal+57.58f) >= 100*FLT_EPSILON) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, "setFloat() failed");
		return;
	}

	DC_RawDataItem_setDouble(pDoubleData, 59.60);
	if (fabs(doubleVal-59.60) >= 100*DBL_EPSILON) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, "setDouble() failed");
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

TestCaseRawDataItem_1* TestCaseRawDataItem_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASERAWDATAITEM_1);
    
    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                    ID_RAWDATAITEM*10+1,
                                                    "TestCaseRawDataItem_1"); 

    return (TestCaseRawDataItem_1*)obj;
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
    .name = TYPE_TESTCASERAWDATAITEM_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseRawDataItem_1),
    .abstract = false,
    .class_size = sizeof(TestCaseRawDataItem_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseRawDataItem_1_register(void)
{
    type_register_static(&type_info);
}
