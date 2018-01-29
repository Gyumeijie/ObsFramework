//
//
// DC_DummyObsClock.h
//


#ifndef DC_DUMMYOBSCLOCK_H
#define DC_DUMMYOBSCLOCK_H


#include "../GeneralInclude/BasicTypes.h"
#include "ObsClock.h"
#include "../Qom/object.h"


/*
 * Dummy OBS Clock component useful for testing purposes or for applications
 * where timing information is not available.
 * This component provides a dummy implementation of the OBS Clock abstract
 * class. It exposes a method <code>setTime</code> through which an external
 * entity can set the on-board time and the on-board cycle. These values are
 * then returned by the standard timing services declared by the OBS Clock
 * abstract base class. No timing synchronization service is implemented.
 * <p>
 * A dummy clock can be useful because the correct configuration of the
 * <code>CC_RootObject</code> class requires the class to be provided with an
 * OBS Clock plug-in component. This dummy component can be used when no "real"
 * OBS Clock component is available(for instance, during testing).
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_DUMMYOBSCLOCK "dc_dummyobsclock"

void DC_DummyObsClock_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_DummyObsClock {
    ObsClock parent;

    TD_ObsCycle cycle;
    TD_ObsTime time;
};


struct DC_DummyObsClockClass {
    ObsClockClass parent_class;
};


#define DC_DUMMYOBSCLOCK_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_DummyObsClockClass, obj, TYPE_DC_DUMMYOBSCLOCK)

#define DC_DUMMYOBSCLOCK_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_DummyObsClockClass, klass, TYPE_DC_DUMMYOBSCLOCK)

#define DC_DUMMYOBSCLOCK(obj) \
        OBJECT_CHECK(DC_DummyObsClock, obj, TYPE_DC_DUMMYOBSCLOCK)


DC_DummyObsClock* DC_DummyObsClock_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the value of the on-board time that will be returned
 * by method <code>getTime</code> and <code>getCycle</code>. The on-board time 
 * value must be zero or a positive number.
 * @see #getTime
 * @param time the on-board time
 */
void DC_DummyObsClock_setTime(DC_DummyObsClock *This, TD_ObsTime time);

/**
 * Set the value of the cycle that will be returned
 * by method <code>getCycle</code>. The cycle value 
 * must be zero or a positive numbers.
 * @see #getCycle
 * @param time the on-board time
 * @param cycle the on-board cycle
 */
void DC_DummyObsClock_setCycle(DC_DummyObsClock *This, TD_ObsCycle cycle);


#endif
