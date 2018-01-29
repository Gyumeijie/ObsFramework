//
//
// DC_PUSTmLogger.h
//


#ifndef DC_PUSTMLOGGER_H
#define DC_PUSTMLOGGER_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "TelemetryStream.h"
#include "../Qom/object.h"


/*
 * <i>Telemetry logger stream</i> that logs all telemetry packets in an internal
 * data structure and offers methods to inspect their content. 
 * This class defines a <i>telemetry buffer</i> where telemetry
 * packets are stored as they are written to the telemetry stream.
 * The telemetry buffer is organized as a circular buffer.
 * When the end of the buffer is reached, its first entry is overwritten.
 * This class must be configured by specifying the capacity of the
 * buffer and the maximum length(in bytes) of the application data
 * of the telemetry packets to be stored in the buffer.
 * This class is intended to be used for testing purposes only.
 * <p>
 * This telemetry stream writes the following data to the telemery
 * buffer for each telemetry packet: <ul>
 * <li>The application data read from the telemetry packet.</li>
 * <li>The number of bytes in the application data.</li>
 * <li>The type of the telemetry packet.</li>
 * <li>The subtype of the telemetry packet.</li>
 * <li>The packet time tag as read from the telemetry packet. </li>
 * </ul>
 * Each of the above items can be separately accessed through dedicated
 * getter methods. 
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_PUSTMLOGGER "dc_pustmlogger"

void DC_PUSTmLogger_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TmPacket {
    TD_TelemetryType type;
    TD_TelemetrySubType subType;
    TD_ObsTime timeTag;
    unsigned char *data;
    unsigned int nData;
} TmPacket;

struct DC_PUSTmLogger {
    TelemetryStream parent;

    TmPacket *tmBuffer;
    unsigned int maxData;
    unsigned int counter;
    unsigned int capacity;
};


struct DC_PUSTmLoggerClass {
    TelemetryStreamClass parent_class;
};


#define DC_PUSTMLOGGER_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_PUSTmLoggerClass, obj, TYPE_DC_PUSTMLOGGER)

#define DC_PUSTMLOGGER_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_PUSTmLoggerClass, klass, TYPE_DC_PUSTMLOGGER)

#define DC_PUSTMLOGGER(obj) \
        OBJECT_CHECK(DC_PUSTmLogger, obj, TYPE_DC_PUSTMLOGGER)


DC_PUSTmLogger* DC_PUSTmLogger_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the capacity of the telemetry buffer. 
 * The capacity of the telemetry buffer is the maximum number of
 * telemetry packets that can be written to the buffer without
 * overwriting any existing packet. This is an initialization
 * method that should only be called once. 
 * Only positive values for the argument of this method are legal.
 * @param n the capacity of the telemetry buffer
 */
void DC_PUSTmLogger_setBufferCapacity(DC_PUSTmLogger *This, unsigned int n);

/**
 * Return the capacity of the telemetry buffer. 
 * @see #setBufferCapacity
 * @return the capacity of the telemetry buffer
 */
unsigned int DC_PUSTmLogger_getBufferCapacity(const DC_PUSTmLogger *This);

/**
 * Set the maximum DC_PUSTmLogger_length(in number of bytes) of the application
 * of the telemetry packets. This is an initialization
 * method that should only be called once. 
 * Only positive values for the argument of this method are legal.
 * @param n the maximum length of the telemetry packet application data
 */
void DC_PUSTmLogger_setMaxPacketLength(DC_PUSTmLogger *This, unsigned int n);

/**
 * Return the capacity of the telemetry buffer. 
 * @see #setBufferCapacity
 * @return the capacity of the telemetry buffer
 */
unsigned int DC_PUSTmLogger_getMaxPacketLength(const DC_PUSTmLogger *This);

/**
 * Get the number of packets that have been written to the telemetry
 * logger so far.
 * @return the number of packets written so far
 */
unsigned int DC_PUSTmLogger_getPacketCounter(const DC_PUSTmLogger *This);

/**
 * Get the type of the i-th packet before the last in the telemetry
 * buffer. If N is the number of packets to have been written so far 
 * to the telemetry logger stream, then this method returns the type
 * of DC_PUSTmLogger_the(N-i)-th packet to have been written to the logger.
 * The value of i should be smaller than the capacity of the telemetry 
 * buffer. If this is not the case, then a value of zero is returned.
 * @param i the packet index
 * @return the packet type
 */
TD_TelemetryType DC_PUSTmLogger_getType
(
   const DC_PUSTmLogger *This, 
   unsigned int i
);

/**
 * Get the subtype of the i-th packet before the last in the telemetry
 * buffer. The way the argument i is interpreted is the same as for 
 * method <code>getType</code>.
 * @see #getType
 * @param i the packet index
 * @return the packet sub type
 */
TD_TelemetrySubType DC_PUSTmLogger_getSubType
(
    const DC_PUSTmLogger *This,
    unsigned int i
);

/**
 * Get the time tag of the i-th packet before the last in the telemetry
 * buffer. The way the argument i is interpreted is the same as for 
 * method <code>getType</code>.
 * @see #getType
 * @param i the packet index
 * @return the packet time tag
 */
TD_ObsTime DC_PUSTmLogger_getTimeTag
(
    const DC_PUSTmLogger *This, 
    unsigned int i
);

/**
 * Get the DC_PUSTmLogger_length(number of bytes in the application data) of the 
 * i-th packet before the last in the telemetry
 * buffer. The way the argument i is interpreted is the same as for 
 * method <code>getType</code>.
 * @see #getType
 * @param i the packet index
 * @return the packet length
 */
unsigned int DC_PUSTmLogger_getLength
(
    const DC_PUSTmLogger *This,
    unsigned int i
);

/**
 * Get the j-th application data byte of the 
 * i-th packet before the last in the telemetry
 * buffer. The way the argument i is interpreted is the same as for 
 * method <code>getType</code>. The argument j must lie in the range
 * [0, L-1] where L is the length of the i-th DC_PUSTmLogger_packet(as returned 
 * by method <code>getLength</code>).
 * @see #getType
 * @param i the packet index
 * @param j the byte index
 * @return the application data byte
 */
unsigned char DC_PUSTmLogger_getData
(
    const DC_PUSTmLogger *This, 
    unsigned int i,
    unsigned int j
);


#endif
