//
//
// DC_ManoeuvrePunctualAction.h
//


#ifndef DC_MANOEUVREPUNCTUALACTION_H
#define DC_MANOEUVREPUNCTUALACTION_H


#include "../GeneralInclude/BasicTypes.h"
#include "../Base/PunctualAction.h"
#include "../Manoeuvre/CC_ManoeuvreManager.h"
#include "../Qom/object.h"


/*
 * Punctual action that launches a manoeuvre.
 * The action associated to this punctual action consists in loading
 * manoeuvre in the manoeuvre manager. The manoeuvre to be loaded
 * is a configuration parameter.
 * This punctual action is useful to model an action that consists
 * in triggering other actions that extend over time and which
 * therefore cannot be directly executed by the punctual action
 * component itself. In such a case, the actions that extend over a
 * time interval can be encoded in a manoeuvre component.
 * @see Manoeuvre
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_MANOEUVREPUNCTUALACTION "dc_manoeuvrepunctualaction"

void DC_ManoeuvrePunctualAction_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_ManoeuvrePunctualAction {
    PunctualAction parent;

    CC_ManoeuvreManager *pManoeuvreManager;
    Manoeuvre *pManoeuvre;
};


struct DC_ManoeuvrePunctualActionClass {
    PunctualActionClass parent_class;
};


#define DC_MANOEUVREPUNCTUALACTION_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_ManoeuvrePunctualActionClass, \
                                          obj, TYPE_DC_MANOEUVREPUNCTUALACTION)

#define DC_MANOEUVREPUNCTUALACTION_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_ManoeuvrePunctualActionClass, \
                                        klass, TYPE_DC_MANOEUVREPUNCTUALACTION)

#define DC_MANOEUVREPUNCTUALACTION(obj) \
        OBJECT_CHECK(DC_ManoeuvrePunctualAction, \
                                          obj, TYPE_DC_MANOEUVREPUNCTUALACTION)


DC_ManoeuvrePunctualAction* DC_ManoeuvrePunctualAction_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Setter method for the manoeuvre manager into which the target
 * manoeuvre is to be loaded.
 * @see #doAction
 * @param pManMan the manoeuvre manager
 */
void DC_ManoeuvrePunctualAction_setManoeuvreManager
(
    DC_ManoeuvrePunctualAction *This, 
    CC_ManoeuvreManager *pManMan
);

/**
 * Getter method for the manoeuvre manager.
 * @see #setManoeuvreManager
 * @return pManMan the manoeuvre manager
 */
CC_ManoeuvreManager* DC_ManoeuvrePunctualAction_getManoeuvreManager
(
    const DC_ManoeuvrePunctualAction *This
);

/**
 * Setter method for the manoeuvre to be loaded into the manoeuvre
 * manager.
 * @see #doAction
 * @param pMan the manoeuvre
 */
void DC_ManoeuvrePunctualAction_setManoeuvre
(
    DC_ManoeuvrePunctualAction *This,
    Manoeuvre *pMan
);

/**
 * Getter method for the manoeuvre.
 * @see #doAction
 * @return pManMan the manoeuvre manager
 */
Manoeuvre* DC_ManoeuvrePunctualAction_getManoeuvre
(
    const DC_ManoeuvrePunctualAction *This
);


#endif
