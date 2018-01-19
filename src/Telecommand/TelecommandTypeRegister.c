#include "TelecommandTypeRegister.h"
#include "Telecommand.h"
#include "DC_DummyTelecommand.h" 

void telecommand_type_register(void)
{
   Telecommand_register();
   DC_DummyTelecommand_register();
}

