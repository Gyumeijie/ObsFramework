//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyCopyControlBlock.c
//
// Version	1.3
// Date	    11.04.03 (Version 1.0)
//          14.10.03 (Version 1.1)
//          16.10.03 (Version 1.2 & 1.3)
// Author	A. Pasetti (P&P Software), R. Totaro
//
// Change Record:
//   Version 1.1: Updated to reflect the new structure of the ControlBlock class
//   Version 1.2: The class is now derived from CopyControlBlock
//   Version 1.3: Added missing assert()s

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "DC_DummyCopyControlBlock.h"



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
    assert(cc_roc->isObjectConfigured(obj));

    ControlBlock *cb = CONTROLBLOCK(obj);
    CopyControlBlock *ccb = COPYCONTROLBLOCK(obj); 

    cb->x[0] = (cb->p[0]*cb->x[0]) + ccb->u[0] + ccb->u[1] + ccb->u[2];
}

/**
 * Implement the output update function. 
 * @see ControlBlock#propagate
 */
static void updateOutput(void *obj)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    assert(cc_roc->isObjectConfigured(obj));

    ControlBlock *cb = CONTROLBLOCK(obj);
    CopyControlBlock *ccb = COPYCONTROLBLOCK(obj); 

    ccb->y[0] = cb->x[0];
    ccb->y[1] = cb->p[1] * cb->x[0];
}

/**
 * Reset the control block by setting the state values to 1.0 and the inputs to 0.0.
 */
static void reset(void *obj)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    assert(cc_roc->isObjectConfigured(obj));

    ControlBlockClass *cbc = GET_CLASS(TYPE_CONTROLBLOCK); 
    cbc->reset(obj);

    // Set initial state to 1.0
    ControlBlock *cb = CONTROLBLOCK(obj);
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
    cbc->setNumberOfOutputs(obj, 2);

    ControlBlock_setNumberOfStates((ControlBlock*)obj, 1);
    ControlBlock_setNumberOfParameters((ControlBlock*)obj, 2);

    cbc->reset(obj);

    CC_RootObject_setClassId((CC_RootObject*)obj, ID_DUMMYCOPYCONTROLBLOCK);
}

DC_DummyCopyControlBlock* DC_DummyCopyControlBlock_new(void)
{
    return (DC_DummyCopyControlBlock*)object_new(TYPE_DC_DUMMYCOPYCONTROLBLOCK);
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    ControlBlockClass *cbc = CONTROLBLOCK_CLASS(oc);

    cbc->propagateState = propagateState;
    cbc->updateOutput = updateOutput;
    cbc->reset = reset;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_DUMMYCOPYCONTROLBLOCK,
    .parent = TYPE_COPYCONTROLBLOCK,
    .instance_size = sizeof(DC_DummyCopyControlBlock),
    .abstract = false,
    .class_size = sizeof(DC_DummyCopyControlBlockClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_DummyCopyControlBlock_register(void)
{
    type_register_static(&type_info);
}
