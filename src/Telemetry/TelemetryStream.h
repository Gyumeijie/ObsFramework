//
//
// TelemetryStream.h
//
//
// Change Record:


#ifndef TELEMETRYSTREAM_H
#define TELEMETRYSTREAM_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "../Qom/object.h"


/*
 * Base class from which all telemetry stream classes are derived.
 * A <i>telemetry stream</i> represents a
 * data sink to which individual <i>telemetry packets</i> can be written.
 * The telemetry packets are assumed to be encapsulated in objects of type
 * <code>TelemetryPacket</code>.
 * This is an abstract class since the mechanism through which the telemetry
 * items are written to a physical telemetry channel vary widely across
 * applications.
 * <p>
 * The basic service provided by this class is implemented by a <code>write</code>
 * operation that takes an instance of type <code>TelemetryPacket</code> as
 * an argument. An application would implement this operation to write the content
 * of the telemetry packet to a physical telemetry channel.
 * Additionally, housekeeping operations are provided to manage the telemetry
 * stream.
 * These operations are designed to be compatible with a wide range of
 * concrete telemetry stream mechanisms.
 * Given the diversity of such mechanisms, this means that the semantics of
 * the operations is only weakly defined in this base class. More specific
 * definitions are left to the sub-classes. There is however one important constraint
 * on the implementations provided by the sub-classes. Some of the methods declared
 * by class <code>TelemetryStream</code> receive as an argument a pointer to the
 * telemetry packet whose content must be written to the telemetry data sink.
 * Telemetry packets are in principle allocated dynamically by a <i>telemetry packet
 * factory</i>. Hence, if the telemetry stream needs to buffer information about the
 * telemetry packet, it should do so by copying its content to an internal buffer. It
 * should <i>not</i> try to store the pointer to the telemetry packet in order to
 * access it at a later time.
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 * @ingroup Telemetry
 */
#define TYPE_TELEMETRYSTREAM "telemetrystream"

void TelemetryStream_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct TelemetryStream {
    CC_RootObject parent;
};


struct TelemetryStreamClass {
    CC_RootObjectClass parent_class;
 
    void (*reset)(void *obj);
    void (*flush)(void *obj);
    unsigned int (*getCapacity)(void *obj);
    bool (*doesPacketFit)(void *obj, TelemetryPacket* pTmPacket);
 
    void (*write)(void *obj, TelemetryPacket* tmItem);
 
};


#define TELEMETRYSTREAM_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TelemetryStreamClass, obj, TYPE_TELEMETRYSTREAM)

#define TELEMETRYSTREAM_CLASS(klass) \
        OBJECT_CLASS_CHECK(TelemetryStreamClass, klass, TYPE_TELEMETRYSTREAM)

#define TELEMETRYSTREAM(obj) \
        OBJECT_CHECK(TelemetryStream, obj, TYPE_TELEMETRYSTREAM)


TelemetryStream* TelemetryStream_new(void);

#endif
