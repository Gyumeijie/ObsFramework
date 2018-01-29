//
//
// ModeManager.h
//
//
// Change Record:


#ifndef MODEMANAGER_H
#define MODEMANAGER_H


#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "../Qom/object.h"


/*
 * Base class from which all classes encapsulating mode managers are
 * derived.
 * Conceptually, a mode manager is characterized by:<ul>
 * <li>A set of <i>operational modes</i> of which, at any given time,
 * one and only one is the <i>current operational mode</i>,</li>
 * <li>A set of <i>strategies</i>,</li>
 * <li>For each strategy, a set of <i>implementations</i> of which,
 * at any given time, one and only one is the <i>current implementation</i>,
 * and</li>
 * <li>An <i>update mechanism</i> for controlling the change in the current
 * operational mode.</li>
 * </ul>
 * This is an abstract class because it only defines the management of
 * the operational mode. All other aspects listed above are defined and/or
 * implemented by subclasses.
 * <p>
 * Changes in operational mode are recorded through an event report.
 * It is possible to selectively disable transitions to certain
 * operational modes or to disable all mode transitions.
 * <p>
 * An initialization sequence for this class consists of the following
 * steps: <ul>
 * <li>Set the number of modes with method <code>setNumberOfModes</code></li>
 * <li>Set the default mode with method <code>setDefaultMode</code></li>
 * <li>Reset the component by calling method <code>reset</code></li>
 * </ul>
 * The above operations must be performed in the order given.
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 * @ingroup Base
 * @ingroup ModeManagement
 */
#define TYPE_MODEMANAGER "modemanager"

void ModeManager_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct ModeManager {
    CC_RootObject parent;

    bool *enabledStatus;    // this is an array
    bool transitionsEnabled;
    TD_Mode numberOfModes;
    TD_Mode currentMode;
    TD_Mode defaultMode;
};


struct ModeManagerClass {
    CC_RootObjectClass parent_class;
 
    void (*reset)(void *obj);
 
    void (*update)(void *obj);
    void (*allocateMemory)(void *obj, TD_Mode numberOfModes);
};


#define MODEMANAGER_GET_CLASS(obj) \
        OBJECT_GET_CLASS(ModeManagerClass, obj, TYPE_MODEMANAGER)

#define MODEMANAGER_CLASS(klass) \
        OBJECT_CLASS_CHECK(ModeManagerClass, klass, TYPE_MODEMANAGER)

#define MODEMANAGER(obj) \
        OBJECT_CHECK(ModeManager, obj, TYPE_MODEMANAGER)


ModeManager* ModeManager_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the number of modes of the mode manager.
 * This is an initialization method. It should only be called once.
 * Successive calls have no effect. The number of modes should be
 * greater than zero.
 * <p>
 * A pseudo-code implementation for this method is as follows: <PRE>
 *      . . .    // allocate memory for internal data structures
 *      ModeManager_allocateMemor y(ModeManager *This, numberOfModes); </PRE>
 * Concrete mode managers will normally use some internal data
 * structure to hold mode-related information. The memory for this
 * data structure must be allocated when the component is initialized.
 * The call to the and abstract method <code>allocateMemory</code>
 * can be used for this purpose.
 * <p>
 * This is an initialization method. It should be called only once. Only
 * positive number of modes are legal.
 * @see allocateMemory
 * @param numberOfModes the number of modes
 */
void ModeManager_setNumberOfModes(ModeManager *This, TD_Mode numberOfModes);

/**
 * Set the default mode of the mode manager.
 * The default mode of the mode manager is its operational mode at the
 * end of the configuration process or after a
 * call to method <code>rest</code>. The default mode argument must lie in the
 * interval [0, N-1] where N is the total number of modes. If an illegal
 * default mode is used, then the method generates an event report of type
 * EVT_ILLEGAL_MM and returns without taking any action.
 * @param defaultMode the default mode
 */
void ModeManager_setDefaultMode(ModeManager *This, TD_Mode defaultMode);

/**
 * Enable/disable all mode transitions.
 * When mode transitions are disabled, the current operational mode is
 * never changed.
 * @see #update
 * @param enabled the transition are disabled if false, enabled if true
 */
void ModeManager_setTransitionEnableStatus(ModeManager *This, bool enabled);

/**
 * Enable/disable transitions to the toMode-th operational mode.
 * The toMode argument must lie in the
 * interval [0, N-1] where N is the total number of modes. If an illegal
 * default mode is used, then the method generates an event report of type
 * EVT_ILLEGAL_MM and returns without taking any action.
 * @see #update
 * @param toMode the operational mode to which transitions are enabled/disabled
 * @param enabled the transition is disabled if false, enabled if true
 */
void ModeManager_setTransitionEnableStatusToMode
(
    ModeManager *This, 
    TD_Mode toMode, 
    bool enabled
);

/**
 * Check whether mode transitions are enabled.
 * @see #setTransitionEnableStatus
 * @return true if mode transitions are enabled, false otherwise
 */
bool ModeManager_isTransitionEnabled(const ModeManager *This);

/**
 * Check whether transitions to the argument target mode are enabled.
 * @see #setTransitionEnableStatus
 * @param toMode the target mode
 * @return true if a transition into the target mode is enabled
 */
bool ModeManager_isTransitionEnabledToMode(const ModeManager *This, TD_Mode toMode);

/**
 * Return the current operational mode.
 * @return the current mode
 */
TD_Mode ModeManager_getCurrentMode(const ModeManager *This);

/**
 * Return the number of operational mode.
 * @return the number of operational modes
 */
TD_Mode ModeManager_getNumberOfModes(const ModeManager *This);

/**
 * Change the operational mode the mode manager.
 * This method is responsible for managing the event reporting
 * mechanism and the mode transition inhibition mechanism.
 * All mode changes should occurr through this method. This in
 * particular applies to changes commanded by implementations of
 * method <code>update</code> in derived classes.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *   ModeManager_if(newMode != currentMode)
 *      ModeManager_if(ModeManager_isTransitionEnabled(void) && ModeManager_isTransitionEnabled(newMode))
 *        currentMode = newMode;
 *        ModeManager_createEventRepor t(ModeManager *This, EVT_MOD_TRANS_PERFORMED);
 *      else
 *        ModeManager_createEventRepor t(ModeManager *This, EVT_MOD_TRANS_INHIBITED);</PRE>
 * where <code>currentMode</code> is the operational mode at the
 * time the method is called and <code>instanceId</code> is the
 * instance identifier of the mode manager component.
 * @see #update
 * @see TD_EventType
 * @see CC_RootObject
 * @param newMode the new operational mode
 */
void ModeManager_setMode(ModeManager *This, TD_Mode newMode);


#endif
