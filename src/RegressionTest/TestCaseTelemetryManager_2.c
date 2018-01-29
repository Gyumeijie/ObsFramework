//
//
// TestCaseTelemetryManager_2.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/TestConstants.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../Event/DC_EventRepository.h"
#include "../Telemetry/DC_SimpleTelemetryModeManager.h"
#include "../Telemetry/DC_ByteArrayTelemetryStream.h"
#include "../Telemetry/DC_DummyTelemetryPacket.h"
#include "../Telemetry/CC_TelemetryManager.h"
#include "../Telemetry/TelemetryModeManager.h"
#include "TestCaseTelemetryManager_2.h"




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

   // Retrieve the event repository and the event counter
   unsigned int nEvt = TestCaseWithEvtCheck_getNumberOfEvents(obj);

   // Create the telemetry manager
   CC_TelemetryManager *pTm = CC_TelemetryManager_new();
   CC_TelemetryManagerClass *cc_tmc = CC_TELEMETRYMANAGER_GET_CLASS(pTm);

   // Create and configure the dummy telemetry packets
   unsigned char d11 = 11;
   unsigned char d12 = 12;
   unsigned char d21 = 21;
   unsigned char d22 = 22;
   DC_DummyTelemetryPacket *pTW1 = DC_DummyTelemetryPacket_new();
   DC_DummyTelemetryPacket *pTW2 = DC_DummyTelemetryPacket_new();
   DC_DummyTelemetryPacket_setNumberOfBytes(pTW1, 2);
   DC_DummyTelemetryPacket_setValue(pTW1, 0, d11);
   DC_DummyTelemetryPacket_setValue(pTW1, 1, d12);
   DC_DummyTelemetryPacket_setNumberOfBytes(pTW2, 2);
   DC_DummyTelemetryPacket_setValue(pTW2, 0, d21);
   DC_DummyTelemetryPacket_setValue(pTW2, 1, d22);

   // Create, configure and load the telemetry mode manager
   DC_SimpleTelemetryModeManager *pTmMm = DC_SimpleTelemetryModeManager_new();
   ModeManagerClass *mmc = MODEMANAGER_GET_CLASS(pTmMm);
   TelemetryListModeManager_setListLength((void*)pTmMm, 0, 2);
   TelemetryListModeManager_setListItem((void*)pTmMm, 0, 0, (void*)pTW1);
   TelemetryListModeManager_setListItem((void*)pTmMm, 0, 1, (void*)pTW2);
   mmc->reset(pTmMm);
   CC_TelemetryManager_setTelemetryModeManager(pTm, (TelemetryModeManager*)pTmMm);

   // Create, configure and load the telemetry stream
   unsigned int const size = 8;
   unsigned char tmData[size];      // TM data are written here
   for (unsigned int i=0; i<size; i++) {
       tmData[i] = 0;
   }
   DC_ByteArrayTelemetryStream *pTmSt = DC_ByteArrayTelemetryStream_new();
   DC_ByteArrayTelemetryStream_setCapacity(pTmSt, size);
   DC_ByteArrayTelemetryStream_setStartingAddress(pTmSt, tmData);
   CC_TelemetryManager_setTelemetryStream(pTm, (TelemetryStream*)pTmSt);
   CC_TelemetryManager_setImmediateQueueSize(pTm, 2);

   // Check that the components are configured
   if ((!CC_ROOTOBJECT_GET_CLASS(pTm)->isObjectConfigured(pTm)) ||
       (!CC_ROOTOBJECT_GET_CLASS(pTmMm)->isObjectConfigured(pTmMm)) ||
       (!CC_ROOTOBJECT_GET_CLASS(pTmSt)->isObjectConfigured(pTmSt)) ||
       (!CC_ROOTOBJECT_GET_CLASS(pTW1)->isObjectConfigured(pTW1)) ||
       (!CC_ROOTOBJECT_GET_CLASS(pTW2)->isObjectConfigured(pTW2))) 
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong configuration status");
        return;
   }

   // Reset "in use" status
   TelemetryPacket_setInUse((TelemetryPacket*)pTW1, true);
   TelemetryPacket_setInUse((TelemetryPacket*)pTW2, true);

   // Load the TM packets, unload them and check success (try to unload pTW2 twice)
   if (CC_TelemetryManager_isImmediateQueueFull(pTm))
   { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong status of immediate dispatch queue");
        return;
   }
   if (CC_TelemetryManager_getImmediateQueueLoaded(pTm) != 0)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
        "Wrong number of entries in immediate dispatch queue");
        return;
   }
   CC_TelemetryManager_sendTelemetryPacket(pTm, (TelemetryPacket*)pTW1);
   CC_TelemetryManager_sendTelemetryPacket(pTm, (TelemetryPacket*)pTW2);
   if (CC_TelemetryManager_getImmediateQueueLoaded(pTm) != 2)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
        "Wrong number of entries in immediate dispatch queue");
        return;
   }
   if (!CC_TelemetryManager_isImmediateQueueFull(pTm))
   {     
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong status of immediate dispatch queue");
        return;
   }
   CC_TelemetryManager_unloadTelemetryPacket(pTm, (TelemetryPacket*)pTW2);
   if (CC_TelemetryManager_getImmediateQueueLoaded(pTm) != 1)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
        "Wrong number of entries in immediate dispatch queue");
        return;
   }
   if (CC_TelemetryManager_isImmediateQueueFull(pTm))
   { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong status of immediate dispatch queue");
        return;
   }
   CC_TelemetryManager_unloadTelemetryPacket(pTm, (TelemetryPacket*)pTW2);
   if (CC_TelemetryManager_getImmediateQueueLoaded(pTm) != 1)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
        "Wrong number of entries in immediate dispatch queue");
        return;
   }
   CC_TelemetryManager_unloadTelemetryPacket(pTm, (TelemetryPacket*)pTW1);
   if (CC_TelemetryManager_getImmediateQueueLoaded(pTm) != 0)
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
        "Wrong number of entries in immediate dispatch queue");
        return;
   }

   // Activate telemetry manager and check correctness of values sent to TM stream
   // (Recall that the values encapsulated in the DC_DummyTelemetryPacket component
   // are incremented by 1 every time the component receives an update request)
   cc_tmc->activate(pTm);
   if ((tmData[0] != d11+1) || (tmData[1] != d12+1))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong data written to telemetry stream");
        return;
   }
   if ((tmData[2] != d21+1) || (tmData[3] != d22+1))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong data written to telemetry stream");
        return;
   }

   // Check that "in use" status has not been changed
   if (!TelemetryPacket_isInUse((TelemetryPacket*)pTW1))
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong inUse status");
        return;
   }
   if (!TelemetryPacket_isInUse((TelemetryPacket*)pTW2))
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong inUse status");
        return;
   }

   // Submit telemetry packets for immediate dispatch, activate telemetry manager
   // and check that telemetry data are correctly written to telemetry stream
   CC_TelemetryManager_sendTelemetryPacket(pTm, (TelemetryPacket*)pTW1);
   CC_TelemetryManager_sendTelemetryPacket(pTm, (TelemetryPacket*)pTW2);
   cc_tmc->activate(pTm);
   if ((tmData[0] != d11+2) || (tmData[1] != d12+2))
   { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong data written to telemetry stream");
        return;
   }
   if ((tmData[2] != d21+2) || (tmData[3] != d22+2))
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong data written to telemetry stream");
        return;
   }
   if ((tmData[4] != d11+3) || (tmData[5] != d12+3))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong data written to telemetry stream");
        return;
   }
   if ((tmData[6] != d21+3) || (tmData[7] != d22+3))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong data written to telemetry stream");
        return;
   }

   // Check that "in use" status has been set to "not in use"
   if (TelemetryPacket_isInUse((TelemetryPacket*)pTW1))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong inUse status");
        return;
   }
   if (TelemetryPacket_isInUse((TelemetryPacket*)pTW2))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong inUse status");
        return;
   }

   // Reset "in use" status
   TelemetryPacket_setInUse((TelemetryPacket*)pTW1, true);
   TelemetryPacket_setInUse((TelemetryPacket*)pTW2, true);

   // Reset the array where telemetry data are written
   for (unsigned int i=0; i<size; i++) {
       tmData[i] = 0;
   }

   // Force the first telemetry packet to be "not valid"
   DC_DummyTelemetryPacket_setValidStatus(pTW1, NOT_VALID);

   // Activate telemetry manager and check that only the second telemetry packet
   // is sent to TM stream
   cc_tmc->activate(pTm);
   if ((tmData[0] != d21+4) || (tmData[1] != d22+4))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong data written to telemetry stream");
        return;
   }
   if ((tmData[2] != 0) || (tmData[3] != 0))
   { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong data written to telemetry stream");
        return;
   }

   // Check that the correct event was generated
   if (!verifyLatestEvent(obj, nEvt+1, EVT_TM_ITEM_NOT_VALID)) return;
   nEvt++;

   // Decrease the size of the telemetry stream and make the telemetry
   // valid again
   DC_ByteArrayTelemetryStream_setCapacity(pTmSt, 3);
   DC_DummyTelemetryPacket_setValidStatus(pTW1, VALID);

   // Activate the telemetry manager and check that the correct event is generated
   // (The second telemetry packet should have been rejected)
   cc_tmc->activate(pTm);
   if (!verifyLatestEvent(obj, nEvt+1, EVT_TOO_MANY_TM_BYTES)) return;
   nEvt++;

   // Reset the array where telemetry data are written, reset the
   // size of the telemetry stream, and reset the values of the telemetry packets
   DC_ByteArrayTelemetryStream_setCapacity(pTmSt, size);
   DC_DummyTelemetryPacket_setValue(pTW1, 0, d11);
   DC_DummyTelemetryPacket_setValue(pTW1, 1, d12);
   DC_DummyTelemetryPacket_setValue(pTW2, 0, d21);
   DC_DummyTelemetryPacket_setValue(pTW2, 1, d22);
   for (unsigned int i=0; i<size; i++) {
       tmData[i] = 0;
   }

   // Force the first telemetry packet to be "not valid" and submit it for
   // immediate dispatch to the telemetry stream. Activate the telemetry manager.
   // The immediate dispatch packet should not be written to the telemetry stream.
   // Two events should be generated (the telemetry packet is sent twice!)
   DC_DummyTelemetryPacket_setValidStatus(pTW1, NOT_VALID);
   CC_TelemetryManager_sendTelemetryPacket(pTm, (TelemetryPacket*)pTW1);
   cc_tmc->activate(pTm);
   if ((tmData[4] != 0) || (tmData[5] != 0))
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong data written to telemetry stream");
        return;
   }
   if (!verifyLatestEvent(obj, nEvt+2, EVT_TM_ITEM_NOT_VALID)) return;
   if (!verifySpecificEvent(obj, nEvt+1, EVT_TM_ITEM_NOT_VALID)) return;
   nEvt++;
   nEvt++;

   // Check that "in use" status of pTW1 has been set to "not in use"
   if (TelemetryPacket_isInUse((TelemetryPacket*)pTW1))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong inUse status");
        return;
   }
   if (!TelemetryPacket_isInUse((TelemetryPacket*)pTW2))
   {   
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong inUse status");
        return;
   }

   // Reset "in use" status
   TelemetryPacket_setInUse((TelemetryPacket*)pTW1, true);
   TelemetryPacket_setInUse((TelemetryPacket*)pTW2, true);

   // Reset the array where telemetry data are written
   for (unsigned int i=0; i<size; i++) {
       tmData[i] = 0;
   }

   // Decrease the size of the telemetry stream to make it too small for the
   // telemetry packet, make the telemetry valid again, and resubmit for sending
   // to the TM stream
   // Nothing should be written to the TM stream and two events should be generated
   // (one for the repetitive packet and one for the immediate dispatch packet)
   DC_ByteArrayTelemetryStream_setCapacity(pTmSt, 1);
   DC_DummyTelemetryPacket_setValidStatus(pTW1, VALID);
   CC_TelemetryManager_sendTelemetryPacket(pTm, (TelemetryPacket*)pTW1);
   cc_tmc->activate(pTm);
   if ((tmData[0] != 0) || (tmData[1] != 0))
   {
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong data written to telemetry stream");
       return;
   }
   if (!verifyLatestEvent(obj, nEvt+2, EVT_TOO_MANY_TM_BYTES)) return;
   if (!verifySpecificEvent(obj, nEvt+1, EVT_TOO_MANY_TM_BYTES)) return;
   nEvt++;
   nEvt++;

   // Check that "in use" status of pTW1 has been set to "not in use"
   if (TelemetryPacket_isInUse((TelemetryPacket*)pTW1))
   {   
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong inUse status");
        return;
   }
   if (!TelemetryPacket_isInUse((TelemetryPacket*)pTW2))
   {    TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong inUse status");
        return;
   }

   // Reset "in use" status
   TelemetryPacket_setInUse((TelemetryPacket*)pTW1, true);
   TelemetryPacket_setInUse((TelemetryPacket*)pTW2, true);
   // Try to submit three packets for immediate dispatch (the capacity of the
   // imemdiate dispatch queue is 2) and check that the correct event is generated
   CC_TelemetryManager_sendTelemetryPacket(pTm, (TelemetryPacket*)pTW1);
   CC_TelemetryManager_sendTelemetryPacket(pTm, (TelemetryPacket*)pTW1);
   CC_TelemetryManager_sendTelemetryPacket(pTm, (TelemetryPacket*)pTW1);
   if (!verifyLatestEvent(obj, nEvt+1, EVT_TM_QUEUE_FULL)) return;
   nEvt++;

   TestCase_setTestResult((TestCase*)obj, TEST_SUCCESS, "Test Successful");
   return;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj){}

TestCaseTelemetryManager_2* TestCaseTelemetryManager_2_new(void)
{
    Object *obj = object_new(TYPE_TESTCASETELEMETRYMANAGER_2);

    TESTCASEWITHEVTCHECK_GET_CLASS(obj)->post_init((TestCaseWithEvtCheck*)obj,
                                                     ID_TELEMETRYMANAGER*10+2,
                                                "TestCaseTelemetryManager_2"); 

    return (TestCaseTelemetryManager_2*)obj;
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
    .name = TYPE_TESTCASETELEMETRYMANAGER_2,
    .parent = TYPE_TESTCASEWITHEVTCHECK,
    .instance_size = sizeof(TestCaseTelemetryManager_2),
    .abstract = false,
    .class_size = sizeof(TestCaseTelemetryManager_2Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseTelemetryManager_2_register(void)
{
    type_register_static(&type_info);
}
