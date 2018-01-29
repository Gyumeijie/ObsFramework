//
//
// DC_RawDataItem.c (from DC_RawDataItem_inl.h file)
//


#include "../GeneralInclude/CompilerSwitches.h"
#include "DC_RawDataItem.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * In the following methods, we don't use macro DC_DATAITEM(This), for it is
 * cost, and effects runtime efficiency. For parameter "This" has a type of
 * "DC_RawDataItem*", so we can safely use "(DC_DataItem*)This" to cast. This
 * kind of type cast is done at the compile time. 
 */
char DC_RawDataItem_getChar(const DC_RawDataItem *This)
{
    DC_DataItem *parent = (DC_DataItem*)This;
	return *(char*)parent->pVar;
}

void DC_RawDataItem_setChar(DC_RawDataItem *This, char newValue)
{
    DC_DataItem *parent = (DC_DataItem*)This;
	*(char*)parent->pVar = newValue;
}

unsigned char DC_RawDataItem_getUnsignedChar(const DC_RawDataItem *This)
{
    DC_DataItem *parent = (DC_DataItem*)This;
	return *(unsigned char*)parent->pVar;
}

void DC_RawDataItem_setUnsignedChar(DC_RawDataItem *This, unsigned char newValue)
{
    DC_DataItem *parent = (DC_DataItem*)This;
	*(unsigned char*)parent->pVar = newValue;
}

short DC_RawDataItem_getShort(const DC_RawDataItem *This)
{
    DC_DataItem *parent = (DC_DataItem*)This;
	return *(short*)parent->pVar;
}

void DC_RawDataItem_setShort(DC_RawDataItem *This, short newValue)
{
    DC_DataItem *parent = (DC_DataItem*)This;
	*(short*)parent->pVar = newValue;
}

unsigned short DC_RawDataItem_getUnsignedShort(const DC_RawDataItem *This)
{
    DC_DataItem *parent = (DC_DataItem*)This;
	return *(unsigned short*)parent->pVar;
}

void DC_RawDataItem_setUnsignedShort(DC_RawDataItem *This, unsigned short newValue)
{
    DC_DataItem *parent = (DC_DataItem*)This;
	*(unsigned short*)parent->pVar = newValue;
}

int DC_RawDataItem_getInt(const DC_RawDataItem *This)
{
    DC_DataItem *parent = (DC_DataItem*)This;
	return *(int*)parent->pVar;
}

void DC_RawDataItem_setInt(DC_RawDataItem *This, int newValue)
{
    DC_DataItem *parent = (DC_DataItem*)This;
	*(int*)parent->pVar = newValue;
}

unsigned int DC_RawDataItem_getUnsignedInt(const DC_RawDataItem *This)
{
    DC_DataItem *parent = (DC_DataItem*)This;
	return *(unsigned int*)parent->pVar;
}

void DC_RawDataItem_setUnsignedInt(DC_RawDataItem *This, unsigned int newValue)
{
    DC_DataItem *parent = (DC_DataItem*)This;
	*(unsigned int*)parent->pVar = newValue;
}

float DC_RawDataItem_getFloat(const DC_RawDataItem *This)
{
    DC_DataItem *parent = (DC_DataItem*)This;
	return *(float*)(parent->pVar);
}

void DC_RawDataItem_setFloat(DC_RawDataItem *This, float newValue)
{
    DC_DataItem *parent = (DC_DataItem*)This;
	*(float*)parent->pVar = newValue;
}

double DC_RawDataItem_getDouble(const DC_RawDataItem *This)
{
    DC_DataItem *parent = (DC_DataItem*)This;
	return *(double*)parent->pVar;
}

void DC_RawDataItem_setDouble(DC_RawDataItem *This, double newValue)
{
    DC_DataItem *parent = (DC_DataItem*)This;
	*(double*)parent->pVar = newValue;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void post_init(DC_RawDataItem *This, void *data)
{
    DC_DATAITEM_GET_CLASS(This)->post_init((DC_DataItem*)This, data, DI_INT);
}

DC_RawDataItem* DC_RawDataItem_new(void *data)
{
   Object *obj = object_new(TYPE_DC_RAWDATAITEM);

   post_init((DC_RawDataItem*)obj, data);

   return (DC_RawDataItem*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data){}

static const TypeInfo type_info = {
    .name = TYPE_DC_RAWDATAITEM,
    .parent = TYPE_DC_DATAITEM,
    .instance_size = sizeof(DC_RawDataItem),
    .abstract = false,
    .class_size = sizeof(DC_RawDataItemClass),
    .class_init = class_init,
};

void DC_RawDataItem_register(void)
{
    type_register_static(&type_info);
}
