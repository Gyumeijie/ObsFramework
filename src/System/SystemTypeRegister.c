#include "SystemTypeRegister.h"
#include "Tracer.h"
#include "DC_DummyTracer.h"
#include "DC_TestTracer.h"
#include "ObsClock.h"
#include "DC_DummyObsClock.h"

void system_type_register()
{
    Tracer_register();
    DC_DummyTracer_register();
    DC_TestTracer_register();
   
    ObsClock_register();
    DC_DummyObsClock_register();
}

