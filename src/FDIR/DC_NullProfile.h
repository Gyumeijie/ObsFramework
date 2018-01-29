//
//
// DC_NullProfile.h
//
//
// Change Record:


#ifndef DC_NULLPROFILE_H
#define DC_NULLPROFILE_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "MonitoringProfile.h"
#include "../Qom/object.h"


/*
 * Default component implementing a "null monitoring profile".
 * A null monitoring profile always reports "no deviation from profile".
 * This profile is typically useful as a placeholder where a component of type
 * <code>MonitoringProfile</code> is needed to complete the configuration of a component
 * but where there is no need to perform any profile monitoring check.
 * It is similarly useful where a variable must formally be subjected to 
 * profile monitoring but its value in fact not subject to any limitation.
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_NULLPROFILE "dc_nullprofile"

void DC_NullProfile_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_NullProfile {
    MonitoringProfile parent;
};


struct DC_NullProfileClass {
    MonitoringProfileClass parent_class;
};


#define DC_NULLPROFILE_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_NullProfileClass, obj, TYPE_DC_NULLPROFILE)

#define DC_NULLPROFILE_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_NullProfileClass, klass, TYPE_DC_NULLPROFILE)

#define DC_NULLPROFILE(obj) \
        OBJECT_CHECK(DC_NullProfile, obj, TYPE_DC_NULLPROFILE)


DC_NullProfile* DC_NullProfile_new(void);

#endif
