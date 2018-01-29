//
//
// TestCaseDummyTracer_1.c
//

#include "TestCaseDummyTracer_1.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../System/Tracer.h"
#include "../System/DC_DummyTracer.h"



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

   DC_DummyTracer* dc_dt = DC_DummyTracer_new();

   // Dummy tracer should be disabled upon creation
   if ((Tracer_isEnabled((Tracer*)dc_dt) != DISABLED) ) {
        TestCase_setTestResult((TestCase*)obj,
                               TEST_FAILURE, 
                               "Dummy Tracer component should be disabled");
		return;
	}

   // Send a synch trace signal. This operation should have no effect. No
   // correctness check can be performed. The test can fail only through
   // a run time-error.
   TD_TraceItem item = 0x0001;
   Tracer_sendSynchTrace((Tracer*)dc_dt, item);

   // Send a packet trace signal. This operation should have no effect. No
   // correctness check can be performed. The test can fail only through
   // a run time-error.
   TD_TraceItem itemPacket[2];
   itemPacket[0] = 0x0002;
   itemPacket[0] = 0x0003;
   Tracer_sendPacketTrace((Tracer*)dc_dt, 2, itemPacket);

   TestCase_setTestResult((TestCase*)obj, TEST_SUCCESS, "Test Successful");
   return;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj) {}

TestCaseDummyTracer_1* TestCaseDummyTracer_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEDUMMYTRACER_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                    ID_DUMMYTRACER*10+1,
                                                    "TestCaseDummyTracer_1");
    return (TestCaseDummyTracer_1*)obj;
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
    .name = TYPE_TESTCASEDUMMYTRACER_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseDummyTracer_1),
    .abstract = false,
    .class_size = sizeof(TestCaseDummyTracer_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseDummyTracer_1_register(void)
{
    type_register_static(&type_info);
}
