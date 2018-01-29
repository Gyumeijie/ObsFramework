//
//
// TestCasePUSFull.c
//

#include "TestCasePUSFull.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/TestConstants.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../System/DC_DummyObsClock.h"
#include "../Event/DC_PUSEventRepository.h"
#include "../Data/DC_DummyDataPool.h"
#include "../Data/DC_DummyDatabase.h"
#include "../Manoeuvre/CC_ManoeuvreManager.h"
#include "../Telemetry/CC_TelemetryManager.h"
#include "../Telemetry/DC_PUSTelemetryModeManager.h"
#include "../Telemetry/DC_PUSDataReportingPacket.h"
#include "../Telemetry/DC_PUSTmLogger.h"
#include "../Telemetry/TelemetryPacket.h"
#include "../Telecommand/CC_TelecommandManager.h"
#include "../Telecommand/DC_BasicPUSTcLoader.h"
#include "../Telecommand/TelecommandLoader.h"
#include "../Telecommand/PUSTelecommand.h"

#include <string.h>
#include <assert.h>

#define  TC_COMMAND_MAX_CAPACITY (TC_COMMAND_AREA_MAX_N_TC*TC_COMMAND_AREA_MAX_TC_LEN)


///////////////////////////////////////////////////////////////////////////////
//
//                            class data
//
///////////////////////////////////////////////////////////////////////////////

static bool firstActivation = true;

static CC_TelemetryManager *pTmManager = pNULL;

static DC_PUSTelemetryModeManager *pTmModeMan = pNULL;

static CC_TelecommandManager *pTcManager = pNULL;

static CC_ManoeuvreManager *pManManager = pNULL;

static DC_PUSTmLogger *pTmLogger = pNULL;

static DC_BasicPUSTcLoader *pTcLoader = pNULL;

static DC_PUSEventRepository *pEvtRep = pNULL;

static DC_DummyObsClock *pObsClock = pNULL;

static unsigned char tcCommandArea[TC_COMMAND_MAX_CAPACITY];


///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void TestCasePUSFull_writeTcHeader(TestCasePUSFull *This, 
                                   unsigned short length, 
                                   unsigned short packetSeqControl)
{
    TD_PUSPacketId id = PUSTelecommand_getPacketId();
    assert(sizeof(TD_PUSPacketId) == 2);
    memcpy(tcCommandArea + This->tcCmdPos, &id, 2);
    memcpy(tcCommandArea + This->tcCmdPos + 2, &packetSeqControl, 2);
    memcpy(tcCommandArea + This->tcCmdPos + 4, &length, 2);
    This->tcCmdPos = This->tcCmdPos + 6;
}

CC_TelecommandManager* TestCasePUSFull_getTelecommandManager
(
    const TestCasePUSFull *This
)
{
    return pTcManager;
}

CC_TelemetryManager* TestCasePUSFull_getTelemetryManager
(
    const TestCasePUSFull *This
)
{
    return pTmManager;
}

DC_PUSTelemetryModeManager* TestCasePUSFull_getTelemetryModeManager
(
    const TestCasePUSFull *This
)
{
    return pTmModeMan;
}

CC_ManoeuvreManager* TestCasePUSFull_getManoeuvreManager
(
    const TestCasePUSFull *This
)
{
    return pManManager;
}

DC_BasicPUSTcLoader* TestCasePUSFull_getTcLoader(const TestCasePUSFull *This)
{
    return pTcLoader;
}

DC_PUSTmLogger* TestCasePUSFull_getTmStream(const TestCasePUSFull *This)
{
    return pTmLogger;
}

DC_DummyObsClock* TestCasePUSFull_getObsClock(const TestCasePUSFull *This)
{
    return pObsClock;
}

DC_PUSEventRepository* TestCasePUSFull_getEventRepository
(
    const TestCasePUSFull *This
)
{
    return pEvtRep;
}

bool TestCasePUSFull_writeTestPUSTelecommand
(
    TestCasePUSFull *This, 
    unsigned char ackField, 
    unsigned int execCounter, 
    bool execCheckVal, 
    bool valCheckVal, 
    TD_CheckCode execCheckCode,
    TD_CheckCode valCheckCode, 
    bool execOutcome, 
    unsigned short packetSeqControl
)
{
    // Check that TC packet fits in command load area
    unsigned short appDataLength = 6;
    unsigned short packetLength = 11 + sizeof(TD_TelecommandSource) + appDataLength;

    // In order access tcCmdPos concisely below
    unsigned int tcCmdPos = This->tcCmdPos;

    if ((tcCmdPos+packetLength) > TC_COMMAND_MAX_CAPACITY) {
        return false;
    }

    // Write TC packet header
    TestCasePUSFull_writeTcHeader(This, packetLength-6, packetSeqControl);

    // Write packet data field header
    *(unsigned char*)(tcCommandArea+tcCmdPos) = ackField;
    *(unsigned char*)(tcCommandArea+tcCmdPos+1) = PUS_TYPE_TEST;
    *(unsigned char*)(tcCommandArea+tcCmdPos+2) = PUS_ST_TC_TEST;
    TD_TelecommandSource tcSrc = DEF_PUS_TC_SOURCE;
    memcpy(tcCommandArea+tcCmdPos+3, &tcSrc, sizeof(TD_TelecommandSource));
    tcCmdPos = tcCmdPos + 3 + sizeof(TD_TelecommandSource);

    // Write application data
    *(unsigned char*)(tcCommandArea+tcCmdPos) = (unsigned char)execCounter;
    *(unsigned char*)(tcCommandArea+tcCmdPos+1) = execCheckVal;
    *(unsigned char*)(tcCommandArea+tcCmdPos+2) = valCheckVal;
    *(unsigned char*)(tcCommandArea+tcCmdPos+3) = (unsigned char)execCheckCode;
    *(unsigned char*)(tcCommandArea+tcCmdPos+4) = (unsigned char)valCheckCode;
    *(unsigned char*)(tcCommandArea+tcCmdPos+5) = execOutcome;
    tcCmdPos = tcCmdPos + 6;

    // Write packet error control bytes
    *(unsigned char*)(tcCommandArea+tcCmdPos) = 0;
    *(unsigned char*)(tcCommandArea+tcCmdPos+1) = 0;
    tcCmdPos = tcCmdPos + 2;

    // Write tcCmdPos back to update tcCmdPos data member
    This->tcCmdPos = tcCmdPos;

    return true;
}

bool TestCasePUSFull_writePUSDefineDataReporting
(
    TestCasePUSFull *This, 
    unsigned char ackField, 
    TD_PUSCollectionInterval collectionInterval, 
    TD_SID sid, 
    TD_DataPoolId par, 
    unsigned short packetSeqControl,
    TD_TelecommandSubType tcSubType
)
{
    // Check that TC packet fits in command load area
    unsigned short appDataLength = sizeof(TD_SID) + 
                                   sizeof(TD_PUSCollectionInterval) +
                                   sizeof(TD_PUSNumberOfParameters) +
                                   sizeof(TD_DataPoolId);
    unsigned short packetLength = 11 + sizeof(TD_TelecommandSource) + appDataLength;

    // In order access tcCmdPos concisely below
    unsigned int tcCmdPos = This->tcCmdPos;

    if ((tcCmdPos+packetLength) > TC_COMMAND_MAX_CAPACITY) {
        return false;
    }

    // Write TC packet header
    TestCasePUSFull_writeTcHeader(This, packetLength-6, packetSeqControl);

    // Write packet data field header
    *(unsigned char*)(tcCommandArea+tcCmdPos) = ackField;
    *(unsigned char*)(tcCommandArea+tcCmdPos+1) = PUS_TYPE_DATA_REP;
    *(unsigned char*)(tcCommandArea+tcCmdPos+2) = tcSubType;
    TD_TelecommandSource tcSrc = DEF_PUS_TC_SOURCE;
    memcpy(tcCommandArea+tcCmdPos+3, &tcSrc, sizeof(TD_TelecommandSource));
    tcCmdPos = tcCmdPos + 3 + sizeof(TD_TelecommandSource);

    // Write application data
    memcpy(tcCommandArea+tcCmdPos, &sid, sizeof(TD_SID));
    tcCmdPos = tcCmdPos + sizeof(TD_SID);

    memcpy(tcCommandArea+tcCmdPos, &collectionInterval, sizeof(TD_PUSCollectionInterval));
    tcCmdPos = tcCmdPos + sizeof(TD_PUSCollectionInterval);

    TD_PUSNumberOfParameters npTemp = 1;
    memcpy(tcCommandArea+tcCmdPos, &npTemp, sizeof(TD_PUSNumberOfParameters));
    tcCmdPos = tcCmdPos + sizeof(TD_PUSNumberOfParameters);

    memcpy(tcCommandArea+tcCmdPos, &par, sizeof(TD_DataPoolId));
    tcCmdPos = tcCmdPos + sizeof(TD_DataPoolId);

    // Write packet error control bytes
    *(unsigned char*)(tcCommandArea+tcCmdPos) = 0;
    *(unsigned char*)(tcCommandArea+tcCmdPos+1) = 0;
    tcCmdPos = tcCmdPos + 2;

    // Write tcCmdPos back to update tcCmdPos data member
    This->tcCmdPos = tcCmdPos;

    return true;
}

bool TestCasePUSFull_writePUSDataReportingControl
(
    TestCasePUSFull *This, 
    unsigned char ackField, 
    unsigned char NSID, 
    TD_SID *sid, 
    TD_TelecommandSubType tcSubType, 
    unsigned short packetSeqControl
)
{
    // Check that TC packet fits in command load area
    unsigned short appDataLength = 1 + NSID*sizeof(TD_SID);
    unsigned short packetLength = 11 + sizeof(TD_TelecommandSource) + appDataLength;

    // In order access tcCmdPos concisely below
    unsigned int tcCmdPos = This->tcCmdPos;

    if ((tcCmdPos+packetLength) > TC_COMMAND_MAX_CAPACITY) {
        return false;
    }

    // Write TC packet header
    TestCasePUSFull_writeTcHeader(This, packetLength-6, packetSeqControl);

    // Write packet data field header
    *(unsigned char*)(tcCommandArea+tcCmdPos) = ackField;
    *(unsigned char*)(tcCommandArea+tcCmdPos+1) = PUS_TYPE_DATA_REP;
    *(unsigned char*)(tcCommandArea+tcCmdPos+2) = tcSubType;
    TD_TelecommandSource tcSrc = DEF_PUS_TC_SOURCE;
    memcpy(tcCommandArea+tcCmdPos+3, &tcSrc, sizeof(TD_TelecommandSource));
    tcCmdPos = tcCmdPos + 3 + sizeof(TD_TelecommandSource);

    // Write application data
    *(unsigned char*)(tcCommandArea+tcCmdPos) = (unsigned char)NSID;
    tcCmdPos++;
    for (unsigned char i=0; i<NSID; i++) {
        memcpy(tcCommandArea+tcCmdPos, &sid[i], sizeof(TD_SID));
        tcCmdPos = tcCmdPos + sizeof(TD_SID);
    }

    // Write packet error control bytes
    *(unsigned char*)(tcCommandArea+tcCmdPos) = 0;
    *(unsigned char*)(tcCommandArea+tcCmdPos+1) = 0;
    tcCmdPos = tcCmdPos + 2;

    // Write tcCmdPos back to update tcCmdPos data member
    This->tcCmdPos = tcCmdPos;

    return true;
}

void TestCasePUSFull_resetCommandLoadArea(TestCasePUSFull *This)
{
    This->tcCmdPos = 1;
    tcCommandArea[0] = 0;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Call the test setup service of the super class and then create
 * and configure the components listed in the class comment. 
 * Component creation and configuration of some parameters is only performed the first
 * time this method is executed. Configuration parameters that can updated 
 * once are instead set at every activation. This ensures that all derived test cases
 * can rely on the same initial configuration. The values of
 * the configuration parameters are constants that are defined in file <code>TestConstants.h</code>.
 * This method also loads the PUS event repository in <code>CC_RootObject</code>.
 */
static bool setUpTestCase(void *obj)
{
   TestCaseWithFactoriesClass *tcwfc = GET_CLASS(TYPE_TESTCASEWITHFACTORIES);
   TestCasePUSFull *This = TESTCASEPUSFULL(obj); 
   CC_RootObjectClass *cc_roc;

   if (!TESTCASE_CLASS(tcwfc)->setUpTestCase(obj)) {
       return INITIALIZATION_FAILURE;
   }

   if (firstActivation) {

      // Create the components
      pTmManager = CC_TelemetryManager_new();
      pTmModeMan = DC_PUSTelemetryModeManager_new();
      pTcManager = CC_TelecommandManager_new();
      pManManager = CC_ManoeuvreManager_new();
      pTmLogger = DC_PUSTmLogger_new();
      pTcLoader =  DC_BasicPUSTcLoader_new();
      pEvtRep = DC_PUSEventRepository_new();
      pObsClock = DC_DummyObsClock_new();

      // Configure the non-changeable part of the tc manager
      cc_roc = CC_ROOTOBJECT_GET_CLASS(pTcManager);
      if (cc_roc->isObjectConfigured(pTcManager)) {
        return false;
      }
      CC_TelecommandManager_setPendingTelecommandListSize(pTcManager, 
                                          TC_MAN_PEND_TC_LIST_SIZE);
     
     // Configure the non-changeable part of the tm mode manager
     cc_roc = CC_ROOTOBJECT_GET_CLASS(pTmModeMan);
     if (cc_roc->isObjectConfigured(pTmModeMan)) {
        return false;
     }
     DC_PUSTelemetryModeManager_setMaxNumberOfPackets(pTmModeMan, 
                                      TM_MODE_MAN_MAX_N_PACKETS);

     // Configure the non-changeable part of the tm manager
     cc_roc = CC_ROOTOBJECT_GET_CLASS(pTmManager);
     if (cc_roc->isObjectConfigured(pTmManager)) {
        return false;
     }
     CC_TelemetryManager_setImmediateQueueSize(pTmManager, TM_MAN_IMMEDIATE_QUEUE);

     // Configure the non-changeable part of the manoeuvre manager
     cc_roc = CC_ROOTOBJECT_GET_CLASS(pManManager);
     if (cc_roc->isObjectConfigured(pManManager)) {
        return false;
     }
     CC_ManoeuvreManager_setPendingManoeuvreListSize(pManManager, 
                                  MAN_MAN_PENDING_MAN_LIST_SIZE);

     // Configure the non-changeable part of the tc loader
     cc_roc = CC_ROOTOBJECT_GET_CLASS(pTcLoader);
     if (cc_roc->isObjectConfigured(pTcLoader)) {
        return false;
     }

     // Configure the non-changeable part of the tm stream
     cc_roc = CC_ROOTOBJECT_GET_CLASS(pTmLogger);
     if (cc_roc->isObjectConfigured(pTmLogger)) {
        return false;
     }
     DC_PUSTmLogger_setBufferCapacity(pTmLogger, TM_LOGGER_BUFFER_CAPACITY);
     DC_PUSTmLogger_setMaxPacketLength(pTmLogger, TM_LOGGER_MAX_TM_LENGTH);
     if (!cc_roc->isObjectConfigured(pTmLogger)) {
         return false;
     }

     // Configure the non-changeable part of the evt repository
     cc_roc = CC_ROOTOBJECT_GET_CLASS(pEvtRep);
     if (cc_roc->isObjectConfigured(pEvtRep)) {
         return false;
     }
     DC_EventRepository_setRepositorySize((DC_EventRepository*)pEvtRep, PUS_EVT_REP_SIZE);

     firstActivation = false;
   }

   // Configure the updatable part of the tc manager
   ObsClock *clock = (ObsClock*)TestCasePUSFull_getObsClock(obj);
   CC_TelecommandManager_setObsClock(pTcManager, clock);
   CC_TelecommandManager_setTelecommandLoader(pTcManager, (TelecommandLoader*)pTcLoader);
   cc_roc = CC_ROOTOBJECT_GET_CLASS(pTcManager);
   if (!cc_roc->isObjectConfigured(pTcManager)) {
        return false;
   }

   // Configure the updatable part of the tm mode manager
   ModeManagerClass *mmc = MODEMANAGER_GET_CLASS(pTmModeMan);
   mmc->reset(pTmModeMan);
   cc_roc = CC_ROOTOBJECT_GET_CLASS(pTmModeMan);
   if (!cc_roc->isObjectConfigured(pTmModeMan)) {
        return false;
   }

   // Configure the updatable part of the tm manager
   CC_TelemetryManager_setTelemetryStream(pTmManager, (TelemetryStream*)pTmLogger);
   CC_TelemetryManager_setTelemetryModeManager(pTmManager, (TelemetryModeManager*)pTmModeMan);
   cc_roc = CC_ROOTOBJECT_GET_CLASS(pTmManager);
   if (!cc_roc->isObjectConfigured(pTmManager)) {
        return false;
   }

   // Configure the updatable part of the manoeuvre manager
   cc_roc = CC_ROOTOBJECT_GET_CLASS(pManManager);
   if (!cc_roc->isObjectConfigured(pManManager)) {
        return false;
   }

   // Configure the updatable part of the tc loader
   DC_BasicPUSTcLoader_setMaxNumberOfTc(pTcLoader, TC_COMMAND_AREA_MAX_N_TC);
   DC_BasicPUSTcLoader_setMaxTcLength(pTcLoader, TC_COMMAND_AREA_MAX_TC_LEN);
   DC_BasicPUSTcLoader_setTcLoadAreaStart(pTcLoader, tcCommandArea);
   TelecommandLoader_setTelecommandManager((TelecommandLoader*)pTcLoader, pTcManager);
   cc_roc = CC_ROOTOBJECT_GET_CLASS(pTcLoader);
   if (!cc_roc->isObjectConfigured(pTcLoader)) {
        return false;
   }

    // Configure the updatable part of the evt repository
    DC_EventRepository_setObsClock((DC_EventRepository*)pEvtRep, 
                                   (ObsClock*)TestCasePUSFull_getObsClock(obj));
    DC_PUSEventRepository_setTelemetryManager(pEvtRep, pTmManager);
    cc_roc = CC_ROOTOBJECT_GET_CLASS(pEvtRep);
    if (!cc_roc->isObjectConfigured(pEvtRep)) {
        return false;
    }

    // Swap the event repository
    This->pOldEvtRep = CC_RootObject_getEventRepository();
    CC_RootObject_setEventRepository((DC_EventRepository*)pEvtRep);
    // Reset the telecommand load area
    TestCasePUSFull_resetCommandLoadArea(obj);

    // Clear the mode manager of any packets that were loaded in previous tests  
    TelemetryModeManagerClass *tmmc = TELEMETRYMODEMANAGER_GET_CLASS(pTmModeMan);
    for (tmmc->first(pTmModeMan); 
             !tmmc->isIterationFinished(pTmModeMan); 
                   tmmc->next(pTmModeMan)) 
    {
       TelemetryPacket *pTP = tmmc->getIterationTelemetryPacket(pTmModeMan);

       if (CC_RootObject_getClassId((CC_RootObject*)pTP) != ID_PUSDATAREPORTINGPACKET) {
           return INITIALIZATION_FAILURE;
       } else {
           TD_SID sid = DC_PUSDataReportingPacket_getSID(((DC_PUSDataReportingPacket*)pTP));
           DC_PUSTelemetryModeManager_unloadPacket(pTmModeMan, sid);
       }
    }

    // Flush the functionality managers
    CC_TelecommandManagerClass *cc_tcmc = CC_TELECOMMANDMANAGER_GET_CLASS(pTcManager);
    cc_tcmc->activate(pTcManager);

    CC_TelemetryManagerClass *cc_tmc = CC_TELEMETRYMANAGER_GET_CLASS(pTmManager);
    cc_tmc->activate(pTmManager);
    cc_tmc->activate(pTmManager);

    return INITIALIZATION_SUCCESS;
}

/**
 * Restore the old event repository that was loaded at the time this
 * test case was started.
 * 
 */
static bool shutDownTestCase(void *obj)
{
   TestCasePUSFull *This = TESTCASEPUSFULL(obj); 
   CC_RootObject_setEventRepository(This->pOldEvtRep);

   // TODO The following code is added by myself, I will check this later.
   TestCaseWithFactoriesClass *tcwfc = GET_CLASS(TYPE_TESTCASEWITHFACTORIES);
   if (!TESTCASE_CLASS(tcwfc)->shutDownTestCase(obj)) {
       return SHUTDOWN_FAILURE;
   } else {
       return SHUTDOWN_SUCCESS;
   }
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void post_init(TestCasePUSFull *This, int testId, char *testName)
{
    TESTCASEWITHFACTORIES_GET_CLASS(This)->post_init((TestCaseWithFactories*)This,
                                                      testId, 
                                                      testName);
    return;
}

TestCasePUSFull* TestCasePUSFull_new(int testId, char *testName)
{
   Object *obj = object_new(TYPE_TESTCASEPUSFULL);

   post_init((TestCasePUSFull*)obj, testId, testName);

   return (TestCasePUSFull*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    TestCasePUSFullClass *tcpfc = TESTCASEPUSFULL_CLASS(oc);
    tcpfc->post_init = post_init;

    TestCaseClass *tcc = TESTCASE_CLASS(oc);
    tcc->setUpTestCase = setUpTestCase;
    tcc->shutDownTestCase = shutDownTestCase;

}

static const TypeInfo type_info = {
    .name = TYPE_TESTCASEPUSFULL,
    .parent = TYPE_TESTCASEWITHFACTORIES,
    .instance_size = sizeof(TestCasePUSFull),
    .abstract = false,
    .class_size = sizeof(TestCasePUSFullClass),
    .class_init = class_init,
};

void TestCasePUSFull_register(void)
{
    type_register_static(&type_info);
}
