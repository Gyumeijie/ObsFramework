//
//
// DC_DummyModeManager.h
//


#ifndef DC_DUMMYMODEMANAGER_H
#define DC_DUMMYMODEMANAGER_H


#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "ModeManager.h"
#include "../Qom/object.h"


/*
 * Dummy mode manager to be used for testing purposes.
 * This mode manager does not define any strategies.
 * Its implementation of the update service consists in cycling through
 * all possible operational modes.
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_DUMMYMODEMANAGER "dc_dummymodemanager"

void DC_DummyModeManager_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_DummyModeManager {
    ModeManager parent;
};


struct DC_DummyModeManagerClass {
    ModeManagerClass parent_class;
};


#define DC_DUMMYMODEMANAGER_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_DummyModeManagerClass, obj, TYPE_DC_DUMMYMODEMANAGER)

#define DC_DUMMYMODEMANAGER_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_DummyModeManagerClass, klass, TYPE_DC_DUMMYMODEMANAGER)

#define DC_DUMMYMODEMANAGER(obj) \
        OBJECT_CHECK(DC_DummyModeManager, obj, TYPE_DC_DUMMYMODEMANAGER)


DC_DummyModeManager* DC_DummyModeManager_new(void);

#endif
