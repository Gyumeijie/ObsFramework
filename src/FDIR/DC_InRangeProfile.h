//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_InRangeProfile.h
//
// Version	1.1
// Date		16.01.03 (Version 1.0)
//          01.10.03 (Version 1.1)
// Author	A. Pasetti(P&P Software), R. Totaro
//
// Change Record:
//   Version 1.1: replaced double and int with TD_Float and TD_Integer


#ifndef DC_INRANGEPROFILE_H
#define DC_INRANGEPROFILE_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "RangeProfile.h"
#include "../Qom/object.h"


/*
 * Default component implementing an "in range" monitoring profile.
 * This monitoring profile reports a "deviation from profile" if the 
 * value of the monitored variable lies inside a predefined
 * range interval [lowerBound, upperBound].  
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_INRANGEPROFILE "dc_inrangeprofile"

void DC_InRangeProfile_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_InRangeProfile {
    RangeProfile parent;
};


struct DC_InRangeProfileClass {
    RangeProfileClass parent_class;
};


#define DC_INRANGEPROFILE_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_InRangeProfileClass, obj, TYPE_DC_INRANGEPROFILE)

#define DC_INRANGEPROFILE_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_InRangeProfileClass, klass, TYPE_DC_INRANGEPROFILE)

#define DC_INRANGEPROFILE(obj) \
        OBJECT_CHECK(DC_InRangeProfile, obj, TYPE_DC_INRANGEPROFILE)


DC_InRangeProfile* DC_InRangeProfile_new(void);

#endif
