//
//
// TelemetryPacket.h
//


#ifndef TELEMETRYPACKET_H
#define TELEMETRYPACKET_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "../Qom/object.h"


/*
 * Base class from which all telemetry packet classes are derived.
 * The <i>Telemetry Item</i> concept is implemented here to represent a group
 * of ordered bytes that
 * are intended to be sent to the telemetry stream and that constitute one
 * single logical unit in the sense that they are collected together.
 * This group of ordered bytes is referred to in what follows as the
 * <i>telemetry bytes</i>.
 * <p>
 * This class defines five attributes, two services, and one check.
 * The attributes allow the telemetry bytes to be characterized. They are: <ul>
 * <li>The <i>telemetry packet type</i>: this attribute defines the type of the telemetry
 * item. </li>
 * <li>The <i>telemetry packet subtype</i>: this attribute defines the subtype of the
 * telemetry packet. It is useful where the type attribute does not provide sufficient
 * granularity to characterize the telemetry packet type.</li>
 * <li>The <i>destination</i>: this attribute defines the destination of the telemetry bytes.</li>
 * <li>The <i>time tag</i>: this attribute represents a time stamp for the telemetry bytes.</li>
 * <li>The <i>in use flag</i>: this is a toggle attribute that can have two values:
 * "packet is in use" and "packet is not in use". This attribute
 * is useful when telemetry packets need to be allocated dynamically. The "in use" attribute can then
 * be used to discriminate between packets that are already allocated and
 * packets that are still free. </li>
 * </ul>
 * The two services defined by this class are: <ul>
 * <li>The <i>data update service</i> is used by a client to direct the telemetry
 * item component to update the
 * internal information that it uses to construct the telemetry bytes.</li>
 * <li>The <i>data acquisition service</i> is used by a client to format and acquire
 * the most recently updated telemetry bytes.</li>
 * </ul>
 * Finally, the check defined by this class is the
 * <i>validity check</i>. This service allows a client to ask a telemetry packet
 * component to verify that the most recently updated information is valid.
 * <p>
 * Two implementations of the data acquisition service are provided: a <i>safe implementation</i>
 * and a <i>fast implementation</i>. The safe implementation is built upon methods
 * <code>getUnsignedByte</code> and <code>getNumberOfBytes</code>. It allows the
 * most recently acquired telemetry bytes to be transfered one by one to the caller.
 * This implementation is safe because it complies with all coding rules defined for
 * the OBS Framework. However, it may not be fast because the transfer of each byte
 * requires a call to a virtual method. The alternative implementation is built on
 * methods <code>getStartAddress</code> and <code>getNumberOfBytes</code>. The former
 * method returns a pointer to the internal data area where the telemetry bytes are
 * stored. The latter returns the number of telemetry bytes. This implementation is
 * fast because the caller can copy the telemetry bytes using a fast memory copy 
 * algorithm. It is potentially unsafe because it gives the caller access to an
 * internal data structure of the telemetry packet component. The safe implementation
 * of the data update service must always be provided by all concrete subclasses.
 * The fast version may be provided by subclasses that manage large amounts of 
 * telemetry data. Method <code>isFastAcquisitionImplemented</code> is provided to
 * allow a caller to check whether the fast implementation is provided.
 * The fast version of the data acquisition service should be used only when
 * necessary for performance reasons. By default, the safe version should be used.
 * <p>
 * Telemetry item instances are intended to be used by a component that collects
 * telemetry data
 * and forwards them to a telemetry channel(in the OBS Framework, this telemetry
 * data collecting component is the <i>telemetry manager</i> instantiated from class
 * <code>CC_TelemetryManager</code>). The telemetry packet class assumes that the
 * collection of the telemetry data from one of its instances
 * is performed in three steps as follows:<ol>
 * <li>The data update service is called</li>
 * <li>The validity check is performed on the newly updated data</li>
 * <li>The data acquisition service is called to acquire the telemetry data</li>
 * </ol>
 * This class does not make any assumptions about the data structure that
 * is used internally to store the telemetry bytes.
 * It is an abstract class that is intended to provide a general interface
 * capable of modeling telemetry packet concepts
 * of varying complexity but it only provides minimal default implementations for
 * its attributes, services and for the validity check.
 * Applications should provide subclasses that implement their particular
 * telemetry concept.
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 * @ingroup Telemetry
 */
#define TYPE_TELEMETRYPACKET "telemetrypacket"

void TelemetryPacket_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct TelemetryPacket {
    CC_RootObject parent;

    bool inUse;
};


struct TelemetryPacketClass {
    CC_RootObjectClass parent_class;
 
    void (*setType)(void *obj, TD_TelemetryType tmType);
    void (*setSubType)(void *obj, TD_TelemetrySubType tmSubType);
    void (*setTimeTag)(void *obj, TD_ObsTime timeTag);
    void (*setDestination)(void *obj, TD_TelemetryDestination tmDest);
    bool (*isValid)(void *obj);
    unsigned char* (*getStartAddress)(void *obj);
    bool (*isFastAcquisitionImplemented)(void *obj);
    TD_TelemetryType (*getType)(const void *obj);
    TD_TelemetrySubType (*getSubType)(const void *obj);
    TD_ObsTime (*getTimeTag)(const void *obj);
    TD_TelemetryDestination (*getDestination)(const void *obj);
 
    unsigned int (*getNumberOfBytes)(void *obj);
    void (*update)(void *obj);
    unsigned char (*getUnsignedByte)(void *obj, unsigned int n);
 
};


#define TELEMETRYPACKET_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TelemetryPacketClass, obj, TYPE_TELEMETRYPACKET)

#define TELEMETRYPACKET_CLASS(klass) \
        OBJECT_CLASS_CHECK(TelemetryPacketClass, klass, TYPE_TELEMETRYPACKET)

#define TELEMETRYPACKET(obj) \
        OBJECT_CHECK(TelemetryPacket, obj, TYPE_TELEMETRYPACKET)


TelemetryPacket* TelemetryPacket_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the value of the "in use" attribute.
 * @see #isInUse
 * @param newInUse the new value of the in use attribute
 */
void TelemetryPacket_setInUse(TelemetryPacket *This, bool newInUse);

/**
 * Return the value of the "in use" attribute. If the method returns true, then
 * the packet is already in use, otherwise it is free and can be configured.
 * @see #setInUse
 * @return the value of the "in use" attribute.
 */
bool TelemetryPacket_isInUse(const TelemetryPacket *This);


#endif
