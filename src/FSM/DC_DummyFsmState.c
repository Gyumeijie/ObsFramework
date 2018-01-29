//
//
// DC_DummyFsmState.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "DC_DummyFsmState.h"



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Implement dummy continued action: the method increments the activation
 * counter by 1 returns.
 * <p>
 * @see FsmState#doContinue
 */
static void doContinue(void *obj)
{
   return;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
   CC_RootObject_setClassId((CC_RootObject*)obj, ID_DUMMYFSMSTATE);
}

DC_DummyFsmState* DC_DummyFsmState_new(void)
{
    Object *obj = object_new(TYPE_DC_DUMMYFSMSTATE);
    return (DC_DummyFsmState*)obj;
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
}

static const TypeInfo type_info = {
    .name = TYPE_DC_DUMMYFSMSTATE,
    .parent = TYPE_FSMSTATE,
    .instance_size = sizeof(DC_DummyFsmState),
    .abstract = false,
    .class_size = sizeof(DC_DummyFsmStateClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_DummyFsmState_register(void)
{
    type_register_static(&type_info);
}
