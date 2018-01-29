//
//
// TestCaseDummyTelemetryPacket_1.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/TestConstants.h"
#include "../GeneralInclude/Constants.h"
#include "../Telemetry/DC_DummyTelemetryPacket.h"
#include "TestCaseDummyTelemetryPacket_1.h"



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
   DC_DummyTelemetryPacket *pTmWord = DC_DummyTelemetryPacket_new();
   TelemetryPacketClass *tpc = TELEMETRYPACKET_GET_CLASS(pTmWord);
   CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pTmWord);

   // Check the value of the class identifier
   if (CC_RootObject_getClassId((CC_RootObject*)pTmWord) != ID_DUMMYTELEMETRYITEM) {    
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong class identifier");
       return;
   }

   // Check configuration statur
   if (cc_roc->isObjectConfigured(pTmWord)) {    
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong configuration status");
       return;
   }

   // Set number of bytes and check configuration status
   DC_DummyTelemetryPacket_setNumberOfBytes(pTmWord, 2);
   if (!cc_roc->isObjectConfigured(pTmWord)) {    
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong configuration status");
       return;
   }

   // Check number of bytes
   if (tpc->getNumberOfBytes(pTmWord) != 2) {    
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong number of bytes");
       return;
   }

   // Check default value of the encapsulated telemetry bytes
   if (tpc->getUnsignedByte(pTmWord, 0) != 0) {    
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong telemetry byte value");
       return;
   }
   if (tpc->getUnsignedByte(pTmWord, 1) != 0) {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong telemetry byte value");
        return;
   }

   // Set and read out the encapsulated telemetry byte
   DC_DummyTelemetryPacket_setValue(pTmWord, 0, 1);
   if (tpc->getUnsignedByte(pTmWord, 0) != 1) {    
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong telemetry byte value");
       return;
   }
   DC_DummyTelemetryPacket_setValue(pTmWord, 1, 2);
   if (tpc->getUnsignedByte(pTmWord, 1) != 2) {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong telemetry byte value");
        return;
   }

   // Check default value of the validity check service
   if (!tpc->isValid(pTmWord)) {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong validity check result");
        return;
   }

   // Set and read out the validity status
   DC_DummyTelemetryPacket_setValidStatus(pTmWord, NOT_VALID);
   if (tpc->isValid(pTmWord)) {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong validity check result");
        return;
   }

   // Check update service (the update service simply increments by one the
   // value of the telemetry bytes)
   tpc->update(pTmWord);
   if (tpc->getUnsignedByte(pTmWord, 0) != 2) {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong telemetry byte value");
        return;
   }
   if (tpc->getUnsignedByte(pTmWord, 1) != 3) {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong telemetry byte value");
        return;
   }

   // Check update service with wrap around
   DC_DummyTelemetryPacket_setValue(pTmWord, 0, 255);
   tpc->update(pTmWord);
   if (tpc->getUnsignedByte(pTmWord, 0) != 0) {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong telemetry byte value");
        return;
   }
   if (tpc->getUnsignedByte(pTmWord, 1) != 4) {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong telemetry byte value");
        return;
   }

   // Check default values of non-implemented attributes
   if (tpc->getDestination(pTmWord) != 0) {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong telemetry destination");
        return;
   }
   
   TD_TelemetryType type = CC_RootObject_getClassId((CC_RootObject*)pTmWord)%256;
   if (tpc->getType(pTmWord) != type) {    
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong telemetry type");
       return;
   }
   if (tpc->getSubType(pTmWord) != 0) {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong telemetry sub type");
        return;
   }
   if (tpc->getTimeTag(pTmWord) != 0) {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong telemetry time tag");
        return;
   }

   if (TelemetryPacket_isInUse((TelemetryPacket*)pTmWord)) {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong inUse status");
        return;
   }

   // Check implementation of "in use" flag
   TelemetryPacket_setInUse((TelemetryPacket*)pTmWord, true);
   if (!TelemetryPacket_isInUse((TelemetryPacket*)pTmWord)) {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong inUse status");
        return;
   }

   // Check number of bytes
   if (tpc->getNumberOfBytes(pTmWord) != 2) {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong number of bytes");
        return;
   }

   // Check default value of fast acquisition service
   if (tpc->getStartAddress(pTmWord) != pNULL) {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong fast aquisition service");
        return;
   }
   if (tpc->isFastAcquisitionImplemented(pTmWord)) {    
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
       "Wrong fast aquisition service availability check");
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

TestCaseDummyTelemetryPacket_1* TestCaseDummyTelemetryPacket_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEDUMMYTELEMETRYPACKET_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
	                                               ID_DUMMYTELEMETRYITEM*10+1,
                                            "TestCaseDummyTelemetryPacket_1");

    return (TestCaseDummyTelemetryPacket_1*)obj;
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
    .name = TYPE_TESTCASEDUMMYTELEMETRYPACKET_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseDummyTelemetryPacket_1),
    .abstract = false,
    .class_size = sizeof(TestCaseDummyTelemetryPacket_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseDummyTelemetryPacket_1_register(void)
{
    type_register_static(&type_info);
}
