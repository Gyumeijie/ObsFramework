//
//
// DC_DummyConfigurableFsmState.h
//
//
// Change Record:


#ifndef DC_DUMMYCONFIGURABLEFSMSTATE_H
#define DC_DUMMYCONFIGURABLEFSMSTATE_H


#include "FsmState.h"
#include "../Qom/object.h"


/*
 * Dummy configurable FsmState useful for testing purposes. It represents an
 * FsmState with simple actions and configurable check results.
 * The actions
 * associated to the FsmState consist in the incrementation of three counters:
 * the <i>activation counter</i>, <i>initialization counter</i> and the
 * <i>termination counter</i>.
 * The checks associated to the FsmState are implemented
 * to return user-defined values.
 * @see CC_FSM
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.1
 */
#define TYPE_DC_DUMMYCONFIGURABLEFSMSTATE "dc_dummyconfigurablefsmstate"

void DC_DummyConfigurableFsmState_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_DummyConfigurableFsmState {
    FsmState parent;

    unsigned int activationCounter;
    unsigned int initializationCounter;
    unsigned int exitCounter;
    bool initializationCheck;
    bool exitCheck;
    bool terminationCheck;
};


struct DC_DummyConfigurableFsmStateClass {
    FsmStateClass parent_class;
};


#define DC_DUMMYCONFIGURABLEFSMSTATE_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_DummyConfigurableFsmStateClass,\
                                         obj, TYPE_DC_DUMMYCONFIGURABLEFSMSTATE)

#define DC_DUMMYCONFIGURABLEFSMSTATE_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_DummyConfigurableFsmStateClass,\
                                       klass, TYPE_DC_DUMMYCONFIGURABLEFSMSTATE)

#define DC_DUMMYCONFIGURABLEFSMSTATE(obj) \
        OBJECT_CHECK(DC_DummyConfigurableFsmState,\
                                         obj, TYPE_DC_DUMMYCONFIGURABLEFSMSTATE)


DC_DummyConfigurableFsmState* DC_DummyConfigurableFsmState_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Return the value of the activation counter.
 * @return the value of the activation counter
 */
unsigned int DC_DummyConfigurableFsmState_getActivationCounter
(
    DC_DummyConfigurableFsmState *This
);

/**
 * Return the value of the initialization counter.
 * @return the value of the initialization counter
 */
unsigned int DC_DummyConfigurableFsmState_getInitializationCounter
(
    DC_DummyConfigurableFsmState *This
);

/**
 * Return the value of the exit counter.
 * @return the value of the exit counter
 */
unsigned int DC_DummyConfigurableFsmState_getExitCounter
(
    DC_DummyConfigurableFsmState *This
);

/**
 * Set the return value of the initialization check.
 * @return the value that shall be returned by the next call to the
 * initialization check
 */
void DC_DummyConfigurableFsmState_setInitializationCheckValue
(
    DC_DummyConfigurableFsmState *This,
    bool value
);

/**
 * Set the return value of the exit check.
 * @return the value that shall be returned by the next call to the
 * exit check
 */
void DC_DummyConfigurableFsmState_setExitCheckValue
(
    DC_DummyConfigurableFsmState *This,
    bool value
);

/**
 * Set the return value of the termination check.
 * @return the value that shall be returned by the next call to the
 * termination check
 */
void DC_DummyConfigurableFsmState_setTerminationCheckValue
(
    DC_DummyConfigurableFsmState *This,
    bool value
);


#endif
