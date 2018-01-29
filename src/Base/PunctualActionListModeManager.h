//
//
// PunctualActionListModeManager.h
//


#ifndef PUNCTUALACTIONLISTMODEMANAGER_H
#define PUNCTUALACTIONLISTMODEMANAGER_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/PunctualActionModeManager.h"
#include "../Qom/object.h"


/*
 * Base abstract class for list-based punctual action mode managers.
 * A list-based punctual action mode manager handles the set of 
 * punctual action in a punctual action mode manager as a statically defined 
 * linear list. 
 * The mode manager maintains several such lists, one for each
 * operational mode.
 * <p>
 * At any given time, one list is the <i>current list</i> (or
 * <i>active list</i>).
 * The iteration methods specified in the super class are implemented
 * to iterate over the items in the list starting with the one with the 
 * lowest position and ending with the one with the highest position
 * in the list.
 * <p>
 * The lists are loaded, one item at a time, when the mode manager
 * is configured. The loading methods
 * are: <code>loadListLength</code> (to load the number
 * items in each list) and <code>loadItem</code>
 * (to load the individual items in each list).
 * <p>
 * This class is abstract because it does not define the update
 * mechanism for the mode manager. This must be defined by concrete
 * subclasses.
 * </p>
 * An initialization sequence for this class consists of the following
 * steps(to be performed in the order given): <ul>
 * <li>Set the number of modes through method <code>setNumberOfModes</code></li>
 * <li>Set the default mode <code>setDefaultMode</code></li>
 * <li>Set the lengths of the lists through method
 * <code>setListLength</code></li>
 * <li>Load the individual items through method <code>setListItem</code></li>
 * <li>Reset the component by calling method <code>reset</code></li>
 * </ul>
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 * @ingroup Base
 * @ingroup ModeManagement
 */
#define TYPE_PUNCTUALACTIONLISTMODEMANAGER "punctualactionlistmodemanager"

void PunctualActionListModeManager_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct PunctualActionListModeManager {
    PunctualActionModeManager parent;

    PunctualAction ***list;    // list[i][j] is the j-th item in the i-th list
    unsigned int *listLength;   // listLength[i] is the length of the i-th list
    unsigned int iterationListIndex;  // the index of the iteration list
    unsigned int counter;             // iteration counter
};


struct PunctualActionListModeManagerClass {
    PunctualActionModeManagerClass parent_class;
};


#define PUNCTUALACTIONLISTMODEMANAGER_GET_CLASS(obj) \
        OBJECT_GET_CLASS(PunctualActionListModeManagerClass,\
                                       obj, TYPE_PUNCTUALACTIONLISTMODEMANAGER)

#define PUNCTUALACTIONLISTMODEMANAGER_CLASS(klass) \
        OBJECT_CLASS_CHECK(PunctualActionListModeManagerClass,\
                                     klass, TYPE_PUNCTUALACTIONLISTMODEMANAGER)

#define PUNCTUALACTIONLISTMODEMANAGER(obj) \
        OBJECT_CHECK(PunctualActionListModeManager,\
                                       obj, TYPE_PUNCTUALACTIONLISTMODEMANAGER)


PunctualActionListModeManager* PunctualActionListModeManager_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Load an item in a list. The item <code>pItem</code> is loaded in the pos-th
 * position of the n-th list. A check is performed on the legality of the
 * <code>n</code> and <code>pos</code> arguments. If they are found
 * to be out of range, the fact is reported as an event of type EVT_ILLEGAL_MM.
 * <p>
 * @param n the list index
 * @param pos the position within the list where the item is loaded
 * @param pItem the item to be loaded
 */
void PunctualActionListModeManager_setListItem
(
    PunctualActionListModeManager *This, 
    unsigned int n, 
    unsigned int pos, 
    PunctualAction* pItem
);

/**
 * Set the size of the n-th list. The n-th list is the list that is active
 * in the n-th operational mode.
 * A call to this method causes memory to be allocated to store the items in
 * the n-th list. The newly allocated memory is initialized
 * to pNULL.
 * <p>
 * This is an initialization method. It should only be called once.
 * @param n the list PunctualActionListModeManager_index(should be in the range [0, N-1] where N is the
 * number of modes)
 * @param length the number of items in the list-th telemetry packet PunctualActionListModeManager_list(should
 * be greater than zero)
 */
void PunctualActionListModeManager_setListLength
(
    PunctualActionListModeManager *This, 
    unsigned int n,
    unsigned int length
);


#endif
