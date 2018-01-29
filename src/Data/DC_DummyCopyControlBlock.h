//
//
// DC_DummyCopyControlBlock.cpp
//
//
// Change Record:


#ifndef DC_DUMMYCOPYCONTROLBLOCK_H
#define DC_DUMMYCOPYCONTROLBLOCK_H


#include "CopyControlBlock.h"
#include "../Qom/object.h"


/*
 * Dummy control block useful for testing purposes.
 * This control block has three inputs, two outputs, one state and
 * two parameters.
 * The <i>state propagation function</i> is as follows:<PRE>
 *      x[0](k+1) = p[0]*x[0](k) + u[0](k) + u[1](k) + u[2](k);</PRE>
 * The <i>output update function</i> is as follows:<PRE>
 *      y[0](k) = x[0](k);
 *      y[1](k) = p[1]*x[0](k);</PRE>
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @author Roberto Totaro
 * @version 1.2
 */
#define TYPE_DC_DUMMYCOPYCONTROLBLOCK "dc_dummycopycontrolblock"

void DC_DummyCopyControlBlock_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_DummyCopyControlBlock {
    CopyControlBlock parent;
};


struct DC_DummyCopyControlBlockClass {
    CopyControlBlockClass parent_class;
};


#define DC_DUMMYCOPYCONTROLBLOCK_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_DummyCopyControlBlockClass,\
                                            obj, TYPE_DC_DUMMYCOPYCONTROLBLOCK)

#define DC_DUMMYCOPYCONTROLBLOCK_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_DummyCopyControlBlockClass,\
                                          klass, TYPE_DC_DUMMYCOPYCONTROLBLOCK)

#define DC_DUMMYCOPYCONTROLBLOCK(obj) \
        OBJECT_CHECK(DC_DummyCopyControlBlock, obj, TYPE_DC_DUMMYCOPYCONTROLBLOCK)


DC_DummyCopyControlBlock* DC_DummyCopyControlBlock_new(void);

#endif
