//
//
// DC_NestedFsmActivatorWithEndState.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../FSM/CC_FSM.h"
#include "DC_NestedFsmActivatorWithEndState.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_NestedFsmActivatorWithEndState_setTargetState
(
    DC_NestedFsmActivatorWithEndState *This, 
    TD_FsmStateIndex targetState
)
{
	assert(targetState >= 0);
	This->targetState = targetState;
}

TD_FsmStateIndex DC_NestedFsmActivatorWithEndState_getTargetState
(
    DC_NestedFsmActivatorWithEndState *This
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
 * Return true if the target FSM has reached the target state.
 * @see FsmState#isFinished
 * @return true if the target FSM has reached the target state
 */
static bool isFinished(void *obj)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    DC_NestedFsmActivatorWithEndState *This = DC_NESTEDFSMACTIVATORWITHENDSTATE(obj);

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
    DC_NestedFsmActivatorClass *dc_nfac = GET_CLASS(TYPE_DC_NESTEDFSMACTIVATOR);
    DC_NestedFsmActivatorWithEndState *This = DC_NESTEDFSMACTIVATORWITHENDSTATE(obj);

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
    DC_NestedFsmActivatorWithEndState *This = DC_NESTEDFSMACTIVATORWITHENDSTATE(obj);

	This->targetState = -1;
	CC_RootObject_setClassId((CC_RootObject*)obj, ID_NESTEDFSMACTIVATORWITHENDSTATE);
}

DC_NestedFsmActivatorWithEndState* DC_NestedFsmActivatorWithEndState_new(void)
{
    Object *obj = object_new(TYPE_DC_NESTEDFSMACTIVATORWITHENDSTATE);
    return (DC_NestedFsmActivatorWithEndState*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    FsmStateClass *fsc = FSMSTATE_CLASS(oc);
    fsc->isFinished = isFinished;

    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_NESTEDFSMACTIVATORWITHENDSTATE,
    .parent = TYPE_DC_NESTEDFSMACTIVATOR,
    .instance_size = sizeof(DC_NestedFsmActivatorWithEndState),
    .abstract = false,
    .class_size = sizeof(DC_NestedFsmActivatorWithEndStateClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_NestedFsmActivatorWithEndState_register(void)
{
    type_register_static(&type_info);
}
