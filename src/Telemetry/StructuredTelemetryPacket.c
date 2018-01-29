//
//
// StructuredTelemetryPacket.c
//
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "StructuredTelemetryPacket.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void StructuredTelemetryPacket_setUnsignedByte(StructuredTelemetryPacket *This,
                                               unsigned int index, 
                                               unsigned char data)
{
    assert((This->numberOfBytes > 0) && (index < This->numberOfBytes));
    This->pByteBuffer[index] = data;
}

void StructuredTelemetryPacket_setUnsignedShort(StructuredTelemetryPacket *This, 
                                                unsigned int index, 
                                                unsigned short data)
{
    assert((This->numberOfBytes > 0) && 
           (sizeof(unsigned short)*(index+1) <= This->numberOfBytes));
    This->pShortBuffer[index] = data;
}

void StructuredTelemetryPacket_setUnsignedInt(StructuredTelemetryPacket *This, 
                                              unsigned int index, 
                                              unsigned int data)
{
    assert((This->numberOfBytes > 0) && 
           (sizeof(unsigned int)*(index+1) <= This->numberOfBytes));
    This->pIntBuffer[index] = data;
}

void StructuredTelemetryPacket_setNumberOfBytes(StructuredTelemetryPacket *This,
                                                unsigned int n)
{
	assert(This->numberOfBytes == 0);  // should not be called more than once
	assert(n > 0);

    if (This->numberOfBytes == 0) {

	    This->numberOfBytes = n;
        unsigned int nToBeAssigned;
        if ((n%sizeof(unsigned int)) == 0) {
            nToBeAssigned = n/sizeof(unsigned int);
        } else {
            nToBeAssigned = n/sizeof(unsigned int) + 1;
        }

	    This->pIntBuffer = g_malloc(sizeof(unsigned int)*nToBeAssigned);
	    assert(This->pIntBuffer != pNULL);

        This->pByteBuffer = (unsigned char*)This->pIntBuffer;
	    This->pShortBuffer = (unsigned short*)This->pIntBuffer;
    }
}

unsigned short StructuredTelemetryPacket_getUnsignedShort(StructuredTelemetryPacket *This, 
                                                        unsigned int index)
{
    TelemetryPacketClass *tpc = TELEMETRYPACKET_GET_CLASS(This);

    assert(sizeof(unsigned short)*(index+1) <= tpc->getNumberOfBytes(This));
    assert(This->numberOfBytes > 0);

    return This->pShortBuffer[index];
}

unsigned int StructuredTelemetryPacket_getUnsignedInt(StructuredTelemetryPacket *This, 
                                                      unsigned int index)
{
    TelemetryPacketClass *tpc = TELEMETRYPACKET_GET_CLASS(This);

    assert(sizeof(unsigned int)*(index+1) <= tpc->getNumberOfBytes(This));
    assert(This->numberOfBytes > 0);

    return This->pIntBuffer[index];
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Return the size of the internal telemetry buffer.
 * This is the number that was set with the first call to method
 * <code>setNumberOfBytes</code>.
 * @see #setNumberOfBytes
 * @return number of bytes in this telemetry packet
 */
static unsigned int getNumberOfBytes(void *obj)
{
    StructuredTelemetryPacket *This = STRUCTUREDTELEMETRYPACKET(obj);
	return This->numberOfBytes;
}

/**
 * Return the n-th element of the internal telemetry buffer.
 * A pseudo-code implementation for this method is as follows:<PRE>
 *		return pByteBuffer[n]; </PRE>
 * @see #setNumberOfBytes
 * @return value of n-th telemetry byte
 * @param n the telemetry byte to be returned(starting with byte 0)
 */
static unsigned char getUnsignedByte(void *obj, unsigned int n)
{
    StructuredTelemetryPacket *This = STRUCTUREDTELEMETRYPACKET(obj);

    assert(n < This->numberOfBytes);
    assert(This->numberOfBytes > 0);

    return This->pByteBuffer[n];
}

/**
 * Perform a class-specific configuration check on a structured
 * telemetry packet: verify that the telemetry buffers have been
 * initialized and allocated.
 * @return true if the telemetry packet is configured, false otherwise.
 */
static bool isObjectConfigured(void *obj)
{
    TelemetryPacketClass *tpc = GET_CLASS(TYPE_TELEMETRYPACKET);
    StructuredTelemetryPacket *This = STRUCTUREDTELEMETRYPACKET(obj);

    return ((CC_ROOTOBJECT_CLASS(tpc)->isObjectConfigured(obj)) &&
            (This->numberOfBytes > 0) && 
            (This->pByteBuffer != pNULL));
}



///////////////////////////////////////////////////////////////////////////////
//
//                    pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Implement the <i>data update service</i>. This method should be
 * implemented to load the telemetry buffers using the setter methods
 * defined in this class.
 * A call to this method should normally be followed by a call to method
 * <CODE>isValid</CODE> to verify the validity of the newly updated data.
 */
static void update(void *obj)
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
    StructuredTelemetryPacket *This = STRUCTUREDTELEMETRYPACKET(obj);

	This->pByteBuffer = pNULL;
	This->pShortBuffer = pNULL;
	This->pIntBuffer = pNULL;
	This->numberOfBytes = 0;
}

StructuredTelemetryPacket* StructuredTelemetryPacket_new(void)
{
    Object *obj = object_new(TYPE_STRUCTUREDTELEMETRYPACKET);
    return (StructuredTelemetryPacket*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    TelemetryPacketClass *tpc = TELEMETRYPACKET_CLASS(oc);
    tpc->getNumberOfBytes = getNumberOfBytes;
    tpc->getUnsignedByte = getUnsignedByte;
    tpc->update = update;

    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_STRUCTUREDTELEMETRYPACKET,
    .parent = TYPE_TELEMETRYPACKET,
    .instance_size = sizeof(StructuredTelemetryPacket),
    .abstract = true,
    .class_size = sizeof(StructuredTelemetryPacketClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void StructuredTelemetryPacket_register(void)
{
    type_register_static(&type_info);
}
