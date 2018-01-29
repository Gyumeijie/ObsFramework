//
//
// DC_DataItem16TmWord.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Data/DC_RawDataItem.h"
#include "DC_DataItem16TmWord.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_DataItem16TmWord_setDataItem(DC_DataItem16TmWord *This, 
                                     DC_RawDataItem *pDataItem)
{
    This->pDataItem = pDataItem;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Implement the <i>data update service</i>. The internal telemetry buffer
 * is loaded with the value of the data item.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *		tmWord = . . .;  // retrieve the 16-bit value of the data item
 *		setUnsignedShort(0, tmWord);</PRE>
 */
static void update(void *obj)
{
    DC_DataItem16TmWord *This = DC_DATAITEM16TMWORD(obj);

    assert(This->pDataItem != pNULL);

    unsigned short data = DC_RawDataItem_getUnsignedShort(This->pDataItem);
    StructuredTelemetryPacket_setUnsignedShort(obj, 0, data);
}

/**
 * Perform a class-specific configuration check on a
 * <code>DC_DataItem16TmWord</code>: verify that the data item has been
 * loaded.
 * @return true if the object is configured, false otherwise.
 */
static bool isObjectConfigured(void *obj)
{
   StructuredTelemetryPacketClass *stpc = GET_CLASS(TYPE_STRUCTUREDTELEMETRYPACKET);
   DC_DataItem16TmWord *This = DC_DATAITEM16TMWORD(obj);

   return ((CC_ROOTOBJECT_CLASS(stpc)->isObjectConfigured(obj)) && 
           (This->pDataItem!=pNULL));
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    DC_DataItem16TmWord *This = DC_DATAITEM16TMWORD(obj);
    This->pDataItem = pNULL;

    StructuredTelemetryPacket_setNumberOfBytes((StructuredTelemetryPacket*)obj, 2);
    StructuredTelemetryPacket_setUnsignedShort((StructuredTelemetryPacket*)obj, 0, 0);

    CC_RootObject_setClassId((CC_RootObject*)obj, ID_DATAITEM16TMWORD);
}

DC_DataItem16TmWord* DC_DataItem16TmWord_new(void)
{
    Object *obj = object_new(TYPE_DC_DATAITEM16TMWORD);
    return (DC_DataItem16TmWord*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    TelemetryPacketClass *tpc = TELEMETRYPACKET_CLASS(oc);
    tpc->update = update;

    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_DATAITEM16TMWORD,
    .parent = TYPE_STRUCTUREDTELEMETRYPACKET,
    .instance_size = sizeof(DC_DataItem16TmWord),
    .abstract = false,
    .class_size = sizeof(DC_DataItem16TmWordClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_DataItem16TmWord_register(void)
{
    type_register_static(&type_info);
}
