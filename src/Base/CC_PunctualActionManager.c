//
//
// CC_PunctualActionManager.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "PunctualActionModeManager.h"
#include "CC_PunctualActionManager.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void CC_PunctualActionManager_setPunctualActionModeManager
(
    CC_PunctualActionManager *This, 
    PunctualActionModeManager *pModeManager
)
{
    assert(pModeManager);

    This->pModeManager = pModeManager;
}

PunctualActionModeManager* CC_PunctualActionManager_getPunctualActionModeManager
(
    const CC_PunctualActionManager *This
)
{
    return This->pModeManager;
}

void CC_PunctualActionManager_activate(CC_PunctualActionManager *This)
{
    assert(This->pModeManager);

    PunctualActionModeManagerClass *pammc;
    PunctualAction *pa;
    PunctualActionModeManager* const pModeManager = This->pModeManager;  

    pammc= PUNCTUALACTIONMODEMANAGER_GET_CLASS(pModeManager);
    for (pammc->first(pModeManager);
              !pammc->isIterationFinished(pModeManager);
                   pammc->next(pModeManager)) 
    {
        pa = pammc->getIterationPunctualAction(pModeManager);
        PunctualAction_execute(pa);
    }
    
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Perform a class-specific configuration check on the punctual action
 * manager: verify that the punctual action mode manager
 * has been loaded.
 * @return true if the punctual action manager is configured, false otherwise.
 */
static bool isObjectConfigured(void *obj)
{
    CC_PunctualActionManager *This = CC_PUNCTUALACTIONMANAGER(obj);
    return (This->pModeManager != pNULL);
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    CC_PunctualActionManager *This = CC_PUNCTUALACTIONMANAGER(obj);
    This->pModeManager = pNULL;

    CC_RootObject_setClassId((CC_RootObject*)obj, ID_PUNCTUALACTIONMANAGER);
}

CC_PunctualActionManager* CC_PunctualActionManager_new(void)
{
    Object *obj = object_new(TYPE_CC_PUNCTUALACTIONMANAGER);
    return (CC_PunctualActionManager*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_CC_PUNCTUALACTIONMANAGER,
    .parent = TYPE_CC_ROOTOBJECT,
    .instance_size = sizeof(CC_PunctualActionManager),
    .abstract = false,
    .class_size = sizeof(CC_PunctualActionManagerClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void CC_PunctualActionManager_register(void)
{
    type_register_static(&type_info);
}
