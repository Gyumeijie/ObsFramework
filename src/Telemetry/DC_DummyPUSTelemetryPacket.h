//
//
// DC_DummyPUSTelemetryPacket.h
//


#ifndef DC_DUMMYPUSTELEMETRYPACKET_H
#define DC_DUMMYPUSTELEMETRYPACKET_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "PUSTelemetryPacket.h"
#include "../Qom/object.h"


/*
 * Dummy implementation of the <code>PUSTelemetryPacket</code> class
 * useful for testing purposes.
 * This telemetry packet encapsulates a single and settable byte. The
 * update service is implemented to increment the value of the byte
 * by one(with a wrap-around to zero when the value of 255 is reached).
 * The values of the telemetry packet attributes are initialized
 * to: <ul>
 * <li>The telemetry packet type is set to TEST_TM_TYPE</li>
 * <li>The telemetry packet subtype is set to TEST_TM_SUBTYPE</li>
 * <li>The telemetry packet time tag is set to TEST_TM_TIMETAG</li>
 * </ul>
 * The constants are defined in file <code>TestConstants.h</code>.
 * Note that the telemetry destination does not need to be set because
 * it is already set to a default value by the constructor of
 * class <code>PUSTelemetryPacket</code>. Similarly, the APID of the process
 * generating the telemetry data does not need to be set because it is
 * a static field that should be set during the test set up process.
 * @see TestConstants
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_DUMMYPUSTELEMETRYPACKET "dc_dummypustelemetrypacket"

void DC_DummyPUSTelemetryPacket_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_DummyPUSTelemetryPacket {
    PUSTelemetryPacket parent;

    unsigned char item;
};


struct DC_DummyPUSTelemetryPacketClass {
    PUSTelemetryPacketClass parent_class;
};


#define DC_DUMMYPUSTELEMETRYPACKET_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_DummyPUSTelemetryPacketClass,\
                                          obj, TYPE_DC_DUMMYPUSTELEMETRYPACKET)

#define DC_DUMMYPUSTELEMETRYPACKET_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_DummyPUSTelemetryPacketClass,\
                                        klass, TYPE_DC_DUMMYPUSTELEMETRYPACKET)

#define DC_DUMMYPUSTELEMETRYPACKET(obj) \
        OBJECT_CHECK(DC_DummyPUSTelemetryPacket,\
                                          obj, TYPE_DC_DUMMYPUSTELEMETRYPACKET)


DC_DummyPUSTelemetryPacket* DC_DummyPUSTelemetryPacket_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the value of the encapsulated byte. This is the value returned by
 * method <code>getUnsignedByteUnchecked</code>.
 * @see #getUnsignedByteUnchecked
 * @param value the value of the encapsulated byte
 */
void DC_DummyPUSTelemetryPacket_setValue
(
    DC_DummyPUSTelemetryPacket *This, 
    unsigned char value
);


#endif
