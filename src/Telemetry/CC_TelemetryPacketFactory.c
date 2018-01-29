//
//
// CC_TelemetryPacketFactory.c
//
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Telemetry/DC_DummyPUSTelemetryPacket.h"
#include "../Telemetry/DC_PUSDataReportingPacket.h"
#include "../Telemetry/DC_PUSMemoryDumpAbsolute.h"
#include "../Telemetry/DC_PUSMemoryDumpOffset.h"
#include "../Telemetry/DC_PUSTcVerificationPacket.h"
#include "../Base/CC_RootObject.h"
#include "CC_TelemetryPacketFactory.h"
#include <string.h>




///////////////////////////////////////////////////////////////////////////////
//
//                            class data
//
///////////////////////////////////////////////////////////////////////////////

static CC_TelemetryPacketFactory *pInstance;     



///////////////////////////////////////////////////////////////////////////////
//
//                            class  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

CC_TelemetryPacketFactory* CC_TelemetryPacketFactory_getInstance(void)
{
    if (pInstance == pNULL) {
        pInstance = CC_TelemetryPacketFactory_new();
    }

    return pInstance;
}



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void CC_TelemetryPacketFactory_setTelemetryPacket
(
    CC_TelemetryPacketFactory *This, 
    unsigned int i,
    TelemetryPacket *pItem
)
{
    assert(pItem != pNULL);

    const char *typeName = object_get_typename((Object*)pItem);
    
    if (strcmp(typeName, TYPE_DC_DUMMYPUSTELEMETRYPACKET) == 0) {
       setDummyPUSTelemetryPacket(This, i, (void*)pItem);
    } else if (strcmp(typeName, TYPE_DC_PUSDATAREPORTINGPACKET) == 0) {
       setPUSDataReportingPacket(This, i, (void*)pItem);
    } else if (strcmp(typeName, TYPE_DC_PUSMEMORYDUMPABSOLUTE) == 0) {
       setPUSMemoryDumpAbsolute(This, i, (void*)pItem);
    } else if (strcmp(typeName, TYPE_DC_PUSMEMORYDUMPOFFSET) == 0) {
       setPUSMemoryDumpOffset(This, i, (void*)pItem);
    } else if (strcmp(typeName, TYPE_DC_PUSTCVERIFICATIONPACKET) == 0) {
       setPUSTcVerificationPacket(This, i, (void*)pItem);
    } else {
       // Unknown TelemetryPacket type
       assert(false);
    }
}

static void setDummyPUSTelemetryPacket
(
    CC_TelemetryPacketFactory *This, 
    unsigned int i,
    DC_DummyPUSTelemetryPacket *pItem
)
{
    assert(i < This->sizeDummyPUSTelemetryPacket);
    assert(pItem != pNULL);
    This->poolDummyPUSTelemetryPacket[i] = pItem;
    TelemetryPacket_setInUse((TelemetryPacket*)This->poolDummyPUSTelemetryPacket[i],  
                              false);
}

unsigned int CC_TelemetryPacketFactory_getNumberDummyPUSTelemetryPacket
(
    CC_TelemetryPacketFactory *This
)
{
    unsigned int counter = 0;
    DC_DummyPUSTelemetryPacket** const pool = This->poolDummyPUSTelemetryPacket;
    for (unsigned int i=0; i<This->sizeDummyPUSTelemetryPacket; i++) {
        if (TelemetryPacket_isInUse((TelemetryPacket*)pool[i])) {
            counter++;
        }
    }

    return counter;
}

unsigned int CC_TelemetryPacketFactory_getCapacityDummyPUSTelemetryPacket
(
    CC_TelemetryPacketFactory *This
)
{
    return This->sizeDummyPUSTelemetryPacket;
}

DC_DummyPUSTelemetryPacket* CC_TelemetryPacketFactory_allocateDummyPUSTelemetryPacket
(
    CC_TelemetryPacketFactory *This
)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(This);
    assert(cc_roc->isObjectConfigured(This));

    DC_DummyPUSTelemetryPacket** const pool = This->poolDummyPUSTelemetryPacket;
    for (unsigned int i=0; i<This->sizeDummyPUSTelemetryPacket; i++) {
        if (!TelemetryPacket_isInUse((TelemetryPacket*)pool[i])) {
           TelemetryPacket_setInUse((TelemetryPacket*)pool[i], true);
           return This->poolDummyPUSTelemetryPacket[i];
        }
    }

    return pNULL;
}

bool CC_TelemetryPacketFactory_isFreeDummyPUSTelemetryPacket
(
    CC_TelemetryPacketFactory *This
)
{
    DC_DummyPUSTelemetryPacket** const pool = This->poolDummyPUSTelemetryPacket;
    for (unsigned int i=0; i<This->sizeDummyPUSTelemetryPacket; i++) {
        if (!TelemetryPacket_isInUse((TelemetryPacket*)pool[i])) {
           return true;
        }
    }

    return false;
}

static void setPUSDataReportingPacket
(
    CC_TelemetryPacketFactory *This, 
    unsigned int i,
    DC_PUSDataReportingPacket *pItem
)
{
    assert(i < This->sizePUSDataReportingPacket);
    assert(pItem != pNULL);
    This->poolPUSDataReportingPacket[i] = pItem;
    TelemetryPacket_setInUse((TelemetryPacket*)This->poolPUSDataReportingPacket[i],
                              false);
}

unsigned int CC_TelemetryPacketFactory_getNumberPUSDataReportingPacket
(
    CC_TelemetryPacketFactory *This
)
{
    unsigned int counter = 0;
    DC_PUSDataReportingPacket** const pool = This->poolPUSDataReportingPacket;
    for (unsigned int i=0; i<This->sizePUSDataReportingPacket; i++) {
        if (TelemetryPacket_isInUse((TelemetryPacket*)pool[i])) {
            counter++;
        }
    }

    return counter;
}

unsigned int CC_TelemetryPacketFactory_getCapacityPUSDataReportingPacket
(
    CC_TelemetryPacketFactory *This
)
{
    return This->sizePUSDataReportingPacket;
}

DC_PUSDataReportingPacket* CC_TelemetryPacketFactory_allocatePUSDataReportingPacket
(
    CC_TelemetryPacketFactory *This, 
    unsigned int DefinitionBufferSize, 
    unsigned int ValueBufferSize, 
    unsigned int MaxNumberFA
)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(This);
    assert(cc_roc->isObjectConfigured(This));

    unsigned int defBufferSize; 
    unsigned int valBufferSize;
    unsigned int maxNumFA;
    DC_PUSDataReportingPacket** const pool = This->poolPUSDataReportingPacket;
    for (unsigned int i=0; i<This->sizePUSDataReportingPacket; i++) {
        defBufferSize = DC_PUSDataReportingPacket_getDefinitionBufferSize(pool[i]); 
        valBufferSize = DC_PUSDataReportingPacket_getValueBufferSize(pool[i]);
        maxNumFA = DC_PUSDataReportingPacket_getMaxNumberFA(pool[i]);

        if ((defBufferSize >= DefinitionBufferSize) &&
            (valBufferSize >= ValueBufferSize) &&
            (maxNumFA >= MaxNumberFA) &&
            (!TelemetryPacket_isInUse((TelemetryPacket*)pool[i]))) 
        {
            TelemetryPacket_setInUse((TelemetryPacket*)pool[i], true);
            return pool[i];
        }
    }

    return pNULL;
}

bool CC_TelemetryPacketFactory_isFreePUSDataReportingPacket
(
    CC_TelemetryPacketFactory *This, 
    unsigned int DefinitionBufferSize, 
    unsigned int ValueBufferSize, 
    unsigned int MaxNumberFA
)
{
    unsigned int defBufferSize; 
    unsigned int valBufferSize;
    unsigned int maxNumFA;
    DC_PUSDataReportingPacket** const pool = This->poolPUSDataReportingPacket;
    for (unsigned int i=0; i<This->sizePUSDataReportingPacket; i++) {
        defBufferSize = DC_PUSDataReportingPacket_getDefinitionBufferSize(pool[i]); 
        valBufferSize = DC_PUSDataReportingPacket_getValueBufferSize(pool[i]);
        maxNumFA = DC_PUSDataReportingPacket_getMaxNumberFA(pool[i]);

        if ((defBufferSize >= DefinitionBufferSize) &&
            (valBufferSize >= ValueBufferSize) &&
            (MaxNumberFA >= MaxNumberFA) &&
            (!TelemetryPacket_isInUse((TelemetryPacket*)pool[i]))) 
        {
           return true;
        }
    }

    return false;
}

DC_PUSDataReportingPacket* CC_TelemetryPacketFactory_getPUSDataReportingPacket
(
    CC_TelemetryPacketFactory *This, 
    TD_SID sid
)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(This);
    assert(cc_roc->isObjectConfigured(This));
    assert(sid > 0);

    DC_PUSDataReportingPacket** const pool = This->poolPUSDataReportingPacket;
    for (unsigned int i=0; i<This->sizePUSDataReportingPacket; i++) {
        if ((DC_PUSDataReportingPacket_getSID(pool[i]) == sid ) &&
            (TelemetryPacket_isInUse((TelemetryPacket*)pool[i]))) {
            return pool[i];
        }
    }

    return pNULL;
}

static void setPUSMemoryDumpAbsolute
(
    CC_TelemetryPacketFactory *This,
    unsigned int i,
    DC_PUSMemoryDumpAbsolute *pItem
)
{
    assert(i < This->sizePUSMemoryDumpAbsolute);
    assert(pItem != pNULL);
    This->poolPUSMemoryDumpAbsolute[i] = pItem;
    TelemetryPacket_setInUse((TelemetryPacket*)This->poolPUSMemoryDumpAbsolute[i],
                              false);
}

unsigned int CC_TelemetryPacketFactory_getNumberPUSMemoryDumpAbsolute
(
    CC_TelemetryPacketFactory *This
)
{
    unsigned int counter = 0;
    DC_PUSMemoryDumpAbsolute** const pool = This->poolPUSMemoryDumpAbsolute;
    for (unsigned int i=0; i<This->sizePUSMemoryDumpAbsolute; i++) {
        if (TelemetryPacket_isInUse((TelemetryPacket*)pool[i])) {
            counter++;
        }
    }

    return counter;
}

unsigned int CC_TelemetryPacketFactory_getCapacityPUSMemoryDumpAbsolute
(
    CC_TelemetryPacketFactory *This
)
{
    return This->sizePUSMemoryDumpAbsolute;
}

DC_PUSMemoryDumpAbsolute* CC_TelemetryPacketFactory_allocatePUSMemoryDumpAbsolute
(
    CC_TelemetryPacketFactory *This,
    unsigned int MaxNumberBlocks, 
    unsigned int DumpBufferSize
)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(This);
    assert(cc_roc->isObjectConfigured(This));
    
    unsigned int maxNumBlks; 
    unsigned int dumpBufSize;
    DC_PUSMemoryDumpAbsolute** const pool = This->poolPUSMemoryDumpAbsolute;
    for (unsigned int i=0; i<This->sizePUSMemoryDumpAbsolute; i++) {
        maxNumBlks = PUSMemoryDump_getMaxNumberBlocks((PUSMemoryDump*)pool[i]);
        dumpBufSize = PUSMemoryDump_getDumpBufferSize((PUSMemoryDump*)pool[i]);

        if ((maxNumBlks >= MaxNumberBlocks) &&
            (dumpBufSize >= DumpBufferSize) &&
            (!TelemetryPacket_isInUse((TelemetryPacket*)pool[i])))
        {
           TelemetryPacket_setInUse((TelemetryPacket*)pool[i], true);
           return pool[i];
        }
    }

    return pNULL;
}

bool CC_TelemetryPacketFactory_isFreePUSMemoryDumpAbsolute
(
   CC_TelemetryPacketFactory *This,
   unsigned int MaxNumberBlocks, 
   unsigned int DumpBufferSize
)
{
    unsigned int maxNumBlks; 
    unsigned int dumpBufSize;
    DC_PUSMemoryDumpAbsolute** const pool = This->poolPUSMemoryDumpAbsolute;
    for (unsigned int i=0; i<This->sizePUSMemoryDumpAbsolute; i++) {
        maxNumBlks = PUSMemoryDump_getMaxNumberBlocks((PUSMemoryDump*)pool[i]);
        dumpBufSize = PUSMemoryDump_getDumpBufferSize((PUSMemoryDump*)pool[i]);

        if ((maxNumBlks >= MaxNumberBlocks) &&
            (dumpBufSize >= DumpBufferSize) &&
            (!TelemetryPacket_isInUse((TelemetryPacket*)pool[i])))
        {
           return true;
        }
    }

    return false;
}

static void setPUSMemoryDumpOffset
(
    CC_TelemetryPacketFactory *This, 
    unsigned int i,
    DC_PUSMemoryDumpOffset *pItem
)
{
    assert(i < This->sizePUSMemoryDumpOffset);
    assert(pItem != pNULL);
    This->poolPUSMemoryDumpOffset[i] = pItem;
    TelemetryPacket_setInUse((TelemetryPacket*)This->poolPUSMemoryDumpOffset[i], 
                              false);
}

unsigned int CC_TelemetryPacketFactory_getNumberPUSMemoryDumpOffset
(
    CC_TelemetryPacketFactory *This
)
{
    unsigned int counter = 0;
    DC_PUSMemoryDumpOffset** const  pool = This->poolPUSMemoryDumpOffset;
    for (unsigned int i=0; i<This->sizePUSMemoryDumpOffset; i++) {
        if (TelemetryPacket_isInUse((TelemetryPacket*)pool[i])) {
            counter++;
        }
    }

    return counter;
}

unsigned int CC_TelemetryPacketFactory_getCapacityPUSMemoryDumpOffset
(
    CC_TelemetryPacketFactory *This
)
{
    return This->sizePUSMemoryDumpOffset;
}

DC_PUSMemoryDumpOffset* CC_TelemetryPacketFactory_allocatePUSMemoryDumpOffset
(
   CC_TelemetryPacketFactory *This,
   unsigned int MaxNumberBlocks, 
   unsigned int DumpBufferSize
)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(This);
    assert(cc_roc->isObjectConfigured(This));

    unsigned int maxNumBlks; 
    unsigned int dumpBufSize;
    DC_PUSMemoryDumpOffset** const  pool = This->poolPUSMemoryDumpOffset;
    for (unsigned int i=0; i<This->sizePUSMemoryDumpOffset; i++) 
    {
        maxNumBlks = PUSMemoryDump_getMaxNumberBlocks((PUSMemoryDump*)pool[i]);
        dumpBufSize = PUSMemoryDump_getDumpBufferSize((PUSMemoryDump*)pool[i]);

        if ((maxNumBlks >= MaxNumberBlocks) &&
            (dumpBufSize >= DumpBufferSize) &&
            (!TelemetryPacket_isInUse((TelemetryPacket*)pool[i])))
        {
           TelemetryPacket_setInUse((TelemetryPacket*)pool[i], true);
           return pool[i];
        }
    }

    return pNULL;
}

bool CC_TelemetryPacketFactory_isFreePUSMemoryDumpOffset
(
    CC_TelemetryPacketFactory *This, 
    unsigned int MaxNumberBlocks, 
    unsigned int DumpBufferSize
)
{
    unsigned int maxNumBlks; 
    unsigned int dumpBufSize;
    DC_PUSMemoryDumpOffset** const  pool = This->poolPUSMemoryDumpOffset;
    for (unsigned int i=0; i<This->sizePUSMemoryDumpOffset; i++)
    {
        maxNumBlks = PUSMemoryDump_getMaxNumberBlocks((PUSMemoryDump*)pool[i]);
        dumpBufSize = PUSMemoryDump_getDumpBufferSize((PUSMemoryDump*)pool[i]);

        if ((maxNumBlks >= MaxNumberBlocks) &&
            (dumpBufSize >= DumpBufferSize) &&
            (!TelemetryPacket_isInUse((TelemetryPacket*)pool[i])))
        {
           return true;
        }
    }

    return false;
}

static void setPUSTcVerificationPacket(CC_TelemetryPacketFactory *This, 
                                       unsigned int i,
                                       DC_PUSTcVerificationPacket *pItem)
{
    assert(i < This->sizePUSTcVerificationPacket);
    assert(pItem != pNULL);
    This->poolPUSTcVerificationPacket[i] = pItem;
    TelemetryPacket_setInUse((TelemetryPacket*)This->poolPUSTcVerificationPacket[i],
                              false);
}

unsigned int CC_TelemetryPacketFactory_getNumberPUSTcVerificationPacket
(
    CC_TelemetryPacketFactory *This
)
{
    unsigned int counter = 0;
    DC_PUSTcVerificationPacket** const pool = This->poolPUSTcVerificationPacket;
    for (unsigned int i=0; i<This->sizePUSTcVerificationPacket; i++) {
       if (TelemetryPacket_isInUse((TelemetryPacket*)pool[i])) {
           counter++;
       }
    }

    return counter;
}

unsigned int CC_TelemetryPacketFactory_getCapacityPUSTcVerificationPacket
(
    CC_TelemetryPacketFactory *This
)
{
    return This->sizePUSTcVerificationPacket;
}

DC_PUSTcVerificationPacket* CC_TelemetryPacketFactory_allocatePUSTcVerificationPacket
(
    CC_TelemetryPacketFactory *This
)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(This);
    assert(cc_roc->isObjectConfigured(This));

    DC_PUSTcVerificationPacket** const pool = This->poolPUSTcVerificationPacket;
    for (unsigned int i=0; i<This->sizePUSTcVerificationPacket; i++) {
       if (!TelemetryPacket_isInUse((TelemetryPacket*)pool[i])) {
          TelemetryPacket_setInUse((TelemetryPacket*)pool[i], true);
          return pool[i];
       }
    }

    return pNULL;
}

bool CC_TelemetryPacketFactory_isFreePUSTcVerificationPacket
(
    CC_TelemetryPacketFactory *This
)
{
    DC_PUSTcVerificationPacket** const pool = This->poolPUSTcVerificationPacket;
    for (unsigned int i=0; i<This->sizePUSTcVerificationPacket; i++) {
       if (!TelemetryPacket_isInUse((TelemetryPacket*)pool[i])) {
          return true;
       }

    }

    return false;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Check that all component instances required by the factory have been loaded.
 * @return true if the component is configured, false otherwise
 */
static bool isObjectConfigured(void *obj)
{
    CC_RootObjectClass *cc_roc = GET_CLASS(TYPE_CC_ROOTOBJECT);
    CC_TelemetryPacketFactory *This = CC_TELEMETRYPACKETFACTORY(obj);

    if (!cc_roc->isObjectConfigured(obj)) {
        return false;
    }
  
    if (This->poolDummyPUSTelemetryPacket == pNULL) {
        return false;
    }

    for (unsigned int i=0; i<This->sizeDummyPUSTelemetryPacket; i++) {
        if (This->poolDummyPUSTelemetryPacket[i] == pNULL) {
            return false;
        }
    }
     
    if (This->poolPUSDataReportingPacket == pNULL) {
        return false;
    }

    for (unsigned int i=0; i<This->sizePUSDataReportingPacket; i++) {
        if (This->poolPUSDataReportingPacket[i] == pNULL) {
            return false;
        }
    }
     
    if (This->poolPUSMemoryDumpAbsolute == pNULL) {
        return false;
    }

    for (unsigned int i=0; i<This->sizePUSMemoryDumpAbsolute; i++) {
        if (This->poolPUSMemoryDumpAbsolute[i] == pNULL) {
            return false;
        }
    }
     
    if (This->poolPUSMemoryDumpOffset == pNULL) {
        return false;
    }

    for (unsigned int i=0; i<This->sizePUSMemoryDumpOffset; i++) {
        if (This->poolPUSMemoryDumpOffset[i] == pNULL) {
            return false;
        }
    }
     
    if (This->poolPUSTcVerificationPacket == pNULL) {
        return false;
    }

    for (unsigned int i=0; i<This->sizePUSTcVerificationPacket; i++) {
        if (This->poolPUSTcVerificationPacket[i] == pNULL) {
            return false;
        }
    }
     
   return true;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    CC_TelemetryPacketFactory *This = CC_TELEMETRYPACKETFACTORY(obj);
    unsigned int size;

    // DC_DummyPUSTelemetryPacket*
    size = 2;
    This->poolDummyPUSTelemetryPacket = g_malloc(size*sizeof(void*));
    for (unsigned int i=0; i<size; i++) {
        This->poolDummyPUSTelemetryPacket[i] = pNULL;
    }
    This->sizeDummyPUSTelemetryPacket = size;
      
    // DC_PUSDataReportingPacket* 
    size = 2;
    This->poolPUSDataReportingPacket = g_malloc(size*sizeof(void*));
    for (unsigned int i=0; i<size; i++) {
        This->poolPUSDataReportingPacket[i] = pNULL;
    }
    This->sizePUSDataReportingPacket = size;
      
    // DC_PUSMemoryDumpAbsolute* 
    size = 1;
    This->poolPUSMemoryDumpAbsolute = g_malloc(size*sizeof(void*));
    for (unsigned int i=0; i<size; i++) {
        This->poolPUSMemoryDumpAbsolute[i] = pNULL;
    }
    This->sizePUSMemoryDumpAbsolute = size;

    // DC_PUSMemoryDumpOffset* 
    size = 1;
    This->poolPUSMemoryDumpOffset = g_malloc(size*sizeof(void*));
    for (unsigned int i=0; i<size; i++) {
        This->poolPUSMemoryDumpOffset[i] = pNULL;
    }
    This->sizePUSMemoryDumpOffset = size;
      
    // DC_PUSTcVerificationPacket* 
    size = 1;
    This->poolPUSTcVerificationPacket = g_malloc(size*sizeof(void*));
    for (unsigned int i=0; i<size; i++) {
        This->poolPUSTcVerificationPacket[i] = pNULL;
    }
    This->sizePUSTcVerificationPacket = size;


    CC_RootObject_setClassId((CC_RootObject*)obj, ID_TELECOMMANDFACTORY);
}

CC_TelemetryPacketFactory* CC_TelemetryPacketFactory_new(void)
{
    Object *obj = object_new(TYPE_CC_TELEMETRYPACKETFACTORY);
    return (CC_TelemetryPacketFactory*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_CC_TELEMETRYPACKETFACTORY,
    .parent = TYPE_CC_ROOTOBJECT,
    .instance_size = sizeof(CC_TelemetryPacketFactory),
    .abstract = false,
    .class_size = sizeof(CC_TelemetryPacketFactoryClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void CC_TelemetryPacketFactory_register(void)
{
    type_register_static(&type_info);
}
