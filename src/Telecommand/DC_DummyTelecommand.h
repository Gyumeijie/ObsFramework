//
//
// DC_DummyTelecommand.h
//


#ifndef DC_DUMMYTELECOMMAND_H
#define DC_DUMMYTELECOMMAND_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "Telecommand.h"
#include "../Qom/object.h"


/*
 * Dummy telecommand that increments a counter every time it is 
 * executed. This telecommand is useful for testing purposes.
 * The telecommand maintains an <i>execution counter</i> that is initialized 
 * to zero when the telecommand object is first instantiated and is 
 * incremented by one every time the telecommand receives an <code>execute</code>
 * request. There is no way to reset the execution counter.
 * <p>
 * The telecommand offer methods to change the return value of its
 * execution check and of its validity check and to set the values of
 * validity and execution check codes. These are useful to 
 * simulate telecommands whose
 * execution check returns "telecommand cannot executed" or whose
 * validity check returns "telecommand not valid".
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_DUMMYTELECOMMAND "dc_dummytelecommand"

void DC_DummyTelecommand_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_DummyTelecommand {
    Telecommand parent;

    unsigned int executionCounter; 
    bool executionCheckValue;
    bool validityCheckValue;
    TD_CheckCode executionCheckCode;
    TD_CheckCode validityCheckCode;
};


struct DC_DummyTelecommandClass {
    TelecommandClass parent_class;
};


#define DC_DUMMYTELECOMMAND_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_DummyTelecommandClass, obj, TYPE_DC_DUMMYTELECOMMAND)

#define DC_DUMMYTELECOMMAND_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_DummyTelecommandClass, klass, TYPE_DC_DUMMYTELECOMMAND)

#define DC_DUMMYTELECOMMAND(obj) \
        OBJECT_CHECK(DC_DummyTelecommand, obj, TYPE_DC_DUMMYTELECOMMAND)


DC_DummyTelecommand* DC_DummyTelecommand_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Getter method for the execution counter.
 * @return the execution counter
 */
unsigned int DC_DummyTelecommand_getExecutionCounter(DC_DummyTelecommand *This);

/**
 * Set the return value of the execution check.
 * This is a setter method for the internal variable <code>executionCheckValue</code>
 * which defines the return value of the execution check implemented by this
 * telecommand.
 * @see #canExecute
 * @param executionCheckValue the value of the internal variable
 * <code>setExecutionCheckValue</code>
 */
void DC_DummyTelecommand_setExecutionCheckValue
(
    DC_DummyTelecommand *This,
    bool executionCheckValue
);

/**
 * Set the return value of the validity check.
 * This is a setter method for the internal variable <code>validityCheckValue</code>
 * which defines the return value of the validity check implemented by this
 * telecommand.
 * @see #isValid
 * @param validityCheckValue the value of the internal variable 
 * <code>setExecutionCheckValue</code>
 */
void DC_DummyTelecommand_setValidityCheckValue
(
    DC_DummyTelecommand *This,
    bool validityCheckValue
);

/**
 * Set the value of the validity check code.
 * This is a setter method for an internal variable 
 * which defines the return value of method <code>getValidityCheckCode</code>.
 * @see #getValidityCheckCode
 * @param validityCheckCode the value of the validity check code
 */
void DC_DummyTelecommand_setValidityCheckCode
(
   DC_DummyTelecommand *This, 
   TD_CheckCode validityCheckCode
);

/**
 * Set the value of the execution check code.
 * This is a setter method for an internal variable 
 * which defines the return value of method <code>getExecutionCheckCode</code>.
 * @see #getExecutionCheckCode
 * @param executionCheckCode the value of the validity check code
 */
void DC_DummyTelecommand_setExecutionCheckCode
(
   DC_DummyTelecommand *This, 
   TD_CheckCode executionCheckCode
);


#endif
