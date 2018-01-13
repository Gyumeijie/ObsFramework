//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyFsmState.h
//
// Version	1.1
// Date		02.10.02 (Version 1.0)
//          25.02.03 (Version 1.1)
// Author	A. Pasetti(P&P Software)
//
// Change Record:
//   Version 1.1: fixed errors in CcDoc references


#ifndef DC_DUMMYFSMSTATE_H
#define DC_DUMMYFSMSTATE_H


#include "FsmState.h"
#include "../Qom/object.h"


/*
 * Dummy FsmState useful for testing purposes and to represent FsmStates to
 * which no actions and no checks are associated. The actions
 * associated to the FsmState are implemented as dummy actions that return
 * without doing anything. The checks associated to the FsmState are implemented
 * to always return: "state can be entered", "state can be exited", and
 * "continued action has not yet terminated". This means that this state
 * is a stable state that will not be exited unless a state change is
 * commanded to the FSM.
 * @see CC_FSM
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.1
 */
#define TYPE_DC_DUMMYFSMSTATE "dc_dummyfsmstate"

void DC_DummyFsmState_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_DummyFsmState {
    FsmState parent;
};


struct DC_DummyFsmStateClass {
    FsmStateClass parent_class;
};


#define DC_DUMMYFSMSTATE_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_DummyFsmStateClass, obj, TYPE_DC_DUMMYFSMSTATE)

#define DC_DUMMYFSMSTATE_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_DummyFsmStateClass, klass, TYPE_DC_DUMMYFSMSTATE)

#define DC_DUMMYFSMSTATE(obj) \
        OBJECT_CHECK(DC_DummyFsmState, obj, TYPE_DC_DUMMYFSMSTATE)


DC_DummyFsmState* DC_DummyFsmState_new(void);

#endif
