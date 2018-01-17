#include "TelemetryTypeRegister.h"
#include "TelemetryPacket.h"
#include "DC_DummyTelemetryPacket.h"
#include "PUSTelemetryPacket.h"
#include "DC_DummyPUSTelemetryPacket.h"
#include "PUSMemoryDump.h"
#include "DC_PUSMemoryDumpOffset.h"
#include "DC_PUSMemoryDumpAbsolute.h"
#include "StructuredTelemetryPacket.h"
#include "DC_DataItem16TmWord.h"

void telemetry_type_register(void)
{
    TelemetryPacket_register();
    DC_DummyTelemetryPacket_register();
    PUSTelemetryPacket_register();
    DC_DummyPUSTelemetryPacket_register();
    PUSMemoryDump_register();
    DC_PUSMemoryDumpOffset_register();
    DC_PUSMemoryDumpAbsolute_register();
    StructuredTelemetryPacket_register();
    DC_DataItem16TmWord_register();
}
