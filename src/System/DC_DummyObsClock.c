//
//
// DC_DummyObsClock.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "DC_DummyObsClock.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_DummyObsClock_setTime(DC_DummyObsClock *This, TD_ObsTime time)
{
     assert( time>= 0 );
     This->time = time;
}

void DC_DummyObsClock_setCycle(DC_DummyObsClock *This, TD_ObsCycle cycle)
{
     assert( cycle>=0 );
     This->cycle = cycle;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Return the on-board time last set with <code>setTime</code>.
 * @see #setTime
 * @return the current on-board time
 */
static TD_ObsTime getTime(void *obj)
{
    return DC_DUMMYOBSCLOCK(obj)->time;
}

/**
 * Return the on-board cycle last set with <code>setTime</code>.
 * @see #setTime
 * @return the current on-board cycle
 */
static TD_ObsCycle getCycle(void *obj)
{
    return DC_DUMMYOBSCLOCK(obj)->cycle;
}

/**
 * No synchronization service is implemented: method returns without
 * taking any action.
 */
static void synchronizeWithSystemTime(void *obj)
{
    return;
}

/**
 * Reset the OBS clock by resetting the on-board time and cycle to zero.
 */
static void reset(void *obj)
{
    DC_DummyObsClock *This = DC_DUMMYOBSCLOCK(obj);

    This->time = 0;
    This->cycle = 0;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
     reset(obj);
     CC_RootObject_setClassId((CC_RootObject*)obj, ID_DUMMYOBSCLOCK);
}

DC_DummyObsClock* DC_DummyObsClock_new(void)
{
    return (DC_DummyObsClock*)object_new(TYPE_DC_DUMMYOBSCLOCK);
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    DC_DummyObsClockClass *dc_docc = DC_DUMMYOBSCLOCK_CLASS(oc);

    ObsClockClass *occ = OBSCLOCK_CLASS(oc);
    occ->getTime = getTime;
    occ->getCycle = getCycle;
    occ->synchronizeWithSystemTime = synchronizeWithSystemTime;
    occ->reset = reset;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_DUMMYOBSCLOCK,
    .parent = TYPE_OBSCLOCK,
    .instance_size = sizeof(DC_DummyObsClock),
    .abstract = false,
    .class_size = sizeof(DC_DummyObsClockClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_DummyObsClock_register(void)
{
    type_register_static(&type_info);
}
