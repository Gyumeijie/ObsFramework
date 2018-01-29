//
//
// DC_SimpleTelemetryModeManager.h
//


#ifndef DC_SIMPLETELEMETRYMODEMANAGER_H
#define DC_SIMPLETELEMETRYMODEMANAGER_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "TelemetryListModeManager.h"
#include "../Qom/object.h"


/*
 * Telemetry list mode manager with a single and fixed mode.
 * This mode manager has a trivial implementation of the update
 * service that returns without taking any action. It is typically
 * used when the telemetry format is fixed.
 * <p>
 * An initialization sequence for this class consists of the following
 * steps(to be performed in the order given here): <ul>
 * <li>Set the length of the single telemetry packet list through method
 * <code>setListLength</code></li>
 * <li>Load the individual items through method <code>setListTelemetryPacket</code></li>
 * <li>Reset the component by calling method <code>reset</code></li>
 * </ul>
 * @see TelemetryPacket
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_SIMPLETELEMETRYMODEMANAGER "dc_simpletelemetrymodemanager"

void DC_SimpleTelemetryModeManager_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_SimpleTelemetryModeManager {
    TelemetryListModeManager parent;
};


struct DC_SimpleTelemetryModeManagerClass {
    TelemetryListModeManagerClass parent_class;
};


#define DC_SIMPLETELEMETRYMODEMANAGER_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_SimpleTelemetryModeManagerClass, \
                                       obj, TYPE_DC_SIMPLETELEMETRYMODEMANAGER)

#define DC_SIMPLETELEMETRYMODEMANAGER_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_SimpleTelemetryModeManagerClass, \
                                     klass, TYPE_DC_SIMPLETELEMETRYMODEMANAGER)

#define DC_SIMPLETELEMETRYMODEMANAGER(obj) \
        OBJECT_CHECK(DC_SimpleTelemetryModeManager, \
                                       obj, TYPE_DC_SIMPLETELEMETRYMODEMANAGER)


DC_SimpleTelemetryModeManager* DC_SimpleTelemetryModeManager_new(void);

#endif
