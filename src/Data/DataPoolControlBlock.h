//
//
// DataPoolControlBlock.h
//
//
// Change Record:


#ifndef DATAPOOLCONTROLBLOCK_H
#define DATAPOOLCONTROLBLOCK_H


#include "ControlBlock.h"
#include "../Qom/object.h"


/*
 * Base class for data pool control blocks. 
 * A <i>data pool control block</i> is a control block that takes its inputs from locations
 * in the data pool and writes its outputs into locations in the data pool. The data pool
 * locations for the inputs and the outputs are defined as configuration parameters for the 
 * control block. This class therefore adds the following attributes to its
 * <code>ControlBlock</code> base class:<ul>
 * <li>The <i>input identifiers</i>: the identifiers of the data pool items in the
 * data pool from which the input values are read.</li>
 * <li>The <i>output identifiers</i>: the identifiers of the data pool items in the
 * data pool to which the output values are written.</li>
 * </ul>
 * This class adds services to set up the link between the block inputs and outputs and the
 * data pool locations from which the inputs are read and to which the outputs are written.
 * @see DataPool
 * @author Alessandro Pasetti, Roberto Totaro
 * @version 1.0
 * @ingroup Data
 */
#define TYPE_DATAPOOLCONTROLBLOCK "datapoolcontrolblock"

void DataPoolControlBlock_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DataPoolControlBlock {
    ControlBlock parent;

    /**
     * Array of input identifiers.
     * Element dpu[i] holds the identifier of the data pool item that provides the i-th input variable.
     * The integer i must lie in the 
     * interval [0,N-1] where N is the number of inputs.
     * @see #setInputLink
     */
    TD_DataPoolId *dpu;
    /**
     * Array of output identifiers.
     * Element dpy[i] holds the identifier of the data pool item that receives the i-th output variable.
     * The integer i must lie in the 
     * interval [0,N-1] where N is the number of outputs.
     * @see #setOutputLink
     */
    TD_DataPoolId *dpy;
};


struct DataPoolControlBlockClass {
    ControlBlockClass parent_class;
};


#define DATAPOOLCONTROLBLOCK_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DataPoolControlBlockClass, obj, TYPE_DATAPOOLCONTROLBLOCK)

#define DATAPOOLCONTROLBLOCK_CLASS(klass) \
        OBJECT_CLASS_CHECK(DataPoolControlBlockClass, klass, TYPE_DATAPOOLCONTROLBLOCK)

#define DATAPOOLCONTROLBLOCK(obj) \
        OBJECT_CHECK(DataPoolControlBlock, obj, TYPE_DATAPOOLCONTROLBLOCK)


DataPoolControlBlock* DataPoolControlBlock_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the data pool identifier for the i-th input. The argument i must lie in the 
 * interval [0, n-1] where n is the number of inputs.
 * An illegal value for argument i triggers the generation of an event report 
 * EVT_ILLEGAL_CB. There is no check on the legality of the data pool identifier.
 * This should normally be a valid identifier for an item of type <code>TD_Float</code>.
 * @param i the index of the input 
 * @param dpIdentifier the data pool item identifier 
 */
void DataPoolControlBlock_setInputLink
(
    DataPoolControlBlock *This, 
    unsigned int i, 
    TD_DataPoolId dpIdentifier
);

/**
 * Set the data pool identifier for the i-th output. The argument i must lie in the 
 * interval [0, n-1] where n is the number of outputs.
 * An illegal value for argument i triggers the generation of an event report 
 * EVT_ILLEGAL_CB. There is no check on the legality of the data pool identifier.
 * This should normally be a valid identifier for an item of type <code>TD_Float</code>.
 * @param i the index of the input 
 * @param dpIdentifier the data pool item identifier 
 */
void DataPoolControlBlock_setOutputLink
(
   DataPoolControlBlock *This,
   unsigned int i, 
   TD_DataPoolId dpIdentifier
);


#endif
