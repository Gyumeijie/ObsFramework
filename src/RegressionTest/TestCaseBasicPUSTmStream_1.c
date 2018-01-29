//
//
// TestCaseBasicPUSTmStream_1.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "../Telemetry/CC_TelemetryPacketFactory.h"
#include "../Telemetry/DC_DummyPUSTelemetryPacket.h"
#include "../Telemetry/DC_BasicPUSTmStream.h"
#include "../Data/DC_SampleFullDataPool.h"
#include "TestCaseBasicPUSTmStream_1.h"

#include <string.h>
#include <assert.h>



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////


bool TestCaseBasicPUSTmStream_1_checkTmImage
(
    TestCaseBasicPUSTmStream_1 *This, 
    unsigned int start, 
    unsigned char value
)
{
    unsigned short usTemp = 0;
    unsigned char ucTemp = 0;
    TD_ObsTime otTemp = 0;
    assert(sizeof(unsigned short) == 2);

    // In order to access the following variables concisely below
    unsigned char const *tmArea = This->tmArea;
    DC_DummyPUSTelemetryPacket* const pTM = This->pTM;
    DC_BasicPUSTmStream* const pTMS = This->pTMS;

    TelemetryPacketClass *tpc = TELEMETRYPACKET_GET_CLASS(pTM);

    memcpy(&usTemp, This->tmArea+start, 2);
    if (usTemp != PUSTelemetryPacket_getPacketId()) {
        TestCase_setTestResult((TestCase*)This, TEST_FAILURE,
                                "Bytes 0 and 1 of header are wrong");
        return false;
    }

    memcpy(&usTemp, tmArea+start+2, 2);
    if (usTemp != (0xC0+DC_BasicPUSTmStream_getSequenceCounter(pTMS))) {
        TestCase_setTestResult((TestCase*)This, TEST_FAILURE,
                                "Bytes 2 and 3 of header are wrong");
        return false;
    }

    memcpy(&usTemp, tmArea+start+4, 2);
    if (usTemp != (3+sizeof(TD_ObsTime)+tpc->getNumberOfBytes(pTM)+2)) {
        TestCase_setTestResult((TestCase*)This, TEST_FAILURE,
                                "Bytes 4 and 5 of header are wrong");
        return false;
    }

    memcpy(&ucTemp, tmArea+start+6, 1);
    if (ucTemp != 0x10) {
        TestCase_setTestResult((TestCase*)This, TEST_FAILURE,
                               "Byte 1 of data field is wrong");
        return false;
    }

    memcpy(&ucTemp, tmArea+start+7, 1);
    if (ucTemp != tpc->getType(pTM)) {
        TestCase_setTestResult((TestCase*)This, TEST_FAILURE,
                               "Byte 2 of data field is wrong");
        return false;
    }

    memcpy(&ucTemp, tmArea+start+8, 1);
    if (ucTemp != tpc->getSubType(pTM)) {
        TestCase_setTestResult((TestCase*)This, TEST_FAILURE,
                                "Byte 3 of data field is wrong");
        return false;
    }

    memcpy(&otTemp, tmArea+start+9, sizeof(TD_ObsTime));
    if (otTemp != tpc->getTimeTag(pTM)) {
        TestCase_setTestResult((TestCase*)This, TEST_FAILURE, 
                                "Time field is wrong");
        return false;
    }

    memcpy(&ucTemp, tmArea+start+9+sizeof(TD_ObsTime), 1);
    if (usTemp != value) {
        TestCase_setTestResult((TestCase*)This, TEST_FAILURE,
                               "Application data field is wrong");
        return false;
    }

    memcpy(&usTemp, tmArea+start+9+sizeof(TD_ObsTime)+1, 2);
    if (usTemp != (unsigned short)0) {
        TestCase_setTestResult((TestCase*)This, TEST_FAILURE,
                                "Error control field is wrong");
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
    TestCaseBasicPUSTmStream_1 *This = TESTCASEBASICPUSTMSTREAM_1(obj);

    const unsigned int TM_AREA_SIZE = 50;
    This->tmArea = g_malloc(sizeof(unsigned char)*TM_AREA_SIZE);
    CC_TelemetryPacketFactory *pTCF = CC_TelemetryPacketFactory_getInstance();

    unsigned int capacity;
    unsigned int numPacket;
    capacity = CC_TelemetryPacketFactory_getCapacityDummyPUSTelemetryPacket(pTCF);
    numPacket = CC_TelemetryPacketFactory_getNumberDummyPUSTelemetryPacket(pTCF);
    if (capacity == numPacket)
    {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "No more available TM packets");
    	return;
    }
    This->pTM = CC_TelemetryPacketFactory_allocateDummyPUSTelemetryPacket(pTCF);
    unsigned int nEvt = TestCaseWithEvtCheck_getNumberOfEvents(obj);
    This->pTMS = DC_BasicPUSTmStream_new();

    // In order to access the following variables concisely below
    unsigned char* const tmArea = This->tmArea;
    DC_DummyPUSTelemetryPacket* const pTM = This->pTM;
    DC_BasicPUSTmStream* const pTMS = This->pTMS;

    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pTMS); 
    TelemetryStreamClass *tsc = TELEMETRYSTREAM_GET_CLASS(pTMS);
    TelemetryPacketClass *tpc = TELEMETRYPACKET_GET_CLASS(pTM);

    // Check the correctness of the class identifier
    if ((CC_RootObject_getClassId((CC_RootObject*)pTMS) != ID_BASICPUSTMSTREAM))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong class identifier");
        return;
    }

    // Check that tm stream is initially not configured
    if (cc_roc->isObjectConfigured(pTMS))
    {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong configuration status");
        return;
    }

    // Set stream capacity and check success
    DC_BasicPUSTmStream_setCapacity(pTMS, TM_AREA_SIZE);
    if (tsc->getCapacity(pTMS) != TM_AREA_SIZE)
    {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong stream capacity");
        return;
    }

    // Set the start address of the telemetry write area and check success
    DC_BasicPUSTmStream_setStartAddress(pTMS, tmArea);
    if (DC_BasicPUSTmStream_getStartAddress(pTMS) != tmArea)
    {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong tm write area address");
        return;
    }

    // Check that tm stream is configured
    if (!cc_roc->isObjectConfigured(pTMS))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong configuration status");
        return;
    }

    // Check initial value of packet counter
    if (DC_BasicPUSTmStream_getPacketCounter(pTMS) != 0)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong packet counter value");
        return;
    }

    // Get initial value of sequence counter
    unsigned int seqCounter = DC_BasicPUSTmStream_getSequenceCounter(pTMS);

    // Configure the TM packet and write it to the TM stream
    unsigned char value = 10;
    DC_DummyPUSTelemetryPacket_setValue(pTM, value);
    tsc->write(pTMS, (TelemetryPacket*)pTM);
    if (!TestCaseBasicPUSTmStream_1_checkTmImage(This, 1, value))
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Incorrect packet image");
        return;
    }

    // Check the value of the packet counter
    if (DC_BasicPUSTmStream_getPacketCounter(pTMS) != 1)
    {   
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong packet counter value");
        return;
    }

    // Check the value of the sequence counter
    if (DC_BasicPUSTmStream_getSequenceCounter(pTMS) != seqCounter+1)
    {   
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong sequence counter value");
        return;
    }
    
    // Compute maximum number of packets that fit in the telemetry area
    unsigned int maxNPackets;
    maxNPackets = (TM_AREA_SIZE-1)/(tpc->getNumberOfBytes(pTM)+11+sizeof(TD_ObsTime));

    // Fill up the telemetry write area
    for (unsigned int i=1; i<(maxNPackets+1); i++) {
        tsc->write(pTMS, (TelemetryPacket*)pTM);
    }

    // Check that the correct event was generated
    if (!verifyLatestEvent(obj, nEvt+1, EVT_TM_STREAM_END)) return;

    // Check the value of the packet counter
    if (DC_BasicPUSTmStream_getPacketCounter(pTMS) != maxNPackets)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong packet counter value");
        return;
    }

    // Check the value of the sequence counter
    if (DC_BasicPUSTmStream_getSequenceCounter(pTMS) != seqCounter+maxNPackets+1)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong sequence counter value");
        return;
    }

    // Reset stream and check success
    tsc->reset(pTMS);
    if (DC_BasicPUSTmStream_getPacketCounter(pTMS) != 0)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong packet counter value");
        return;
    }

    // Write operation should now succeed
    tsc->write(pTMS, (TelemetryPacket*)pTM);
    if (DC_BasicPUSTmStream_getPacketCounter(pTMS) != 1)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong packet counter value");
        return;
    }
    if (TestCaseWithEvtCheck_getNumberOfEvents(obj) != nEvt+1)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong number of events");
        return;
    }

    // Fill up again the telemetry write area
    for (unsigned int i=1; i<(maxNPackets+1); i++) {
        tsc->write(pTMS, (TelemetryPacket*)pTM);
    }

    // Flush stream and check success
    tsc->flush(pTMS);
    if (DC_BasicPUSTmStream_getPacketCounter(pTMS) != 0)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong packet counter value");
        return;
    }

    // Write operation should now succeed
    tsc->write(pTMS, (TelemetryPacket*)pTM);
    if (DC_BasicPUSTmStream_getPacketCounter(pTMS) != 1)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong packet counter value");
        return;
    }
    if (TestCaseWithEvtCheck_getNumberOfEvents(obj) != nEvt+2)
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong number of events");
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

TestCaseBasicPUSTmStream_1* TestCaseBasicPUSTmStream_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEBASICPUSTMSTREAM_1);

    TESTCASEWITHFACTORIES_GET_CLASS(obj)->post_init((TestCaseWithFactories*)obj,
                                                       ID_BASICPUSTMSTREAM*10+1,
                                                  "TestCaseBasicPUSTmStream_1"); 
    return (TestCaseBasicPUSTmStream_1*)obj;
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
    .name = TYPE_TESTCASEBASICPUSTMSTREAM_1,
    .parent = TYPE_TESTCASEWITHFACTORIES,
    .instance_size = sizeof(TestCaseBasicPUSTmStream_1),
    .abstract = false,
    .class_size = sizeof(TestCaseBasicPUSTmStream_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseBasicPUSTmStream_1_register(void)
{
    type_register_static(&type_info);
}
