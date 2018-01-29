//
//
// DC_DummyCriticalTelecommand.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "DC_DummyCriticalTelecommand.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

unsigned int DC_DummyCriticalTelecommand_getNumberOfExecutions
(
    DC_DummyCriticalTelecommand *This
)
{
	return This->numberOfExecutions;
}

void DC_DummyCriticalTelecommand_setImageValidity
(
    DC_DummyCriticalTelecommand *This, 
    bool isValid
)
{
	This->imageValid = isValid;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Increments <code>numberOfExecutions</code> and returns a code
 * of "action successful".
 * @see #getNumberOfExecutions
 * @see CriticalTelecommand#doAction
 * @return always returns a "telecommand successfully executed" code
 */
static TD_ActionOutcome doCriticalAction(void *obj)
{
    DC_DummyCriticalTelecommand *This = DC_DUMMYCRITICALTELECOMMAND(obj);

	This->numberOfExecutions++;
	return ACTION_SUCCESS;
}

/**
 * The base class default implementation is overridden in order
 * to be able to thoroughly test <code>canExecute(void)</code>. This method
 * returns the value of the <code>imageValid</code> member variable.
 * @see CriticalTelecommand#canExecute
 * @see #setImageValidity
 * @return the value of imageValid
 */
static bool isImageValid(void *obj)
{
    DC_DummyCriticalTelecommand *This = DC_DUMMYCRITICALTELECOMMAND(obj);
	return This->imageValid;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    DC_DummyCriticalTelecommand *This = DC_DUMMYCRITICALTELECOMMAND(obj);
	This->numberOfExecutions = 0;
	This->imageValid = false;

	CC_RootObject_setClassId((CC_RootObject*)obj, ID_DUMMYCRITICALTELECOMMAND);
}

DC_DummyCriticalTelecommand* DC_DummyCriticalTelecommand_new(void)
{
    Object *obj = object_new(TYPE_DC_DUMMYCRITICALTELECOMMAND);
    return (DC_DummyCriticalTelecommand*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    CriticalTelecommandClass *ctc = CRITICALTELECOMMAND_CLASS(oc);

    ctc->doCriticalAction = doCriticalAction;
    ctc->isImageValid = isImageValid;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_DUMMYCRITICALTELECOMMAND,
    .parent = TYPE_CRITICALTELECOMMAND,
    .instance_size = sizeof(DC_DummyCriticalTelecommand),
    .abstract = false,
    .class_size = sizeof(DC_DummyCriticalTelecommandClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_DummyCriticalTelecommand_register(void)
{
    type_register_static(&type_info);
}
