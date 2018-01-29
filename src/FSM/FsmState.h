//
//
// FsmState.h
//
//
//
// Change Record:


#ifndef FSMSTATE_H
#define FSMSTATE_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "../Qom/object.h"


/*
 * Base class from which all FsmState classes are derived.
 * An FsmState class encapsulates a state of an finite state machine(FSM).
 * <p>
 * This is an abstract class that declares abstract methods to implement: the
 * actions associated to the
 * FsmState and the checks associated to the FsmState.
 * Concrete methods are also defined to implement configuration operations.
 * <p>
 * An FsmState can execute three types of actions.
 * An <i>initialization action</i> that is a punctual action performed
 * immediately after the state is entered.
 * A <i>continuation action</i> that is an action performed every time the
 * state is activated.
 * A <i>termination action</i> that is a punctual action that is performed
 * immediately before the state is exited.
 * This class provides default implementation for the initialization and
 * termination actions that do not do anything.
 * <p>
 * An FsmState performs three types of checks.
 * An <i>initialization check</i> that checks whether the state can be
 * entered.
 * A <i>exit check</i> that checks whether the state can be exited.
 * A <i>termination check</i> that checks whether the state has terminated
 * execution and is ready to perform
 * an autonomous state transition.
 * This class provides default implementations for the initialization and
 * exit checks that always return true(check is passed).
 * <p>
 * An FsmState holds a reference to a <i>next state</i>.
 * This represents the state to which the current state wants to perform an
 * autonomous transition after it
 * has performed all its actions.
 * FsmStates however are "passive" objects and state transitions are under
 * the control of the FSM.
 * This class provides a default implementation that returns a null pointer
 * for the next state signifying that
 * there is no next state.
 * @see CC_FSM
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 * @ingroup FSM
 */
#define TYPE_FSMSTATE "fsmstate"

void FsmState_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct FsmState {
    CC_RootObject parent;

    FsmState *pNextState;
};


struct FsmStateClass {
    CC_RootObjectClass parent_class;
 
    bool (*canEnter)(void *obj);
    void (*doInit)(void *obj);
    bool (*canExit)(void *obj);
    void (*doExit)(void *obj);
    bool (*isFinished)(void *obj);
 
    void (*doContinue)(void *obj);
};


#define FSMSTATE_GET_CLASS(obj) \
        OBJECT_GET_CLASS(FsmStateClass, obj, TYPE_FSMSTATE)

#define FSMSTATE_CLASS(klass) \
        OBJECT_CLASS_CHECK(FsmStateClass, klass, TYPE_FSMSTATE)

#define FSMSTATE(obj) \
        OBJECT_CHECK(FsmState, obj, TYPE_FSMSTATE)


FsmState* FsmState_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the next state associated to this state.
 * This method would normally be called only once during the application
 * initialization phase.
 * However, it is not formally classified as an <i>initialization
 * method</i> in order to leave the option
 * open to FsmState objects to dynamically set their next state on the
 * basis of their termination status.
 * @param pNextState the next state associated to the current state
 */
void FsmState_setNextState(FsmState *This, FsmState *pNextState);

/**
 * Return the next state associated to this state.
 * If no next state is associated to this state, then the method return
 * pNULL.
 * @return the next state associated to the current state
 */
FsmState* FsmState_getNextState(const FsmState *This);


#endif
