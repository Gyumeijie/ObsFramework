//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyDatabase.c
//
// Version	1.0
// Date		12.10.02
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/ClassId.h"
#include "DC_DummyDatabase.h"



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
   DC_DummyDatabase *This = DC_DUMMYDATABASE(obj);

   DC_BasicDatabase_setTableLength((DC_BasicDatabase*)obj, 1);
   DC_BasicDatabase_setOperationalTable((DC_BasicDatabase*)obj, &This->table);
   DC_BasicDatabase_setDefaultTable((DC_BasicDatabase*)obj, &This->table);

   ParameterDatabaseClass *pdc = PARAMETERDATABASE_GET_CLASS(obj);
   pdc->reset(obj);
   pdc->setParameterChar((DC_BasicDatabase*)obj, 0, (char)0);
   
   CC_RootObject_setClassId((CC_RootObject*)obj, ID_DUMMYDATABASE);
}

DC_DummyDatabase* DC_DummyDatabase_new(void)
{
    return (DC_DummyDatabase*)object_new(TYPE_DC_DUMMYDATABASE);
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data){}

static const TypeInfo type_info = {
    .name = TYPE_DC_DUMMYDATABASE,
    .parent = TYPE_DC_BASICDATABASE,
    .instance_size = sizeof(DC_DummyDatabase),
    .abstract = false,
    .class_size = sizeof(DC_DummyDatabaseClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_DummyDatabase_register(void)
{
    type_register_static(&type_info);
}