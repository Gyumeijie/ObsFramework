#include "TelemetryTypeRegister.h"
#include "TelemetryPacket.h"
#include "DC_DummyTelemetryPacket.h"
#include "PUSTelemetryPacket.h"
#include "DC_PUSTcVerificationPacket.h"
#include "DC_DummyPUSTelemetryPacket.h"
#include "DC_PUSDataReportingPacket.h"
#include "PUSMemoryDump.h"
#include "DC_PUSMemoryDumpOffset.h"
#include "DC_PUSMemoryDumpAbsolute.h"
#include "StructuredTelemetryPacket.h"
#include "DC_DataItem16TmWord.h"
#include "TelemetryStream.h"
#include "DC_ByteArrayTelemetryStream.h"
#include "DC_DummyTelemetryStream.h" 
#include "DC_CycleDataItem16TmStream.h" 
#include "DC_FileTelemetryStream.h"
#include "DC_PUSTmLogger.h"
#include "TelemetryModeManager.h"
#include "TelemetryListModeManager.h"
#include "DC_SimpleTelemetryModeManager.h"
#include "DC_CyclingTelemetryModeManager.h"
#include "CC_TelemetryManager.h" 
#include "DC_BasicPUSTmStream.h"
#include "CC_TelemetryPacketFactory.h"
#include "DC_PUSTelemetryModeManager.h"

void telemetry_type_register(void)
{
    TelemetryPacket_register();
    DC_DummyTelemetryPacket_register();
    PUSTelemetryPacket_register();
    DC_PUSTcVerificationPacket_register();
    DC_PUSDataReportingPacket_register();
    DC_DummyPUSTelemetryPacket_register();
    PUSMemoryDump_register();
    DC_PUSMemoryDumpOffset_register();
    DC_PUSMemoryDumpAbsolute_register();
    StructuredTelemetryPacket_register();
    DC_DataItem16TmWord_register();

    TelemetryStream_register(); 
    DC_ByteArrayTelemetryStream_register();
    DC_DummyTelemetryStream_register();
    DC_CycleDataItem16TmStream_register();
    DC_FileTelemetryStream_register();
    DC_PUSTmLogger_register();
    DC_BasicPUSTmStream_register();

    TelemetryModeManager_register();
    TelemetryListModeManager_register();
    DC_SimpleTelemetryModeManager_register();
    DC_CyclingTelemetryModeManager_register();
    DC_PUSTelemetryModeManager_register();

    CC_TelemetryManager_register();

    CC_TelemetryPacketFactory_register();

}
