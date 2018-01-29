//
//
// DC_UnstableFsmState.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "DC_UnstableFsmState.h"



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * This method returns without doing anything.
 * @see FsmState#doContinue
 */
static void doContinue(void *obj)
{
    return;
}

/**
 * This method always returns "state has terminated".
 * @see FsmState#doContinue
 * @return always return true
 */
static bool isFinished(void *obj)
{
    return true;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
	CC_RootObject_setClassId((CC_RootObject*)obj, ID_UNSTABLEFSMSTATE);
}

DC_UnstableFsmState* DC_UnstableFsmState_new(void)
{
    Object *obj = object_new(TYPE_DC_UNSTABLEFSMSTATE);
    return (DC_UnstableFsmState*)obj;
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
    fsc->isFinished = isFinished;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_UNSTABLEFSMSTATE,
    .parent = TYPE_FSMSTATE,
    .instance_size = sizeof(DC_UnstableFsmState),
    .abstract = false,
    .class_size = sizeof(DC_UnstableFsmStateClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_UnstableFsmState_register(void)
{
    type_register_static(&type_info);
}
