//
//
// TestCaseBasicDataPool_1.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Data/DC_BasicDatabase.h"
#include "../FDIR/RecoveryAction.h"
#include "../FDIR/MonitoringProfile.h"
#include "../Data/DC_BasicDataPool.h"
#include "../Data/DC_DataItem.h"
#include "TestCaseBasicDataPool_1.h"

#include <math.h>
#include <float.h>



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Execute the test case. See class comment for details.
 * Warining: When compiled without --std=c99, the following condition is
 * false, but with --std=c99 it is true. So to work in c99, we multiply
 * FLT_EPSILON and DBL_EPSILON with 100, which will make it work and doesn't
 * have much effect on the assertion.
 */	
static void runTestCase(void *obj)
{

   // Data to be written and read back from the data pool together with their identifiers.
   TD_Float f = (TD_Float)2.0;
   TD_Integer i = (TD_Integer)3;
   TD_DataPoolId f_id = 0;
   TD_DataPoolId i_id = sizeof(TD_Float);

   // Instantiate basic datapool
   DC_BasicDataPool* pDP = DC_BasicDataPool_new();
   CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pDP);
   DataPoolClass *dpc = DATAPOOL_GET_CLASS(pDP);

   // Verify correctness of class ID
   if (CC_RootObject_getClassId((CC_RootObject*)pDP) != ID_BASICDATAPOOL) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, "Wrong class ID");
		return;
	}

   // Check that datapool is not yet configured
    
   if (cc_roc->isObjectConfigured(pDP) != NOT_CONFIGURED) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Incorrect configuration status at creation");
		return;
	}

   // Set data pool size and check correctness
   TD_DataPoolId size = sizeof(TD_Integer)+sizeof(TD_Float);
   DC_BasicDataPool_setDataPoolSize(pDP, size);
   if (DC_BasicDataPool_getDataPoolSize(pDP) != size) {
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Incorrect value for the data pool size");
       return;
   }

   // Check that database is configured
   if (cc_roc->isObjectConfigured(pDP) != CONFIGURED) {
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
           "Incorrect configuration status after configuration was completed");
       return;
   }

   // Check retrieval of data item attribute
   DC_DataItem* pDI = dpc->getDataItem(pDP, 3);
   if (DC_DataItem_getIntegerValue(pDI) != 0) {
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Incorrect data item attribute");
	   return;
   }

   // Check retrieval of time stamp attribute
   if (dpc->getTimeStamp(pDP, 2) != 0) {
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Incorrect time stamp attribute");
	   return;
   }

   // Check retrieval of validity attribute
   if (!dpc->isValid(pDP, 2)) {
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Incorrect validity attribute");
	   return;
   }

   // Check type checking services
   if ((!dpc->isFloat(pDP, 7)) || (!dpc->isInteger(pDP, 7))) {
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Incorrect type checking services");
	   return;
   }

   // Check iteration methods
   if ((dpc->firstIdentifier(pDP)!=0) ||
       (dpc->nextIdentifier(pDP)!=0)  ||
       (!dpc->isLastIdentifier(pDP))) {
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                              "Incorrect iteration services");
	   return;
   }

   // Check retrieval of monitoring profile attribute
   MonitoringProfile *mp = dpc->getMonitoringProfile(pDP, 2);
   if (CC_RootObject_getClassId((CC_RootObject*)mp) != ID_NULLPROFILE) {
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Incorrect monitoring profile attribute");
	    return;
   }

   // Check retrieval of recovery action attribute
   RecoveryAction *ra = dpc->getRecoveryAction(pDP, 3);
   if (CC_RootObject_getClassId((CC_RootObject*)ra) != ID_NULLRECOVERYACTION) {
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Incorrect monitoring profile attribute");
	   return;
   }

   // Call reset and validity setter methods (just to show that they can be called without
   // crashing the system)
   dpc->reset(pDP);
   dpc->setValidityStatus(pDP, 0, true);

   // Set and read float value and check correctness
   dpc->setFloatValue(pDP, f_id, f);
   if (fabs(dpc->getFloatValue(pDP, f_id)-f)>100*FLT_EPSILON) {
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Incorrect write/read cycle for float value");
       return;
   }

   // Set and read integer value and check correctness
   dpc->setIntegerValue(pDP, i_id, i);
   if (dpc->getIntegerValue(pDP, i_id)!=i) {
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Incorrect write/read cycle for integer value");
       return;
   }

   // Check pointer access for float values
   TD_Float tmpFloatVal = *(dpc->getPointerFloatValue(pDP, f_id));
   if (fabs(tmpFloatVal-f)>100*FLT_EPSILON) {
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Incorrect pointer access to float value");
       return;
   }

   // Check pointer access for integer values
   if ((*(dpc->getPointerIntegerValue(pDP, i_id)))!=i) {
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Incorrect pointer access to integer value");
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

TestCaseBasicDataPool_1* TestCaseBasicDataPool_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEBASICDATAPOOL_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                    ID_BASICDATAPOOL*10+1,
                                                    "TestCaseBasicDataPool_1"); 
    return (TestCaseBasicDataPool_1*)obj;
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
    .name = TYPE_TESTCASEBASICDATAPOOL_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseBasicDataPool_1),
    .abstract = false,
    .class_size = sizeof(TestCaseBasicDataPool_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseBasicDataPool_1_register(void)
{
    type_register_static(&type_info);
}
