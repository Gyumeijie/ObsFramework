//
//
// TestCaseDummyDataPool_1.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Data/DC_BasicDatabase.h"
#include "../FDIR/RecoveryAction.h"
#include "../FDIR/MonitoringProfile.h"
#include "../Data/DC_DummyDataPool.h"
#include "TestCaseDummyDataPool_1.h"



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
   // Instantiate dummy datapool
   DC_DummyDataPool* pDP = DC_DummyDataPool_new();

   // Check class identifier
   if (CC_RootObject_getClassId((CC_RootObject*)pDP) != ID_DUMMYDATAPOOL) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, "Wrong class ID");
		return;
	}

   // Check size and value of data pool item
   if (DC_BasicDataPool_getDataPoolSize((void*)pDP) != sizeof(TD_Integer)) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Incorrect size of the data pool");
		return;
	}

    DataPoolClass *dpc = DATAPOOL_GET_CLASS(pDP);
    if (dpc->getIntegerValue(pDP, 0) != (TD_Integer)0) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Incorrect value of data pool item");
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

TestCaseDummyDataPool_1* TestCaseDummyDataPool_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEDUMMYDATAPOOL_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                    ID_DUMMYDATAPOOL*10+1,
                                                    "TestCaseDummyDataPool_1");

    return (TestCaseDummyDataPool_1*)obj;
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
    .name = TYPE_TESTCASEDUMMYDATAPOOL_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseDummyDataPool_1),
    .abstract = false,
    .class_size = sizeof(TestCaseDummyDataPool_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseDummyDataPool_1_register(void)
{
    type_register_static(&type_info);
}
