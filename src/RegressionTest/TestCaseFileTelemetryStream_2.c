//
//
// TestCaseFileTelemetryStream_2.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/TestConstants.h"
#include "../Telemetry/DC_FileTelemetryStream.h"
#include "../Telemetry/DC_DummyTelemetryPacket.h"
#include "TestCaseFileTelemetryStream_2.h"
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

   DC_FileTelemetryStream* pTmStream = DC_FileTelemetryStream_new();
   TelemetryStreamClass *tsc = TELEMETRYSTREAM_GET_CLASS(pTmStream);

   // Load the telemetry stream and check correctness
   FILE* out = pNULL;
   DC_FileTelemetryStream_setOutputStream(pTmStream, out);
   if (DC_FileTelemetryStream_getOutputStream(pTmStream) != pNULL) {    
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
   if (out != pNULL) fclose(out);
   TestCase_setTestResult((TestCase*)obj, TEST_SUCCESS, "Check standard output");
   return;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj){}

TestCaseFileTelemetryStream_2* TestCaseFileTelemetryStream_2_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEFILETELEMETRYSTREAM_2);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                  ID_FILETELEMETRYSTREAM*10+2,
                                             "TestCaseFileTelemetryStream_2"); 

    return (TestCaseFileTelemetryStream_2*)obj;
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
    .name = TYPE_TESTCASEFILETELEMETRYSTREAM_2,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseFileTelemetryStream_2),
    .abstract = false,
    .class_size = sizeof(TestCaseFileTelemetryStream_2Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseFileTelemetryStream_2_register(void)
{
    type_register_static(&type_info);
}
