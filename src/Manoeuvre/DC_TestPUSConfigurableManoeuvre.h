//
//
// DC_TestPUSConfigurableManoeuvre.h
//


#ifndef DC_TESTPUSCONFIGURABLEMANOEUVRE_H
#define DC_TESTPUSCONFIGURABLEMANOEUVRE_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "PUSTcManoeuvre.h"
#include "../Qom/object.h"


/*
 * Test implementation of the <code>PUSManoeuvre</code> abstract class
 * to be used for testing purposes. This class implements some simple
 * forms of manoeuvre actions and it allows the return values of the
 * manoeuvre checks to be configured by the user.
 * <p>
 * This class associates three counters to each of the three actions
 * (<i>initialization action</i>, <i>continuation action</i>, and
 * <i>termination action</i>) that characterize a manoeuvre.
 * The counters are initialized to zero
 * by the constructor and are incremented by one every time the
 * action is executed. Execution of the continuation action also causes
 * the <i>progress event generation service</i> to be called.
 * The return value of the three checks(<i>start check</i>,
 * <i>continuation check</i>, and <i>termination check</i>) associated
 * to the manoeuvres can be set be the user. The value of the continuation
 * check code can also be set by the user.
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_TESTPUSCONFIGURABLEMANOEUVRE "dc_testpusconfigurablemanoeuvre"

void DC_TestPUSConfigurableManoeuvre_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_TestPUSConfigurableManoeuvre {
    PUSTcManoeuvre parent;

    int initializationActionCounter;
    int continuationActionCounter;
    int terminationActionCounter;
    bool startCheck;
    bool continuationCheck;
    bool terminationCheck;
    TD_CheckCode continuationCheckCode;
};


struct DC_TestPUSConfigurableManoeuvreClass {
    PUSTcManoeuvreClass parent_class;
};


#define DC_TESTPUSCONFIGURABLEMANOEUVRE_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_TestPUSConfigurableManoeuvreClass, \
                                     obj, TYPE_DC_TESTPUSCONFIGURABLEMANOEUVRE)

#define DC_TESTPUSCONFIGURABLEMANOEUVRE_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_TestPUSConfigurableManoeuvreClass, \
                                   klass, TYPE_DC_TESTPUSCONFIGURABLEMANOEUVRE)

#define DC_TESTPUSCONFIGURABLEMANOEUVRE(obj) \
        OBJECT_CHECK(DC_TestPUSConfigurableManoeuvre, \
                                     obj, TYPE_DC_TESTPUSCONFIGURABLEMANOEUVRE)


DC_TestPUSConfigurableManoeuvre* DC_TestPUSConfigurableManoeuvre_new(void);


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
void DC_TestPUSConfigurableManoeuvre_setStartCheckStatus
(
    DC_TestPUSConfigurableManoeuvre *This, 
    bool startCheck
);

/**
 * Set the value of the continuation check.
 * The value set with this method is the value returned by the continuation check method.
 * @see #canContinue
 * @param continuationCheck the return value of the continuation check
 */
void DC_TestPUSConfigurableManoeuvre_setContinuationCheckStatus
(
    DC_TestPUSConfigurableManoeuvre *This, 
    bool continuationCheck
);

/**
 * Set the value of the continuation check code.
 * The value set with this method is the value returned by method
 * <code>getContinuationCheckCode</code>.
 * @see #canContinue
 * @param continuationCheckCode the return value of the continuation check
 */
void DC_TestPUSConfigurableManoeuvre_setContinuationCheckCode
(
    DC_TestPUSConfigurableManoeuvre *This, 
    TD_CheckCode continuationCheckCode
);

/**
 * Set the value of the termination check.
 * The value set with this method is the value returned by the termination check methods.
 * @see #isFinished
 * @param terminationCheck the return value of the termination check
 */
void DC_TestPUSConfigurableManoeuvre_setTerminationCheckStatus
(
    DC_TestPUSConfigurableManoeuvre *This,
    bool terminationCheck
);

/**
 * Getter method for the initialization action counter.
 * @see #initialize
 * @return the initialization action counter
 */
int DC_TestPUSConfigurableManoeuvre_getInitializationActionCounter
(
    DC_TestPUSConfigurableManoeuvre *This
);

/**
 * Getter method for the continuation action counter.
 * @see #doInternalContinue
 * @return the continuation action counter
 */
int DC_TestPUSConfigurableManoeuvre_getContinuationActionCounter
(
    DC_TestPUSConfigurableManoeuvre *This
);

/**
 * Getter method for the termination action counter.
 * @see #internalTerminate
 * @return the termination action counter
 */
int DC_TestPUSConfigurableManoeuvre_getTerminationActionCounter
(
    DC_TestPUSConfigurableManoeuvre *This
);


#endif
