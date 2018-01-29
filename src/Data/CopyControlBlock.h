//
//
// CopyControlBlock.h
//
//
// Change Record:


#ifndef COPYCONTROLBLOCK_H
#define COPYCONTROLBLOCK_H


#include "ControlBlock.h"
#include "../Qom/object.h"


/*
 * Base class for copy control blocks. 
 * A <i>copy control block</i> is a control block that implements a copy link to its
 * inputs and outputs. It adds to its <code>ControlBlock</code> base class
 * the following attributes:<ul>
 * <li>The <i>input buffers</i>: internal data structure where the values of the
 * control block inputs are copied at the beginning of a propagation cycle. The
 * state propagation and output update services read the value of the inputs from
 * the input buffers.</li>
 * <li>The <i>output buffers</i>: internal data structure where the values of the
 * control block outputs are written by the output update service. These values
 * are intended to be copied to the external output destination locations.</li>
 * </ul>
 * The input and output buffers are implemented as arrays. They are declared 
 * <code>protected</code> to give concrete subclasses ready access to them.
 * <p>
 * This class adds services to copy the input values from their external locations
 * to the internal input buffers and to copy the output values from the internal
 * output buffers to their external destinations. 
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @author Roberto Totaro
 * @version 1.0
 * @ingroup Data
 */
#define TYPE_COPYCONTROLBLOCK "copycontrolblock"

void CopyControlBlock_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct CopyControlBlock {
    ControlBlock parent;

    /**
     * Array to hold the input buffer.
     * u[i] holds the i-th state variable with i lying in the interval [0,N-1] where N
     * is the number of inputs.
     * @see ControlBlock#setNumberOfInputs
     * @see #setInput
     * @see #getInput
     */
    TD_Float *u;
    /**
     * Array to hold the output buffer.
     * y[i] holds the i-th output variable with i lying in the interval [0,N-1] where N
     * is the number of outputs.
     * @see ControlBlock#setNumberOfOutputs
     * @see #setOutput
     * @see #getOutput
     */
    TD_Float *y;
};


struct CopyControlBlockClass {
    ControlBlockClass parent_class;
};


#define COPYCONTROLBLOCK_GET_CLASS(obj) \
        OBJECT_GET_CLASS(CopyControlBlockClass, obj, TYPE_COPYCONTROLBLOCK)

#define COPYCONTROLBLOCK_CLASS(klass) \
        OBJECT_CLASS_CHECK(CopyControlBlockClass, klass, TYPE_COPYCONTROLBLOCK)

#define COPYCONTROLBLOCK(obj) \
        OBJECT_CHECK(CopyControlBlock, obj, TYPE_COPYCONTROLBLOCK)


CopyControlBlock* CopyControlBlock_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Return the value of the i-th input. The argument i must lie
 * in the interval [0, n-1] where n is the number of inputs.
 * No check is performed on the legality of the index i.
 * @return the value of the i-th input variable
 * @param i the index of the input variable
 */
TD_Float CopyControlBlock_getInput(const CopyControlBlock *This, unsigned int i);

/**
 * Return the value of the i-th output. The argument i must lie
 * in the interval [0, n-1] where n is the number of outputs.
 * No check is performed on the legality of the index i.
 * @return the value of the i-th output variable
 * @param i the index of the output variable
 */
TD_Float CopyControlBlock_getOutput(const CopyControlBlock *This, unsigned int i);

/**
 * Set the value of the i-th input. The argument i must lie
 * in the interval [0, n-1] where n is the number of inputs.
 * Illegal argument values trigger the generation of an event report EVT_ILLEGAL_CB.
 * @param newValue the new value of the i-th input variable
 * @param i the index of the input variable
 */
void CopyControlBlock_setInput
(
    CopyControlBlock *This, 
    unsigned int i, 
    TD_Float newValue
);

/**
 * Set the value of the i-th output. The argument i must lie
 * in the interval [0, n-1] where n is the number of outputs.
 * Illegal argument values trigger the generation of an event report EVT_ILLEGAL_CB.
 * This method should not normally be used since the output is computed internally by
 * propagating the input and the state. It is provided for convenience only
 * for non-nominal situations.
 * @param newValue the new value of the i-th output variable
 * @param i the index of the output variable
 */
void CopyControlBlock_setOutput
(
    CopyControlBlock *This, 
    unsigned int i,
    TD_Float newValue
);


#endif
