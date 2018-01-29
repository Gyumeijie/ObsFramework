//
//
// DC_PUSMemoryDumpAbsolute.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/TestConstants.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../Base/CC_RootObject.h"
#include "../Utilities/Checksum.h"
#include "../Telemetry/PUSTelemetryPacket.h"
#include "../Telemetry/DC_PUSMemoryDumpAbsolute.h"

#include <string.h>



///////////////////////////////////////////////////////////////////////////////
// //                    non-pure virtual  method(s) definition //
///////////////////////////////////////////////////////////////////////////////

/**
 * Implement the <i>data update service</i> for the PUS memory dump with absolute addresses packet.
 * The memory locations to be dumped are stored in the <code>block</code> data structure
 * defined in the superclass. The memory dump data are collected and stored in the
 * <i>dump buffer</i> which is also defined in the superclass. Both the <code>block</code>
 * and <i>dump buffer</i> structures are declared <code>protected</code> in the superclass
 * and can therefore be directly accessed here. This method uses the data in the 
 * <code>block</code> structure and the value of the base address to construct and image of the
 * telemetry packet and store it in the <i>dump buffer</i>. 
 */
static void update(void *obj)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    PUSMemoryDump *parent = PUSMEMORYDUMP(obj);

    assert(parent->memId != 0);
    assert(cc_roc->isObjectConfigured(obj));

    unsigned char *data = parent->data;
    MemBlockType* const block = parent->block;

    unsigned int offset = 0;
    memcpy(data+offset, &parent->memId, sizeof(TD_PUSMemId));
    offset = offset + sizeof(TD_PUSMemId);
    memcpy(data+offset, &parent->numberBlocks, sizeof(TD_PUSNumberMemBlocks));
    offset = offset + sizeof(TD_PUSNumberMemBlocks);

    assert(parent->numberBlocks < parent->maxNumberBlocks);

    for (TD_PUSNumberMemBlocks i=0; i<parent->numberBlocks; i++)  {
        memcpy(data+offset, &block[i].startAddress, sizeof(TD_PUSMemData*));
        offset = offset + sizeof(TD_PUSMemData*);
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
        assert(sizeof(unsigned short) == 2);
    }
}


///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    TelemetryPacketClass *tpc = TELEMETRYPACKET_GET_CLASS(obj);
    tpc->setSubType(obj, PUS_ST_TM_DMP_ABS);

    CC_RootObject_setClassId((CC_RootObject*)obj, ID_PUSMEMORYDUMPABSOLUTE);
}

DC_PUSMemoryDumpAbsolute* DC_PUSMemoryDumpAbsolute_new(void)
{
    Object *obj = object_new(TYPE_DC_PUSMEMORYDUMPABSOLUTE);
    return (DC_PUSMemoryDumpAbsolute*)obj;
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
    .name = TYPE_DC_PUSMEMORYDUMPABSOLUTE,
    .parent = TYPE_PUSMEMORYDUMP,
    .instance_size = sizeof(DC_PUSMemoryDumpAbsolute),
    .abstract = false,
    .class_size = sizeof(DC_PUSMemoryDumpAbsoluteClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_PUSMemoryDumpAbsolute_register(void)
{
    type_register_static(&type_info);
}
