//
//
// TestCaseDataItem16TmWord_1.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/TestConstants.h"
#include "../Telemetry/DC_DataItem16TmWord.h"
#include "../Base/CC_RootObject.h"
#include "../Event/DC_EventRepository.h"
#include "../Data/DC_RawDataItem.h"
#include "../Data/DC_DataItem.h"
#include "TestCaseDataItem16TmWord_1.h"

#include <string.h>



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
   unsigned short usTemp;
   unsigned char ucTemp;
   unsigned char *pTemp;

   // Create a data item component
   unsigned short var = 0xaabb;
   DC_RawDataItem *pd1 = DC_RawDataItem_new(&var);

   // Create the DataItem16TmWord_1 component
   DC_DataItem16TmWord *pTmWord = DC_DataItem16TmWord_new();
   CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pTmWord);
   TelemetryPacketClass *tpc = TELEMETRYPACKET_GET_CLASS(pTmWord);

   // Check the value of the class identifier
   if (CC_RootObject_getClassId((CC_RootObject*)pTmWord) != ID_DATAITEM16TMWORD) {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong class identifier");
        return;
   }

   // Check that the DataItem16TmWord_1 is not configured
   if (cc_roc->isObjectConfigured(pTmWord)) { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong object configuration status");
        return;
   }

   // Load the data item into the DataItem16TmWord_1 object and check that the
   // DataItem16TmWord_1 object becomes configured
   DC_DataItem16TmWord_setDataItem(pTmWord, pd1);
   if (!cc_roc->isObjectConfigured(pTmWord)) { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong object configuration status");
        return;
   }

   // Check the correct validity status
   if (!tpc->isValid(pTmWord)) { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong validity status");
        return;
   }

   // Check the correct number of bytes
   if (tpc->getNumberOfBytes(pTmWord) != 2) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong number of bytes");
        return;
   }

   // Send an update request to DataItem16TmWord_1 and check the
   // data acquired from it are correct
   tpc->update(pTmWord);
   if (StructuredTelemetryPacket_getUnsignedShort((void*)pTmWord, 0) != 0xaabb) {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong data acquisition result");
        return;
   }

   usTemp = DC_RawDataItem_getUnsignedShort(pd1);
   pTemp = (unsigned char*)&usTemp;
   memcpy(&ucTemp, pTemp, 1);
   if (tpc->getUnsignedByte(pTmWord, 0) != ucTemp) { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong data acquisition result");
        return;
   }
   memcpy(&ucTemp, pTemp+1, 1);
   if (tpc->getUnsignedByte(pTmWord, 1) != ucTemp) { 
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong data acquisition result");
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

TestCaseDataItem16TmWord_1* TestCaseDataItem16TmWord_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEDATAITEM16TMWORD_1);

    TESTCASEGENERICSETUP_GET_CLASS(obj)->post_init((TestCaseGenericSetUp*)obj,
                                                     ID_DATAITEM16TMWORD*10+1,
                                                 "TestCaseDataItem16TmWord_1"); 
    return (TestCaseDataItem16TmWord_1*)obj;
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
    .name = TYPE_TESTCASEDATAITEM16TMWORD_1,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseDataItem16TmWord_1),
    .abstract = false,
    .class_size = sizeof(TestCaseDataItem16TmWord_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseDataItem16TmWord_1_register(void)
{
    type_register_static(&type_info);
}
