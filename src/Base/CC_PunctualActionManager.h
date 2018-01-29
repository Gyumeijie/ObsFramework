//
//
// CC_PunctualActionManager.h
//


#ifndef CC_PUNCTUALACTIONMANAGER_H
#define CC_PUNCTUALACTIONMANAGER_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "PunctualActionModeManager.h"
#include "../Qom/object.h"


/*
 * This class encapsulates a punctual action manager.
 * The punctual action manager is responsible for controlling the execution
 * of a list of punctual actions.
 * The punctual actions are encapsulated in instances of <code>PunctualAction</code>
 * components.
 * The punctual actions to be executed are provided by a <i>punctual action
 * mode manager</i> that is loaded as a plug-in component in the punctual
 * action manager.
 * <p>
 * When the punctual action manager is activated, it asks its mode manager
 * for the list of punctual actions to be executed and executes them in
 * sequence.
 * <p>
 * @see PunctualAction
 * @see PunctualActionModeManager
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 * @ingroup FunctionalityManagers
 */
#define TYPE_CC_PUNCTUALACTIONMANAGER "cc_punctualactionmanager"

void CC_PunctualActionManager_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct CC_PunctualActionManager {
    CC_RootObject parent;

    PunctualActionModeManager *pModeManager;
};


struct CC_PunctualActionManagerClass {
    CC_RootObjectClass parent_class;
};


#define CC_PUNCTUALACTIONMANAGER_GET_CLASS(obj) \
        OBJECT_GET_CLASS(CC_PunctualActionManagerClass, \
                                               obj, TYPE_CC_PUNCTUALACTIONMANAGER)

#define CC_PUNCTUALACTIONMANAGER_CLASS(klass) \
        OBJECT_CLASS_CHECK(CC_PunctualActionManagerClass, \
                                             klass, TYPE_CC_PUNCTUALACTIONMANAGER)

#define CC_PUNCTUALACTIONMANAGER(obj) \
        OBJECT_CHECK(CC_PunctualActionManager, obj, TYPE_CC_PUNCTUALACTIONMANAGER)


CC_PunctualActionManager* CC_PunctualActionManager_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Load the punctual action mode manager.
 * @param pModeManager the telemetry mode manager
 */
void CC_PunctualActionManager_setPunctualActionModeManager
(
    CC_PunctualActionManager *This, 
    PunctualActionModeManager *pModeManager
);

/**
 * Get the punctual action mode manager.
 * @return the punctual action mode manager
 */
PunctualActionModeManager* CC_PunctualActionManager_getPunctualActionModeManager
(
    const CC_PunctualActionManager *This
);

/**
 * Execute the punctual actions supplied by the mode manager.
 * A pseudocode implementation for this method is as follows: <PRE>
 *      CC_PunctualActionManager_for(all pItem items provided by the puntual action mode manager)
 *          pItem->CC_PunctualActionManager_execut e(CC_PunctualActionManager *This); </PRE>
 * Note that the outcome of the punctual CC_PunctualActionManager_action(i.e. the return
 * value of the <code>execute</code> method) is disregarded.
 */
void CC_PunctualActionManager_activate(CC_PunctualActionManager *This);


#endif
