//
//
// DC_OutOfRangeProfile.h
//
//
// Change Record:


#ifndef DC_OUTOFRANGEPROFILE_H
#define DC_OUTOFRANGEPROFILE_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "RangeProfile.h"
#include "../Qom/object.h"


/*
 * Default component implementing an "out of range" monitoring profile.
 * This monitoring profile reports a "deviation from profile" if the 
 * value of the monitored variable lies outside a predefined
 * range interval [lowerBound, upperBound].  
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @author Roberto Totaro
 * @version 1.1
 */
#define TYPE_DC_OUTOFRANGEPROFILE "dc_outofrangeprofile"

void DC_OutOfRangeProfile_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_OutOfRangeProfile {
    RangeProfile parent;
};


struct DC_OutOfRangeProfileClass {
    RangeProfileClass parent_class;
};


#define DC_OUTOFRANGEPROFILE_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_OutOfRangeProfileClass,\
                                                obj, TYPE_DC_OUTOFRANGEPROFILE)

#define DC_OUTOFRANGEPROFILE_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_OutOfRangeProfileClass,\
                                              klass, TYPE_DC_OUTOFRANGEPROFILE)

#define DC_OUTOFRANGEPROFILE(obj) \
        OBJECT_CHECK(DC_OutOfRangeProfile, obj, TYPE_DC_OUTOFRANGEPROFILE)


DC_OutOfRangeProfile* DC_OutOfRangeProfile_new(void);

#endif
