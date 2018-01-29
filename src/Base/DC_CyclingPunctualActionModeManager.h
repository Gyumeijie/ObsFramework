//
//
// DC_CyclingPunctualActionModeManager.h
//


#ifndef DC_CYCLINGPUNCTUALACTIONMODEMANAGER_H
#define DC_CYCLINGPUNCTUALACTIONMODEMANAGER_H


#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "PunctualActionListModeManager.h"
#include "../Qom/object.h"


/*
 * Punctual action mode manager that cycles through the lists of punctual actions.
 * This class extends the base class <code>PunctualActionListModeManager</code> 
 * by adding to it an implementation for the <i>update mechanism</i> that
 * cycles through all the operational modes defined for the mode manager.
 * </p>
 * An initialization sequence for this class consists of the following
 * steps(to be performed in the order given): <ul>
 * <li>Set the number of modes through method <code>setNumberOfModes</code></li>
 * <li>Set the default mode <code>setDefaultMode</code></li>
 * <li>Set the lengths of the lists through method
 * <code>setListLength</code></li>
 * <li>Load the individual items through method <code>setListItem</code></li>
 * <li>Reset the component by calling method <code>reset</code></li>
 * </ul>
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_CYCLINGPUNCTUALACTIONMODEMANAGER "dc_cyclingpunctualactionmodemanager"

void DC_CyclingPunctualActionModeManager_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_CyclingPunctualActionModeManager {
    PunctualActionListModeManager parent;
};


struct DC_CyclingPunctualActionModeManagerClass {
    PunctualActionListModeManagerClass parent_class;
};


#define DC_CYCLINGPUNCTUALACTIONMODEMANAGER_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_CyclingPunctualActionModeManagerClass,\
                                  obj, TYPE_DC_CYCLINGPUNCTUALACTIONMODEMANAGER)

#define DC_CYCLINGPUNCTUALACTIONMODEMANAGER_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_CyclingPunctualActionModeManagerClass,\
                                klass, TYPE_DC_CYCLINGPUNCTUALACTIONMODEMANAGER)

#define DC_CYCLINGPUNCTUALACTIONMODEMANAGER(obj) \
        OBJECT_CHECK(DC_CyclingPunctualActionModeManager,\
                                  obj, TYPE_DC_CYCLINGPUNCTUALACTIONMODEMANAGER)


DC_CyclingPunctualActionModeManager* DC_CyclingPunctualActionModeManager_new(void);

#endif
