//
//
// TestCasePUSClearDataReporting_1.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "../Telecommand/DC_PUSClearDataReporting.h"
#include "../Telemetry/DC_PUSDataReportingPacket.h"
#include "../Telemetry/CC_TelemetryPacketFactory.h"
#include "../Telemetry/DC_PUSTelemetryModeManager.h"
#include "../Data/DC_SampleFullDataPool.h"
#include "../Utilities/TestCasePUSFull.h"
#include "TestCasePUSClearDataReporting_1.h"

#include <assert.h>
#include <string.h>



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

    // Recover the packet factory
    CC_TelemetryPacketFactory *pFct = CC_TelemetryPacketFactory_getInstance();
    CC_RootObjectClass *cc_roc;

    // Recover the PUS telemetry mode manager 
    DC_PUSTelemetryModeManager *pTMM = TestCasePUSFull_getTelemetryModeManager(obj);

    // Allocate the two telemetry packets
    unsigned short defPacketSize = PUS_DRP_DEF_BUF_SIZE_SMALL - 2;
    unsigned int valBufferSize = PUS_DRP_VAL_BUF_SIZE_SMALL - 2;
    DC_PUSDataReportingPacket *pTMP_a, *pTMP_b;

    pTMP_a = CC_TelemetryPacketFactory_allocatePUSDataReportingPacket(pFct, 
                                              defPacketSize, valBufferSize, 0);
    pTMP_b = CC_TelemetryPacketFactory_allocatePUSDataReportingPacket(pFct,
                                              defPacketSize, valBufferSize, 0);
    if ((pTMP_a == pNULL) || (pTMP_b == pNULL))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Failure to allocate telemetry packets");
     	return;
    }

    // Construct the packet
    TD_SID sid_a = 121;
    TD_SID sid_b = 131;
    TD_PUSCollectionInterval collectionInterval = 1;
    TD_PUSNumberOfParameters NPAR1 = 1;
    TD_DataPoolId par1 = 1;

    unsigned char *packet = g_malloc(sizeof(unsigned char)*defPacketSize);
    unsigned int offset = 0;
    memcpy(packet+offset, &sid_a, sizeof(TD_SID));
    offset += sizeof(TD_SID);
    memcpy(packet+offset, &collectionInterval, sizeof(TD_PUSCollectionInterval));
    offset += sizeof(TD_PUSCollectionInterval);
    memcpy(packet+offset, &NPAR1, sizeof(TD_PUSNumberOfParameters));
    offset += sizeof(TD_PUSNumberOfParameters);
    memcpy(packet+offset, &par1, sizeof(TD_DataPoolId));
    offset += sizeof(TD_DataPoolId);

    assert(offset < defPacketSize);

    DC_PUSDataReportingPacketClass *oc = GET_CLASS(TYPE_DC_PUSDATAREPORTINGPACKET);
    TelemetryPacketClass *tpc = TELEMETRYPACKET_CLASS(oc);
    cc_roc = CC_ROOTOBJECT_CLASS(oc);

    // Configure the two packets and check that they are configured
    tpc->setSubType(pTMP_a, PUS_ST_DATA_REP_PAR_HK_REP);
    tpc->setTimeTag(pTMP_a, 0);
    if (!cc_roc->isObjectConfigured(pTMP_a))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong configuration status");
     	return;
    }
    tpc->setSubType(pTMP_b, PUS_ST_DATA_REP_PAR_HK_REP);
    tpc->setTimeTag(pTMP_b, 0);
    if (!cc_roc->isObjectConfigured(pTMP_b))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong configuration status");
     	return;
    }

    // Load the packet definitions for the first TM packet
    for (unsigned short i=0; i<offset; i++) {
        DC_PUSDataReportingPacket_setDefinitionBuffer(pTMP_a, i, packet[i]);
    }

    // Load the packet definitions for the second TM packet
    memcpy(packet, &sid_b, sizeof(TD_SID));
    for (unsigned short i=0; i<offset; i++) {
        DC_PUSDataReportingPacket_setDefinitionBuffer(pTMP_b, i, packet[i]);
    }

    // Load the second packet in the TM mode manager and check success
    DC_PUSTelemetryModeManager_loadPacket(pTMM, pTMP_b);
    if (!DC_PUSTelemetryModeManager_isSIDLoaded(pTMM, sid_b))
    {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "TM packet is not loaded");
        return;
    }

    // Create the telecommand 
    DC_PUSClearDataReporting *pTC = DC_PUSClearDataReporting_new();
    TelecommandClass *tc = TELECOMMAND_GET_CLASS(pTC);

    // Check the value of the class identifier
    if (CC_RootObject_getClassId((CC_RootObject*)pTC) != ID_PUSCLEARDATAREPORTING)
    { 
         TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                 "Wrong class identifier");
         return;
    }

    // Check configuration status
    cc_roc = CC_ROOTOBJECT_GET_CLASS(pTC);
    if (cc_roc->isObjectConfigured(pTC))
    {
         TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                 "Wrong configuration status");
         return;
    }
    
    // Set the maximum number of SIDs and check success
    DC_PUSClearDataReporting_setMaxNumberSID(pTC, 2);
    // Check this in test case for control data reporting
    if (tc->getNumberOfRawData(pTC) != (2*sizeof(TD_SID)+1))
    {
         TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                 "Wrong configuration value");
         return;
    }

    // Load TM mode manager and check success
    DC_PUSClearDataReporting_setPUSTelemetryModeManager(pTC, pTMM);
    if (DC_PUSClearDataReporting_getPUSTelemetryModeManager(pTC) != pTMM)
    { 
         TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,  
                                 "Wrong configuration value");
         return;
    }

    // Complete configuration of telecommand and check configuration status
    TD_TelecommandSource tcSource = 1;
    TD_TelecommandId tcId = 2;
    tc->setSource(pTC, tcSource);
    tc->setSubType(pTC, PUS_ST_DATA_REP_CLR_HK);
    tc->setTelecommandId(pTC, tcId);
    Telecommand_setTimeTag((Telecommand*)pTC, 0);
    if (!cc_roc->isObjectConfigured(pTC))
    {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong configuration status");
        return;
    }
    
    // set up data structures to hold telecommand raw data
    unsigned int maxNSID = 2;
    TD_SID *temp = g_malloc(sizeof(TD_SID)*maxNSID+1);
    TD_SID* sid = &temp[1];
    unsigned char *rawData = ((unsigned char*)sid) - 1;

    // Load raw data in telecommandand 
    rawData[0] = 2;
    sid[0] = sid_a;
    sid[1] = sid_b;
    for (unsigned int i=0; i<(1+2*sizeof(TD_SID)); i++) {
        tc->setRawData(pTC, i, rawData[i]);
    }

    // Check validity
    if (!tc->isValid(pTC))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong validity status");
        return;
    }

    // Execute telecommand and check success
    if (!TelemetryPacket_isInUse((TelemetryPacket*)pTMP_a))
    {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong enable status");
        return;
    }
    if (!TelemetryPacket_isInUse((TelemetryPacket*)pTMP_b))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong enable status");
        return;
    }
    if (!DC_PUSTelemetryModeManager_isSIDLoaded(pTMM, sid_b))
    {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong load status");
        return;
    }

    TD_ActionOutcome ao = PunctualAction_execute((PunctualAction*)pTC);
    if (ao != ACTION_SUCCESS)
    {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong action outcome");
        return;
    }
    if (TelemetryPacket_isInUse((TelemetryPacket*)pTMP_a))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong enable status");
        return;
    }
    if (TelemetryPacket_isInUse((TelemetryPacket*)pTMP_b))
    {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,  
                                "Wrong enable status");
        return;
    }
    if (DC_PUSTelemetryModeManager_isSIDLoaded(pTMM, sid_b))
    {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong enable status");
        return;
    }
    
    // Execute telecommand again and check that now it fails
    ao = PunctualAction_execute((PunctualAction*)pTC);
    if (ao != ACTION_FAILURE)
    {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong action outcome");
        return;
    }

    // Try to load too many SIDs and check validity 
    rawData[0] = 3;
    sid[0] = sid_a;
    sid[1] = sid_b;
    for (unsigned int i=0; i<(1+2*sizeof(TD_SID)); i++) {
        tc->setRawData(pTC, i, rawData[i]);
    }

    // Check validity
    if (tc->isValid(pTC) || 
        (tc->getValidityCheckCode(pTC) != VC_TOO_MANY_SIDS))
    {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong validity status");
        return;
    }

    // Try to load too many raw data and check validity 
    if (TestCase_isNonNominalCheckAllowed(obj)) {
        rawData[0] = 2;
        sid[0] = sid_a;
        sid[1] = sid_b;
        for (unsigned int i=0; i<(2+2*sizeof(TD_SID)); i++) {
            tc->setRawData(pTC, i, rawData[i]);
        }

        // Check validity
        if (tc->isValid(pTC) || 
            (tc->getValidityCheckCode(pTC)!=VC_TOO_MANY_RAW_DATA))
        {    
            TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                    "Wrong validity status");
            return;
        }
    }

    // Try to load an inconsistent number of raw data and check validity 
    rawData[0] = 2;
    sid[0] = sid_a;
    sid[1] = sid_b;
    for (unsigned int i=0; i<(2*sizeof(TD_SID)); i++) {
        tc->setRawData(pTC, i, rawData[i]);
    }

    // Check validity
    if (tc->isValid(pTC) ||
        (tc->getValidityCheckCode(pTC) != VC_INCONSISTENT_RAW_DATA))
    {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong validity status");
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

TestCasePUSClearDataReporting_1* TestCasePUSClearDataReporting_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEPUSCLEARDATAREPORTING_1);

    TESTCASEWITHEVTCHECK_GET_CLASS(obj)->post_init((TestCaseWithEvtCheck*)obj,
                                                ID_PUSCLEARDATAREPORTING*10+1,
                                           "TestCasePUSClearDataReporting_1"); 

    return (TestCasePUSClearDataReporting_1*)obj;
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
    .name = TYPE_TESTCASEPUSCLEARDATAREPORTING_1,
    .parent = TYPE_TESTCASEPUSFULL,
    .instance_size = sizeof(TestCasePUSClearDataReporting_1),
    .abstract = false,
    .class_size = sizeof(TestCasePUSClearDataReporting_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCasePUSClearDataReporting_1_register(void)
{
    type_register_static(&type_info);
}
