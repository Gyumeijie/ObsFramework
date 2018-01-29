//
//
// TestCaseFileTelemetryStream_1.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/TestConstants.h"
#include "../GeneralInclude/Constants.h"
#include "../Telemetry/DC_FileTelemetryStream.h"
#include "../Telemetry/DC_DummyTelemetryPacket.h"
#include "TestCaseFileTelemetryStream_1.h"
#include <stdio.h>



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

   DC_FileTelemetryStream *pTmStream = DC_FileTelemetryStream_new();
   CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pTmStream);
   TelemetryStreamClass *tsc = TELEMETRYSTREAM_GET_CLASS(pTmStream);

   // Check the value of the class identifier
   if (CC_RootObject_getClassId((CC_RootObject*)pTmStream) != ID_FILETELEMETRYSTREAM) { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong class identifier");
        return;
   }

   // Open and load the telemetry stream file and check correctness
   FILE *out=pNULL;
   if((out = fopen("TelemetryStream.txt","w")) == pNULL) {
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                              "File 'TelemetryStream.txt' could not be opened");
        return;
   }
   DC_FileTelemetryStream_setOutputStream(pTmStream, out);
   if (DC_FileTelemetryStream_getOutputStream(pTmStream) != out) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong telemetry stream file");
        return;
   }

   // Create and configure the telemetry packet to be written to the stream
   DC_DummyTelemetryPacket *pTI = DC_DummyTelemetryPacket_new();
   DC_DummyTelemetryPacket_setNumberOfBytes(pTI, 2);
   DC_DummyTelemetryPacket_setValue(pTI, 0, 1);
   DC_DummyTelemetryPacket_setValue(pTI, 1, 2);

   // Write telemetry packet to the telemetry stream
   tsc->write(pTmStream, (TelemetryPacket*)pTI);
   tsc->flush(pTmStream);
   DC_DummyTelemetryPacket_setValue(pTI, 0, 2);
   DC_DummyTelemetryPacket_setValue(pTI, 1, 3);
   tsc->write(pTmStream, (TelemetryPacket*)pTI);
   tsc->flush(pTmStream);

   // Close output file and set test result message
   fclose(out);
   TestCase_setTestResult((TestCase*)obj, TEST_SUCCESS, 
                           "Check 'TelemetryStream.txt' file");
   return;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj){}

TestCaseFileTelemetryStream_1* TestCaseFileTelemetryStream_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEFILETELEMETRYSTREAM_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                  ID_FILETELEMETRYSTREAM*10+1,
                                             "TestCaseFileTelemetryStream_1");

    return (TestCaseFileTelemetryStream_1*)obj;
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
    .name = TYPE_TESTCASEFILETELEMETRYSTREAM_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseFileTelemetryStream_1),
    .abstract = false,
    .class_size = sizeof(TestCaseFileTelemetryStream_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseFileTelemetryStream_1_register(void)
{
    type_register_static(&type_info);
}
