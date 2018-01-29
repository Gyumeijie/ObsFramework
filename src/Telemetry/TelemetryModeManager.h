//
//
// TelemetryModeManager.h
//


#ifndef TELEMETRYMODEMANAGER_H
#define TELEMETRYMODEMANAGER_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/ModeManager.h"
#include "../Qom/object.h"


/*
 * Base abstract class for mode manager components for the telemetry
 * manager.
 * A telemetry mode manager handles one single <i>strategy</i>, which
 * is represented by a set of <i>telemetry packet</i> components.
 * To every operational mode, the telemetry mode manager associates 
 * a set of telemetry packets. 
 * Client access the items in this set through four
 * <i>iteration methods</i>: <code>first</code>, <code>next</code>,
 * <code>isIterationFinished</code>, and <code>getIterationTelemetryPacket</code>.
 * <p>
 * This is an abstract class because it specifies neither the implementation
 * mechanism for the set of telemetry packets nor the mode update mechanism.
 * @see CC_TelemetryManager
 * @see TelemetryPacket
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 * @ingroup ModeManagement
 * @ingroup Telemetry
 */
#define TYPE_TELEMETRYMODEMANAGER "telemetrymodemanager"

void TelemetryModeManager_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct TelemetryModeManager {
    ModeManager parent;
};


struct TelemetryModeManagerClass {
    ModeManagerClass parent_class;
 
    void (*first)(void *obj);
    void (*next)(void *obj);
    bool (*isIterationFinished)(void *obj);
    TelemetryPacket* (*getIterationTelemetryPacket)(void *obj);
};


#define TELEMETRYMODEMANAGER_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TelemetryModeManagerClass, obj, TYPE_TELEMETRYMODEMANAGER)

#define TELEMETRYMODEMANAGER_CLASS(klass) \
        OBJECT_CLASS_CHECK(TelemetryModeManagerClass, klass, TYPE_TELEMETRYMODEMANAGER)

#define TELEMETRYMODEMANAGER(obj) \
        OBJECT_CHECK(TelemetryModeManager, obj, TYPE_TELEMETRYMODEMANAGER)


TelemetryModeManager* TelemetryModeManager_new(void);

#endif
