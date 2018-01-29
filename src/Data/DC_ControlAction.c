//
//
// DC_ControlAction.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "../Base/ConditionalPunctualAction.h"
#include "ControlBlock.h"
#include "DC_ControlAction.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_ControlAction_setTargetControlBlock(DC_ControlAction *This, 
                                            ControlBlock *pBlock)
{
    assert(pBlock != pNULL);
    This->pTargetControlBlock = pBlock;
}

ControlBlock* DC_ControlAction_getTargetControlBlock(DC_ControlAction *This)
{
    return This->pTargetControlBlock;
}

void DC_ControlAction_reset(DC_ControlAction *This)
{
    assert(This->pTargetControlBlock != pNULL);
    
    ControlBlockClass *cbc = CONTROLBLOCK_GET_CLASS(This->pTargetControlBlock);
    cbc->reset(This->pTargetControlBlock);
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
    return true;
}

/**
 * Send a propagate request to the target control block. This
 * method always returns: "ACTION_SUCCESS"
 * @see ConditionalPunctualAction#doAction
 * @return the outcome code of the punctual action
 */
static TD_ActionOutcome doConditionalAction(void *obj)
{
    DC_ControlAction *This = DC_CONTROLACTION(obj);
    ControlBlockClass *cbc = CONTROLBLOCK_GET_CLASS(This->pTargetControlBlock);

    assert(This->pTargetControlBlock != pNULL);
    cbc->propagate(This->pTargetControlBlock);
    return ACTION_SUCCESS;
}

/**
 * Perform a class-specific configuration check on a control action. It is
 * verified that the target control block has been loaded.
 */
static bool isObjectConfigured(void *obj)
{
   ConditionalPunctualActionClass *cpac = GET_CLASS(TYPE_CONDITIONALPUNCTUALACTION);
   DC_ControlAction *This = DC_CONTROLACTION(obj);
   
   return (CC_ROOTOBJECT_CLASS(cpac)->isObjectConfigured(obj) &&
           (This->pTargetControlBlock != pNULL));
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    DC_ControlAction *This = DC_CONTROLACTION(obj);
    This->pTargetControlBlock = pNULL;

    CC_RootObject_setClassId((CC_RootObject*)obj, ID_CONTROLACTION);
}

DC_ControlAction* DC_ControlAction_new(void)
{
    Object *obj = object_new(TYPE_DC_CONTROLACTION);
    return (DC_ControlAction*)obj;
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
    .name = TYPE_DC_CONTROLACTION,
    .parent = TYPE_CONDITIONALPUNCTUALACTION,
    .instance_size = sizeof(DC_ControlAction),
    .abstract = false,
    .class_size = sizeof(DC_ControlActionClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_ControlAction_register(void)
{
    type_register_static(&type_info);
}
