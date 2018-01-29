//
//
// DC_DummyPunctualAction.c
//
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "DC_DummyPunctualAction.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

unsigned int DC_DummyPunctualAction_getActivationCounter
(
    const DC_DummyPunctualAction *This
)
{
    return This->counter;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * This method increments the activation counter and returns a code
 * of "action successful".
 * @see PunctualAction#execute
 * @return always returns an "action successful" code
 */
static TD_ActionOutcome doAction(void *obj)
{
    DC_DummyPunctualAction *This = DC_DUMMYPUNCTUALACTION(obj);
    ++This->counter;

    return ACTION_SUCCESS;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    DC_DummyPunctualAction *This = DC_DUMMYPUNCTUALACTION(obj);
    This->counter = 0;

    CC_RootObject_setClassId((CC_RootObject*)obj, ID_DUMMYPUNCTUALACTION);
}

DC_DummyPunctualAction* DC_DummyPunctualAction_new(void)
{
    Object *obj = object_new(TYPE_DC_DUMMYPUNCTUALACTION);
    return (DC_DummyPunctualAction*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    PunctualActionClass *pac = PUNCTUALACTION_CLASS(oc);
    pac->doAction = doAction;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_DUMMYPUNCTUALACTION,
    .parent = TYPE_PUNCTUALACTION,
    .instance_size = sizeof(DC_DummyPunctualAction),
    .abstract = false,
    .class_size = sizeof(DC_DummyPunctualActionClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_DummyPunctualAction_register(void)
{
    type_register_static(&type_info);
}
