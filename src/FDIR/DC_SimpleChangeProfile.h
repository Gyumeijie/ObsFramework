//
//
// DC_SimpleChangeProfile.h
//
//
// Change Record:


#ifndef DC_SIMPLECHANGEPROFILE_H
#define DC_SIMPLECHANGEPROFILE_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "MonitoringProfile.h"
#include "../Qom/object.h"


/*
 * Default component implementing a simple change monitoring profile.
 * This monitoring profile reports a "deviation from profile" if the 
 * value of the monitored variable is different
 * from a fixed reference value. 
 * The reference value is a settable parameter.
 * <p>
 * This type of check only makes sense for monitored variables of
 * integer type. The version of the monitoring check for variables
 * of doble type is therefore implemented as a dummy operation
 * that always returns "deviation from profile has been detected".
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @author Roberto Totaro
 * @version 1.1
 */
#define TYPE_DC_SIMPLECHANGEPROFILE "dc_simplechangeprofile"

void DC_SimpleChangeProfile_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_SimpleChangeProfile {
    MonitoringProfile parent;

    TD_Integer referenceValue;
};


struct DC_SimpleChangeProfileClass {
    MonitoringProfileClass parent_class;
};


#define DC_SIMPLECHANGEPROFILE_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_SimpleChangeProfileClass, \
                                             obj, TYPE_DC_SIMPLECHANGEPROFILE)

#define DC_SIMPLECHANGEPROFILE_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_SimpleChangeProfileClass, \
                                           klass, TYPE_DC_SIMPLECHANGEPROFILE)

#define DC_SIMPLECHANGEPROFILE(obj) \
        OBJECT_CHECK(DC_SimpleChangeProfile, obj, TYPE_DC_SIMPLECHANGEPROFILE)


DC_SimpleChangeProfile* DC_SimpleChangeProfile_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the reference value against which the monitoring check is performed.
 * The reference value can be modified dynamically.
 * @see #doProfileCheck
 * @param refValue the value of the reference value
 */
void DC_SimpleChangeProfile_setReferenceValue
(
    DC_SimpleChangeProfile *This, 
    TD_Integer refValue
);

/**
 * Get the reference value.
 * @see #setReferenceValue
 * @return the value of the reference value
 */
TD_Integer DC_SimpleChangeProfile_getReferenceValue
(
    const DC_SimpleChangeProfile *This
);


#endif
