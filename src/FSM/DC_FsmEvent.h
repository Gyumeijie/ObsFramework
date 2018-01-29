//
//
// DC_FsmEvent.h
//


#ifndef DC_FSMEVENT_H
#define DC_FSMEVENT_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/PunctualAction.h"
#include "../Qom/object.h"


/*
 * Base class from which all FsmEvents are derived.
 * An FsmEvent is a <i>punctual action</i> that, when it is executed, causes
 * an FSM to attempt a state transition.
 * The FSM upon which the FsmEvent acts is called the <i>target FSM</i>.
 * The FSM state to which the transition is commanded is called the <i>target
 * state</i>.
 * Both the target FSM and target state are encapsulated in the FsmEvent
 * object as configuration parameters.
 * This class encapsulate the following FsmEvent execution logic: when the
 * event is executed, a state
 * transition request to the target state is made to the target FSM.
 * Other FsmEvent execution logic would in principle be possible.
 * For instance, the state transition request might be not just to a certain
 * target state but from a given starting state to a given target state.
 * Alternative execution logic can be implemented by subclassing this class
 * and overriding its <CODE>doAction</CODE> method.
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 * @ingroup FSM
 */
#define TYPE_DC_FSMEVENT "dc_fsmevent"

void DC_FsmEvent_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_FsmEvent {
    PunctualAction parent;

    CC_FSM *pTargetFsm;
    TD_FsmStateIndex targetState;
};


struct DC_FsmEventClass {
    PunctualActionClass parent_class;
};


#define DC_FSMEVENT_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_FsmEventClass, obj, TYPE_DC_FSMEVENT)

#define DC_FSMEVENT_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_FsmEventClass, klass, TYPE_DC_FSMEVENT)

#define DC_FSMEVENT(obj) \
        OBJECT_CHECK(DC_FsmEvent, obj, TYPE_DC_FSMEVENT)


DC_FsmEvent* DC_FsmEvent_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Setter method for the target FSM.
 * This is an initialization method.
 * <p>
 * @param pTargetFsm the target FSM
 */
void DC_FsmEvent_setTargetFsm(DC_FsmEvent *This, CC_FSM *pTargetFsm);

/**
 * Setter method for the target state.
 * The target state is specified as an index that must lie in the range
 * [0, N-1] where N is the total number of states in the target FSM.
 * <p>
 * This is an initialization method.
 * <p>
 * @see #isObjectConfigured
 * @param targetState the target state
 */
void DC_FsmEvent_setTargetState(DC_FsmEvent *This, TD_FsmStateIndex targetState);

/**
 * Getter method for the target FSM.
 * <p>
 * @return the target FSM
 */
CC_FSM* DC_FsmEvent_getTargetFsm(const DC_FsmEvent *This);

/**
 * Getter method for the target state.
 * <p>
 * @see #setTargetState
 * @return the target state
 */
TD_FsmStateIndex DC_FsmEvent_getTargetState(const DC_FsmEvent *This);


#endif
