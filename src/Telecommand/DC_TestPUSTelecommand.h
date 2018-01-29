//
//
// DC_TestPUSTelecommand.h
//


#ifndef DC_TESTPUSTELECOMMAND_H
#define DC_TESTPUSTELECOMMAND_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "PUSTelecommand.h"
#include "../Qom/object.h"


/*
 * Telecommand that can be used as part of an end-to-end PUS test scenario to 
 * simulate a PUS telecommand.
 * This telecommand consists of an <i>execution counter</i> that is incremented 
 * by one every time the telecommand is executed. 
 * The telecommand additionally offers methods to change the return value of its
 * execution check and of its validity check and to set the values of
 * validity and execution check codes. These are useful to 
 * simulate telecommands whose
 * execution check returns "telecommand cannot executed" or whose
 * validity check returns "telecommand not valid". 
 * Similarly, it is possible to set the return value of the execution method to
 * either ACTION_SUCCESS or ACTION_FAILURE.
 * <p>
 * The initial values of the execution counter, of the
 * validity and execution check return values, of the execution return value, 
 * and of the validity and
 * execution check codes are defined in the telecommand application data that
 * are loaded when the telecommand is configured through the <i>raw data load service</i>.
 * <p>
 * The type and subtype of the telecommand are set to PUS_TYPE_TEST and
 * PUS_ST_TC_TEST, respectively.
 * <p>
 * The application data associated to this telecommand are assumed to consist
 * of 6 bytes which are interpreted as follows:<ul>
 * <li>Byte 0: the initial value of the execution counter</li>
 * <li>Byte 1: the initial value of the execution check value</li>
 * <li>Byte 2: the initial value of the validity check value</li>
 * <li>Byte 3: the initial value of the execution check code</li>
 * <li>Byte 4: the initial value of the validity check code</li>
 * <li>Byte 5: the value of the execution outcome return value(ACTION_FAILURE if 1,
 * ACTION_SUCCESS otherwise)</li>
 * </ul>
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_TESTPUSTELECOMMAND "dc_testpustelecommand"

void DC_TestPUSTelecommand_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_TestPUSTelecommand {
    PUSTelecommand parent;

    unsigned char executionCounter; 
    bool executionCheckValue;
    bool validityCheckValue;
    bool executionSuccess;
    TD_CheckCode executionCheckCode;
    TD_CheckCode validityCheckCode;
    unsigned int lasti;
};


struct DC_TestPUSTelecommandClass {
    PUSTelecommandClass parent_class;
};


#define DC_TESTPUSTELECOMMAND_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_TestPUSTelecommandClass, \
                                           obj, TYPE_DC_TESTPUSTELECOMMAND)

#define DC_TESTPUSTELECOMMAND_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_TestPUSTelecommandClass, \
                                         klass, TYPE_DC_TESTPUSTELECOMMAND)

#define DC_TESTPUSTELECOMMAND(obj) \
        OBJECT_CHECK(DC_TestPUSTelecommand, obj, TYPE_DC_TESTPUSTELECOMMAND)


DC_TestPUSTelecommand* DC_TestPUSTelecommand_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Getter method for the execution counter.
 * @return the execution counter
 */
unsigned int DC_TestPUSTelecommand_getExecutionCounter
(
    DC_TestPUSTelecommand *This
);

/**
 * Set the return value of the execution check.
 * This is a setter method for the internal variable <code>executionCheckValue</code>
 * which defines the return value of the execution check implemented by this
 * telecommand.
 * @see #canExecute
 * @param executionCheckValue the value of the internal variable <code>setExecutionCheckValue</code>
 */
void DC_TestPUSTelecommand_setExecutionCheckValue
(
    DC_TestPUSTelecommand *This,
    bool executionCheckValue
);

/**
 * Set the return value of the validity check.
 * This is a setter method for the internal variable <code>validityCheckValue</code>
 * which defines the return value of the validity check implemented by this
 * telecommand.
 * @see #isValid
 * @param validityCheckValue the value of the internal variable <code>setExecutionCheckValue</code>
 */
void DC_TestPUSTelecommand_setValidityCheckValue
(
    DC_TestPUSTelecommand *This, 
    bool validityCheckValue
);

/**
 * Set the value of the validity check code.
 * This is a setter method for an internal variable 
 * which defines the return value of method <code>getValidityCheckCode</code>.
 * @see #getValidityCheckCode
 * @param validityCheckCode the value of the validity check code
 */
void DC_TestPUSTelecommand_setValidityCheckCode
(
    DC_TestPUSTelecommand *This, 
    TD_CheckCode validityCheckCode
);

/**
 * Set the value of the execution check code.
 * This is a setter method for an internal variable 
 * which defines the return value of method <code>getExecutionCheckCode</code>.
 * @see #getExecutionCheckCode
 * @param executionCheckCode the value of the validity check code
 */
void DC_TestPUSTelecommand_setExecutionCheckCode
(
    DC_TestPUSTelecommand *This, 
    TD_CheckCode executionCheckCode
);

/**
 * Set the action outcome returned by method <code>doAction</code>.
 * The possible values are foreseen ACTION_SUCCESS or ACTION_FAILURE.
 * The former is used if the value set with this method is true. Otherwise
 * the latter is used.
 * @see #doAction
 * @param executionSuccess if true, then the action outcome is forced to
 * ACTION_SUCCESS, otherwise  it is forced to ACTION_FAILURE
 */
void DC_TestPUSTelecommand_setActionOutcome
(
    DC_TestPUSTelecommand *This, 
    bool executionSuccess
);

/**
 * Get the action outcome returned by method <code>doAction</code>.
 * If the return value is true, then action outcome is ACTION_SUCCESS.
 * Otherwise it ACTION_FAILURE.
 * @see #setActionOutcome
 * @return a flag indicating which value of action outcome is returned by
 * method <code>doAction</code>
 */
bool DC_TestPUSTelecommand_getActionOutcome
(
    DC_TestPUSTelecommand *This
);


#endif
