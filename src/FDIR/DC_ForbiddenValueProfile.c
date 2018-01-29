//
//
// DC_ForbiddenValueProfile.c
//
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "DC_ForbiddenValueProfile.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_ForbiddenValueProfile_setForbiddenValue
(
    DC_ForbiddenValueProfile *This, 
    TD_Integer forbiddenValue
)
{
    This->forbiddenValue = forbiddenValue;
}

TD_Integer DC_ForbiddenValueProfile_getForbiddenValue
(
    const DC_ForbiddenValueProfile *This
)
{
    return This->forbiddenValue;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Check whether the monitored value is equal to the forbidden value.
 * If it is, a "devation from profile" is reported.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *   if( value == forbiddenValue )
 *     return MON_PROFILE_DEVIATION;
 *   return NO_MON_PROFILE_DEVIATION; </PRE>
 * <p>
 * @param value the value of the monitored variable
 * @return true if the monitored variable is equal to the forbidden value, 
 * false otherwise
 */
static bool doProfileCheckForInteger(void *obj, TD_Integer value)
{
    DC_ForbiddenValueProfile *This = DC_FORBIDDENVALUEPROFILE(obj);
    return (value == This->forbiddenValue);
}

/**
 * Dummy implementation of a monitoring check that always returns "deviation
 * from profile detected".
 * This operation should never be called since a forbidden value monitoring 
 * check on
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
    DC_ForbiddenValueProfile *This = DC_FORBIDDENVALUEPROFILE(obj);
    This->forbiddenValue = 0;

    CC_RootObject_setClassId((CC_RootObject*)obj, ID_FORBIDDENVALUEPROFILE);
}

DC_ForbiddenValueProfile* DC_ForbiddenValueProfile_new(void)
{
    Object *obj = object_new(TYPE_DC_FORBIDDENVALUEPROFILE);
    return (DC_ForbiddenValueProfile*)obj;
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
    .name = TYPE_DC_FORBIDDENVALUEPROFILE,
    .parent = TYPE_MONITORINGPROFILE,
    .instance_size = sizeof(DC_ForbiddenValueProfile),
    .abstract = false,
    .class_size = sizeof(DC_ForbiddenValueProfileClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_ForbiddenValueProfile_register(void)
{
    type_register_static(&type_info);
}
