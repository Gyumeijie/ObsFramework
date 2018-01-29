//
//
// DC_PUSTelemetryModeManager.h
//


#ifndef DC_PUSTELEMETRYMODEMANAGER_H
#define DC_PUSTELEMETRYMODEMANAGER_H


#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/ForwardDeclarations.h"
#include "TelemetryModeManager.h"
#include "../Qom/object.h"


/*
 * PUS telemetry mode manager.
 * This telemetry mode manager has one single mode to which there 
 * corresponds a set of PUS data reporting telemetry packets 
 * (instances of class <code>PUSDataReportingPacket</code>).
 * The telemetry packets can be loaded and unloaded dynamically. 
 * The iteration methods iterate through all the currently loaded 
 * telemetry packets(the order of the iteration is undefined).
 * The mode manager is configured with the maximum number of 
 * telemetry packets that it can hold(method <code>setMaxNumberOfPackets</code>).
 * </p>
 * An initialization sequence for this class consists of the following
 * steps(to be performed in the order given): <ul>
 * <li>Set the maximum number of loadable packets with method <code>setMaxNumberOfPackets</code></li>
 * <li>Reset the component by calling method <code>reset</code></li>
 * </ul>
 * @ingroup PUS
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_PUSTELEMETRYMODEMANAGER "dc_pustelemetrymodemanager"

void DC_PUSTelemetryModeManager_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_PUSTelemetryModeManager {
    TelemetryModeManager parent;

    DC_PUSDataReportingPacket **list;    
    unsigned int listLength;   
    unsigned int iterationCounter;   
    unsigned int counter;             // number of items in list
};


struct DC_PUSTelemetryModeManagerClass {
    TelemetryModeManagerClass parent_class;
};


#define DC_PUSTELEMETRYMODEMANAGER_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_PUSTelemetryModeManagerClass, \
                                          obj, TYPE_DC_PUSTELEMETRYMODEMANAGER)

#define DC_PUSTELEMETRYMODEMANAGER_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_PUSTelemetryModeManagerClass, \
                                        klass, TYPE_DC_PUSTELEMETRYMODEMANAGER)

#define DC_PUSTELEMETRYMODEMANAGER(obj) \
        OBJECT_CHECK(DC_PUSTelemetryModeManager, \
                                          obj, TYPE_DC_PUSTELEMETRYMODEMANAGER)


DC_PUSTelemetryModeManager* DC_PUSTelemetryModeManager_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Load a telemetry packet in the set of packets managed by this
 * mode manager. If the set is already full, then an event of 
 * type EVT_ILLEGAL_MM is generated. Before calling this method, clients 
 * should call method
 * <code>isFull</code> to check whether there is space available.
 * @param pItem the item to be loaded
 */
void DC_PUSTelemetryModeManager_loadPacket
(
    DC_PUSTelemetryModeManager *This, 
    DC_PUSDataReportingPacket *pItem
);

/**
 * Unload the PUS telemetry packet identified by the argument SID.
 * If none of the currently loaded packets matches the given DC_PUSTelemetryModeManager_SID(or
 * if the set is currently empty), 
 * no action is taken other than generating an event report of type
 * EVT_SID_NOT_FOUND. Method <code>isSIDLoaded</code> can be used 
 * to check whether a packet with a certain SID is currently loaded.
 * @param sid the SID of the packet to be unloaded
 */
void DC_PUSTelemetryModeManager_unloadPacket
(
    DC_PUSTelemetryModeManager *This, 
    TD_SID sid
);

/**
 * Check whether the mode manager is full. 
 * @see #loadPacket
 * @return true if no packets are currently loaded
 */
bool DC_PUSTelemetryModeManager_isFull
(
    const DC_PUSTelemetryModeManager *This
);

/**
 * Return the number of packets that are currently loaded.
 * @return number of packets currently loaded
 */
unsigned int DC_PUSTelemetryModeManager_getNumberOfPackets
(
    const DC_PUSTelemetryModeManager *This
);

/**
 * Check whether the packet with the argument SID is currently loaded.
 * @see #unloadPacket
 * @param sid the SID 
 * @return true if a packet with the argument SID is currently loaded
 */
bool DC_PUSTelemetryModeManager_isSIDLoaded
(
    const DC_PUSTelemetryModeManager *This, 
    TD_SID sid
);

/**
 * Set the maximum number of packets that can be loaded. 
 * This is an initialization method. It should only be called once.
 * Only positive values for the maximum number of packets are legal.
 * @param n the maximum number of packets
 */
void DC_PUSTelemetryModeManager_setMaxNumberOfPackets
(
    DC_PUSTelemetryModeManager *This, 
    unsigned int n
);

/**
 * Return the maximum number of packets that can be loaded.
 * @return maximum number of packets that can be loaded
 */
unsigned int DC_PUSTelemetryModeManager_getMaxNumberOfPackets
(
    const DC_PUSTelemetryModeManager *This
);


#endif
