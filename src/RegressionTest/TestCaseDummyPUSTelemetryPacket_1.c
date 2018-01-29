//
//
// TestCaseDummyPUSTelemetryPacket_1.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/TestConstants.h"
#include "../GeneralInclude/Constants.h"
#include "../Telemetry/DC_DummyPUSTelemetryPacket.h"
#include "../System/DC_DummyObsClock.h"
#include "TestCaseDummyPUSTelemetryPacket_1.h"



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
   DC_DummyPUSTelemetryPacket *pTmWord = DC_DummyPUSTelemetryPacket_new();
   CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pTmWord);
   TelemetryPacketClass *tpc = TELEMETRYPACKET_GET_CLASS(pTmWord);

   // Check the value of the class identifier
   if (CC_RootObject_getClassId((CC_RootObject*)pTmWord) != ID_DUMMYPUSTELEMETRYPACKET) {    
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong class identifier");
       return;
   }

   // Verify that the object is configured
   if (!cc_roc->isObjectConfigured(pTmWord)) {
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong configuration status");
       return;
   }

   // Check default value of the encapsulated telemetry byte
   if (tpc->getUnsignedByte(pTmWord, 0) != 0) {    
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong telemetry byte value");
       return;
   }

   // Set and read out the encapsulated telemetry byte
   DC_DummyPUSTelemetryPacket_setValue(pTmWord, 2);
   if (tpc->getUnsignedByte(pTmWord, 0) != 2) {    
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong telemetry byte value");
       return;
   }

   // Check update service
   tpc->update(pTmWord);
   if (tpc->getUnsignedByte(pTmWord, 0) != 3) {    
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                              "Wrong telemetry byte value");
       return;
   }

   // Check update service with wrap around
   DC_DummyPUSTelemetryPacket_setValue(pTmWord, 255);
   tpc->update(pTmWord);
   if (tpc->getUnsignedByte(pTmWord, 0) != 0) {    
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong telemetry byte value");
       return;
   }

   // Check the attribute values
   if (PUSTelemetryPacket_getDefaultDestination() != TEST_TM_DEF_DEST) {
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong default telemetry destination");
       return;
   }

   if (tpc->getDestination(pTmWord) != TEST_TM_DEF_DEST) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong telemetry destination");
        return;
   }
   if (tpc->getType(pTmWord) != TEST_TM_TYPE) { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong telemetry type");
        return;
   }
   if (tpc->getSubType(pTmWord) != TEST_TM_SUBTYPE) { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong telemetry sub type");
        return;
   }
   if (tpc->getTimeTag(pTmWord) != TEST_TM_TIMETAG) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong telemetry time tag");
        return;
   }
   if (PUSTelemetryPacket_getPacketId() != (2048+TEST_TM_APID)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong packet ID");
        return;
   }

   // Update TM destination and check success
   tpc->setDestination(pTmWord, TEST_TM_DEST);
   if (tpc->getDestination(pTmWord) != TEST_TM_DEST) { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong telemetry destination");
        return;
   }

   // Check OBS clock
   if (PUSTelemetryPacket_getObsClock() == pNULL) { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong clock plug-in");
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

TestCaseDummyPUSTelemetryPacket_1* TestCaseDummyPUSTelemetryPacket_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEDUMMYPUSTELEMETRYPACKET_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                              ID_DUMMYPUSTELEMETRYPACKET*10+1,
                                         "TestCaseDummyPUSTelemetryPacket_1"); 

    return (TestCaseDummyPUSTelemetryPacket_1*)obj;
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
    .name = TYPE_TESTCASEDUMMYPUSTELEMETRYPACKET_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseDummyPUSTelemetryPacket_1),
    .abstract = false,
    .class_size = sizeof(TestCaseDummyPUSTelemetryPacket_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseDummyPUSTelemetryPacket_1_register(void)
{
    type_register_static(&type_info);
}
