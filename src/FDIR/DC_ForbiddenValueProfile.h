//
//
// DC_ForbiddenValueProfile.h
//
//
// Change Record:


#ifndef DC_FORBIDDENVALUEPROFILE_H
#define DC_FORBIDDENVALUEPROFILE_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "MonitoringProfile.h"
#include "../Qom/object.h"


/*
 * Default component implementing a forbidden value monitoring profile.
 * This monitoring profile reports a "deviation from profile" if the 
 * value of the monitored variable is equal to a pre-specified 
 * <i>forbidden value</i>. The forbidden value is a settable parameter. 
 * <p>
 * This type of check only makes sense for monitored variables of
 * integer type. The version of the monitoring check for variables
 * of doble type is therefore implemented as a dummy operation
 * that always returns "deviation from profile has been detected".
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @author Roberto Totaro
 * @version 1.1
 */
#define TYPE_DC_FORBIDDENVALUEPROFILE "dc_forbiddenvalueprofile"

void DC_ForbiddenValueProfile_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_ForbiddenValueProfile {
    MonitoringProfile parent;

    TD_Integer forbiddenValue;
};


struct DC_ForbiddenValueProfileClass {
    MonitoringProfileClass parent_class;
};


#define DC_FORBIDDENVALUEPROFILE_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_ForbiddenValueProfileClass,\
                                            obj, TYPE_DC_FORBIDDENVALUEPROFILE)

#define DC_FORBIDDENVALUEPROFILE_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_ForbiddenValueProfileClass,\
                                          klass, TYPE_DC_FORBIDDENVALUEPROFILE)

#define DC_FORBIDDENVALUEPROFILE(obj) \
        OBJECT_CHECK(DC_ForbiddenValueProfile,\
                                            obj, TYPE_DC_FORBIDDENVALUEPROFILE)


DC_ForbiddenValueProfile* DC_ForbiddenValueProfile_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the forbidden value against which the monitoring check is performed.
 * The forbidden value can be modified dynamically.
 * @see #doProfileCheck
 * @param forbiddenValue the forbidden value 
 */
void DC_ForbiddenValueProfile_setForbiddenValue
(
    DC_ForbiddenValueProfile *This,
    TD_Integer forbiddenValue
);

/**
 * Get the forbidden value.
 * @see #setForbiddenValue
 * @return the value of the reference value
 */
TD_Integer 
DC_ForbiddenValueProfile_getForbiddenValue(const DC_ForbiddenValueProfile *This);


#endif
