//
//
// DC_DeltaProfile.h
//
//
// Change Record:


#ifndef DC_DELTAPROFILE_H
#define DC_DELTAPROFILE_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "MonitoringProfile.h"
#include "../Qom/object.h"


/*
 * Default component implementing a "stuck data" monitoring profile.
 * This monitoring profile reports a "deviation from profile" if the 
 * value of the monitored variable undergoes a change in between two 
 * successive checks greater than a certain threshold. 
 * The threshold is called the <i>delta threshold</i>.
 * The delta threshold is a settable parameter. Its value must be
 * greater than zero. 
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @author Roberto Totaro
 * @version 1.1
 */
#define TYPE_DC_DELTAPROFILE "dc_deltaprofile"

void DC_DeltaProfile_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_DeltaProfile {
    MonitoringProfile parent;

    TD_Float deltaThreshold;
    TD_Float previousValue;
    bool notFirst;
};


struct DC_DeltaProfileClass {
    MonitoringProfileClass parent_class;
};


#define DC_DELTAPROFILE_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_DeltaProfileClass, obj, TYPE_DC_DELTAPROFILE)

#define DC_DELTAPROFILE_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_DeltaProfileClass, klass, TYPE_DC_DELTAPROFILE)

#define DC_DELTAPROFILE(obj) \
        OBJECT_CHECK(DC_DeltaProfile, obj, TYPE_DC_DELTAPROFILE)


DC_DeltaProfile* DC_DeltaProfile_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the delta threshold.
 * @see #doProfileCheck
 * @param deltaThreshold the value of the delta threshold
 */
void DC_DeltaProfile_setDeltaThreshold
(
    DC_DeltaProfile *This, 
    TD_Float deltaThreshold
);

/**
 * Get the delta threshold.
 * @see #doProfileCheck
 * @return the value of the delta threshold
 */
TD_Float DC_DeltaProfile_getDeltaThreshold(DC_DeltaProfile *This);


#endif
