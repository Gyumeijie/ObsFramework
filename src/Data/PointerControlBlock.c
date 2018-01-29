//
//
// PointerControlBlock.c
//
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../Event/DC_EventRepository.h"
#include "../Base/CC_RootObject.h"
#include "PointerControlBlock.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void PointerControlBlock_setInputLink(PointerControlBlock *This, 
                                      unsigned int i, TD_Float *pInput)
{
    ControlBlock *parent = (ControlBlock*)This;

    assert((This->pU != pNULL) && 
           (pInput != pNULL) && 
           ((int)i < parent->nInputs));

    if ((int)i < parent->nInputs) {
        This->pU[i] = pInput;
    } else {
        DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
        DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
        dc_erc->create(dc_er, (CC_RootObject*)This, EVT_ILLEGAL_CB);
    }
}

void PointerControlBlock_setOutputLink(PointerControlBlock *This,
                                       unsigned int i, TD_Float *pOutput)
{
    ControlBlock *parent = (ControlBlock*)This;

    assert((This->pY != pNULL) && 
           (pOutput != pNULL) && 
           ((int)i < parent->nOutputs));

    if ((int)i < parent->nOutputs) {
        This->pY[i] = pOutput;
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
 * the input pointers to be allocated. This is an initialization method:  it shall
 * be called only once.
 * @param n the number of inputs
 */
static void setNumberOfInputs(void *obj, unsigned int n)
{
    ControlBlock *parent = CONTROLBLOCK(obj);
    PointerControlBlock *This = POINTERCONTROLBLOCK(obj);

    assert(parent->nInputs < 0);
    assert(n > 0);

    parent->nInputs = n;
    This->pU = g_malloc(sizeof(TD_Float)*n);

    for (unsigned int i=0; i<n; i++) {
        This->pU[i] = pNULL;
    }
}

/**
 * Set the number of outputs. This method causes the memory for the array holding
 * the output pointers to be allocated. This is an initialization method:  it shall
 * be called only once.
 * @param n the number of outputs
 */
static void setNumberOfOutputs(void *obj, unsigned int n)
{
    ControlBlock *parent = CONTROLBLOCK(obj);
    PointerControlBlock *This = POINTERCONTROLBLOCK(obj);
    
    assert(parent->nOutputs < 0);
    assert(n > 0);

    parent->nOutputs = n;
    This->pY = g_malloc(sizeof(TD_Float)*n);

    for (unsigned int i=0; i<n; i++) {
        This->pY[i] = pNULL;
    }
}

/**
 * Perform a class-specific configuration check on a pointer control block. 
 * It is checked that the input and output pointers have been loaded.
 */
static bool isObjectConfigured(void *obj)
{
    ControlBlockClass *cbc = GET_CLASS(TYPE_CONTROLBLOCK);
    ControlBlock *parent = CONTROLBLOCK(obj);
    PointerControlBlock *This = POINTERCONTROLBLOCK(obj);

    if (!CC_ROOTOBJECT_CLASS(cbc)->isObjectConfigured(obj)) {
        return false;
    }

    for (int i=0; i<parent->nInputs; i++) {
        if (This->pU[i] == pNULL) return false;
    }

    for (int i=0; i<parent->nOutputs; i++)
        if (This->pY[i] == pNULL) return false;

    return true;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    PointerControlBlock *This = POINTERCONTROLBLOCK(obj);

    This->pU = pNULL;
    This->pY = pNULL;
}

PointerControlBlock* PointerControlBlock_new(void)
{
    Object *obj = object_new(TYPE_POINTERCONTROLBLOCK);
    return (PointerControlBlock*)obj;
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
    .name = TYPE_POINTERCONTROLBLOCK,
    .parent = TYPE_CONTROLBLOCK,
    .instance_size = sizeof(PointerControlBlock),
    .abstract = false,
    .class_size = sizeof(PointerControlBlockClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void PointerControlBlock_register(void)
{
    type_register_static(&type_info);
}
