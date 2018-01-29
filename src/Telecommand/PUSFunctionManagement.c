//
//
// PUSFunctionManagement.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "PUSFunctionManagement.h"



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    TelecommandClass *tc = TELECOMMAND_GET_CLASS(obj);

    tc->setType(obj, PUS_TYPE_TC_FNC);
    tc->setSubType(obj, PUS_ST_TC_FNC_PER);
}

PUSFunctionManagement* PUSFunctionManagement_new(void)
{
    Object *obj = object_new(TYPE_PUSFUNCTIONMANAGEMENT);
    return (PUSFunctionManagement*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data){}

static const TypeInfo type_info = {
    .name = TYPE_PUSFUNCTIONMANAGEMENT,
    .parent = TYPE_PUSTELECOMMAND,
    .instance_size = sizeof(PUSFunctionManagement),
    .abstract = false,
    .class_size = sizeof(PUSFunctionManagementClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void PUSFunctionManagement_register(void)
{
    type_register_static(&type_info);
}
