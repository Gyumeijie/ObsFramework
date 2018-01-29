//
//
// DC_NestedFsmActivatorWithExitCheck.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../FSM/CC_FSM.h"
#include "DC_NestedFsmActivatorWithExitCheck.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_NestedFsmActivatorWithExitCheck_setTargetState
(
    DC_NestedFsmActivatorWithExitCheck *This, 
    TD_FsmStateIndex targetState
)
{
	assert(targetState >= 0);
	This->targetState = targetState;
}

TD_FsmStateIndex DC_NestedFsmActivatorWithExitCheck_getTargetState
(
    DC_NestedFsmActivatorWithExitCheck *This
)
{
	assert(This->targetState >= 0);
	return This->targetState;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Return true(state can be exited) if the target FSM has reached
 * the target state.
 * @see FsmState#canExit
 * @return true if the target FSM has reached the target state
 */
static bool canExit(void *obj)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    DC_NestedFsmActivatorWithExitCheck *This = DC_NESTEDFSMACTIVATORWITHEXITCHECK(obj);

	assert(cc_roc->isObjectConfigured(obj));

    CC_FSM *targetFsm = DC_NestedFsmActivator_getTargetFsm(obj);

	return (CC_FSM_getCurrentState(targetFsm) == This->targetState);
}

/**
 * Perform a class-specific configuration check: verify that the base
 * class is configured and that the target state has been loaded.
 * @return true if the object is configured, false otherwise.
 */
static bool isObjectConfigured(void *obj)
{
    DC_NestedFsmActivatorWithExitCheck *This = DC_NESTEDFSMACTIVATORWITHEXITCHECK(obj);
    DC_NestedFsmActivatorClass *dc_nfac = GET_CLASS(TYPE_DC_NESTEDFSMACTIVATOR);

	return ((CC_ROOTOBJECT_CLASS(dc_nfac)->isObjectConfigured(obj)) && 
            (This->targetState >= 0));
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    DC_NestedFsmActivatorWithExitCheck *This = DC_NESTEDFSMACTIVATORWITHEXITCHECK(obj);
	This->targetState = -1;

	CC_RootObject_setClassId((CC_RootObject*)obj, ID_NESTEDFSMACTIVATORWITHEXITCHECK);
}

DC_NestedFsmActivatorWithExitCheck* DC_NestedFsmActivatorWithExitCheck_new(void)
{
    Object *obj = object_new(TYPE_DC_NESTEDFSMACTIVATORWITHEXITCHECK);
    return (DC_NestedFsmActivatorWithExitCheck*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    FsmStateClass *fsc = FSMSTATE_CLASS(oc);
    fsc->canExit = canExit;

    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_NESTEDFSMACTIVATORWITHEXITCHECK,
    .parent = TYPE_DC_NESTEDFSMACTIVATOR,
    .instance_size = sizeof(DC_NestedFsmActivatorWithExitCheck),
    .abstract = false,
    .class_size = sizeof(DC_NestedFsmActivatorWithExitCheckClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_NestedFsmActivatorWithExitCheck_register(void)
{
    type_register_static(&type_info);
}
