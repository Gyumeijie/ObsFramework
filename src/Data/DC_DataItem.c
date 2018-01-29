//
//
// DC_DataItem.c (from DC_DataItem_inl.h file)
//


#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "DC_DataItem.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

TD_Float DC_DataItem_getFloatValue(const DC_DataItem *This)
{
	assert(This->varType == DI_FLOAT);
	return *(TD_Float*)This->pVar;
}

void DC_DataItem_setFloatValue(DC_DataItem *This, TD_Float newValue)
{
    assert(This->varType == DI_FLOAT);
    *(TD_Float*)This->pVar = newValue;
}

TD_Integer DC_DataItem_getIntegerValue(const DC_DataItem *This)
{
    assert(This->varType == DI_INT);
	return *(TD_Integer*)This->pVar;
}

void DC_DataItem_setIntegerValue(DC_DataItem *This, TD_Integer newValue)
{
   assert(This->varType == DI_INT);
   *(TD_Integer*)This->pVar = newValue;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void post_init(DC_DataItem *This, void *data, TD_DataItemType type)
{
	assert(data);

	This->pVar = data;
	This->varType = type;
}

DC_DataItem* DC_DataItem_new(void *data, TD_DataItemType type)
{
   Object *obj = object_new(TYPE_DC_DATAITEM);

   post_init((DC_DataItem*)obj, data, type);

   return (DC_DataItem*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    DC_DataItemClass *dc_dic = DC_DATAITEM_CLASS(oc);
    dc_dic->post_init = post_init;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_DATAITEM,
    .parent = TYPE_OBJECT,
    .instance_size = sizeof(DC_DataItem),
    .abstract = false,
    .class_size = sizeof(DC_DataItemClass),
    .class_init = class_init,
};

void DC_DataItem_register(void)
{
    type_register_static(&type_info);
}
