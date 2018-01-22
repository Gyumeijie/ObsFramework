#include "TelecommandTypeRegister.h"
#include "Telecommand.h"
#include "DC_DummyTelecommand.h" 
#include "CriticalTelecommand.h"
#include "DC_DummyCriticalTelecommand.h" 
#include "PUSTelecommand.h" 
#include "DC_DummyPUSTelecommand.h"
#include "PUSDumpMemory.h"
#include "DC_PUSDumpMemoryAbsolute.h"

void telecommand_type_register(void)
{
   Telecommand_register();
   DC_DummyTelecommand_register();
   CriticalTelecommand_register();
   DC_DummyCriticalTelecommand_register(); 
   PUSTelecommand_register();
   DC_DummyPUSTelecommand_register();
   PUSDumpMemory_register();
   DC_PUSDumpMemoryAbsolute_register();
}

