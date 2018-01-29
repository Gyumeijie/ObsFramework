  
//
//
// TestCaseSampleFullDataPool_1.h
//
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Data/DC_SampleFullDataPool.h"
#include "../Data/DC_DataItem.h"
#include "../System/DC_DummyObsClock.h"
#include "../FDIR/DC_NullProfile.h"
#include "../FDIR/DC_NullRecoveryAction.h"
#include "TestCaseSampleFullDataPool_1.h"
#include "../Utilities/TestCaseWithEvtCheck.h"

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

    // Variable to hold the number of events
    unsigned int nEvt = TestCaseWithEvtCheck_getNumberOfEvents(obj);

    // Variable to hold number of parameters in the data pool
    TD_DataPoolId numberOfPar = 8;

    // Variable to hold first identifier of a real-value parameter
    TD_DataPoolId firstRealId = 2;

    // Variable to hold first identifier of an integer-valued parameter
    TD_DataPoolId firstIntegerId = 1;

    // Instantiate datapool
    DC_SampleFullDataPool *pDP = DC_SampleFullDataPool_new();
    DC_SampleFullDataPoolClass *dc_sfdc = DC_SAMPLEFULLDATAPOOL_GET_CLASS(pDP);
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pDP);
    DataPoolClass *dpc = DATAPOOL_GET_CLASS(pDP);

    // Variable to hold maximum parameter identifier
    TD_DataPoolId maxParId;
    maxParId = 11;

    // Auxiliary variable to hold a data pool item identifier
    TD_DataPoolId id;
    id = 0;

    // Variable to hold the lowest illegal parameter id
    TD_DataPoolId lowestIllegalParId;
    lowestIllegalParId = (TD_DataPoolId)3;

    // Verify correctness of class ID
    if (CC_RootObject_getClassId((CC_RootObject*)pDP) != ID_SAMPLEFULLDATAPOOL)
    {    
         TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                 "Wrong class ID");
         return;
    }

    // Check default value of validity status.
    if (!dpc->isValid(pDP, 1))
    {    
         TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                 "Wrong default validity status on data item 1");
         return;
    }
    
    if (!dpc->isValid(pDP, 2))
    {    
         TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                 "Wrong default validity status on data item 2");
         return;
    }
    
    if (!dpc->isValid(pDP, 4))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong default validity status on data item 4");
        return;
    }
    
    if (!dpc->isValid(pDP, 5))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong default validity status on data item 5");
        return;
    }
    
    if (!dpc->isValid(pDP, 7))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong default validity status on data item 7");
        return;
    }
    
    if (!dpc->isValid(pDP, 8))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong default validity status on data item 8");
        return;
    }
    
    if (!dpc->isValid(pDP, 10))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong default validity status on data item 10");
        return;
    }
    
    if (!dpc->isValid(pDP, 11))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong default validity status on data item 11");
        return;
    }
    
    // Check that the data pool is not yet configured
    if (cc_roc->isObjectConfigured(pDP) != NOT_CONFIGURED)
    {   
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Incorrect configuration status at creation");
        return;
    }

    // Create and load dummy clock
    DC_DummyObsClock *pClk = DC_DummyObsClock_new();
    TD_ObsTime time = (TD_ObsTime)10;
    DC_DummyObsClock_setTime(pClk, time);
    DC_DummyObsClock_setCycle(pClk, 0);
    DC_SampleFullDataPool_setObsClock(pDP, (ObsClock*)pClk);
    if (DC_SampleFullDataPool_getObsClock(pDP) != (ObsClock*)pClk)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Incorrect OBS Clock");
        return;
    }

    // Check that the data pool is not yet configured
    if (cc_roc->isObjectConfigured(pDP) != NOT_CONFIGURED)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Incorrect configuration status at creation");
        return;
    }

    // Load monitoring profiles and check correctness of load operations
    DC_NullProfile *pNP = DC_NullProfile_new();  
    dc_sfdc->setMonitoringProfile(pDP, 1, (MonitoringProfile*)pNP);
    if (dpc->getMonitoringProfile(pDP, 1) != (MonitoringProfile*)pNP)
    {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Failure to read back monitoring profile");
        return;
    }
    
    dc_sfdc->setMonitoringProfile(pDP, 2, (MonitoringProfile*)pNP);
    if (dpc->getMonitoringProfile(pDP, 2) != (MonitoringProfile*)pNP)
    {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Failure to read back monitoring profile");
        return;
    }
    
    dc_sfdc->setMonitoringProfile(pDP, 4, (MonitoringProfile*)pNP);
    if (dpc->getMonitoringProfile(pDP, 4) != (MonitoringProfile*)pNP)
    {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Failure to read back monitoring profile");
        return;
    }
    
    dc_sfdc->setMonitoringProfile(pDP, 5, (MonitoringProfile*)pNP);
    if (dpc->getMonitoringProfile(pDP, 5)!= (MonitoringProfile*)pNP)
    {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Failure to read back monitoring profile");
        return;
    }
    
    dc_sfdc->setMonitoringProfile(pDP, 7, (MonitoringProfile*)pNP);
    if (dpc->getMonitoringProfile(pDP, 7) != (MonitoringProfile*)pNP)
    {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Failure to read back monitoring profile");
        return;
    }
    
    dc_sfdc->setMonitoringProfile(pDP, 8, (MonitoringProfile*)pNP);
    if (dpc->getMonitoringProfile(pDP, 8) != (MonitoringProfile*)pNP)
    {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Failure to read back monitoring profile");
        return;
    }
    
    dc_sfdc->setMonitoringProfile(pDP, 10, (MonitoringProfile*)pNP);
    if (dpc->getMonitoringProfile(pDP, 10) != (MonitoringProfile*)pNP)
    {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Failure to read back monitoring profile");
        return;
    }
    
    dc_sfdc->setMonitoringProfile(pDP, 11, (MonitoringProfile*)pNP);
    if (dpc->getMonitoringProfile(pDP, 11) != (MonitoringProfile*)pNP)
    {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Failure to read back monitoring profile");
        return;
    }
    
    // Load recovery actions and check correctness of load operations
    DC_NullRecoveryAction *pRA = DC_NullRecoveryAction_new();  
    dc_sfdc->setRecoveryAction(pDP, 1, (RecoveryAction*)pRA);
    if (dpc->getRecoveryAction(pDP, 1) != (RecoveryAction*)pRA)
    {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Failure to read back recovery action");
        return;
    }
    
    dc_sfdc->setRecoveryAction(pDP, 2, (RecoveryAction*)pRA);
    if (dpc->getRecoveryAction(pDP, 2) != (RecoveryAction*)pRA)
    {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Failure to read back recovery action");
        return;
    }
    
    dc_sfdc->setRecoveryAction(pDP, 4, (RecoveryAction*)pRA);
    if (dpc->getRecoveryAction(pDP, 4) != (RecoveryAction*)pRA)
    {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Failure to read back recovery action");
        return;
    }
    
    dc_sfdc->setRecoveryAction(pDP, 5, (RecoveryAction*)pRA);
    if (dpc->getRecoveryAction(pDP, 5) != (RecoveryAction*)pRA)
    {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Failure to read back recovery action");
        return;
    }
    
    dc_sfdc->setRecoveryAction(pDP, 7, (RecoveryAction*)pRA);
    if (dpc->getRecoveryAction(pDP, 7) != (RecoveryAction*)pRA)
    {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Failure to read back recovery action");
        return;
    }
    
    dc_sfdc->setRecoveryAction(pDP, 8, (RecoveryAction*)pRA);
    if (dpc->getRecoveryAction(pDP, 8) != (RecoveryAction*)pRA)
    {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Failure to read back recovery action");
        return;
    }
    
    dc_sfdc->setRecoveryAction(pDP, 10, (RecoveryAction*)pRA);
    if (dpc->getRecoveryAction(pDP, 10) != (RecoveryAction*)pRA)
    {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Failure to read back recovery action");
        return;
    }
    
    dc_sfdc->setRecoveryAction(pDP, 11, (RecoveryAction*)pRA);
    if (dpc->getRecoveryAction(pDP, 11) != (RecoveryAction*)pRA)
    {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Failure to read back recovery action");
        return;
    }
    
    // Check that the data pool is configured
    if (cc_roc->isObjectConfigured(pDP) != CONFIGURED)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Incorrect configuration status");
        return;
    }

    // Check data setting and getting services for the data pool item values
    // Do it for the real-value items first and then for the interger-valued items

    id = 2;
    dpc->setFloatValue(pDP, id,(TD_Float)id);
    if (fabs((float)(dpc->getFloatValue(pDP, id)-id)) > FLT_EPSILON)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Failure to read back data pool item with ID: id");
        return;
    }
    if (fabs((float)((*dpc->getPointerFloatValue(pDP, id))-id)) > FLT_EPSILON)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Failure to read back data pool item with ID: id");
        return;
    }
    id = 5;
    dpc->setFloatValue(pDP, id,(TD_Float)id);
    if (fabs((float)(dpc->getFloatValue(pDP, id)-id)) > FLT_EPSILON)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Failure to read back data pool item with ID: id");
        return;
    }
    if (fabs((float)((*dpc->getPointerFloatValue(pDP, id))-id)) > FLT_EPSILON)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Failure to read back data pool item with ID: id");
        return;
    }
    id = 8;
    dpc->setFloatValue(pDP, id, (TD_Float)id);
    if (fabs((float)(dpc->getFloatValue(pDP, id)-id)) > FLT_EPSILON)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Failure to read back data pool item with ID: id");
        return;
    }
    if (fabs((float)((*dpc->getPointerFloatValue(pDP, id))-id)) > FLT_EPSILON)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Failure to read back data pool item with ID: id");
        return;
    }
    id = 11;
    dpc->setFloatValue(pDP, id,(TD_Float)id);
    if (fabs((float)(dpc->getFloatValue(pDP, id)-id)) > FLT_EPSILON)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Failure to read back data pool item with ID: id");
        return;
    }
    if (fabs((float)((*dpc->getPointerFloatValue(pDP, id))-id)) > FLT_EPSILON)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Failure to read back data pool item with ID: id");
        return;
    }
    id = 1;
    dpc->setIntegerValue(pDP, id, (TD_Integer)id);
    if (dpc->getIntegerValue(pDP, id) != id)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Failure to read back data pool item with ID: id");
        return;
    }
    if ((*dpc->getPointerIntegerValue(pDP, id)) != id)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Failure to read back data pool item with ID: id");
        return;
    }
    id = 4;
    dpc->setIntegerValue(pDP, id, (TD_Integer)id);
    if (dpc->getIntegerValue(pDP, id) != id)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Failure to read back data pool item with ID: id");
        return;
    }
    if ((*dpc->getPointerIntegerValue(pDP, id)) != id)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Failure to read back data pool item with ID: id");
        return;
    }
    id = 7;
    dpc->setIntegerValue(pDP, id, (TD_Integer)id);
    if (dpc->getIntegerValue(pDP, id) != id)
    {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Failure to read back data pool item with ID: id");
        return;
    }
    if ((*dpc->getPointerIntegerValue(pDP, id)) != id)
    {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Failure to read back data pool item with ID: id");
        return;
    }
    id = 10;
    dpc->setIntegerValue(pDP, id, (TD_Integer)id);
    if (dpc->getIntegerValue(pDP, id) != id)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Failure to read back data pool item with ID: id");
        return;
    }
    if ((*dpc->getPointerIntegerValue(pDP, id)) != id)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Failure to read back data pool item with ID: id");
        return;
    }
    // Check the time stamp of a data pool item
    if (dpc->getTimeStamp(pDP, 1) != time)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong time stamp");
        return;
    }

    // Check the setting/getting of the validity status
    id = 1;
    dpc->setValidityStatus(pDP, id, false);
    if (dpc->isValid(pDP, id))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong validity status");
        return;
    }

    // Check illegal attempt to set the validity status
    if (TestCase_isNonNominalCheckAllowed(obj)) {
        dpc->setValidityStatus(pDP, 11+1, false);
        if (!verifyLatestEvent(obj, nEvt+1, EVT_ILLEGAL_DP_ACCESS)) return;
        nEvt = nEvt+1;
    }

    // Reset the data pool and check that all items are valid
    id = 1;
    dpc->setValidityStatus(pDP, id, false);
    dpc->reset(pDP);
    if (!dpc->isValid(pDP, id))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Reset failure");
        return;
    }


    // Check the back-up value mechanism  (for an integer-valued data pool item)
    id = 1;
    TD_Integer oldValue = dpc->getIntegerValue(pDP, id);
    dpc->setValidityStatus(pDP, id, false);
    dpc->setIntegerValue(pDP, id, (TD_Integer)(oldValue+1));
    if (dpc->getIntegerValue(pDP, id) != oldValue)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Back-up value failure");
        return;
    }
    if (DC_DataItem_getIntegerValue(dpc->getDataItem(pDP, id)) != oldValue)
    {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Back-up value failure");
        return;
    }
    dpc->setValidityStatus(pDP, id,true);
    dpc->setIntegerValue(pDP, id, (TD_Integer)(oldValue+1));
    if (dpc->getIntegerValue(pDP, id) != (oldValue+1))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Back-up value failure");
        return;
    }
    if (DC_DataItem_getIntegerValue(dpc->getDataItem(pDP, id)) != (oldValue+1))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Back-up value failure");
        return;
    }

    // Check the back-up value mechanism  (for a real-valued data pool item)
    id = 2;
    TD_Float fOldValue = dpc->getFloatValue(pDP, id);
    dpc->setValidityStatus(pDP, id, false);
    dpc->setFloatValue(pDP, id, (TD_Float)(fOldValue+1.0));
    if (fabs((float)(dpc->getFloatValue(pDP, id)-fOldValue)) > FLT_EPSILON)
    {      TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                   "Back-up value failure");
           return;
    }
    dpc->setValidityStatus(pDP, id, true);
    dpc->setFloatValue(pDP, id, (TD_Float)(fOldValue+1.0));
    if (fabs((float)(dpc->getFloatValue(pDP, id)-(fOldValue+1.0))) > FLT_EPSILON)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Back-up value failure");
        return;
    }

    // Check the iteration service
    TD_DataPoolId counter = 0;
    for (TD_DataPoolId i=dpc->firstIdentifier(pDP); 
             !dpc->isLastIdentifier(pDP); 
                 i=dpc->nextIdentifier(pDP)) {
        counter++;
        dpc->setValidityStatus(pDP, i, false); // dummy call -- just to exercise data pool access
    }
    if (counter != numberOfPar)
    {   
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Error in data pool iteration");
        return;
    }

    if (!dpc->isFloat(pDP, firstRealId) || dpc->isInteger(pDP, firstRealId))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Error in type checking service");
        return;
    }
    if (!dpc->isInteger(pDP, firstIntegerId) || dpc->isFloat(pDP, firstIntegerId))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Error in type checking service");
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

TestCaseSampleFullDataPool_1* TestCaseSampleFullDataPool_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASESAMPLEFULLDATAPOOL_1);

    TESTCASEWITHEVTCHECK_GET_CLASS(obj)->post_init((TestCaseWithEvtCheck*)obj,
                                                   ID_SAMPLEFULLDATAPOOL*10+1,
                                              "TestCaseSampleFullDataPool_1"); 

    return (TestCaseSampleFullDataPool_1*)obj;
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
    .name = TYPE_TESTCASESAMPLEFULLDATAPOOL_1,
    .parent = TYPE_TESTCASEWITHEVTCHECK,
    .instance_size = sizeof(TestCaseSampleFullDataPool_1),
    .abstract = false,
    .class_size = sizeof(TestCaseSampleFullDataPool_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseSampleFullDataPool_1_register(void)
{
    type_register_static(&type_info);
}
