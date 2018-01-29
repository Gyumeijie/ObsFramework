//
//
// DC_ProfileList.h
//
//
// Change Record:


#ifndef DC_PROFILELIST_H
#define DC_PROFILELIST_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "MonitoringProfile.h"
#include "../Qom/object.h"


/*
 * Monitoring profile that encapsulates a list of monitoring profiles.
 * This monitoring profile reports a "deviation from profile" if any of the
 * monitoring profiles in the list report "deviation from profile".
 * This component is useful when there is a need to subject a variable
 * to a sequence of monitoring actions. Use of this component allows the
 * client(the component that is responsible for performing the monitoring
 * action) to be shielded from the knowledge of which and how many monitoring
 * profiles are being used.
 * <p>
 * The size of the list of monitoring profiles is set as an initialization
 * parameter.
 * <p>
 * <i>Note:</i> This class has effectively become redundant after class 
 * <code>MonitoringProfile</code> was modified to handle chains of linked 
 * monitoring profiles. 
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @author Roberto Totaro
 * @version 1.2
 */
#define TYPE_DC_PROFILELIST "dc_profilelist"

void DC_ProfileList_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_ProfileList {
    MonitoringProfile parent;

    /**
     * Array of pointers to the monitoring profiles
     */
    MonitoringProfile **pList;
    /**
     * Size of the monitoring profile list
     */
    unsigned int listSize;
};


struct DC_ProfileListClass {
    MonitoringProfileClass parent_class;
};


#define DC_PROFILELIST_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_ProfileListClass, obj, TYPE_DC_PROFILELIST)

#define DC_PROFILELIST_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_ProfileListClass, klass, TYPE_DC_PROFILELIST)

#define DC_PROFILELIST(obj) \
        OBJECT_CHECK(DC_ProfileList, obj, TYPE_DC_PROFILELIST)


DC_ProfileList* DC_ProfileList_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the size of the list of monitoring profiles.
 * The list size defines the maximum number of monitoring profiles
 * that can be loaded into this component. A call to this method
 * causes memory for an internal data structure to be allocated.
 * This is an initialization method: it shall be called only
 * once, before the component is used for the first time.
 * It is not legal to set the repository size to 0.
 * The entries in the list are initialized to pNULL.
 * @param listSize the size of the monitoring list size
 */
void DC_ProfileList_setListSize(DC_ProfileList *This, unsigned int listSize);

/**
 * Return the size of the list of monitoring profiles.
 * @see #setListSize
 * @return listSize the size of the monitoring list size
 */
unsigned int DC_ProfileList_getListSize(const DC_ProfileList *This);

/**
 * Set the i-th entry in the list of monitoring profiles.
 * Only non-null entries are legal. The index i must lie in the range [0, N-1]
 * where N is size of the monitoring profile list.
 * Use of illegal values result in the generation of the
 * EVT_ILLEGAL_MP event report.
 * @see TD_EventId
 * @param i the index of the monitoring list
 * @param item the item to be added to the list at position i
 */
void DC_ProfileList_setMonitoringProfile
(
    DC_ProfileList *This,
    unsigned int i, 
    MonitoringProfile *item
);

/**
 * Get the i-th entry in the list of monitoring profiles.
 * If the i-th entry has not yet been loaded, a null value is returned.
 * The index i should lie in the range [0, N-1]
 * where N is size of the monitoring profile list.
 * @param i the index of the monitoring list
 * @return the item at position i of the monitoring profile list
 */
MonitoringProfile* DC_ProfileList_getMonitoringProfile
(
    const DC_ProfileList *This, 
    unsigned int i
);


#endif
