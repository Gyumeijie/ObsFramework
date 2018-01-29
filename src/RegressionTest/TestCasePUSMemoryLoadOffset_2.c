//
//
// TestCasePUSMemoryLoadOffset_2.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "../Telecommand/DC_PUSMemoryLoadOffset.h"
#include "../Utilities/TestCaseWithEvtCheck.h"
#include "TestCasePUSMemoryLoadOffset_2.h"

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
        pa[i] = 0;
   }

   // Data area for the telecommand packet
   const unsigned short defPacketSize = 100;
   unsigned char packet[defPacketSize];

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

   // Define the load packet (one block with four data) with the valid checksum
   // The data and their checksum are taken from one of the examples
   // in the appendix 3 of the PUS
   TD_PUSMemOffset os1 = 2;
   TD_PUSMemLength len1 = 4;
   TD_PUSMemData d1 = 0xAB;
   TD_PUSMemData d2 = 0xCD;
   TD_PUSMemData d3 = 0xEF;
   TD_PUSMemData d4 = 0x01;
   TD_PUSNumberMemBlocks nmb = 1;
   unsigned short checkSum = 0x9CF8;

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
   memcpy(packet+offset, &d4, sizeof(TD_PUSMemData));
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
   if ((pa[os1] != d1) || (pa[os1+1] != d2) || (pa[os1+2] != d3) || (pa[os1+3] != d4))
   {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong loaded data");
    	return;
   }

   // Clear patch memory area
   for (unsigned int i=0; i<paSize; i++) {
        pa[i] = 0;
   }

   // Define the load packet (one block with four data) with the invalid checksum
   // The data and their checksum are taken from one of the examples
   // in the appendix 3 of the PUS
   offset = sizeof(TD_PUSMemId) + sizeof(unsigned char*);
   os1 = 2;
   len1 = 4;
   d1 = 0xAB;
   d2 = 0xCD;
   d3 = 0xEF;
   d4 = 0x01;
   nmb = 1;
   checkSum = 0x9CF9;

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
   memcpy(packet+offset, &d4, sizeof(TD_PUSMemData));
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

   // Execute TC and check correctness of outcome
   if (PunctualAction_execute((PunctualAction*)pML) != MEM_LOAD_PRE_CHECKSUM_FAILED)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong execution outcome");
    	return;
   }

   // Check that no data were written to patch area
   for (unsigned int i=0; i<paSize; i++) {
        if (pa[i] != 0)
        {	
            TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                    "Wrong loaded data");
        	return;
        }
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

TestCasePUSMemoryLoadOffset_2* TestCasePUSMemoryLoadOffset_2_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEPUSMEMORYLOADOFFSET_2);

    TESTCASEWITHEVTCHECK_GET_CLASS(obj)->post_init((TestCaseWithEvtCheck*)obj,
                                                  ID_PUSMEMORYLOADOFFSET*10+2,
                                             "TestCasePUSMemoryLoadOffset_2"); 
    return (TestCasePUSMemoryLoadOffset_2*)obj;
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
    .name = TYPE_TESTCASEPUSMEMORYLOADOFFSET_2,
    .parent = TYPE_TESTCASEWITHEVTCHECK,
    .instance_size = sizeof(TestCasePUSMemoryLoadOffset_2),
    .abstract = false,
    .class_size = sizeof(TestCasePUSMemoryLoadOffset_2Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCasePUSMemoryLoadOffset_2_register(void)
{
    type_register_static(&type_info);
}
