//
//
// RangeProfile.c
//
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "RangeProfile.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void RangeProfile_setLowerBound(RangeProfile *This, TD_Float lowerBound)
{
    This->lowerBound = lowerBound;
}

void RangeProfile_setUpperBound(RangeProfile *This, TD_Float upperBound)
{
    This->upperBound = upperBound;
}

TD_Float RangeProfile_getLowerBound(const RangeProfile *This)
{
	return This->lowerBound;
}

TD_Float RangeProfile_getUpperBound(const RangeProfile *This)
{
	return This->upperBound;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * of type TD_Integer. The check is performed by using the "TD_Float" version
 * of <code>doProfileCheck</code>.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *   return doProfileCheck( (TD_Float)value ); </PRE>
 * @see #doProfileCheck
 */
static bool doProfileCheckForInteger(void *obj, TD_Integer value)
{
    MonitoringProfileClass *mpc = MONITORINGPROFILE_GET_CLASS(obj);
    RangeProfile *This = RANGEPROFILE(obj);

    assert(This->lowerBound < This->upperBound);
    return mpc->doProfileCheckForFloat(obj, (TD_Float)value);
}

/**
 * Perform a class-specific configuration check on the range monitoring
 * profile: verify that the lower bound is smaller than the upper bound.
 * @return true if the monitoring profile is configured, false otherwise.
 */
static bool isObjectConfigured(void *obj)
{ 
    MonitoringProfileClass *mpc = GET_CLASS(TYPE_MONITORINGPROFILE);
    RangeProfile *This = RANGEPROFILE(obj);

    return ((CC_ROOTOBJECT_CLASS(mpc)->isObjectConfigured(obj)) &&
            (This->lowerBound < This->upperBound));
}



///////////////////////////////////////////////////////////////////////////////
//
//                    pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * This method shall be implemented by the derived classes.
 */
static bool doProfileCheckForFloat(void *obj, TD_Float value)
{
    // this is automate genenrated by converter
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    RangeProfile *This = RANGEPROFILE(obj);

    This->lowerBound = (TD_Float)0.0;
    This->upperBound = (TD_Float)0.0;
}

RangeProfile* RangeProfile_new(void)
{
    Object *obj = object_new(TYPE_RANGEPROFILE);
    return (RangeProfile*)obj;
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

    CC_RootObjectClass *roc = CC_ROOTOBJECT_CLASS(oc);
    roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_RANGEPROFILE,
    .parent = TYPE_MONITORINGPROFILE,
    .instance_size = sizeof(RangeProfile),
    .abstract = true,
    .class_size = sizeof(RangeProfileClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void RangeProfile_register(void)
{
    type_register_static(&type_info);
}
