#include "TelecommandTypeRegister.h"
#include "Telecommand.h"
#include "DC_DummyTelecommand.h" 
#include "CriticalTelecommand.h"
#include "DC_DummyCriticalTelecommand.h" 
#include "PUSTelecommand.h" 

void telecommand_type_register(void)
{
   Telecommand_register();
   DC_DummyTelecommand_register();
   CriticalTelecommand_register();
   DC_DummyCriticalTelecommand_register(); 
   PUSTelecommand_register();
}

