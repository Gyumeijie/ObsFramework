//
//
// DC_PUSControlDataReporting.h
//


#ifndef DC_PUSCONTROLDATAREPORTING_H
#define DC_PUSCONTROLDATAREPORTING_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "PUSTelecommand.h"
#include "../Qom/object.h"


/*
 * PUS telecommand to enable and disable the housekeeping and diagnostic 
 * data reporting telemetry packets.
 * This class encapsulates the following subtypes of PUS service number 3:<ul>
 * <li>Subtype 5: enable housekeeping parameter report generation</li>
 * <li>Subtype 6: disable housekeeping parameter report generation</li>
 * <li>Subtype 7: enable diagnostic parameter report generation</li>
 * <li>Subtype 8: disable diagnostic parameter report generation</li>
 * </ul>
 * This class is configured at initialization time by setting the maximum 
 * number of SIDs that can be handled by a single instance of the telecommand.
 * This is done through method <code>setMaxNumberSID</code>. A call to this
 * method initializes the internal data structures that are used to hold the
 * application data of the telecommand.
 * <p>
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
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_PUSCONTROLDATAREPORTING "dc_puscontroldatareporting"

void DC_PUSControlDataReporting_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_PUSControlDataReporting {
    PUSTelecommand parent;

    TD_SID *sid;
    unsigned char *sidOverlay;
    unsigned char maxNsid;
    unsigned char nsid;
    unsigned int lasti;
};


struct DC_PUSControlDataReportingClass {
    PUSTelecommandClass parent_class;
};


#define DC_PUSCONTROLDATAREPORTING_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_PUSControlDataReportingClass, \
                                          obj, TYPE_DC_PUSCONTROLDATAREPORTING)

#define DC_PUSCONTROLDATAREPORTING_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_PUSControlDataReportingClass, \
                                        klass, TYPE_DC_PUSCONTROLDATAREPORTING)

#define DC_PUSCONTROLDATAREPORTING(obj) \
        OBJECT_CHECK(DC_PUSControlDataReporting, \
                                          obj, TYPE_DC_PUSCONTROLDATAREPORTING)


DC_PUSControlDataReporting* DC_PUSControlDataReporting_new(void);


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
void DC_PUSControlDataReporting_setMaxNumberSID
(
    DC_PUSControlDataReporting *This, 
    unsigned char max
);

/**
 * Get the maximum number of SIDs that can be processed by this telecommand.
 * @see #setMaxNumberSID
 * @return the maximum number of SIDs
 */
unsigned int DC_PUSControlDataReporting_getMaxNumberSID
(
    DC_PUSControlDataReporting *This
);


#endif
