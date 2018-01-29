//
//
// DC_DummyTelemetryPacket.h
//


#ifndef DC_DUMMYTELEMETRYPACKET_H
#define DC_DUMMYTELEMETRYPACKET_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "TelemetryPacket.h"
#include "../Qom/object.h"


/*
 * Dummy implementation of the <code>TelemetryPacket</code> interface
 * useful for testing purposes.
 * This telemetry packet encapsulates N settable bytes. The value of N
 * is a configuration parameter. The
 * update service is implemented to increment the value of each telemetry byte
 * by one(with a wrap-around to zero when the value of 255 is reached).
 * The <i>validity check</i> can be dynamically set up to return
 * either "data valid" or "data not valid".
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_DUMMYTELEMETRYPACKET "dc_dummytelemetrypacket"

void DC_DummyTelemetryPacket_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_DummyTelemetryPacket {
    TelemetryPacket parent;

    unsigned int nOfBytes;
    unsigned char *item;
    bool validStatus;
};


struct DC_DummyTelemetryPacketClass {
    TelemetryPacketClass parent_class;
};


#define DC_DUMMYTELEMETRYPACKET_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_DummyTelemetryPacketClass,\
                                              obj, TYPE_DC_DUMMYTELEMETRYPACKET)

#define DC_DUMMYTELEMETRYPACKET_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_DummyTelemetryPacketClass,\
                                            klass, TYPE_DC_DUMMYTELEMETRYPACKET)

#define DC_DUMMYTELEMETRYPACKET(obj) \
        OBJECT_CHECK(DC_DummyTelemetryPacket, obj, TYPE_DC_DUMMYTELEMETRYPACKET) 

DC_DummyTelemetryPacket* DC_DummyTelemetryPacket_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the validity status. This is the value returned by the validity check
 * (method <code>isValid</code>.
 * @see #isValid
 * @param validStatus the validity status
 */
void DC_DummyTelemetryPacket_setValidStatus
(
    DC_DummyTelemetryPacket *This, 
    bool validStatus
);

/**
 * Set the value of the n-th encapsulated byte. This is the value returned by
 * method <code>getUnsignedByteUnchecked</code>. The value of n must lie in
 * the range [0, N-1] where N is the total number of telemetry bytes
 * encapsulated in the telemetry packet. Calls with out-of-range values of n
 * have no effect.
 * @see #getUnsignedByteUnchecked
 * @param value the value of the encapsulated byte
 * @param n the index of the encapsulated byte
 */
void DC_DummyTelemetryPacket_setValue
(
    DC_DummyTelemetryPacket *This, 
    unsigned int n,
    unsigned char value
);

/**
 * Set the number of bytes encapsulated by this telemetry packet.
 * This is an initialization method. It should only be called once.
 * Only positive values of the argument n are legal.
 * The telemetry bytes are initialized to zero.
 * @see #getUnsignedByteUnchecked
 * @param n the number of bytes encapsulated in this telemetry packet
 */
void DC_DummyTelemetryPacket_setNumberOfBytes
(
    DC_DummyTelemetryPacket *This, 
    unsigned int n
);


#endif
