//
//
// CC_TelecommandManager.h
//
//
// Change Record:


#ifndef CC_TELECOMMANDMANAGER_H
#define CC_TELECOMMANDMANAGER_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "Telecommand.h"
#include "TelecommandLoader.h"
#include "../Qom/object.h"


/*
 * This class encapsulates a telecommand manager.
 * The telecommand manager is the component that is responsible for controlling
 * execution of telecommands.
 * Telecommands are loaded into the telecommand manager(normally by the
 * telecommand loader) and from that
 * moment onward their execution remains under the control of the telecommand
 * manager.
 * The telecomand manager sees telecommands as objects of type
 * <CODE>Telecommand</CODE>.
 * <p>
 * The telecommand manager maintains a list of pending telecommand objects.
 * This is called the <i>pending telecommand list</i>.
 * The <i>pending telecommands</i> are the telecommand objects that are
 * currently loaded into the telecommand manager and that
 * are due for execution.
 * Execution can be immediate or it can be deferred to a certain time
 * (time-tagged telecommands).
 * Before a telecommand is executed, the <i>execution check</i> is performed
 * upon it.
 * In this way, the telecommand has a way of checking whether the conditions
 * for its execution are fulfilled.
 * If the execution check fails, the telecommand is aborted.
 * <p>
 * When a telecommand is loaded into the telecommand manager, the telecommand
 * manager performs a <i>validity check</i>
 * upon it.
 * If the validity check fails, the telecommand is immediately aborted.
 * <p>
 * After being executed, or after being aborted, a telecommand is <i>unloaded</i>.
 * This means that the telecommand is removed from the list of pending
 * telecommands and that the telecommand loader is notified that the
 * telecommand is no longer in use.
 * This allows the telecommand loader to release any resources that it had
 * allocated to the telecommand and to perform any other clean-up actions.
 * <p>
 * Telecommands can be <i>aborted</i>.
 * An abort operation consists in the unloading of a telecommand that has not
 * yet been executed.
 * <p>
 * The telecommand manager creates event reports to record the following
 * occurrences: a telecommand has been loaded; a telecommand has been
 * unloaded; a telecommand has been aborted; a telecommand could not be
 * loaded because it failed its validity check; a telecommand could
 * not be loaded because the list of telecommands was full; a
 * telecommand could not be executed because its execution check failed.
 * Note that execution of the telecommand is not recorded because
 * telecommands are punctual actions and
 * therefore their execution is automatically recorded as an event
 * by the services provided by the <code>PunctualAction</code> class.
 * <p>
 * The configuration procedure for a newly instantiated telecommand
 * manager is as follows: <ol>
 * <li>Load an OBS clock in the telecommand manager(method
 * <code>setObsClock</code>.</li>
 * <li>Load a telecommand loader in the telecommand manager(method
 * <code>setTelecommandLoader</code>.</li>
 * <li>Set the size of the pending telecommand list(method
 * <code>setPendingTelecommandListSize</code>).</li>
 * </ol>
 * The above operations can be execute in any order.
 * <p>
 * The telecommand manager is intended to be used "as is" and without
 * changes. However, the <code>load</code>, <code>abort</code> and
 * <code>activate</code> methods are marked virtual to
 * allow users to customize their logic.
 * @todo extend the test case for the telecommand manager to check the
 * generation of an event in case the telecommand execution is not successful
 * @todo the name of method setPendingTelecommandListSize is not consistent with
 * the name of the equivalent method in class ManoeuvreManager(which is simply
 * called setPendingListSize. The two names should perhaps be harmonized.
 * @see Telecommand
 * @see TelecommandLoader
 * @see PunctualAction
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 * @ingroup FunctionalityManagers
 * @ingroup Telecommand
 */
#define TYPE_CC_TELECOMMANDMANAGER "cc_telecommandmanager"

void CC_TelecommandManager_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct CC_TelecommandManager {
    CC_RootObject parent;

    Telecommand **pTcList;    // array of pointers -- pending telecommand list
    unsigned int tcListSize;
    unsigned int tcCounter;   // number of pending telecommands
    TelecommandLoader *pTcLoader;
    ObsClock *pObsClock;
};


struct CC_TelecommandManagerClass {
    CC_RootObjectClass parent_class;
 
    void (*load)(void *obj, Telecommand* pTelecommand);
    void (*abort)(void *obj, Telecommand* pTelecommand);
    void (*activate)(void *obj);
};


#define CC_TELECOMMANDMANAGER_GET_CLASS(obj) \
        OBJECT_GET_CLASS(CC_TelecommandManagerClass, \
                                            obj, TYPE_CC_TELECOMMANDMANAGER)

#define CC_TELECOMMANDMANAGER_CLASS(klass) \
        OBJECT_CLASS_CHECK(CC_TelecommandManagerClass, \
                                          klass, TYPE_CC_TELECOMMANDMANAGER)

#define CC_TELECOMMANDMANAGER(obj) \
        OBJECT_CHECK(CC_TelecommandManager, obj, TYPE_CC_TELECOMMANDMANAGER)


CC_TelecommandManager* CC_TelecommandManager_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Abort all pending telecommands. A reset bring the telecommand manager
 * to the state where it was immediately after having being configured.
 */
void CC_TelecommandManager_reset(CC_TelecommandManager *This);

/**
 * Set the size of the pending telecommand list representing the maximum
 * number of pending telecommands that can be managed by the telecommand
 * manager.
 * This method causes memory for the pending telecommand list data
 * structure to be allocated and the data structure to be
 * initialized. Only positive telecommand list sizes are legal.
 * <p>
 * This is an initialization method. It should be called before the
 * telecommand manager is used the first time and it should not be called more
 * than once.
 * @param listSize the maximum number of pending telecommands that can be
 * managed by the Telecommand Manager. This should be a positive number.
 */
void CC_TelecommandManager_setPendingTelecommandListSize
(
    CC_TelecommandManager *This, 
    unsigned int listSize
);

/**
 * Get the size of the pending telecommand list.
 * @see #setPendingTelecommandListSize
 * @return the maximum number of pending telecommands that can be
 * managed by the Telecommand Manager
 */
unsigned int CC_TelecommandManager_getPendingTelecommandListSize
(
    CC_TelecommandManager *This
);

/**
 * Get the number of currently pending telecommands.
 * @see #setPendingTelecommandListSize
 * @return the number of currently pending telecommands
 */
unsigned int CC_TelecommandManager_getPendingTelecommands
(
    CC_TelecommandManager *This
);

/**
 * Get the i-th pending CC_TelecommandManager_telecommand(only provided for testing purposes). 
 * This method returns the i-th entry in the list of pending telecommands.
 * The index i should be in the range [0, N-1] where N is the size of the telecommand
 * lending list. A null
 * pointer is returned if no telecommand is currently loaded at the i-th
 * position of the list. This method is only intended to be used for
 * testing purposes. It should not be used during normal operation.
 * @see #setPendingTelecommandListSize
 * @return the i-th pending telecommand or null if the i-the entry in the list is empty
 */
Telecommand* CC_TelecommandManager_getPendingTelecommand
(
    CC_TelecommandManager *This, 
    unsigned int i
);

/**
 * Abort a telecommand.
 * This method has the same semantics as the abort method that takes a
 * telecommand pointer as argument but it designates the telecommand to
 * be aborted by its identifier rather than through a pointer to the
 * object that encapsulates it. See the documentation of that method
 * for more information.
 * <p>
 * However, note that in this case, if a telecommand with a given id
 * appears more than once in the pending telecommand CC_TelecommandManager_list(e.g. with two
 * different time tags), then all its instances will be aborted.
 * @see abort
 * @see TelecommandLoader#release
 * @param telecommandId the telecommand to be aborted
 */
void CC_TelecommandManager_abort
(
    CC_TelecommandManager *This, 
    TD_TelecommandId telecommandId
);

/**
 * Load the telecommand loader as a plug-in component.
 * The telecommand manager needs access to the telecommand loader because
 * it must notify it when a telecommand is unloaded.
 * @see #activate
 * @see #abort
 * @param pTcLoader the telecommand loader
 */
void CC_TelecommandManager_setTelecommandLoader
(
    CC_TelecommandManager *This, 
    TelecommandLoader *pTcLoader
);

/**
 * Getter method for the telecommand loader plug-in component.
 * @see #setTelecommandLoader
 * @return the telecommand loader
 */
TelecommandLoader* CC_TelecommandManager_getTelecommandLoader
(
    CC_TelecommandManager *This
);

/**
 * Load the OBS clock as a plug-in component.
 * The telecommand manager needs access to the on-board time because it
 * needs to check the telecommand time tag with the current time.
 * @see #activate
 * @param pObsClock the on-board clock
 */
void CC_TelecommandManager_setObsClock
(
    CC_TelecommandManager *This,
    ObsClock *pObsClock
);

/**
 * Getter method for the OBS clock plug-in component.
 * @see #setObsClock
 * @return the on-board clock
 */
ObsClock* CC_TelecommandManager_getObsClock(CC_TelecommandManager *This);


#endif
