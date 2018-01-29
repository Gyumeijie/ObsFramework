//
//
// DC_StuckDataProfile.c
//
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "DC_StuckDataProfile.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_StuckDataProfile_setStuckThreshold
(
    DC_StuckDataProfile *This, 
    unsigned int stuckThreshold
)
{
    This->stuckThreshold = stuckThreshold;
}

unsigned int DC_StuckDataProfile_getStuckThreshold
(
    const DC_StuckDataProfile *This
)
{
    return This->stuckThreshold;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Check whether the monitored value is stuck.
 * If it is, a "devation from profile" is reported.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *   if( value == previousValue )
 *   {  counter++;
 *      previousValue = value;
 *      if(counter == stuckThreshold)
 *      { counter = 0;
 *        return MON_PROFILE_DEVIATION; 
 *      }
 *      else
 *        return NO_MON_PROFILE_DEVIATION; 
 *   }
 *   else
 *      counter = 0;
 *   previousValue = value;   
 *   return NO_MON_PROFILE_DEVIATION; </PRE>
 * <p>
 * The value of <code>previousValue</code> and <code>counter</code>
 * are initialized by the constructor and by method <code>reset</code>. 
 * Spurious triggerings can occurr either after a reset or after the
 * component is created.
 * @see #reset
 * @see #DC_StuckDataProfile
 * @param value the value of the monitored variable
 * @return true if the monitored variable is stuck, false otherwise
 */
static bool doProfileCheckForInteger(void *obj, TD_Integer value)
{
    DC_StuckDataProfile *This = DC_STUCKDATAPROFILE(obj);

    assert(This->counter < (This->stuckThreshold + 1));

    if (value != This->previousValue) {
        This->counter = 0;
        This->previousValue = value;
    } else {
        This->counter++;
        if (This->counter == This->stuckThreshold) {
            This->counter = 0;
            return MON_PROFILE_DEVIATION; 
        }
    }

    return NO_MON_PROFILE_DEVIATION;
}

/**
 * Dummy implementation of a monitoring check that always returns "deviation
 * from profile detected".
 * This operation should never be called since stuck data monitoring checks on
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

/**
 * Perform a class-specific configuration check on the monitoring
 * profile: verify that the stuck threshold has a value greater than zero.
 * @return true if the monitoring profile is configured, false otherwise.
 */
static bool isObjectConfigured(void *obj)
{
   MonitoringProfileClass *mpc = GET_CLASS(TYPE_MONITORINGPROFILE);
   DC_StuckDataProfile *This = DC_STUCKDATAPROFILE(obj);

   return ((CC_ROOTOBJECT_CLASS(mpc)->isObjectConfigured(obj)) &&
           (This->stuckThreshold > 0));
}

/**
 * Reset the stuck value profile check. With reference to the 
 * implementation of method <code>doProfileCheck(TD_Integer)</code>, a call to
 * this method causes the variable <code>counter</code> to be reset to
 * zero and the variable <code>previousValue</code> to be reset to 
 * PREVIOUS_VALUE_INIT.
 */
static void reset(void *obj)
{
    DC_StuckDataProfile *This = DC_STUCKDATAPROFILE(obj);

    This->counter = 0;
    This->previousValue = PREVIOUS_VALUE_INIT;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    DC_StuckDataProfile *This = DC_STUCKDATAPROFILE(obj);
    This->stuckThreshold = 0;

    reset(obj);

    CC_RootObject_setClassId((CC_RootObject*)obj, ID_STUCKDATAPROFILE);
}

DC_StuckDataProfile* DC_StuckDataProfile_new(void)
{
    Object *obj = object_new(TYPE_DC_STUCKDATAPROFILE);
    return (DC_StuckDataProfile*)obj;
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
    .name = TYPE_DC_STUCKDATAPROFILE,
    .parent = TYPE_MONITORINGPROFILE,
    .instance_size = sizeof(DC_StuckDataProfile),
    .abstract = false,
    .class_size = sizeof(DC_StuckDataProfileClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_StuckDataProfile_register(void)
{
    type_register_static(&type_info);
}
