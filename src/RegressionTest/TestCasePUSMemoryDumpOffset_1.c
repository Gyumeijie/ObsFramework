//
//
// TestCasePUSMemoryDumpOffset_1.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "../Telemetry/DC_PUSMemoryDumpOffset.h"
#include "../Utilities/TestCaseWithEvtCheck.h"
#include "TestCasePUSMemoryDumpOffset_1.h"

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

   DC_PUSMemoryDumpOffset *pMD = DC_PUSMemoryDumpOffset_new();
   TelemetryPacketClass *tpc = TELEMETRYPACKET_GET_CLASS(pMD);
   CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pMD);

   // Set dummy values for the configuration parameters defined at
   // the level of telemetry packet and PUS telemmetry packet superclasses
   tpc->setTimeTag(pMD, 0);
   tpc->setDestination(pMD, 1);

   // Memory area from where telemetry data will be collected
   const unsigned int paSize =100;
   TD_PUSMemData pa[paSize];
   for (TD_PUSMemData i=0; i<paSize; i++) {
        pa[i] = i;
   }

   // Data area for the telemetry packet packet
   const unsigned short defPacketSize = 100;
   unsigned char packet[defPacketSize];

   // Check the correctness of the class identifier
   if ((CC_RootObject_getClassId((CC_RootObject*)pMD) != ID_PUSMEMORYDUMPOFFSET)) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong class identifier");
        return;
   }

   // Check the correctness of the type and subtype
   if ((tpc->getType(pMD) != 6) || (tpc->getSubType(pMD) != 4)) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong type or subtype");
        return;
   }

   // Check configuration status
   if (cc_roc->isObjectConfigured(pMD)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong configuration status at initialization");
    	return;
   }

   // Set maximum number of blocks
   TD_PUSNumberMemBlocks numberBlocks = 3;
   PUSMemoryDump_setMaxNumberBlocks((PUSMemoryDump*)pMD, numberBlocks);
   if (PUSMemoryDump_getMaxNumberBlocks((PUSMemoryDump*)pMD) != numberBlocks) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong configuration parameter");
    	return;
   }

   // Set maximum number of data
   TD_PUSMemLength maxNumberData = 50;
   PUSMemoryDump_setDumpBufferSize((PUSMemoryDump*)pMD, maxNumberData);
   if (PUSMemoryDump_getDumpBufferSize((PUSMemoryDump*)pMD) != maxNumberData) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong configuration parameter");
    	return;
   }

   // Check configuration status
   if (!cc_roc->isObjectConfigured(pMD)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
        "Wrong configuration status after initialization");
    	return;
   }

   // Check initial value of checksum flag
   if (PUSMemoryDump_isChecksumFlagSet()) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong value of checksum flag");
    	return;
   }

   // Set base address and check success
   DC_PUSMemoryDumpOffset_setBaseAddress(pMD, pa);
   if (DC_PUSMemoryDumpOffset_getBaseAddress(pMD) != pa) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong value of base address");
    	return;
   }

   // Set memory ID and check success
   TD_PUSMemId memId = 12;
   PUSMemoryDump_setMemoryId((PUSMemoryDump*)pMD, memId);
   if (PUSMemoryDump_getMemoryId((PUSMemoryDump*)pMD) != memId) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong value of memory id");
    	return;
   }

   // Check availability of fast acquisition service
   if (!tpc->isFastAcquisitionImplemented(pMD)) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Missing fast acquisition service");
    	return;
   }

   // Configure the packet to dump two blocks of three locations each
   TD_PUSMemOffset osa = 2;
   TD_PUSMemOffset osb = 5;
   TD_PUSMemLength lena = 2;
   TD_PUSMemLength lenb = 3;
   PUSMemoryDump_setNumberBlocks((PUSMemoryDump*)pMD, 2);
   PUSMemoryDump_defineBlock((PUSMemoryDump*)pMD, 0, pa+osa, lena);
   PUSMemoryDump_defineBlock((PUSMemoryDump*)pMD, 1, pa+osb, lenb);
   if ((PUSMemoryDump_getStartAddressOfMemBlock((PUSMemoryDump*)pMD, 0) != (pa+osa)) || 
       (PUSMemoryDump_getStartAddressOfMemBlock((PUSMemoryDump*)pMD, 1) != (pa+osb)))
   {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong block configuration values");
    	return;
   }
   if ((PUSMemoryDump_getLength((PUSMemoryDump*)pMD, 0) != lena) || 
       (PUSMemoryDump_getLength((PUSMemoryDump*)pMD, 1) != lenb))
   {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong block configuration values");
    	return;
   }

   // Do a data update
   tpc->update(pMD);

   // Compute expected size of the telemetry packet
   unsigned int fixedLength   = sizeof(TD_PUSMemId) + 
                                sizeof(TD_PUSMemData*) + 
                                sizeof(TD_PUSNumberMemBlocks);
   unsigned int blockLength_1 = sizeof(TD_PUSMemOffset) +
                                sizeof(TD_PUSMemLength) +
                                sizeof(unsigned short) + 
                                lena*sizeof(TD_PUSMemData);
   unsigned int blockLength_2 = sizeof(TD_PUSMemOffset) + 
                                sizeof(TD_PUSMemLength) +
                                sizeof(unsigned short) + 
                                lenb*sizeof(TD_PUSMemData);

   if (tpc->getNumberOfBytes(pMD) != (fixedLength + blockLength_1 + blockLength_2)) {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong packet size");
    	return;
   }

   // Do data acquisition and check success
   unsigned int nBytes = tpc->getNumberOfBytes(pMD);
   for (unsigned int i=0; i<nBytes; i++) {
       packet[i] = tpc->getUnsignedByte(pMD, i);
   }

   bool testFailed = false;
   unsigned int offset = 0;
   if (memcmp(packet+offset, &memId, sizeof(TD_PUSMemId)) != 0) {
       testFailed = true;
   }
   offset += sizeof(TD_PUSMemId);
   TD_PUSMemData* miTemp = pa;
   if (memcmp(packet+offset, &miTemp, sizeof(TD_PUSMemData*)) != 0) {
       testFailed = true;
   }
   offset += sizeof(TD_PUSMemData*);
   TD_PUSNumberMemBlocks nmbTemp = 2;
   if (memcmp(packet+offset, &nmbTemp, sizeof(TD_PUSNumberMemBlocks)) != 0) {
       testFailed = true;
   }
   offset += sizeof(TD_PUSNumberMemBlocks);

   // -- first block --
   if (memcmp(packet+offset, &osa, sizeof(TD_PUSMemOffset)) != 0) {
       testFailed = true;
   }
   offset += sizeof(TD_PUSMemOffset);
   if (memcmp(packet+offset, &lena, sizeof(TD_PUSMemLength)) != 0) {
       testFailed = true;
   }
   offset += sizeof(TD_PUSMemLength);
   for (TD_PUSMemOffset i=osa; i<osa+lena; i++) {
        TD_PUSMemData mpTemp = (TD_PUSMemData)(i);
        if (memcmp(packet+offset, &mpTemp, sizeof(TD_PUSMemData)) != 0){
            testFailed = true;
        }
        offset += sizeof(TD_PUSMemData);
   }
   unsigned short usTemp = 0;
   if (memcmp(packet+offset, &usTemp, 2) != 0) {
       testFailed = true;
   }
   offset += sizeof(unsigned short);

   // -- second block --
   if (memcmp(packet+offset, &osb, sizeof(TD_PUSMemOffset)) != 0) {
       testFailed = true;
   }
   offset += sizeof(TD_PUSMemOffset);
   if (memcmp(packet+offset, &lenb, sizeof(TD_PUSMemLength)) != 0) {
       testFailed = true;
   }
   offset += sizeof(TD_PUSMemLength);
   for (TD_PUSMemOffset i=osb; i<osb+lenb; i++) {
        TD_PUSMemData mpTemp = (TD_PUSMemData)(i);
        if (memcmp(packet+offset, &mpTemp, sizeof(TD_PUSMemData)) != 0) {
            testFailed = true;
        }
        offset += sizeof(TD_PUSMemData);
   }
   usTemp = 0;
   if (memcmp(packet+offset, &usTemp, 2) != 0) {
       testFailed = true;
   }
   offset += sizeof(unsigned short);
   // -- end second block --

   if (testFailed){	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong telemetry packet content");
    	return;
   }

   // Change setting of checksum flag and check success
   PUSMemoryDump_setChecksumFlag(true);
   if (!PUSMemoryDump_isChecksumFlagSet()) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong checksum value");
    	return;
   }

   // Configure the packet to dump one block of one location. The offset is chosen to be zero so as
   // to ensure that the dumped location has value zero and its expected checksum is then "FF FF".
   osa = 0;
   lena = 1;
   PUSMemoryDump_setNumberBlocks((PUSMemoryDump*)pMD, 1);
   PUSMemoryDump_defineBlock((PUSMemoryDump*)pMD, 0, pa+osa, lena);

   // Do a data update
   tpc->update(pMD);

   // Do data acquisition and check success
   nBytes = tpc->getNumberOfBytes(pMD);
   for (unsigned int i=0; i<nBytes; i++) {
       packet[i] = tpc->getUnsignedByte(pMD, i);
   }

   testFailed = false;
   offset = 0;
   if (memcmp(packet+offset, &memId, sizeof(TD_PUSMemId)) != 0) {
       testFailed = true;
   }
   offset += sizeof(TD_PUSMemId);
   miTemp = pa;
   if (memcmp(packet+offset, &miTemp, sizeof(TD_PUSMemData*)) != 0) {
       testFailed = true;
   }
   offset += sizeof(TD_PUSMemData*);
   nmbTemp = 1;
   if (memcmp(packet+offset, &nmbTemp, sizeof(TD_PUSNumberMemBlocks)) != 0) {
       testFailed = true;
   }
   offset += sizeof(TD_PUSNumberMemBlocks);

   // -- first block --
   if (memcmp(packet+offset,&osa,sizeof(TD_PUSMemOffset)) != 0) {
       testFailed = true;
   }
   offset += sizeof(TD_PUSMemOffset);
   if (memcmp(packet+offset, &lena, sizeof(TD_PUSMemLength)) != 0) {
       testFailed = true;
   }
   offset += sizeof(TD_PUSMemLength);
   for (TD_PUSMemOffset i=osa; i<osa+lena; i++) {
        TD_PUSMemData mpTemp = (TD_PUSMemData)(i);
        if (memcmp(packet+offset, &mpTemp, sizeof(TD_PUSMemData)) != 0) {
            testFailed = true;
        }
        offset += sizeof(TD_PUSMemData);
   }
   usTemp = 0xFFFF;
   if (memcmp(packet+offset, &usTemp, 2) != 0) {
       testFailed = true;
   }
   offset += sizeof(unsigned short);

   if (testFailed) {
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong telemetry packet content");
       return;
   }

   // Do non-nominal behaviour checks and check event generation
   if (TestCase_isNonNominalCheckAllowed(obj)) {
       unsigned int nEvt = TestCaseWithEvtCheck_getNumberOfEvents(obj);

       // Try defining a non-existent block
       PUSMemoryDump_defineBlock((PUSMemoryDump*)pMD, 3, pa+osa, lena);       
       if (!verifyLatestEvent(obj, nEvt+1, EVT_PUS_ILLEGAL_BLOCK_INDEX)) return;

       // Try loading too many blocks
       PUSMemoryDump_setNumberBlocks((PUSMemoryDump*)pMD, 5);
       if (!verifyLatestEvent(obj, nEvt+2, EVT_PUS_TOO_MANY_DUMP_BLOCKS)) return;

       // Try dumping more memory locations than fit in the dump buffer
       PUSMemoryDump_defineBlock((PUSMemoryDump*)pMD, 0, pa+osb, maxNumberData+1);    
       tpc->update(pMD);
       if (!verifyLatestEvent(obj, nEvt+3, EVT_PUS_TOO_MANY_MEM_DATA)) return;
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

TestCasePUSMemoryDumpOffset_1* TestCasePUSMemoryDumpOffset_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEPUSMEMORYDUMPOFFSET_1);

    TESTCASEWITHEVTCHECK_GET_CLASS(obj)->post_init((TestCaseWithEvtCheck*)obj,
                                                  ID_PUSMEMORYDUMPOFFSET*10+1,
                                             "TestCasePUSMemoryDumpOffset_1"); 
    return (TestCasePUSMemoryDumpOffset_1*)obj;
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
    .name = TYPE_TESTCASEPUSMEMORYDUMPOFFSET_1,
    .parent = TYPE_TESTCASEWITHEVTCHECK,
    .instance_size = sizeof(TestCasePUSMemoryDumpOffset_1),
    .abstract = false,
    .class_size = sizeof(TestCasePUSMemoryDumpOffset_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCasePUSMemoryDumpOffset_1_register(void)
{
    type_register_static(&type_info);
}
