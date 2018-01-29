//
//
// DC_Event.c (from DC_Event_inl.h file)
//


#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "DC_Event.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

TD_ObsTime DC_Event_getTimeStamp(const DC_Event *This)
{
	assert(This->timeStamp >= 0);
	return This->timeStamp;
}

TD_EventType DC_Event_getEventType(const DC_Event *This)
{
	assert(This->evtType > 0);
	return This->evtType;
}

void DC_Event_setTimeStamp(DC_Event *This, TD_ObsTime timeStamp)
{
	assert(timeStamp >= 0);
	This->timeStamp = timeStamp;
}

void DC_Event_setEventType(DC_Event *This, TD_EventType eventType)
{
	assert(eventType > 0);
	This->evtType = eventType;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj){}

DC_Event* DC_Event_new(void)
{
    Object *obj = object_new(TYPE_DC_EVENT);
    return (DC_Event*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data){}

static const TypeInfo type_info = {
    .name = TYPE_DC_EVENT,
    .parent = TYPE_OBJECT,
    .instance_size = sizeof(DC_Event),
    .abstract = false,
    .class_size = sizeof(DC_EventClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_Event_register(void)
{
    type_register_static(&type_info);
}
