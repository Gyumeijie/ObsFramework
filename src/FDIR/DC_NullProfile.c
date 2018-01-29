//
//
// DC_NullProfile.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "DC_NullProfile.h"



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Always return "no deviation from profile"
 * @param value the value of the monitored variable
 * @return alway returns false 
 */
static bool doProfileCheckForInteger(void *obj, TD_Integer value)
{
    return NO_MON_PROFILE_DEVIATION;
}

/**
 * Always return "no deviation from profile"
 * @param value the value of the monitored variable
 * @return alway returns false 
 */
static bool doProfileCheckForFloat(void *obj, TD_Float value)
{
    return NO_MON_PROFILE_DEVIATION;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    CC_RootObject_setClassId((CC_RootObject*)obj, ID_NULLPROFILE);
}

DC_NullProfile* DC_NullProfile_new(void)
{
    Object *obj = object_new(TYPE_DC_NULLPROFILE);
    return (DC_NullProfile*)obj;
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
    .name = TYPE_DC_NULLPROFILE,
    .parent = TYPE_MONITORINGPROFILE,
    .instance_size = sizeof(DC_NullProfile),
    .abstract = false,
    .class_size = sizeof(DC_NullProfileClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_NullProfile_register(void)
{
    type_register_static(&type_info);
}
