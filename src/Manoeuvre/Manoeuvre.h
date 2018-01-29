//
//
// Manoeuvre.h
//


#ifndef MANOEUVRE_H
#define MANOEUVRE_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "../Qom/object.h"


/*
 * Base class from which all manoeuvre classes are derived.
 * A manoeuvre is primarily characterized by its ability to encapsulate
 * an action that takes place over a period of time. In this sense, it
 * is opposed to a <i>punctual action</i> which instead encapsulates
 * an action that takes place "in one shot".
 * More specifically, manoeuvres are
 * characterized by three types of <i>actions</i> and three
 * types of <i>checks</i> which they can
 * perform. The actions are:<ul>
 * <li>An <i>initialization action</i> that is executed once when the
 * manoeuvre first becomes due for execution.</li>
 * <li>A <i>continuation action</i> that is executed repeatedly until the
 * manoeuvre has terminated execution.</li>
 * <li>A <i>termination action</i> that is executed once when the manoeuvre
 * has terminated execution.</li>
 * </ul>
 * An <i>activation step counter</i> is associated to the continuation
 * action. This is initialized to zero when the manoeuvre starts execution
 * and is incremented by one every time the continuation action is advanced
 * by a step(i.e. every time method <code>doInternalContinue</code> is
 * executed). This counter helps other components keep track of the progress
 * of the manoeuvre.
 * <p>
 * The three checks that are associated to a manoeuvre are:<ul>
 * <li>A <i>start check</i> to be performed just before launching
 * execution of a manoeuvre. It verifies whether the manoeuvre is
 * ready to start execution.</li>
 * <li>A <i>continuation check</i> to be performed while the manoeuvre
 * is executing to verify whether continuation can be continued
 * or whether the manoeuvre should be aborted. </li>
 * <li>A <i>termination check</i> to be performed before terminating
 * execution of the manoeuvre. It checks whether the manoeuvre has
 * terminated its execution and whether it should be terminated.
 * </ul>
 * This class is abstract. Concrete manoeuvre actions and manoeuvre
 * checks are defined by subclasses. This class provides either default
 * trivial implementations or leaves the implementation of the actions
 * and checks undefined.
 * <p>
 * Execution of a manoeuvre as defined here must respect certain
 * constraints(e.g. a start check should be performed before
 * starting execution of a manoeuvre, a termination action should
 * be performed before terminating execution of a manoeuvre, etc).
 * Manoeuvres are defined here as low-level components that cannot
 * take responsibility for their own execution. They are intended
 * to be <i>loaded</i> into some other component that is then
 * responsible for calling their methods in the correct sequence
 * and in compliance with the constraints defined by the present
 * interface. This class implements assertions that, to some
 * extent, ensure that the manoeuvre is used correctly but
 * responsibility for correct usage lies with the component managing
 * a manoeuvre.
 * In the OBS Framework, manoeuvres are normally loaded in the
 * <i>manoeuvre manager</i> (instance of class <code>CC_ManoeuvreManager</code>)
 * which then becomes responsible for their execution.
 * <p>
 * This class additionally manages three boolean flags: <i>isExecuting</i>,
 * <i>inUse</i>, and <i>isSuspended</i>.
 * Flag isExecuting is set to true immediately after the execution of
 * the manoeuvre starts and is reset
 * to false when execution has terminated or the manoeuvre is aborted.
 * This flag is useful for external entities that wish to check whether
 * a manoeuvre is actually executing.
 * <p>
 * Manoeuvres are intended to be used by some other components. Since they have
 * an internal state, they cannot normally be used by more than one component at
 * a time. Flag inUse helps prevent this type of conflict. The component that
 * uses the manoeuvre should set it when it starts using it and should reset it
 * when it finishes using it. Normally, the management of the inUse flag is done
 * jointly by the manoeuvre factory component(instance of class <code>CC_ManoeuvreFactory</code>)
 * and by the manoeuvre manager.
 * <p>
 * Flag isSuspended is set to true to signify that execution of the manoeuvre
 * should be temporarily suspended("the manoeuvre is held"). Execution
 * resumes when the flag is reset to false. When a manoeuvre is suspended,
 * its continuation action is not performed but this is the only
 * effect of suspension: the other two actions and all three checks remain
 * unaffected. However, when a manoeuvre terminates or aborts, its
 * isSuspended flag is set to false.
 * <p>
 * Certain changes in the execution state of a manoeuvre should be
 * recorded through event reports. This class is responsible for
 * creating event reports in the following cases: <ul>
 * <li>The manoeuvre is suspended or resumed(its isSuspended flag changes
 * value)</li>
 * <li>The manoeuvre starts and terminates execution(its isExecuting
 * flag changes value)</li>
 * <li>The manoeuvre is aborted</li>
 * </ul>
 * Manoeuvres can be <i>disabled</i> and <i>enabled</i>.
 * When a manoeuvre is disabled, its start check is guaranteed to
 * return: "manoeuvre cannot start". This class is responsible
 * for the management of the enable status and for ensuring that
 * this constraint is respected. Note that this means that changes
 * in the enable status of a manoeuvre have no effect upon
 * manoeuvres that are already executiong.
 * @see CC_ManoeuvreFactory
 * @see CC_ManoeuvreManager
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 * @ingroup Manoeuvre
 */
#define TYPE_MANOEUVRE "manoeuvre"

void Manoeuvre_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct Manoeuvre {
    CC_RootObject parent;

    bool executing;
    bool inUse;
    bool enabled;
    bool suspended;
    unsigned int activationStepCounter;
};


struct ManoeuvreClass {
    CC_RootObjectClass parent_class;
 
    void (*internalAbort)(void *obj);
    void (*internalTerminate)(void *obj);
    bool (*internalCanStart)(void *obj);
    bool (*canStart)(void *obj);
    void (*initialize)(void *obj);
    bool (*canContinue)(void *obj);
    TD_CheckCode (*getContinuationCheckCode)(const void *obj);
 
    void (*doInternalContinue)(void *obj);
    bool (*isFinished)(void *obj);
};


#define MANOEUVRE_GET_CLASS(obj) \
        OBJECT_GET_CLASS(ManoeuvreClass, obj, TYPE_MANOEUVRE)

#define MANOEUVRE_CLASS(klass) \
        OBJECT_CLASS_CHECK(ManoeuvreClass, klass, TYPE_MANOEUVRE)

#define MANOEUVRE(obj) \
        OBJECT_CHECK(Manoeuvre, obj, TYPE_MANOEUVRE)


Manoeuvre* Manoeuvre_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Advance the execution of the manoeuvre.
 * Manoeuvres execute over a prolonged period of time.
 * This method is intended to be called to advance the execution of the
 * manoeuvre.
 * The implementation provided by this class is responsible for managing the
 * isExecuting flag, for managing the activation step counter, and for
 * creating an event report when the status of
 * the flag changes from "not executing" to "executing" (this signals the
 * beginning of the execution of the manoeuvre).
 * Execution of the manoeuvre is advanced only if the manoeuvre is not
 * suspended.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *   Manoeuvre_if( !isExecuting ) {
 *     activationStepCounter = 0;
 *     isExecuting=true;
 *     Manoeuvre_createEventRepor t(Manoeuvre *This, EVT_MAN_STARTED);
 *   }
 *   Manoeuvre_if( !Manoeuvre_isSuspended(void) ) {
 *     activationStepCounter++;
 *     Manoeuvre_doInternalContinu e(Manoeuvre *This);
 *   } </PRE>
 * The <CODE>Manoeuvre_doInternalContinue(void)</CODE> method is virtual and encapsulates
 * the implementation of the actions to be performed by the manoeuvre. This
 * method is only called if the manoeuvre is not suspended.
 * The <CODE>isExecuting</CODE> flag is initialized to false by the constructor
 * and is reset to false when the manoeuvre has finished execution or is aborted.
 * Note that the activation
 * step counter is implemented as an unsigned integer and there is no protection
 * against overflow. This puts an upper ceiling on the number of activation
 * steps of a manoeuvre.
 * The <code>manId</code> parameter in the pseudo-code is a manoeuvre identifier.
 * This class uses the <i>class identifier</i> of the manoeuvre component as
 * manoeuvre identifier.
 * <p>
 * This method should only be called on a manoeuvre that is already in use.
 * @see TD_EventType
 * @see CC_ManoeuvreManager#activate
 */
void Manoeuvre_doContinue(Manoeuvre *This);

/**
 * Abort execution of a running manoeuvre.
 * If the manoeuvre is not currently Manoeuvre_executing(if the isExecuting flag is
 * false), no action is taken. Otherwise, its execution status is changed
 * to "not executing", an event reporting the abort operation is created, and
 * the abort operations are executed.
 * The manoeuvre is forced into "not suspended" Manoeuvre_status(its isSuspended flag
 * is set to false).
 * <p>
 * In general, a manoeuvre may be aborted either as a result of an autonomous
 * decision of an external entity or because the manoeuvre itself declares that
 * it is unable to continue Manoeuvre_execution(i.e. its <CODE>canContinue</CODE> method
 * returns false) in which case the manoeuvre must be aborted.
 * After being aborted, a manoeuvre should be de-scheduled and should no
 * longer be considered for execution.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *   isSuspended = false;
 *   Manoeuvre_if( !isExecuting )
 *     return;
 *   else {
 *     isExecuting = false;
 *     Manoeuvre_createEventRepor t(Manoeuvre *This, EVT_MAN_ABORTED);
 *     Manoeuvre_internalAbor t(Manoeuvre *This);
 *   } </PRE>
 * The <CODE>Manoeuvre_internalAbort(void)</CODE> method is intended to be overridden by
 * subclasses to specify concrete actions to be taken by a manoeuvre that is
 * aborted. These would typically be clean-up actions that bring the
 * internal state of the manoeuvre to some pre-defined and consistent state.
 * @see TD_EventType
 * @see #canContinue
 * @see CC_ManoeuvreManager#activate
 * @see CC_ManoeuvreManager#abort
 */
void Manoeuvre_abort(Manoeuvre *This);

/**
 * Perform the termination actions associated to this manoeuvre.
 * This method is intended to be called when a manoeuvre has terminated
 * execution Manoeuvre_nominally(after its <code>isFinished</code> method returns true).
 * It can be used to implement any clean-up actions that is required at the end
 * of a manoeuvre's execution.
 * The manoeuvre is forced into "not suspended" Manoeuvre_status(its isSuspended flag
 * is set to false).
 * The implementation in this class is responsible for resetting the
 * isExecuting and isSuspended flags and for creating an event report recording the termination of
 * the manoeuvre. A pseudo-code implementation for this method is as follows: <PRE>
 *   isSuspended = false;
 *   isExecuting = false;
 *   Manoeuvre_createEventRepor t(Manoeuvre *This, EVT_MAN_TERMINATED);
 *   Manoeuvre_internalTerminat e(Manoeuvre *This); </PRE>
 * The <CODE>Manoeuvre_internalTerminate(void)</CODE> method can be overridden by concrete
 * subclasses to implement their own termination actions.
 * <p>
 * This method should only be called on a manoeuvre that is in use and
 * that is already executing.
 * @see TD_EventType
 * @see #doContinue
 * @see CC_ManoeuvreManager#activate
 */
void Manoeuvre_terminate(Manoeuvre *This);

/**
 * Set the value of the inUse flag.
 * @see TD_EventType
 * @see CC_ManoeuvreManager#load
 * @param newInUse the new value of the inUse flag
 */
void Manoeuvre_setInUse(Manoeuvre *This, bool newInUse);

/**
 * Return the value of the inUse flag.
 * @return the value of the inUse flag
 */
bool Manoeuvre_isInUse(const Manoeuvre *This);

/**
 * Set the value of the isSuspended flag. If the requested value of the
 * flag is different from the current Manoeuvre_value(indicating a change in the
 * state of the manoevre), this is recorded through an even report.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *   Manoeuvre_if( isSuspended and !newIsSuspended )      // manoeuvre is resumed
 *     Manoeuvre_createEventRepor t(Manoeuvre *This, EVT_MAN_RESUMED);
 *   else Manoeuvre_if( !isSuspended and newIsSuspended )
 *     Manoeuvre_createEventRepor t(Manoeuvre *This, EVT_MAN_SUSPENDED);
 *   isSuspended = newIsSuspended; </PRE>
 * @see TD_EventType
 * @see #doContinue
 * @param newIsSuspended the new value of the isSuspended flag
 */
void Manoeuvre_setIsSuspended(Manoeuvre *This, bool newIsSuspended);

/**
 * Return the value of the isSuspended flag.
 * @return the value of the isSuspended flag
 */
bool Manoeuvre_isSuspended(const Manoeuvre *This);

/**
 * Return the value of the isExecuting flag.
 * @return the value of the isExecuting flag.
 */
bool Manoeuvre_isExecuting(const Manoeuvre *This);

/**
 * Set the enable status of the manoeuvre.
 * @param isEnabled if true, then the manoeuvre is enabled; if false, then
 * the manoeuvre is disabled
 */
void Manoeuvre_setEnabled(Manoeuvre *This, bool isEnabled);

/**
 * Check the enable status of the manoeuvre profile.
 * @return true if the manoeuvre is enabled, false otherwise
 */
bool Manoeuvre_isEnabled(const Manoeuvre *This);

/**
 * Return the value of the activation step counter.
 * @see #doContinue
 * @return the current value of the activation step counter
 */
unsigned int Manoeuvre_getActivationStepCounter(const Manoeuvre *This);


#endif
