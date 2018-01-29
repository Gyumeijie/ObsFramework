//
//
// DC_SimplePunctualActionModeManager.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "DC_SimplePunctualActionModeManager.h"



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Since this is a fixed-mode mode manager, this method returns without
 * taking any action.
 */
static void update(void *obj){}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    ModeManager_setNumberOfModes((ModeManager*)obj, 1);
    ModeManager_setDefaultMode((ModeManager*)obj, 0);
    CC_RootObject_setClassId((CC_RootObject*)obj, ID_SIMPLEPUNCTUALACTIONMODEMANAGER);
}

DC_SimplePunctualActionModeManager* DC_SimplePunctualActionModeManager_new(void)
{
    Object *obj = object_new(TYPE_DC_SIMPLEPUNCTUALACTIONMODEMANAGER);
    return (DC_SimplePunctualActionModeManager*)obj;
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
}

static const TypeInfo type_info = {
    .name = TYPE_DC_SIMPLEPUNCTUALACTIONMODEMANAGER,
    .parent = TYPE_PUNCTUALACTIONLISTMODEMANAGER,
    .instance_size = sizeof(DC_SimplePunctualActionModeManager),
    .abstract = false,
    .class_size = sizeof(DC_SimplePunctualActionModeManagerClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_SimplePunctualActionModeManager_register(void)
{
    type_register_static(&type_info);
}
