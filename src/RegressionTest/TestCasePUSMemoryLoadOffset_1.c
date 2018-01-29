//
//
// TestCasePUSMemoryLoadOffset_1.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "../Telecommand/DC_PUSMemoryLoadOffset.h"
#include "../Utilities/TestCaseWithEvtCheck.h"
#include "TestCasePUSMemoryLoadOffset_1.h"

#include <assert.h>
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
   DC_PUSMemoryLoadOffset *pML = DC_PUSMemoryLoadOffset_new();
   TelecommandClass *tc = TELECOMMAND_GET_CLASS(pML);
   CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pML);

   // Set dummy values for the configuration parameters defined at
   // the level of Telecommand and PUSTelecommand superclasses
   Telecommand_setTimeTag((Telecommand*)pML, 0);
   tc->setSource(pML, 1);
   tc->setTelecommandId(pML, 2);

   // Memory area where telecommand data will be loaded
   const unsigned int paSize = 100;
   TD_PUSMemData pa[paSize];
   for (unsigned int i=0; i<paSize; i++) {
        pa[i]=0;
   }

   // Data area for the telecommand packet
   const unsigned short defPacketSize = 100;
   unsigned char packet[defPacketSize];

   // Check the correctness of the class identifier
   if (CC_RootObject_getClassId((CC_RootObject*)pML) != ID_PUSMEMORYLOADOFFSET)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong class identifier");
        return;
   }

   // Check configuration status
   if (cc_roc->isObjectConfigured(pML))
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong configuration status at initialization");
    	return;
   }

   // Set maximum number of blocks
   PUSMemoryLoad_setMaxNumberBlocks((PUSMemoryLoad*)pML, 3);
   if (PUSMemoryLoad_getMaxNumberBlocks((PUSMemoryLoad*)pML) != 3)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong configuration parameter");
    	return;
   }

   // Set maximum number of data
   PUSMemoryLoad_setMaxNumberData((PUSMemoryLoad*)pML, 10);
   if (PUSMemoryLoad_getMaxNumberData((PUSMemoryLoad*)pML) != 10)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong configuration parameter");
    	return;
   }

   // Check configuration status
   if (!cc_roc->isObjectConfigured(pML))
   {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong configuration status after initialization");
    	return;
   }

   // Define fixed part of the memory load PUS packet 
   unsigned int offset = 0;
   TD_PUSMemId id = 12;
   TD_PUSMemData *base = pa;
   memcpy(packet+offset, &id, sizeof(TD_PUSMemId));
   offset += sizeof(TD_PUSMemId);
   memcpy(packet+offset, &base, sizeof(TD_PUSMemData*));
   offset += sizeof(TD_PUSMemData*);

   // Define the first load packet (one block with two data)
   TD_PUSMemOffset os1 = 2;
   TD_PUSMemLength len1 = 2;
   TD_PUSMemData d1 = 1;
   TD_PUSMemData d2 = 2;
   TD_PUSNumberMemBlocks nmb = 1;
   unsigned short checkSum = 0;

   memcpy(packet+offset, &nmb, sizeof(TD_PUSNumberMemBlocks));
   offset += sizeof(TD_PUSNumberMemBlocks);
   memcpy(packet+offset, &os1, sizeof(TD_PUSMemLength));
   offset += sizeof(TD_PUSMemLength);
   memcpy(packet+offset, &len1, sizeof(TD_PUSMemLength));
   offset += sizeof(TD_PUSMemLength);
   memcpy(packet+offset, &d1, sizeof(TD_PUSMemData));
   offset += sizeof(TD_PUSMemData);
   memcpy(packet+offset, &d2, sizeof(TD_PUSMemData));
   offset += sizeof(TD_PUSMemData);
   memcpy(packet+offset, &checkSum, 2);
   offset += sizeof(unsigned short);

   // Load packet and check validity
   if (tc->getValidityCheckCode(pML) != 0)
   {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong validity code");
    	return;
   }
   tc->setRawDataFastly(pML, packet, offset);
   if (tc->getValidityCheckCode(pML) != 0)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong validity code");
    	return;
   }

   // Execute TC and check correctness
   if (PunctualAction_execute((PunctualAction*)pML) != ACTION_SUCCESS)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong execution outcome");
    	return;
   }
   if ((pa[os1] != d1) || (pa[os1+1] != d2))
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong loaded data");
    	return;
   }

   // Define the second load packet (three blocks with three data each)
   offset = sizeof(TD_PUSMemId) + sizeof(unsigned char*);
   os1 = 2;
   TD_PUSMemOffset os2 = 20;
   TD_PUSMemOffset os3 = 30;
   TD_PUSMemLength len = 3;
   d1 = 3;
   d2 = 4;
   TD_PUSMemData d3 = 5;
   nmb = 3;
   checkSum = 0;

   memcpy(packet+offset, &nmb, sizeof(TD_PUSNumberMemBlocks));
   offset += sizeof(TD_PUSNumberMemBlocks);
   memcpy(packet+offset, &os1, sizeof(TD_PUSMemLength));
   offset += sizeof(TD_PUSMemLength);
   memcpy(packet+offset, &len, sizeof(TD_PUSMemLength));
   offset += sizeof(TD_PUSMemLength);
   memcpy(packet+offset, &d1, sizeof(TD_PUSMemData));
   offset += sizeof(TD_PUSMemData);
   memcpy(packet+offset, &d2, sizeof(TD_PUSMemData));
   offset += sizeof(TD_PUSMemData);
   memcpy(packet+offset, &d3, sizeof(TD_PUSMemData));
   offset += sizeof(TD_PUSMemData);
   memcpy(packet+offset, &checkSum, 2);
   offset += sizeof(unsigned short);

   d1 = d1*2;
   d2 = d2*2;
   d3 = d3*2;
   memcpy(packet+offset, &os2, sizeof(TD_PUSMemLength));
   offset += sizeof(TD_PUSMemLength);
   memcpy(packet+offset, &len, sizeof(TD_PUSMemLength));
   offset += sizeof(TD_PUSMemLength);
   memcpy(packet+offset, &d1, sizeof(TD_PUSMemData));
   offset += sizeof(TD_PUSMemData);
   memcpy(packet+offset, &d2, sizeof(TD_PUSMemData));
   offset += sizeof(TD_PUSMemData);
   memcpy(packet+offset, &d3, sizeof(TD_PUSMemData));
   offset += sizeof(TD_PUSMemData);
   memcpy(packet+offset, &checkSum, 2);
   offset += sizeof(unsigned short);

   d1 = d1*3;
   d2 = d2*3;
   d3 = d3*3;
   memcpy(packet+offset, &os3, sizeof(TD_PUSMemLength));
   offset += sizeof(TD_PUSMemLength);
   memcpy(packet+offset, &len, sizeof(TD_PUSMemLength));
   offset += sizeof(TD_PUSMemLength);
   memcpy(packet+offset, &d1, sizeof(TD_PUSMemData));
   offset += sizeof(TD_PUSMemData);
   memcpy(packet+offset, &d2, sizeof(TD_PUSMemData));
   offset += sizeof(TD_PUSMemData);
   memcpy(packet+offset, &d3, sizeof(TD_PUSMemData));
   offset += sizeof(TD_PUSMemData);
   memcpy(packet+offset, &checkSum, 2);
   offset += sizeof(unsigned short);


   // Load packet and check validity
   if (tc->getValidityCheckCode(pML) != 0)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong validity code");
    	return;
   }
   tc->setRawDataFastly(pML, packet, offset);
   if (tc->getValidityCheckCode(pML) != 0)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong validity code");
    	return;
   }

   // Execute TC and check correctness
   if (PunctualAction_execute((PunctualAction*)pML) != ACTION_SUCCESS)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong execution outcome");
    	return;
   }
   if ((pa[os1] != d1/6) || (pa[os1+1] != d2/6) || (pa[os1+2] != d3/6))
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong loaded data");
    	return;
   }
   if ((pa[os2] != d1/3) || (pa[os2+1] != d2/3) || (pa[os2+2] != d3/3))
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong loaded data");
    	return;
   }
   if ((pa[os3] != d1) || (pa[os3+1] != d2) || (pa[os3+2] != d3))
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong loaded data");
    	return;
   }

   // Define the third load packet (four blocks)
   offset = sizeof(TD_PUSMemId) + sizeof(unsigned char*);
   nmb = 4;
   memcpy(packet+offset, &nmb, sizeof(TD_PUSNumberMemBlocks));
   offset += sizeof(TD_PUSNumberMemBlocks);
   offset += 10;   // dummy: just to simulate presence of memory load data 
       
   // Load packet and check validity
   tc->setRawDataFastly(pML, packet, offset);
   if (tc->getValidityCheckCode(pML) != VC_TOO_MANY_MEM_BLOCK)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong validity code");
    	return;
   }

   // Define the fourth load packet (one block with 2 data, one block with nine data)
   offset = sizeof(TD_PUSMemId) + sizeof(unsigned char*);
   os1 = 2;
   os2 = 10;
   len1 = 2;
   TD_PUSMemLength len2 = 9;
   nmb = 2;
   checkSum = 0;

   d1 = 0;
   d2 = 0;
   memcpy(packet+offset, &nmb, sizeof(TD_PUSNumberMemBlocks));
   offset += sizeof(TD_PUSNumberMemBlocks);
   memcpy(packet+offset, &os1, sizeof(TD_PUSMemLength));
   offset += sizeof(TD_PUSMemLength);
   memcpy(packet+offset, &len1, sizeof(TD_PUSMemLength));
   offset += sizeof(TD_PUSMemLength);
   memcpy(packet+offset, &d1, sizeof(TD_PUSMemData));
   offset += sizeof(TD_PUSMemData);
   memcpy(packet+offset, &d2, sizeof(TD_PUSMemData));
   offset += sizeof(TD_PUSMemData);
   memcpy(packet+offset, &d3, sizeof(TD_PUSMemData));
   offset += sizeof(TD_PUSMemData);
   memcpy(packet+offset, &checkSum, 2);
   offset += sizeof(unsigned short);
   memcpy(packet+offset, &os2, sizeof(TD_PUSMemLength));
   offset += sizeof(TD_PUSMemLength);
   memcpy(packet+offset, &len2, sizeof(TD_PUSMemLength));
   offset += sizeof(TD_PUSMemLength);

   // Load packet and check validity
   tc->setRawDataFastly(pML, packet, offset);
   if (tc->getValidityCheckCode(pML) != VC_TOO_MANY_MEM_DATA)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong validity code");
    	return;
   }

   // Load packet with invalid number of bytes and check validity
   tc->setRawDataFastly(pML, packet, 1);
   if (tc->getValidityCheckCode(pML) != VC_INCONSISTENT_RAW_DATA)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong validity code");
    	return;
   }

   // Define the first load packet again (one block with two data)
   offset = sizeof(TD_PUSMemId) + sizeof(unsigned char*);
   os1 = 2;
   len1 = 2;
   d1 = 1;
   d2 = 2;
   nmb = 1;
   checkSum = 0;

   memcpy(packet+offset, &nmb, sizeof(TD_PUSNumberMemBlocks));
   offset += sizeof(TD_PUSNumberMemBlocks);
   memcpy(packet+offset, &os1, sizeof(TD_PUSMemLength));
   offset += sizeof(TD_PUSMemLength);
   memcpy(packet+offset, &len1, sizeof(TD_PUSMemLength));
   offset += sizeof(TD_PUSMemLength);
   memcpy(packet+offset, &d1, sizeof(TD_PUSMemData));
   offset += sizeof(TD_PUSMemData);
   memcpy(packet+offset, &d2, sizeof(TD_PUSMemData));
   offset += sizeof(TD_PUSMemData);
   memcpy(packet+offset, &checkSum, 2);
   offset += sizeof(unsigned short);

   // Load packet with wrong number of bytes and check validity
   tc->setRawDataFastly(pML, packet, offset+1);
   if (tc->getValidityCheckCode(pML) != VC_INCONSISTENT_RAW_DATA)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong validity code");
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

TestCasePUSMemoryLoadOffset_1* TestCasePUSMemoryLoadOffset_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEPUSMEMORYLOADOFFSET_1);

    TESTCASEWITHEVTCHECK_GET_CLASS(obj)->post_init((TestCaseWithEvtCheck*)obj,
                                                  ID_PUSMEMORYLOADOFFSET*10+1,
                                              "TestCasePUSMemoryLoadOffset_1"); 

    return (TestCasePUSMemoryLoadOffset_1*)obj;
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
    .name = TYPE_TESTCASEPUSMEMORYLOADOFFSET_1,
    .parent = TYPE_TESTCASEWITHEVTCHECK,
    .instance_size = sizeof(TestCasePUSMemoryLoadOffset_1),
    .abstract = false,
    .class_size = sizeof(TestCasePUSMemoryLoadOffset_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCasePUSMemoryLoadOffset_1_register(void)
{
    type_register_static(&type_info);
}
