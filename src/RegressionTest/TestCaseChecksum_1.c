//
//
// TestCaseChecksum_1.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../Utilities/Checksum.h"
#include "TestCaseChecksum_1.h"



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

   unsigned char data[10];
   unsigned short result;

   // Check the first stream of data
   data[0] = 0;
   data[1] = 0;

   result = doChecksum(data, 2);
   if (result != 0xFFFF) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Incorrect checksum result");
		return;
   }
   if (!verifyChecksum(data, 2, result)) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Incorrect checksum verification");
		return;
   }

   // Check the second stream of data
   data[0] = 0;
   data[1] = 0;
   data[2] = 0;

   result = doChecksum(data, 3);
   if (result != 0xFFFF) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Incorrect checksum result");
		return;
   }
   if (!verifyChecksum(data, 3, result)) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Incorrect checksum verification");
		return;
   }

   // Check the third stream of data
   data[0] = 0xAB;
   data[1] = 0xCD;
   data[2] = 0xEF;
   data[3] = 0x01;

   result = doChecksum(data, 4);
   if (result != 0x9CF8) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Incorrect checksum result");
		return;
   }
   if (!verifyChecksum(data, 4, result)) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Incorrect checksum verification");
		return;
   }  

   verifyChecksum(data, 4, result) ;

   // Check the fourth stream of data
   data[0] = 0x14;
   data[1] = 0x56;
   data[2] = 0xF8;
   data[3] = 0x9A;
   data[4] = 0x00;
   data[5] = 0x01;

   result = doChecksum(data, 6);
   if (result != 0x24DC) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Incorrect checksum result");
		return;
   }
   if (!verifyChecksum(data, 6, result)) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Incorrect checksum verification");
		return;
   }

   TestCase_setTestResult((TestCase*)obj, TEST_SUCCESS, 
                            "Test Successful");
   return;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj){}

TestCaseChecksum_1* TestCaseChecksum_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASECHECKSUM_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                    ID_CHECKSUM*10+1,
                                                    "TestCaseChecksum_1"); 
    return (TestCaseChecksum_1*)obj;
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
    .name = TYPE_TESTCASECHECKSUM_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseChecksum_1),
    .abstract = false,
    .class_size = sizeof(TestCaseChecksum_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseChecksum_1_register(void)
{
    type_register_static(&type_info);
}
