//
//
// TestCaseByteArrayTelemetryStream_1.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/TestCompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/TestConstants.h"
#include "../Telemetry/DC_ByteArrayTelemetryStream.h"
#include "../Telemetry/DC_DummyTelemetryPacket.h"
#include "TestCaseByteArrayTelemetryStream_1.h"



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

   // Create the byte array
   unsigned int const size = 5;
   unsigned char ba[size];
   for (unsigned int i=0; i<size; i++) {
       ba[i] = 0;
   }

   // Create the telemetry stream component
   DC_ByteArrayTelemetryStream *pTmStream = DC_ByteArrayTelemetryStream_new();
   TelemetryStreamClass *tsc = TELEMETRYSTREAM_GET_CLASS(pTmStream); 
   CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pTmStream);
   
   // Create and configure the telemetry packet to be written to the stream
   DC_DummyTelemetryPacket *pTI = DC_DummyTelemetryPacket_new();
   TelemetryPacketClass *tpc = TELEMETRYPACKET_GET_CLASS(pTI);

   DC_DummyTelemetryPacket_setNumberOfBytes(pTI, 2);
   DC_DummyTelemetryPacket_setValue(pTI, 0,1);
   DC_DummyTelemetryPacket_setValue(pTI, 1,2);

   // Check the value of the class identifier
   if (CC_RootObject_getClassId((CC_RootObject*)pTmStream) != ID_BYTEARRAYTELEMETRYSTREAM)
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong class identifier");
        return;
   }

   // Check that the telemetry stream is not configured
   if (cc_roc->isObjectConfigured(pTmStream))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong object configuration status");
        return;
   }

   // Set the size of the byte array and verify correctness
   DC_ByteArrayTelemetryStream_setCapacity(pTmStream, size);
   if (tsc->getCapacity(pTmStream) != size)
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong telemetry stream size");
        return;
   }

   // Set the starting address of the byte array and verify correctness
   DC_ByteArrayTelemetryStream_setStartingAddress(pTmStream, ba);
   if (DC_ByteArrayTelemetryStream_getStartingAddress(pTmStream) != ba)
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong byte array starting address");
        return;
   }

   // Check that the telemetry stream is now configured
   if (!cc_roc->isObjectConfigured(pTmStream))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong object configuration status");
        return;
   }

   // Make write requests and check success
   tsc->write(pTmStream, (TelemetryPacket*)pTI);
   if ((ba[0] != 1) || (ba[1] != 2))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Write request failed");
        return;
   }

   // Check doesPacketFit method
   if (!tsc->doesPacketFit(pTmStream, (TelemetryPacket*)pTI))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Failure of method doesPacketFit");
        return;
   }

   // Write a new telemetry packet and check again doesPacketFit method (now it should fail)
   tsc->write(pTmStream, (TelemetryPacket*)pTI);
   if (tsc->doesPacketFit(pTmStream, (TelemetryPacket*)pTI))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Failure of method doesPacketFit");
        return;
   }

   // Make a write request that should be only partially executed
   tsc->write(pTmStream, (TelemetryPacket*)pTI);
   if (ba[4] != 1)
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Write request failed");
        return;
   }

   // Reset telemetry stream and verify new write request
   tsc->reset(pTmStream);
   DC_DummyTelemetryPacket_setValue(pTI, 0, 3);
   DC_DummyTelemetryPacket_setValue(pTI, 1, 4);
   tsc->write(pTmStream, (TelemetryPacket*)pTI);
   if ((ba[0] != 3) || (ba[1] != 4))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Write request failed");
        return;
   }

   // Saturate again the telemetry stream, flush and write again
   tsc->write(pTmStream, (TelemetryPacket*)pTI);
   tsc->write(pTmStream, (TelemetryPacket*)pTI);
   tsc->flush(pTmStream);
   DC_DummyTelemetryPacket_setValue(pTI, 0, 5);
   DC_DummyTelemetryPacket_setValue(pTI, 1, 6);
   tsc->write(pTmStream, (TelemetryPacket*)pTI);
   if ((ba[0] != 5) || (ba[1] != 6))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Write request failed");
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

TestCaseByteArrayTelemetryStream_1* TestCaseByteArrayTelemetryStream_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEBYTEARRAYTELEMETRYSTREAM_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                             ID_BYTEARRAYTELEMETRYSTREAM*10+1,
                                        "TestCaseByteArrayTelemetryStream_1"); 

    return (TestCaseByteArrayTelemetryStream_1*)obj;
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
    .name = TYPE_TESTCASEBYTEARRAYTELEMETRYSTREAM_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseByteArrayTelemetryStream_1),
    .abstract = false,
    .class_size = sizeof(TestCaseByteArrayTelemetryStream_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseByteArrayTelemetryStream_1_register(void)
{
    type_register_static(&type_info);
}
