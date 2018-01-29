//
//
// DC_DummyConditionalPunctualAction.h
//


#ifndef DC_DUMMYCONDITIONALPUNCTUALACTION_H
#define DC_DUMMYCONDITIONALPUNCTUALACTION_H


#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "ConditionalPunctualAction.h"
#include "../Qom/object.h"


/*
 * Dummy conditional punctual action that does not perform any action
 * and always returns "action successful".
 * A setter method allows the return value of the execution check to
 * be set by the user.
 * This punctual action is used for testing purposes.
 * @author Roberto Totaro
 * @version 1.0
 */
#define TYPE_DC_DUMMYCONDITIONALPUNCTUALACTION "dc_dummyconditionalpunctualaction"

void DC_DummyConditionalPunctualAction_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_DummyConditionalPunctualAction {
    ConditionalPunctualAction parent;

    bool executionFlag;
};


struct DC_DummyConditionalPunctualActionClass {
    ConditionalPunctualActionClass parent_class;
};


#define DC_DUMMYCONDITIONALPUNCTUALACTION_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_DummyConditionalPunctualActionClass,\
                                   obj, TYPE_DC_DUMMYCONDITIONALPUNCTUALACTION)

#define DC_DUMMYCONDITIONALPUNCTUALACTION_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_DummyConditionalPunctualActionClass,\
                                 klass, TYPE_DC_DUMMYCONDITIONALPUNCTUALACTION)

#define DC_DUMMYCONDITIONALPUNCTUALACTION(obj) \
        OBJECT_CHECK(DC_DummyConditionalPunctualAction,\
                                   obj, TYPE_DC_DUMMYCONDITIONALPUNCTUALACTION)


DC_DummyConditionalPunctualAction* DC_DummyConditionalPunctualAction_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the return value of <code>canExecute</code>. This method
 * was implemented only for testing purposes.
 * @see ConditionalPunctualAction#canExecute
 * @param newState the new value of <code>executionFlag</code>
 */
void DC_DummyConditionalPunctualAction_setExecutionFlag
(
    DC_DummyConditionalPunctualAction *This, 
    bool newState
);


#endif
