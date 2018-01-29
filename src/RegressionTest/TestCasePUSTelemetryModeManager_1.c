//
//
// TestCasePUSTelemetryModeManager_1.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "../Telemetry/DC_PUSTelemetryModeManager.h"
#include "../Telemetry/DC_PUSDataReportingPacket.h"
#include "../Telemetry/CC_TelemetryPacketFactory.h"
#include "../Utilities/TestCaseWithFactories.h"
#include "TestCasePUSTelemetryModeManager_1.h"

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
    CC_RootObjectClass *cc_roc = pNULL;
    TelemetryPacketClass *tpc = pNULL;
    DC_PUSDataReportingPacketClass *dc_pdrpc = pNULL;

    // Allocate the two telemetry packets
    unsigned short defPacketSize = PUS_DRP_DEF_BUF_SIZE_SMALL - 2;
    unsigned int valBufferSize = PUS_DRP_VAL_BUF_SIZE_SMALL - 2;
    DC_PUSDataReportingPacket *pTMP_a;
    DC_PUSDataReportingPacket *pTMP_b;

    pTMP_a = CC_TelemetryPacketFactory_allocatePUSDataReportingPacket(pFct, 
                                                             defPacketSize, 
                                                             valBufferSize, 
                                                             0);
    pTMP_b = CC_TelemetryPacketFactory_allocatePUSDataReportingPacket(pFct, 
                                                             defPacketSize, 
                                                             valBufferSize, 
                                                             0);

    dc_pdrpc = GET_CLASS(TYPE_DC_PUSDATAREPORTINGPACKET);
    tpc = TELEMETRYPACKET_CLASS(dc_pdrpc);
    cc_roc = CC_ROOTOBJECT_CLASS(dc_pdrpc);

    // TODO figure out why not the first configuration asssertion not pass
    // without adding the following two statements
    tpc->setTimeTag(pTMP_a, 1);
    tpc->setTimeTag(pTMP_b, 1);

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

    // Configure the two packets and check that they are configured
    tpc->setSubType(pTMP_a, PUS_ST_DATA_REP_PAR_HK_REP);
    if (!cc_roc->isObjectConfigured(pTMP_a))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong configuration status");
     	return;
    }
    tpc->setSubType(pTMP_b, PUS_ST_DATA_REP_PAR_HK_REP);
    if (!cc_roc->isObjectConfigured(pTMP_b))
    {   
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong configuration status");
     	return;
    }

    // Load the packet definitions for the first TM packet
    for (unsigned short j=0; j<offset; j++) {
        DC_PUSDataReportingPacket_setDefinitionBuffer(pTMP_a, j, packet[j]);
    }

    // Load the packet definitions for the second TM packet
    memcpy(packet, &sid_b, sizeof(TD_SID));
    for (unsigned short j=0; j<offset; j++) {
        DC_PUSDataReportingPacket_setDefinitionBuffer(pTMP_b, j, packet[j]);
    }

    // Retrieve the mode manager
    DC_PUSTelemetryModeManager *pMM = TestCasePUSFull_getTelemetryModeManager(obj);
    TelemetryModeManagerClass *tmmc = TELEMETRYMODEMANAGER_GET_CLASS(pMM);
    ModeManagerClass *mmc = MODEMANAGER_GET_CLASS(pMM);
    cc_roc = CC_ROOTOBJECT_GET_CLASS(pMM);


    // Check the value of the class identifier
    if (CC_RootObject_getClassId((CC_RootObject*)pMM) != ID_PUSTELEMETRYMODEMANAGER)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                 "Wrong class identifier");
        return;
    }

    // Check that the number of packets is correct
    if (DC_PUSTelemetryModeManager_getMaxNumberOfPackets(pMM) != TM_MODE_MAN_MAX_N_PACKETS)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong max number of TM packets");
        return;
    }

    // Terminate configuration of mode manager and check configuration status
    mmc->reset(pMM);
    if (!cc_roc->isObjectConfigured(pMM))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                 "Wrong configuration status");
        return;
    }
    
    // Load packets and check success
    DC_PUSTelemetryModeManager_loadPacket(pMM, pTMP_a);
    DC_PUSTelemetryModeManager_loadPacket(pMM, pTMP_b);
    if (DC_PUSTelemetryModeManager_getNumberOfPackets(pMM) != 2)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong number of packets");
        return;
    }

    // Load the packet SID_B till the mode manager is full
    for (unsigned int j=2; j<TM_MODE_MAN_MAX_N_PACKETS; j++) {
        DC_PUSTelemetryModeManager_loadPacket(pMM, pTMP_b);
    }

    // Check that mode manager is full
    if (!DC_PUSTelemetryModeManager_isFull(pMM))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong full status");
        return;
    }

    // Attempt to load a further packet and check failure
    unsigned int nEvt = TestCaseWithEvtCheck_getNumberOfEvents(obj);
    DC_PUSTelemetryModeManager_loadPacket(pMM, pTMP_a);
    if (!verifyLatestEvent(obj, nEvt+1, EVT_ILLEGAL_MM)) return;

    // Unload all SID_B packets but one
    for (unsigned int j=2; j<TM_MODE_MAN_MAX_N_PACKETS; j++) {
        DC_PUSTelemetryModeManager_unloadPacket(pMM, sid_b);
    }

    // Get sid for pTMP_a and pTMP_b
    const TD_SID sid_of_a = DC_PUSDataReportingPacket_getSID(pTMP_a);
    const TD_SID sid_of_b = DC_PUSDataReportingPacket_getSID(pTMP_b);

    // Check iterator
    DC_PUSDataReportingPacket *pItem;
    unsigned int i = 0;
    bool sid_a_found = false;
    bool sid_b_found = false;
    for (tmmc->first(pMM); !tmmc->isIterationFinished(pMM); tmmc->next(pMM)) {
        pItem = (DC_PUSDataReportingPacket*)tmmc->getIterationTelemetryPacket(pMM);
        i++;
        TD_SID sid = DC_PUSDataReportingPacket_getSID(pItem);

        if ((sid == sid_of_a) && !sid_a_found) {
            sid_a_found = true;
            continue;
        }

        if ((sid == sid_of_b) && !sid_b_found) {
            sid_b_found = true;
            continue;
        }

        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong iteration number");
        return;
    }
    if (!sid_a_found || !sid_b_found || (i != 2))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong iteration number");
        return;
    }
    
    // Check packet presence 
    if (!DC_PUSTelemetryModeManager_isSIDLoaded(pMM, sid_of_a))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                 "Wrong presence check result");
        return;
    }
    if (DC_PUSTelemetryModeManager_isSIDLoaded(pMM, sid_of_a+2))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong presence check result");
        return;
    }

    // Unload packet and check success
    DC_PUSTelemetryModeManager_unloadPacket(pMM, sid_of_b);
    if (DC_PUSTelemetryModeManager_getNumberOfPackets(pMM) != 1)
    {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong number of packets");
        return;
    }
    if (DC_PUSTelemetryModeManager_isFull(pMM))
    {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                 "Wrong full status");
        return;
    }

    // Attempt to unload non-existent packet and check failure
    nEvt = TestCaseWithEvtCheck_getNumberOfEvents(obj);
    DC_PUSTelemetryModeManager_unloadPacket(pMM, sid_b+2);
    if (!verifyLatestEvent(obj, nEvt+1, EVT_SID_NOT_FOUND))
        return;
      
    // Check iterator
    i = 0;
    sid_a_found = false;
    for (tmmc->first(pMM); !tmmc->isIterationFinished(pMM); tmmc->next(pMM)) {
        pItem = (DC_PUSDataReportingPacket*)tmmc->getIterationTelemetryPacket(pMM);
        i++;
        TD_SID sid = DC_PUSDataReportingPacket_getSID(pItem);

        if ((sid == sid_of_a) && !sid_a_found) {
            sid_a_found = true;
            continue;
        }

        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong iteration number");
        return;
    }
    if (!sid_a_found || (i != 1))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong iteration number");
        return;
    }

    // Reload packet SID_B and unload packet SID_A and check success
    DC_PUSTelemetryModeManager_loadPacket(pMM, pTMP_b);
    DC_PUSTelemetryModeManager_unloadPacket(pMM, sid_of_a);
    if (DC_PUSTelemetryModeManager_getNumberOfPackets(pMM) != 1)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong number of packets");
        return;
    }
    if (DC_PUSTelemetryModeManager_isFull(pMM))
    {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong full status");
        return;
    }

    // Check iterator
    i = 0;
    sid_b_found = false;
    for (tmmc->first(pMM); !tmmc->isIterationFinished(pMM); tmmc->next(pMM)) {
        pItem = (DC_PUSDataReportingPacket*)tmmc->getIterationTelemetryPacket(pMM);
        i++;
        TD_SID sid = DC_PUSDataReportingPacket_getSID(pItem);

        if ((sid == sid_of_b) && !sid_b_found) {
            sid_b_found = true;
            continue;
        }

        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong iteration number");
        return;
    }
    if (!sid_b_found || (i != 1))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong iteration number");
        return;
    }   
    
    // Unload the last remaining packet and check success
    DC_PUSTelemetryModeManager_unloadPacket(pMM, sid_of_b);
    if (DC_PUSTelemetryModeManager_getNumberOfPackets(pMM) != 0)
    { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong number of packets");
         return;
    }
    if (DC_PUSTelemetryModeManager_isFull(pMM))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                 "Wrong full status");
        return;
    }

    // Check iterator
    bool flag = false;
    for (tmmc->first(pMM); !tmmc->isIterationFinished(pMM); tmmc->next(pMM)) {
        flag = true;
    }
    if (flag)
    {   TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong iteration number");
        return;
    }
  
    TestCase_setTestResult((TestCase*)obj,TEST_SUCCESS,"Test Successful");
    return;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj){}

TestCasePUSTelemetryModeManager_1* TestCasePUSTelemetryModeManager_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEPUSTELEMETRYMODEMANAGER_1);

    TESTCASEPUSFULL_GET_CLASS(obj)->post_init((TestCasePUSFull*)obj,
                                    ID_PUSTELEMETRYMODEMANAGER*10+1,
                                "TestCasePUSTelemetryModeManager_1"); 

    return (TestCasePUSTelemetryModeManager_1*)obj;
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
    .name = TYPE_TESTCASEPUSTELEMETRYMODEMANAGER_1,
    .parent = TYPE_TESTCASEPUSFULL,
    .instance_size = sizeof(TestCasePUSTelemetryModeManager_1),
    .abstract = false,
    .class_size = sizeof(TestCasePUSTelemetryModeManager_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCasePUSTelemetryModeManager_1_register(void)
{
    type_register_static(&type_info);
}
