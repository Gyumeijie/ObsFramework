//
//
// DC_ByteArrayTelemetryStream.h
//


#ifndef DC_BYTEARRAYTELEMETRYSTREAM_H
#define DC_BYTEARRAYTELEMETRYSTREAM_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Data/DC_DataItem.h"
#include "TelemetryStream.h"
#include "../Qom/object.h"


/*
 * Telemetry stream that writes the telemetry data to an array of
 * bytes(the <i>byte array</i>). Only the telemetry bytes in the telemetry
 * item are written to the stream. Header information(the telemetry packet
 * destination, time tag, type and subtype) are ignored. The byte array is characterized by
 * a <i>starting address</i> and by a <i>size</i>. The starting
 * address and the size are settable configuration parameters.
 * <p>
 * This class maintains a <i>write counter</i>. The write counter
 * is reset to 0 by
 * a call to operation <code>reset</code> or <code>flush</code>.
 * It is incremented every
 * time a byte is written to the byte array.
 * If its value is smaller than the size of the byte array, then the
 * write counter points
 * to the location in the byte array where the next telemetry data
 * will be written. Write requests that cannot be processed because
 * there is not enough space in the byte array have no effect.
 * It is the responsibility of the user to perform reset or flush
 * operations when the byte array has been completely filled.
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_BYTEARRAYTELEMETRYSTREAM "dc_bytearraytelemetrystream"

void DC_ByteArrayTelemetryStream_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_ByteArrayTelemetryStream {
    TelemetryStream parent;

    unsigned char *tmData;    // the byte array
    unsigned int size;        // the size of the byte array in bytes
    unsigned int writeCounter;
};


struct DC_ByteArrayTelemetryStreamClass {
    TelemetryStreamClass parent_class;
};


#define DC_BYTEARRAYTELEMETRYSTREAM_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_ByteArrayTelemetryStreamClass, \
                                         obj, TYPE_DC_BYTEARRAYTELEMETRYSTREAM)

#define DC_BYTEARRAYTELEMETRYSTREAM_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_ByteArrayTelemetryStreamClass, \
                                       klass, TYPE_DC_BYTEARRAYTELEMETRYSTREAM)

#define DC_BYTEARRAYTELEMETRYSTREAM(obj) \
        OBJECT_CHECK(DC_ByteArrayTelemetryStream, \
                                         obj, TYPE_DC_BYTEARRAYTELEMETRYSTREAM)


DC_ByteArrayTelemetryStream* DC_ByteArrayTelemetryStream_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the capacity of the telemetry stream. The capacity of this
 * telemetry stream is equal to the size in bytes of the byte array.
 * If s is the staring address of the byte DC_ByteArrayTelemetryStream_array(loaded with method
 * <code>setStartingAddress</code>) and if L is the byte array size
 * defined with this method, then the i-th location of the byte array is
 * internally accessed as s[i] where i must be in the range [0, L-1].
 * It is the responsibility of the user to ensure that the locations thus
 * accessed are free for use by this telemetry stream component.
 * Note that the size of the byte array should be greater than 0.
 * @see #setStartingAddress
 * @param n the size of the byte array in number of bytes
 */
void DC_ByteArrayTelemetryStream_setCapacity
(
    DC_ByteArrayTelemetryStream *This, 
    unsigned int n
);

/**
 * Set the starting address of the byte array. This component does not
 * perform any memory allocation operation. It assumes that the memory
 * for the byte array has already been allocated by the caller of this
 * method.
 * @param pAddress pointer to the first location of the byte array
 */
void DC_ByteArrayTelemetryStream_setStartingAddress
(
    DC_ByteArrayTelemetryStream *This, 
    unsigned char *pAddress
);

/**
 * Get the starting address of the byte array.
 * @return the pointer to the first location of the byte array
 */
unsigned char* DC_ByteArrayTelemetryStream_getStartingAddress
(
    const DC_ByteArrayTelemetryStream *This
);


#endif
