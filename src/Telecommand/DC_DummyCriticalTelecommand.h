//
//
// DC_DummyCriticalTelecommand.h
//


#ifndef DC_DUMMYCRITICALTELECOMMAND_H
#define DC_DUMMYCRITICALTELECOMMAND_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "CriticalTelecommand.h"
#include "../Qom/object.h"


/*
 * Dummy telecommand that increments a counter every time it is 
 * executed. This telecommand is useful for testing purposes.
 * The telecommand maintains an <i>execution counter</i> that is initialized 
 * to zero when the telecommand object is first instantiated and is 
 * incremented by one every time the telecommand receives an <code>execute</code>
 * request. There is no way to reset the execution counter.
 * <p>
 * The telecommand offers a method to change the return value of its
 * execution check and of its validity check. These are useful to 
 * simulate telecommands whose
 * execution check returns "telecommand cannot executed" or whose
 * validity check returns "telecommand not valid".
 * @author Roberto Totaro
 * @version 1.0
 */
#define TYPE_DC_DUMMYCRITICALTELECOMMAND "dc_dummycriticaltelecommand"

void DC_DummyCriticalTelecommand_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_DummyCriticalTelecommand {
    CriticalTelecommand parent;

    unsigned int numberOfExecutions;
    bool imageValid;
};


struct DC_DummyCriticalTelecommandClass {
    CriticalTelecommandClass parent_class;
};


#define DC_DUMMYCRITICALTELECOMMAND_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_DummyCriticalTelecommandClass, \
                                         obj, TYPE_DC_DUMMYCRITICALTELECOMMAND)

#define DC_DUMMYCRITICALTELECOMMAND_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_DummyCriticalTelecommandClass, \
                                       klass, TYPE_DC_DUMMYCRITICALTELECOMMAND)

#define DC_DUMMYCRITICALTELECOMMAND(obj) \
        OBJECT_CHECK(DC_DummyCriticalTelecommand, \
                                         obj, TYPE_DC_DUMMYCRITICALTELECOMMAND)


DC_DummyCriticalTelecommand* DC_DummyCriticalTelecommand_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Getter method for <code>numberOfExecutions</code>. Used only for
 * testing purposes.
 * @see #doCriticalAction
 * @return the number of times DC_DummyCriticalTelecommand_doCriticalAction(void)
 * has been called
 */
unsigned int DC_DummyCriticalTelecommand_getNumberOfExecutions
(
    DC_DummyCriticalTelecommand *This
);

/**
 * Setter method for <code>imageValid</code>. Used only for testing purposes.
 * @see #isImageValid
 * @param isValid new value of imageValid
 */
void DC_DummyCriticalTelecommand_setImageValidity
(
    DC_DummyCriticalTelecommand *This, 
    bool isValid
);


#endif
