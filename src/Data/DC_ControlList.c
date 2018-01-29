//
//
// DC_ControlList.c
//
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "../Event/DC_EventRepository.h"
#include "../Base/CC_RootObject.h"
#include "DC_ControlList.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_ControlList_setListSize(DC_ControlList *This, unsigned int listSize)
{
    assert((listSize != 0) && (This->listSize == 0));

    This->listSize = listSize;
    This->controlBlockList = g_malloc(listSize*sizeof(ControlBlock*));

    for (unsigned int i=0; i<listSize; i++) {
        This->controlBlockList[i] = pNULL;
    }
}

unsigned int DC_ControlList_getListSize(const DC_ControlList *This)
{
	return This->listSize;
}

void DC_ControlList_setControlBlock(DC_ControlList *This, 
                                    unsigned int i,
                                    ControlBlock *item)
{
	assert((item != pNULL) && (i < This->listSize));

	if (i < This->listSize) {
		This->controlBlockList[i] = item;
    } else {
        DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
        DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
		dc_erc->create(dc_er, (CC_RootObject*)This, EVT_ILLEGAL_CL);
    }
}

ControlBlock* DC_ControlList_getControlBlock(const DC_ControlList *This, 
                                             unsigned int i)
{
	assert(i < This->listSize);

    return This->controlBlockList[i];
}

void DC_ControlList_reset(DC_ControlList *This)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(This);
    assert(cc_roc->isObjectConfigured(This));

    for (unsigned int i=0; i<This->listSize; i++) {
        ControlBlock *cb = This->controlBlockList[i];
        ControlBlockClass *cbc = CONTROLBLOCK_GET_CLASS(cb);
        cbc->reset(cb);
    }
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Encapsulate an <i>execution check</i> that always returns
 * "control action can execute".
 * @see ConditionalPunctualAction#doAction
 * @return always returns true.
 */
static bool canExecute(void *obj)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    assert(cc_roc->isObjectConfigured(obj));

    return true;
}

/**
 * Send a propagate request to the target control block. This
 * method always returns: "ACTION_SUCCESS"
 * @see ConditionalPunctualAction#doAction
 * @return always returns ACTION_SUCCESS
 */
static TD_ActionOutcome doConditionalAction(void *obj)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    DC_ControlList *This = DC_CONTROLLIST(obj);
    
    assert(cc_roc->isObjectConfigured(obj));

    for (unsigned int i=0; i<This->listSize; i++) {
        ControlBlock *cb = This->controlBlockList[i];
        ControlBlockClass *cbc = CONTROLBLOCK_GET_CLASS(cb);
        cbc->propagate(cb);
    }

    return ACTION_SUCCESS;
}

/**
 * Perform a class-specific configuration check on the control
 * list: verify that the size of the list of control blocks has
 * a value greater than zero and that all the entries in the list
 * have been loaded with control blocks.
 * @return true if the control list is configured, false otherwise.
 */
static bool isObjectConfigured(void *obj)
{
    ConditionalPunctualActionClass *cpac = GET_CLASS(TYPE_CONDITIONALPUNCTUALACTION);
    DC_ControlList *This = DC_CONTROLLIST(obj);


    if (!(CC_ROOTOBJECT_CLASS(cpac)->isObjectConfigured(obj)) || 
         (This->listSize == 0)) 
    {
        return NOT_CONFIGURED;
    }

    for (unsigned int i=0; i<This->listSize; i++) { 
        if (This->controlBlockList[i] == pNULL) return NOT_CONFIGURED;
    }

    return CONFIGURED;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    DC_ControlList *This = DC_CONTROLLIST(obj);
    This->listSize = 0;
    This->controlBlockList = pNULL;

    CC_RootObject_setClassId((CC_RootObject*)obj, ID_CONTROLLIST);
}

DC_ControlList* DC_ControlList_new(void)
{
    Object *obj = object_new(TYPE_DC_CONTROLLIST);
    return (DC_ControlList*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    ConditionalPunctualActionClass *cpac = CONDITIONALPUNCTUALACTION_CLASS(oc);
    cpac->canExecute = canExecute;
    cpac->doConditionalAction = doConditionalAction;

    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc); 
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_CONTROLLIST,
    .parent = TYPE_CONDITIONALPUNCTUALACTION,
    .instance_size = sizeof(DC_ControlList),
    .abstract = false,
    .class_size = sizeof(DC_ControlListClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_ControlList_register(void)
{
    type_register_static(&type_info);
}
