//
//
// ControlBlock.h
//
//
// Change Record:


#ifndef CONTROLBLOCK_H
#define CONTROLBLOCK_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "../Qom/object.h"


/*
 * Base class from which all control block classes are derived.
 * A control block is intended to model a discrete transfer function of the
 * following kind<PRE>
 *      x(k+1) = h( x(k) , u(k), p )
 *      y(k) = g( x(k), u(k), p )   </PRE>
 * where: <ul>
 * <li>k is a temporal index</li>
 * <li>x is a vector of state variables that are updated at every sampling time k</li>
 * <li>u is a vector of input variables that are updated at every sampling time k</li>
 * <li>y is a vector of output variables that are updated at every sampling time k</li>
 * <li>p is a vector of nominally constant parameters</li>
 * <li>h(.) is a state propagation function</li>
 * <li>g(.) is an output update function</li>
 * </ul>
 * This class offers the following types of services: <ul>
 * <li>services to set and get the number of the inputs, outputs,
 * states, and parameters</li>
 * <li>services to set and get the values of the state variables and of the parameters</li>
 * <li>services to propagate the state and update the outputs</li>
 * <li>reset service to reset the state propagation and output update algorithms
 * and bring the state back to the value it had at the time the control block
 * was initialized</li>
 * </ul>
 * No services are defined to set and get the output and input values because there can
 * be several ways in which a control block is linked to the source of its inputs and to
 * the destination for its outputs. Example of typical input/output linking mechanisms are: <ul>
 * <li><i>Copy Link</i>: at every sampling time, the inputs are copied from the external
 * input source into an internal buffer maintained by the control block. After state and
 * output propagation, the updated values of the outputs are copied to the external output
 * destination location.</li>
 * <li><i>Pointer Link</i>: during the configuration phase, the control block is loaded with
 * pointers to the input sources and to the output destinations. The control block then accesses
 * its inputs and outputs through these pointers.</li>
 * <li><i>Data Item Link</i>: during the configuration phase, the control block is loaded with
 * data items(instances of class <code>DC_DataItem</code>) that encapsulate the input sources and
 * output destinations. The control block then accesses its inputs and outputs through their data
 * items.</li>
 * <li><i>Data Pool Link</i>: the input sources and output destinations are assumed to be located
 * in the data pool. During the configuration phase, the control block is loaded with the identifiers
 * of the data pool locations that hold the inputs and outputs. The control block then accesses
 * its inputs and outputs directloy from the data pool.</li>
 * </ul>
 * The diversity of the above mechansims makes it impossible to define the services to access
 * the inputs and outputs at the level of this base class. The definition of these services is
 * therefore left to subclasses of <code>ControlBlock</code>.
 * <p>
 * This is an abstract class because it defines neither the state propagation
 * and output update functions nor the input and output allocation, setter and getter
 * functions. However it internally defines variables that are intended to make it easy for
 * developers to create concrete classes that implement specific state propagation and
 * output update algorithms.
 * More specifically, this class defines the following items: <ul>
 * <li>The number of inputs(nInputs)</li>
 * <li>The number of outputs(nOutputs)</li>
 * <li>The number of state variables(nStates)</li>
 * <li>The number of parameters(nParameters)</li>
 * <li>An array x to hold the state variables</li>
 * <li>An array p to hold the parameter variables</li>
 * </ul>
 * These variables are declared <code>protected</code> so as to give subclasses
 * ready and easy access to them. It should be stressed however that there is no
 * obligation on the part of subclasses to use these data structures. If
 * they are subject to special requirements, they are free to implement the
 * state propagation and output update services using class-specific structures.
 * <p>
 * The internal data structures must be configured by the user. Thus,
 * the configuration process for an instance of this class is
 * as follows: <ul>
 * <li>set the number of inputs</li>
 * <li>set the number of outputs</li>
 * <li>set the number of states</li>
 * <li>set the number of parameters</li>
 * </ul>
 * Access to specific parameter and state values is
 * performed through an integer index i that designates the location
 * of the desired input, output, parameter or state value within the
 * corresponding array. Run-time checks on the legality of the index
 * are only performed where errors might corrupt internal data
 * structures(i.e. during write accesses). In other cases,
 * responsibility for ensuring the legality of the index is left
 * to the caller.
 * @author Alessandro Pasetti, Roberto Totaro
 * @version 1.0
 * @ingroup Data
 */
#define TYPE_CONTROLBLOCK "controlblock"

void ControlBlock_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct ControlBlock {
    CC_RootObject parent;

    /**
     * Number of inputs
     */
    int nInputs;
    /**
     * Number of outputs
     */
    int nOutputs;
    /**
     * Number of state variables
     */
    int nStates;
    /**
     * Number of parameters
     */
    int nParameters;
    /**
     * Array to hold the state variables.
     * x[i] holds the i-th state variable with i in the interval [0,N] where N is
     * the number of states.
     * @see #nStates
     */
    TD_Float *x;
    /**
     * Array to hold the parameter variables.
     * p[i] holds the i-th state variable with i in the interval [0,N-1] where N is
     * the number of parameters.
     * @see #nParameters
     */
    TD_Float *p;
};


struct ControlBlockClass {
    CC_RootObjectClass parent_class;
 
    void (*propagate)(void *obj);
    void (*reset)(void *obj);
 
    void (*setNumberOfInputs)(void *obj, unsigned int n);
    void (*setNumberOfOutputs)(void *obj, unsigned int n);
    void (*propagateState)(void *obj);
    void (*updateOutput)(void *obj);
};


#define CONTROLBLOCK_GET_CLASS(obj) \
        OBJECT_GET_CLASS(ControlBlockClass, obj, TYPE_CONTROLBLOCK)

#define CONTROLBLOCK_CLASS(klass) \
        OBJECT_CLASS_CHECK(ControlBlockClass, klass, TYPE_CONTROLBLOCK)

#define CONTROLBLOCK(obj) \
        OBJECT_CHECK(ControlBlock, obj, TYPE_CONTROLBLOCK)


ControlBlock* ControlBlock_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the number of states. This method causes the memory for the state array
 * to be allocated. The number of states must be non-negative. The state values
 * are initialized to zero. This is an initialization method: it shall be called
 * only once.
 * @param n the number of states
 */
void ControlBlock_setNumberOfStates(ControlBlock *This, unsigned int n);

/**
 * Set the number of parameters. This method causes the memory for the parameter array
 * to be allocated. The number of parameters must be non-negative. The parameter values
 * are initialized to zero. This is an initialization method: it shall be called
 * only once.
 * @param n the number of parameters
 */
void ControlBlock_setNumberOfParameters(ControlBlock *This, unsigned int n);

/**
 * Return the number of outputs of the control block.
 * @return the number of outputs
 */
int ControlBlock_getNumberOfOutputs(const ControlBlock *This);

/**
 * Return the number of states of the control block.
 * @return the number of states
 */
int ControlBlock_getNumberOfStates(const ControlBlock *This);

/**
 * Return the number of inputs of the control block.
 * @return the number of inputs
 */
int ControlBlock_getNumberOfInputs(const ControlBlock *This);

/**
 * Return the number of parameters of the control block.
 * @return the number of parameters
 */
int ControlBlock_getNumberOfParameters(const ControlBlock *This);

/**
 * Return the value of the i-th state. The argument i must lie
 * in the interval [0, n-1] where n is the number of states.
 * No check is performed on the legality of the index i.
 * @return the value of the i-th state variable
 * @param i the index of the state variable
 */
TD_Float ControlBlock_getState(const ControlBlock *This, unsigned int i);

/**
 * Return the value of the i-th parameter. The argument i must lie
 * in the interval [0, n-1] where n is the number of parameters.
 * No check is performed on the legality of the index i.
 * @return the value of the i-th parameter variable
 * @param i the index of the parameter variable
 */
TD_Float ControlBlock_getParameter(const ControlBlock *This, unsigned int i);

/**
 * Set the value of the i-th state. The argument i must lie
 * in the interval [0, n-1] where n is the number of states.
 * Illegal argument values trigger the generation of an event report EVT_ILLEGAL_CB.
 * This method should not normally be used since the state values are internally computed
 * by propagating the input and the previous state values. It is provided for the
 * (non-nominal) case where there is a need to overwrite the internally computed state.
 * @param newValue the new value of the i-th state variable
 * @param i the index of the state variable
 */
void ControlBlock_setState(ControlBlock *This, unsigned int i, TD_Float newValue);

/**
 * Set the value of the i-th parameter. The argument i must lie
 * in the interval [0, n-1] where n is the number of parameters.
 * Illegal argument values trigger the generation of an event report EVT_ILLEGAL_CB.
 * @param newValue the new value of the i-th parameter variable
 * @param i the index of the parameter variable
 */
void ControlBlock_setParameter(ControlBlock *This, unsigned int i, TD_Float newValue);


#endif
