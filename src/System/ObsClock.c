//
//
// ObsClock.c (generated from ObsClock.h)
//

#include "ObsClock.h"



///////////////////////////////////////////////////////////////////////////////
//
//                    pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Return the current on-board time.
 * @return the current on-board time
 */
static TD_ObsTime getTime(void *obj)
{
    // this is automate genenrated by converter
}

/**
 * Return the current on-board cycle.
 * @return the current on-board cycle
 */
static TD_ObsCycle getCycle(void *obj)
{
    // this is automate genenrated by converter
}

/**
 * Implement the timing synchronization service.
 */
static void synchronizeWithSystemTime(void *obj)
{
    // this is automate genenrated by converter
}

/**
 * Reset the OBS clock.
 */
static void reset(void *obj)
{
    // this is automate genenrated by converter
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj){}

ObsClock* ObsClock_new(void)
{
    return (ObsClock*)object_new(TYPE_OBSCLOCK);
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    ObsClockClass *occ = OBSCLOCK_CLASS(oc);

    occ->getTime = getTime;
    occ->getCycle = getCycle;
    occ->synchronizeWithSystemTime = synchronizeWithSystemTime;
    occ->reset = reset;
}

static const TypeInfo type_info = {
    .name = TYPE_OBSCLOCK,
    .parent = TYPE_CC_ROOTOBJECT,
    .instance_size = sizeof(ObsClock),
    .abstract = true,
    .class_size = sizeof(ObsClockClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void ObsClock_register(void)
{
    type_register_static(&type_info);
}
