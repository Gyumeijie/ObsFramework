//
//
// DC_SimpleChangeProfile.c
//
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "DC_SimpleChangeProfile.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_SimpleChangeProfile_setReferenceValue
(
    DC_SimpleChangeProfile *This, 
    TD_Integer refValue
)
{
    This->referenceValue = refValue;
}

TD_Integer DC_SimpleChangeProfile_getReferenceValue
(
    const DC_SimpleChangeProfile *This
)
{
    return This->referenceValue;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Check whether the monitored value is different from the reference value.
 * If it is, a "devation from profile" is reported.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *   if( value != refValue )
 *     return MON_PROFILE_DEVIATION;
 *   return NO_MON_PROFILE_DEVIATION; </PRE>
 * <p>
 * @param value the value of the monitored variable
 * @return true if the monitored variable is different from the reference value, 
 * false otherwise
 */
static bool doProfileCheckForInteger(void *obj, TD_Integer value)
{
    DC_SimpleChangeProfile *This = DC_SIMPLECHANGEPROFILE(obj);
    return (value != This->referenceValue); 
}

/**
 * Dummy implementation of a monitoring check that always returns "deviation
 * from profile detected".
 * This operation should never be called since simple monitoring check on
 * non-integer variables may give unpredictable results due to numerical
 * precision errors.
 * @param value the value of the monitored variable
 * @return always returns true 
 */
static bool doProfileCheckForFloat(void *obj, TD_Float value)
{
    assert(false);
    return MON_PROFILE_DEVIATION;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    DC_SimpleChangeProfile *This = DC_SIMPLECHANGEPROFILE(obj);
    This->referenceValue = 0;

    CC_RootObject_setClassId((CC_RootObject*)obj, ID_SIMPLECHANGEPROFILE);
}

DC_SimpleChangeProfile* DC_SimpleChangeProfile_new(void)
{
    return (DC_SimpleChangeProfile*)object_new(TYPE_DC_SIMPLECHANGEPROFILE);
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
}

static const TypeInfo type_info = {
    .name = TYPE_DC_SIMPLECHANGEPROFILE,
    .parent = TYPE_MONITORINGPROFILE,
    .instance_size = sizeof(DC_SimpleChangeProfile),
    .abstract = false,
    .class_size = sizeof(DC_SimpleChangeProfileClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_SimpleChangeProfile_register(void)
{
    type_register_static(&type_info);
}
