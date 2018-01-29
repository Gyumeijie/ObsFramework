//
//
// PointerControlBlock.h
//
//
// Change Record:


#ifndef POINTERCONTROLBLOCK_H
#define POINTERCONTROLBLOCK_H


#include "ControlBlock.h"
#include "../Qom/object.h"


/*
 * Base class for pointer control blocks. 
 * A <i>pointer control block</i> is a control block that is linked to its inputs
 * and outputs through pointers. It adds to its <code>ControlBlock</code> base class
 * the following attributes:<ul>
 * <li>The <i>input pointers</i>: the pointers to the external locations from which the input
 * values are loaded.</li>
 * <li>The <i>output pointers</i>: the pointers to the external locations to which the output
 * values are written.</li>
 * </ul>
 * This class adds services to set up the link between the block inputs and outputs and the
 * external locations from which the inputs are read and to which the outputs are written.
 * <p>
 * This class deviates from the project-specific coding rule PR3.1.
 * Use of pointers to a variable of primitive type is necessary to fulfill
 * the function of the class.
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @author Roberto Totaro
 * @version 1.0
 * @ingroup Data
 */
#define TYPE_POINTERCONTROLBLOCK "pointercontrolblock"

void PointerControlBlock_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct PointerControlBlock {
    ControlBlock parent;

    /**
     * Array of input pointers.
     * pU[i] holds the pointer to the i-th input variable with i lying in the 
     * interval [0,N-1] where N is the number of inputs.
     * @see #setInputLink
     */
    TD_Float **pU;
    /**
     * Array of output pointers.
     * pY[i] holds the pointer to the i-th output variable with i lying in the 
     * interval [0,N-1] where N is the number of outputs.
     * @see #setOutputLink
     */
    TD_Float **pY;
};


struct PointerControlBlockClass {
    ControlBlockClass parent_class;
};


#define POINTERCONTROLBLOCK_GET_CLASS(obj) \
        OBJECT_GET_CLASS(PointerControlBlockClass, obj, TYPE_POINTERCONTROLBLOCK)

#define POINTERCONTROLBLOCK_CLASS(klass) \
        OBJECT_CLASS_CHECK(PointerControlBlockClass, klass, TYPE_POINTERCONTROLBLOCK)

#define POINTERCONTROLBLOCK(obj) \
        OBJECT_CHECK(PointerControlBlock, obj, TYPE_POINTERCONTROLBLOCK)


PointerControlBlock* PointerControlBlock_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the i-th input pointer. This method sets the pointer to the location from which the
 * the i-th input should be read. The argument i must lie in the interval [0, n-1] where
 * n is the number of inputs.
 * Illegal argument values trigger the generation of an event report EVT_ILLEGAL_CB.
 * @param i the index of the input 
 * @param pInput the pointer to the external input location
 */
void PointerControlBlock_setInputLink
(
    PointerControlBlock *This,
    unsigned int i,
    TD_Float *pInput
);

/**
 * Set the i-th output pointer. This method sets the pointer to the location to which the
 * the i-th output should be written. The argument i must lie in the interval [0, n-1]
 * where n is the number of outputs.
 * Illegal argument values trigger the generation of an event report EVT_ILLEGAL_CB.
 * @param i the index of the output 
 * @param pOutput the pointer to the external output location
 */
void PointerControlBlock_setOutputLink
(
    PointerControlBlock *This, 
    unsigned int i, 
    TD_Float *pOutput
);


#endif
