//
//
// TelemetryPacket.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "TelemetryPacket.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void TelemetryPacket_setInUse(TelemetryPacket *This, bool newInUse)
{
    This->inUse = newInUse;
}

bool TelemetryPacket_isInUse(const TelemetryPacket *This)
{
    return This->inUse;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Setter method for the telemetry packet type. Since this class
 * identifies the telemetry packet type with the class identifier
 * (see <code>CC_RootObject</code>), this method is implemented as
 * a dummy method that returns without taking any action.
 * @see #getType
 * @param tmType the telemetry packet type
 */
static void setType(void *obj, TD_TelemetryType tmType)
{
    return;
}

/**
 * Setter method for the telemetry packet sub-type. Since this class
 * does not model the telemetry packet sub-type, this method is implemented as
 * a dummy method that returns without taking any action.
 * @see #getSubType
 * @param tmSubType the telemetry packet sub-type
 */
static void setSubType(void *obj, TD_TelemetrySubType tmSubType)
{
    return;
}

/**
 * Setter method for the telemetry packet time tag. Since this class
 * does not model the telemetry packet time tag, this method is implemented as
 * a dummy method that returns without taking any action.
 * @see #getTimeTag
 * @param timeTag the telemetry packet time tag
 */
static void setTimeTag(void *obj, TD_ObsTime timeTag)
{
    return;
}

/**
 * Setter method for the telemetry packet destination. Since this class
 * does not model the telemetry packet destination, this method is implemented as
 * a dummy method that returns without taking any action.
 * @see #getDestination
 * @param tmDest telemetry packet destination
 */
static void setDestination(void *obj, TD_TelemetryDestination tmDest)
{
    return;
}

/**
 * Execute the <i>validity check</i> on the most recently updated
 * telemetry bytes.
 * This class provides a default implementation that always return "data
 * valid".
 * @see #update
 * @return true if the most recently updated telemetry bytes are valid, 
 * false otherwise
 */
static bool isValid(void *obj)
{
	return VALID;
}

/**
 * Implement the fast version of the <i>data acquisition service</i>.
 * If this version of the service is implemented, then this method returns
 * a pointer to start address of an internal data structure that holds all
 * telemetry data as a linear sequence of bytes. The size of the internal
 * data structure is given by method <code>getNumberOfBytes</code>).
 * This method only has a meaningful implementation if the fast version of the
 * data acquisition service is provided. This is the case if method
 * <code>isFastAcquisitionImplemented</code> returns a value of <code>true</code>.
 * If this is not the case, this method should return a null pointer.
 * This class provideds a default implementation that returns a null
 * pointer.
 * @return a null pointer
 */
static unsigned char* getStartAddress(void *obj)
{
    return pNULL;
}

/**
 * Return <code>true</code> if the fast version of the data acquisition
 * service is implemented. This class provides a default implementation
 * that returns <code>false</code>.
 * @see #getStartAddress
 * @return <code>true</code> if the fast version of the data acquisition
 * service is implemented
 */
static bool isFastAcquisitionImplemented(void *obj)
{
    return false;
}

/**
 * Getter method for the telemetry packet type. This class implements the
 * the type to coincide with the lest significant byte of the class identifier.
 * A pseudo-code implementation of this method therefore is:<pre>
 *      return(TD_TelemetryType)(getClassId(void)%256);</pre>
 * The modulo operation ensures that there is no overflow even if there is a
 * type mismatch between type <code>TD_TelemetryType</code> the type of the
 * type of the class identifier.
 * @return the telemetry packet type
 */
static TD_TelemetryType getType(const void *obj)
{
    return (TD_TelemetryType)(CC_RootObject_getClassId(obj)%256);
}

/**
 * Getter method for the telemetry sub-type. This class does not model
 * the telemetry sub-type. This method always returns zero.
 * @return the telemetry sub-type
 */
static TD_TelemetrySubType getSubType(const void *obj)
{
    return 0;
}

/**
 * Getter method for the telemetry packet time tag. This class does not model
 * the telemetry packet time tag. This method always returns zero.
 * @return the telemetry packet time
 */
static TD_ObsTime getTimeTag(const void *obj)
{
    return 0;
}

/**
 * Getter method for the telemetry packet destination. This class does not model
 * the telemetry packet destination. This method always returns zero.
 * @return the telemetry packet destination
 */
static TD_TelemetryDestination getDestination(const void *obj)
{
    return 0;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Return the number of bytes managed by this telemetry packet.
 * Each telemetry packet is responsible for generating a fixed number of
 * telemetry bytes. This method returns this fixed number.
 * <p>
 * @return number of bytes in this telemetry packet
 */
static unsigned int getNumberOfBytes(void *obj)
{
    // this is automate genenrated by converter
}

/**
 * Implement the <i>data update service</i>.
 * A call to this method should normally be followed by a call to method
 * <CODE>isValid</CODE> to verify the validity of the newly updated data.
 */
static void update(void *obj)
{
    // this is automate genenrated by converter
}

/**
 * Implement the safe version of the <i>data acquisition service</i>.
 * The telemetry data provided by this class are treated as a sequence
 * of bytes.
 * The method returns the n-th telemetry byte.
 * The parameter n must lie in the interval [0, N-1] where N is the
 * number of telemetry bytes(the return value
 * of method <CODE>getNumberOfBytes</CODE>).
 * @return value of n-th telemetry byte
 * @param n the telemetry byte to be returned(starting with byte 0)
 */
static unsigned char getUnsignedByte(void *obj, unsigned int n)
{
    // this is automate genenrated by converter
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    TelemetryPacket *This = TELEMETRYPACKET(obj);
    This->inUse = false;
}

TelemetryPacket* TelemetryPacket_new(void)
{
    Object *obj = object_new(TYPE_TELEMETRYPACKET);
    return (TelemetryPacket*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    TelemetryPacketClass *tpc = TELEMETRYPACKET_CLASS(oc);

    tpc->setType = setType;
    tpc->setSubType = setSubType;
    tpc->setTimeTag = setTimeTag;
    tpc->setDestination = setDestination;
    tpc->isValid = isValid;
    tpc->getStartAddress = getStartAddress;
    tpc->isFastAcquisitionImplemented = isFastAcquisitionImplemented;
    tpc->getType = getType;
    tpc->getSubType = getSubType;
    tpc->getTimeTag = getTimeTag;
    tpc->getDestination = getDestination;

    tpc->getNumberOfBytes = getNumberOfBytes;
    tpc->update = update;
    tpc->getUnsignedByte = getUnsignedByte;
}

static const TypeInfo type_info = {
    .name = TYPE_TELEMETRYPACKET,
    .parent = TYPE_CC_ROOTOBJECT,
    .instance_size = sizeof(TelemetryPacket),
    .abstract = true,
    .class_size = sizeof(TelemetryPacketClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TelemetryPacket_register(void)
{
    type_register_static(&type_info);
}
