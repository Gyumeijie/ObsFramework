//
//
// DC_DummyRecoveryAction.h
//


#ifndef DC_DUMMYRECOVERYACTION_H
#define DC_DUMMYRECOVERYACTION_H


#include "../GeneralInclude/BasicTypes.h"
#include "RecoveryAction.h"
#include "../Qom/object.h"


/*
 * Recovery action that performs no action and returns a configurable
 * outcome(see <code>setActionOutcome(void)</code>). This recovery action is
 * used only for testing purposes.
 * @author Roberto Totaro
 * @version 1.0
 */
#define TYPE_DC_DUMMYRECOVERYACTION "dc_dummyrecoveryaction"

void DC_DummyRecoveryAction_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_DummyRecoveryAction {
    RecoveryAction parent;

    bool actionCanExecute;
    TD_ActionOutcome actionOutcome;
};


struct DC_DummyRecoveryActionClass {
    RecoveryActionClass parent_class;
 
    TD_ActionOutcome (*doRecoveryAction)(void *obj);
    bool (*canExecute)(void *obj);
};


#define DC_DUMMYRECOVERYACTION_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_DummyRecoveryActionClass,\
                                              obj, TYPE_DC_DUMMYRECOVERYACTION)

#define DC_DUMMYRECOVERYACTION_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_DummyRecoveryActionClass,\
                                            klass, TYPE_DC_DUMMYRECOVERYACTION)

#define DC_DUMMYRECOVERYACTION(obj) \
        OBJECT_CHECK(DC_DummyRecoveryAction, obj, TYPE_DC_DUMMYRECOVERYACTION)


DC_DummyRecoveryAction* DC_DummyRecoveryAction_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the action's outcome.
 * @see #doRecoveryAction
 * @param nextOutcome the outcome of the action
 */
void DC_DummyRecoveryAction_setActionOutcome
(
    DC_DummyRecoveryAction *This,
    TD_ActionOutcome nextOutcome
);

/**
 * Set the status of the execution flag.
 * @see #canExecute
 * @param canExecute the value returned by <code>DC_DummyRecoveryAction_canExecute(void)</code>
 */
void DC_DummyRecoveryAction_setExecutionFlag
(
    DC_DummyRecoveryAction *This, 
    bool canExecute
);


#endif
