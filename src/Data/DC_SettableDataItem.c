//
//
// DC_RawDataItem.c
//


#include "DC_DataItem.h"
#include "DC_SettableDataItem.h"


///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_SettableDataItem_setIntegerVariable
(
    DC_SettableDataItem *This,  
    TD_Integer *pNewVar
)
{
    DC_DataItem *parent = (DC_DataItem*)This;
	parent->pVar = pNewVar;
}

void DC_SettableDataItem_setFloatVariable
(
    DC_SettableDataItem *This, 
    TD_Float *pNewVar
)
{
    DC_DataItem *parent = (DC_DataItem*)This;
	parent->pVar = pNewVar;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void post_init(DC_SettableDataItem *This, void *data, TD_DataItemType type)
{
    DC_DATAITEM_GET_CLASS(This)->post_init((DC_DataItem*)This, data, type);
}

DC_SettableDataItem* DC_SettableDataItem_new(void *data, TD_DataItemType type)
{
   Object *obj = object_new(TYPE_DC_SETTABLEDATAITEM);
   post_init((DC_SettableDataItem*)obj, data, type);
   return (DC_SettableDataItem*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    DC_SettableDataItemClass *dc_sdic = DC_SETTABLEDATAITEM_CLASS(oc);
    dc_sdic->post_init = post_init;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_SETTABLEDATAITEM,
    .parent = TYPE_DC_DATAITEM,
    .instance_size = sizeof(DC_SettableDataItem),
    .abstract = false,
    .class_size = sizeof(DC_SettableDataItemClass),
    .class_init = class_init,
};

void DC_SettableDataItem_register(void)
{
    type_register_static(&type_info);
}
