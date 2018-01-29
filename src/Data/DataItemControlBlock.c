//
//
// DataItemControlBlock.c
//
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../Event/DC_EventRepository.h"
#include "../Base/CC_RootObject.h"
#include "DC_DataItem.h"
#include "DataItemControlBlock.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DataItemControlBlock_setInputLink(DataItemControlBlock *This,
                                       unsigned int i, DC_DataItem* pDataItem)
{
    ControlBlock *parent = (ControlBlock*)This;

    assert((This->pDIU != pNULL) && 
           (pDataItem != pNULL) && 
           ((int)i < parent->nInputs));

    if ((int)i < parent->nInputs) {
        This->pDIU[i] = pDataItem;
    } else {
        DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
        DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
        dc_erc->create(dc_er, (CC_RootObject*)This, EVT_ILLEGAL_CB);
    }
}

void DataItemControlBlock_setOutputLink(DataItemControlBlock *This, 
                                        unsigned int i, DC_DataItem* pDataItem)
{
    ControlBlock *parent = (ControlBlock*)This;

    assert((This->pDIY != pNULL) && 
           ((pDataItem != pNULL)) && 
           ((int)i < parent->nOutputs));

    if ((int)i < parent->nOutputs) {
        This->pDIY[i] = pDataItem;
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
 * the input data items to be allocated.
 * @param n the number of inputs
 */
static void setNumberOfInputs(void *obj, unsigned int n)
{
    ControlBlock *parent = CONTROLBLOCK(obj);
    DataItemControlBlock *This = DATAITEMCONTROLBLOCK(obj);

    assert(parent->nInputs<0 && n>0);

    parent->nInputs = n;
    This->pDIU = g_malloc(sizeof(DC_DataItem)*n);

    for (unsigned int i=0; i<n; i++) {
        This->pDIU[i] = pNULL;
    }
}

/**
 * Set the number of outputs. This method causes the memory for the array holding
 * the output data items to be allocated.
 * @param n the number of outputs
 */
static void setNumberOfOutputs(void *obj, unsigned int n)
{
    ControlBlock *parent = CONTROLBLOCK(obj);
    DataItemControlBlock *This = DATAITEMCONTROLBLOCK(obj);

    assert((parent->nOutputs < 0) && (n > 0));

    parent->nOutputs = n;
    This->pDIY = g_malloc(sizeof(DC_DataItem)*n);

    for (unsigned int i=0; i<n; i++) {
        This->pDIY[i] = pNULL;
    }
}

/**
 * Perform a class-specific configuration check on a pointer control block. 
 * It is checked that the input and output data items have been loaded.
 */
static bool isObjectConfigured(void *obj)
{
    ControlBlockClass *cbc = GET_CLASS(TYPE_CONTROLBLOCK);
    ControlBlock *parent = CONTROLBLOCK(obj);
    DataItemControlBlock *This = DATAITEMCONTROLBLOCK(obj);

    if (!CC_ROOTOBJECT_CLASS(cbc)->isObjectConfigured(obj)) {
        return false;
    }

    for (int i=0; i<parent->nInputs; i++) {
        if (This->pDIU[i] == pNULL) return false;
    }

    for (int i=0; i<parent->nOutputs; i++) {
        if (This->pDIY[i] == pNULL) return false;
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
    DataItemControlBlock *This = DATAITEMCONTROLBLOCK(obj);

    This->pDIU=pNULL;
    This->pDIY=pNULL;
}

DataItemControlBlock* DataItemControlBlock_new(void)
{
    Object *obj = object_new(TYPE_DATAITEMCONTROLBLOCK);
    return (DataItemControlBlock*)obj;
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
    .name = TYPE_DATAITEMCONTROLBLOCK,
    .parent = TYPE_CONTROLBLOCK,
    .instance_size = sizeof(DataItemControlBlock),
    .abstract = false,
    .class_size = sizeof(DataItemControlBlockClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DataItemControlBlock_register(void)
{
    type_register_static(&type_info);
}
