//
//
// DC_DummyDataItemControlBlock.h
//
//
// Change Record:


#ifndef DC_DUMMYDATAITEMCONTROLBLOCK_H
#define DC_DUMMYDATAITEMCONTROLBLOCK_H


#include "DataItemControlBlock.h"
#include "../Qom/object.h"


/*
 * Dummy data item control block useful for testing purposes.
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
#define TYPE_DC_DUMMYDATAITEMCONTROLBLOCK "dc_dummydataitemcontrolblock"

void DC_DummyDataItemControlBlock_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_DummyDataItemControlBlock {
    DataItemControlBlock parent;
};


struct DC_DummyDataItemControlBlockClass {
    DataItemControlBlockClass parent_class;
};


#define DC_DUMMYDATAITEMCONTROLBLOCK_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_DummyDataItemControlBlockClass,\
                                        obj, TYPE_DC_DUMMYDATAITEMCONTROLBLOCK)

#define DC_DUMMYDATAITEMCONTROLBLOCK_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_DummyDataItemControlBlockClass,\
                                      klass, TYPE_DC_DUMMYDATAITEMCONTROLBLOCK)

#define DC_DUMMYDATAITEMCONTROLBLOCK(obj) \
        OBJECT_CHECK(DC_DummyDataItemControlBlock,\
                                        obj, TYPE_DC_DUMMYDATAITEMCONTROLBLOCK)


DC_DummyDataItemControlBlock* DC_DummyDataItemControlBlock_new(void);

#endif
