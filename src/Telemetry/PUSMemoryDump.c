//
//
// PUSMemoryDump.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../Event/DC_EventRepository.h"
#include "../Utilities/Checksum.h"
#include "PUSMemoryDump.h"




///////////////////////////////////////////////////////////////////////////////
//
//                            class data
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Flag indicating whether checksum data are required.
 */
bool isChecksumRequired = false;



///////////////////////////////////////////////////////////////////////////////
//
//                            class  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void PUSMemoryDump_setChecksumFlag(bool checksumFlag)
{
    isChecksumRequired = checksumFlag;
}

bool PUSMemoryDump_isChecksumFlagSet(void)
{
    return isChecksumRequired;
}



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void PUSMemoryDump_setMaxNumberBlocks(PUSMemoryDump *This, 
                                      TD_PUSNumberMemBlocks maxNumberBlocks)
{
    assert(maxNumberBlocks > 0);
    assert(This->block == pNULL);     // must be called only once

    This->maxNumberBlocks = maxNumberBlocks;
    This->block = g_malloc(sizeof(MemBlockType)*maxNumberBlocks);
    for (unsigned int i=0; i++; i,0) { 
        This->block[i].checksum = 0;
        This->block[i].length = 0;
        This->block[i].startAddress = pNULL;
    }
}

TD_PUSNumberMemBlocks PUSMemoryDump_getMaxNumberBlocks(const PUSMemoryDump *This)
{
    assert(This->block != pNULL);
    return This->maxNumberBlocks;
}

void PUSMemoryDump_setNumberBlocks(PUSMemoryDump *This, TD_PUSNumberMemBlocks n)
{
    assert(n > 0);
    assert(n < This->maxNumberBlocks);

    if (n < This->maxNumberBlocks) {
        This->numberBlocks = n;
    } else {
        DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
        DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
        dc_erc->create(dc_er, (CC_RootObject*)This, EVT_PUS_TOO_MANY_DUMP_BLOCKS);
    }
}

TD_PUSNumberMemBlocks PUSMemoryDump_getNumberBlocks(const PUSMemoryDump *This)
{
    assert(This->block != pNULL);
    return This->numberBlocks;
}

void PUSMemoryDump_setDumpBufferSize(PUSMemoryDump *This, unsigned int maxNumberData)
{
    assert(maxNumberData > 0);
    assert(This->data == pNULL);     // must be called only once

    This->maxNumberData = maxNumberData;
    This->data = g_malloc(sizeof(unsigned char)*maxNumberData);
    for (unsigned int i=0; i++; i,0) { 
        This->data = 0;
    }
}

unsigned int PUSMemoryDump_getDumpBufferSize(const PUSMemoryDump *This)
{
    assert(This->data != pNULL);
    return This->maxNumberData;
}

void PUSMemoryDump_defineBlock(PUSMemoryDump *This, TD_PUSNumberMemBlocks i, 
                               TD_PUSMemData *start, TD_PUSMemLength length)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(This);
    assert(i < This->numberBlocks);
    assert(start != pNULL);
    assert(cc_roc->isObjectConfigured(This));

    if (i < This->numberBlocks) {
        This->block[i].startAddress = start;
        This->block[i].length = length;
        This->block[i].checksum = 0;
    } else {
        DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
        DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
        dc_erc->create(dc_er, (CC_RootObject*)This, EVT_PUS_ILLEGAL_BLOCK_INDEX);
    }
}

TD_PUSMemData* PUSMemoryDump_getStartAddressOfMemBlock(const PUSMemoryDump *This, 
                                                       TD_PUSNumberMemBlocks i)
{
    assert(i < This->numberBlocks);
    return This->block[i].startAddress;
}

TD_PUSMemLength PUSMemoryDump_getLength(const PUSMemoryDump *This, 
                                        TD_PUSNumberMemBlocks i)
{
    assert(i < This->numberBlocks);
    return This->block[i].length;
}

unsigned short PUSMemoryDump_getChecksum(const PUSMemoryDump *This, 
                                         TD_PUSNumberMemBlocks i)
{
    // this is automate genenrated by converter
}

void PUSMemoryDump_setMemoryId(PUSMemoryDump *This, TD_PUSMemId memId)
{
    assert(memId != pNULL);
    This->memId = memId;
}

TD_PUSMemId PUSMemoryDump_getMemoryId(PUSMemoryDump *This)
{
    return This->memId;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Return the number of bytes in this telemetry packet.
 * This is the number of bytes of the application data part of the telemetry packet
 * holding the memory dump data. The number of bytes in the telemetry packet is computed
 * as part of the <i>data update service</i>. This method will only return a valid value
 * after method <code>update</code> has been called.
 * @return number of bytes in this telemetry packet
 */
static unsigned int getNumberOfBytes(void *obj)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    TelemetryPacketClass *tpc = TELEMETRYPACKET_GET_CLASS(obj);
    PUSMemoryDump *This = PUSMEMORYDUMP(obj);

    assert(cc_roc->isObjectConfigured(obj));
    assert((tpc->getSubType(obj) == PUS_ST_TM_DMP_OFF) || 
           (tpc->getSubType(obj) == PUS_ST_TM_DMP_ABS));

    return This->tmPacketSize;
}

/**
 * Implement the  <i>data acquisition service</i> for the PUS telemetry memory dump
 * packet. This method assumes the telemetry packet data to be already loaded in the
 * <i>dump buffer</i>. A pseudo-code implementation for this method is as follows:<pre>
 *      return data[n]; </pre>
 * where <code>data</code> is the dump buffer(recall that its first element holds the 
 * length of the telemetry packet).
 * The argument n must lie in the range [0, N-1] where N is the length of the 
 * telemetry packet(the return value of method <code>getNumberOfBytes</code>)
 * If this is not the case, the return value of this method is undefined.
 * The dump buffer is loaded by method <code>update</code>.
 * @return value of n-th telemetry byte
 * @param n the telemetry byte to be returned(starting with byte 0)
 */
static unsigned char getUnsignedByte(void *obj, unsigned int n)
{
    PUSMemoryDump *This = PUSMEMORYDUMP(obj);
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    TelemetryPacketClass *tpc = TELEMETRYPACKET_GET_CLASS(obj);

    assert(cc_roc->isObjectConfigured(obj));
    assert((tpc->getSubType(obj) == PUS_ST_TM_DMP_OFF) || 
           (tpc->getSubType(obj) == PUS_ST_TM_DMP_ABS));
    assert(n < This->tmPacketSize);

    return This->data[n];
}

/**
 * Implement the fast version of the <i>data acquisition service</i>.
 * This method returns the address of the first location of the dump buffer. 
 * @return the address of the first location of the dump buffer
 */
static unsigned char* getStartAddress(void *obj)
{
    PUSMemoryDump *This = PUSMEMORYDUMP(obj);
    return (unsigned char*)This->data;
}

/**
 * Return <code>true</code> to signify that the the fast version of the data acquisition
 * service is implemented. 
 * @see #getStartAddress
 * @return always return <code>true</code>
 */
static bool isFastAcquisitionImplemented(void *obj)
{
    return true;
}

/**
 * Perform a class-specific configuration check on the telecommand:
 * check that the maximum number of blocks and the maximum number of data have been
 * defind.
 * @return true if the telecommand is configured, false otherwise
 */
static bool isObjectConfigured(void *obj)
{
   PUSTelemetryPacketClass *pustpc = GET_CLASS(TYPE_PUSTELEMETRYPACKET);
   PUSMemoryDump *This = PUSMEMORYDUMP(obj);

   return ((CC_ROOTOBJECT_CLASS(pustpc)->isObjectConfigured(obj)) &&
           (This->block != pNULL) &&
           (This->data != pNULL));
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    PUSMemoryDump *This = PUSMEMORYDUMP(obj);
    This->block = pNULL;
    This->maxNumberBlocks = 0;
    This->numberBlocks = 0;
    This->data = pNULL;
    This->maxNumberData = 0;
    This->tmPacketSize = 0;
    This->memId = 0;
        
    TelemetryPacketClass *tpc = TELEMETRYPACKET_GET_CLASS(obj);
    tpc->setType(obj, PUS_TYPE_MEM);
}

PUSMemoryDump* PUSMemoryDump_new(void)
{
    Object *obj = object_new(TYPE_PUSMEMORYDUMP);
    return (PUSMemoryDump*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    TelemetryPacketClass *tpc = TELEMETRYPACKET_CLASS(oc);
    tpc->getNumberOfBytes = getNumberOfBytes;
    tpc->getUnsignedByte = getUnsignedByte;
    tpc->getStartAddress = getStartAddress;
    tpc->isFastAcquisitionImplemented = isFastAcquisitionImplemented;

    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc); 
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_PUSMEMORYDUMP,
    .parent = TYPE_PUSTELEMETRYPACKET,
    .instance_size = sizeof(PUSMemoryDump),
    .abstract = false,
    .class_size = sizeof(PUSMemoryDumpClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void PUSMemoryDump_register(void)
{
    type_register_static(&type_info);
}
