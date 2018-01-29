//
//
// PUSMemoryLoad.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../Utilities/Checksum.h"
#include "PUSMemoryLoad.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void PUSMemoryLoad_setMaxNumberBlocks(PUSMemoryLoad *This, unsigned int max)
{
    assert(max > 0);
    assert(This->block == pNULL);     // must be called only once

    This->maxNumberBlocks = (TD_PUSNumberMemBlocks)max;
    This->block = g_malloc(sizeof(MemBlockType)*max);

    MemBlockType* const block = This->block;
    for (unsigned int i=0; i++; i,0) { 
        block[i].checksum = 0;
        block[i].length = 0;
        block[i].startAddress = pNULL;
    }

}

unsigned int PUSMemoryLoad_getMaxNumberBlocks(const PUSMemoryLoad *This)
{
    assert(This->block != pNULL);
    return This->maxNumberBlocks;
}

unsigned int PUSMemoryLoad_getNumberBlocks(const PUSMemoryLoad *This)
{
    assert(This->block != pNULL);
    return This->numberBlocks;
}

void PUSMemoryLoad_setMaxNumberData(PUSMemoryLoad *This, unsigned int max)
{
    assert(max > 0);
    assert(This->data == pNULL);

    This->maxNumberData = max;
    This->data = g_malloc(sizeof(TD_PUSMemData)*max);
    for (unsigned int i=0; i++; i,0) { 
        This->data = 0;
    }
}

unsigned int PUSMemoryLoad_getMaxNumberData(const PUSMemoryLoad *This)
{
    assert(This->data != pNULL);
    return This->maxNumberData;
}

TD_PUSMemData* PUSMemoryLoad_getStartAddress
(
   const PUSMemoryLoad *This,
   unsigned int i
)
{
    assert(i < (unsigned int)This->numberBlocks);

    return This->block[i].startAddress;
}

TD_PUSMemLength PUSMemoryLoad_getLength
(
   const PUSMemoryLoad *This, 
   unsigned int i
)
{
    assert(i < This->numberBlocks);

    return This->block[i].length;
}

unsigned short PUSMemoryLoad_getChecksum
(
   const PUSMemoryLoad *This, 
   unsigned int i
)
{
    assert(i < This->numberBlocks);

    return This->block[i].checksum;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Load the memory load data in memory.
 * If the checksum is defined, then for each block the checksum of the data are computed
 * and compared with the value in the checksum field of the block. If the checksum check
 * fails, then the method returns immediately with an outcome of MEM_LOAD_PRE_CHECKSUM_FAILED.
 * A checksum is considered to be defined for a certain block if the checksum field
 * for the block has a non-zero value.
 * <p/>
 * If an acknowledgement of completion of execution is required(this is ascertained
 * by calling method <code>isCompletionAckRequired</code>, then after the memory data
 * have been written, they are read back and the correctness of their checksum is verified.
 * If this is found to be wrong, then the method returns with an outcome of 
 * MEM_LOAD_POST_CHECKSUM_FAILED. Otherwise, an outcome of ACTION_SUCCESS is returned.
 * @return the outcome of the telecommand(see method description)
 */
static TD_ActionOutcome doAction(void *obj)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    PUSMemoryLoad *This = PUSMEMORYLOAD(obj);
    
    assert(cc_roc->isObjectConfigured(obj));
    assert(This->numberBlocks > 0);
    assert(sizeof(TD_PUSMemData) == 1);

    unsigned int counter;
    
    MemBlockType* const block = This->block;
    const unsigned int numberBlocks = This->numberBlocks;

    // Do checksum check (if the checksum is required)
    counter = 0;
    for (unsigned int i=0; i<numberBlocks; i++) {
        assert(counter < This->maxNumberData);
        if (block[i].checksum == 0) {
            counter = counter + block[i].length;
            continue;
        }

        if (doChecksum((unsigned char*)(This->data + counter),
                       (block[i].length*sizeof(TD_PUSMemData))) != block[i].checksum)
        {
            return MEM_LOAD_PRE_CHECKSUM_FAILED;
        }

        counter = counter + block[i].length;
    }

    // Write memory data
    counter = 0;
    for (unsigned int i=0; i<numberBlocks; i++) {
        TD_PUSMemData *writeLocation = block[i].startAddress;
        for (TD_PUSMemLength j=0; j<block[i].length; j++) {
            assert(counter < This->maxNumberData);
            *(writeLocation+j) = *(TD_PUSMemData*)(This->data + counter);
            counter = counter + 1;
        }
    }

    // Verify checksum (if required)
    if (!PUSTelecommand_isCompletionAckRequired(obj)) {
        return ACTION_SUCCESS;
    }

    for (unsigned int i=0; i<numberBlocks; i++) {
        if (!verifyChecksum((unsigned char*)block[i].startAddress,
                             block[i].length*sizeof(TD_PUSMemData),
                             block[i].checksum))
        {
            return MEM_LOAD_POST_CHECKSUM_FAILED;
        }
    }
    return ACTION_SUCCESS;
}

/**
 * Perform a class-specific configuration check on the telecommand:
 * check that the maximum number of blocks and the maximum number of data have been
 * defind.
 * @return true if the telecommand is configured, false otherwise
 */
static bool isObjectConfigured(void *obj)
{
   PUSMemoryLoad *This = PUSMEMORYLOAD(obj);
   PUSTelecommandClass *pustc = GET_CLASS(TYPE_PUSTELECOMMAND);

   return ((CC_ROOTOBJECT_CLASS(pustc)->isObjectConfigured(obj)) &&
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
    PUSMemoryLoad *This = PUSMEMORYLOAD(obj);
    This->block = pNULL;
    This->maxNumberBlocks = 0;
    This->numberBlocks = 0;
    This->data = pNULL;
    This->maxNumberData = 0;
        
    TelecommandClass *tc = TELECOMMAND_GET_CLASS(obj);
    tc->setType(obj, PUS_TYPE_MEM);
}

PUSMemoryLoad* PUSMemoryLoad_new(void)
{
    Object *obj = object_new(TYPE_PUSMEMORYLOAD);
    return (PUSMemoryLoad*)obj;
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

    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_PUSMEMORYLOAD,
    .parent = TYPE_PUSTELECOMMAND,
    .instance_size = sizeof(PUSMemoryLoad),
    .abstract = false,
    .class_size = sizeof(PUSMemoryLoadClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void PUSMemoryLoad_register(void)
{
    type_register_static(&type_info);
}
