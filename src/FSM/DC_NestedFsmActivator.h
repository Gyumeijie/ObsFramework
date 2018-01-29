//
//
// DC_NestedFsmActivator.h
//
//
// Change Record:


#ifndef DC_NESTEDFSMACTIVATOR_H
#define DC_NESTEDFSMACTIVATOR_H


#include "FsmState.h"
#include "CC_FSM.h"
#include "../Qom/object.h"


/*
 * FsmState that activates an FSM. This FsmState is useful to
 * implement "nested FSM" where one outer FSM controls one or more
 * "inner" FSMs. In this case, to each FsmState of the outer FSM,
 * one of the inner FSMs is associated. The task of the FsmStates is
 * activate their associated FSMs. This class can be used to implement
 * one of these FsmStates.
 * <p>
 * A <code>DC_NestedFsmActivator</code> is configured with one parameter:
 * the <i>target FSM</i>. The target FSM is the FSM that the FsmState controls
 * and must periodically activate. The <i>continuation action</i> of an
 * <code>DC_NestedFsmActivator</code> consists in activating the target FSM.
 * <p>
 * The <i>initialization action</i> of the <code>DC_NestedFsmActivator</code>
 * is implemented to reset the target FSM.
 * <p>
 * All other actions and checks associated to the <code>DC_NestedFsmActivator</code>
 * have their default implementations as defined in the base class <code>FsmState</code>.
 * @see CC_FSM
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_NESTEDFSMACTIVATOR "dc_nestedfsmactivator"

void DC_NestedFsmActivator_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_NestedFsmActivator {
    FsmState parent;

    CC_FSM *pTargetFsm;
};


struct DC_NestedFsmActivatorClass {
    FsmStateClass parent_class;
};


#define DC_NESTEDFSMACTIVATOR_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_NestedFsmActivatorClass,\
                                            obj, TYPE_DC_NESTEDFSMACTIVATOR)

#define DC_NESTEDFSMACTIVATOR_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_NestedFsmActivatorClass,\
                                          klass, TYPE_DC_NESTEDFSMACTIVATOR)

#define DC_NESTEDFSMACTIVATOR(obj) \
        OBJECT_CHECK(DC_NestedFsmActivator, obj, TYPE_DC_NESTEDFSMACTIVATOR)


DC_NestedFsmActivator* DC_NestedFsmActivator_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the target FSM.
 * @see #doContinue
 */
void DC_NestedFsmActivator_setTargetFsm
(
    DC_NestedFsmActivator *This,
    CC_FSM *pTargetFsm
);

/**
 * Get the target FSM.
 * @see #doContinue
 */
CC_FSM* DC_NestedFsmActivator_getTargetFsm(DC_NestedFsmActivator *This);


#endif
