//
//
// DC_PUSMemoryLoadAbsolute.h
//


#ifndef DC_PUSMEMORYLOADABSOLUTE_H
#define DC_PUSMEMORYLOADABSOLUTE_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "PUSMemoryLoad.h"
#include "../Qom/object.h"


/*
 * Class implementing the PUS service to load memory using absolute addresses(PUS 
 * service type 6, subtype 2).
 * This class adds to its superclass the implementation of the 
 * <i>raw data load mechanism</i>. Since the amount of data to be loaded will often
 * be large, the fast version of this service is implemented. 
 * The data load mechanism interprets the application data in the telecommand
 * packet and uses them to configure the internal data structure defined by the
 * super class. The interpretation of the application data can result in the
 * detection of inconsistencies or invalid data. These are reported by setting the
 * <i>validity check code</i>.
 * <p>
 * The PUS leaves some leeway in the definition of the structure of the application
 * data for memory load telecommands. This implementation makes the following 
 * assumptions: <ul>
 * <li>The memory ID field is always present and its type is <code>TD_PUSMemId</code>.</li>
 * <li>The number of blocks field is an integer of type <code>TD_PUSNumberMemBlocks</code>.</li>
 * </ul>
 * The implementation of this class assumes type <code>TD_PUSMemId</code> to have size 1
 * (i.e. to be a <code>char</code> or an <code>unsigned char</code>).
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_PUSMEMORYLOADABSOLUTE "dc_pusmemoryloadabsolute"

void DC_PUSMemoryLoadAbsolute_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_PUSMemoryLoadAbsolute {
    PUSMemoryLoad parent;

    TD_PUSMemId memId;
};


struct DC_PUSMemoryLoadAbsoluteClass {
    PUSMemoryLoadClass parent_class;
};


#define DC_PUSMEMORYLOADABSOLUTE_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_PUSMemoryLoadAbsoluteClass, \
                                           obj, TYPE_DC_PUSMEMORYLOADABSOLUTE)

#define DC_PUSMEMORYLOADABSOLUTE_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_PUSMemoryLoadAbsoluteClass, \
                                         klass, TYPE_DC_PUSMEMORYLOADABSOLUTE)

#define DC_PUSMEMORYLOADABSOLUTE(obj) \
        OBJECT_CHECK(DC_PUSMemoryLoadAbsolute, \
                                           obj, TYPE_DC_PUSMEMORYLOADABSOLUTE)


DC_PUSMemoryLoadAbsolute* DC_PUSMemoryLoadAbsolute_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Get the memory block ID.
 * @return the maximum number of blocks
 */
TD_PUSMemId DC_PUSMemoryLoadAbsolute_getMemoryBlockId
(
    const DC_PUSMemoryLoadAbsolute *This
);


#endif
