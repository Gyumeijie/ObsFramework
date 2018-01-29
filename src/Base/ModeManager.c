//
//
// ModeManager.c
//
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../Event/DC_EventRepository.h"
#include "../Base/CC_RootObject.h"
#include "ModeManager.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void ModeManager_setNumberOfModes(ModeManager *This, TD_Mode numberOfModes)
{
    ModeManagerClass *mmc = MODEMANAGER_GET_CLASS(This);

    assert(This->numberOfModes == 0);  // should be called only once
    assert(numberOfModes > 0);

    This->numberOfModes = numberOfModes;
    This->enabledStatus =  g_malloc(sizeof(bool)*numberOfModes);
    for (TD_Mode i=0; i<numberOfModes; i++) {
       This->enabledStatus[i] = ENABLED;
    }

    mmc->allocateMemory(This, numberOfModes);
}

void ModeManager_setDefaultMode(ModeManager *This, TD_Mode defaultMode)
{
    assert((defaultMode >= 0) && (defaultMode < This->numberOfModes));

    if ((defaultMode >= 0) && (defaultMode < This->numberOfModes)) {
        This->defaultMode = defaultMode;
    } else {
        DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
        DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er); 
        dc_erc->create(dc_er, (CC_RootObject*)This, EVT_ILLEGAL_MM);
    }
}

void ModeManager_setTransitionEnableStatus(ModeManager *This, bool enabled)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(This);

    assert(cc_roc->isObjectConfigured(This));
    This->transitionsEnabled = enabled;
}

void ModeManager_setTransitionEnableStatusToMode
(
    ModeManager *This, 
    TD_Mode toMode, 
    bool enabled
)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(This);

    assert(cc_roc->isObjectConfigured(This));
    assert((toMode >= 0) && (toMode < This->numberOfModes));

    if ((toMode >= 0) && (toMode < This->numberOfModes)) {
        This->enabledStatus[toMode] = enabled;
    } else {
        DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
        DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er); 
        dc_erc->create(dc_er, (CC_RootObject*)This, EVT_ILLEGAL_MM);
    }
}

bool ModeManager_isTransitionEnabled(const ModeManager *This)
{
    return This->transitionsEnabled;
}

bool ModeManager_isTransitionEnabledToMode(const ModeManager *This, TD_Mode toMode)
{
    assert(toMode < This->numberOfModes);
    assert(toMode >= 0);

    return This->enabledStatus[toMode];
}

TD_Mode ModeManager_getCurrentMode(const ModeManager *This)
{
    assert(This->numberOfModes > 0); 
    assert(This->currentMode >= 0);
    assert(This->currentMode < This->numberOfModes);

    return This->currentMode;
}

TD_Mode ModeManager_getNumberOfModes(const ModeManager *This)
{
    return This->numberOfModes;
}

void ModeManager_setMode(ModeManager *This, TD_Mode newMode)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(This);
    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er); 

    assert((newMode >= 0) && (newMode < This->numberOfModes));
    assert(cc_roc->isObjectConfigured(This));

    if (newMode == This->currentMode) return;

    if (ModeManager_isTransitionEnabled(This) && 
        ModeManager_isTransitionEnabledToMode(This, newMode)) {
        This->currentMode = newMode;
        dc_erc->create(dc_er, (CC_RootObject*)This, EVT_MOD_TRANS_PERFORMED);
    } else {
        dc_erc->create(dc_er, (CC_RootObject*)This, EVT_MOD_TRANS_INHIBITED);
    }
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Enable all mode transitions and set the operational mode to the default
 * mode. This method is declared virtual so as to allow concrete mode managers
 * to define more specific reset operations.
 */
static void reset(void *obj)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    ModeManager *This = MODEMANAGER(obj);

    assert(cc_roc->isObjectConfigured(obj));

    This->currentMode = This->defaultMode;
    for (int i=0; i<This->numberOfModes; i++) {
        This->enabledStatus[i] = ENABLED;
    }

    This->transitionsEnabled = ENABLED;
}

/**
 * Perform a class-specific configuration check on a mode manager: verify
 * that the number of modes and the default modes have legal values.
 * @return true if the object is configured, false otherwise
 */
static bool isObjectConfigured(void *obj)
{
    CC_RootObjectClass *cc_roc = GET_CLASS(TYPE_CC_ROOTOBJECT);
    ModeManager *This = MODEMANAGER(obj);

    return ((cc_roc->isObjectConfigured(obj)) &&
            (This->numberOfModes > 0) && 
            (This->defaultMode >= 0));
}



///////////////////////////////////////////////////////////////////////////////
//
//                    pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Execute the <i>update operation</i> for the mode manager.
 * This method is declared abstract because the update mechanism is
 * application-specific and must be defined by concrete subclasses.
 * A pseudo-code implementation for a typical implementation of this
 * method takes the following form: <PRE>
 *   newMode = . . .    // compute new operational mode;
 *   setMode(newMode);</PRE>
 * Thus, the method computes the new mode and then uses the
 * <code>setMode</code> method to attempt a mode update. Note that
 * it is this latter method that is responsible for enforcing
 * the mode transition inhibitions and for reporting mode changes
 * as events.
 * <p>
 * This method implements the <i>update</i> basic
 * operation of mode managers.
 * @see #setMode
 */
static void update(void *obj)
{
    // this is automate genenrated by converter
}

/**
 * Allocate the memory for the internal data structures whose size
 * depends on the number of modes.
 * @see #setNumberOfModes
 * @param numberOfModes the number of modes
 */
static void allocateMemory(void *obj, TD_Mode numberOfModes)
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
    ModeManager *This = MODEMANAGER(obj);

    This->enabledStatus = pNULL;
    This->transitionsEnabled = ENABLED;
    This->numberOfModes = 0;
    This->currentMode = -1;
    This->defaultMode = -1;
}

ModeManager* ModeManager_new(void)
{
    Object *obj = object_new(TYPE_MODEMANAGER);
    return (ModeManager*)obj;
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
    mmc->reset = reset;

    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_MODEMANAGER,
    .parent = TYPE_CC_ROOTOBJECT,
    .instance_size = sizeof(ModeManager),
    .abstract = true,
    .class_size = sizeof(ModeManagerClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void ModeManager_register(void)
{
    type_register_static(&type_info);
}
