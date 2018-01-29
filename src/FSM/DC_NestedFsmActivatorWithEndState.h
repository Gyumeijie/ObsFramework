//
//
// DC_NestedFsmActivatorWithEndState.h
//
//
// Change Record:
//                to be derived from FsmState.


#ifndef DC_NESTEDFSMACTIVATORWITHENDSTATE_H
#define DC_NESTEDFSMACTIVATORWITHENDSTATE_H


#include "DC_NestedFsmActivator.h"
#include "../Qom/object.h"


/*
 * FsmState that activates an FSM. This FsmState is useful to
 * implement "nested FSM" where one outer FSM controls one or more
 * "inner" FSMs. In this case, to each FsmState of the outer FSM,
 * one of the inner FSMs is associated. The task of the FsmStates is
 * to activate their associated FSMs. This class can be used to implement
 * one of these FsmStates.
 * <p>
 * A <code>DC_NestedFsmActivatorWithEndState</code> is configured with two parameters:
 * the <i>target FSM</i> and the <i>target state index</i>. The target
 * FSM is the FSM that the FsmState controls and must periodically
 * activate. The <i>continuation action</i> of an <code>DC_NestedFsmActivatorWithEndState</code>
 * consists in activating the target FSM.
 * <p>
 * The FsmState activates the target FSM until it has reached the
 * target state. At that point, the FsmState terminates. In other
 * words, the <i>termination check</i> of an <code>DC_NestedFsmActivator</code>
 * returns "terminated" when the taregt FSM has reached the target state.
 * <p>
 * The <i>initialization action</i> of the <code>DC_NestedFsmActivatorWithEndState</code>
 * is implemented to reset the target FSM.
 *
 * @see CC_FSM
 * @see DC_NestedFsmActivator
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @author R. Totaro
 * @version 1.1
 */
#define TYPE_DC_NESTEDFSMACTIVATORWITHENDSTATE "dc_nestedfsmactivatorwithendstate"

void DC_NestedFsmActivatorWithEndState_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_NestedFsmActivatorWithEndState {
    DC_NestedFsmActivator parent;

    TD_FsmStateIndex targetState;
};


struct DC_NestedFsmActivatorWithEndStateClass {
    DC_NestedFsmActivatorClass parent_class;
};


#define DC_NESTEDFSMACTIVATORWITHENDSTATE_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_NestedFsmActivatorWithEndStateClass,\
                                   obj, TYPE_DC_NESTEDFSMACTIVATORWITHENDSTATE)

#define DC_NESTEDFSMACTIVATORWITHENDSTATE_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_NestedFsmActivatorWithEndStateClass,\
                                 klass, TYPE_DC_NESTEDFSMACTIVATORWITHENDSTATE)

#define DC_NESTEDFSMACTIVATORWITHENDSTATE(obj) \
        OBJECT_CHECK(DC_NestedFsmActivatorWithEndState,\
                                   obj, TYPE_DC_NESTEDFSMACTIVATORWITHENDSTATE)


DC_NestedFsmActivatorWithEndState* DC_NestedFsmActivatorWithEndState_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the target state index.
 * @see #isFinished
 */
void DC_NestedFsmActivatorWithEndState_setTargetState
(
    DC_NestedFsmActivatorWithEndState *This, 
    TD_FsmStateIndex targetState
);

/**
 * Get the target state index.
 * @see #isFinished
 */
TD_FsmStateIndex DC_NestedFsmActivatorWithEndState_getTargetState
(
    DC_NestedFsmActivatorWithEndState *This
);


#endif
