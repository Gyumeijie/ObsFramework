//
//
// PUSTelemetryPacket.h
//


#ifndef PUSTELEMETRYPACKET_H
#define PUSTELEMETRYPACKET_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Telemetry/TelemetryPacket.h"
#include "../Qom/object.h"


/*
 * Base class from which all PUS telemetry packet classes are derived.
 * A PUS telemetry packet class encapsulate a packet of telemetry data
 * that is compliant with the Packet Utilization Stadard(PUS). PUS
 * telemetry packet classes are organized as <i>telemetry packets</i> in the
 * sense that this class extends class <code>TelemetryPacket</code>. Class
 * <code>TelemetryPacket</code> defines a <i>data acquisition service</i> to
 * acquire a stream of telemetry bytes. From the point of view of the
 * <code>PUSTelemetryPacket</code> class, this stream of bytes represent
 * the source data part of the PUS packet encapsulated by the class.
 * The mapping between the attributes defined by the <code>TelemetryPacket</code> superclass
 * and the attributes mandated by the PUS is as follows:<ul>
 * <li>The <i>packet ID</i> PUS attribute has a fixed value for all telemetry packet
 * originating from the same
 * application process and it is therefore implemented as a static attribute.</li>
 * <li>The <i>service type</i> PUS attribute is mapped to the <i>telemetry packet
 * type</i> attribute of the <code>TelemetryPacket</code> class.</li>
 * <li>The <i>service subtype</i> PUS attribute is mapped to the <i>telemetry packet
 * subtype</i> attribute of the <code>TelemetryPacket</code> class.</li>
 * <li>The <i>destination</i> PUS attribute is mapped to the <i>telemetry packet
 * destination</i> attribute of the <code>TelemetryPacket</code> class.</li>
 * <li>The <i>time</i> PUS attribute is mapped to the <i>telemetry packet
 * time tag</i> attribute of the <code>TelemetryPacket</code> class.</li>
 * </ul>
 * Since most telemetry packets in an application can be expected to have the
 * same destination, this class also defines a static <i>default destination</i>
 * attribute.
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 * @ingroup PUS
 * @ingroup Telemetry
 */
#define TYPE_PUSTELEMETRYPACKET "pustelemetrypacket"

void PUSTelemetryPacket_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct PUSTelemetryPacket {
    TelemetryPacket parent;

    TD_TelemetryType type;
    TD_TelemetrySubType subType;
    TD_TelemetryDestination dest;
    TD_ObsTime timeTag;
};


struct PUSTelemetryPacketClass {
    TelemetryPacketClass parent_class;
};


#define PUSTELEMETRYPACKET_GET_CLASS(obj) \
        OBJECT_GET_CLASS(PUSTelemetryPacketClass, obj, TYPE_PUSTELEMETRYPACKET)

#define PUSTELEMETRYPACKET_CLASS(klass) \
        OBJECT_CLASS_CHECK(PUSTelemetryPacketClass, klass, TYPE_PUSTELEMETRYPACKET)

#define PUSTELEMETRYPACKET(obj) \
        OBJECT_CHECK(PUSTelemetryPacket, obj, TYPE_PUSTELEMETRYPACKET)


PUSTelemetryPacket* PUSTelemetryPacket_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Setter method for the application PUSTelemetryPacket_identifier(APID). The APID is used to construct
 * the telemetry packet identifier. The APID is placed in the 11 least-significant bits
 * of the PUS packet identifier. A pseudo-code implementation for this method is as
 * follows: <pre>
 *      packetId = 2**11;           // set the fixed part of the packet ID
 *      packetId = packetId + apid; // set the APID part of the packet ID </pre>
 * The APID should be smaller than 2**11.
 * @see getPacketId
 * @param apid the identifier of the application generating the telemetry packet
 */
void PUSTelemetryPacket_setApplicationId(TD_APID apid);

/**
 * Getter method for the telemetry packet identifier. The telemetry packet
 * identifier is assumed to be fixed for all telemetry packets in the same
 * application process. According to the PUS, the packet identifier consists
 * of the following four fields: <ul>
 * <li>The version number: this field is fixed and equal to 0</li>
 * <li>The type: this field is fixed and equal to 0</li>
 * <li>The data field header: this field is fixed and equal to 1 (indicating
 * that a telemetry packet always has a secondary header)</li>
 * <li>The application ID: this field is fixed within the application process and
 * it is equal to the application identifier</li>
 * </ul>
 * @see #setApplicationId
 * @return the packet identifier
 */
TD_PUSPacketId PUSTelemetryPacket_getPacketId(void);

/**
 * Getter method for the telemetry packet default destination.
 * @return the telemetry packet default destination
 */
TD_TelemetryDestination PUSTelemetryPacket_getDefaultDestination(void);

/**
 * Setter method for the telemetry packet default destination.
 * @param defDest the telemetry packet default destination
 */
void PUSTelemetryPacket_setDefaultDestination(TD_TelemetryDestination defDest);

/**
 * Load the OBS Clock component. Telemetry packets may need access to
 * this component in order to time-stamp the telemetry data as they are collected.
 * @param pObsClock the OBS Clock component.
 */
void PUSTelemetryPacket_setObsClock(ObsClock *pObsClock);

/**
 * Return the OBS Clock component.
 * @see #setObsClock
 * @return the OBS Clock component.
 */
ObsClock* PUSTelemetryPacket_getObsClock(void);


#endif
