//
//
// DC_NestedFsmActivator.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "DC_NestedFsmActivator.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_NestedFsmActivator_setTargetFsm
(
    DC_NestedFsmActivator *This,
    CC_FSM *pTargetFsm
)
{
	assert(pTargetFsm != pNULL);
	This->pTargetFsm = pTargetFsm;
}

CC_FSM* DC_NestedFsmActivator_getTargetFsm(DC_NestedFsmActivator *This)
{
	assert(This->pTargetFsm != pNULL);
	return This->pTargetFsm;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Activate the target FSM.
 * @see FsmState#doContinue
 */
static void doContinue(void *obj)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    DC_NestedFsmActivator *This = DC_NESTEDFSMACTIVATOR(obj);

	assert(cc_roc->isObjectConfigured(obj));

	CC_FSM_activate(This->pTargetFsm);
}

/**
 * Reset the target FSM.
 * @see FsmState#doInit
 */
static void doInit(void *obj)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    DC_NestedFsmActivator *This = DC_NESTEDFSMACTIVATOR(obj);

	assert(cc_roc->isObjectConfigured(obj));

	CC_FSM_reset(This->pTargetFsm);
}

/**
 * Perform a class-specific configuration check:
 * verify that the target FSM has been loaded.
 * @return true if the object is configured, false otherwise.
 */
static bool isObjectConfigured(void *obj)
{
    DC_NestedFsmActivator *This = DC_NESTEDFSMACTIVATOR(obj);
    FsmStateClass *fsc = GET_CLASS(TYPE_FSMSTATE);

	return ((CC_ROOTOBJECT_CLASS(fsc)->isObjectConfigured(obj)) && 
            (This->pTargetFsm != pNULL));
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    DC_NestedFsmActivator *This = DC_NESTEDFSMACTIVATOR(obj);
	This->pTargetFsm = pNULL;

	CC_RootObject_setClassId((CC_RootObject*)obj, ID_NESTEDFSMACTIVATOR);
}

DC_NestedFsmActivator* DC_NestedFsmActivator_new(void)
{
    Object *obj = object_new(TYPE_DC_NESTEDFSMACTIVATOR);
    return (DC_NestedFsmActivator*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    FsmStateClass *fsc = FSMSTATE_CLASS(oc);
    fsc->doContinue = doContinue;
    fsc->doInit = doInit;

    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_NESTEDFSMACTIVATOR,
    .parent = TYPE_FSMSTATE,
    .instance_size = sizeof(DC_NestedFsmActivator),
    .abstract = false,
    .class_size = sizeof(DC_NestedFsmActivatorClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_NestedFsmActivator_register(void)
{
    type_register_static(&type_info);
}
