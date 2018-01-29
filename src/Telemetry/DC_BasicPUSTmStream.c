//
//
// DC_BasicPUSTmStream.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../Event/DC_EventRepository.h"
#include "../Telemetry/TelemetryPacket.h"
#include "../Telemetry/PUSTelemetryPacket.h"
#include "DC_BasicPUSTmStream.h"

#include <string.h>



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_BasicPUSTmStream_setCapacity(DC_BasicPUSTmStream *This,
                                     unsigned int n)
{
    assert(n > 0);
    This->size = n;
}

void DC_BasicPUSTmStream_setStartAddress(DC_BasicPUSTmStream *This, 
                                         unsigned char *pAddress)
{
    assert(pAddress != pNULL);
    This->tmData = pAddress;
    TelemetryStreamClass *tsc = TELEMETRYSTREAM_GET_CLASS(This);
    tsc->reset(This);
}

unsigned char* DC_BasicPUSTmStream_getStartAddress(const DC_BasicPUSTmStream *This)
{
    assert(This->tmData != pNULL);
    return This->tmData;
}

unsigned int DC_BasicPUSTmStream_getPacketCounter(const DC_BasicPUSTmStream *This)
{
    assert(This->tmData != pNULL);
    return This->tmData[0];
}

unsigned int DC_BasicPUSTmStream_getWriteCounter(const DC_BasicPUSTmStream *This)
{
    return This->writeCounter;
}

unsigned int DC_BasicPUSTmStream_getSequenceCounter(const DC_BasicPUSTmStream *This)
{
    return (This->packetSequenceControl%0x40);
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Reset the telemetry stream. The write counter is set to 1 and the packet 
 * counter is set to 0.
 * The next packet will be written at the beginning of the telemetry
 * write area(starting at location 1, location 0 is reserved for the 
 * packet counter).
 */
static void reset(void *obj)
{
    DC_BasicPUSTmStream *This = DC_BASICPUSTMSTREAM(obj);

    assert((This->size > 0) && (This->tmData != pNULL));
    This->writeCounter = 1;
    This->tmData[0] = 0;
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
 * telemetry stream is equal to the size in bytes of the telemetry write
 * area.
 * @return the size of the byte array in number of bytes
 */
static unsigned int getCapacity(void *obj)
{
    DC_BasicPUSTmStream *This = DC_BASICPUSTMSTREAM(obj);

    assert(This->size > 0);
    return This->size;
}

/**
 * Return true if there is enough space in the telemetry write area to write
 * the argument telemetry packet.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *      if(pItem->getNumberOfBytes(void)==0)
 *          return true;
 *	    if((pItem->getNumberOfBytes(void)+headerSize) greater than(N-writeCounter))
 *	        return false;
 *	    else
 *          return true; </PRE>
 * where N is the size of the telemetry write area, 
 * <code>writeCounter</code> is the value of the write counter, and
 * <code>headerSize</code> is the size of the PUS header that method
 * <code>write</code> adds to the application data returned by the packet.
 * <p>
 * @param pPacket the telemetry packet to be written to the telemetry stream
 * @return true if there is enough space in the telemetry stream to write
 * the telemetry packet, false otherwise
 */
static bool doesPacketFit(void *obj, TelemetryPacket *pItem)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    TelemetryPacketClass *tpc = TELEMETRYPACKET_GET_CLASS(pItem);
    DC_BasicPUSTmStream *This = DC_BASICPUSTMSTREAM(obj);

    assert(cc_roc->isObjectConfigured(obj));
     
    const unsigned int nBytes = tpc->getNumberOfBytes(pItem);
    if (nBytes == 0) return true;

    return ((nBytes+This->nAdditionalBytes) <= (This->size-This->writeCounter));
}

/**
 * Write one telemetry packet to the telemetry write area.
 * First the PUS header is written to the telemetry write area. Then
 * the telemetry bytes read from the telemetry packet are written in
 * sequence. The write operation begins at
 * location wc in the telemetry write area 
 * where wc is the value of the write counter.
 * Before beginning to write the packet data, a check is made to verify that
 * there is enough space in the telemetry write area. If this is not the case, 
 * then an event of type
 * EVT_TM_STREAM_END is generated and the method returns.
 * After successful completion of a write operation, the packet counter is
 * incremented by 1. The sequence count is incremented by one for each write
 * request regardless of whether or not it was successful
 * <p>
 * There is no check on an overflow of either the write or
 * packet counter.
 * <p>
 * The telemetry packet data are extracted from the telemetry packet 
 * component through its <i>data acquisition service</i>. If the packet
 * provides it, then the <i>fast version</i> of the service is used.
 * Otherwise the <i>safe version</i> is used. Method 
 *<code>isFastAcquisitionImplemented</code> is used to determine 
 * whether the fast version is provided.
 * @param pItem the telemetry packet to be written to the telemetry stream
 */
static void write(void *obj, TelemetryPacket *pItem)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    TelemetryPacketClass *tpc = TELEMETRYPACKET_GET_CLASS(pItem);
    TelemetryStreamClass *tsc = TELEMETRYSTREAM_GET_CLASS(obj);
    DC_BasicPUSTmStream *This = DC_BASICPUSTMSTREAM(obj);

    assert(cc_roc->isObjectConfigured(obj));
    unsigned int nTmData = tpc->getNumberOfBytes(pItem);

    // Increment packet sequence counter
    if (This->packetSequenceControl == 0xFF) {
        This->packetSequenceControl = 0xC0;
    } else {
        This->packetSequenceControl++;
    }

    // In order to access them concisely and efficiently below
    unsigned char* const tmData = This->tmData;  
    unsigned int writeCounter = This->writeCounter;

    // Check if the packet fits in the telemetry write area
    unsigned int capacity = writeCounter + nTmData + This->nAdditionalBytes;
    if (capacity > tsc->getCapacity(obj)) {
        DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
        DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
        dc_erc->create(dc_er, obj, EVT_TM_STREAM_END);
        return;
    }

    assert(sizeof(TD_PUSPacketId) == 2);

    // Write packet header
    TD_PUSPacketId t1 = PUSTelemetryPacket_getPacketId();
    unsigned short t3 = (unsigned short)(This->nAdditionalBytes-6+nTmData);
    memcpy(tmData+writeCounter, &t1, 2);
    memcpy(tmData+writeCounter+2, &This->packetSequenceControl, 2);
    memcpy(tmData+writeCounter+4, &t3, 2);
    writeCounter = writeCounter + 6;

    // Write packet data field
    assert(sizeof(TD_TelemetryType) == 1);
    assert(sizeof(TD_TelemetrySubType) == 1);
    tmData[writeCounter] = 0x10;
    tmData[writeCounter+1] = tpc->getType(pItem);
    tmData[writeCounter+2] = tpc->getSubType(pItem);

    TD_ObsTime obsTimeTag = tpc->getTimeTag(pItem);
    memcpy(tmData+writeCounter+3, &obsTimeTag, sizeof(TD_ObsTime));

    writeCounter = writeCounter + 3 + sizeof(TD_ObsTime);

    if (tpc->isFastAcquisitionImplemented(pItem)) {
       unsigned char *s = tpc->getStartAddress(pItem);
       for (unsigned int j=0; j<nTmData; j++) {
           tmData[writeCounter+j] = s[j];
       }
    } else {
       for (unsigned int i=0; i<nTmData; i++) {
           tmData[writeCounter+i] = tpc->getUnsignedByte(pItem, i);
       }
    }
    writeCounter = writeCounter + nTmData;

    // Write the packet error control field
    tmData[writeCounter] = 0;
    tmData[writeCounter+1] = 0;
    writeCounter = writeCounter + 2;

    // Write back data member writeCounter
    This->writeCounter = writeCounter;

    // Update the packet counter
    tmData[0]++;

}

/**
 * Perform a class-specific configuration check on the telemetry stream:
 * verify that the size and starting address of the telemetry write area have
 * been loaded.
 * @return true if the telemetry stream is configured, false otherwise.
 */
static bool isObjectConfigured(void *obj)
{
    DC_BasicPUSTmStream *This = DC_BASICPUSTMSTREAM(obj);
    TelemetryStreamClass *tsc = GET_CLASS(TYPE_TELEMETRYSTREAM); 

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
    DC_BasicPUSTmStream *This = DC_BASICPUSTMSTREAM(obj);
    This->size = 0;
    This->tmData = pNULL;
    This->writeCounter = 0;
    This->packetSequenceControl = 0xC0;   
    This->nAdditionalBytes = 11 + sizeof(TD_ObsTime);

    CC_RootObject_setClassId((CC_RootObject*)obj, ID_BASICPUSTMSTREAM);
}

DC_BasicPUSTmStream* DC_BasicPUSTmStream_new(void)
{
    Object *obj = object_new(TYPE_DC_BASICPUSTMSTREAM);
    return (DC_BasicPUSTmStream*)obj;
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
    .name = TYPE_DC_BASICPUSTMSTREAM,
    .parent = TYPE_TELEMETRYSTREAM,
    .instance_size = sizeof(DC_BasicPUSTmStream),
    .abstract = false,
    .class_size = sizeof(DC_BasicPUSTmStreamClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_BasicPUSTmStream_register(void)
{
    type_register_static(&type_info);
}
