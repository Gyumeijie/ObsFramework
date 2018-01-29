//
//
// DC_FdirCheck.h
//


#ifndef DC_FDIRCHECK_H
#define DC_FDIRCHECK_H


#include "../GeneralInclude/BasicTypes.h"
#include "../Base/PunctualAction.h"
#include "../FDIR/RecoveryAction.h"
#include "../Qom/object.h"


/*
 * Encapsulation of a failure detection and isolation check and of its
 * associated recovery action. A FDIR(fault detection, isolation
 * and recovery) check usually consists of two parts. A check that
 * determines the existence of a fault and isolates its cause(the
 * <i>failure detection and isolation check</i> or FDI check), and a
 * a <i>recovery action</i> to counteract the fault. This component
 * encapsulates a complete FDIR check and allows both the
 * FDI check and the recovery action to be executed
 * as a single action.
 * <p>
 * This component assumes that the FDI check check is encapsulated
 * in a component of type <code>PunctualAction</code>.
 * and that the recovery action is encapsulated in a component of type
 * <code>RecoveryAction</code>.
 * <p>
 * This component is offered as a form of <i>punctual action</i> (it
 * is derived from the base class <code>PunctualAction</code>). Its
 * associated action consists in the execution of the FDI check
 * and, if this returns with a failure code, in
 * the subsequent and immediate execution of the associated recovery
 * action. Note that there is no conditional execution check associated to an
 * FDIR check: the FDI check is always executed when the <code>FdirCheck</code>
 * component is executed. If it is desired to have the FDIR check executed only
 * if certain conditions hold, the conditional execution check can be built
 * into the FDI check(this is typically done by implementing the FDI check
 * as a subclass of <code>ConditionalPunctualAction</code>).
 * @todo change the name of this class to: DC_FdirAction(remember to update
 * the comments to reflect the change of class name)
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 * @ingroup FDIR
 */
#define TYPE_DC_FDIRCHECK "dc_fdircheck"

void DC_FdirCheck_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_FdirCheck {
    PunctualAction parent;

    RecoveryAction *pRecoveryAction;
    PunctualAction *pFdiCheck;
};


struct DC_FdirCheckClass {
    PunctualActionClass parent_class;
};


#define DC_FDIRCHECK_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_FdirCheckClass, obj, TYPE_DC_FDIRCHECK)

#define DC_FDIRCHECK_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_FdirCheckClass, klass, TYPE_DC_FDIRCHECK)

#define DC_FDIRCHECK(obj) \
        OBJECT_CHECK(DC_FdirCheck, obj, TYPE_DC_FDIRCHECK)


DC_FdirCheck* DC_FdirCheck_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the FDI check.
 * @see #doAction
 * @param pFdiCheck the FDI check component
 */
void DC_FdirCheck_setFdiCheck(DC_FdirCheck *This, PunctualAction *pFdiCheck);

/**
 * Get the FDI check.
 * @see #doAction
 * @return the FDI check component
 */
PunctualAction* DC_FdirCheck_getFdiCheck(DC_FdirCheck *This);

/**
 * Set the recovery action.
 * @see #doAction
 * @param pRecoveryAction the recovery action
 */
void DC_FdirCheck_setRecoveryAction
(
    DC_FdirCheck *This, 
    RecoveryAction *pRecoveryAction
);

/**
 * Get the recovery action.
 * @see #doAction
 * @return the recovery action
 */
RecoveryAction* DC_FdirCheck_getRecoveryAction(DC_FdirCheck *This);


#endif
