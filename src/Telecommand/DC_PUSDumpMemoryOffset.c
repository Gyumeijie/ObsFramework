//
//
// DC_PUSDumpMemoryOffset.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "DC_PUSDumpMemoryOffset.h"
#include "../Telemetry/CC_TelemetryManager.h"
#include "../Telemetry/CC_TelemetryPacketFactory.h"
#include "../Telemetry/DC_PUSMemoryDumpOffset.h"
#include "../Telemetry/DC_PUSMemoryDumpAbsolute.h"
#include "../Data/DataPool.h"

#include <string.h>



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Use the application data to configure and load a memory dump telemetry packet
 * with base plus offset.
 * This method queries the dynamic telemetry packet factory for a new
 * memory dump packet. If it obtains it, it interprets the application data and 
 * configures the memory dump packet. The following operations are performed on
 * the memory dump packet:<ul>
 * <li>The number of blocks is defined </li>
 * <li>If a memory dump with base plus offset is required, the base address is
 * set</li>
 * <li>Each memory block is configured with its start address and length</li>
 * </ul>
 * After being configured, the telemetry packet is loaded in the immediate
 * dispatch queue of the telemetry manager.
 * This method can return a failure code. See the class comment for details.
 * @see PunctualAction#execute
 * @return action outcome code(see class comment)
 */
static TD_ActionOutcome doAction(void *obj)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    PUSDumpMemory *This = PUSDUMPMEMORY(obj);

    assert(cc_roc->isObjectConfigured(obj));

    CC_TelemetryPacketFactory *pFct = CC_TelemetryPacketFactory_getInstance();
    unsigned int offset;

    // recover the number of blocks
    offset = sizeof(TD_PUSMemId) + sizeof(TD_PUSMemData*);
    TD_PUSNumberMemBlocks numberBlocks;
    memcpy(&numberBlocks, This->data+offset, sizeof(TD_PUSNumberMemBlocks));

    // compute the length of the fixed part of the telemetry packet
    unsigned int fixedLength;
    fixedLength = sizeof(TD_PUSMemId) + sizeof(TD_PUSMemData*) + sizeof(TD_PUSNumberMemBlocks);
    
    // compute the length of the data part of the telemetry packet
    unsigned int t = fixedLength + sizeof(TD_PUSMemOffset);
    unsigned int dataLength = 0;
    for (TD_PUSNumberMemBlocks i=0; i<numberBlocks; i++) {
        TD_PUSMemLength blockLength;
        memcpy(&blockLength, This->data+t, sizeof(TD_PUSMemLength));
        dataLength = dataLength + blockLength;
        t = t + sizeof(TD_PUSMemOffset);
    }

    // compute the total length of the telemery packet
    unsigned int packetLength = fixedLength+dataLength + 
                                numberBlocks*(sizeof(TD_PUSMemOffset) +
                                sizeof(TD_PUSMemLength) + sizeof(unsigned short));

    // performa a consistency check: the number of blocks must be consistent with the
    // length of the application data
    if (This->numberData != (fixedLength + 
                             numberBlocks*(sizeof(TD_PUSMemOffset) + 
                             sizeof(TD_PUSMemLength)))) 
    {
        return APP_DATA_INCONSISTENT;
    }
    // recover the telemetry packet from the telemetry factory
    DC_PUSMemoryDumpOffset *pPck;
    pPck = CC_TelemetryPacketFactory_allocatePUSMemoryDumpOffset(pFct, numberBlocks, packetLength);
    if (pPck == pNULL) return PACKET_NOT_FOUND;

    //configure the telemetry packet
    PUSMemoryDump_setNumberBlocks((PUSMemoryDump*)pPck, numberBlocks);
    offset = sizeof(TD_PUSMemId);
    TD_PUSMemData *base;
    memcpy(&base, This->data+offset, sizeof(TD_PUSMemData*));
    DC_PUSMemoryDumpOffset_setBaseAddress(pPck, base);
    offset = sizeof(TD_PUSMemId) + sizeof(TD_PUSMemData*) + sizeof(TD_PUSNumberMemBlocks);
    for (TD_PUSNumberMemBlocks i=0; i<numberBlocks; i++) {
        TD_PUSMemOffset blockOffset;
        memcpy(&blockOffset, This->data+offset, sizeof(TD_PUSMemOffset));
        offset = offset + sizeof(TD_PUSMemOffset);
        TD_PUSMemData *startAddress = base + blockOffset;
        TD_PUSMemLength blockLength;
        memcpy(&blockLength, This->data+offset, sizeof(TD_PUSMemLength));
        offset = offset + sizeof(TD_PUSMemLength);
        PUSMemoryDump_defineBlock((PUSMemoryDump*)pPck, i, startAddress, blockLength);
    }

    // Load the telemetry packet in the telemetry manager
    if (!CC_TelemetryManager_isImmediateQueueFull(This->pTmManager)) {
        TelemetryPacket_setInUse((TelemetryPacket*)pPck, NOT_IN_USE);    
        return TM_MAN_QUEUE_FULL;
    } else {
        CC_TelemetryManager_sendTelemetryPacket(This->pTmManager, (TelemetryPacket*)pPck);
    }
    
    return ACTION_SUCCESS;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    TelecommandClass *tc = TELECOMMAND_GET_CLASS(obj);
    tc->setSubType(obj, PUS_ST_TC_DMP_OFF);

    CC_RootObject_setClassId((CC_RootObject*)obj, ID_PUSDUMPMEMORYOFFSET);
}

DC_PUSDumpMemoryOffset* DC_PUSDumpMemoryOffset_new(void)
{
    Object *obj = object_new(TYPE_DC_PUSDUMPMEMORYOFFSET);
    return (DC_PUSDumpMemoryOffset*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    PunctualActionClass *pac = PUNCTUALACTION_CLASS(oc);
    pac->doAction = doAction;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_PUSDUMPMEMORYOFFSET,
    .parent = TYPE_PUSDUMPMEMORY,
    .instance_size = sizeof(DC_PUSDumpMemoryOffset),
    .abstract = false,
    .class_size = sizeof(DC_PUSDumpMemoryOffsetClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_PUSDumpMemoryOffset_register(void)
{
    type_register_static(&type_info);
}
