//
//
// RecoveryAction.h
//


#ifndef RECOVERYACTION_H
#define RECOVERYACTION_H


#include "../GeneralInclude/BasicTypes.h"
#include "../Base/ConditionalPunctualAction.h"
#include "../Qom/object.h"


/*
 * Punctual action that performs a <i>recovery action</i>.
 * A recovery action is an action that is executed in response to the
 * detection of a failure. Recovery actions are implemented as a
 * form of <i>punctual action</i>. They add to their base class
 * the <i>next recovery action</i> attribute and the <i>execution
 * check</i>.
 * <p>
 * Recovery actions can be linked in sequential
 * chains. The client only sees one single recovery action(the one
 * at the head of the chain) but its execution can lead to all actions
 * in the chain being executed in sequence. The <i>next recovery action</i>
 * attribute holds the pointer to the next recovery action in the
 * chain.
 * <p>
 * The execution check is performed before executing the recovery
 * action. Its implementation is left open and concrete subclasses
 * can use it to define the conditions under which the execution of
 * the recovery action is allowed.
 * <p>
 * This is an abstract class because it leaves open the definition of
 * actual actions to be performed by the recovery action component
 * and the definition of the execution check open.
 * This class only implements the management of the next recovery
 * action.
 * <p>
 * Punctual actions return an <i>outcome</i>. The outcome of a
 * recovery action R is the outcome of the last recovery action in
 * the chain of recovery actions that has R as its first item.
 * <p>
 * <i>Implementation Note:</i> This could in principle be implemented
 * as a subclass of <code>ConditionalPunctualAction</code>. This is
 * not done because class a failure of the execution check in
 * class <code>ConditionalPunctualAction</code> simply leads
 * to an immediate termination of the punctual action. In the case
 * of the <code>RecoveryAction</code> class, instead, a failure
 * of the execution check leads to an attempt to execute the next
 * recovery action.
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 * @ingroup FDIR
 */
#define TYPE_RECOVERYACTION "recoveryaction"

void RecoveryAction_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct RecoveryAction {
    PunctualAction parent;

    RecoveryAction *pNextRecoveryAction;
};


struct RecoveryActionClass {
    PunctualActionClass parent_class;
 
    bool (*canExecute)(void *obj);

    TD_ActionOutcome (*doRecoveryAction)(void *obj);
};


#define RECOVERYACTION_GET_CLASS(obj) \
        OBJECT_GET_CLASS(RecoveryActionClass, obj, TYPE_RECOVERYACTION)

#define RECOVERYACTION_CLASS(klass) \
        OBJECT_CLASS_CHECK(RecoveryActionClass, klass, TYPE_RECOVERYACTION)

#define RECOVERYACTION(obj) \
        OBJECT_CHECK(RecoveryAction, obj, TYPE_RECOVERYACTION)


RecoveryAction* RecoveryAction_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the next recovery action.
 * @see #doAction
 * @param pNextRecoveryAction the next recovery action
 */
void RecoveryAction_setNextRecoveryAction
(
    RecoveryAction *This, 
    RecoveryAction *pNextRecoveryAction
);

/**
 * Get the next recovery action. If no recovery action has been chained
 * to this one, then a value of pNULL is returned.
 * @see #doAction
 * @return the next recovery action
 */
RecoveryAction* RecoveryAction_getNextRecoveryAction(RecoveryAction *This);


#endif
