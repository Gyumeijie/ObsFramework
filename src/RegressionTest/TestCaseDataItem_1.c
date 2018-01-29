//
//
// TestCaseDataItem_1.c
//
//
// Change Record:

#include <math.h>
#include <float.h>

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/TestCompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/TestConstants.h"
#include "../Data/DC_DataItem.h"
#include "TestCaseDataItem_1.h"



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
	TD_Float       fv;
	TD_Integer     iv;
	DC_DataItem   *pFDI = DC_DataItem_new(&fv, DI_FLOAT);
	DC_DataItem   *pIDI = DC_DataItem_new(&iv, DI_INT);

	// Check the working of the getter methods
	iv = (TD_Integer)41;
	if (DC_DataItem_getIntegerValue(pIDI) != (TD_Integer)41) {
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, "getInteger() failed");
       return;
     }

	fv = (TD_Float)41;
	if (DC_DataItem_getFloatValue(pFDI) != (TD_Float)41) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, "getFloat() failed");
		return;
	}

	// Verify the setter methods
	DC_DataItem_setIntegerValue(pIDI, (TD_Integer)51);
	if (iv != (TD_Integer)51) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, "setInteger() failed");
		return;
	}

    DC_DataItem_setFloatValue(pFDI, (TD_Float)50);
	if (fv != (TD_Float)50) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, "setFloat() failed");
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

TestCaseDataItem_1* TestCaseDataItem_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEDATAITEM_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                    ID_DATAITEM*10+1,
                                                    "TestCaseDataItem_1");

    return (TestCaseDataItem_1*)obj;
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
    .name = TYPE_TESTCASEDATAITEM_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseDataItem_1),
    .abstract = false,
    .class_size = sizeof(TestCaseDataItem_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseDataItem_1_register(void)
{
    type_register_static(&type_info);
}
