//
//
// TestCasePUSEventRepository_1.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "../System/DC_DummyObsClock.h"
#include "../Event/DC_PUSEventRepository.h"
#include "../Manoeuvre/CC_ManoeuvreFactory.h"
#include "../Manoeuvre/DC_DummyConfigurableManoeuvre.h"
#include "../Telemetry/CC_TelemetryManager.h"
#include "../Telemetry/CC_TelemetryPacketFactory.h"
#include "../Telecommand/CC_TelecommandFactory.h"
#include "../Telecommand/CC_TelecommandManager.h"
#include "../Telecommand/DC_TestPUSTelecommand.h"
#include "../Telemetry/DC_PUSTcVerificationPacket.h"
#include "../Data/DC_SampleFullDataPool.h"
#include "../Utilities/TestCasePUSFull.h"
#include "TestCasePUSEventRepository_1.h"




///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

bool TestCasePUSEventRepository_1_checkTmPacket
(
    TestCasePUSEventRepository_1 *This,
    DC_PUSEventRepository *pEvtRep, 
    TD_TelemetrySubType tmSubType, 
    TD_TelecommandId tcId,
    TD_ObsTime tt, 
    TD_CheckCode errCode
)
{
    CC_TelemetryManager *pTMM = DC_PUSEventRepository_getTelemetryManager(pEvtRep);
    CC_TelemetryManagerClass *cc_tmc = CC_TELEMETRYMANAGER_GET_CLASS(pTMM);

    TelemetryPacket *pTemp = CC_TelemetryManager_getImmediateQueueEntry(pTMM, 0);

    if (pTemp == pNULL) {
        return false;
    }

    if (CC_RootObject_getClassId((CC_RootObject*)pTemp) != ID_PUSTCVERIFICATIONPACKET)
    {
        return false;
    }

    DC_PUSTcVerificationPacket *pTM = (DC_PUSTcVerificationPacket*)pTemp;
    TelemetryPacketClass *tpc = TELEMETRYPACKET_GET_CLASS(pTM);

    if (tpc->getSubType(pTM) != tmSubType) {
        return false;
    }

    if (DC_PUSTcVerificationPacket_getTelecommandId(pTM) != tcId) {
        return false;
    }

    if (tpc->getTimeTag(pTM) != tt) {
        return false;
    }

    if (tpc->getType(pTM) != PUS_TYPE_TC_VER) {
        return false;
    }

    if (errCode != 0) {
        if (DC_PUSTcVerificationPacket_getErrorCode(pTM) != errCode) {
            return false;
        }
    }

    // Flush telemetry manager
    cc_tmc->activate(pTMM);

    return true;
}

bool TestCasePUSEventRepository_1_checkNoTmPacket
(
    TestCasePUSEventRepository_1 *This,
    DC_PUSEventRepository *pEvtRep
)
{

    CC_TelemetryManager *pTMM = DC_PUSEventRepository_getTelemetryManager(pEvtRep);
    TelemetryPacket *pTemp = CC_TelemetryManager_getImmediateQueueEntry(pTMM, 0);

    if (pTemp == pNULL) {
        return true;
    } else {
        return false;
    }
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

    unsigned int nEvt;
    const TD_TelecommandId tcId_1 = 121;
    const TD_TelecommandId tcId_2 = 122;

    CC_TelecommandFactory *pTCF = CC_TelecommandFactory_getInstance();
    if (CC_TelecommandFactory_getNumberTestPUSTelecommand(pTCF) != 0)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong number of telecommands");
    	return;
    }
    if (CC_TelecommandFactory_getCapacityTestPUSTelecommand(pTCF) < 1)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Insufficient TC factory capacity");
    	return;
    }

    DC_TestPUSTelecommand *pTC;
    pTC = CC_TelecommandFactory_allocateTestPUSTelecommand(pTCF);
    TelecommandClass *tc = TELECOMMAND_GET_CLASS(pTC);
    tc->setTelecommandId(pTC, tcId_1);

    CC_ManoeuvreFactory *pMF = CC_ManoeuvreFactory_getInstance();
    if (CC_ManoeuvreFactory_getNumberTestPUSConfigurableManoeuvre(pMF) != 0)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong number of manoeuvres");
    	return;
    }
    if (CC_ManoeuvreFactory_getCapacityTestPUSConfigurableManoeuvre(pMF) < 1)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Insufficient manoeuvre factory capacity");
    	return;
    }
    DC_TestPUSConfigurableManoeuvre *pMan;
    pMan = CC_ManoeuvreFactory_allocateTestPUSConfigurableManoeuvre(pMF);
    PUSTcManoeuvreClass *ptmc = PUSTCMANOEUVRE_GET_CLASS(pMan);
    ptmc->setTelecommandId(pMan, tcId_2);

    DC_PUSEventRepository *pEvtRep = TestCasePUSFull_getEventRepository(obj);

    // Check the correctness of the class identifier
    if ((CC_RootObject_getClassId((CC_RootObject*)pEvtRep) != ID_PUSEVENTREPOSITORY))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong class identifier");
        return;
    }

    // Flush telemetry manager to make sure that there are no pending packets in the
    // immediate dispatch queue
    CC_TelemetryManager *cc_tm = DC_PUSEventRepository_getTelemetryManager(pEvtRep);
    CC_TelemetryManagerClass *cc_tmc = CC_TELEMETRYMANAGER_GET_CLASS(cc_tm);
    cc_tmc->activate(cc_tm);

    // Make repeated call to the create method for telecommands and check success
    const TD_CheckCode VAL_CODE = 100;
    const TD_CheckCode EXEC_CODE = 101;
    const TD_CheckCode CONT_CODE = 102;

    nEvt = TestCaseWithEvtCheck_getNumberOfEvents(obj);
    tc->setAcknowledgeLevel(pTC, 1);         // acceptance acknowledge flag is set
    DC_PUSEventRepository_create(pEvtRep, (Object*)pTC, EVT_TC_LOADED);

    ObsClock *clock = (ObsClock*)TestCasePUSFull_getObsClock(obj);
    ObsClockClass *occ = OBSCLOCK_GET_CLASS(clock);

    bool checkResult = TestCasePUSEventRepository_1_checkTmPacket(obj, pEvtRep,
                                                  PUS_ST_TC_VER_ACC_SC, tcId_1, 
                                                  occ->getTime(clock), 0);
    if (!checkResult)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong packet configuration");
        return;
    }
    if (!verifyLatestEvent(obj, nEvt+1, EVT_TC_LOADED)) {
        return;
    }

    tc->setAcknowledgeLevel(pTC, 0);       // acceptance acknowledge flag is reset
    DC_PUSEventRepository_create(pEvtRep, (Object*)pTC, EVT_TC_LOADED);
    if (!TestCasePUSEventRepository_1_checkNoTmPacket(obj, pEvtRep))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Unexpected packet");
        return;
    }

    DC_TestPUSTelecommand_setValidityCheckCode(pTC, 0);
    DC_PUSEventRepository_create(pEvtRep, (Object*)pTC, EVT_TC_NOT_VALID);

    checkResult = TestCasePUSEventRepository_1_checkTmPacket(obj, pEvtRep,
                                                 PUS_ST_TC_VER_ACC_FL, tcId_1, 
                                                 occ->getTime(clock), 
                                                 EVT_TC_NOT_VALID);
    if (!checkResult)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong packet configuration");
        return;
    }

    DC_TestPUSTelecommand_setValidityCheckCode(pTC, VAL_CODE);
    DC_PUSEventRepository_create(pEvtRep, (Object*)pTC, EVT_TC_NOT_VALID);
    checkResult = TestCasePUSEventRepository_1_checkTmPacket(obj, pEvtRep, 
                                                PUS_ST_TC_VER_ACC_FL, tcId_1,
                                                occ->getTime(clock), VAL_CODE);
    if (!checkResult)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong packet configuration");
        return;
    }

    DC_PUSEventRepository_create(pEvtRep, (Object*)pTC, EVT_TC_LIST_FULL);
    checkResult = TestCasePUSEventRepository_1_checkTmPacket(obj, pEvtRep,
                                                PUS_ST_TC_VER_ACC_FL, tcId_1,
                                                occ->getTime(clock),
                                                EVT_TC_LIST_FULL);
    if (!checkResult)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong packet configuration");
        return;
    }

    nEvt = TestCaseWithEvtCheck_getNumberOfEvents(obj);
    PUSTcManoeuvre_setStartAckFlag((PUSTcManoeuvre*)pMan, true);
    DC_PUSEventRepository_create(pEvtRep, (Object*)pMan, EVT_MAN_STARTED);
    checkResult = TestCasePUSEventRepository_1_checkTmPacket(obj, pEvtRep,
                                                PUS_ST_TC_EXE_STR_SC, tcId_2,
                                                occ->getTime(clock), 0);

    if (!checkResult)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong packet configuration");
        return;
    }
    if (!verifyLatestEvent(obj, nEvt+1, EVT_MAN_STARTED))
        return;

    PUSTcManoeuvre_setStartAckFlag((PUSTcManoeuvre*)pMan, false);
    DC_PUSEventRepository_create(pEvtRep, (Object*)pMan, EVT_MAN_STARTED);
    if (!TestCasePUSEventRepository_1_checkNoTmPacket(obj, pEvtRep))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Unexpected packet");
        return;
    }

    DC_PUSEventRepository_create(pEvtRep, (Object*)pMan, EVT_MAN_LIST_FULL);
    checkResult = TestCasePUSEventRepository_1_checkTmPacket(obj, pEvtRep,
                                                  PUS_ST_TC_EXE_STR_FL, tcId_2,
                                                  occ->getTime(clock), 
                                                  EVT_MAN_LIST_FULL);
    if (!checkResult)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong packet configuration");
        return;
    }

    DC_TestPUSTelecommand_setExecutionCheckCode(pTC, 0);
    DC_PUSEventRepository_create(pEvtRep, (Object*)pTC, EVT_TC_EXEC_CHECK_FAIL);
    checkResult = TestCasePUSEventRepository_1_checkTmPacket(obj, pEvtRep,
                                                  PUS_ST_TC_EXE_STR_FL, tcId_1, 
                                                  occ->getTime(clock),
                                                  EVT_TC_EXEC_CHECK_FAIL);
    if (!checkResult)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong packet configuration");
        return;
    }

    DC_TestPUSTelecommand_setExecutionCheckCode(pTC, EXEC_CODE);
    DC_PUSEventRepository_create(pEvtRep, (Object*)pTC, EVT_TC_EXEC_CHECK_FAIL);
    checkResult = TestCasePUSEventRepository_1_checkTmPacket(obj, pEvtRep,
                                                  PUS_ST_TC_EXE_STR_FL, tcId_1,
                                                  occ->getTime(clock), 
                                                  EXEC_CODE);
    if (!checkResult)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong packet configuration");
        return;
    }

    DC_PUSEventRepository_create(pEvtRep, (Object*)pTC, EVT_TC_ABORTED);
    checkResult = TestCasePUSEventRepository_1_checkTmPacket(obj, pEvtRep,
                                                PUS_ST_TC_EXE_STR_FL, tcId_1,
                                                occ->getTime(clock),
                                                EVT_TC_ABORTED);
    if (!checkResult)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong packet configuration");
        return;
    }

    PUSTcManoeuvre_setProgressAckFlag((PUSTcManoeuvre*)pMan, true);
    DC_PUSEventRepository_create(pEvtRep, (Object*)pMan, EVT_MAN_PROGRESS);
    checkResult = TestCasePUSEventRepository_1_checkTmPacket(obj, pEvtRep,
                                                 PUS_ST_TC_EXE_PRO_SC, tcId_2,
                                                 occ->getTime(clock), 0);
    if (!checkResult)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong packet configuration");
        return;
    }

    PUSTcManoeuvre_setProgressAckFlag((PUSTcManoeuvre*)pMan, false);
    DC_PUSEventRepository_create(pEvtRep, (Object*)pMan, EVT_MAN_PROGRESS);
    if (!TestCasePUSEventRepository_1_checkNoTmPacket(obj, pEvtRep))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Unexpected packet");
        return;
    }

    tc->setAcknowledgeLevel(pTC, 8);        // set completion acknowledge flag
    DC_PUSEventRepository_create(pEvtRep, (Object*)pTC, EVT_TC_EXEC_SUCC);
    checkResult = TestCasePUSEventRepository_1_checkTmPacket(obj, pEvtRep,
                                                  PUS_ST_TC_EXE_END_SC, tcId_1,
                                                  occ->getTime(clock), 0);
    if (!checkResult)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong packet configuration1");
        return;
    }

    tc->setAcknowledgeLevel(pTC, 0);        // reset acknowledge flags
    DC_PUSEventRepository_create(pEvtRep, (Object*)pTC, EVT_TC_EXEC_SUCC);
    if (!TestCasePUSEventRepository_1_checkNoTmPacket(obj, pEvtRep))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Unexpected packet");
        return;
    }

    // This test point need telecommand loader to be activated first; So
    // TestCaseBasicPUSTcLoader should be run before this testcase.
    DC_TestPUSTelecommand_setActionOutcome(pTC, true);
    
    DC_PUSEventRepository_create(pEvtRep, (Object*)pTC, EVT_TC_EXEC_FAIL);
    checkResult = TestCasePUSEventRepository_1_checkTmPacket(obj, pEvtRep,
                                                 PUS_ST_TC_EXE_END_FL, tcId_1,
                                                 occ->getTime(clock), 
                                                 (TD_CheckCode)ACTION_SUCCESS);
    if (!checkResult)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong packet configuration");
        return;
    }

    DC_TestPUSConfigurableManoeuvre_setContinuationCheckCode(pMan, 0);
    DC_PUSEventRepository_create(pEvtRep, (Object*)pMan, EVT_MAN_ABORTED);
    checkResult = TestCasePUSEventRepository_1_checkTmPacket(obj, pEvtRep,
                                             PUS_ST_TC_EXE_PRO_FL, tcId_2,
                                             occ->getTime(clock),
                                             EVT_MAN_ABORTED);
    if (!checkResult)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong packet configuration");
        return;
    }

    DC_TestPUSConfigurableManoeuvre_setContinuationCheckCode(pMan, CONT_CODE);
    DC_PUSEventRepository_create(pEvtRep, (Object*)pMan, EVT_MAN_ABORTED);
    checkResult = TestCasePUSEventRepository_1_checkTmPacket(obj, pEvtRep,
                                                 PUS_ST_TC_EXE_PRO_FL, tcId_2,
                                                 occ->getTime(clock), 
                                                 CONT_CODE);
    if (!checkResult)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong packet configuration");
        return;
    }

   	PUSTcManoeuvre_setCompletionAckFlag((PUSTcManoeuvre*)pMan, true);
    DC_PUSEventRepository_create(pEvtRep, (Object*)pMan, EVT_MAN_TERMINATED);
    checkResult = TestCasePUSEventRepository_1_checkTmPacket(obj, pEvtRep,
                                                  PUS_ST_TC_EXE_END_SC, tcId_2,
                                                  occ->getTime(clock), 0);
    if (!checkResult)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong packet configuration");
        return;
    }

   	PUSTcManoeuvre_setCompletionAckFlag((PUSTcManoeuvre*)pMan, false);
    DC_PUSEventRepository_create(pEvtRep, (Object*)pMan, EVT_MAN_TERMINATED);
    if (!TestCasePUSEventRepository_1_checkNoTmPacket(obj, pEvtRep))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong packet configuration");
        return;
    }

    // Force a situation where the telemetry packet factory in the 
    // PUS event repository runs out of telemetry packets and check that correct event is generated
    CC_TelemetryPacketFactory* pTMF = CC_TelemetryPacketFactory_getInstance();
    while (CC_TelemetryPacketFactory_isFreePUSTcVerificationPacket(pTMF)) {
        DC_PUSEventRepository_create(pEvtRep, (Object*)pMan, EVT_MAN_ABORTED);
    }
    nEvt = TestCaseWithEvtCheck_getNumberOfEvents(obj);
    DC_PUSEventRepository_create(pEvtRep, (Object*)pMan, EVT_MAN_TERMINATED);
    if (TestCaseWithEvtCheck_getNumberOfEvents(obj) != nEvt+2)
    {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong number of events");
        return;
    }
    if (!verifySpecificEvent(obj, nEvt+1, EVT_TM_PCK_ALLOC_FAILURE)) {
        return;
    }

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

TestCasePUSEventRepository_1* TestCasePUSEventRepository_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEPUSEVENTREPOSITORY_1);

    TESTCASEPUSFULL_GET_CLASS(obj)->post_init((TestCasePUSFull*)obj,
                                         ID_PUSEVENTREPOSITORY*10+1,
                                    "TestCasePUSEventRepository_1"); 

    return (TestCasePUSEventRepository_1*)obj;
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
    .name = TYPE_TESTCASEPUSEVENTREPOSITORY_1,
    .parent = TYPE_TESTCASEPUSFULL,
    .instance_size = sizeof(TestCasePUSEventRepository_1),
    .abstract = false,
    .class_size = sizeof(TestCasePUSEventRepository_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCasePUSEventRepository_1_register(void)
{
    type_register_static(&type_info);
}
