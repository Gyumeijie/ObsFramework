//
//
// DC_OutOfRangeProfile.c
//
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "RangeProfile.h"
#include "DC_OutOfRangeProfile.h"



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Check whether the monitored value is outside the range.
 * If it is, a "devation from profile" is reported.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *   if( ( value<lowerBound) || (value>upperBound) )
 *      return MON_PROFILE_DEVIATION; 
 *   else
 *      return NO_MON_PROFILE_DEVIATION; </PRE>
 * <p>
 * @param value the value of the monitored variable
 * @return true if the monitored variable lies within the range, false otherwise
 */
static bool doProfileCheckForFloat(void *obj, TD_Float value)
{
    TD_Float low = RangeProfile_getLowerBound(obj);
    TD_Float upper = RangeProfile_getUpperBound(obj);

    assert(low < upper);

    return ((value < low) || (value > upper));
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    CC_RootObject_setClassId((CC_RootObject*)obj, ID_OUTOFRANGEPROFILE);
}

DC_OutOfRangeProfile* DC_OutOfRangeProfile_new(void)
{
    Object *obj = object_new(TYPE_DC_OUTOFRANGEPROFILE);
    return (DC_OutOfRangeProfile*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    MonitoringProfileClass *mpc = MONITORINGPROFILE_CLASS(oc);
    mpc->doProfileCheckForFloat = doProfileCheckForFloat;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_OUTOFRANGEPROFILE,
    .parent = TYPE_RANGEPROFILE,
    .instance_size = sizeof(DC_OutOfRangeProfile),
    .abstract = false,
    .class_size = sizeof(DC_OutOfRangeProfileClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_OutOfRangeProfile_register(void)
{
    type_register_static(&type_info);
}
