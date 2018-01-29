//
//
// CopyControlBlock.c
//
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "../Event/DC_EventRepository.h"
#include "../Base/CC_RootObject.h"
#include "CopyControlBlock.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

TD_Float CopyControlBlock_getInput(const CopyControlBlock *This, unsigned int i)
{
    ControlBlock *parent = (ControlBlock*)This;

    assert((This->u != pNULL) && ((int)i < parent->nInputs));
    return This->u[i];
}

TD_Float CopyControlBlock_getOutput(const CopyControlBlock *This, unsigned int i)
{
    ControlBlock *parent = (ControlBlock*)This;

    assert((This->y != pNULL) && ((int)i < parent->nOutputs));
    return This->y[i];
}

void CopyControlBlock_setInput(CopyControlBlock *This,
                               unsigned int i, TD_Float newValue)
{
    ControlBlock *parent = (ControlBlock*)This;

    assert((This->u != pNULL) && ((int)i < parent->nInputs));

    if ((int)i < parent->nInputs) {
        This->u[i] = newValue;
    } else {
        DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
        DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
        dc_erc->create(dc_er, (CC_RootObject*)This, EVT_ILLEGAL_CB);
    }
}

void CopyControlBlock_setOutput(CopyControlBlock *This, 
                                unsigned int i, TD_Float newValue)
{
    ControlBlock *parent = (ControlBlock*)This;

    assert((This->y != pNULL) && ((int)i < parent->nInputs));

    if ((int)i < parent->nOutputs) {
        This->y[i]=newValue;
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
 * Set the number of inputs. This method causes the memory for the input buffer
 * to be allocated. The number of inputs must be non-negative. The input values
 * are initialized to zero. This is an initialization method:  it shall be called
 * only once.
 * @param n the number of inputs
 */
static void setNumberOfInputs(void *obj, unsigned int n)
{
    ControlBlock *parent = CONTROLBLOCK(obj);
    CopyControlBlock *This = COPYCONTROLBLOCK(obj);

    assert(parent->nInputs < 0);
    assert(n > 0);

    parent->nInputs = n;
    This->u = g_malloc(sizeof(TD_Float)*n);

    unsigned int i;
    for (i=0; i<n; i++) {
        This->u[i] = (TD_Float)0.0;
    }
}

/**
 * Set the number of outputs. This method causes the memory for the output buffer
 * to be allocated. The number of outputs must be non-negative. The output values
 * are initialized to zero. This is an initialization method:  it shall be called
 * only once.
 * @param n the number of outputs
 */
static void setNumberOfOutputs(void *obj, unsigned int n)
{
    ControlBlock *parent = CONTROLBLOCK(obj);
    CopyControlBlock *This = COPYCONTROLBLOCK(obj);

    assert(parent->nOutputs < 0);
    assert(n > 0);

    parent->nOutputs = n;
    This->y = g_malloc(sizeof(TD_Float)*n);

    for (unsigned int i=0; i<n; i++) {
        This->y[i] = (TD_Float)0.0;
    }
}

/**
 * Reset the control block bringing its state and input and output buffers to the values
 * they had when the configuration process of the control block was terminated. 
 * A pseudocode implementation of this method is as follows:<pre>
 *      ControlBlock::reset(void);  // call method in super class to reset the state
 *      reset the input buffers to zero;
 *      reset the output buffers to zero;</pre>
 */
static void reset(void *obj)
{
    CopyControlBlock *This = COPYCONTROLBLOCK(obj);
    ControlBlock *parent = CONTROLBLOCK(obj);
    ControlBlockClass *cbc = GET_CLASS(TYPE_CONTROLBLOCK);

    assert((parent->x != pNULL) && (This->u != pNULL));

    // Reset the state variables
    cbc->reset(obj);

    for (int i=0; i<parent->nInputs; i++) {
        This->u[i] = (TD_Float)0.0;
    }
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    CopyControlBlock *This = COPYCONTROLBLOCK(obj);

    This->u = pNULL;
    This->y = pNULL;
}

CopyControlBlock* CopyControlBlock_new(void)
{
    Object *obj = object_new(TYPE_COPYCONTROLBLOCK);
    return (CopyControlBlock*)obj;
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
    cbc->reset = reset;
}

static const TypeInfo type_info = {
    .name = TYPE_COPYCONTROLBLOCK,
    .parent = TYPE_CONTROLBLOCK,
    .instance_size = sizeof(CopyControlBlock),
    .abstract = false,
    .class_size = sizeof(CopyControlBlockClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void CopyControlBlock_register(void)
{
    type_register_static(&type_info);
}
