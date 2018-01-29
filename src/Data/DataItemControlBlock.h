//
//
// DataItemControlBlock.h
//
//
// Change Record:


#ifndef DATAITEMCONTROLBLOCK_H
#define DATAITEMCONTROLBLOCK_H


#include "ControlBlock.h"
#include "../Qom/object.h"


/*
 * Base class for data item control blocks. 
 * A <i>data item control block</i> is a control block that takes its inputs from and writes
 * its outputs to <i>data items</i> (instances of class <code>DC_DataItem</code>). The data
 * items are loaded as part of the control block configuration. This class therefore adds 
 * the following attributes to its <code>ControlBlock</code> base class:<ul>
 * <li>The <i>input data items</i>: the data items from which the input values are read.</li>
 * <li>The <i>output data items</i>: the data items to which the output values are written.</li>
 * </ul>
 * This class adds services to set up the link between the block inputs and outputs and the
 * data items from which the inputs are read and to which the outputs are written.
 * @see DC_DataItem
 * @author Alessandro Pasetti, Roberto Totaro
 * @version 1.0
 * @ingroup Data
 */
#define TYPE_DATAITEMCONTROLBLOCK "dataitemcontrolblock"

void DataItemControlBlock_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DataItemControlBlock {
    ControlBlock parent;

    /**
     * Array of input data items.
     * Element pDIU[i] holds the pointer to the data item that provides the i-th input variable.
     * The integer i must lie in the 
     * interval [0,N-1] where N is the number of inputs.
     * @see #setInputLink
     */
    DC_DataItem **pDIU;
    /**
     * Array of output data items.
     * Element pDIY[i] holds the pointer to the data item to which the i-th output variable is written.
     * The integer i must lie in the 
     * interval [0,N-1] where N is the number of outputs.
     * @see #setOutputLink
     */
    DC_DataItem **pDIY;
};


struct DataItemControlBlockClass {
    ControlBlockClass parent_class;
};


#define DATAITEMCONTROLBLOCK_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DataItemControlBlockClass, obj, TYPE_DATAITEMCONTROLBLOCK)

#define DATAITEMCONTROLBLOCK_CLASS(klass) \
        OBJECT_CLASS_CHECK(DataItemControlBlockClass, klass, TYPE_DATAITEMCONTROLBLOCK)

#define DATAITEMCONTROLBLOCK(obj) \
        OBJECT_CHECK(DataItemControlBlock, obj, TYPE_DATAITEMCONTROLBLOCK)


DataItemControlBlock* DataItemControlBlock_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Load the data item for the i-th input. The argument i must lie in the 
 * interval [0, N-1] where N is the number of inputs.
 * An illegal value for argument i triggers the generation of an event report 
 * EVT_ILLEGAL_CB. 
 * @param i the index of the input 
 * @param pDataItem the data item 
 */
void DataItemControlBlock_setInputLink
(
    DataItemControlBlock *This, 
    unsigned int i,
    DC_DataItem* pDataItem
);

/**
 * Load the data item for the i-th output. The argument i must lie in the 
 * interval [0, N-1] where N is the number of outputs.
 * An illegal value for argument i triggers the generation of an event report 
 * EVT_ILLEGAL_CB. 
 * @param i the index of the output 
 * @param pDataItem the data item 
 */
void DataItemControlBlock_setOutputLink
(
    DataItemControlBlock *This, 
    unsigned int i, 
    DC_DataItem* pDataItem
);


#endif
