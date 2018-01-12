//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyDataPool.c
//
// Version	1.0
// Date		10.10.03 (Version 1.0)
// Author	A. Pasetti (P&P Software)
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

    DC_BasicDataPool_setDataPoolSize((DC_BasicDataPool*)obj, sizeof(TD_Integer));

    DataPoolClass *dpc = DATAPOOL_GET_CLASS(obj);
    dpc->setIntegerValue(obj, 0, 0);
}

DC_DummyDataPool* DC_DummyDataPool_new(void)
{
    return (DC_DummyDataPool*)object_new(TYPE_DC_DUMMYDATAPOOL);
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
