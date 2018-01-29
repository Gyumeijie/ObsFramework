//
//
// DC_PUSDefineDataReporting.h
//


#ifndef DC_PUSDEFINEDATAREPORTING_H
#define DC_PUSDEFINEDATAREPORTING_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "PUSTelecommand.h"
#include "../Qom/object.h"


/*
 * PUS telecommand to define the housekeeping and diagnostic 
 * data reporting telemetry packets.
 * This class encapsulates the following subtypes of PUS service number 3:<ul>
 * <li>Subtype 1: define new housekeeping parameter report </li>
 * <li>Subtype 2: define new diagnostic parameter report </li>
 * </ul>
 * This class defines an internal buffer to store the application data 
 * that define the telemetry packet. The maximum size of this buffer is
 * a configuration parameter that must be set at application initialization 
 * time(method <code>setNumberOfRawData</code>). 
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
 * Execution of this telecommand consists in retrieving a free data reporting telemetry packet
 * from the telemetry packet factory, configuring it with the application
 * data and loading it in the PUS telemetry mode manager. The PUS telemetry mode
 * manager is loaded as a plug-in component at configuration time. Execution can have 
 * two outcomes. 
 * The telecommand
 * can have a successful outcome(the return value of <code>doAction</code>
 * is ACTION_SUCCESS) or it can fail for the following reasons:
 * <ul>
 * <li>No free packet could be found in the
 * telemetry packet factory(the return value of <code>doAction</code>
 * is PACKET_NOT_FOUND)   </li>
 * <li>The packet could not be loaded in the
 * telemetry mode manager(the return value of <code>doAction</code>
 * is PUS_MODE_MAN_FULL)   </li>
 * <li>The internal structure of the application data was found to be 
 * inconsistent(the return value of <code>doAction</code>
 * is APP_DATA_INCONSISTENT)   </li>
 * </ul> . 
 * No event reports are generated in case of failure as it is assumed that
 * this is done by the calling client.
 * <p>
 * Note that this class does not try to interpret its application data. It simply passes
 * them on as unformatted raw data to the data reporting telemetry packet.
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_PUSDEFINEDATAREPORTING "dc_pusdefinedatareporting"

void DC_PUSDefineDataReporting_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_PUSDefineDataReporting {
    PUSTelecommand parent;

    unsigned char *data;
    unsigned int maxNumberData;
    unsigned int numberData;
    DC_PUSTelemetryModeManager *pTmModeManager;
};


struct DC_PUSDefineDataReportingClass {
    PUSTelecommandClass parent_class;
 
    unsigned int (*getNumberOfApplicationData)(const void *obj);
};


#define DC_PUSDEFINEDATAREPORTING_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_PUSDefineDataReportingClass, \
                                           obj, TYPE_DC_PUSDEFINEDATAREPORTING)

#define DC_PUSDEFINEDATAREPORTING_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_PUSDefineDataReportingClass, \
                                         klass, TYPE_DC_PUSDEFINEDATAREPORTING)

#define DC_PUSDEFINEDATAREPORTING(obj) \
        OBJECT_CHECK(DC_PUSDefineDataReporting, \
                                           obj, TYPE_DC_PUSDEFINEDATAREPORTING)


DC_PUSDefineDataReporting* DC_PUSDefineDataReporting_new(void);


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
void DC_PUSDefineDataReporting_setNumberOfRawData
(
    DC_PUSDefineDataReporting *This, 
    unsigned int max
);

/**
 * Load the PUS telemetry mode manager.
 * @see #doAction
 * @param pTmModeManager the PUS telemetry mode manager
 */
void DC_PUSDefineDataReporting_setPUSTelemetryModeManager
(
    DC_PUSDefineDataReporting *This, 
    DC_PUSTelemetryModeManager *pTmModeManager
);

/**
 * Getter method for the PUS telemetry mode manager.
 * @see #setPUSTelemetryModeManager
 * @return the PUS telemetry mode manager
 */
DC_PUSTelemetryModeManager* DC_PUSDefineDataReporting_getPUSTelemetryModeManager
(
    const DC_PUSDefineDataReporting *This
);


#endif
