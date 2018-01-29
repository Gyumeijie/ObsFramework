//
//
// DC_DataPoolMonitor.h
//


#ifndef DC_DATAPOOLMONITOR_H
#define DC_DATAPOOLMONITOR_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/ConditionalPunctualAction.h"
#include "../Qom/object.h"


/*
 * Component to perform a monitoring check on all items in the system
 * data pool. The system data pool that is subjected to monitoring 
 * is loaded from the <code>CC_RootObject</code> class.
 * The data pool monitor is implemented as a form of
 * <i>conditional punctual action</i>. When it is executed,
 * the component iterates over all
 * items in the data pool(using the <i>iteration service</i> offered by
 * the data pool). It retrieves the <i>monitoring profile</i> associated to
 * each item and it uses it to check the current value of the item. If a
 * monitoring violation is detected, the <i>validity status</i> of the item
 * is set to "not valid" and the <i>recovery action</i> associated to
 * the item is executed.
 * @todo change the specification and the implementation of the class to set the status
 * of a data pool item whose monitoring check reports "no deviation from profile" to
 * "valid". At present, the validity status can only go from "valid" to "not valid".
 * @see DataPool
 * @see CC_RootObject
 * @see MonitoringProfile
 * @see RecoveryAction
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_DATAPOOLMONITOR "dc_datapoolmonitor"

void DC_DataPoolMonitor_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_DataPoolMonitor {
    ConditionalPunctualAction parent;
};


struct DC_DataPoolMonitorClass {
    ConditionalPunctualActionClass parent_class;
};


#define DC_DATAPOOLMONITOR_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_DataPoolMonitorClass, obj, TYPE_DC_DATAPOOLMONITOR)

#define DC_DATAPOOLMONITOR_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_DataPoolMonitorClass, klass, TYPE_DC_DATAPOOLMONITOR)

#define DC_DATAPOOLMONITOR(obj) \
        OBJECT_CHECK(DC_DataPoolMonitor, obj, TYPE_DC_DATAPOOLMONITOR)


DC_DataPoolMonitor* DC_DataPoolMonitor_new(void);

#endif
