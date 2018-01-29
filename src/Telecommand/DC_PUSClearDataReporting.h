//
//
// DC_PUSClearDataReporting.h
//


#ifndef DC_PUSCLEARDATAREPORTING_H
#define DC_PUSCLEARDATAREPORTING_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "PUSTelecommand.h"
#include "../Qom/object.h"


/*
 * PUS telecommand to clear one or more housekeeping and diagnostic 
 * data reporting telemetry packets.
 * This class encapsulates the following subtypes of PUS service number 3:<ul>
 * <li>Subtype 3: clear housekeeping parameter report definition</li>
 * <li>Subtype 4: clear diagnostic parameter report definition</li>
 * </ul>
 * A parameter report definition is cleared by performing the following actions:<ul>
 * <li>The telemetry packet that encapsulates the parameter report is marked
 * "not in use".</li>
 * <li>The telemetry packet is unloaded from the PUS telemetry mode manager.</li>
 * </ul>
 * This class is configured at initialization time by performing the following
 * actions: <ul>
 * <li>The maximum 
 * number of SIDs that can be handled by a single instance of the telecommand
 * is set through method <code>setMaxNumberSID</code>. A call to this
 * method initializes the internal data structures that are used to hold the
 * application data of the telecommand.</li>
 * <li>The PUS telemetry mode manager is loaded as a plug-in component.</li>
 * </ul>
 * During normal operation, configuration is performed using the <i>raw
 * data load service</i>.
 * <p>
 * This telecommand implements a <i>validity check</i> that returns "telecommand
 * not valid" in case an attempt is made to load more application data than fit
 * into the telecommand component or in case the application data are internally
 * inconsistent.
 * <p>
 * Execution of this telecommand can have two outcomes. The telecommand
 * can either have a successful outcome(the return value of <code>doAction</code>
 * is ACTION_SUCCESS) or it can fail(the return value of <code>doAction</code>
 * is ACTION_FAILURE). A failure is declared if any of the SIDs provided to 
 * the telecommand do not correspond to a data reporting packet that is
 * currently in use.
 * <p>
 * The PUS specifies that the first item in the application data of this
 * telecommand is the NSID field. The type of this field is not mandated by the 
 * standard. This class assumes it to be of type <code>unsigned char</code>.
 * The standard also allows this field to be omitted. This class however
 * requires this field to be always present.
 * @todo This class can only take one telemetry mode manager
 * as configuration parameters. If we assume that the same applications can have several
 * telemetry managers(maybe to manage telemetry packets with different levels of RT
 * priority), then it would be necessary to modify this class to accept several
 * telemetry mode managers.
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_PUSCLEARDATAREPORTING "dc_puscleardatareporting"

void DC_PUSClearDataReporting_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_PUSClearDataReporting {
    PUSTelecommand parent;

    TD_SID *sid;
    unsigned char *sidOverlay;
    unsigned char maxNsid;
    unsigned char nsid;
    unsigned int lasti;
    DC_PUSTelemetryModeManager *pTmModeManager;
};


struct DC_PUSClearDataReportingClass {
    PUSTelecommandClass parent_class;
};


#define DC_PUSCLEARDATAREPORTING_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_PUSClearDataReportingClass, \
                                               obj, TYPE_DC_PUSCLEARDATAREPORTING)

#define DC_PUSCLEARDATAREPORTING_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_PUSClearDataReportingClass, \
                                             klass, TYPE_DC_PUSCLEARDATAREPORTING)

#define DC_PUSCLEARDATAREPORTING(obj) \
        OBJECT_CHECK(DC_PUSClearDataReporting, obj, TYPE_DC_PUSCLEARDATAREPORTING)


DC_PUSClearDataReporting* DC_PUSClearDataReporting_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the maximum number of SIDs that can be processed by this telecommand.
 * This is an initialization method that should only be called once.
 * A call to this method causes the internal data structures where the SIDs are
 * held to be allocated and initialized. Only positive values of the method argument
 * are legal.
 * @param max the maximum number of SIDs
 */
void DC_PUSClearDataReporting_setMaxNumberSID
(
    DC_PUSClearDataReporting *This,
    unsigned char max
);

/**
 * Load the PUS telemetry mode manager.
 * @see #doAction
 * @param pTmModeManager the PUS telemetry mode manager
 */
void DC_PUSClearDataReporting_setPUSTelemetryModeManager
(
   DC_PUSClearDataReporting *This, 
   DC_PUSTelemetryModeManager *pTmModeManager
);

/**
 * Getter method for the PUS telemetry mode manager.
 * @see #setPUSTelemetryModeManager
 * @return the PUS telemetry mode manager
 */
DC_PUSTelemetryModeManager* DC_PUSClearDataReporting_getPUSTelemetryModeManager
(
    const DC_PUSClearDataReporting *This
);


#endif
