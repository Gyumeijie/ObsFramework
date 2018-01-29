//
//
// CC_ManoeuvreManager.h
//


#ifndef CC_MANOEUVREMANAGER_H
#define CC_MANOEUVREMANAGER_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "Manoeuvre.h"
#include "../Qom/object.h"


/*
 * This class encapsulates a manoeuvre manager.
 * The manoeuvre manager is responsible for controlling the execution
 * of manoeuvres.
 * Manoeuvres are loaded into the manoeuvre manager and from
 * that moment onward their execution,
 * termination, and abortion remain under the control of the manoeuvre
 * manager.
 * The manoeuvre manager sees manoeuvres as instances of type
 * <CODE>Manoeuvre</CODE>.
 * <p>
 * The manoeuvre manager maintains a list of pending manoeuvres.
 * This is called the <i>pending manoeuvre list</i>.
 * The <i>pending manoeuvres</i> are the manouvres that are currently
 * loaded into the manoeuvre manager and that
 * are either executing or awaiting to start execution.
 * <p>
 * External entities typically performs three types of operations
 * upon a manoeuvre manager.
 * They can <i>load</i> a new manoeuvre in the manoeuvre manager.
 * They can <i>abort</i> execution of an already loaded manoeuvre.
 * They can <i>activate</i> the manoeuvre manager to advance the execution
 * of the pending manoeuvres.
 * <p>
 * The manoeuvre manager contributes to the management of the "in use" status of
 * manoeuvres. More precisely, before unloading a manoeuvre, the manoeuvre
 * manager marks if as "no longer in use".
 * <p>
 * The manoeuvre manager creates event reports to record the following
 * occurrences:<ul>
 * <li>Attempt to load a manoeuvre when the list of pending manoeuvres
 * is already full</li>
 * <li>A new manoeuvre is loaded</li>
 * <li>A manoeuvre is unloaded</li>
 * </ul>
 * In all cases, the <i>event originator</i> that is passed to the event creation
 * method is the manoeuvre that is being processed.
 * Note that the creation of event reports describing
 * changes of state of the manoeuvre are the responsibility of the
 * manoeuvres themselves.
 * @see Manoeuvre
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 * @ingroup FunctionalityManagers
 * @ingroup Manoeuvre
 */
#define TYPE_CC_MANOEUVREMANAGER "cc_manoeuvremanager"

void CC_ManoeuvreManager_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct CC_ManoeuvreManager {
    CC_RootObject parent;

    Manoeuvre **pManList;    // array of pointers -- pending manoeuvre list
    unsigned int manListSize;
    unsigned int manCounter;   // number of pending manoeuvres
};


struct CC_ManoeuvreManagerClass {
    CC_RootObjectClass parent_class;
 
    void (*unload)(void *obj, Manoeuvre* pManoeuvre);
    void (*load)(void *obj, Manoeuvre* pManoeuvre);
    void (*abort)(void *obj, Manoeuvre* pManoeuvre);
    void (*activate)(void *obj);
};


#define CC_MANOEUVREMANAGER_GET_CLASS(obj) \
        OBJECT_GET_CLASS(CC_ManoeuvreManagerClass, obj, TYPE_CC_MANOEUVREMANAGER)

#define CC_MANOEUVREMANAGER_CLASS(klass) \
        OBJECT_CLASS_CHECK(CC_ManoeuvreManagerClass, klass, TYPE_CC_MANOEUVREMANAGER)

#define CC_MANOEUVREMANAGER(obj) \
        OBJECT_CHECK(CC_ManoeuvreManager, obj, TYPE_CC_MANOEUVREMANAGER)


CC_ManoeuvreManager* CC_ManoeuvreManager_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Unload all pending CC_ManoeuvreManager_manoeuvres(aborting those that are executing).
 * A reset bring the telecommand manager
 * to the state where it was immediately after having being configured.
 */
void CC_ManoeuvreManager_reset(CC_ManoeuvreManager *This);

/**
 * Set the size of the pending manoeuvre list representing the maximum number
 * of pending manoeuvre that can be managed by the manoeuvre manager.
 * This method causes the memory for the pending manoeuvre list data structure
 * to be allocated and the data structure to be initialized. Only positive values
 * of the manoeuvre list size are legal.
 * <p>
 * This is an initialization method. It should be called before the
 * manoeuvre manager is used the first time and it should not be called more
 * than once.
 * @param listSize the maximum number of pending manoeuvres that can be
 * managed by the Manoeuvre Manager. This should be a positive number.
 */
void CC_ManoeuvreManager_setPendingManoeuvreListSize
(
    CC_ManoeuvreManager *This,
    const unsigned int listSize
);

/**
 * Get the size of the pending manoeuvre list.
 * @see #setPendingManoeuvreListSize
 * @return the maximum number of pending manoeuvres that can be
 * managed by the Manoeuvre Manager
 */
unsigned int CC_ManoeuvreManager_getPendingManoeuvreListSize(CC_ManoeuvreManager *This);

/**
 * Get the number of currently pending manoeuvres.
 * @see #setPendingManoeuvreListSize
 * @return the number of currently pending manoeuvres
 */
unsigned int CC_ManoeuvreManager_getPendingManoeuvres(CC_ManoeuvreManager *This);


#endif
