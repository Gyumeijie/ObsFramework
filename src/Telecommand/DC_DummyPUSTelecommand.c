//
//
// DC_DummyPUSTelecommand.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/TestConstants.h"
#include "DC_DummyPUSTelecommand.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

unsigned int DC_DummyPUSTelecommand_getExecutionCounter
(
    DC_DummyPUSTelecommand *This
)
{
   return This->executionCounter;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Increment the execution counter by one and return a code of "action successful".
 * @see PunctualAction#execute
 * @return always returns a "telecommand successfully executed" code
 */
static TD_ActionOutcome doAction(void *obj)
{
   DC_DummyPUSTelecommand *This = DC_DUMMYPUSTELECOMMAND(obj);

   This->executionCounter++;
   return ACTION_SUCCESS;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
   DC_DummyPUSTelecommand *This = DC_DUMMYPUSTELECOMMAND(obj);
   This->executionCounter = 0; 

   CC_RootObject_setClassId((CC_RootObject*)obj, ID_DUMMYPUSTELECOMMAND);

   TelecommandClass *tc = TELECOMMAND_GET_CLASS(obj);
   tc->setAcknowledgeLevel(obj, 0);
   tc->setTelecommandId(obj, TEST_TC_ID);
   tc->setSource(obj, TEST_TC_SOURCE);
   tc->setSubType(obj, TEST_TC_SUBTYPE);
   tc->setType(obj, TEST_TC_TYPE);

}

DC_DummyPUSTelecommand* DC_DummyPUSTelecommand_new(void)
{
    Object *obj = object_new(TYPE_DC_DUMMYPUSTELECOMMAND);
    return (DC_DummyPUSTelecommand*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    PunctualActionClass *pac = PUNCTUALACTION_CLASS(oc);
    pac->doAction = doAction;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_DUMMYPUSTELECOMMAND,
    .parent = TYPE_PUSTELECOMMAND,
    .instance_size = sizeof(DC_DummyPUSTelecommand),
    .abstract = false,
    .class_size = sizeof(DC_DummyPUSTelecommandClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_DummyPUSTelecommand_register(void)
{
    type_register_static(&type_info);
}
