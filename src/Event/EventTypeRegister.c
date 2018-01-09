#include "EventTypeRegister.h"
#include "DC_EventRepository.h"
#include "DC_Event.h"

void event_type_register()
{
   DC_Event_register();
   DC_EventRepository_register();
}
