//
//
// DC_CycleDataItem16TmStream.c
//
//
// Change Record:
//                equivalent to a call to method reset.

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Data/DC_RawDataItem.h"
#include "../Telemetry/TelemetryPacket.h"
#include "DC_CycleDataItem16TmStream.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_CycleDataItem16TmStream_setNumberOfDataItems
(
    DC_CycleDataItem16TmStream *This, 
    unsigned int n
)
{
    TelemetryStreamClass *tsc = TELEMETRYSTREAM_GET_CLASS(This);

    assert(This->nDataItems == 0);        // should only be called once
    assert(n > 0);

    if (This->nDataItems == 0) {
        This->nDataItems = n;
        This->pDataItem = g_malloc(n*sizeof(DC_RawDataItem*));
        for (unsigned int i=0; i<n; i++) {
            This->pDataItem[i] = pNULL;
        }
    
        tsc->reset(This);
    }
}

void DC_CycleDataItem16TmStream_setDataItem
(
    DC_CycleDataItem16TmStream *This, 
    unsigned int index, 
    DC_RawDataItem *pDI
)
{
    assert((This->nDataItems > 0) && (index < This->nDataItems));
    assert(pDI != pNULL);
    This->pDataItem[index] = pDI;
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
    DC_CycleDataItem16TmStream *This = DC_CYCLEDATAITEM16TMSTREAM(obj);

    assert((This->nDataItems > 0) && (This->pDataItem != pNULL));
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
 * Return the number of data items managed by this telemetry stream.
 * The number of data items is set with method <code>setNumberOfDataItems</code>
 * @see #setNumberOfDataItems
 * @return the size of the telemetry stream(the number of data items)
 */
static unsigned int getCapacity(void *obj)
{
    DC_CycleDataItem16TmStream *This = DC_CYCLEDATAITEM16TMSTREAM(obj);

    assert((This->nDataItems > 0) && (This->pDataItem != pNULL));
    return This->nDataItems;
}

/**
 * Return true if it is possible to write the entire content of the argument
 * telemetry packet to the data item.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *	    if(pItem->getNumberOfBytes(void) greater than 2*(N-writeCounter))
 *	        return false;
 *	    else
 *		    return true; </PRE>
 * where N is the number of data items in the telemetry stream and
 * <code>writeCounter</code> is the value of the write counter.
 * <p>
 * @param pPacket the telemetry packet to be written to the telemetry stream.
 * @return true if there is enough space in the telemetry stream to write
 * n bytes, false otherwise
 */
static bool doesPacketFit(void *obj, TelemetryPacket* pItem)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    TelemetryPacketClass *tpc = TELEMETRYPACKET_GET_CLASS(pItem);
    DC_CycleDataItem16TmStream *This = DC_CYCLEDATAITEM16TMSTREAM(obj);

    assert(cc_roc->isObjectConfigured(obj));
    
    const unsigned int nBytes = tpc->getNumberOfBytes(pItem);
    return (nBytes <= 2*(This->nDataItems - This->writeCounter));
}

/**
 * Write the telemetry packet content to the data items.
 * Only the telemetry bytes in the telemetry packet are written(the header
 * information - the telemetry packet time tag, destination, type and subtype -
 * are not written).
 * A pseudo-code implementation for this method is as follows: <PRE>
 *      for(i=0; i<(pItem->getNumberOfBytes(void)-1); i=i+2)
 *          collect the i-th and(i+1)-bytes from pItem
 *          if(writeCounter smaller than N-1)
 *	            combine the i-th and(i+1)-bytes in one 16-bit word;
 *              write the 16-bit word to writeCounter-th data item;
 *              writeCounter++;
 *          else
 *              return; </PRE>
 * where N is the number of data items in the telemetry stream.
 * The merge of two successive telemetry bytes from the telemetry packet
 * into one single 16-bit word is done by overlaying the i-th byte with the
 * least significant byte of the data item word and the(i+1)-th byte with
 * the most significant byte.
 * @param pItem the telemetry packet to be written to the
 * telemetry stream.
 */
static void write(void *obj, TelemetryPacket *pItem)
{   
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    TelemetryPacketClass *tpc = TELEMETRYPACKET_GET_CLASS(pItem);
    DC_CycleDataItem16TmStream *This = DC_CYCLEDATAITEM16TMSTREAM(obj);

    assert(cc_roc->isObjectConfigured(obj));

    unsigned short tmValue;
    unsigned short temp;
    const unsigned int nBytes = tpc->getNumberOfBytes(pItem) - 1;
    for (unsigned int i=0; i<nBytes; i=i+2) {
        if (This->writeCounter < This->nDataItems) {
            tmValue = (unsigned short)tpc->getUnsignedByte(pItem, i);
            temp = ((unsigned short)tpc->getUnsignedByte(pItem, i+1))<<8;
            tmValue = tmValue + temp;

            DC_RawDataItem *dataItem = This->pDataItem[This->writeCounter];
            DC_RawDataItem_setUnsignedShort(dataItem, tmValue);

            This->writeCounter++;
        } else {
            break;
        }
    }
}

/**
 * Perform a class-specific configuration check on the telemetry stream:
 * verify that the number of data items has been set and that all
 * data items have been loaded.
 * @return true if the telemetry stream is configured, false otherwise.
 */
static bool isObjectConfigured(void *obj)
{
    TelemetryStreamClass *tsc =  GET_CLASS(TYPE_TELEMETRYSTREAM);
    DC_CycleDataItem16TmStream *This = DC_CYCLEDATAITEM16TMSTREAM(obj);

    if (!(CC_ROOTOBJECT_CLASS(tsc)->isObjectConfigured(obj)) || 
         (This->nDataItems == 0)) {
        return NOT_CONFIGURED;
    }
    
    for (unsigned int i=0; i<This->nDataItems; i++) {
        if (This->pDataItem[i] == pNULL) return NOT_CONFIGURED;
    }

    return CONFIGURED;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    DC_CycleDataItem16TmStream *This = DC_CYCLEDATAITEM16TMSTREAM(obj);
    This->nDataItems = 0;
    This->writeCounter = 0;

    CC_RootObject_setClassId((CC_RootObject*)obj, ID_CYCLEDATAITEM16TMSTREAM);
}

DC_CycleDataItem16TmStream* DC_CycleDataItem16TmStream_new(void)
{
    Object *obj = object_new(TYPE_DC_CYCLEDATAITEM16TMSTREAM);
    return (DC_CycleDataItem16TmStream*)obj;
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
    .name = TYPE_DC_CYCLEDATAITEM16TMSTREAM,
    .parent = TYPE_TELEMETRYSTREAM,
    .instance_size = sizeof(DC_CycleDataItem16TmStream),
    .abstract = false,
    .class_size = sizeof(DC_CycleDataItem16TmStreamClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_CycleDataItem16TmStream_register(void)
{
    type_register_static(&type_info);
}
