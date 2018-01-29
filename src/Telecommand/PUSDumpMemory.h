//
//
// PUSDumpMemory.h
//


#ifndef PUSDUMPMEMORY_H
#define PUSDUMPMEMORY_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "PUSTelecommand.h"
#include "../Qom/object.h"


/*
 * Base class for PUS telecommands to set up a memory dump either with base plus offset or absolute address.
 * This class encapsulates the commonalities for the following subtypes of PUS service number 6:<ul>
 * <li>Subtype 3: dump memory using base plus offset</li>
 * <li>Subtype 5: dump memory using absolute addresses</li>
 * </ul>
 * This class defines an internal buffer to store the application data 
 * that define the telemetry packet. The maximum size of this buffer is
 * a configuration parameter that must be set at application initialization 
 * time(method <code>setNumberOfRawData</code>). This and other internal data structured
 * are declared <code>protected</code> in order to facilitate the implementation of
 * concrete subclasses.
 * <p>
 * During normal operation, configuration is performed using the <i>raw
 * data load service</i>. Since in most cases the amount of data to be loaded
 * can be large, the more efficient(but less safe) implementation of this service
 * is used.
 * <p>
 * This telecommand implements a <i>validity check</i> that returns "telecommand
 * not valid" in case an attempt is made to load more application data than fit
 * into the telecommand component.
 * <p>
 * No implementation for the execution action of this telecommand is provided. This
 * depends on whether the memory dump is of the "absolute address" or the "base address
 * plus offset" type and must therefore be provided by the concrete subclasses.
 * <p>
 * The PUS leaves some leeway in the definition of the structure of the application
 * data for memory dump telecommands. This implementation makes the same
 * assumptions as defined in the class comment of class <code>PUS_MemoryDump</code>.
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_PUSDUMPMEMORY "pusdumpmemory"

void PUSDumpMemory_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct PUSDumpMemory {
    PUSTelecommand parent;

    /**
     * The buffer where the application data are stored
     */
    unsigned char *data;
    /**
     * The size in number of bytes of the <code>data</code> buffer
     */
    unsigned int maxNumberData;
    /**
     * The size in the number of bytes of the currently loaded application data
     */
    unsigned int numberData;
    /**
     * The telemetry manager
     */
    CC_TelemetryManager *pTmManager;
};


struct PUSDumpMemoryClass {
    PUSTelecommandClass parent_class;
 
    unsigned int (*getNumberOfApplicationData)(const void *obj);
};


#define PUSDUMPMEMORY_GET_CLASS(obj) \
        OBJECT_GET_CLASS(PUSDumpMemoryClass, obj, TYPE_PUSDUMPMEMORY)

#define PUSDUMPMEMORY_CLASS(klass) \
        OBJECT_CLASS_CHECK(PUSDumpMemoryClass, klass, TYPE_PUSDUMPMEMORY)

#define PUSDUMPMEMORY(obj) \
        OBJECT_CHECK(PUSDumpMemory, obj, TYPE_PUSDUMPMEMORY)


PUSDumpMemory* PUSDumpMemory_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the maximum size of the application data array. The maximum size is specified as the
 * maximum number of bytes of the application data. 
 * This is an initialization method that should only be called once.
 * A call to this method causes the internal data structures of the
 * telecommand to be allocated and initialized. Only positive values of the method argument
 * are legal.
 * @param max the maximum size of the application data in number of bytes
 */
void PUSDumpMemory_setNumberOfRawData(PUSDumpMemory *This, unsigned int max);

/**
 * Load the telemetry manager.
 * @see #doAction
 * @param pTmManager the PUS telemetry mode manager
 */
void PUSDumpMemory_setTelemetryManager
(
    PUSDumpMemory *This, 
    CC_TelemetryManager *pTmManager
);

/**
 * Getter method for the telemetry manager.
 * @see #setTelemetryManager
 * @return the telemetry manager
 */
CC_TelemetryManager* PUSDumpMemory_getTelemetryManager(const PUSDumpMemory *This);


#endif
