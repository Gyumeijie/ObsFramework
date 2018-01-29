//
//
// TestCaseBasicPUSTcLoader_1.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "../Telecommand/CC_TelecommandFactory.h"
#include "../Telecommand/CC_TelecommandManager.h"
#include "../Telecommand/DC_TestPUSTelecommand.h"
#include "../Telecommand/DC_BasicPUSTcLoader.h"
#include "../Data/DC_SampleFullDataPool.h"
#include "../Utilities/TestCasePUSFull.h"
#include "TestCaseBasicPUSTcLoader_1.h"

#include <string.h>
#include <assert.h>



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void TestCaseBasicPUSTcLoader_1_writeTcHeader
(
    TestCaseBasicPUSTcLoader_1 *This,
    unsigned int start, 
    unsigned short packetId, 
    unsigned short packetSeqControl,
    unsigned short packetLength, 
    unsigned char ackField, 
    unsigned char tcType,
    unsigned char tcSubType, 
    TD_TelecommandSource tcSource
)
{
    unsigned char* const tcArea = This->tcArea;

    assert(sizeof(unsigned short) == 2);
    assert(sizeof(unsigned char) == 1);
    memcpy((tcArea+start), &packetId, 2);
    memcpy((tcArea+start+2), &packetSeqControl ,2);
    memcpy((tcArea+start+4), &packetLength, 2);
    memcpy((tcArea+start+6), &ackField, 1);
    memcpy((tcArea+start+7), &tcType, 1);
    memcpy((tcArea+start+8), &tcSubType, 1);
    memcpy((tcArea+start+9), &tcSource, sizeof(TD_TelecommandSource));
}

void TestCaseBasicPUSTcLoader_1_writeTcData
(
    TestCaseBasicPUSTcLoader_1 *This,
    unsigned int start, 
    unsigned int execCounter, 
    bool execCheckVal,
    bool valCheckVal, 
    TD_CheckCode execCheckCode,
    TD_CheckCode valCheckCode, 
    bool execOutcome
)
{
    unsigned char* const tcArea = This->tcArea;

    *(unsigned char*)(tcArea+start) = (unsigned char)execCounter;
    *(unsigned char*)(tcArea+start+1) = execCheckVal;
    *(unsigned char*)(tcArea+start+2) = valCheckVal;
    *(unsigned char*)(tcArea+start+3) = (unsigned char)execCheckCode;
    *(unsigned char*)(tcArea+start+4) = (unsigned char)valCheckCode;
    *(unsigned char*)(tcArea+start+5) = execOutcome;
}

bool TestCaseBasicPUSTcLoader_1_checkTcConfig
(
    TestCaseBasicPUSTcLoader_1 *This,
    DC_TestPUSTelecommand *pTC, 
    unsigned short packetID, 
    unsigned short packetSeqControl,
    unsigned char ackField, 
    TD_TelecommandSource tcSource,
    unsigned int execCounter, 
    bool execCheckVal,
    bool valCheckVal, 
    TD_CheckCode execCheckCode,
    TD_CheckCode valCheckCode, 
    bool execOutcome
)
{
    TelecommandClass *tc = TELECOMMAND_GET_CLASS(pTC);

    if (PUSTelecommand_getPacketId() != packetID) {
        return false;
    }

    if (tc->getTelecommandId(pTC) != packetSeqControl) {
        return false;
    }

    if (PUSTelecommand_isAcceptanceAckRequired((PUSTelecommand*)pTC) &&
        !(ackField&1)) {
        return false;
    }

    if (PUSTelecommand_isStartAckRequired((PUSTelecommand*)pTC) && 
        !(ackField&2)) {
        return false;
    }

    if (PUSTelecommand_isProgressAckRequired((PUSTelecommand*)pTC) &&
       !(ackField&4)) {
        return false;
    }

    if (PUSTelecommand_isCompletionAckRequired((PUSTelecommand*)pTC) && 
       !(ackField&8)) {
        return false;
    }

    if (tc->getSource(pTC) != tcSource) {
        return false;
    }

    if (DC_TestPUSTelecommand_getExecutionCounter(pTC) != execCounter) {
        return false;
    }

    if (tc->canExecute(pTC) && !execCheckVal) {
        return false;
    }

    if (tc->isValid(pTC) && !valCheckVal) {
        return false;
    }

    if (tc->getExecutionCheckCode(pTC) != execCheckCode) {
        return false;
    }

    if (tc->getValidityCheckCode(pTC) != valCheckCode) {
        return false;
    }

    if ((PunctualAction_execute((PunctualAction*)pTC) == ACTION_SUCCESS) && 
        !execOutcome) {
        return false;
    }

    return true;
}



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
    TestCaseBasicPUSTcLoader_1 *This = TESTCASEBASICPUSTCLOADER_1(obj);

    const unsigned int TC_AREA_SIZE = 85;
    This->tcArea = g_malloc(sizeof(unsigned char)*TC_AREA_SIZE);
    unsigned char* const tcArea = This->tcArea;
    CC_TelecommandFactory *pTCF = CC_TelecommandFactory_getInstance();

    if (CC_TelecommandFactory_getNumberTestPUSTelecommand(pTCF) != 0)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong number of telecommands");
    	return;
    }
    if (CC_TelecommandFactory_getCapacityTestPUSTelecommand(pTCF) < 3)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Insufficient TC factory capacity");
    	return;
    }

    unsigned int nEvt;
    CC_TelecommandManager *pTCM = TestCasePUSFull_getTelecommandManager(obj);
    CC_TelecommandManagerClass *cc_tmc = CC_TELECOMMANDMANAGER_GET_CLASS(pTCM);

    This->pTCL = TestCasePUSFull_getTcLoader(obj);
    DC_BasicPUSTcLoader* const pTCL = This->pTCL;
    TelecommandLoaderClass *tlc = TELECOMMANDLOADER_GET_CLASS(pTCL);

    // Check the correctness of the class identifier
    if ((CC_RootObject_getClassId((CC_RootObject*)pTCL) != ID_BASICPUSTCLOADER))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong class identifier");
        return;
    }

    // Set the start address of the telecommand load area
    DC_BasicPUSTcLoader_setTcLoadAreaStart(pTCL, tcArea);

    // Set max number of TCs
    const unsigned int MAX_NUMBER_OF_TC = 4;
    DC_BasicPUSTcLoader_setMaxNumberOfTc(pTCL, MAX_NUMBER_OF_TC);
    if (DC_BasicPUSTcLoader_getMaxNumberOfTc(pTCL) != MAX_NUMBER_OF_TC)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong configuration value");
        return;
    }

    // Set max length of TCs
    const unsigned int MAX_TC_LENGTH = 20;
    DC_BasicPUSTcLoader_setMaxTcLength(pTCL, MAX_TC_LENGTH);
    if (DC_BasicPUSTcLoader_getMaxTcLength(pTCL)!=MAX_TC_LENGTH)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong configuration value");
        return;
    }

    // Load one telecommand image
    unsigned short tcID = 11;
    TD_TelecommandSource tcSource = 13;
    unsigned int start = 0;
    *(tcArea+start) = 1;    // number of telecommands
    start++;
    TestCaseBasicPUSTcLoader_1_writeTcHeader(obj, start, 
                                             PUSTelecommand_getPacketId(), tcID, 
                                             11+sizeof(TD_TelecommandSource),
                                             0xA, PUS_TYPE_TEST,
                                             PUS_ST_TC_TEST, tcSource);
    start = start + 9 + sizeof(TD_TelecommandSource);
    TestCaseBasicPUSTcLoader_1_writeTcData(obj, start, 3, false, true, 1, 2, 0);
    start = start + 8;
    tlc->activate(pTCL);

    // Check the number of loaded telecommands
    if (CC_TelecommandManager_getPendingTelecommands(pTCM) != 1)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong number of pending TCs1");
        return;
    }

    // Check the configuration of the loaded telecommand
    Telecommand *pTC = CC_TelecommandManager_getPendingTelecommand(pTCM, 0);
    if (pTC == pNULL)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "No loaded telecommand");
        return;
    }
    if (CC_RootObject_getClassId((CC_RootObject*)pTC) != ID_TESTPUSTELECOMMAND)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong loaded telecommand");
        return;
    }

    bool checkResult;
    checkResult = TestCaseBasicPUSTcLoader_1_checkTcConfig(obj, 
                                                          (DC_TestPUSTelecommand*)pTC, 
                                                          PUSTelecommand_getPacketId(), 
                                                          tcID, 0xA, tcSource, 3, 
                                                          false, false, 1, 2, 0);
    if (checkResult)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong telecommand configuration");
        return;
    }

    // Check the "in use" status
    if (!Telecommand_isInUse(pTC))
    {	TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong in_use status");
        return;
    }
    cc_tmc->activate(pTCM);
    if (Telecommand_isInUse(pTC))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong in_use status");
        return;
    }

    // Write two TC packets to the tc load area of which the second is not intended for the TC loader
    *(tcArea) = 2;    // number of telecommands
    start = 1;

    TestCaseBasicPUSTcLoader_1_writeTcHeader(obj, start,
                                             PUSTelecommand_getPacketId()+1,
                                             tcID,
                                             11+sizeof(TD_TelecommandSource),
                                             0xA, PUS_TYPE_TEST,
                                             PUS_ST_TC_TEST, tcSource);
    start = start + 9 + sizeof(TD_TelecommandSource);
    TestCaseBasicPUSTcLoader_1_writeTcData(obj, start, 3, false, true, 1, 2, 0);
    start = start + 8;

    TestCaseBasicPUSTcLoader_1_writeTcHeader(obj, start, 
                                            PUSTelecommand_getPacketId(), tcID,
                                            11+sizeof(TD_TelecommandSource),
                                            0xA, PUS_TYPE_TEST,
                                            PUS_ST_TC_TEST, tcSource);
    start = start + 9 + sizeof(TD_TelecommandSource);
    TestCaseBasicPUSTcLoader_1_writeTcData(obj, start, 3, false, true, 1, 2, 0);
    start = start + 8;
    tlc->activate(pTCL);

    // Check the number of loaded telecommands
    if (CC_TelecommandManager_getPendingTelecommands(pTCM) != 1)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong number of pending TCs2");
        return;
    }

    // Write three TC packets to the tc load area 
    *(tcArea) = 3;    // number of telecommands
    start = 1;

    TestCaseBasicPUSTcLoader_1_writeTcHeader(obj, start, 
                                            PUSTelecommand_getPacketId(), tcID,
                                            11+sizeof(TD_TelecommandSource),
                                            0xB, PUS_TYPE_TEST,
                                            PUS_ST_TC_TEST, tcSource);
    start = start + 9 + sizeof(TD_TelecommandSource);
    TestCaseBasicPUSTcLoader_1_writeTcData(obj, start, 7, true, true, 1, 1, 1);
    start = start + 8;

    TestCaseBasicPUSTcLoader_1_writeTcHeader(obj, start, 
                                             PUSTelecommand_getPacketId(), tcID,
                                             11+sizeof(TD_TelecommandSource),
                                             0xC, PUS_TYPE_TEST,
                                             PUS_ST_TC_TEST, tcSource);
    start = start + 9 + sizeof(TD_TelecommandSource);
    TestCaseBasicPUSTcLoader_1_writeTcData(obj, start, 17, false, true, 2, 2, 0);
    start = start + 8;

    TestCaseBasicPUSTcLoader_1_writeTcHeader(obj, start,
                                             PUSTelecommand_getPacketId(), tcID,
                                             11+sizeof(TD_TelecommandSource),
                                             0xD, PUS_TYPE_TEST,
                                             PUS_ST_TC_TEST, tcSource);
    start = start + 9 + sizeof(TD_TelecommandSource);
    TestCaseBasicPUSTcLoader_1_writeTcData(obj, start, 27, true, true, 3, 3, 1);
    start = start + 8;
    tlc->activate(pTCL);

    // Check the number of loaded telecommands
    if (CC_TelecommandManager_getPendingTelecommands(pTCM) != 3)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong number of pending TCs3");
        return;
    }

    // Check the configuration of the first telecommand
    Telecommand *pTCa = CC_TelecommandManager_getPendingTelecommand(pTCM, 0);
    if (pTC == pNULL)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "No loaded telecommand");
        return;
    }
    if (CC_RootObject_getClassId((CC_RootObject*)pTC) != ID_TESTPUSTELECOMMAND)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong loaded telecommand");
        return;
    }

    checkResult = TestCaseBasicPUSTcLoader_1_checkTcConfig(obj,  
                                                          (DC_TestPUSTelecommand*)pTC, 
                                                          PUSTelecommand_getPacketId(), 
                                                          tcID, 0xB, tcSource, 7,
                                                          true, true, 1, 1, 1);
    if (checkResult)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong telecommand configuration");
        return;
    }

    // Check the configuration of the second telecommand
    Telecommand *pTCb = CC_TelecommandManager_getPendingTelecommand(pTCM, 1);
    if (pTC == pNULL)
    {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "No loaded telecommand");
        return;
    }
    if (CC_RootObject_getClassId((CC_RootObject*)pTC) != ID_TESTPUSTELECOMMAND)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong loaded telecommand");
        return;
    }
    checkResult = TestCaseBasicPUSTcLoader_1_checkTcConfig(obj, 
                                                          (DC_TestPUSTelecommand*)pTC, 
                                                          PUSTelecommand_getPacketId(), 
                                                          tcID, 0xC, tcSource, 17,
                                                          false, false, 2, 2, 0);
    if (checkResult)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong telecommand configuration");
        return;
    }

    // Check the configuration of the third telecommand
    Telecommand *pTCc = CC_TelecommandManager_getPendingTelecommand(pTCM, 2);
    if (pTC == pNULL)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "No loaded telecommand");
        return;
    }
    if (CC_RootObject_getClassId((CC_RootObject*)pTC) != ID_TESTPUSTELECOMMAND)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong loaded telecommand");
        return;
    }

    checkResult = TestCaseBasicPUSTcLoader_1_checkTcConfig(obj,  
                                                          (DC_TestPUSTelecommand*)pTC, 
                                                          PUSTelecommand_getPacketId(), 
                                                          tcID, 0xD, tcSource, 27,
                                                          true, false, 3, 3, 1);
    if (checkResult)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong telecommand configuration");
        return;
    }

    // Check the "in use" status
    if (!Telecommand_isInUse(pTCa) || 
        !Telecommand_isInUse(pTCb) || 
        !Telecommand_isInUse(pTCc))
    {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong in_use status");
        return;
    }
    cc_tmc->activate(pTCM);
    if (Telecommand_isInUse(pTCa) || 
        Telecommand_isInUse(pTCb) || 
        Telecommand_isInUse(pTCc))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong in_use status");
        return;
    }

    // Write a TC packets that is too long
    *(tcArea) = 1;    // number of telecommands
    start = 1;

    TestCaseBasicPUSTcLoader_1_writeTcHeader(obj, start, 
                                             PUSTelecommand_getPacketId(),
                                             tcID, MAX_TC_LENGTH+1, 
                                             0xA, PUS_TYPE_TEST, 
                                             PUS_ST_TC_TEST, tcSource);
    start = start + 9 + sizeof(TD_TelecommandSource);
    TestCaseBasicPUSTcLoader_1_writeTcData(obj, start, 3, false, true, 1, 2, 0);
    start = start + 8;
    nEvt = TestCaseWithEvtCheck_getNumberOfEvents(obj);
    tlc->activate(pTCL);

    // Check the number of loaded telecommands
    if (CC_TelecommandManager_getPendingTelecommands(pTCM) != 0)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong number of pending TCs4");
        return;
    }

    // Check correct event generation and flush the TC manager
    if (!verifyLatestEvent(obj, nEvt+1, EVT_TC_TOO_LONG))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong event report type");
        return;
    }
    nEvt++;
    cc_tmc->activate(pTCM);

    // Write two TC packets of which the first one has a type not recongnized by the TC loader
    *(tcArea) = 2;    // number of telecommands
    start = 1;

    TestCaseBasicPUSTcLoader_1_writeTcHeader(obj, start,
                                             PUSTelecommand_getPacketId(), tcID,
                                             11+sizeof(TD_TelecommandSource),
                                             0xA, PUS_TYPE_TEST+1,
                                             PUS_ST_TC_TEST, tcSource);
    start = start + 9 + sizeof(TD_TelecommandSource);
    TestCaseBasicPUSTcLoader_1_writeTcData(obj, start, 3, false, true, 1, 2, 0);
    start = start + 8;

    TestCaseBasicPUSTcLoader_1_writeTcHeader(obj, start,
                                             PUSTelecommand_getPacketId(), tcID,
                                             11+sizeof(TD_TelecommandSource),
                                             0xA, PUS_TYPE_TEST,
                                             PUS_ST_TC_TEST, tcSource);
    start = start + 9 + sizeof(TD_TelecommandSource);
    TestCaseBasicPUSTcLoader_1_writeTcData(obj, start, 3, false, true, 1, 2, 0);
    start = start + 8;

    nEvt = TestCaseWithEvtCheck_getNumberOfEvents(obj);
    tlc->activate(pTCL);

    // Check the number of loaded telecommands
    if (CC_TelecommandManager_getPendingTelecommands(pTCM) != 1)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong number of pending TCs5");
        return;
    }

    // Check correct event generation 
    if (!verifySpecificEvent(obj, nEvt+1, EVT_UNKNOWN_TC_TYPE))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong event report type");
        return;
    }
    cc_tmc->activate(pTCM);       // flush the TC manager

    // Write more TC packets that allowed
    *(tcArea) = MAX_NUMBER_OF_TC + 1;    // number of telecommands

    nEvt = TestCaseWithEvtCheck_getNumberOfEvents(obj);
    tlc->activate(pTCL);

    // Check the number of loaded telecommands
    if (CC_TelecommandManager_getPendingTelecommands(pTCM) != 0)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong number of pending TCs6");
        return;
    }

    // Check correct event generation 
    if (!verifyLatestEvent(obj, nEvt+1, EVT_TOO_MANY_TC_PCKT))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong event report type");
        return;
    }
    cc_tmc->activate(pTCM);       // flush the TC manager

    // Write four TC packets to the tc load area 
    *(tcArea) = 4;    // number of telecommands
    start = 1;

    TestCaseBasicPUSTcLoader_1_writeTcHeader(obj, start,
                                             PUSTelecommand_getPacketId(), tcID,
                                             11+sizeof(TD_TelecommandSource),
                                             0xB, PUS_TYPE_TEST,
                                             PUS_ST_TC_TEST, tcSource);
    start = start + 9 + sizeof(TD_TelecommandSource);
    TestCaseBasicPUSTcLoader_1_writeTcData(obj, start, 7, true, true, 1, 1, 1);
    start = start + 8;

    TestCaseBasicPUSTcLoader_1_writeTcHeader(obj, start,
                                             PUSTelecommand_getPacketId(), tcID,
                                             11+sizeof(TD_TelecommandSource),
                                             0xC, PUS_TYPE_TEST,
                                             PUS_ST_TC_TEST, tcSource);
    start = start + 9 + sizeof(TD_TelecommandSource);
    TestCaseBasicPUSTcLoader_1_writeTcData(obj, start, 17, false, true, 2, 2, 0);
    start = start + 8;

    TestCaseBasicPUSTcLoader_1_writeTcHeader(obj, start,
                                             PUSTelecommand_getPacketId(), tcID,
                                             11+sizeof(TD_TelecommandSource),
                                             0xD, PUS_TYPE_TEST,
                                             PUS_ST_TC_TEST, tcSource);
    start = start + 9 + sizeof(TD_TelecommandSource);
    TestCaseBasicPUSTcLoader_1_writeTcData(obj, start, 27, true, true, 3, 3, 1);
    start = start + 8;

    TestCaseBasicPUSTcLoader_1_writeTcHeader(obj, start,
                                             PUSTelecommand_getPacketId(), tcID,
                                             11+sizeof(TD_TelecommandSource),
                                             0xD, PUS_TYPE_TEST,
                                             PUS_ST_TC_TEST, tcSource);
    start = start + 9 + sizeof(TD_TelecommandSource);
    TestCaseBasicPUSTcLoader_1_writeTcData(obj, start, 27, true, true, 3, 3, 1);
    start = start + 8;
    nEvt = TestCaseWithEvtCheck_getNumberOfEvents(obj);
    tlc->activate(pTCL);

    // Check the number of loaded telecommands
    if (CC_TelecommandManager_getPendingTelecommands(pTCM) != 3)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong number of pending TCs7");
        return;
    }

    // Check correct event generation (NB: one event is created whenever a TC is 
    // successufully loaded in the TC manager)
    if (!verifyLatestEvent(obj, nEvt+4, EVT_NO_TC_AVAIL))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong event report type");
        return;
    }
    cc_tmc->activate(pTCM);       // flush the TC manager

    // If this point is reached, the test was successful
    TestCase_setTestResult((TestCase*)obj, TEST_SUCCESS, "Test Successful");
    return;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj){}

TestCaseBasicPUSTcLoader_1* TestCaseBasicPUSTcLoader_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEBASICPUSTCLOADER_1);

    TESTCASEPUSFULL_GET_CLASS(obj)->post_init((TestCasePUSFull*)obj,
                                           ID_BASICPUSTCLOADER*10+1,
                                      "TestCaseBasicPUSTcLoader_1"); 

    return (TestCaseBasicPUSTcLoader_1*)obj;
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
    .name = TYPE_TESTCASEBASICPUSTCLOADER_1,
    .parent = TYPE_TESTCASEPUSFULL,
    .instance_size = sizeof(TestCaseBasicPUSTcLoader_1),
    .abstract = false,
    .class_size = sizeof(TestCaseBasicPUSTcLoader_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseBasicPUSTcLoader_1_register(void)
{
    type_register_static(&type_info);
}
