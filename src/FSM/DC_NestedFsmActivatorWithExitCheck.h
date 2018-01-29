//
//
// DC_NestedFsmActivatorWithExitCheck.h
//
//
// Change Record:


#ifndef DC_NESTEDFSMACTIVATORWITHEXITCHECK_H
#define DC_NESTEDFSMACTIVATORWITHEXITCHECK_H


#include "DC_NestedFsmActivator.h"
#include "../Qom/object.h"


/*
 * FsmState that activates an FSM. This FsmState is useful to
 * implement "nested FSM" where one outer FSM controls one or more
 * "inner" FSMs. In this case, to each FsmState of the outer FSM,
 * one of the inner FSMs is associated. The task of the FsmStates is
 * activate their associated FSMs. This class can be used to implement
 * one of these FsmStates.
 * <p>
 * A <code>DC_NestedFsmActivatorWithExitCheck</code> is configured with two parameters:
 * the <i>target FSM</i> and the <i>target state index</i>. The target
 * FSM is the FSM that the FsmState controls and must periodically
 * activate. The <i>continuation action</i> of an <code>DC_NestedFsmActivatorWithExitCheck</code>
 * consists in activating the target FSM.
 * The FsmState thus implemented by an
 * <code>DC_NestedFsmActivatorWithExitCheck</code> is a stable state that,
 * barring any external action, never terminates.
 * <p>
 * This state performs an <i>exit check</i> that consists in verifying whether
 * the target FSM has reached the <i>target state</i> passed as to the
 * state as a configuration parameter.
 * <p>
 * The <i>initialization action</i> of the <code>DC_NestedFsmActivatorWithEndState</code>
 * is implemented to reset the target FSM.
 * @see CC_FSM
 * @see DC_NestedFsmActivator
 * @author Alessandro Pasetti
 * @author R. Totaro
 * @version 1.0
 */
#define TYPE_DC_NESTEDFSMACTIVATORWITHEXITCHECK "dc_nestedfsmactivatorwithexitcheck"

void DC_NestedFsmActivatorWithExitCheck_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_NestedFsmActivatorWithExitCheck {
    DC_NestedFsmActivator parent;

    TD_FsmStateIndex targetState;
};


struct DC_NestedFsmActivatorWithExitCheckClass {
    DC_NestedFsmActivatorClass parent_class;
};


#define DC_NESTEDFSMACTIVATORWITHEXITCHECK_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_NestedFsmActivatorWithExitCheckClass,\
                                  obj, TYPE_DC_NESTEDFSMACTIVATORWITHEXITCHECK)

#define DC_NESTEDFSMACTIVATORWITHEXITCHECK_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_NestedFsmActivatorWithExitCheckClass,\
                                klass, TYPE_DC_NESTEDFSMACTIVATORWITHEXITCHECK)

#define DC_NESTEDFSMACTIVATORWITHEXITCHECK(obj) \
        OBJECT_CHECK(DC_NestedFsmActivatorWithExitCheck,\
                                  obj, TYPE_DC_NESTEDFSMACTIVATORWITHEXITCHECK)


DC_NestedFsmActivatorWithExitCheck* DC_NestedFsmActivatorWithExitCheck_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the target state index.
 * @see #canExit
 */
void DC_NestedFsmActivatorWithExitCheck_setTargetState
(
    DC_NestedFsmActivatorWithExitCheck *This, 
    TD_FsmStateIndex targetState
);

/**
 * Get the target state index.
 * @see #canExit
 */
TD_FsmStateIndex DC_NestedFsmActivatorWithExitCheck_getTargetState
(
    DC_NestedFsmActivatorWithExitCheck *This
);


#endif
