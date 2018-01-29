//
//
// DC_ManoeuvrePunctualAction.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "../Manoeuvre/CC_ManoeuvreManager.h"
#include "DC_ManoeuvrePunctualAction.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_ManoeuvrePunctualAction_setManoeuvreManager
(
    DC_ManoeuvrePunctualAction *This, 
    CC_ManoeuvreManager *pManMan
)
{
    assert(pManMan != pNULL);
    This->pManoeuvreManager = pManMan;
}

CC_ManoeuvreManager* DC_ManoeuvrePunctualAction_getManoeuvreManager
(
    const DC_ManoeuvrePunctualAction *This
)
{
    return This->pManoeuvreManager;
}

void DC_ManoeuvrePunctualAction_setManoeuvre
(
    DC_ManoeuvrePunctualAction *This, 
    Manoeuvre *pMan
)
{
    assert(pMan != pNULL);
    This->pManoeuvre = pMan;
}

Manoeuvre* DC_ManoeuvrePunctualAction_getManoeuvre
(
    const DC_ManoeuvrePunctualAction *This
)
{
    return This->pManoeuvre;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Perform a class-specific configuration check: verify that the manoeuvre
 * and manoeuvre manager have been loaded.
 * @return true if the object is configured, false otherwise
 */
static bool isObjectConfigured(void *obj)
{
    PunctualActionClass *pac = GET_CLASS(TYPE_PUNCTUALACTION);
    DC_ManoeuvrePunctualAction *This = DC_MANOEUVREPUNCTUALACTION(obj);

    return ((CC_ROOTOBJECT_CLASS(pac)->isObjectConfigured(obj)) &&
            (This->pManoeuvre != pNULL) && 
            (This->pManoeuvreManager != pNULL));
}

/**
 * Load the manoeuvre in the manoeuvre manager. This method always
 * return "action successfully executed". Note that reporting of
 * possible failures
 * related to the loading or execution of the manoeuvre should be
 * the responsibility of the manoeuvre manager.
 * @see PunctualAction#execute
 * @see TD_ActionOutcome
 * @return always returns ACTION_SUCCESS
 */
static TD_ActionOutcome doAction(void *obj)
{
   DC_ManoeuvrePunctualAction *This = DC_MANOEUVREPUNCTUALACTION(obj);
   CC_ManoeuvreManagerClass *cc_mmc;

   assert((This->pManoeuvre != pNULL) && (This->pManoeuvreManager != pNULL));

   cc_mmc = CC_MANOEUVREMANAGER_GET_CLASS(This->pManoeuvreManager);
   cc_mmc->load(This->pManoeuvreManager, This->pManoeuvre);

   return ACTION_SUCCESS;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
   DC_ManoeuvrePunctualAction *This = DC_MANOEUVREPUNCTUALACTION(obj);
   This->pManoeuvre = pNULL;
   This->pManoeuvreManager = pNULL;

   CC_RootObject_setClassId((CC_RootObject*)obj, ID_MANOEUVREPUNCTUALACTION);
}

DC_ManoeuvrePunctualAction* DC_ManoeuvrePunctualAction_new(void)
{
    Object *obj = object_new(TYPE_DC_MANOEUVREPUNCTUALACTION);
    return (DC_ManoeuvrePunctualAction*)obj;
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

    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_MANOEUVREPUNCTUALACTION,
    .parent = TYPE_PUNCTUALACTION,
    .instance_size = sizeof(DC_ManoeuvrePunctualAction),
    .abstract = false,
    .class_size = sizeof(DC_ManoeuvrePunctualActionClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_ManoeuvrePunctualAction_register(void)
{
    type_register_static(&type_info);
}
