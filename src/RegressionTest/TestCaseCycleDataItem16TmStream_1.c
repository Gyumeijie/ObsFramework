//
//
// TestCaseCycleDataItem16TmStream_1.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/TestConstants.h"
#include "../Telemetry/DC_CycleDataItem16TmStream.h"
#include "../Telemetry/DC_DummyTelemetryPacket.h"
#include "../Data/DC_DataItem.h"
#include "../Data/DC_RawDataItem.h"
#include "TestCaseCycleDataItem16TmStream_1.h"



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

   // Create three data item components
   unsigned short var1, var2, var3;
   DC_RawDataItem *pd1 = DC_RawDataItem_new(&var1);
   DC_RawDataItem *pd2 = DC_RawDataItem_new(&var2);
   DC_RawDataItem *pd3 = DC_RawDataItem_new(&var3);

   // Create and configure the dummy telemetry data item
   unsigned char d1 = 1;
   unsigned char d2 = 2;
   unsigned char d3 = 3;
   unsigned char d4 = 4;
   DC_DummyTelemetryPacket *pTW1 = DC_DummyTelemetryPacket_new();
   DC_DummyTelemetryPacket_setNumberOfBytes(pTW1, 4);
   DC_DummyTelemetryPacket_setValue(pTW1, 0, d1);
   DC_DummyTelemetryPacket_setValue(pTW1, 1, d2);
   DC_DummyTelemetryPacket_setValue(pTW1, 2, d3);
   DC_DummyTelemetryPacket_setValue(pTW1, 3, d4);

   // Create the CycleDataItem16TmStream_1 component
   DC_CycleDataItem16TmStream *pTmStream = DC_CycleDataItem16TmStream_new();
   CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pTmStream);
   TelemetryStreamClass *tsc = TELEMETRYSTREAM_GET_CLASS(pTmStream);

   // Check the value of the class identifier
   if (CC_RootObject_getClassId((CC_RootObject*)pTmStream) != ID_CYCLEDATAITEM16TMSTREAM)
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

   // Set the size of the telemetry stream and verify correctness
   DC_CycleDataItem16TmStream_setNumberOfDataItems(pTmStream, 3);
   if (tsc->getCapacity(pTmStream) != 3)
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong telemetry stream size");
        return;
   }

   // Load the data item into the telemetry stream and check that the
   // telemetry stream object becomes configured
   DC_CycleDataItem16TmStream_setDataItem(pTmStream, 0, pd1);
   DC_CycleDataItem16TmStream_setDataItem(pTmStream, 1, pd2);
   DC_CycleDataItem16TmStream_setDataItem(pTmStream, 2, pd3);
   if (!cc_roc->isObjectConfigured(pTmStream))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong object configuration status");
        return;
   }

   // Check that the telemetry packet can be written to the telemetry stream
   if (!tsc->doesPacketFit(pTmStream, (TelemetryPacket*)pTW1))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Check on telemetry stream capacity failed");
        return;
   }

   // Make a write request to the telemetry stream and check correctness
   // (Recall that when a pair of bytes read from the telemetry packet are
   // written to a data item, the first byte is overlaid upon the least
   // significant byte of the data item and the second byte is overlaid upon
   // the most significant byte)
   tsc->write(pTmStream, (TelemetryPacket*)pTW1);
   if ((DC_RawDataItem_getUnsignedShort(pd1) != d1+256*d2) ||
       (DC_RawDataItem_getUnsignedShort(pd2) != d3+256*d4))
   {    TestCase_setTestResult((TestCase*)obj,TEST_FAILURE, "Write operations failed");
        return;
   }

   // Check whether the telemetry packet can be written again to the telemetry stream
   if (tsc->doesPacketFit(pTmStream, (TelemetryPacket*)pTW1))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Check on telemetry stream capacity failed");
        return;
   }

   // Rewrite the telemetry packet and check that the first two bytes were correctly written
   tsc->write(pTmStream, (TelemetryPacket*)pTW1);
   if ((DC_RawDataItem_getUnsignedShort(pd3) != d1+256*d2))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Write operations failed");
        return;
   }

   // Reset the telemetry stream and clear all data items
   tsc->reset(pTmStream);
   DC_RawDataItem_setUnsignedShort(pd1, 0);
   DC_RawDataItem_setUnsignedShort(pd2, 0);
   DC_RawDataItem_setUnsignedShort(pd3, 0);

   // Check that the telemetry packet can be written to the telemetry stream
   if (!tsc->doesPacketFit(pTmStream, (TelemetryPacket*)pTW1))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Check on telemetry stream capacity failed");
        return;
   }

   // Make a write request to the telemetry stream and check correctness
   tsc->write(pTmStream, (TelemetryPacket*)pTW1);
   if ((DC_RawDataItem_getUnsignedShort(pd1) != d1+256*d2) ||
       (DC_RawDataItem_getUnsignedShort(pd2) != d3+256*d4))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Write operations failed");
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

TestCaseCycleDataItem16TmStream_1* TestCaseCycleDataItem16TmStream_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASECYCLEDATAITEM16TMSTREAM_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                              ID_CYCLEDATAITEM16TMSTREAM*10+1,
                                         "TestCaseCycleDataItem16TmStream_1");

    return (TestCaseCycleDataItem16TmStream_1*)obj;
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
    .name = TYPE_TESTCASECYCLEDATAITEM16TMSTREAM_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseCycleDataItem16TmStream_1),
    .abstract = false,
    .class_size = sizeof(TestCaseCycleDataItem16TmStream_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseCycleDataItem16TmStream_1_register(void)
{
    type_register_static(&type_info);
}
