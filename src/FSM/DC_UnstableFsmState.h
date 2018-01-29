//
//
// DC_UnstableFsmState.h
//
//
// Change Record:


#ifndef DC_UNSTABLEFSMSTATE_H
#define DC_UNSTABLEFSMSTATE_H


#include "FsmState.h"
#include "../Qom/object.h"


/*
 * FsmState that takes no action and exits immediately. This state is
 * useful as a placeholder state. The actions
 * associated to the FsmState are implemented as dummy actions that return
 * without doing anything. The checks associated to the FsmState are implemented
 * to always return: "state can be entered", "state can be exited", and
 * "continued action has terminated". This means that this state
 * is an unstable state that will be immediately exited.
 * @see CC_FSM
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.1
 */
#define TYPE_DC_UNSTABLEFSMSTATE "dc_unstablefsmstate"

void DC_UnstableFsmState_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_UnstableFsmState {
    FsmState parent;
};


struct DC_UnstableFsmStateClass {
    FsmStateClass parent_class;
};


#define DC_UNSTABLEFSMSTATE_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_UnstableFsmStateClass, obj, TYPE_DC_UNSTABLEFSMSTATE)

#define DC_UNSTABLEFSMSTATE_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_UnstableFsmStateClass, klass, TYPE_DC_UNSTABLEFSMSTATE)

#define DC_UNSTABLEFSMSTATE(obj) \
        OBJECT_CHECK(DC_UnstableFsmState, obj, TYPE_DC_UNSTABLEFSMSTATE)


DC_UnstableFsmState* DC_UnstableFsmState_new(void);

#endif
