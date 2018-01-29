//
//
// DC_ControlList.h
//
//
// Change Record:


#ifndef DC_CONTROLLIST_H
#define DC_CONTROLLIST_H


#include "../GeneralInclude/BasicTypes.h"
#include "../Base/ConditionalPunctualAction.h"
#include "ControlBlock.h"
#include "../Qom/object.h"


/*
 * Encapsulation of list of <i>control blocks</i>. This control action can be
 * configured with a list of control blocks whose <code>propagate(void)</code> method
 * is invoked upon execution of the action. This class assumes that the target
 * control blocks are already fully configured.
 * <p>
 * Control lists offer a <i>reset service</i>. A call to the reset service
 * causes all the target control blocks to be reset.
 * <p>
 * This class implements a default <i>execution check</i> that always returns
 * "can execute". This means that, if the control action is enabled, then its
 * execution will always result in the target control blocks receiving a propagation
 * request. Subclasses can of course implement different execution checks.
 * @author Roberto Totaro
 * @version 1.0
 */
#define TYPE_DC_CONTROLLIST "dc_controllist"

void DC_ControlList_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_ControlList {
    ConditionalPunctualAction parent;

    unsigned int listSize;
    ControlBlock **controlBlockList;
};


struct DC_ControlListClass {
    ConditionalPunctualActionClass parent_class;
};


#define DC_CONTROLLIST_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_ControlListClass, obj, TYPE_DC_CONTROLLIST)

#define DC_CONTROLLIST_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_ControlListClass, klass, TYPE_DC_CONTROLLIST)

#define DC_CONTROLLIST(obj) \
        OBJECT_CHECK(DC_ControlList, obj, TYPE_DC_CONTROLLIST)


DC_ControlList* DC_ControlList_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the size of the list of control blocks.
 * The list size defines the maximum number of control blocks
 * that can be loaded into this component. A call to this method
 * causes memory for an internal data structure to be allocated.
 * This is an initialization method: it shall be called only
 * once, before the component is used for the first time. It is not legal
 * to set the repository size to 0. The entries in the list are initialized
 * to illegal values to signify that the component is not yet configured.
 * @param listSize the size of the control block list size
 */
void DC_ControlList_setListSize(DC_ControlList *This, unsigned int listSize);

/**
 * Return the size of the list of control blocks.
 * @see #setListSize
 * @return listSize the size of the control block list size
 */
unsigned int DC_ControlList_getListSize(const DC_ControlList *This);

/**
 * Load the i-th entry in the list of control blocks.
 * Only non-null entries are legal. The index i must lie in the interval [0, N-1]
 * where N is the size of the control block list.
 * Use of illegal values results in the generation of an EVT_ILLEGAL_CL event report.
 * @see TD_EventId
 * @param i the index of the control block list
 * @param item the item to be added to the list at position i
 */
void DC_ControlList_setControlBlock
(
    DC_ControlList *This, 
    unsigned int i,
    ControlBlock *item
);

/**
 * Get the i-th entry in the list of control blocks.
 * The index i should lie in the interval [0, N-1]
 * where N is the size of the control block list.
 * No checks are performed on the legality of the index.
 * @param i the index of the control block list
 * @return the item at position i of the control block list
 */
ControlBlock* DC_ControlList_getControlBlock
(
    const DC_ControlList *This, 
    unsigned int i
);

/**
 * Reset all the control blocks.
 */
void DC_ControlList_reset(DC_ControlList *This);


#endif
