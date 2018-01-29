//
//
// DC_DummyDataPoolControlBlock.h
//
//
// Change Record:


#ifndef DC_DUMMYDATAPOOLCONTROLBLOCK_H
#define DC_DUMMYDATAPOOLCONTROLBLOCK_H


#include "DataPoolControlBlock.h"
#include "../Qom/object.h"


/*
 * Dummy data pool control block useful for testing purposes.
 * This control block has three inputs, two outputs, one state and
 * two parameters.
 * The <i>state propagation function</i> is as follows:<PRE>
 *      x[0](k+1) = p[0]*x[0](k) + u[0](k) + u[1](k) + u[2](k);</PRE>
 * The <i>output update function</i> is as follows:<PRE>
 *      y[0](k) = x[0](k);
 *      y[1](k) = p[1]*x[0](k);</PRE>
 * @author Roberto Totaro
 * @version 1.0
 */
#define TYPE_DC_DUMMYDATAPOOLCONTROLBLOCK "dc_dummydatapoolcontrolblock"

void DC_DummyDataPoolControlBlock_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_DummyDataPoolControlBlock {
    DataPoolControlBlock parent;
};


struct DC_DummyDataPoolControlBlockClass {
    DataPoolControlBlockClass parent_class;
};


#define DC_DUMMYDATAPOOLCONTROLBLOCK_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_DummyDataPoolControlBlockClass,\
                                         obj, TYPE_DC_DUMMYDATAPOOLCONTROLBLOCK)

#define DC_DUMMYDATAPOOLCONTROLBLOCK_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_DummyDataPoolControlBlockClass,\
                                       klass, TYPE_DC_DUMMYDATAPOOLCONTROLBLOCK)

#define DC_DUMMYDATAPOOLCONTROLBLOCK(obj) \
        OBJECT_CHECK(DC_DummyDataPoolControlBlock,\
                                         obj, TYPE_DC_DUMMYDATAPOOLCONTROLBLOCK)


DC_DummyDataPoolControlBlock* DC_DummyDataPoolControlBlock_new(void);

#endif
