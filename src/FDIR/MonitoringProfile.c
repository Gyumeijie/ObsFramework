//
//
// MonitoringProfile.c
//
//
// Change Record:
//                the instance ID, is the class ID)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../Event/DC_EventRepository.h"
#include "MonitoringProfile.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

bool MonitoringProfile_floatDeviatesFromProfile(MonitoringProfile *This, 
                                                TD_Float value)
{
    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
    MonitoringProfileClass *mpc = MONITORINGPROFILE_GET_CLASS(This);

    bool outcome = NO_MON_PROFILE_DEVIATION;

    if (MonitoringProfile_isEnabled(This)) {
        if (mpc->doProfileCheckForFloat(This, value)) {
            dc_erc->create(dc_er, (CC_RootObject*)This, EVT_MON_PROFILE_VIOLATION);
            outcome = MON_PROFILE_DEVIATION;
        }
    }

    if (This->pNext != pNULL) {
        // recursively call the following function if pNext is not null
        if (MonitoringProfile_floatDeviatesFromProfile(This->pNext, value)) {
            outcome = MON_PROFILE_DEVIATION;
        }
    }
    return outcome;
}

bool MonitoringProfile_integerDeviatesFromProfile(MonitoringProfile *This,
                                                  TD_Integer value)
{
    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
    MonitoringProfileClass *mpc = MONITORINGPROFILE_GET_CLASS(This);

    bool outcome = NO_MON_PROFILE_DEVIATION;

    if (MonitoringProfile_isEnabled(This)) {
        if (mpc->doProfileCheckForInteger(This, value)) {
            dc_erc->create(dc_er, (CC_RootObject*)This, EVT_MON_PROFILE_VIOLATION);
            outcome = MON_PROFILE_DEVIATION;
        }
    }

    if (This->pNext != pNULL) {
        // recursively call the following function if pNext is not null
        if (MonitoringProfile_integerDeviatesFromProfile(This->pNext, value)) {
            outcome = MON_PROFILE_DEVIATION;
        }
    }
    return outcome;
}

void MonitoringProfile_setEnabled(MonitoringProfile *This, bool enableStatus)
{
    This->enableStatus = enableStatus;
}

bool MonitoringProfile_isEnabled(MonitoringProfile *This)
{
    return This->enableStatus;
}

void MonitoringProfile_setNextMonitoringProfile
(
    MonitoringProfile *This, 
    MonitoringProfile *pNextMonitoringProfile
)
{
    assert(pNextMonitoringProfile != pNULL);
    This->pNext = pNextMonitoringProfile;
}

MonitoringProfile* MonitoringProfile_getNextMonitoringProfile(MonitoringProfile *This)
{
    return This->pNext;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Reset the internal state of the monitoring profile to the value it had
 * immediately after instantiation.
 * Some monitoring profiles need to keep track of past values of the monitored
 * variable and therefore have
 * an internal state.
 * This method allows this internal state to be reset.
 * This class offers a default implementation of this method that does not
 * do anything.
 * Subclasses may need to override this default implementation.
 */
static void reset(void *obj)
{
    return;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Encapsulate the check of the monitored variable value against the
 * monitoring profile.
 * This method is called by method <CODE>deviatesFromProfile(void)</CODE>
 * in this same class.
 * User of monitoring profiles do not see <CODE>method doProfileCheck(void)</CODE>, 
 * they only see method
 * <CODE>deviatesFromProfile(void)</CODE>.
 * @see #deviatesFromProfile
 * @param value the value of the monitored variable
 * @return true if the monitored variable deviates from the monitoring profile, false otherwise
 */
static bool doProfileCheckForFloat(void *obj, TD_Float value)
{
    // this is automate genenrated by converter
}

/**
 * of integer type.
 * @see #doProfileCheck
 */
static bool doProfileCheckForInteger(void *obj, TD_Integer value)
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
    MonitoringProfile *This = MONITORINGPROFILE(obj);
        
    This->enableStatus = ENABLED;
    This->pNext = pNULL;
}

MonitoringProfile* MonitoringProfile_new(void)
{
    Object *obj = object_new(TYPE_MONITORINGPROFILE);
    return (MonitoringProfile*)obj;
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
    mpc->doProfileCheckForInteger = doProfileCheckForInteger;

    mpc->reset = reset;
}

static const TypeInfo type_info = {
    .name = TYPE_MONITORINGPROFILE,
    .parent = TYPE_CC_ROOTOBJECT,
    .instance_size = sizeof(MonitoringProfile),
    .abstract = true,
    .class_size = sizeof(MonitoringProfileClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void MonitoringProfile_register(void)
{
    type_register_static(&type_info);
}
