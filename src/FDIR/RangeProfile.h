//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// RangeProfile.h
//
// Version	1.1
// Date		16.01.03 (Version 1.0)
//          01.10.03 (Version 1.1)
// Author	A. Pasetti(P&P Software), R. Totaro
//
// Change Record:
//   Version 1.1: replaced double and int with TD_Float and TD_Integer


#ifndef RANGEPROFILE_H
#define RANGEPROFILE_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "MonitoringProfile.h"
#include "../Qom/object.h"


/*
 * Base class for monitoring profile components that
 * build a monitoring check as a function of a range interval. 
 * The range interval is
 * characterized by a <i>lower bound</i> and by an <i>upper bound</i>
 * and takes the following form: [lowerBound, upperBound].
 * The lower and upper bounds are settable parameter. The upper bound
 * is constrained to be greater than the lower bound.
 * <p>
 * This class is abstract because it does not define any specific
 * monitoring checks. It only provides the services to define the
 * range interval
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_RANGEPROFILE "rangeprofile"

void RangeProfile_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct RangeProfile {
    MonitoringProfile parent;

    TD_Float lowerBound;
    TD_Float upperBound;
};


struct RangeProfileClass {
    MonitoringProfileClass parent_class;
};


#define RANGEPROFILE_GET_CLASS(obj) \
        OBJECT_GET_CLASS(RangeProfileClass, obj, TYPE_RANGEPROFILE)

#define RANGEPROFILE_CLASS(klass) \
        OBJECT_CLASS_CHECK(RangeProfileClass, klass, TYPE_RANGEPROFILE)

#define RANGEPROFILE(obj) \
        OBJECT_CHECK(RangeProfile, obj, TYPE_RANGEPROFILE)


RangeProfile* RangeProfile_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the lower bound.
 * @param lowerBound the value of the lower bound
 */
void RangeProfile_setLowerBound(RangeProfile *This, TD_Float lowerBound);

/**
 * Set the upper bound.
 * @param upperBound the value of the lower bound
 */
void RangeProfile_setUpperBound(RangeProfile *This, TD_Float upperBound);

/**
 * Get the lower bound.
 * @return the value of the lower bound
 */
TD_Float RangeProfile_getLowerBound(const RangeProfile *This);

/**
 * Get the upper bound.
 * @return the value of the lower bound
 */
TD_Float RangeProfile_getUpperBound(const RangeProfile *This);


#endif
