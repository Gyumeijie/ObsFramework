//
//
// MonitoringProfile.h
//
//
// Change Record:


#ifndef MONITORINGPROFILE_H
#define MONITORINGPROFILE_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "../Qom/object.h"


/*
 * Base class from which all monitoring profile classes are derived.
 * A monitoring profile encapsulates a profile against which the value
 * of a monitored variable must be checked(<i>monitoring check</i>).
 * Two versions of the monitoring check are offered by this class,
 * one for monitored variables of <code>TD_Float</code> type and one for monitored
 * variables of <code>TD_Integer</code> type.
 * <p>
 * Monitoring profiles can be enabled or disabled.
 * A monitoring profile that is disabled will always report:
 * "no deviation from profile".
 * <p>
 * Monitoring profiles can be linked in sequential
 * chains. The client only sees one single monitoring profile(the one
 * at the head of the chain) but its execution can lead to all profiles 
 * in the chain being executed in sequence. This class defines a <i>next monitoring
 * profile</i> attribute that holds the pointer to the next monitoring profile in the
 * chain. A monitoring profile reports "no profile violation detected" only if
 * neither itself nor any of the monitoring profiles downstream in the chain of
 * linked profiles report "no profile violation detected".
 * <p>
 * A violation of a monitoring profile is reported as an event.
 * <p>
 * This class is abstract because the implementation of the monitoring
 * profile is class-specific and must be defined in the derived classes
 * that implement concrete profiles.
 * The management of the enable status and the reporting of profile
 * violation as events is however performed in this base class.
 * @todo Add an internal variable that to record the reason for the violation
 * and that concrete monitoring profiles can set to indicate how the profile
 * was violated(e.g. violation of upper boundary of a range interval). Clients
 * can then inspect the value of this variable to know the exact reason of the
 * profile violation.
 * @todo Add a test case to cover the "next monitoring profile" functionality.
 * This could be obtained by modifying the test case of DC_ProfileList.
 * @todo Monitoring profiles use parameters that are implemented as internal variables.
 * In practice, these parameters will often have to come from the parameter database.
 * Two solutions are possible: generators are used to parameterize the concrete 
 * monitoring profiles classes with respect to the mode of implementation of the
 * profile parameters. Or aspect programs are used modify the monitoring profile class
 * as follows: code to set the link to the parameter database is inserted, and 
 * code to update the value of the internal parameter with the value read from the
 * parameter database is added at the beginning of method doProfileCheck.
 * @author Alessandro Pasetti 
 * @author Roberto Totaro
 * @version 1.0
 * @ingroup FDIR
 */
#define TYPE_MONITORINGPROFILE "monitoringprofile"

void MonitoringProfile_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct MonitoringProfile {
    CC_RootObject parent;

    bool enableStatus;
    MonitoringProfile *pNext;
};


struct MonitoringProfileClass {
    CC_RootObjectClass parent_class;
 
    void (*reset)(void *obj);
 
    bool (*doProfileCheckForFloat)(void *obj, TD_Float value);
    bool (*doProfileCheckForInteger)(void *obj, TD_Integer value);
};


#define MONITORINGPROFILE_GET_CLASS(obj) \
        OBJECT_GET_CLASS(MonitoringProfileClass, obj, TYPE_MONITORINGPROFILE)

#define MONITORINGPROFILE_CLASS(klass) \
        OBJECT_CLASS_CHECK(MonitoringProfileClass, klass, TYPE_MONITORINGPROFILE)

#define MONITORINGPROFILE(obj) \
        OBJECT_CHECK(MonitoringProfile, obj, TYPE_MONITORINGPROFILE)


MonitoringProfile* MonitoringProfile_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Check whether the value of the monitored variable - passed as an argument
 * to the method - is within
 * the profile encapsulated by the monitoring profile object.
 * The check is only done if the monitoring profile object is enabled.
 * If it is disabled, the method returns true indicating that there is no
 * deviation from the profile.
 * After performing the monitoring check encapsulated by this class, 
 * it is verified whether there are any linked monitoring checks and, if
 * so, the check value is passed on to them. A return value of "deviation
 * detected" may indicate either that this check has detected a violation
 * or that a violation has been detected by the next monitoring profile 
 * in the chain.
 * <p>
 * A pseudo-code implementation for this method is as follows: <PRE>
 *   bool outcome = NO_MON_PROFILE_DEVIATION;
 *   MonitoringProfile_if( MonitoringProfile_isEnabled(void) )
 *   { MonitoringProfile_if(MonitoringProfile_doProfileCheck(value))
 *     { MonitoringProfile_createEventRepor t(MonitoringProfile *This, EVT_MON_PROFILE_VIOLATION);
 *       outcome = MON_PROFILE_DEVIATION;
 *     }
 *   }
 *   MonitoringProfile_if( pNext!=pNULL )     // there is a next monitoring profile 
 *      MonitoringProfile_if( next->MonitoringProfile_deviatesFromProfile(value) )
 *          outcome = MON_PROFILE_DEVIATION;
 *   return outcome; </PRE>
 * The <CODE>MonitoringProfile_doProfileCheck(void)</CODE> method is abstract and encapsulates
 * the implementation of the profile check.
 * Thus, this class enforces the management of the enabled status and 
 * of the "next monitoring profile" but delegates implementation of the
 * monitoring profile check to derived classes implementing concrete profiles.
 * An event is created when deviations from the profile are detected.
 * The event parameter is the class identifier of the monitoring profile
 * object itself.
 * @param value the value of the monitored variable
 * @return true if the monitored variable deviates from the monitoring profile, 
 * false otherwise
 */
bool MonitoringProfile_floatDeviatesFromProfile
(
    MonitoringProfile *This, 
    TD_Float value
);

/**
 * variables of integer type.
 * @see #deviatesFromProfile
 */
bool MonitoringProfile_integerDeviatesFromProfile
(
    MonitoringProfile *This, 
    TD_Integer value
);

/**
 * Set the enable status of the monitoring profile.
 * When the profile is disabled, a call to method <CODE>MonitoringProfile_deviatesFromProfile(void)</CODE>
 * always returns "no deviation from profile".
 * @param enableStatus if true, then the profile is enabled; if false, then
 * the profile is disabled
 */
void MonitoringProfile_setEnabled(MonitoringProfile *This, bool enableStatus);

/**
 * Check the enable status of the monitoring profile.
 * @return true if the profile is enabled, false otherwise
 */
bool MonitoringProfile_isEnabled(MonitoringProfile *This);

/**
 * Set the next monitoring profile.
 * @see #deviatesFromProfile
 * @param pNextMonitoringProfile the next monitoring profile
 */
void MonitoringProfile_setNextMonitoringProfile
(
    MonitoringProfile *This,
    MonitoringProfile *pNextMonitoringProfile
);

/**
 * Get the next monitoring profile. If no monitoring profile has been chained
 * to this one, then a value of pNULL is returned.
 * @see #deviatesFromProfile
 * @return the next monitoring profile
 */
MonitoringProfile* MonitoringProfile_getNextMonitoringProfile(MonitoringProfile *This);


#endif
