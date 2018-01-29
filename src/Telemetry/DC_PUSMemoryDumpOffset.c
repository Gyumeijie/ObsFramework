//
//
// DC_PUSMemoryDumpOffset.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/TestConstants.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../Base/CC_RootObject.h"
#include "../Utilities/Checksum.h"
#include "../Event/DC_EventRepository.h"
#include "../Telemetry/PUSTelemetryPacket.h"
#include "../Telemetry/DC_PUSMemoryDumpOffset.h"

#include <string.h>



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_PUSMemoryDumpOffset_setBaseAddress(DC_PUSMemoryDumpOffset *This, 
                                           TD_PUSMemData* base)
{
    assert(base != 0);
    This->base = base;
}

TD_PUSMemData* DC_PUSMemoryDumpOffset_getBaseAddress(DC_PUSMemoryDumpOffset *This)
{
    return This->base;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Implement the <i>data update service</i> for the PUS memory dump with offset telemetry packet.
 * The memory locations to be dumped are stored in the <code>block</code> data structure
 * defined in the superclass. The memory dump data are collected and stored in the
 * <i>dump buffer</i> which is also defined in the superclass. Both the <code>block</code>
 * and <i>dump buffer</i> structures are declared <code>protected</code> in the superclass
 * and can therefore be directly accessed here. This method uses the data in the 
 * <code>block</code> structure and the value of the base address to construct and image of the
 * telemetry packet and store it in the <i>dump buffer</i>. 
 * <p>
 * This method relies on the data in the <code>block</code> data structure to be consistent with
 * the value of the base address. In particular, the following must be ensured: <ul>
 * <li>The value of the base address must be smaller than all the <code>startAddress</code>
 * fields of the <code>block</code> data structure.</li>
 * <li>The offset field is computed as the difference between the value of the <code>startAddress</code>
 * field of the <code>block</code> data structure and the value of the base address. The result
 * must be expressible as an integer of type <code>TD_PUSMemOffset</code>.</li>
 * </ul>
 * Compliance with the above conditions is not checked at run time(but violation may result in
 * in a run-time exception). As they are collected, the memory dump data are stored in the
 * <i>dump buffer</i> defined by the superclass. A check is made that there is no overflow.
 * If this is found to be the case, then the method returns after generating event report
 * EVT_PUS_TOO_MANY_MEM_DATA. In this case, no memory dump data are collected.
 */
static void update(void *obj)
{
    DC_PUSMemoryDumpOffset *This = DC_PUSMEMORYDUMPOFFSET(obj);
    TelemetryPacketClass *tpc = TELEMETRYPACKET_GET_CLASS(obj);
    PUSMemoryDump *parent = PUSMEMORYDUMP(obj);

    assert(This->base != pNULL);
    assert(parent->memId != 0);
    assert(CC_ROOTOBJECT_CLASS(tpc)->isObjectConfigured(obj));
        
    // compute the number of bytes in the packet. Compute first the size of the
    // fixed part of the packet and then the size of each block.
    unsigned int fixedLength = sizeof(TD_PUSMemId) + 
                               sizeof(TD_PUSMemData*) + 
                               sizeof(TD_PUSNumberMemBlocks);
    unsigned int blockLength = 0;

    unsigned char* const data = parent->data;
    MemBlockType* const block = parent->block;

    for (TD_PUSNumberMemBlocks i=0; i<parent->numberBlocks; i++) {
        blockLength = blockLength + sizeof(TD_PUSMemOffset) + 
                      sizeof(TD_PUSMemLength) + sizeof(unsigned short);
        blockLength = blockLength + block[i].length*sizeof(TD_PUSMemData);
    }

    parent->tmPacketSize = blockLength + fixedLength;
    if (parent->tmPacketSize > parent->maxNumberData) {
        DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
        DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
        dc_erc->create(dc_er, (CC_RootObject*)This, EVT_PUS_TOO_MANY_MEM_DATA);
        return;
    }

    unsigned int offset = 0;
    memcpy(data+offset, &parent->memId, sizeof(TD_PUSMemId));
    offset = offset + sizeof(TD_PUSMemId);
    memcpy(data+offset, &This->base, sizeof(TD_PUSMemData*));
    offset = offset + sizeof(TD_PUSMemData*);
    memcpy(data+offset, &parent->numberBlocks, sizeof(TD_PUSNumberMemBlocks));
    offset = offset + sizeof(TD_PUSNumberMemBlocks);

    assert(parent->numberBlocks < parent->maxNumberBlocks);

    for (TD_PUSNumberMemBlocks i=0; i<parent->numberBlocks; i++)  {

        TD_PUSMemOffset moTemp = (TD_PUSMemOffset)(block[i].startAddress-This->base);
        memcpy(data+offset, &moTemp, sizeof(TD_PUSMemOffset));
        offset = offset + sizeof(TD_PUSMemOffset);
        memcpy(data+offset, &block[i].length, sizeof(TD_PUSMemLength));
        offset = offset + sizeof(TD_PUSMemLength);

        unsigned char *start = (unsigned char*)(block[i].startAddress);
        unsigned int nBytes = (block[i].length)*sizeof(TD_PUSMemData);
        memcpy(data+offset, start, nBytes);
        offset = offset + nBytes;

        unsigned short checksum;
        if (PUSMemoryDump_isChecksumFlagSet()) {
            checksum = doChecksum(start, nBytes);
        } else {
            checksum = 0;
        }

        memcpy(data+offset, &checksum, sizeof(unsigned short));
        offset = offset + sizeof(unsigned short);
    }
}


///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    DC_PUSMemoryDumpOffset *This = DC_PUSMEMORYDUMPOFFSET(obj);
    This->base = pNULL;
   
    TelemetryPacketClass *tpc = TELEMETRYPACKET_GET_CLASS(obj);
    tpc->setSubType(obj, PUS_ST_TM_DMP_OFF);

    CC_RootObject_setClassId((CC_RootObject*)obj, ID_PUSMEMORYDUMPOFFSET);
}

DC_PUSMemoryDumpOffset* DC_PUSMemoryDumpOffset_new(void)
{
    Object *obj = object_new(TYPE_DC_PUSMEMORYDUMPOFFSET);
    return (DC_PUSMemoryDumpOffset*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    TelemetryPacketClass *tpc = TELEMETRYPACKET_CLASS(oc);
    tpc->update = update;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_PUSMEMORYDUMPOFFSET,
    .parent = TYPE_PUSMEMORYDUMP,
    .instance_size = sizeof(DC_PUSMemoryDumpOffset),
    .abstract = false,
    .class_size = sizeof(DC_PUSMemoryDumpOffsetClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_PUSMemoryDumpOffset_register(void)
{
    type_register_static(&type_info);
}
