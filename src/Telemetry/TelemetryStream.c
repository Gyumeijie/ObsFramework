//
//
// TelemetryStream.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/Constants.h"
#include "TelemetryStream.h"



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Reset the telemetry stream. The effect of a reset are
 * implementation-specific.
 * This class provides a default implementation that does not take any
 * action.
 */
static void reset(void *obj)
{
}

/**
 * Flush the telemetry stream. The effect of a flush are
 * implementation-specific.
 * This class provides a default implementation that does not take any
 * action.
 * This operation is typically useful when the telemetry stream maintains
 * an internal buffer to which it writes the telemetry data. The <code>flush</code>
 * operation can then be implemented to emtpy the buffer and write its content
 * to a telemetry channel.
 */
static void flush(void *obj)
{
}

/**
 * Return the capacity of the telemetry stream.
 * Some telemetry stream may have a capacity attribute associated to them.
 * This method returns its value.
 * This class provides a default implementation that returns MAX_INT.
 * @see MAX_INT
 * @return the capacity of the telemetry stream
 */
static unsigned int getCapacity(void *obj)
{
    return MAX_INT;
}

/**
 * Check whether there is enough space in the telemetry stream for writing
 * the argument telemetry packet.
 * Some telemetry streams may have a limited capacity.
 * Before performing a write operation, it may therefore be necessary to
 * check whether there is enough space in the
 * telemetry stream for the data that it is desired to write.
 * This operation checks whether there is enough space for writing the
 * content of the argument telemetry packet.
 * This class provides a default implementation that always returns
 * "enough space".
 * @param pTmPacket the telemetry packet to be written to the telemetry stream
 * @return true if there is enough space in the telemetry stream to write
 * n bytes, false otherwise
 */
static bool doesPacketFit(void *obj, TelemetryPacket* pTmPacket)
{
    return true;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Write the content of the telemetry packet to the telemetry stream.
 * @param tmItem the telemetry packet to be written to the telemetry stream
 */
static void write(void *obj, TelemetryPacket* tmItem)
{
    // this is automate genenrated by converter
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj){}

TelemetryStream* TelemetryStream_new(void)
{
    Object *obj = object_new(TYPE_TELEMETRYSTREAM);
    return (TelemetryStream*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    TelemetryStreamClass *tsc = TELEMETRYSTREAM_CLASS(oc);

    tsc->reset = reset;
    tsc->flush = flush;
    tsc->getCapacity = getCapacity;
    tsc->doesPacketFit = doesPacketFit;

    tsc->write = write;
}

static const TypeInfo type_info = {
    .name = TYPE_TELEMETRYSTREAM,
    .parent = TYPE_CC_ROOTOBJECT,
    .instance_size = sizeof(TelemetryStream),
    .abstract = true,
    .class_size = sizeof(TelemetryStreamClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TelemetryStream_register(void)
{
    type_register_static(&type_info);
}
