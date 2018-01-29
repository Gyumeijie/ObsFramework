//
//
// ObsClock.h
//


#ifndef OBSCLOCK_H
#define OBSCLOCK_H


#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "../Qom/object.h"


/*
 * Abstract class representing the interface to an <i>OBS Clock Component</i> that can
 * provide timing-related information and services to the application.
 * OBS Clock Components can provide two types of timing information
 * and one service. The timing information are: the <i>on-board time</i>
 * and the <i>on-board cycle</i>. The service is the <i>timing synchronization
 * service</i>.
 * <p>
 * The <i>on-board time</i> is a time measurement provided by some external
 * source. The <i>on-board cycle</i> assumes that the application is running
 * cyclically and it represents the number of cycle from some arbitrary point
 * (for instance, the time of creation of the OBS clock component, or the time
 * it was last reset).
 * <p>
 * The <i>timing synchronization service</i> is an application-dependent service
 * to synchronize the on-board time maintained by the OBS clock component.
 * @todo create a PUSObsClock class derived from this class to implement 
 * PUS-specific timing services
 * @todo spilt the setTime method into two setter methods 
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_OBSCLOCK "obsclock"

void ObsClock_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct ObsClock {
    CC_RootObject parent;
};


struct ObsClockClass {
    CC_RootObjectClass parent_class;
 
    TD_ObsTime (*getTime)(void *obj);
    TD_ObsCycle (*getCycle)(void *obj);
    void (*synchronizeWithSystemTime)(void *obj);
    void (*reset)(void *obj);
};


#define OBSCLOCK_GET_CLASS(obj) \
        OBJECT_GET_CLASS(ObsClockClass, obj, TYPE_OBSCLOCK)

#define OBSCLOCK_CLASS(klass) \
        OBJECT_CLASS_CHECK(ObsClockClass, klass, TYPE_OBSCLOCK)

#define OBSCLOCK(obj) \
        OBJECT_CHECK(ObsClock, obj, TYPE_OBSCLOCK)


ObsClock* ObsClock_new(void);

#endif
