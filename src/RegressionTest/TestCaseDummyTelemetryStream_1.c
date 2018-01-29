//
//
// TestCaseDummyTelemetryStream_1.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/TestConstants.h"
#include "../GeneralInclude/Constants.h"
#include "../Telemetry/DC_DummyTelemetryPacket.h"
#include "../Telemetry/DC_DummyTelemetryStream.h"
#include "TestCaseDummyTelemetryStream_1.h"



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
    DC_DummyTelemetryStream *pTmStream = DC_DummyTelemetryStream_new();
    TelemetryStreamClass *tsc = TELEMETRYSTREAM_GET_CLASS(pTmStream);
    DC_DummyTelemetryPacket *pTmItem = DC_DummyTelemetryPacket_new();

    // Check the value of the class identifier
    if (CC_RootObject_getClassId((CC_RootObject*)pTmStream) != ID_DUMMYTELEMETRYSTREAM) 
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong class identifier");
        return;
    }

    // Check getCapacity()'s return value
    if (tsc->getCapacity(pTmStream) != MAX_INT) 
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "getCapacity() failed.");
        return;
    }

    // Check doesPacketFit()'s return value
    if (!tsc->doesPacketFit(pTmStream, (TelemetryPacket*)pTmItem)) 
    {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "doesPacketFit() failed.");
        return;
    }

    // The following three calls won't do anything at all. They are
    // here to exercise the code.
    tsc->reset(pTmStream);
    tsc->flush(pTmStream);
    tsc->write(pTmStream, (TelemetryPacket*)pTmItem);

    TestCase_setTestResult((TestCase*)obj, TEST_SUCCESS, "Test Successful");
    return;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj){}

TestCaseDummyTelemetryStream_1* TestCaseDummyTelemetryStream_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEDUMMYTELEMETRYSTREAM_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                 ID_DUMMYTELEMETRYSTREAM*10+1,
                                            "TestCaseDummyTelemetryStream_1"); 

    return (TestCaseDummyTelemetryStream_1*)obj;
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
    .name = TYPE_TESTCASEDUMMYTELEMETRYSTREAM_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseDummyTelemetryStream_1),
    .abstract = false,
    .class_size = sizeof(TestCaseDummyTelemetryStream_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseDummyTelemetryStream_1_register(void)
{
    type_register_static(&type_info);
}
