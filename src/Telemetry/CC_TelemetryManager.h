//
//
// CC_TelemetryManager.h
//


#ifndef CC_TELEMETRYMANAGER_H
#define CC_TELEMETRYMANAGER_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "TelemetryModeManager.h"
#include "TelemetryStream.h"
#include "../Qom/object.h"


/*
 * This class encapsulates a telemetry manager.
 * The telemetry manager is responsible for controlling the dispatch
 * of telemetry packets to the telemetry stream.
 * The telemetry packets can be dispatched to the telemetry stream in two
 * modes: <ul>
 * <li><i>Repetitive Mode</i>: the packets are provided by a <i>telemetry mode
 * manager</i>.
 * This dispatch mode is typically used for packets that must be written to the
 * telemetry stream on a regular basis.</li>
 * <li><i>Immediate Mode</i>: the packets are direclty loaded by an external
 * client and are dispatched to the telemetry stream at the next activation of
 * the telemetry manager. They are only dispatched once. This dispatch mode
 * is typically used for packets that must be dispatched on an occasional basis.</li>
 * </ul>
 * The telemetry mode manager is a plug-in component that must be configured
 * with the telemetry packets by an external client. The packets for immediate
 * dispatch are instead loaded in an internal queue(the <i>immediate
 * dispatch queue</i>) whose size must be defined as part of the configuration
 * procedure of the telemetry manager.
 * <p>
 * The telemetry packets are written to the telemetry stream when the telemetry
 * stream is <i>activated</i> (invocation of method <code>activate</code>). At this
 * time, the telemetry packets that were directly loaded since the last activation
 * and the telemetry packets that are provided by the telemetry mode manager are
 * first updated and then their written to the telemetry stream.
 * <p>
 * The telemetry manager contributes to the management of the "in use" status of
 * telemetry packets. More precisely, packets that are submitted for immediate
 * dispatch are marked as "no longer in use" after being processed.
 * <p>
 * The telemetry stream component
 * is a plug-in component of the telemetry manager.
 * <p>
 * The configuration procedure for a newly instantiated telemetry
 * manager is as follows: <ol>
 * <li>Load a telemetry stream component(method
 * <code>setTelemetryStream</code>).</li>
 * <li>Load a telemetry mode manager component(method
 * <code>setTelemetryModeManager</code>).</li>
 * <li>Set the size of the immediate dispatch queue(method
 * <code>setImmediateQueueSize</code>).</li>
 * </ol>
 * The above operations can be executed in any order.
 * <p>
 * @see TelemetryPacket
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 * @ingroup FunctionalityManagers
 * @ingroup Telemetry
 */
#define TYPE_CC_TELEMETRYMANAGER "cc_telemetrymanager"

void CC_TelemetryManager_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct CC_TelemetryManager {
    CC_RootObject parent;

    TelemetryModeManager *pTmModeManager;
    TelemetryStream *pTmStream;
    int packetQueueSize;
    TelemetryPacket **pPacketQueue;
};


struct CC_TelemetryManagerClass {
    CC_RootObjectClass parent_class;
 
    void (*activate)(void *obj);
};


#define CC_TELEMETRYMANAGER_GET_CLASS(obj) \
        OBJECT_GET_CLASS(CC_TelemetryManagerClass, obj, TYPE_CC_TELEMETRYMANAGER)

#define CC_TELEMETRYMANAGER_CLASS(klass) \
        OBJECT_CLASS_CHECK(CC_TelemetryManagerClass, klass, TYPE_CC_TELEMETRYMANAGER)

#define CC_TELEMETRYMANAGER(obj) \
        OBJECT_CHECK(CC_TelemetryManager, obj, TYPE_CC_TELEMETRYMANAGER)


CC_TelemetryManager* CC_TelemetryManager_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Load the telemetry mode manager.
 * @param pTmModeManager the telemetry mode manager
 */
void CC_TelemetryManager_setTelemetryModeManager
(
    CC_TelemetryManager *This, 
    TelemetryModeManager *pTmModeManager
);

/**
 * Get the telemetry mode manager.
 * @return the telemetry mode manager
 */
TelemetryModeManager* CC_TelemetryManager_getTelemetryModeManager
(
    const CC_TelemetryManager *This
);

/**
 * Load the telemetry stream component. The telemetry stream is reset
 * immediately after being loaded.
 * @param pTmStream the telemetry stream component
 */
void CC_TelemetryManager_setTelemetryStream
(
    CC_TelemetryManager *This, 
    TelemetryStream* pTmStream
);

/**
 * Get the telemetry stream component.
 * @return the telemetry stream component
 */
TelemetryStream* CC_TelemetryManager_getTelemetryStream
(
    const CC_TelemetryManager *This
);

/**
 * Set the size of the immediate dispatch queue.
 * This is an initialization method. It should only be called once.
 * The size of the immediate dispatch queue can be zero for the
 * case of applications where the immediate load service is disabled.
 * @param size the size of the immediate load packet queue
 */
void CC_TelemetryManager_setImmediateQueueSize
(
    CC_TelemetryManager *This, 
    unsigned int size
);

/**
 * Return the size of the immediate dispatch queue.
 * @return the size of the immediate dispatch queue
 */
unsigned int CC_TelemetryManager_getImmediateQueueSize(CC_TelemetryManager *This);

/**
 * Return the i-th entry in the immediate dispatch queue.
 * The index i should lie in the range [0, N-1] where N is the size of the queue.
 * If the value of i is out of range, a null pointer is returned. A null
 * pointer will also be returned if the i-the entry in the queue is empty.
 * This method is only intended for testing purposes. It should not be used
 * in an operational context. This method may return null
 * @return the size of the immediate dispatch queue
 */
TelemetryPacket* CC_TelemetryManager_getImmediateQueueEntry
(
    CC_TelemetryManager *This, 
    unsigned int i
);

/**
 * Return true if the size of the immediate dispatch queue is 
 * zero or if the immediate dispatch queue is full.
 * @return true if the immediate dispatch queue is full
 */
bool CC_TelemetryManager_isImmediateQueueFull(CC_TelemetryManager *This);

/**
 * Add the argument telemetry packet to the immediate dispatch queue.
 * The telemetry packet will be dispatched to the telemetry stream at the
 * next activation of the telemetry manager.
 * If the queue is already full, then an event report of type EVT_TM_QUEUE_FULL
 * is generated.
 * @param pTmPacket the telemetry packet component
 */
void CC_TelemetryManager_sendTelemetryPacket
(
    CC_TelemetryManager *This, 
    TelemetryPacket *pTmPacket
);

/**
 * Check if the argument telemetry packet is currently in the immediate dispatch queue and, 
 * if it is, remove it.
 * Failure to find the argument packet is treated as a nominal situation and is therefore
 * not recorded through an event report.
 * @param pTmPacket the telemetry packet component
 */
void CC_TelemetryManager_unloadTelemetryPacket
(
    CC_TelemetryManager *This, 
    TelemetryPacket *pTmPacket
);

/**
 * Return the number of telemetry packets currently loaded in the immediate dispatch queue.
 * @return the number of telemetry packets currently loaded in the immediate dispatch queue
 */
unsigned int CC_TelemetryManager_getImmediateQueueLoaded(CC_TelemetryManager *This);


#endif
