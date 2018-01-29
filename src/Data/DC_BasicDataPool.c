//
//
// DC_BasicDataPool.c
//
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Data/DC_BasicDataPool.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_BasicDataPool_setDataPoolSize(DC_BasicDataPool *This, TD_DataPoolId size)
{
    assert((This->value == pNULL) && (size > 0));

    This->size = size;
    This->value = g_malloc(sizeof(double)*((size/sizeof(double))+1));

    for (TD_DataPoolId i=0; i<size; i++) {
        This->value[i] = 0;
    }
}

TD_DataPoolId DC_BasicDataPool_getDataPoolSize(DC_BasicDataPool *This)
{
    return This->size;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Setter method for the value of a real-typed data pool item. 
 * @param id the data identifier of the data pool item to be set
 * @param newValue the new value to be set
 */
static void setFloatValue(void *obj, TD_DataPoolId id, TD_Float newValue)
{ 
    DC_BasicDataPool *This = DC_BASICDATAPOOL(obj);

    assert((This->value != pNULL) && 
           (id <= (int)(This->size - sizeof(TD_Float))));

    *(TD_Float*)(This->value + id) = newValue;
}

/**
 * Setter method for the value of an integer-typed data pool item.  
 * @param id the data identifier of the data pool item to be set
 * @param newValue the new value to be set
 */
static void setIntegerValue(void *obj, TD_DataPoolId id, TD_Integer newValue)
{
    DC_BasicDataPool *This = DC_BASICDATAPOOL(obj);

    assert((This->value != pNULL) && 
           (id <= (int)(This->size - sizeof(TD_Integer))));

    *(TD_Integer*)(This->value + id) = newValue;
}

/**
 * Getter method for the value of a real-typed data pool item. 
 * This method implements the <i>copy link</i>
 * mechanism for real-valued data. 
 * @param id the data identifier of the data pool item to be read
 * @return the value of the data with identifier id
 */
static TD_Float getFloatValue(void *obj, TD_DataPoolId id)
{
    DC_BasicDataPool *This = DC_BASICDATAPOOL(obj);

    assert((This->value != pNULL) && 
           (id <= (int)(This->size - sizeof(TD_Float))));

    return *(TD_Float*)(This->value + id);
}

/**
 * Getter method for the value of an integer-typed data pool item. 
 * This method implements the <i>copy link</i>
 * mechanism for integer-valued data.   
 * @param id the data identifier of the data pool item to be read
 * @return the value of the data with identifier id
 */
static TD_Integer getIntegerValue(void *obj, TD_DataPoolId id)
{
    DC_BasicDataPool *This = DC_BASICDATAPOOL(obj);
    
    assert((This->value != pNULL) && 
           (id <= (int)(This->size - sizeof(TD_Integer))));

    return *(TD_Integer*)(This->value + id);
}

/**
 * Getter method for the pointer to a real-typed data pool item. 
 * This method implements the <i>pointer link</i>
 * mechanism for real-typed data.
 * @param id the data identifier of the data pool item to be read
 * @return the pointer to the data with identifier id
 */
static TD_Float* getPointerFloatValue(void *obj, TD_DataPoolId id)
{
    DC_BasicDataPool *This = DC_BASICDATAPOOL(obj);

    assert((This->value != pNULL) && 
           (id <= (int)(This->size - sizeof(TD_Float))));

    return (TD_Float*)(This->value + id);
}

/**
 * Getter method for the pointer to an integer-typed data pool item. 
 * This method implements the <i>pointer link</i>
 * mechanism for integer-typed data.
 * @param id the data identifier of the data pool item to be read
 * @return the pointer to the data with identifier id
 */
static TD_Integer* getPointerIntegerValue(void *obj, TD_DataPoolId id)
{
    DC_BasicDataPool *This = DC_BASICDATAPOOL(obj);

    assert((This->value != pNULL) && 
           (id <= (int)(This->size - sizeof(TD_Integer))));

    return (TD_Integer*)(This->value + id);
}

/**
 * Perform a class-specific configuration check on a data pool component:
 * verify that the size of the data pool has been set.
 * @see #reset
 * @return true if the database object is configured, false otherwise
 */
static bool isObjectConfigured(void *obj)
{
    CC_RootObjectClass *cc_roc = GET_CLASS(TYPE_CC_ROOTOBJECT);
    DC_BasicDataPool *This = DC_BASICDATAPOOL(obj);
        
    return ((cc_roc->isObjectConfigured(obj)) && 
            (This->value != pNULL));
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    DC_BasicDataPool *This = DC_BASICDATAPOOL(obj);
    This->value = pNULL;
    This->size = 0;

    CC_RootObject_setClassId((CC_RootObject*)obj, ID_BASICDATAPOOL);
}

DC_BasicDataPool* DC_BasicDataPool_new(void)
{
    Object *obj = object_new(TYPE_DC_BASICDATAPOOL);
    return (DC_BasicDataPool*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    DataPoolClass *dpc = DATAPOOL_CLASS(oc);
    dpc->setFloatValue = setFloatValue;
    dpc->setIntegerValue = setIntegerValue;
    dpc->getFloatValue = getFloatValue;
    dpc->getIntegerValue = getIntegerValue;
    dpc->getPointerFloatValue = getPointerFloatValue;
    dpc->getPointerIntegerValue = getPointerIntegerValue;

    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_BASICDATAPOOL,
    .parent = TYPE_DATAPOOL,
    .instance_size = sizeof(DC_BasicDataPool),
    .abstract = false,
    .class_size = sizeof(DC_BasicDataPoolClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_BasicDataPool_register(void)
{
    type_register_static(&type_info);
}
