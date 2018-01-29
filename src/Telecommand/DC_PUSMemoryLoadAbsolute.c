//
//
// DC_PUSMemoryLoadAbsolute.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "DC_PUSMemoryLoadAbsolute.h"

#include <string.h>



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

TD_PUSMemId DC_PUSMemoryLoadAbsolute_getMemoryBlockId
(
    const DC_PUSMemoryLoadAbsolute *This
)
{
    return This->memId;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Implementation of the raw data load service. This method would normally
 * be called by a telecommand loader to load the application data into the
 * the telecommand component. This method interprets the raw data as they are
 * loaded and uses them to configure the data structure(defined by the
 * super class) that holds the start address, the length, the checksum, 
 * and the memory load data for each block. The application data are constrained
 * to fit within the data structures configured at the level of the superclass.
 * Two such constraints apply:<ul>
 * <li>The number of bytes to be transferred(the value of argument n) must
 * be greater than: 
 * <code>sizeof(TD_PUSMemId)+sizeof(TD_PUSNumberMemBlocks)</code>.
 * If this is not the case, the validity check
 * code is set to VC_INCONSISTENT_RAW_DATA.</li>
 * <li>The number of blocks must be less or equal than the maximum number of
 * blocks defined in the super class. If this is not the case, the validity check
 * code is set to VC_TOO_MANY_MEM_BLOCK.</li>
 * <li>The total number of memory data to be loaded must not exceed the maximum
 * value defined in the super class. If this is not the case, the validity check
 * code is set to VC_TOO_MANY_MEM_DATA.</li>
 * <li>The number of bytes to be transferred(the value of argument n) must 
 * be consistent with the number of blocks and of data inferred from the application
 * data. If this is not the case, the validity check
 * code is set to VC_INCONSISTENT_RAW_DATA.</li>
 * </ul>
 * When a constraint is violated, the method returns immediately after setting the
 * value of the validity check code.
 * @param n the number of bytes in the raw data
 * @param d the starting address of the raw data
 */
static void setRawDataFastly(void *obj, unsigned char *d, unsigned int n)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj); 
    PUSMemoryLoad *parent = PUSMEMORYLOAD(obj);
    DC_PUSMemoryLoadAbsolute *This = DC_PUSMEMORYLOADABSOLUTE(obj);

    assert(d != pNULL);
    assert(n > 0);
    assert(cc_roc->isObjectConfigured(obj));
    assert(sizeof(TD_PUSMemData) == 1);

    PUSTelecommand_setValidityCheckCode(obj, 0);

    if (n <= (sizeof(TD_PUSMemId)+sizeof(TD_PUSNumberMemBlocks))) {
        PUSTelecommand_setValidityCheckCode(obj, VC_INCONSISTENT_RAW_DATA);
        return;
    }

    TD_PUSMemLength length;
    unsigned int counter;
    unsigned int dataCounter;

    memcpy(&This->memId, d, sizeof(TD_PUSMemId));
    memcpy(&parent->numberBlocks, 
           d + sizeof(TD_PUSMemId), 
           sizeof(TD_PUSNumberMemBlocks));

    if (parent->numberBlocks > parent->maxNumberBlocks) {
        PUSTelecommand_setValidityCheckCode(obj, VC_TOO_MANY_MEM_BLOCK);
        return;
    }

    counter = sizeof(TD_PUSMemId) + sizeof(TD_PUSNumberMemBlocks);
    dataCounter = 0;
    // In Order to access block and data concisely below.
    MemBlockType* const block = parent->block;
    TD_PUSMemData* const data = parent->data;
    for (unsigned int i=0; i<parent->numberBlocks; i++) {
        memcpy(&block[i].startAddress, d + counter, sizeof(TD_PUSMemData*));
        memcpy(&block[i].length, d + counter + sizeof(TD_PUSMemData*),
               sizeof(TD_PUSMemLength));
        length = block[i].length;
        if ((dataCounter + length) >= parent->maxNumberData) {
            PUSTelecommand_setValidityCheckCode(obj, VC_TOO_MANY_MEM_DATA);
            return;
        }

        // For temporary use. 
        unsigned char *dataOffset = d + counter + sizeof(TD_PUSMemData*) +
                                    sizeof(TD_PUSMemLength);
        for (unsigned int j=0; j<length; j++) {
            TD_PUSMemData *dataAddr = dataOffset + j*sizeof(TD_PUSMemData);
            data[dataCounter+j] = *dataAddr; 
        }

        memcpy(&block[i].checksum, (dataOffset + length*sizeof(TD_PUSMemData)),
               sizeof(unsigned short));

        counter = (counter + sizeof(TD_PUSMemData*) + sizeof(TD_PUSMemLength) +
                   sizeof(TD_PUSMemData)*length + 2);

        dataCounter = dataCounter + length;
    }

    if (counter != n) {
        PUSTelecommand_setValidityCheckCode(obj, VC_INCONSISTENT_RAW_DATA);
        return;
    }
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    DC_PUSMemoryLoadAbsolute *This = DC_PUSMEMORYLOADABSOLUTE(obj);
    This->memId = 0;

    CC_RootObject_setClassId((CC_RootObject*)obj, ID_PUSMEMORYLOADABSOLUTE);

    TelecommandClass *tc = TELECOMMAND_GET_CLASS(obj);
    tc->setSubType(obj, PUS_ST_TC_MEM_ABS);
}

DC_PUSMemoryLoadAbsolute* DC_PUSMemoryLoadAbsolute_new(void)
{
    Object *obj = object_new(TYPE_DC_PUSMEMORYLOADABSOLUTE);
    return (DC_PUSMemoryLoadAbsolute*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    TelecommandClass *tc = TELECOMMAND_CLASS(oc);
    tc->setRawDataFastly = setRawDataFastly;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_PUSMEMORYLOADABSOLUTE,
    .parent = TYPE_PUSMEMORYLOAD,
    .instance_size = sizeof(DC_PUSMemoryLoadAbsolute),
    .abstract = false,
    .class_size = sizeof(DC_PUSMemoryLoadAbsoluteClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_PUSMemoryLoadAbsolute_register(void)
{
    type_register_static(&type_info);
}
