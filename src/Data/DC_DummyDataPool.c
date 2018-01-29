//
//
// DC_DummyDataPool.c
//
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/ClassId.h"
#include "DC_DummyDataPool.h"



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    CC_RootObject_setClassId((CC_RootObject*)obj, ID_DUMMYDATAPOOL);
    DataPoolClass *dpc = DATAPOOL_GET_CLASS(obj);

    DC_BasicDataPool_setDataPoolSize((DC_BasicDataPool*)obj, sizeof(TD_Integer));

    dpc->setIntegerValue(obj, 0, 0);
}

DC_DummyDataPool* DC_DummyDataPool_new(void)
{
    Object *obj = object_new(TYPE_DC_DUMMYDATAPOOL);
    return (DC_DummyDataPool*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data){}

static const TypeInfo type_info = {
    .name = TYPE_DC_DUMMYDATAPOOL,
    .parent = TYPE_DC_BASICDATAPOOL,
    .instance_size = sizeof(DC_DummyDataPool),
    .abstract = false,
    .class_size = sizeof(DC_DummyDataPoolClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_DummyDataPool_register(void)
{
    type_register_static(&type_info);
}
