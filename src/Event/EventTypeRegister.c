#include "EventTypeRegister.h"
#include "DC_EventRepository.h"
#include "DC_Event.h"
#include "DC_PUSEventRepository.h"

void event_type_register()
{
   DC_Event_register();
   DC_EventRepository_register();
   DC_PUSEventRepository_register();
}
