//
//
// DC_DummyPointerControlBlock.h
//
//
// Change Record:


#ifndef DC_DUMMYPOINTERCONTROLBLOCK_H
#define DC_DUMMYPOINTERCONTROLBLOCK_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "PointerControlBlock.h"
#include "../Qom/object.h"


/*
 * Dummy pointer control block useful for testing purposes.
 * This control block has three inputs, two outputs, one state and
 * two parameters.
 * The <i>state propagation function</i> is as follows:<PRE>
 *      x[0](k+1) = p[0]*x[0](k) + u[0](k) + u[1](k) + u[2](k);</PRE>
 * The <i>output update function</i> is as follows:<PRE>
 *      y[0](k) = x[0](k);
 *      y[1](k) = p[1]*x[0](k);</PRE>
 * @author Roberto Totaro
 * @version 1.1
 */
#define TYPE_DC_DUMMYPOINTERCONTROLBLOCK "dc_dummypointercontrolblock"

void DC_DummyPointerControlBlock_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_DummyPointerControlBlock {
    PointerControlBlock parent;
};


struct DC_DummyPointerControlBlockClass {
    PointerControlBlockClass parent_class;
};


#define DC_DUMMYPOINTERCONTROLBLOCK_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_DummyPointerControlBlockClass,\
                                          obj, TYPE_DC_DUMMYPOINTERCONTROLBLOCK)

#define DC_DUMMYPOINTERCONTROLBLOCK_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_DummyPointerControlBlockClass,\
                                        klass, TYPE_DC_DUMMYPOINTERCONTROLBLOCK)

#define DC_DUMMYPOINTERCONTROLBLOCK(obj) \
        OBJECT_CHECK(DC_DummyPointerControlBlock,\
                                          obj, TYPE_DC_DUMMYPOINTERCONTROLBLOCK)


DC_DummyPointerControlBlock* DC_DummyPointerControlBlock_new(void);

#endif
