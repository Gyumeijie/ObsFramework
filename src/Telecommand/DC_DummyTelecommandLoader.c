//
//
// DC_DummyTelecommandLoader.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "CC_TelecommandManager.h"
#include "DC_DummyTelecommandLoader.h"

// The constant N_SAMPLE_TC was initially defined in the header file
// as follows:
//   static int const N_SAMPLE_TC = 3;
// This however gives an error with some compiler settings and was
// therefore replaced with an initialization performed in the
// constructor



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_DummyTelecommandLoader_setSampleTelecommand
(
    DC_DummyTelecommandLoader *This, 
    unsigned int i,
    Telecommand *pSampleTc)
{
    assert(i < This->N_SAMPLE_TC);
    This->pSampleTelecommand[i] = pSampleTc;
}

unsigned int DC_DummyTelecommandLoader_getAllocationCounter
(
    DC_DummyTelecommandLoader *This
)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(This);
    assert(cc_roc->isObjectConfigured(This));
    return This->allocationCounter;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Load a sample telecommand in the telecommand manager.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *      i = allocationCounter MOD 3;
 *      load i-th sample telecommand in telecommand manager;
 *      allocationCounter++;  </PRE>
 * Thus, each activation causes one sample telecommand to be loaded. The
 * three sample telecommands are loaded in a cyclical sequence.
 */
static void activate(void *obj)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    DC_DummyTelecommandLoader *This = DC_DUMMYTELECOMMANDLOADER(obj);

    assert(cc_roc->isObjectConfigured(obj));
    int i = (This->allocationCounter % This->N_SAMPLE_TC);
    This->allocationCounter++;

    CC_TelecommandManager *cc_tm = TelecommandLoader_getTelecommandManager(obj); 
    CC_TelecommandManagerClass *cc_tmc = CC_TELECOMMANDMANAGER_GET_CLASS(cc_tm);
    cc_tmc->load(cc_tm, This->pSampleTelecommand[i]);
}

/**
 * Decrement the allocation counter by 1.
 * @param pTelecommand the telecommand whose resources must be released
 */
static void release(void *obj, Telecommand *pTelecommand)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    DC_DummyTelecommandLoader *This = DC_DUMMYTELECOMMANDLOADER(obj);

    assert(cc_roc->isObjectConfigured(obj));
    assert(This->allocationCounter > 0);
    This->allocationCounter--;
}

/**
 * Perform a class-specific configuration check on the dummy telecommand
 * loader: verify that the sample telecommands have been loaded.
 * @return true if the telecommand loader is configured, false otherwise.
 */
static bool isObjectConfigured(void *obj)
{
   TelecommandLoaderClass *tclc = GET_CLASS(TYPE_TELECOMMANDLOADER);
   DC_DummyTelecommandLoader *This = DC_DUMMYTELECOMMANDLOADER(obj);

   // Check configuration of super object
   if (!CC_ROOTOBJECT_CLASS(tclc)->isObjectConfigured(obj)) {
       return NOT_CONFIGURED;
   }

   for (unsigned int i=0; i<This->N_SAMPLE_TC; i++) {
       if (This->pSampleTelecommand[i] == pNULL) {
           return NOT_CONFIGURED;
       }
   }

   return CONFIGURED;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    DC_DummyTelecommandLoader *This = DC_DUMMYTELECOMMANDLOADER(obj);
    This->N_SAMPLE_TC = 3;
    This->pSampleTelecommand = g_malloc(This->N_SAMPLE_TC*sizeof(Telecommand*));
    for (unsigned int i=0; i<This->N_SAMPLE_TC; i++) {
        This->pSampleTelecommand[i] = pNULL;
    }
    This->allocationCounter = 0;

    CC_RootObject_setClassId((CC_RootObject*)obj, ID_DUMMYTELECOMMANDLOADER);
}

DC_DummyTelecommandLoader* DC_DummyTelecommandLoader_new(void)
{
    Object *obj = object_new(TYPE_DC_DUMMYTELECOMMANDLOADER);
    return (DC_DummyTelecommandLoader*)obj; 
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
    .name = TYPE_DC_DUMMYTELECOMMANDLOADER,
    .parent = TYPE_TELECOMMANDLOADER,
    .instance_size = sizeof(DC_DummyTelecommandLoader),
    .abstract = false,
    .class_size = sizeof(DC_DummyTelecommandLoaderClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_DummyTelecommandLoader_register(void)
{
    type_register_static(&type_info);
}
