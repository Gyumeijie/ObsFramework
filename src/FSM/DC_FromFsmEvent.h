//
//
// DC_FromFsmEvent.h
//


#ifndef DC_FROMFSMEVENT_H
#define DC_FROMFSMEVENT_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/PunctualAction.h"
#include "DC_FsmEvent.h"
#include "../Qom/object.h"


/*
 * Default component encapsulating an FsmEvent that requests a transition in
 * the target FSM between two states.
 * The two states across which the transition is attempted are the
 * <i>starting state</i> and the <i>target state</i>.
 * Both are configuration parameters for the FsmEvent.
 * When the FsmEvent is fired, it checks whether the target FSM is in the
 * starting state and, if it is, it
 * makes a request for a transition to the target state.
 * If the target FSM is not in the starting state, no action is taken.
 * <p>
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_FROMFSMEVENT "dc_fromfsmevent"

void DC_FromFsmEvent_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_FromFsmEvent {
    DC_FsmEvent parent;

    TD_FsmStateIndex startingState;
};


struct DC_FromFsmEventClass {
    DC_FsmEventClass parent_class;
};


#define DC_FROMFSMEVENT_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_FromFsmEventClass, obj, TYPE_DC_FROMFSMEVENT)

#define DC_FROMFSMEVENT_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_FromFsmEventClass, klass, TYPE_DC_FROMFSMEVENT)

#define DC_FROMFSMEVENT(obj) \
        OBJECT_CHECK(DC_FromFsmEvent, obj, TYPE_DC_FROMFSMEVENT)


DC_FromFsmEvent* DC_FromFsmEvent_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Setter method for the starting state.
 * The starting state is expressed as an integer that should be in the
 * range [0, N-1] where N is the total number of states in the target FSM.
 * This is an initialization method.
 * <p>
 * @param startingState the starting state
 */
void DC_FromFsmEvent_setStartingState
(
    DC_FromFsmEvent *This, 
    TD_FsmStateIndex startingState
);

/**
 * Getter method for the starting state.
 * <p>
 * @return the starting state
 */
TD_FsmStateIndex DC_FromFsmEvent_getStartingState(const DC_FromFsmEvent *This);


#endif
