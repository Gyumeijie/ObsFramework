//
//
// DataPoolControlBlock.c
//
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../Event/DC_EventRepository.h"
#include "../Base/CC_RootObject.h"
#include "DataPoolControlBlock.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DataPoolControlBlock_setInputLink(DataPoolControlBlock *This,
                                       unsigned int i,
                                       TD_DataPoolId dpIdentifier)
{
    ControlBlock *parent = (ControlBlock*)This;

    assert((This->dpu != pNULL) && 
           (dpIdentifier > -1) && 
           ((int)i < parent->nInputs));

    if ((int)i < parent->nInputs) {
        This->dpu[i] = dpIdentifier;
    } else {
        DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
        DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
        dc_erc->create(dc_er, (CC_RootObject*)This, EVT_ILLEGAL_CB);
    }
}

void DataPoolControlBlock_setOutputLink(DataPoolControlBlock *This,
                                        unsigned int i, 
                                        TD_DataPoolId dpIdentifier)
{
    ControlBlock *parent = (ControlBlock*)This;

    assert((This->dpy != pNULL) && 
           (dpIdentifier > -1) && 
           ((int)i < parent->nOutputs));

    if ((int)i < parent->nOutputs) {
        This->dpy[i] = dpIdentifier;
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
 * Set the number of inputs. This method causes the memory for the array holding
 * the input identifiers to be allocated.
 * @param n the number of inputs
 */
static void setNumberOfInputs(void *obj, unsigned int n)
{
    ControlBlock *parent = CONTROLBLOCK(obj);
    DataPoolControlBlock *This = DATAPOOLCONTROLBLOCK(obj);

    assert((parent->nInputs < 0) && (n > 0));

    parent->nInputs = n;
    This->dpu = g_malloc(sizeof(TD_DataPoolId)*n);

    for (unsigned int i=0; i<n; i++) {
        This->dpu[i] = -1;
    }
}

/**
 * Set the number of outputs. This method causes the memory for the array holding
 * the output identifiers to be allocated.
 * @param n the number of outputs
 */
static void setNumberOfOutputs(void *obj, unsigned int n)
{
    ControlBlock *parent = CONTROLBLOCK(obj);
    DataPoolControlBlock *This = DATAPOOLCONTROLBLOCK(obj);

    assert((parent->nOutputs < 0) && (n > 0));

    parent->nOutputs = n;
    This->dpy = g_malloc(sizeof(TD_DataPoolId)*n);

    for (unsigned int i=0; i<n; i++) {
        This->dpy[i] = -1;
    }
}


/**
 * Perform a class-specific configuration check on a pointer control block. 
 * It is checked that the input and output identifiers have been defined.
 */
static bool isObjectConfigured(void *obj)
{
    ControlBlockClass *cbc = GET_CLASS(TYPE_CONTROLBLOCK);
    ControlBlock *parent = CONTROLBLOCK(obj);
    DataPoolControlBlock *This = DATAPOOLCONTROLBLOCK(obj);
    
    if (!CC_ROOTOBJECT_CLASS(cbc)->isObjectConfigured(obj)) {
        return false;
    }

    for (int i=0; i<parent->nInputs; i++) {
        if (This->dpu[i] < 0) return false;
    }

    for (int i=0; i<parent->nOutputs; i++) {
        if (This->dpy[i] < 0) return false;
    }

    return true;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    DataPoolControlBlock *This = DATAPOOLCONTROLBLOCK(obj);

    This->dpu = pNULL;
    This->dpy = pNULL;
}

DataPoolControlBlock* DataPoolControlBlock_new(void)
{
    Object *obj = object_new(TYPE_DATAPOOLCONTROLBLOCK);
    return (DataPoolControlBlock*)obj;
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

    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_DATAPOOLCONTROLBLOCK,
    .parent = TYPE_CONTROLBLOCK,
    .instance_size = sizeof(DataPoolControlBlock),
    .abstract = false,
    .class_size = sizeof(DataPoolControlBlockClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DataPoolControlBlock_register(void)
{
    type_register_static(&type_info);
}
