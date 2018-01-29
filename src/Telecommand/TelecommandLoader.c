//
//
// TelecommandLoader.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "TelecommandLoader.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void TelecommandLoader_setTelecommandManager
(
    TelecommandLoader *This, 
    CC_TelecommandManager *pTcManager
)
{
    This->pTelecommandManager = pTcManager;
}

CC_TelecommandManager* TelecommandLoader_getTelecommandManager
(
    TelecommandLoader *This
)
{
    assert(This->pTelecommandManager != pNULL);
    return This->pTelecommandManager;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Perform a class-specific configuration check on the telecommand
 * loader: verify that the telecommand manager has been loaded.
 * @return true if the telecommand loader is configured, false otherwise.
 */
static bool isObjectConfigured(void *obj)
{
    CC_RootObjectClass *cc_roc = GET_CLASS(TYPE_CC_ROOTOBJECT); 
    TelecommandLoader *This = TELECOMMANDLOADER(obj);

    return (cc_roc->isObjectConfigured(obj) &&
            (This->pTelecommandManager != pNULL));
}



///////////////////////////////////////////////////////////////////////////////
//
//                    pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Check whether a telecommand has been received and, if so, construct
 * the <CODE>Telecommand</CODE> object to represent
 * it and load it in the telecommand manager.
 * This is an abstract method because the way in which telecommands are
 * received and the way in which the
 * corresponding objects are constructed is application-specific.
 */
static void activate(void *obj)
{
    // this is automate genenrated by converter
}

/**
 * Release the resources that the telecommand loader had allocated to the
 * argument telecommand.
 * This method should be called after the argument telecommand object has
 * been executed to allow the
 * telecommand loader to release any resources that it had allocated to
 * the telecommand object when it created it.
 * This method would normally be called by the telecommand manager.
 * @see CC_TelecommandManager#activate
 * @param pTelecommand the telecommand whose resources must be released
 */
static void release(void *obj, Telecommand* pTelecommand)
{
    // this is automate genenrated by converter
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    TelecommandLoader *This = TELECOMMANDLOADER(obj);
    This->pTelecommandManager = pNULL;
}

TelecommandLoader* TelecommandLoader_new(void)
{
    Object *obj =object_new(TYPE_TELECOMMANDLOADER);
    return (TelecommandLoader*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    TelecommandLoaderClass *tlc = TELECOMMANDLOADER_CLASS(oc);
    tlc->activate = activate;
    tlc->release = release;

    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_TELECOMMANDLOADER,
    .parent = TYPE_CC_ROOTOBJECT,
    .instance_size = sizeof(TelecommandLoader),
    .abstract = true,
    .class_size = sizeof(TelecommandLoaderClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TelecommandLoader_register(void)
{
    type_register_static(&type_info);
}
