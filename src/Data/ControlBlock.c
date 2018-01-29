//
//
// ControlBlock.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "../Event/DC_EventRepository.h"
#include "../Base/CC_RootObject.h"
#include "ControlBlock.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void ControlBlock_setNumberOfStates(ControlBlock *This, unsigned int n)
{
    assert(This->nStates < 0);

    This->nStates = n;
    This->x = g_malloc(sizeof(TD_Float)*n);

    for (unsigned int i = 0; i<n; i++) {
        This->x[i] = (TD_Float)0.0;
    }
}

void ControlBlock_setNumberOfParameters(ControlBlock *This, unsigned int n)
{
    assert(This->nParameters < 0);

    This->nParameters = n;
    This->p = g_malloc(sizeof(TD_Float)*n);

    for (unsigned int i = 0; i<n; i++) {
        This->p[i] = (TD_Float)0.0;
    }
}

int ControlBlock_getNumberOfOutputs(const ControlBlock *This)
{
    assert(This->nOutputs > -1);

    return This->nOutputs;
}

int ControlBlock_getNumberOfStates(const ControlBlock *This)
{
    assert(This->nStates > -1);

    return This->nStates;
}

int ControlBlock_getNumberOfInputs(const ControlBlock *This)
{
    assert(This->nInputs > -1);

    return This->nInputs;
}

int ControlBlock_getNumberOfParameters(const ControlBlock *This)
{
    assert(This->nParameters > -1);

    return This->nParameters;
}

TD_Float ControlBlock_getState(const ControlBlock *This, unsigned int i)
{
    assert((This->x != pNULL) && ((int)i < This->nStates));

    return This->x[i];
}

TD_Float ControlBlock_getParameter(const ControlBlock *This, unsigned int i)
{
    assert((This->p != pNULL) && ((int)i < This->nParameters));

    return This->p[i];
}

void ControlBlock_setState(ControlBlock *This, unsigned int i, TD_Float newValue)
{
    assert((This->x != pNULL) && ((int)i < This->nStates));

    if ((int)i < This->nStates) {
        This->x[i] = newValue;
    } else {
        DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
        DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
        dc_erc->create(dc_er, (CC_RootObject*)This, EVT_ILLEGAL_CB);
    }
}

void ControlBlock_setParameter(ControlBlock *This, unsigned int i, TD_Float newValue)
{
    assert((This->p != pNULL) && ((int)i < This->nParameters));

    if ((int)i < This->nParameters) {
        This->p[i] = newValue;
    } else {
        DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
        DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
        dc_erc->create(dc_er, (CC_RootObject*)This, EVT_ILLEGAL_CB);
    }
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Propagate the input values updating the state variables and the outputs.
 * This method implements the transfer function encapsulated by the control
 * block. It causes the state
 * variables to be updated to take account of the latest input values and
 * it then uses the new state values to compute a new set of ouptuts.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *      propagateState(void);
 *      updateOutput(void); </PRE>
 * Note that methods <code>propagateState</code> and <code>updateOutput</code>
 * are pure virtual methods. Together, they define the transfer function
 * encapsulated by the control block.
 * <p>
 * This class defines the structure of the propagation cycle.
 * It is defined to be <code>virtual</code> to allow subclasses
 * to implement different propagation cycles.
 */
static void propagate(void *obj)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    assert(cc_roc->isObjectConfigured(obj));

    ControlBlockClass *cbc = CONTROLBLOCK_GET_CLASS(obj);
    cbc->propagateState(obj);
    cbc->updateOutput(obj);
}

/**
 * Reset the control block bringing its state back to the value they had when
 * the configuration process of the control block was terminated. The default
 * implementation provided by this class resets the state values to zero.
 */
static void reset(void *obj)
{
    ControlBlock *This = CONTROLBLOCK(obj);

    assert(This->x != pNULL);
    for (int i=0; i<This->nStates; i++) {
        This->x[i] = (TD_Float)0.0;
    }
}

/**
 * Perform a class-specific configuration check on a control block.
 * It is checked that the number of inputs, outputs, states and parameters
 * have been set to legal values.
 */
static bool isObjectConfigured(void *obj)
{
    CC_RootObjectClass *cc_roc = GET_CLASS(TYPE_CC_ROOTOBJECT);
    ControlBlock *This = CONTROLBLOCK(obj);

    return ((cc_roc->isObjectConfigured(obj)) &&
            (This->nInputs != -1) &&
            (This->nOutputs != -1) && 
            (This->nStates != -1) && 
            (This->nParameters != -1));
}



///////////////////////////////////////////////////////////////////////////////
//
//                    pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the number of inputs and, if required, allocate the necessary storage.
 * The number of inputs must be non-negative.
 * @param n the number of inputs
 */
static void setNumberOfInputs(void *obj, unsigned int n)
{
    // this is automate genenrated by converter
}

/**
 * Set the number of outputs and, if required, allocate the necessary storage.
 * The number of inputs must be non-negative.
 * @param n the number of outputs
 */
static void setNumberOfOutputs(void *obj, unsigned int n)
{
    // this is automate genenrated by converter
}

/**
 * Implement the state propagation function. The result of calling this method
 * should be a new set of values for the state variables computed as a function
 * of the current input values, the old state values, and the parameter values.
 * Note that the state and parameter values are directly accessible as
 * <code>protected</code> variables. This should facilitate the implementation
 * of this method in concrete subclasses.
 * @see #propagate
 */
static void propagateState(void *obj)
{
    // this is automate genenrated by converter
}

/**
 * Implement the output update function. This method uses the current
 * values of the inputs and state variables to compute
 * and apply new values for the outputs. Note that the
 * input, state and parameter values are directly accessible as <code>protected</code>
 * variables. This should facilitate the implementation of this method
 * in concrete subclasses.
 * @see #propagate
 */
static void updateOutput(void *obj)
{
    // this is automate genenrated by converter
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

// the following may be useful if you don't need it, just delete.
static void instance_init(Object *obj)
{
    ControlBlock *This = CONTROLBLOCK(obj);

    This->x           = pNULL;
    This->p           = pNULL;
    This->nInputs     = -1;
    This->nOutputs    = -1;
    This->nStates     = -1;
    This->nParameters = -1;
}

ControlBlock* ControlBlock_new(void)
{
    return (ControlBlock*)object_new(TYPE_CONTROLBLOCK);
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    ControlBlockClass *cbc = CONTROLBLOCK_CLASS(oc);
    cbc->setNumberOfInputs = setNumberOfInputs;
    cbc->setNumberOfOutputs = setNumberOfOutputs;
    cbc->propagateState = propagateState;
    cbc->updateOutput = updateOutput;
    cbc->propagate = propagate;
    cbc->reset = reset;

    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_CONTROLBLOCK,
    .parent = TYPE_CC_ROOTOBJECT,
    .instance_size = sizeof(ControlBlock),
    .abstract = true,
    .class_size = sizeof(ControlBlockClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void ControlBlock_register(void)
{
    type_register_static(&type_info);
}
