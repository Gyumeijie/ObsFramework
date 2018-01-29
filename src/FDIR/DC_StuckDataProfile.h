//
//
// DC_StuckDataProfile.h
//
//
// Change Record:


#ifndef DC_STUCKDATAPROFILE_H
#define DC_STUCKDATAPROFILE_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "MonitoringProfile.h"
#include "../Qom/object.h"


/*
 * Default component implementing a "stuck data" monitoring profile.
 * This monitoring profile reports a "deviation from profile" if the 
 * value of the monitored variable remains unchanged for more
 * a certain number of consecutive activations. 
 * The number of consecutive activations that the
 * monitored variable must remain unchanged before the monitoring check is
 * detected is called the <i>stuck threshold</i>.
 * The stuck threshold is a settable parameter. Its value must be
 * greater than zero.
 * <p>
 * This type of check only makes sense for monitored variables of
 * integer type. The version of the monitoring check for variables
 * of doble type is therefore implemented as a dummy operation
 * that always returns "deviation from profile has been detected".
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @author Roberto Totaro
 * @version 1.1
 */
#define TYPE_DC_STUCKDATAPROFILE "dc_stuckdataprofile"

void DC_StuckDataProfile_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_StuckDataProfile {
    MonitoringProfile parent;

    unsigned int stuckThreshold;
    unsigned int counter;
    TD_Integer previousValue;
};


struct DC_StuckDataProfileClass {
    MonitoringProfileClass parent_class;
};


#define DC_STUCKDATAPROFILE_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_StuckDataProfileClass, obj, TYPE_DC_STUCKDATAPROFILE)

#define DC_STUCKDATAPROFILE_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_StuckDataProfileClass, klass, TYPE_DC_STUCKDATAPROFILE)

#define DC_STUCKDATAPROFILE(obj) \
        OBJECT_CHECK(DC_StuckDataProfile, obj, TYPE_DC_STUCKDATAPROFILE)


DC_StuckDataProfile* DC_StuckDataProfile_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the stuck threshold.
 * @see #doProfileCheck
 * @param stuckThreshold the value of the stuck threshold
 */
void DC_StuckDataProfile_setStuckThreshold
(
    DC_StuckDataProfile *This,
    unsigned int stuckThreshold
);

/**
 * Get the stuck thresholde.
 * @see #setStuckThreshold
 * @return the value of the stuck threshold
 */
unsigned int 
DC_StuckDataProfile_getStuckThreshold(const DC_StuckDataProfile *This);


#endif
