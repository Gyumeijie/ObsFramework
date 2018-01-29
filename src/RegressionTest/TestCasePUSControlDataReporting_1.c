//
//
// TestCasePUSControlDataReporting_1.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "../Telecommand/DC_PUSControlDataReporting.h"
#include "../Telemetry/DC_PUSDataReportingPacket.h"
#include "../Telemetry/CC_TelemetryPacketFactory.h"
#include "../Data/DC_SampleFullDataPool.h"
#include "../Utilities/TestCaseWithFactories.h"
#include "TestCasePUSControlDataReporting_1.h"

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

    // Retrieve the packet factory
    CC_TelemetryPacketFactory *pFct = CC_TelemetryPacketFactory_getInstance();
    CC_RootObjectClass *cc_roc;

    // Allocate the two telemetry packets
    unsigned short defPacketSize = PUS_DRP_DEF_BUF_SIZE_SMALL - 2;
    unsigned int valBufferSize = PUS_DRP_VAL_BUF_SIZE_SMALL - 2;
    DC_PUSDataReportingPacket *pTMP_a, *pTMP_b;

    pTMP_a = CC_TelemetryPacketFactory_allocatePUSDataReportingPacket(pFct, 
                                              defPacketSize, valBufferSize, 0);
    pTMP_b = CC_TelemetryPacketFactory_allocatePUSDataReportingPacket(pFct, 
                                              defPacketSize, valBufferSize, 0);

    // Construct the packet
    TD_SID sid_a = 12;
    TD_SID sid_b = 13;
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

    // Create the telecommand 
    DC_PUSControlDataReporting *pTC = DC_PUSControlDataReporting_new();
    TelecommandClass *tc = TELECOMMAND_GET_CLASS(pTC);

    // Check the value of the class identifier
    if (CC_RootObject_getClassId((CC_RootObject*)pTC) != ID_PUSCONTROLDATAREPORTING)
    { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong class identifier");
        return;
    }

    // Check configuration status
    if (cc_roc->isObjectConfigured(pTC))
    { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong configuration status");
        return;
    }
    
    // Set the number of SIDs and check success
    DC_PUSControlDataReporting_setMaxNumberSID(pTC, 2);
    if (tc->getNumberOfRawData(pTC) != (2*sizeof(TD_SID)+1))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong configuration value");
        return;
    }

    // Complete configuration of telecommand and check configuration status
    TD_TelecommandSource tcSource = 1;
    TD_TelecommandId tcId = 2;
    tc->setSource(pTC, tcSource);
    tc->setSubType(pTC, PUS_ST_DATA_REP_ENB_HK);
    tc->setTelecommandId(pTC, tcId);
    Telecommand_setTimeTag((Telecommand*)pTC, 0);
    cc_roc = CC_ROOTOBJECT_GET_CLASS(pTC);
    if (!cc_roc->isObjectConfigured(pTC))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,  
                                "Wrong configuration status");
        return;
    }
    
    // set up data structures to hold telecommand raw data
    unsigned int maxNSID = 3;
    TD_SID *temp = g_malloc(sizeof(TD_SID)*maxNSID+1);
    TD_SID *sid = &temp[1];
    unsigned char *rawData = ((unsigned char*)sid) - 1;

    // Load raw data in telecommandand 
    rawData[0] = 1;
    sid[0] = sid_a;
    for (unsigned int i=0; i<(1+1*sizeof(TD_SID)); i++) {
        tc->setRawData(pTC, i, rawData[i]);
    }
    tc->setSubType(pTC, PUS_ST_DATA_REP_ENB_HK);

    // Check validity
    if (!tc->isValid(pTC))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong validity status");
        return;
    }

    // Execute telecommand and check success
    TD_ActionOutcome ao = PunctualAction_execute((PunctualAction*)pTC);
    if (ao != ACTION_SUCCESS)
    { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong action outcome");
        return;
    }
    if (!DC_PUSDataReportingPacket_isEnabled(pTMP_a))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong enable status");
        return;
    }
    
    // Load raw data in telecommandand and configure telecommand
    rawData[0] = 1;
    sid[0] = sid_a;
    for (unsigned int i=0; i<(1+1*sizeof(TD_SID)); i++) { 
        tc->setRawData(pTC, i, rawData[i]);
    }
    tc->setSubType(pTC, PUS_ST_DATA_REP_DIS_HK);

    // Check validity
    if (!tc->isValid(pTC))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong validity status");
        return;
    }

    // Execute telecommand and check success
    ao = PunctualAction_execute((PunctualAction*)pTC);
    if (ao != ACTION_SUCCESS)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong action outcome");
        return;
    }
    if (DC_PUSDataReportingPacket_isEnabled(pTMP_a))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong enable status");
        return;
    }

    // Load raw data in telecommandand and configure telecommand
    rawData[0] = 2;
    sid[0] = sid_a;
    sid[1] = sid_b;
    for (unsigned int i=0; i<(1+2*sizeof(TD_SID)); i++) {
        tc->setRawData(pTC, i, rawData[i]);
    }
    tc->setSubType(pTC, PUS_ST_DATA_REP_ENB_HK);

    // Check validity
    if (!tc->isValid(pTC))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong validity status");
        return;
    }

    // Execute telecommand and check success
    ao = PunctualAction_execute((PunctualAction*)pTC);
    if (ao != ACTION_SUCCESS)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong action outcome");
        return;
    }
    if ((!DC_PUSDataReportingPacket_isEnabled(pTMP_a)) ||
        (!DC_PUSDataReportingPacket_isEnabled(pTMP_b)))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong enable status");
        return;
    }

    // Load illegal raw data in telecommandand and configure telecommand
    if (TestCase_isNonNominalCheckAllowed(obj)) {
        rawData[0] = 3;
        sid[0] = sid_a;
        sid[1] = sid_b;
        sid[2] = sid_a;
        for (unsigned int i=0; i<(1+3*sizeof(TD_SID)); i++) { 
            tc->setRawData(pTC, i, rawData[i]);
        }
        tc->setSubType(pTC, PUS_ST_DATA_REP_ENB_HK);

        // Check validity
        if (tc->isValid(pTC) || 
           (tc->getValidityCheckCode(pTC) != VC_TOO_MANY_RAW_DATA))
        { 
            TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                     "Wrong validity status");
            return;
        }
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
           (tc->getValidityCheckCode(pTC) != VC_TOO_MANY_RAW_DATA))
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

    // Load raw data in telecommandand and configure telecommand
    rawData[0] = 2;
    sid[0] = sid_a + 10;
    sid[1] = sid_b;
    for (unsigned int i=0; i<(1+2*sizeof(TD_SID)); i++) {
        tc->setRawData(pTC, i, rawData[i]);
    }
    tc->setSubType(pTC, PUS_ST_DATA_REP_DIS_HK);

    // Check validity
    if (!tc->isValid(pTC))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong validity status");
        return;
    }

    // Execute telecommand and check success
    ao = PunctualAction_execute((PunctualAction*)pTC);
    if (ao != ACTION_FAILURE)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong action outcome");
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

TestCasePUSControlDataReporting_1* TestCasePUSControlDataReporting_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEPUSCONTROLDATAREPORTING_1);

    TESTCASEWITHEVTCHECK_GET_CLASS(obj)->post_init((TestCaseWithEvtCheck*)obj,
                                              ID_PUSCONTROLDATAREPORTING*10+1,
                                         "TestCasePUSControlDataReporting_1"); 

    return (TestCasePUSControlDataReporting_1*)obj;
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
    .name = TYPE_TESTCASEPUSCONTROLDATAREPORTING_1,
    .parent = TYPE_TESTCASEWITHFACTORIES,
    .instance_size = sizeof(TestCasePUSControlDataReporting_1),
    .abstract = false,
    .class_size = sizeof(TestCasePUSControlDataReporting_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCasePUSControlDataReporting_1_register(void)
{
    type_register_static(&type_info);
}
