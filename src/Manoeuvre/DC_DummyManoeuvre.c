//
//
// DC_DummyManoeuvre.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "DC_DummyManoeuvre.h"



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Implement a dummy continuation action. This method returns without
 * doing anything.
 * @see Manoeuvre#doContinue
 */
static void doInternalContinue(void *obj)
{
    assert(Manoeuvre_isInUse(obj) && Manoeuvre_isExecuting(obj));
}

/**
 * Implement a dummy termination check that always returns 
 * "manoeuvre can terminate". 
 * @return true if the manoeuvre has terminated execution
 */
static bool isFinished(void *obj)
{
    assert(Manoeuvre_isInUse(obj) && Manoeuvre_isExecuting(obj));
    return MAN_HAS_TERMINATED;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    CC_RootObject_setClassId((CC_RootObject*)obj, ID_DUMMYMANOEUVRE);
}

DC_DummyManoeuvre* DC_DummyManoeuvre_new(void)
{
    Object *obj = object_new(TYPE_DC_DUMMYMANOEUVRE);
    return (DC_DummyManoeuvre*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    ManoeuvreClass *mc = MANOEUVRE_CLASS(oc);

    mc->doInternalContinue = doInternalContinue;
    mc->isFinished = isFinished;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_DUMMYMANOEUVRE,
    .parent = TYPE_MANOEUVRE,
    .instance_size = sizeof(DC_DummyManoeuvre),
    .abstract = false,
    .class_size = sizeof(DC_DummyManoeuvreClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_DummyManoeuvre_register(void)
{
    type_register_static(&type_info);
}
