//
//
// DC_DummyTelemetryStream.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "DC_DummyTelemetryStream.h"



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Write the content of the telemetry packet to the telemetry stream. This
 * implementation does nothing.
 * @param tmItem the telemetry packet to be written to the telemetry stream
 */
static void write(void *obj, TelemetryPacket *tmItem)
{
    return;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    CC_RootObject_setClassId((CC_RootObject*)obj, ID_DUMMYTELEMETRYSTREAM);
}

DC_DummyTelemetryStream* DC_DummyTelemetryStream_new(void)
{
    Object *obj = object_new(TYPE_DC_DUMMYTELEMETRYSTREAM);
    return (DC_DummyTelemetryStream*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    TelemetryStreamClass *tsc = TELEMETRYSTREAM_CLASS(oc);
    tsc->write = write;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_DUMMYTELEMETRYSTREAM,
    .parent = TYPE_TELEMETRYSTREAM,
    .instance_size = sizeof(DC_DummyTelemetryStream),
    .abstract = false,
    .class_size = sizeof(DC_DummyTelemetryStreamClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_DummyTelemetryStream_register(void)
{
    type_register_static(&type_info);
}
