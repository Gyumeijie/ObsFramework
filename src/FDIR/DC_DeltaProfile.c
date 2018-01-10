//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DeltaProfile.c
//
// Version	1.1
// Date		07.01.03 (Version 1.0)
//          01.10.03 (Version 1.1)
// Author	A. Pasetti (P&P Software), R. Totaro
//
// Change Record:
//   Version 1.1: replaced double and int with TD_Float and TD_Integer

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "DC_DeltaProfile.h"

#include <math.h>



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_DeltaProfile_setDeltaThreshold
(
    DC_DeltaProfile *This, 
    TD_Float deltaThreshold
)
{
    assert(deltaThreshold > (TD_Float)0.0);
    This->deltaThreshold = deltaThreshold;
}

TD_Float DC_DeltaProfile_getDeltaThreshold(DC_DeltaProfile *This)
{
    assert(This->deltaThreshold > (TD_Float)0.0);
    return This->deltaThreshold;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Check whether the monitored value differs from its value at the previous
 * activation by more than the delta threshold.
 * If it does, a "deviation from profile" is reported.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *   if( ( abs(value-previousValue) > deltaThreshold ) && notFirst )
 *   {  previousValue = value;
 *      return MON_PROFILE_DEVIATION; 
 *   }
 *   notFirst = true;
 *   previousValue = value;   
 *   return NO_MON_PROFILE_DEVIATION; </PRE>
 * <p>
 * The value of the <code>notFirst</code> flag is initialized to 
 * 'false' by the constructor and by the reset operation. 
 * @see #reset
 * @see #DC_DeltaProfile
 * @param value the value of the monitored variable
 * @return true if the monitored variable is stuck, false otherwise
 */
static bool doProfileCheckForFloat(void *obj, TD_Float value)
{
    DC_DeltaProfile *This = DC_DELTAPROFILE(obj);

    assert(This->deltaThreshold > (TD_Float)0.0);

    if (This->notFirst && 
        fabs(value - This->previousValue) > (double)This->deltaThreshold) {
        This->previousValue = value;
        return MON_PROFILE_DEVIATION;
    } else {
        This->notFirst = true;
        This->previousValue = value;
        return NO_MON_PROFILE_DEVIATION;
    }
}

/**
 * Version of method <CODE>doProfileCheck(void)</CODE> for monitored variables 
 * of type integer. The check is performed by using the "TD_Float" version
 * of <code>doProfileCheck</code>.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *   return doProfileCheck( (TD_Float)value ); </PRE>
 * @see #doProfileCheck
 */
static bool doProfileCheckForInteger(void *obj, TD_Integer value)
{
    assert(deltaThreshold > (TD_Float)0.0);
    return doProfileCheckForFloat(obj, (TD_Float)value);
}


/**
 * Perform a class-specific configuration check on the monitoring
 * profile: verify that the delta threshold has a value greater than zero.
 * @return true if the monitoring profile is configured, false otherwise.
 */
static bool isObjectConfigured(void *obj)
{
   MonitoringProfileClass *mpc = GET_CLASS(TYPE_MONITORINGPROFILE);
   DC_DeltaProfile *This = DC_DELTAPROFILE(obj);

   return (CC_ROOTOBJECT_CLASS(mpc)->isObjectConfigured(obj) &&
           This->deltaThreshold > (TD_Float)0.0);
}

/**
 * Reset the delta monitoring profile check. With reference to the 
 * implementation of method <code>doProfileCheck(TD_Integer)</code>, a call to
 * this method causes the flag <code>notFirst</code> to be reset to 
 * 'false'.
 */
static void reset(void *obj)
{
    DC_DELTAPROFILE(obj)->notFirst = false;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    DC_DeltaProfile *This = DC_DELTAPROFILE(obj);

    CC_RootObject_setClassId((CC_RootObject*)obj, ID_DELTAPROFILE);
    This->deltaThreshold = (TD_Float)0.0;
    This->previousValue = (TD_Float)0.0;
    reset(obj);
}

DC_DeltaProfile* DC_DeltaProfile_new(void)
{
    return (DC_DeltaProfile*)object_new(TYPE_DC_DELTAPROFILE);
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    MonitoringProfileClass *mpc = MONITORINGPROFILE_CLASS(oc);
    mpc->doProfileCheckForInteger = doProfileCheckForInteger;
    mpc->doProfileCheckForFloat = doProfileCheckForFloat;
    mpc->reset = reset;

    CC_RootObjectClass *roc = CC_ROOTOBJECT_CLASS(oc);
    roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_DELTAPROFILE,
    .parent = TYPE_MONITORINGPROFILE,
    .instance_size = sizeof(DC_DeltaProfile),
    .abstract = false,
    .class_size = sizeof(DC_DeltaProfileClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_DeltaProfile_register(void)
{
    type_register_static(&type_info);
}
