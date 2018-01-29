//
//
// TestCaseWithFactories.c
//

#include "TestCaseWithFactories.h"
#include "TestCase.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/TestConstants.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../Data/DC_DummyDataPool.h"
#include "../Event/DC_EventRepository.h"
#include "../Data/DC_DummyDatabase.h"
#include "../Manoeuvre/DC_DummyManoeuvre.h"
#include "../Manoeuvre/DC_DummyConfigurableManoeuvre.h"
#include "../Manoeuvre/DC_TestPUSConfigurableManoeuvre.h"
#include "../Manoeuvre/CC_ManoeuvreFactory.h"
#include "../Telemetry/PUSTelemetryPacket.h"
#include "../Telemetry/CC_TelemetryPacketFactory.h"
#include "../Telemetry/DC_PUSTcVerificationPacket.h"
#include "../Telemetry/DC_PUSDataReportingPacket.h"
#include "../Telemetry/DC_DummyPUSTelemetryPacket.h"
#include "../Telemetry/DC_PUSMemoryDumpOffset.h"
#include "../Telemetry/DC_PUSMemoryDumpAbsolute.h"
#include "../Telecommand/DC_PUSMemoryLoadOffset.h"
#include "../Telecommand/DC_PUSMemoryLoadAbsolute.h"
#include "../Telecommand/DC_PUSDumpMemoryOffset.h"
#include "../Telecommand/DC_PUSDumpMemoryAbsolute.h"
#include "../Telecommand/DC_PUSControlDataReporting.h"
#include "../Telecommand/DC_PUSDefineDataReporting.h"
#include "../Telecommand/CC_TelecommandFactory.h"
#include "../Telecommand/DC_DummyTelecommand.h"
#include "../Telecommand/DC_DummyPUSTelecommand.h"
#include "../Telecommand/PUSTelecommand.h"




///////////////////////////////////////////////////////////////////////////////
//
//                            class data
//
///////////////////////////////////////////////////////////////////////////////

static bool firstActivation = true;

static DC_DummyPUSTelemetryPacket *pTmDum1 = pNULL;

static DC_DummyPUSTelemetryPacket *pTmDum2 = pNULL;

static DC_PUSTcVerificationPacket *pTmTVP1 = pNULL;

static DC_PUSDataReportingPacket *pTmDRP1 = pNULL;

static DC_PUSDataReportingPacket *pTmDRP2 = pNULL;

static DC_PUSMemoryDumpOffset *pTmMDO = pNULL;

static DC_PUSMemoryDumpAbsolute *pTmMDA = pNULL;

static DC_DummyConfigurableManoeuvre *pManCD = pNULL;

static DC_TestPUSConfigurableManoeuvre *pManTP = pNULL;

static DC_DummyManoeuvre *pManDum = pNULL;

static DC_DummyPUSTelecommand *pTcPDum = pNULL;

static DC_DummyTelecommand *pTcDum1 = pNULL;

static DC_DummyTelecommand *pTcDum2 = pNULL;

static DC_PUSControlDataReporting *pTcCDR = pNULL;

static DC_PUSDefineDataReporting *pTcDDR = pNULL;

static DC_TestPUSTelecommand *pTcTPT1 = pNULL;

static DC_TestPUSTelecommand *pTcTPT2 = pNULL;

static DC_TestPUSTelecommand *pTcTPT3 = pNULL;

static DC_PUSDumpMemoryOffset *pTcDMO = pNULL;

static DC_PUSDumpMemoryAbsolute *pTcDMA = pNULL;

static DC_PUSMemoryLoadOffset *pTcMLO = pNULL;

static DC_PUSMemoryLoadAbsolute *pTcMLA1 = pNULL;

static DC_PUSMemoryLoadAbsolute *pTcMLA2 = pNULL;



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Call the test setup service of the super class and then initialize the
 * dynamic factories.
 * A pseudo-code implementation of this method is as follows: <PRE>
 *   if(!TestCaseWithEvtCheck::setUpTestCase(void))
 *      return false;
 *   else {
 *    if(first activation of this method) {
 *      retrieve the telemetry packet factory
 *      create telemetry packets for the telemetry packet factory
 *      configure telemetry packets 
 *      load telemetry packets in the telemetry packet factory
 *  
 *      retrieve the telecommand factory
 *      create telecommand components for the telecommand factory
 *      load telecommands in the telecommand factory
 *
 *      retrieve the manoeuvre factory
 *      create manoeuvre components for the manoeuvre factory
 *      load manoeuvres in the manoeuvre factory
 *
 *      return true;
 *    }
 *   } </PRE>
 * Note that the dynamic factories are implemented as singletons that
 * are created and initialized by simply calling their <code>getInstance</code> method.
 */
static bool setUpTestCase(void *obj)
{
   TestCaseWithEvtCheckClass *tcwecc = GET_CLASS(TYPE_TESTCASEWITHEVTCHECK);
   CC_RootObjectClass *cc_roc;
 
   if (!TESTCASE_CLASS(tcwecc)->setUpTestCase(obj)) {
       return INITIALIZATION_FAILURE;
   }

   if (firstActivation) {

     // Instantiate the items to go into the factories
     pTmDum1 = DC_DummyPUSTelemetryPacket_new();
     pTmDum2 = DC_DummyPUSTelemetryPacket_new();
     pTmTVP1 = DC_PUSTcVerificationPacket_new();
     pTmDRP1 = DC_PUSDataReportingPacket_new();
     pTmDRP2 = DC_PUSDataReportingPacket_new();
     pTmMDO = DC_PUSMemoryDumpOffset_new();
     pTmMDA = DC_PUSMemoryDumpAbsolute_new();

     pManCD = DC_DummyConfigurableManoeuvre_new();
     pManTP = DC_TestPUSConfigurableManoeuvre_new();
     pManDum = DC_DummyManoeuvre_new();

     pTcPDum = DC_DummyPUSTelecommand_new();
     pTcDum1 = DC_DummyTelecommand_new();
     pTcDum2 = DC_DummyTelecommand_new();
     pTcCDR = DC_PUSControlDataReporting_new();
     pTcDDR = DC_PUSDefineDataReporting_new();
     pTcTPT1 = DC_TestPUSTelecommand_new();
     pTcTPT2 = DC_TestPUSTelecommand_new();
     pTcTPT3 = DC_TestPUSTelecommand_new();
     pTcDMO = DC_PUSDumpMemoryOffset_new();
     pTcDMA = DC_PUSDumpMemoryAbsolute_new();
     pTcMLO = DC_PUSMemoryLoadOffset_new();
     pTcMLA1 = DC_PUSMemoryLoadAbsolute_new();
     pTcMLA2 = DC_PUSMemoryLoadAbsolute_new();

     // Load the telemetry packet factory
     CC_TelemetryPacketFactory *pTmFct = CC_TelemetryPacketFactory_getInstance();
     CC_TelemetryPacketFactory_setTelemetryPacket(pTmFct, 0, (TelemetryPacket*)pTmDum1);
     CC_TelemetryPacketFactory_setTelemetryPacket(pTmFct, 1, (TelemetryPacket*)pTmDum2);
     CC_TelemetryPacketFactory_setTelemetryPacket(pTmFct, 0, (TelemetryPacket*)pTmTVP1);

     DC_PUSDataReportingPacket_setMaxNumberFA(pTmDRP1, PUS_DRP_MAX_FA);
     DC_PUSDataReportingPacket_setDefinitionBufferSize(pTmDRP1, PUS_DRP_DEF_BUF_SIZE_SMALL);
     DC_PUSDataReportingPacket_setValueBufferSize(pTmDRP1, PUS_DRP_VAL_BUF_SIZE_SMALL);
     CC_TelemetryPacketFactory_setTelemetryPacket(pTmFct, 0, (TelemetryPacket*)pTmDRP1);

     DC_PUSDataReportingPacket_setMaxNumberFA(pTmDRP2, PUS_DRP_MAX_FA);
     DC_PUSDataReportingPacket_setDefinitionBufferSize(pTmDRP2, PUS_DRP_DEF_BUF_SIZE_LARGE);
     DC_PUSDataReportingPacket_setValueBufferSize(pTmDRP2, PUS_DRP_VAL_BUF_SIZE_LARGE);
     CC_TelemetryPacketFactory_setTelemetryPacket(pTmFct, 1, (TelemetryPacket*)pTmDRP2);

     PUSMemoryDump_setDumpBufferSize((PUSMemoryDump*)pTmMDO, PUS_MEM_BUFFER_LENGTH);
     PUSMemoryDump_setMaxNumberBlocks((PUSMemoryDump*)pTmMDO, PUS_NUMBER_MEM_BLOCKS);
     CC_TelemetryPacketFactory_setTelemetryPacket(pTmFct, 0, (TelemetryPacket*)pTmMDO);

     PUSMemoryDump_setDumpBufferSize((PUSMemoryDump*)pTmMDA, PUS_MEM_BUFFER_LENGTH);
     PUSMemoryDump_setMaxNumberBlocks((PUSMemoryDump*)pTmMDA, PUS_NUMBER_MEM_BLOCKS);
     CC_TelemetryPacketFactory_setTelemetryPacket(pTmFct, 0, (TelemetryPacket*)pTmMDA);

     // Load the manoeuvre factory
     CC_ManoeuvreFactory *pManFct = CC_ManoeuvreFactory_getInstance();
     CC_ManoeuvreFactory_setManoeuvre(pManFct, 0, (Manoeuvre*)pManCD);
     CC_ManoeuvreFactory_setManoeuvre(pManFct, 0, (Manoeuvre*)pManTP);
     CC_ManoeuvreFactory_setManoeuvre(pManFct, 0, (Manoeuvre*)pManDum);

     // Load the telecommand factory
     CC_TelecommandFactory *pTcFct = CC_TelecommandFactory_getInstance();
     CC_TelecommandFactory_setTelecommand(pTcFct, 0, (Telecommand*)pTcDum1);
     CC_TelecommandFactory_setTelecommand(pTcFct, 1, (Telecommand*)pTcDum2);
     CC_TelecommandFactory_setTelecommand(pTcFct, 0, (Telecommand*)pTcPDum);

     CC_TelecommandFactory_setTelecommand(pTcFct, 0, (Telecommand*)pTcCDR);
     CC_TelecommandFactory_setTelecommand(pTcFct, 0, (Telecommand*)pTcDDR);

     CC_TelecommandFactory_setTelecommand(pTcFct, 0, (Telecommand*)pTcTPT1);
     CC_TelecommandFactory_setTelecommand(pTcFct, 1, (Telecommand*)pTcTPT2);
     CC_TelecommandFactory_setTelecommand(pTcFct, 2, (Telecommand*)pTcTPT3);

     PUSDumpMemory_setNumberOfRawData((PUSDumpMemory*)pTcDMO, PUS_MEM_BUFFER_LENGTH);
     CC_TelecommandFactory_setTelecommand(pTcFct, 0, (Telecommand*)pTcDMO);

     PUSDumpMemory_setNumberOfRawData((PUSDumpMemory*)pTcDMA, PUS_MEM_BUFFER_LENGTH);
     CC_TelecommandFactory_setTelecommand(pTcFct, 0, (Telecommand*)pTcDMA);

     PUSMemoryLoad_setMaxNumberBlocks((PUSMemoryLoad*)pTcMLA1, PUS_NUMBER_MEM_BLOCKS);
     PUSMemoryLoad_setMaxNumberData((PUSMemoryLoad*)pTcMLA1, PUS_MEM_BUFFER_LENGTH);
     CC_TelecommandFactory_setTelecommand(pTcFct, 0, (Telecommand*)pTcMLA1);

     PUSMemoryLoad_setMaxNumberBlocks((PUSMemoryLoad*)pTcMLA2, PUS_NUMBER_MEM_BLOCKS);
     PUSMemoryLoad_setMaxNumberData((PUSMemoryLoad*)pTcMLA2, PUS_MEM_BUFFER_LENGTH);
     CC_TelecommandFactory_setTelecommand(pTcFct, 1, (Telecommand*)pTcMLA2);

     PUSMemoryLoad_setMaxNumberBlocks((PUSMemoryLoad*)pTcMLO, PUS_NUMBER_MEM_BLOCKS);
     PUSMemoryLoad_setMaxNumberData((PUSMemoryLoad*)pTcMLO, PUS_MEM_BUFFER_LENGTH);
     CC_TelecommandFactory_setTelecommand(pTcFct, 0, (Telecommand*)pTcMLO);

     // Check factory configuration
     cc_roc = CC_ROOTOBJECT_GET_CLASS(pTmFct);
     if (!cc_roc->isObjectConfigured(pTmFct)) {
         TestCase_setTestResult((TestCase*)obj, false, 
                                 "TM Factory is not configured");
         return INITIALIZATION_FAILURE;
     }

     cc_roc = CC_ROOTOBJECT_GET_CLASS(pManFct);
     if (!cc_roc->isObjectConfigured(pManFct)) {
         TestCase_setTestResult((TestCase*)obj, false, 
                                "Manoeuvre Factory is not configured");
         return INITIALIZATION_FAILURE;
     }

     cc_roc = CC_ROOTOBJECT_GET_CLASS(pTcFct);
     if (!cc_roc->isObjectConfigured(pTcFct)) {
         TestCase_setTestResult((TestCase*)obj, false,
                                 "TC Factory is not configured");
         return INITIALIZATION_FAILURE;
     }
     
     firstActivation = false;
   }

   return INITIALIZATION_SUCCESS;
}

/**
 * All the items loaded in the factories in the <code>setUpTestCase</code>
 * method are marked as "not in use". The change in the "in use" status is
 * performed by calling their <code>setInUse</code> method with argument
 * NOT_IN_USE. This relieves
 * concrete subclasses of the need to releases components that they have
 * retrieved from a factory at the end of the test. Note that, if a concrete
 * test case also releases the factory components by calling their <code>setInUse</code>
 * method, this does not give rise to an error.
 * 
 */
static bool shutDownTestCase(void *obj)
{
     TestCaseWithEvtCheckClass *tcwecc = GET_CLASS(TYPE_TESTCASEWITHEVTCHECK);
     
     // Mark all items loaded in the factories as "not in use"
     TelemetryPacket_setInUse((TelemetryPacket*)pTmDum1, NOT_IN_USE);
     TelemetryPacket_setInUse((TelemetryPacket*)pTmDum2, NOT_IN_USE);
     TelemetryPacket_setInUse((TelemetryPacket*)pTmTVP1, NOT_IN_USE);
     TelemetryPacket_setInUse((TelemetryPacket*)pTmDRP1, NOT_IN_USE);
     TelemetryPacket_setInUse((TelemetryPacket*)pTmDRP2, NOT_IN_USE);
     TelemetryPacket_setInUse((TelemetryPacket*)pTmMDO, NOT_IN_USE);
     TelemetryPacket_setInUse((TelemetryPacket*)pTmMDA, NOT_IN_USE);

     Manoeuvre_setInUse((Manoeuvre*)pManCD, NOT_IN_USE);
     Manoeuvre_setInUse((Manoeuvre*)pManDum, NOT_IN_USE);
     Manoeuvre_setInUse((Manoeuvre*)pManTP, NOT_IN_USE);

     Telecommand_setInUse((Telecommand*)pTcDum1, NOT_IN_USE);
     Telecommand_setInUse((Telecommand*)pTcDum2, NOT_IN_USE);
     Telecommand_setInUse((Telecommand*)pTcPDum, NOT_IN_USE);
     Telecommand_setInUse((Telecommand*)pTcCDR, NOT_IN_USE);
     Telecommand_setInUse((Telecommand*)pTcDDR, NOT_IN_USE);
     Telecommand_setInUse((Telecommand*)pTcTPT1, NOT_IN_USE);
     Telecommand_setInUse((Telecommand*)pTcTPT2, NOT_IN_USE);
     Telecommand_setInUse((Telecommand*)pTcTPT3, NOT_IN_USE);
     Telecommand_setInUse((Telecommand*)pTcDMO, NOT_IN_USE);
     Telecommand_setInUse((Telecommand*)pTcDMA, NOT_IN_USE);
     Telecommand_setInUse((Telecommand*)pTcMLA1, NOT_IN_USE);
     Telecommand_setInUse((Telecommand*)pTcMLA2, NOT_IN_USE);
     Telecommand_setInUse((Telecommand*)pTcMLO, NOT_IN_USE);

     if (!TESTCASE_CLASS(tcwecc)->shutDownTestCase(obj)) { 
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

static void post_init(TestCaseWithFactories *This, int testId, char *testName)
{
    TESTCASEWITHEVTCHECK_GET_CLASS(This)->post_init((TestCaseWithEvtCheck*)This,
                                                     testId, 
                                                     testName);
    return;
}

TestCaseWithFactories* TestCaseWithFactories_new(int testId, char *testName)
{
   Object *obj = object_new(TYPE_TESTCASEWITHFACTORIES);
   
   post_init((TestCaseWithFactories*)obj, testId, testName);

   return (TestCaseWithFactories*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    TestCaseClass *tcc = TESTCASE_CLASS(oc);
    tcc->setUpTestCase = setUpTestCase;
    tcc->shutDownTestCase = shutDownTestCase;

    TestCaseWithFactoriesClass *tcwfc = TESTCASEWITHFACTORIES_CLASS(oc);
    tcwfc->post_init = post_init;
}

static const TypeInfo type_info = {
    .name = TYPE_TESTCASEWITHFACTORIES,
    .parent = TYPE_TESTCASEWITHEVTCHECK,
    .instance_size = sizeof(TestCaseWithFactories),
    .abstract = false,
    .class_size = sizeof(TestCaseWithFactoriesClass),
    .class_init = class_init,
};

void TestCaseWithFactories_register(void)
{
    type_register_static(&type_info);
}
