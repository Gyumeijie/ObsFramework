//
//
// DC_DummyDataPoolControlBlock.c
//
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "DataPool.h"
#include "DC_DummyDataPoolControlBlock.h"



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Implement the state propagation function. 
 * @see ControlBlock#propagate
 */
static void propagateState(void *obj)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    ControlBlock *cb = CONTROLBLOCK(obj);
    DataPoolControlBlock *dpcb = DATAPOOLCONTROLBLOCK(obj); 

    assert(cc_roc->isObjectConfigured(obj));

    DataPool *pDP = CC_RootObject_getDataPool();
    // Warining: Not use "obj" but pDP, for DC_DummyDataPoolControlBlock does't
    // inherit(indirectly) from DataPool.
    DataPoolClass *dpc = DATAPOOL_GET_CLASS(pDP);

    cb->x[0] = cb->p[0]*cb->x[0] + 
               dpc->getFloatValue(pDP, dpcb->dpu[0]) +
               dpc->getFloatValue(pDP, dpcb->dpu[1]) +
               dpc->getFloatValue(pDP, dpcb->dpu[2]);
}

/**
 * Implement the output update function. 
 * @see ControlBlock#propagate
 */
static void updateOutput(void *obj)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    ControlBlock *cb = CONTROLBLOCK(obj);
    DataPoolControlBlock *dpcb = DATAPOOLCONTROLBLOCK(obj); 

    assert(cc_roc->isObjectConfigured(obj));

    DataPool *pDP = CC_RootObject_getDataPool();
    DataPoolClass *dpc = DATAPOOL_GET_CLASS(pDP);

    dpc->setFloatValue(pDP, dpcb->dpy[0], cb->x[0]);
    dpc->setFloatValue(pDP, dpcb->dpy[1], cb->p[1]*cb->x[0]);
}

/**
 * Reset the control block by setting the state value to 1.0.
 */
static void reset(void *obj)
{
    ControlBlock *cb = CONTROLBLOCK(obj);

    assert(cb->x != pNULL);

    cb->x[0] = (TD_Float)1.0;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    ControlBlockClass *cbc = CONTROLBLOCK_GET_CLASS(obj);

    cbc->setNumberOfInputs((ControlBlock*)obj, 3);
    cbc->setNumberOfOutputs((ControlBlock*)obj, 2);

    ControlBlock_setNumberOfStates((ControlBlock*)obj, 1);
    ControlBlock_setNumberOfParameters((ControlBlock*)obj, 2);

    cbc->reset(obj);

    CC_RootObject_setClassId((CC_RootObject*)obj, ID_DUMMYDATAPOOLCONTROLBLOCK);
}

DC_DummyDataPoolControlBlock* DC_DummyDataPoolControlBlock_new(void)
{
    Object *obj = object_new(TYPE_DC_DUMMYDATAPOOLCONTROLBLOCK);
    return (DC_DummyDataPoolControlBlock*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    ControlBlockClass *cb = CONTROLBLOCK_CLASS(oc);

    cb->propagateState = propagateState;
    cb->updateOutput = updateOutput;
    cb->reset = reset;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_DUMMYDATAPOOLCONTROLBLOCK,
    .parent = TYPE_DATAPOOLCONTROLBLOCK,
    .instance_size = sizeof(DC_DummyDataPoolControlBlock),
    .abstract = false,
    .class_size = sizeof(DC_DummyDataPoolControlBlockClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_DummyDataPoolControlBlock_register(void)
{
    type_register_static(&type_info);
}
