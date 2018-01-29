//
//
// PunctualActionModeManager.h
//
//
// Change Record:


#ifndef PUNCTUALACTIONMODEMANAGER_H
#define PUNCTUALACTIONMODEMANAGER_H


#include "ModeManager.h"
#include "PunctualAction.h"
#include "../Qom/object.h"


/*
 * Base abstract class for mode manager components for the punctual
 * action manager.
 * A punctual action mode manager handles one single <i>strategy</i>, which
 * is represented by a set of <i>punctual action</i> components.
 * To every operational mode, the telemetry mode manager associates 
 * a set of punctual actions. 
 * Client access the items in this set through four
 * <i>iteration methods</i>: <code>first</code>, <code>next</code>,
 * <code>isIterationFinished</code>, and <code>getPunctualAction</code>.
 * <p>
 * This is an abstract class because it specifies neither the implementation
 * mechanism for the set of punctual actions nor the mode update mechanism.
 * @todo Create a class DC_FSMPunctualActionModeManager where the mode is driven
 * by an FSM. Same thing should be done for the TelemetryModeManager
 * @see CC_PunctualActionManager
 * @see PunctualAction
 * @author Alessandro Pasetti 
 * @author Roberto Totaro
 * @version 1.0
 * @ingroup ModeManagement
 */
#define TYPE_PUNCTUALACTIONMODEMANAGER "punctualactionmodemanager"

void PunctualActionModeManager_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct PunctualActionModeManager {
    ModeManager parent;
};


struct PunctualActionModeManagerClass {
    ModeManagerClass parent_class;
 
    void (*first)(void *obj);
    void (*next)(void *obj);
    bool (*isIterationFinished)(void *obj);
    PunctualAction* (*getIterationPunctualAction)(void *obj);
};


#define PUNCTUALACTIONMODEMANAGER_GET_CLASS(obj) \
        OBJECT_GET_CLASS(PunctualActionModeManagerClass,\
                                           obj, TYPE_PUNCTUALACTIONMODEMANAGER)

#define PUNCTUALACTIONMODEMANAGER_CLASS(klass) \
        OBJECT_CLASS_CHECK(PunctualActionModeManagerClass,\
                                         klass, TYPE_PUNCTUALACTIONMODEMANAGER)

#define PUNCTUALACTIONMODEMANAGER(obj) \
        OBJECT_CHECK(PunctualActionModeManager,\
                                           obj, TYPE_PUNCTUALACTIONMODEMANAGER)


PunctualActionModeManager* PunctualActionModeManager_new(void);

#endif
