//
//
// TestCasePUSDataReportingPacket_3.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "../Telemetry/DC_PUSDataReportingPacket.h"
#include "../Data/DC_SampleFullDataPool.h"
#include "../Utilities/TestCaseWithEvtCheck.h"
#include "TestCasePUSDataReportingPacket_3.h"

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
   TD_PUSCollectionInterval collectionInterval = 6;
   TD_PUSNumberOfParameters NPAR1 = 1;
   unsigned char NFA = 2;
   unsigned char NREP2 = 2;
   TD_PUSNumberOfParameters NPAR2 = 2;
   unsigned char NREP3 = 3;
   TD_PUSNumberOfParameters NPAR3 = 1;
   TD_DataPoolId par1 = 1;
   TD_Integer val1 = 11;
   TD_DataPoolId par2 = 2;
   TD_Float val2 = 12.0;
   TD_DataPoolId par3 = 4;
   TD_Integer val3 = 14;
   TD_DataPoolId par4 = 5;
   TD_Float val4 = 15.0;

   // Construct the packet
   unsigned short defPacketSize = 300;
   unsigned char *packet = g_malloc(sizeof(unsigned char)*defPacketSize);
   unsigned int offset = 0;

   memcpy(packet+offset, &sid, sizeof(TD_SID));
   offset += sizeof(TD_SID);
   memcpy(packet+offset, &collectionInterval, sizeof(TD_PUSCollectionInterval));
   offset += sizeof(TD_PUSCollectionInterval);
   memcpy(packet+offset, &NPAR1, sizeof(TD_PUSNumberOfParameters));
   offset += sizeof(TD_PUSNumberOfParameters);
   memcpy(packet+offset, &par1, sizeof(TD_DataPoolId));
   offset += sizeof(TD_DataPoolId);
   memcpy(packet+offset, &NFA, 1);
   offset += 1;
   memcpy(packet+offset, &NREP2, 1);
   offset += 1;
   memcpy(packet+offset, &NPAR2, sizeof(TD_PUSNumberOfParameters));
   offset += sizeof(TD_PUSNumberOfParameters);
   memcpy(packet+offset, &par2, sizeof(TD_DataPoolId));
   offset += sizeof(TD_DataPoolId);
   memcpy(packet+offset, &par3, sizeof(TD_DataPoolId));
   offset += sizeof(TD_DataPoolId);
   memcpy(packet+offset, &NREP3, 1);
   offset += 1;
   memcpy(packet+offset, &NPAR3, sizeof(TD_PUSNumberOfParameters));
   offset += sizeof(TD_PUSNumberOfParameters);
   memcpy(packet+offset, &par4, sizeof(TD_DataPoolId));
   offset += sizeof(TD_DataPoolId);

   assert(offset < defPacketSize);

   // Configure the data reporting packet and check configuration status
   DC_PUSDataReportingPacket_setMaxNumberFA(pTMP, 2);
   DC_PUSDataReportingPacket_setDefinitionBufferSize(pTMP, defPacketSize);
   unsigned int valBufferSize = 75;
   DC_PUSDataReportingPacket_setValueBufferSize(pTMP, valBufferSize);
   tpc->setSubType(pTMP, PUS_ST_DATA_REP_PAR_HK_REP);
   tpc->setTimeTag(pTMP, 0);
   DC_PUSDataReportingPacket_setEnabled(pTMP, ENABLED);
   if (!cc_roc->isObjectConfigured(pTMP))
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong configuration status");
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

   // Set the values of the data pool items
   dpc->setIntegerValue(pDP, par1, val1);
   dpc->setFloatValue(pDP, par2, val2);
   dpc->setIntegerValue(pDP, par3, val3);
   dpc->setFloatValue(pDP, par4, val4);

   // Send five update requests and check that there are no data to be acquired
   // The data pool item values are updated after each update request
   tpc->update(pTMP);
   if (tpc->getNumberOfBytes(pTMP) != 0)
   {	
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong number of bytes");
    	return;
   }
   dpc->setIntegerValue(pDP, par1, (TD_Integer)(2*val1));
   dpc->setFloatValue(pDP, par2, (TD_Float)(2*val2));
   dpc->setIntegerValue(pDP, par3, (TD_Integer)(2*val3));
   dpc->setFloatValue(pDP, par4, (TD_Float)(2*val4));

   tpc->update(pTMP);
   if (tpc->getNumberOfBytes(pTMP) != 0)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong number of bytes");
    	return;
   }

   dpc->setIntegerValue(pDP, par1, (TD_Integer)(3*val1));
   dpc->setFloatValue(pDP, par2, (TD_Float)(3*val2));
   dpc->setIntegerValue(pDP, par3, (TD_Integer)(3*val3));
   dpc->setFloatValue(pDP, par4, (TD_Float)(3*val4));

   tpc->update(pTMP);
   if (tpc->getNumberOfBytes(pTMP) != 0)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong number of bytes");
    	return;
   }
   dpc->setIntegerValue(pDP, par1, (TD_Integer)(4*val1));
   dpc->setFloatValue(pDP, par2, (TD_Float)(4*val2));
   dpc->setIntegerValue(pDP, par3, (TD_Integer)(4*val3));
   dpc->setFloatValue(pDP, par4, (TD_Float)(4*val4));

   tpc->update(pTMP);
   if (tpc->getNumberOfBytes(pTMP) != 0)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong number of bytes");
    	return;
   }
   dpc->setIntegerValue(pDP, par1, (TD_Integer)(5*val1));
   dpc->setFloatValue(pDP, par2, (TD_Float)(5*val2));
   dpc->setIntegerValue(pDP, par3, (TD_Integer)(5*val3));
   dpc->setFloatValue(pDP, par4, (TD_Float)(5*val4));

   tpc->update(pTMP);
   if (tpc->getNumberOfBytes(pTMP) != 0)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong number of bytes");
    	return;
   }
   dpc->setIntegerValue(pDP, par1, (TD_Integer)(6*val1));
   dpc->setFloatValue(pDP, par2, (TD_Float)(6*val2));
   dpc->setIntegerValue(pDP, par3, (TD_Integer)(6*val3));
   dpc->setFloatValue(pDP, par4, (TD_Float)(6*val4));

   // Send the sixth update request and check data acquisition service
   tpc->update(pTMP);
   dpc->setIntegerValue(pDP, par1, (TD_Integer)(7*val1));
   dpc->setFloatValue(pDP, par2, (TD_Float)(7*val2));
   dpc->setIntegerValue(pDP, par3, (TD_Integer)(7*val3));
   dpc->setFloatValue(pDP, par4, (TD_Float)(7*val4));

   unsigned int n1, n2, n3;
   n1 = sizeof(TD_SID);
   n2 = (PUS_DATA_REP_MODE ? 1 : 0);
   n3 = 1*sizeof(TD_Integer) + 2*sizeof(TD_Float) + 
        2*sizeof(TD_Integer) + 3*sizeof(TD_Float);
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
       assert(i < valBufferSize);
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
   valOffset += (PUS_DATA_REP_MODE?1:0);

   memcpy(&intTemp, valBuffer+valOffset, sizeof(TD_Integer));
   if (intTemp != (TD_Integer)6*val1)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong parameter 1 field");
    	return;
   }
   valOffset += sizeof(TD_Integer);

   memcpy(&flTemp, valBuffer+valOffset, sizeof(TD_Float));
   if (fabs((float)(flTemp - (TD_Float)3*val2)) > FLT_EPSILON)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong parameter 2 field");
    	return;
   }
   valOffset += sizeof(TD_Float);

   memcpy(&intTemp, valBuffer+valOffset, sizeof(TD_Integer));
   if (intTemp != (TD_Integer)3*val3)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong parameter 3 field");
    	return;
   }
   valOffset += sizeof(TD_Integer);

   memcpy(&flTemp, valBuffer+valOffset, sizeof(TD_Float));
   if (fabs((float)(flTemp - (TD_Float)6*val2)) > FLT_EPSILON)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong parameter 2 field");
    	return;
   }
   valOffset += sizeof(TD_Float);

   memcpy(&intTemp, valBuffer+valOffset, sizeof(TD_Integer));
   if (intTemp  != (TD_Integer)6*val3)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong parameter 3 field");
    	return;
   }
   valOffset += sizeof(TD_Integer);

   memcpy(&flTemp, valBuffer+valOffset, sizeof(TD_Float));
   if (fabs((float)(flTemp  - (TD_Float)2*val4)) > FLT_EPSILON)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong parameter 4 field");
    	return;
   }
   valOffset += sizeof(TD_Float);

   memcpy(&flTemp, valBuffer+valOffset, sizeof(TD_Float));
   if (fabs((float)(flTemp  - (TD_Float)4*val4)) > FLT_EPSILON)
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong parameter 4 field");
    	return;
   }
   valOffset += sizeof(TD_Float);

   memcpy(&flTemp, valBuffer+valOffset, sizeof(TD_Float));
   if (fabs((float)(flTemp  - (TD_Float)6*val4)) > FLT_EPSILON)
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong parameter 4 field");
    	return;
   }

   assert(valOffset < valBufferSize);

   // Send five update requests and check that there are no data to be acquired
   // The data pool item values are updated after each update request
   tpc->update(pTMP);
   if (tpc->getNumberOfBytes(pTMP) != 0)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong number of bytes");
    	return;
   }
   dpc->setIntegerValue(pDP, par1, (TD_Integer)(8*val1));
   dpc->setFloatValue(pDP, par2, (TD_Float)(8*val2));
   dpc->setIntegerValue(pDP, par3, (TD_Integer)(8*val3));
   dpc->setFloatValue(pDP, par4, (TD_Float)(8*val4));

   tpc->update(pTMP);
   if (tpc->getNumberOfBytes(pTMP) != 0)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong number of bytes");
    	return;
   }
   dpc->setIntegerValue(pDP, par1, (TD_Integer)(9*val1));
   dpc->setFloatValue(pDP, par2, (TD_Float)(9*val2));
   dpc->setIntegerValue(pDP, par3, (TD_Integer)(9*val3));
   dpc->setFloatValue(pDP, par4, (TD_Float)(9*val4));

   tpc->update(pTMP);
   if (tpc->getNumberOfBytes(pTMP) != 0)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong number of bytes");
    	return;
   }
   dpc->setIntegerValue(pDP, par1, (TD_Integer)(10*val1));
   dpc->setFloatValue(pDP, par2, (TD_Float)(10*val2));
   dpc->setIntegerValue(pDP, par3, (TD_Integer)(10*val3));
   dpc->setFloatValue(pDP, par4, (TD_Float)(10*val4));

   tpc->update(pTMP);
   if (tpc->getNumberOfBytes(pTMP) != 0)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong number of bytes");
    	return;
   }
   dpc->setIntegerValue(pDP, par1, (TD_Integer)(11*val1));
   dpc->setFloatValue(pDP, par2, (TD_Float)(11*val2));
   dpc->setIntegerValue(pDP, par3, (TD_Integer)(11*val3));
   dpc->setFloatValue(pDP, par4, (TD_Float)(11*val4));

   tpc->update(pTMP);
   if (tpc->getNumberOfBytes(pTMP) != 0)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong number of bytes");
    	return;
   }
   dpc->setIntegerValue(pDP, par1, (TD_Integer)(12*val1));
   dpc->setFloatValue(pDP, par2, (TD_Float)(12*val2));
   dpc->setIntegerValue(pDP, par3, (TD_Integer)(12*val3));
   dpc->setFloatValue(pDP, par4, (TD_Float)(12*val4));

   // Send the sixth update request and check data acquisition service
   tpc->update(pTMP);

   n1, n2, n3;
   n1 = sizeof(TD_SID);
   n2 = (PUS_DATA_REP_MODE ? 1 : 0);
   n3 = 1*sizeof(TD_Integer) + 2*sizeof(TD_Float) + 
        2*sizeof(TD_Integer) + 3*sizeof(TD_Float);
   expNumberOfBytes = n1+n2+n3;
   if (tpc->getNumberOfBytes(pTMP) != expNumberOfBytes)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong number of bytes");
    	return;
   }

   // Collect the packet data and check their values
   nBytes = tpc->getNumberOfBytes(pTMP);
   for (unsigned int i=0; i<nBytes; i++) {
       valBuffer[i] = tpc->getUnsignedByte(pTMP, i);
       assert(i < valBufferSize);
   }

   valOffset = 0;
   memcpy(&sidTemp, valBuffer+valOffset, sizeof(TD_SID));
   if (memcmp(valBuffer+valOffset, &sid, sizeof(TD_SID)) != 0)
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
   if (intTemp != (TD_Integer)12*val1)
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong parameter 1 field");
    	return;
   }
   valOffset += sizeof(TD_Integer);

   memcpy(&flTemp, valBuffer+valOffset, sizeof(TD_Float));
   if (fabs((float)(flTemp  - (TD_Float)9*val2)) > FLT_EPSILON)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong parameter 2 field");
    	return;
   }
   valOffset += sizeof(TD_Float);

   memcpy(&intTemp, valBuffer+valOffset, sizeof(TD_Integer));
   if (intTemp != (TD_Integer)9*val3)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong parameter 3 field");
    	return;
   }
   valOffset += sizeof(TD_Integer);

   memcpy(&flTemp, valBuffer+valOffset, sizeof(TD_Float));
   if (fabs((float)(flTemp  - (TD_Float)12*val2)) > FLT_EPSILON)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong parameter 2 field");
    	return;
   }
   valOffset += sizeof(TD_Float);

   memcpy(&intTemp, valBuffer+valOffset, sizeof(TD_Integer));
   if (intTemp != (TD_Integer)12*val3)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong parameter 3 field");
    	return;
   }
   valOffset += sizeof(TD_Integer);

   memcpy(&flTemp, valBuffer+valOffset, sizeof(TD_Float));
   if (fabs((float)(flTemp  - (TD_Float)8*val4)) > FLT_EPSILON)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong parameter 4 field");
    	return;
   }
   valOffset += sizeof(TD_Float);

   memcpy(&flTemp, valBuffer+valOffset, sizeof(TD_Float));
   if (fabs((float)(flTemp  - (TD_Float)10*val4)) > FLT_EPSILON)
   {    
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong parameter 4 field");
    	return;
   }
   valOffset += sizeof(TD_Float);

   memcpy(&flTemp, valBuffer+valOffset, sizeof(TD_Float));
   if (fabs((float)(flTemp  - (TD_Float)12*val4)) > FLT_EPSILON)
   {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong parameter 4 field");
    	return;
   }
   valOffset += sizeof(TD_Float);
   assert(valOffset < valBufferSize);

   // Construct a packet that will cause the packet value buffer to overflow
   if (TestCase_isNonNominalCheckAllowed(obj)) {
       unsigned int nIntPar = (unsigned int)(valBufferSize-sizeof(TD_SID)-
                              (PUS_DATA_REP_MODE?1:0))/sizeof(TD_Integer) + 1;
       sid = 13;
       collectionInterval = 1;
       NPAR1 = (TD_PUSNumberOfParameters)nIntPar;
       NFA = 0;
       par1 = 1;

       offset = 0;                                  // the new packet is defined
       memcpy(packet+offset, &sid, sizeof(TD_SID));
       offset += sizeof(TD_SID);
       memcpy(packet+offset, &collectionInterval, sizeof(TD_PUSCollectionInterval));
       offset += sizeof(TD_PUSCollectionInterval);
       memcpy(packet+offset, &NPAR1, sizeof(TD_PUSNumberOfParameters));
       offset += sizeof(TD_PUSNumberOfParameters);

       for (unsigned int i=0; i<NPAR1; i++) {
            memcpy(packet+offset, &par1, sizeof(TD_DataPoolId));
            offset += sizeof(TD_DataPoolId);
       }
       assert(offset < defPacketSize);

       for (unsigned short i=0; i<offset; i++) {  // the new packet definition is loaded
           DC_PUSDataReportingPacket_setDefinitionBuffer(pTMP, i, packet[i]);
       }

       tpc->update(pTMP);

       if (!verifyLatestEvent(obj, nEvt+1, EVT_PUS_DATA_REP_PACKET_TOO_LARGE)) return;
       nEvt = nEvt+1;
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

TestCasePUSDataReportingPacket_3* TestCasePUSDataReportingPacket_3_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEPUSDATAREPORTINGPACKET_3);

    TESTCASEWITHEVTCHECK_GET_CLASS(obj)->post_init((TestCaseWithEvtCheck*)obj,
                                               ID_PUSDATAREPORTINGPACKET*10+3,
                                          "TestCasePUSDataReportingPacket_3");

    return (TestCasePUSDataReportingPacket_3*)obj;
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
    .name = TYPE_TESTCASEPUSDATAREPORTINGPACKET_3,
    .parent = TYPE_TESTCASEWITHEVTCHECK,
    .instance_size = sizeof(TestCasePUSDataReportingPacket_3),
    .abstract = false,
    .class_size = sizeof(TestCasePUSDataReportingPacket_3Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCasePUSDataReportingPacket_3_register(void)
{
    type_register_static(&type_info);
}
