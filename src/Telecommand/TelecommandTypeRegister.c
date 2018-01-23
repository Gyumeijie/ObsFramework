#include "TelecommandTypeRegister.h"
#include "Telecommand.h"
#include "DC_DummyTelecommand.h" 
#include "CriticalTelecommand.h"
#include "DC_DummyCriticalTelecommand.h" 
#include "PUSTelecommand.h" 
#include "DC_DummyPUSTelecommand.h"
#include "PUSDumpMemory.h"
#include "DC_PUSDumpMemoryAbsolute.h"
#include "DC_PUSDumpMemoryOffset.h"
#include "PUSMemoryLoad.h"
#include "DC_PUSMemoryLoadAbsolute.h"
#include "DC_PUSMemoryLoadOffset.h"
#include "TelecommandLoader.h"
#include "DC_DummyTelecommandLoader.h"

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
   DC_PUSDumpMemoryOffset_register();
   PUSMemoryLoad_register();
   DC_PUSMemoryLoadAbsolute_register();
   DC_PUSMemoryLoadOffset_register();

   TelecommandLoader_register();
   DC_DummyTelecommandLoader_register();
}

