//
//
// DC_DummyModeManager.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "DC_DummyModeManager.h"
#include "ModeManager.h"



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Cycle through the operational mode. Let N be the number of modes
 * and C be the current mode. If C is smaller than(N-1), then this
 * method returns C+1. Otherwise it returns 0.
 * @see ModeManager#Update
 * @return returns the update operational mode
 */
static void update(void *obj)
{
    TD_Mode curMode = ModeManager_getCurrentMode(obj);
    TD_Mode nModes  = ModeManager_getNumberOfModes(obj);

    if (curMode < (nModes - 1)) {
        ModeManager_setMode(obj, (curMode + 1));
    } else {
        ModeManager_setMode(obj, 0);
    }
}

/**
 * This method returns without taking any action. No action is
 * required because this implementation of a mode manager does not
 * use any internal data structures.
 */
static void allocateMemory(void *obj, TD_Mode numberOfModes)
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
    CC_RootObject_setClassId((CC_RootObject*)obj, ID_DUMMYMODEMANAGER);
}

DC_DummyModeManager* DC_DummyModeManager_new(void)
{
    Object *obj = object_new(TYPE_DC_DUMMYMODEMANAGER);
    return (DC_DummyModeManager*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    ModeManagerClass *mmc = MODEMANAGER_CLASS(oc);
    mmc->update = update;
    mmc->allocateMemory = allocateMemory;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_DUMMYMODEMANAGER,
    .parent = TYPE_MODEMANAGER,
    .instance_size = sizeof(DC_DummyModeManager),
    .abstract = false,
    .class_size = sizeof(DC_DummyModeManagerClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_DummyModeManager_register(void)
{
    type_register_static(&type_info);
}
