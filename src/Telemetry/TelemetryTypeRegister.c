#include "TelemetryTypeRegister.h"
#include "TelemetryPacket.h"
#include "DC_DummyTelemetryPacket.h"


void telemetry_type_register(void)
{
    TelemetryPacket_register();
    DC_DummyTelemetryPacket_register();
}
