//
//
// DC_PUSMemoryDumpOffset.h
//


#ifndef DC_PUSMEMORYDUMPOFFSET_H
#define DC_PUSMEMORYDUMPOFFSET_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Telemetry/PUSMemoryDump.h"
#include "../Qom/object.h"


/*
 * PUS telemetry packet implementing the memory dump service using base plus offset 
 * (type 6, subtype 4).
 * This class adds to its superclass the modelling of the base address and the 
 * implementation of the <i>data update service</i>.
 * @todo construct a test case for this class.
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_PUSMEMORYDUMPOFFSET "dc_pusmemorydumpoffset"

void DC_PUSMemoryDumpOffset_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_PUSMemoryDumpOffset {
    PUSMemoryDump parent;

    TD_PUSMemData *base;
};


struct DC_PUSMemoryDumpOffsetClass {
    PUSMemoryDumpClass parent_class;
};


#define DC_PUSMEMORYDUMPOFFSET_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_PUSMemoryDumpOffsetClass,\
                                             obj, TYPE_DC_PUSMEMORYDUMPOFFSET)

#define DC_PUSMEMORYDUMPOFFSET_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_PUSMemoryDumpOffsetClass,\
                                           klass, TYPE_DC_PUSMEMORYDUMPOFFSET)

#define DC_PUSMEMORYDUMPOFFSET(obj) \
        OBJECT_CHECK(DC_PUSMemoryDumpOffset, obj, TYPE_DC_PUSMEMORYDUMPOFFSET)


DC_PUSMemoryDumpOffset* DC_PUSMemoryDumpOffset_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the base address for the dump packet.
 * Only values greater than zero are legal.
 * @see #update
 * @param base the base address
 */
void DC_PUSMemoryDumpOffset_setBaseAddress(DC_PUSMemoryDumpOffset *This, TD_PUSMemData *base);

/**
 * Get the base address for the dump packet.
 * @see #setBaseAddress
 * @return the base address
 */
TD_PUSMemData* DC_PUSMemoryDumpOffset_getBaseAddress(DC_PUSMemoryDumpOffset *This);


#endif
