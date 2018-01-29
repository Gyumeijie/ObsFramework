//
//
// DC_DummyPunctualAction.h
//
//
// Change Record:


#ifndef DC_DUMMYPUNCTUALACTION_H
#define DC_DUMMYPUNCTUALACTION_H


#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "PunctualAction.h"
#include "../Qom/object.h"


/*
 * Dummy punctual action that does not perform any action and always
 * returns "action successful".
 * This punctual action may be useful for testing purposes.
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @author Roberto Totaro
 * @version 1.1
 */
#define TYPE_DC_DUMMYPUNCTUALACTION "dc_dummypunctualaction"

void DC_DummyPunctualAction_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_DummyPunctualAction {
    PunctualAction parent;

    unsigned int counter;
};


struct DC_DummyPunctualActionClass {
    PunctualActionClass parent_class;
};


#define DC_DUMMYPUNCTUALACTION_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_DummyPunctualActionClass,\
                                       obj, TYPE_DC_DUMMYPUNCTUALACTION)

#define DC_DUMMYPUNCTUALACTION_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_DummyPunctualActionClass,\
                                      klass, TYPE_DC_DUMMYPUNCTUALACTION)

#define DC_DUMMYPUNCTUALACTION(obj) \
        OBJECT_CHECK(DC_DummyPunctualAction, obj, TYPE_DC_DUMMYPUNCTUALACTION)


DC_DummyPunctualAction* DC_DummyPunctualAction_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Return the value of the activation counter.
 * @see #doAction
 * @return the value of the activation counter
 */
unsigned int 
DC_DummyPunctualAction_getActivationCounter(const DC_DummyPunctualAction *This);


#endif
