//
//
// DC_DummyConfigurableManoeuvre.h
//


#ifndef DC_DUMMYCONFIGURABLEMANOEUVRE_H
#define DC_DUMMYCONFIGURABLEMANOEUVRE_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "Manoeuvre.h"
#include "../Qom/object.h"


/*
 * Dummy implementation of the <code>Manoeuvre</code> abstract class
 * to be used for testing purposes. This class implements some simple
 * forms of manoeuvre actions and it allows the return values of the
 * manoeuvre checks to be configured by the user.
 * <p>
 * This class associates three counters to each of the three actions
 * (<i>initialization action</i>, <i>continuation action</i>, and
 * <i>termination action</i>) that characterize a manoeuvre.
 * The counters are initialized to zero
 * by the constructor and are incremented by one every time the
 * action is executed.
 * The return value of the three checks(<i>start check</i>,
 * <i>continuation check</i>, and <i>termination check</i>) associated
 * to the manoeuvres can be set be the user. The value of the continuation
 * check code can also be set by the user.
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_DUMMYCONFIGURABLEMANOEUVRE "dc_dummyconfigurablemanoeuvre"

void DC_DummyConfigurableManoeuvre_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_DummyConfigurableManoeuvre {
    Manoeuvre parent;

    int initializationActionCounter;
    int continuationActionCounter;
    int terminationActionCounter;
    bool startCheck;
    bool continuationCheck;
    bool terminationCheck;
    TD_CheckCode continuationCheckCode;
};


struct DC_DummyConfigurableManoeuvreClass {
    ManoeuvreClass parent_class;
};


#define DC_DUMMYCONFIGURABLEMANOEUVRE_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_DummyConfigurableManoeuvreClass, \
                                       obj, TYPE_DC_DUMMYCONFIGURABLEMANOEUVRE)

#define DC_DUMMYCONFIGURABLEMANOEUVRE_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_DummyConfigurableManoeuvreClass, \
                                     klass, TYPE_DC_DUMMYCONFIGURABLEMANOEUVRE)

#define DC_DUMMYCONFIGURABLEMANOEUVRE(obj) \
        OBJECT_CHECK(DC_DummyConfigurableManoeuvre, \
                                       obj, TYPE_DC_DUMMYCONFIGURABLEMANOEUVRE)


DC_DummyConfigurableManoeuvre* DC_DummyConfigurableManoeuvre_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the value of the start check.
 * The value set with this method is the value returned by the start check method.
 * @see #canStart
 * @param startCheck the return value of the start check
 */
void DC_DummyConfigurableManoeuvre_setStartCheckStatus
(
    DC_DummyConfigurableManoeuvre *This, 
    bool startCheck
);

/**
 * Set the value of the continuation check.
 * The value set with this method is the value returned by the continuation check method.
 * @see #canContinue
 * @param continuationCheck the return value of the continuation check
 */
void DC_DummyConfigurableManoeuvre_setContinuationCheckStatus
(
    DC_DummyConfigurableManoeuvre *This, 
    bool continuationCheck
);

/**
 * Set the value of the continuation check code.
 * The value set with this method is the value returned by method
 * <code>getContinuationCheckCode</code>.
 * @see #canContinue
 * @param continuationCheckCode the return value of the continuation check
 */
void DC_DummyConfigurableManoeuvre_setContinuationCheckCode
(
    DC_DummyConfigurableManoeuvre *This, 
    TD_CheckCode continuationCheckCode
);

/**
 * Set the value of the termination check.
 * The value set with this method is the value returned by the termination check methods.
 * @see #isFinished
 * @param terminationCheck the return value of the termination check
 */
void DC_DummyConfigurableManoeuvre_setTerminationCheckStatus
(
    DC_DummyConfigurableManoeuvre *This, 
    bool terminationCheck
);

/**
 * Getter method for the initialization action counter.
 * @see #initialize
 * @return the initialization action counter
 */
int DC_DummyConfigurableManoeuvre_getInitializationActionCounter
(
    DC_DummyConfigurableManoeuvre *This
);

/**
 * Getter method for the continuation action counter.
 * @see #doInternalContinue
 * @return the continuation action counter
 */
int DC_DummyConfigurableManoeuvre_getContinuationActionCounter
(
    DC_DummyConfigurableManoeuvre *This
);

/**
 * Getter method for the termination action counter.
 * @see #internalTerminate
 * @return the termination action counter
 */
int DC_DummyConfigurableManoeuvre_getTerminationActionCounter
(
    DC_DummyConfigurableManoeuvre *This
);


#endif
