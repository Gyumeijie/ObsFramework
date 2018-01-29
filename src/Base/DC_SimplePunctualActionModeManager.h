//
//
// DC_SimplePunctualActionModeManager.h
//


#ifndef DC_SIMPLEPUNCTUALACTIONMODEMANAGER_H
#define DC_SIMPLEPUNCTUALACTIONMODEMANAGER_H


#include "PunctualActionListModeManager.h"
#include "../Qom/object.h"


/*
 * Punctual action mode manager with a single and fixed mode.
 * This mode manager has a trivial implementation of the update
 * service that returns without taking any action. It should be 
 * used when the punctual action manager operates upon a fixed
 * list of punctual actions.
 * <p>
 * An initialization sequence for this class consists of the following
 * steps(to be performed in the order given here): <ul>
 * <li>Set the length of the single punctual action list through method
 * <code>setListLength</code></li>
 * <li>Load the individual punctual actions items through successive
 * calles to method <code>setListPunctualAction</code></li>
 * <li>Reset the component by calling method <code>reset</code></li>
 * </ul>
 * @see PunctualAction
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_SIMPLEPUNCTUALACTIONMODEMANAGER "dc_simplepunctualactionmodemanager"

void DC_SimplePunctualActionModeManager_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_SimplePunctualActionModeManager {
    PunctualActionListModeManager parent;
};


struct DC_SimplePunctualActionModeManagerClass {
    PunctualActionListModeManagerClass parent_class;
};


#define DC_SIMPLEPUNCTUALACTIONMODEMANAGER_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_SimplePunctualActionModeManagerClass,\
                                  obj, TYPE_DC_SIMPLEPUNCTUALACTIONMODEMANAGER)

#define DC_SIMPLEPUNCTUALACTIONMODEMANAGER_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_SimplePunctualActionModeManagerClass,\
                                klass, TYPE_DC_SIMPLEPUNCTUALACTIONMODEMANAGER)

#define DC_SIMPLEPUNCTUALACTIONMODEMANAGER(obj) \
        OBJECT_CHECK(DC_SimplePunctualActionModeManager,\
                                  obj, TYPE_DC_SIMPLEPUNCTUALACTIONMODEMANAGER)


DC_SimplePunctualActionModeManager* DC_SimplePunctualActionModeManager_new(void);

#endif
