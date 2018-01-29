//
//
// DC_CyclingTelemetryModeManager.h
//


#ifndef DC_CYCLINGTELEMETRYMODEMANAGER_H
#define DC_CYCLINGTELEMETRYMODEMANAGER_H


#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "TelemetryListModeManager.h"
#include "../Qom/object.h"


/*
 * Telemetry mode manager that cycles through the lists of telemetry packets.
 * This class extends the base class <code>TelemetryListModeManager</code> 
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
#define TYPE_DC_CYCLINGTELEMETRYMODEMANAGER "dc_cyclingtelemetrymodemanager"

void DC_CyclingTelemetryModeManager_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_CyclingTelemetryModeManager {
    TelemetryListModeManager parent;
};


struct DC_CyclingTelemetryModeManagerClass {
    TelemetryListModeManagerClass parent_class;
};


#define DC_CYCLINGTELEMETRYMODEMANAGER_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_CyclingTelemetryModeManagerClass, \
                                      obj, TYPE_DC_CYCLINGTELEMETRYMODEMANAGER)

#define DC_CYCLINGTELEMETRYMODEMANAGER_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_CyclingTelemetryModeManagerClass, \
                                    klass, TYPE_DC_CYCLINGTELEMETRYMODEMANAGER)

#define DC_CYCLINGTELEMETRYMODEMANAGER(obj) \
        OBJECT_CHECK(DC_CyclingTelemetryModeManager, \
                                      obj, TYPE_DC_CYCLINGTELEMETRYMODEMANAGER)


DC_CyclingTelemetryModeManager* DC_CyclingTelemetryModeManager_new(void);

#endif
