//
//
// DC_BasicPUSTmStream.h
//


#ifndef DC_BASICPUSTMSTREAM_H
#define DC_BASICPUSTMSTREAM_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "TelemetryStream.h"
#include "../Qom/object.h"


/*
 * Telemetry stream that packetizes the telemetry data according to the
 * PUS and writes them to a <i>telemetry write area</i>.
 * This component can write several packets to the telemetry write area 
 * in sequence, up to the point where there is no space left in the
 * telemetry write area. 
 * The telemetry write area is characterized by
 * a <i>starting address</i> and by a <i>size</i>. The starting
 * address and the size are settable configuration parameters.
 * They can be changed dynamically. The first byte of the telemetry write
 * area holds the number of packets that have been written to it since the
 * last time the stream was reset. Following bytes hold the images of the
 * the telemetry packets in the order in which they are written.
 * <p>
 * This component maintains a <i>write counter</i> and a <i>packet counter</i>. 
 * Both counters are reset to 0 by
 * a call to operation <code>reset</code> or <code>flush</code>.
 * The write counter is incremented every
 * time a byte is written to the telemetry write array.
 * If its value is smaller than the size of the telemetry write area, then the
 * write counter points
 * to the location in the write area where the next telemetry data byte
 * will be written. The packet counter is equal to the number of packets
 * that have been written to the telemetry write area since the stream
 * was last reset. The value of the packet counter is the same as the
 * value of the first byte of the telemetry write area.
 * <p>
 * Write requests that cannot be processed because
 * there is not enough space in the telemetry write area have no effect
 * other than the generation of event EVT_TM_STREAM_END.
 * It is the responsibility of the user to perform reset or flush
 * operations when the byte array has been completely filled.
 * <p>
 * This telemetry stream adds the header data to the packet data that it
 * retrieves from the packet itself. The format of the packet header
 * is in accordance with the PUS with the following qualifications: <ul>
 * <li>The data field header flag is always set to 1</li>
 * <li>The APID is read from the telemetry packet through method 
 * <code>getPacketId</code></li>
 * <li>The grouping flags are always set to "11" (stand-alone packet)</li>
 * <li>The packet sub-counter is omitted</li>
 * <li>The packet destination ID field is omitted</li>
 * <li>The time information is read from the telemetry packet. It is written
 * as a value of type <code>TD_ObsTime</code>.</li>
 * <li>The packet error control is set to zero(it is assumed that it is computed
 * downstream when the packet is actually dispatched to its destination)</li>
 * <li>The packet sequence count is initialized to zero when the telemetry stream
 * and is incremented by one(with wrap around) every time a packet is written.</li>
 * </ul>
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_BASICPUSTMSTREAM "dc_basicpustmstream"

void DC_BasicPUSTmStream_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_BasicPUSTmStream {
    TelemetryStream parent;

    unsigned char *tmData;  // the telemetry write area
    unsigned int size;      // the size of the byte array in bytes
    unsigned int writeCounter;
    unsigned short packetSequenceControl;
    unsigned int nAdditionalBytes;   // number of bytes added by this TM stream to 
};


struct DC_BasicPUSTmStreamClass {
    TelemetryStreamClass parent_class;
};


#define DC_BASICPUSTMSTREAM_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_BasicPUSTmStreamClass, obj, TYPE_DC_BASICPUSTMSTREAM)

#define DC_BASICPUSTMSTREAM_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_BasicPUSTmStreamClass, klass, TYPE_DC_BASICPUSTMSTREAM)

#define DC_BASICPUSTMSTREAM(obj) \
        OBJECT_CHECK(DC_BasicPUSTmStream, obj, TYPE_DC_BASICPUSTMSTREAM)


DC_BasicPUSTmStream* DC_BasicPUSTmStream_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the capacity of the telemetry stream. The capacity of this
 * telemetry stream is equal to the size in bytes of the telemetry write
 * area.
 * If s is the staring address of the telemetry write DC_BasicPUSTmStream_area(loaded with method
 * <code>setStartingAddress</code>) and if L is the value loaded with 
 * with this method, then the i-th location of the telemetry write area is
 * internally accessed as s[i] where i must be in the range [0, L-1].
 * It is the responsibility of the user to ensure that the locations thus
 * accessed are free for use by this telemetry stream component.
 * Only positive values for the argument of this method are legal.
 * @see #setStartingAddress
 * @param n the size of the telemetry write area in number of bytes
 */
void DC_BasicPUSTmStream_setCapacity
(
    DC_BasicPUSTmStream *This, 
    unsigned int n
);

/**
 * Set the starting address of the telemetry write area. This component does not
 * perform any memory allocation operation. It assumes that the memory
 * for the telemetry write area has already been allocated by the caller.
 * The telemetry stream is reset when a new start address is
 * loaded.
 * @param pAddress pointer to the first location of the byte array
 */
void DC_BasicPUSTmStream_setStartAddress
(
    DC_BasicPUSTmStream *This, 
    unsigned char *pAddress
);

/**
 * Get the starting address of the telemetry write area.
 * @see #setStartingAddress
 * @return the pointer to the first location of the telemetry write area
 */
unsigned char* DC_BasicPUSTmStream_getStartAddress
(
    const DC_BasicPUSTmStream *This
);

/**
 * Get the current value of the packet counter.
 * @return the packet counter
 */
unsigned int DC_BasicPUSTmStream_getPacketCounter
(
    const DC_BasicPUSTmStream *This
);

/**
 * Get the current value of the write counter.
 * @return the write counter
 */
unsigned int DC_BasicPUSTmStream_getWriteCounter
(
    const DC_BasicPUSTmStream *This
);

/**
 * Get the value of the packet sequence count. This is equal to the number of packets 
 * for which write requests have been made since the telemetry stream component 
 * was instantiated.
 * @return the packet sequence count
 */
unsigned int DC_BasicPUSTmStream_getSequenceCounter
(
    const DC_BasicPUSTmStream *This
);


#endif
