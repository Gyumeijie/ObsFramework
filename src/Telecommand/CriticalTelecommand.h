//
//
// CriticalTelecommand.h
//


#ifndef CRITICALTELECOMMAND_H
#define CRITICALTELECOMMAND_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Telecommand/Telecommand.h"
#include "../Qom/object.h"


/*
 * Base class for telecommands with a potentially high criticality
 * level.
 * This is an abstract class. Concrete telecommands are obtained by
 * deriving this class.
 * <p>
 * This class adds to the basic functionalities defined by its base
 * class the possibility of marking a telecommand as <i>critical</i>.
 * Telecommands that are marked critical are executed according to an
 * "arm-fire" protocol. The basic idea is that the first time the
 * telecommand receives an execute request, it does not take any
 * action but it sets an internal status to "armed". The actual
 * execution of the telecommand only occurs when the second execute
 * request is received. The two execution requests must not occur too
 * far from each other in time and they must be made with exactly the
 * same set of parameters. The precise implementation of the "arm-fire"
 * mechanism is described below.
 * <p>
 * The telecommand can be in one of two states: <ul>
 * <li><i>NotArmed</i>: the telecommand is not armed</li>
 * <li><i>Armed</i>: the telecommand has been armed and is now ready
 * to execute</li>
 * </ul>
 * The arm status is maintained by the execution check(see comment
 * of method <code>canExecute</code>).
 * <p>
 * The telecommand maintains a <i>maximum armed duration</i>. Its
 * value represents the maximum time that can elapse between the
 * time when the "arm" command was received and the time when the
 * "fire" command is received. If the "fire" command is received after
 * this interval as elapsed, then an event report
 * is created to record the fact.
 * <p>
 * The telecommand defines an <i>image store</i> service and an
 * <i>image validity</i> check. Their purpose is to allow to verify that
 * telecommand parameters at the time the "arm" command is received
 * are the same as when the "fire" command is received. The image
 * store service allows the current values of the telecommand parameters
 * to be stored in some internal data structure. The image validity check
 * allows the current values of the telecomand parameters to be compared
 * with the values that were stored in the last call to the image store
 * service.
 * <p>
 * The criticality level of the telecommand can be set by the user.
 * The criticality level can have two values: <i>not critical</i> and
 * <i>critical</i>. If the telecommand is marked not critical, then
 * it behaves exactly as an instance of its super class.
 * <p>
 * This implementation of the "arm-fire" mechanism stores the information
 * about the arm status and about the telecommand parameters into the
 * telecommand component itself. Note in particular that the standard
 * telecommand manager provided by the OBS Framework(<code>CC_TelecommandManager</code>),
 * is not aware of whether a given telecommand is critical or not.
 * It is therefore the responsibility of the user to ensure that the
 * same component is loaded into the telecommand manager when the telecommand
 * is received the first time("arm command") and when it is received the
 * second time("fire command").
 * @see CC_TelecommandManager
 * @author Alessandro Pasetti
 * @author Roberto Totaro
 * @version 1.0
 * @ingroup Telecommand
 */
#define TYPE_CRITICALTELECOMMAND "criticaltelecommand"

void CriticalTelecommand_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct CriticalTelecommand {
    Telecommand parent;

    TD_ObsTime maxArmedDuration;
    TD_ObsTime timeWhenArmed;
    ObsClock *pObsClock;
    bool isTcCritical;
    bool isTcArmed;
};


struct CriticalTelecommandClass {
    TelecommandClass parent_class;
 
    bool (*isImageValid)(void *obj);
    void (*storeImage)(void *obj);
 
    TD_ActionOutcome (*doCriticalAction)(void *obj);
};


#define CRITICALTELECOMMAND_GET_CLASS(obj) \
        OBJECT_GET_CLASS(CriticalTelecommandClass, obj, TYPE_CRITICALTELECOMMAND)

#define CRITICALTELECOMMAND_CLASS(klass) \
        OBJECT_CLASS_CHECK(CriticalTelecommandClass, klass, TYPE_CRITICALTELECOMMAND)

#define CRITICALTELECOMMAND(obj) \
        OBJECT_CHECK(CriticalTelecommand, obj, TYPE_CRITICALTELECOMMAND)


CriticalTelecommand* CriticalTelecommand_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Reverts the telecommand to its original CriticalTelecommand_state(i.e. 
 * isTcCritical=CRITICAL, * isTcArmed=NOT_ARMED, timeWhenArmed=-1, 
 * maxArmedDuration=-1, pObsClock=pNULL).
 */
void CriticalTelecommand_reset(CriticalTelecommand *This);

/**
 * Return the criticality level of the telecommand.
 * @return true if the telecommand is critical, false otherwise
 */
bool CriticalTelecommand_isCritical(CriticalTelecommand *This);

/**
 * Set the criticality level. This method would normally be called during
 * the component initialization CriticalTelecommand_phase(probably by the 
 * constructor of * the concrete telecommand class).
 * @param isCritical if true, the telecommand is marked "critical", 
 * otherwise it is marked "not critical"
 */
void CriticalTelecommand_setCriticalityLevel
(
    CriticalTelecommand *This, 
    bool isCritical
);

/**
 * Return the arm status of the telecommand. If the criticality level
 * of the telecommand is "not critical", this method always returns
 * "not armed".
 * @return true if the telecommand is armed, false otherwise
 */
bool CriticalTelecommand_isArmed(CriticalTelecommand *This);

/**
 * Set the maximum armed duration.
 * @param t the maximum armed duration
 * @see #canExecute
 */
void CriticalTelecommand_setMaxArmedDuration
(
    CriticalTelecommand *This, 
    TD_ObsTime t
);

/**
 * Get the maximum armed duration.
 * @return the maximum armed duration
 */
TD_ObsTime CriticalTelecommand_getMaxArmedDuration(CriticalTelecommand *This);

/**
 * Get the value of the on-board time when the telecommand was last armed.
 * If the telecommand was never armed, a value of zero is returned.
 * @return the on-board time when the telecommand was last armed
 */
TD_ObsTime CriticalTelecommand_getTimeWhenArmed(CriticalTelecommand *This);

/**
 * Load the OBS Clock component. Critical telecommands need access to the
 * on-board clock to time-stamp the reception of an "arm" command.
 * @param pObsClock the OBS Clock component.
 */
void CriticalTelecommand_setObsClock
(
    CriticalTelecommand *This, 
    ObsClock *pObsClock
);

/**
 * Return the OBS Clock component.
 * @see #setObsClock
 * @return the OBS Clock component.
 */
ObsClock* CriticalTelecommand_getObsClock(const CriticalTelecommand *This);


#endif
