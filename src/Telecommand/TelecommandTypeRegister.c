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
#include "CC_TelecommandManager.h"
#include "DC_TestPUSTelecommand.h"
#include "CC_TelecommandFactory.h"
#include "DC_BasicPUSTcLoader.h"
#include "DC_PUSClearDataReporting.h"
#include "DC_PUSControlDataReporting.h"
#include "DC_PUSDefineDataReporting.h"
#include "PUSFunctionManagement.h"

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
   DC_TestPUSTelecommand_register();
   DC_PUSClearDataReporting_register();
   DC_PUSControlDataReporting_register();
   DC_PUSDefineDataReporting_register();
   PUSFunctionManagement_register();

   TelecommandLoader_register();
   DC_DummyTelecommandLoader_register();
   DC_BasicPUSTcLoader_register();

   CC_TelecommandManager_register();

   CC_TelecommandFactory_register();
}

