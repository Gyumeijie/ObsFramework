#include "TelecommandTypeRegister.h"
#include "Telecommand.h"
#include "DC_DummyTelecommand.h" 
#include "CriticalTelecommand.h"

void telecommand_type_register(void)
{
   Telecommand_register();
   DC_DummyTelecommand_register();
   CriticalTelecommand_register();
}

