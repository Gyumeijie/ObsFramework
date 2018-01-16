#include "TelemetryTypeRegister.h"
#include "TelemetryPacket.h"
#include "DC_DummyTelemetryPacket.h"
#include "PUSTelemetryPacket.h"
#include "DC_DummyPUSTelemetryPacket.h"
#include "PUSMemoryDump.h"
#include "DC_PUSMemoryDumpOffset.h"

void telemetry_type_register(void)
{
    TelemetryPacket_register();
    DC_DummyTelemetryPacket_register();
    PUSTelemetryPacket_register();
    DC_DummyPUSTelemetryPacket_register();
    PUSMemoryDump_register();
    DC_PUSMemoryDumpOffset_register();
}
