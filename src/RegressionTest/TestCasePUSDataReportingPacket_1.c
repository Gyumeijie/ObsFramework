//
//
// TestCasePUSDataReportingPacket_1.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "../Telemetry/DC_PUSDataReportingPacket.h"
#include "../Data/DC_SampleFullDataPool.h"
#include "../Utilities/TestCaseWithEvtCheck.h"
#include "TestCasePUSDataReportingPacket_1.h"

#include <math.h>
#include <float.h>
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
   unsigned int nEvt = TestCaseWithEvtCheck_getNumberOfEvents(obj);
   unsigned int nBytes = 0; 

   DC_PUSDataReportingPacket *pTMP = DC_PUSDataReportingPacket_new();
   TelemetryPacketClass *tpc = TELEMETRYPACKET_GET_CLASS(pTMP);
   CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pTMP);

   DC_SampleFullDataPool *pDP = DC_SampleFullDataPool_new();
   DataPoolClass *dpc = DATAPOOL_GET_CLASS(pDP);

   // Configure and load the data pool
   DC_SampleFullDataPool_setObsClock(pDP, PUSTelemetryPacket_getObsClock());
   DataPool *pOldDP = CC_RootObject_getDataPool();
   CC_RootObject_setDataPool((DataPool*)pDP);

   // Define the PUS packet
   TD_SID sid = 12;
   TD_PUSCollectionInterval collectionInterval = 3;
   TD_PUSNumberOfParameters NPAR1 = 2;
   TD_DataPoolId par1 = 1;
   TD_Integer val1 = 11;
   TD_DataPoolId par2 = 2;
   TD_Float val2 = 12.0;

   // Construct the packet
   TD_PUSNumberOfParameters const defPacketSize = 30;
   unsigned char packet[defPacketSize];
   TD_PUSNumberOfParameters offset = 0;
   memcpy(packet+offset, &sid, sizeof(TD_SID));
   offset += sizeof(TD_SID);
   memcpy(packet+offset, &collectionInterval, sizeof(TD_PUSCollectionInterval));
   offset += sizeof(TD_PUSCollectionInterval);
   memcpy(packet+offset, &NPAR1, sizeof(TD_PUSNumberOfParameters));
   offset += sizeof(TD_PUSNumberOfParameters);
   memcpy(packet+offset, &par1, sizeof(TD_DataPoolId));
   offset += sizeof(TD_DataPoolId);
   memcpy(packet+offset, &par2, sizeof(TD_DataPoolId));
   offset += sizeof(TD_DataPoolId);

   assert(offset < defPacketSize);

   // Check the correctness of the class identifier
   if ((CC_RootObject_getClassId((CC_RootObject*)pTMP) != ID_PUSDATAREPORTINGPACKET))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong class identifier for the FSM class");
        return;
   }

   // Check configuration status
   if (cc_roc->isObjectConfigured(pTMP))
   {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong configuration status at initialization");
    	return;
   }

   // Set maximum number of FA arrays and check correctness
   DC_PUSDataReportingPacket_setMaxNumberFA(pTMP, 2);
   if (DC_PUSDataReportingPacket_getMaxNumberFA(pTMP) != 2)
   {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong number of FA arrays");
    	return;
   }

   // Set maximum size of the packet definition buffer and check correctness
   DC_PUSDataReportingPacket_setDefinitionBufferSize(pTMP, defPacketSize);
   if (DC_PUSDataReportingPacket_getDefinitionBufferSize(pTMP) != defPacketSize)
   {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong definition buffer size");
    	return;
   }

   // Set maximum size of the packet value buffer and check correctness
   unsigned int valBufferSize = 30;
   DC_PUSDataReportingPacket_setValueBufferSize(pTMP, valBufferSize);
   if (DC_PUSDataReportingPacket_getValueBufferSize(pTMP) != valBufferSize)
   {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong value buffer size");
    	return;
   }

   // Load the packet subtype and time tag check configuration status
   tpc->setTimeTag(pTMP, 0);
   tpc->setSubType(pTMP, PUS_ST_DATA_REP_PAR_HK_REP);
   if (!cc_roc->isObjectConfigured(pTMP))
   {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong configuration status");
    	return;
   }

   // Check that packet is disabled
   if ((DC_PUSDataReportingPacket_isEnabled(pTMP) == ENABLED))
   {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong enable status");
    	return;
   }

   // Load the packet definition
   for (unsigned short i=0; i<offset; i++) {
        DC_PUSDataReportingPacket_setDefinitionBuffer(pTMP, i, packet[i]);
   }

   if (DC_PUSDataReportingPacket_getDefinitionBufferLength(pTMP) != offset)
   {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong definition buffer length");
    	return;
   }

   // Send three update requests and check that there are no data to be acquired
   tpc->update(pTMP);
   if (tpc->getNumberOfBytes(pTMP) != 0)
   {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong number of bytes");
    	return;
   }
   tpc->update(pTMP);
   if (tpc->getNumberOfBytes(pTMP) != 0)
   {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong number of bytes");
    	return;
   }
   tpc->update(pTMP);
   if (tpc->getNumberOfBytes(pTMP) != 0)
   {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong number of bytes");
    	return;
   }

   // Enable the component and check correctness
   DC_PUSDataReportingPacket_setEnabled(pTMP, ENABLED);
   if ((DC_PUSDataReportingPacket_isEnabled(pTMP) == DISABLED))
   {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong enable status");
    	return;
   }

   // Send two update requests and check that there are no data to be acquired
   tpc->update(pTMP);
   if (tpc->getNumberOfBytes(pTMP) != 0)
   {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong number of bytes");
    	return;
   }
   tpc->update(pTMP);
   if (tpc->getNumberOfBytes(pTMP) != 0)
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong number of bytes");
    	return;
   }

   // Update the values of the data pool items
   dpc->setIntegerValue(pDP, par1, val1);
   dpc->setFloatValue(pDP, par2, val2);

   // Send an update request and check data acquisition service
   tpc->update(pTMP);
   unsigned int n1, n2, n3;
   n1 = sizeof(TD_SID);
   n2 = (PUS_DATA_REP_MODE ? 1 : 0);
   n3 = sizeof(TD_Float) + sizeof(TD_Integer);
   unsigned int expNumberOfBytes = n1 + n2 + n3;
   if (tpc->getNumberOfBytes(pTMP) != expNumberOfBytes)
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong number of bytes");
    	return;
   }

   // Collect the packet data and check their values
   unsigned char *valBuffer = g_malloc(sizeof(unsigned char)*valBufferSize);
   nBytes = tpc->getNumberOfBytes(pTMP);
   for (unsigned int i=0; i<nBytes; i++) {
       valBuffer[i] = tpc->getUnsignedByte(pTMP, i);
   }

   unsigned int valOffset = 0;
   TD_SID sidTemp = 0;
   TD_Integer intTemp = 0;
   TD_Float flTemp = 0;

   memcpy(&sidTemp, valBuffer+valOffset, sizeof(TD_SID));
   if (sidTemp != sid)
   {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong sid field");
    	return;
   }
   valOffset += sizeof(TD_SID);

   if ((PUS_DATA_REP_MODE ? (valBuffer[valOffset] != 0) : false))
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong mode field");
    	return;
   }
   valOffset += (PUS_DATA_REP_MODE ? 1 : 0);

   memcpy(&intTemp, valBuffer+valOffset, sizeof(TD_Integer));
   if (intTemp != (TD_Integer)val1)
   {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong parameter 1 field");
    	return;
   }
   valOffset += sizeof(TD_Integer);

   memcpy(&flTemp, valBuffer+valOffset, sizeof(TD_Float));
   if (fabs((float)(flTemp - (TD_Float)val2)) > FLT_EPSILON)
   {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Wrong parameter 2 field");
    	return;
   }
   valOffset += sizeof(TD_Float);

   assert(valOffset < valBufferSize);

   // Check that the fast version of the data acquisition service is implemented
   if (!tpc->isFastAcquisitionImplemented(pTMP))
   {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
        "Fast data acquisition service should be implemented");
    	return;
   }

   // Collect the packet data using the fast version of the data acquisition 
   // service and check their values
   unsigned char *temp = tpc->getStartAddress(pTMP);
   nBytes = tpc->getNumberOfBytes(pTMP);
   for (unsigned int i=0; i<nBytes; i++) {
       valBuffer[i] = temp[i];
   }

   valOffset = 0;
   memcpy(&sidTemp, valBuffer+valOffset, sizeof(TD_SID));
   if (sidTemp != sid)
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong sid field");
    	return;
   }
   valOffset += sizeof(TD_SID);

   if ((PUS_DATA_REP_MODE ? (valBuffer[valOffset] != 0) : false))
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong mode field");
    	return;
   }
   valOffset += (PUS_DATA_REP_MODE ? 1 : 0);

   memcpy(&intTemp, valBuffer+valOffset, sizeof(TD_Integer));
   if (intTemp != (TD_Integer)val1)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong parameter 1 field");
    	return;
   }
   valOffset += sizeof(TD_Integer);
   memcpy(&flTemp, valBuffer+valOffset, sizeof(TD_Float));
   if (fabs((float)(flTemp - (TD_Float)val2)) > FLT_EPSILON)
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong parameter 2 field");
    	return;
   }
   valOffset += sizeof(TD_Float);

   assert(valOffset < valBufferSize);

   // Update the values in the data pool
   dpc->setIntegerValue(pDP, par1, (TD_Integer)(2*val1));
   dpc->setFloatValue(pDP, par2, (TD_Float)(2*val2));

   // Send three update requests and check data acquisition service
   tpc->update(pTMP);
   tpc->update(pTMP);
   tpc->update(pTMP);
   nBytes = tpc->getNumberOfBytes(pTMP);
   for (unsigned int i=0; i<nBytes; i++) { 
       valBuffer[i] = tpc->getUnsignedByte(pTMP, i);
   }

   valOffset = 0;
   memcpy(&sidTemp, valBuffer+valOffset, sizeof(TD_SID));
   if (sidTemp != sid)
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong sid field");
    	return;
   }
   valOffset += sizeof(TD_SID);

   if ((PUS_DATA_REP_MODE ? (valBuffer[valOffset] != 0) : false))
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong mode field");
    	return;
   }
   valOffset += (PUS_DATA_REP_MODE?1:0);

   memcpy(&intTemp, valBuffer+valOffset, sizeof(TD_Integer));
   if (intTemp != (TD_Integer)2*val1)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong parameter 1 field");
    	return;
   }
   valOffset += sizeof(TD_Integer);

   memcpy(&flTemp, valBuffer+valOffset, sizeof(TD_Float));
   if (fabs((float)(flTemp - (TD_Float)2*val2)) > FLT_EPSILON)
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong parameter 2 field");
    	return;
   }
   valOffset += sizeof(TD_Float);

   assert(valOffset < valBufferSize);

   // Update the values in the data pool
   dpc->setIntegerValue(pDP, par1, (TD_Integer)(3*val1));
   dpc->setFloatValue(pDP, par2, (TD_Float)(3*val2));

   // Define a new PUS packet
   sid = 13;
   collectionInterval = 2;
   NPAR1 = 1;

   // Construct the packet
   offset = 0;
   memcpy(packet+offset, &sid, sizeof(TD_SID));
   offset += sizeof(TD_SID);
   memcpy(packet+offset, &collectionInterval, sizeof(TD_PUSCollectionInterval));
   offset += sizeof(TD_PUSCollectionInterval);
   memcpy(packet+offset, &NPAR1, sizeof(TD_PUSNumberOfParameters));
   offset += sizeof(TD_PUSNumberOfParameters);
   memcpy(packet+offset, &par2, sizeof(TD_DataPoolId));
   offset += sizeof(TD_DataPoolId);

   assert(offset < defPacketSize);

   // Load the packet definition
   for (unsigned short i=0; i<offset; i++) { 
        DC_PUSDataReportingPacket_setDefinitionBuffer(pTMP, i, packet[i]);
   }

   if (DC_PUSDataReportingPacket_getDefinitionBufferLength(pTMP) != offset)
   {  
       TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong definition buffer length");
    	return;
   }

   // Send an update request and check that there are no data to be acquired
   tpc->update(pTMP);
   if (tpc->getNumberOfBytes(pTMP) != 0)
   {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong number of bytes");
    	return;
   }

   // Update the values of the data pool items
   dpc->setFloatValue(pDP, par2, 4*val2);

   // Send an update request and check data acquisition service
   tpc->update(pTMP);
   n1 = sizeof(TD_SID);
   n2 = (PUS_DATA_REP_MODE ? 1 : 0);
   n3 = sizeof(TD_Float);
   expNumberOfBytes = n1 + n2 + n3;
   if (tpc->getNumberOfBytes(pTMP) != expNumberOfBytes)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong number of bytes");
    	return;
   }

   // Collect the packet data and check their values
   valBuffer = g_malloc(sizeof(unsigned char)*valBufferSize);
   nBytes = tpc->getNumberOfBytes(pTMP);
   for (unsigned int i=0; i<nBytes; i++) { 
       valBuffer[i] = tpc->getUnsignedByte(pTMP, i);
   }

   valOffset = 0;
   memcpy(&sidTemp, valBuffer+valOffset, sizeof(TD_SID));
   if (sidTemp != sid)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong sid field");
    	return;
   }
   valOffset += sizeof(TD_SID);

   if ((PUS_DATA_REP_MODE ? (valBuffer[valOffset] != 0) : false))
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong mode field");
    	return;
   }

   valOffset += (PUS_DATA_REP_MODE ? 1 : 0);

   memcpy(&flTemp, valBuffer+valOffset, sizeof(TD_Float));
   if (fabs((float)(flTemp - (TD_Float)4*val2)) > FLT_EPSILON)
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong parameter 2 field");
    	return;
   }
   valOffset += sizeof(TD_Float);

   assert(valOffset < valBufferSize);

   // Simulate an attempt to load a larger-than-legal definition packet
   if (TestCase_isNonNominalCheckAllowed(obj)) {
       // the maximum value of the first par is (defPacketSize-1)
        DC_PUSDataReportingPacket_setDefinitionBuffer(pTMP, defPacketSize, 0);
        if (!verifyLatestEvent(obj, nEvt+1, EVT_ILLEGAL_PUS_REP_PACKET)) return;
        nEvt = nEvt + 1;         
   }

   // Restore the original data pool
   CC_RootObject_setDataPool(pOldDP);

   TestCase_setTestResult((TestCase*)obj, TEST_SUCCESS, "Test Successful");
   return;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj){}

TestCasePUSDataReportingPacket_1* TestCasePUSDataReportingPacket_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEPUSDATAREPORTINGPACKET_1);

    TESTCASEWITHEVTCHECK_GET_CLASS(obj)->post_init((TestCaseWithEvtCheck*)obj,
                                               ID_PUSDATAREPORTINGPACKET*10+1,
                                          "TestCasePUSDataReportingPacket_1"); 

    return (TestCasePUSDataReportingPacket_1*)obj;
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
    .name = TYPE_TESTCASEPUSDATAREPORTINGPACKET_1,
    .parent = TYPE_TESTCASEWITHEVTCHECK,
    .instance_size = sizeof(TestCasePUSDataReportingPacket_1),
    .abstract = false,
    .class_size = sizeof(TestCasePUSDataReportingPacket_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCasePUSDataReportingPacket_1_register(void)
{
    type_register_static(&type_info);
}
