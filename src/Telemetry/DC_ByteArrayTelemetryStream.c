//
//
// DC_ByteArrayTelemetryStream.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Telemetry/TelemetryPacket.h"
#include "DC_ByteArrayTelemetryStream.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_ByteArrayTelemetryStream_setCapacity
(
    DC_ByteArrayTelemetryStream *This,
    unsigned int n
)
{
    assert(n > 0);
    This->size = n;
}

void DC_ByteArrayTelemetryStream_setStartingAddress
(
    DC_ByteArrayTelemetryStream *This,
    unsigned char *pAddress
)
{
    assert(pAddress != pNULL);
    This->tmData = pAddress;
}

unsigned char* DC_ByteArrayTelemetryStream_getStartingAddress
(
    const DC_ByteArrayTelemetryStream *This
)
{
    assert(This->tmData != pNULL);
    return This->tmData;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Reset the telemetry stream. The write counter is reset to 0.
 */
static void reset(void *obj)
{
    DC_ByteArrayTelemetryStream *This = DC_BYTEARRAYTELEMETRYSTREAM(obj);

    assert((This->size > 0) && (This->tmData != pNULL));
    This->writeCounter = 0;
}

/**
 * The flush operation is equivalent to a reset operation.
 * @see #reset
 */
static void flush(void *obj)
{
    TelemetryStreamClass *tsc = TELEMETRYSTREAM_GET_CLASS(obj);
    tsc->reset(obj);
}

/**
 * Return the capacity of the telemetry stream. The capacity of this
 * telemetry stream is equal to the size in bytes of the byte array.
 * @return the size of the byte array in number of bytes
 */
static unsigned int getCapacity(void *obj)
{
    DC_ByteArrayTelemetryStream *This = DC_BYTEARRAYTELEMETRYSTREAM(obj);

    assert(This->size > 0);
    return This->size;
}

/**
 * Return true if there is enough space in the byte array to write
 * the argument telemetry packet.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *	    if(pItem->getNumberOFBytes(void) greater than(N-writeCounter))
 *	        return false;
 *	    else
 *          return true; </PRE>
 * where N is the size of the byte array and
 * <code>writeCounter</code> is the value of the write counter.
 * <p>
 * @param pPacket the telemetry packet to be written to the telemetry stream
 * @return true if there is enough space in the telemetry stream to write
 * the telemetry packet, false otherwise
 */
static bool doesPacketFit(void *obj, TelemetryPacket *pItem)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    DC_ByteArrayTelemetryStream *This = DC_BYTEARRAYTELEMETRYSTREAM(obj);
    TelemetryPacketClass *tpc = TELEMETRYPACKET_GET_CLASS(pItem);

    assert(cc_roc->isObjectConfigured(obj));

    const unsigned int nBytes = tpc->getNumberOfBytes(pItem); 
    return (nBytes <= (This->size - This->writeCounter));
}

/**
 * Write one telemetry packet to the byte array.
 * The telemetry bytes read from the telemetry packet are written starting at
 * location wc in the byte array
 * where wc is the value of the write counter.
 * When the end of the byte array is reached, the method returns.
 * @param pItem the telemetry packet to be written to the telemetry stream
 */
static void write(void *obj, TelemetryPacket *pItem)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    DC_ByteArrayTelemetryStream *This = DC_BYTEARRAYTELEMETRYSTREAM(obj);
    TelemetryPacketClass *tpc = TELEMETRYPACKET_GET_CLASS(pItem);

    assert(cc_roc->isObjectConfigured(obj));

    unsigned int base = This->writeCounter;
    const unsigned int nBytes = tpc->getNumberOfBytes(pItem); 
    for (unsigned int i=0; i<nBytes; i++) {
        if ((i+base) >= This->size) break;
        This->tmData[base+i] = tpc->getUnsignedByte(pItem, i);
        This->writeCounter++;
    }
}

/**
 * Perform a class-specific configuration check on the telemetry stream:
 * verify that the size and starting address of the byte array have
 * been loaded.
 * @return true if the telemetry stream is configured, false otherwise.
 */
static bool isObjectConfigured(void *obj)
{
    TelemetryStreamClass *tsc = GET_CLASS(TYPE_TELEMETRYSTREAM);
    DC_ByteArrayTelemetryStream *This = DC_BYTEARRAYTELEMETRYSTREAM(obj);

    return ((CC_ROOTOBJECT_CLASS(tsc)->isObjectConfigured(obj)) && 
            (This->size > 0) && 
            (This->tmData != pNULL));
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    DC_ByteArrayTelemetryStream *This = DC_BYTEARRAYTELEMETRYSTREAM(obj);
    This->size = 0;
    This->tmData = pNULL;
    This->writeCounter = 0;

    CC_RootObject_setClassId((CC_RootObject*)obj, ID_BYTEARRAYTELEMETRYSTREAM);
}

DC_ByteArrayTelemetryStream* DC_ByteArrayTelemetryStream_new(void)
{
    Object *obj = object_new(TYPE_DC_BYTEARRAYTELEMETRYSTREAM);
    return (DC_ByteArrayTelemetryStream*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    TelemetryStreamClass *tsc = TELEMETRYSTREAM_CLASS(oc);
    tsc->reset = reset;
    tsc->flush = flush;
    tsc->getCapacity = getCapacity;
    tsc->doesPacketFit = doesPacketFit;
    tsc->write = write;

    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_BYTEARRAYTELEMETRYSTREAM,
    .parent = TYPE_TELEMETRYSTREAM,
    .instance_size = sizeof(DC_ByteArrayTelemetryStream),
    .abstract = false,
    .class_size = sizeof(DC_ByteArrayTelemetryStreamClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_ByteArrayTelemetryStream_register(void)
{
    type_register_static(&type_info);
}
