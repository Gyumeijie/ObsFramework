//
//
// DC_DummyTelecommand.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "DC_DummyTelecommand.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

unsigned int DC_DummyTelecommand_getExecutionCounter(DC_DummyTelecommand *This)
{
   return This->executionCounter;
}

void DC_DummyTelecommand_setExecutionCheckValue(DC_DummyTelecommand *This,
                                                bool executionCheckValue)
{
    This->executionCheckValue = executionCheckValue;
}

void DC_DummyTelecommand_setValidityCheckValue(DC_DummyTelecommand *This,
                                               bool validityCheckValue)
{
    This->validityCheckValue = validityCheckValue;
}

void DC_DummyTelecommand_setValidityCheckCode(DC_DummyTelecommand *This, 
                                              TD_CheckCode validityCheckCode)
{
    This->validityCheckCode = validityCheckCode;
}

void DC_DummyTelecommand_setExecutionCheckCode(DC_DummyTelecommand *This, 
                                               TD_CheckCode executionCheckCode)
{
    This->executionCheckCode = executionCheckCode;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Increment the execution counter by one and return a code of "action successful".
 * Note that there is no protection against
 * an overflow in the value of the execution counter.
 * @see PunctualAction#execute
 * @return always returns a "telecommand successfully executed" code
 */
static TD_ActionOutcome doAction(void *obj)
{
   DC_DummyTelecommand *This = DC_DUMMYTELECOMMAND(obj);

   This->executionCounter++;
   return ACTION_SUCCESS;
}

/**
 * Execute the execution check on the telecommand.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *      return executionCheckValue; </PRE>
 * The internal variable <code>executionCheckValue</code> is initialized
 * to <code>TC_CANNOT_EXECUTE</code> by the constructor but its value
 * can be changed with method <code>setExecutionCheckValue</code>
 * @see #setExecutionCheckValue
 * @see CC_TelecommandManager#activate
 * @return the value of the internal variable <code>setExecutionCheckValue</code>
 */
static bool canExecute(void *obj)
{
    DC_DummyTelecommand *This = DC_DUMMYTELECOMMAND(obj);
    return This->executionCheckValue;
}

/**
 * Execute the validity check on the telecommand.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *      return validityCheckValue; </PRE>
 * The internal variable <code>validityCheckValue</code> is initialized
 * to <code>VALID</code> by the constructor but its value
 * can be changed with method <code>setValidityCheckValue</code>
 * @see #setValidityCheckValue
 * @see CC_TelecommandManager#load
 * @return the value of the internal variable <code>setExecutionCheckValue</code>
 */
static bool isValid(void *obj)
{
    DC_DummyTelecommand *This = DC_DUMMYTELECOMMAND(obj);
    return This->validityCheckValue;
}

/**
 * Return the validity check code for the telecommand.
 * This implementation returns a user-defined value that is set with method
 * <code>setValidityCheckCode</code>.
 * @see #setValidityCheckCode
 * @return the validity check code
 */
static TD_CheckCode getValidityCheckCode(const void *obj)
{
    DC_DummyTelecommand *This = DC_DUMMYTELECOMMAND(obj);
    return This->validityCheckCode;
}

/**
 * Return the execution check code for the telecommand.
 * This implementation returns a user-defined value that is set with method
 * <code>setExecutionCheckCode</code>.
 * @see #setExecutionCheckCode
 * @return the validity check code
 */
static TD_CheckCode getExecutionCheckCode(const void *obj)
{
    DC_DummyTelecommand *This = DC_DUMMYTELECOMMAND(obj);
    return This->executionCheckCode;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    DC_DummyTelecommand *This = DC_DUMMYTELECOMMAND(obj);
    This->executionCounter = 0; 
    This->executionCheckValue = TC_CAN_EXECUTE;
    This->validityCheckValue = VALID;
    This->executionCheckCode = 0;
    This->validityCheckCode = 0;

    CC_RootObject_setClassId((CC_RootObject*)obj, ID_DUMMYTELECOMMAND);
}

DC_DummyTelecommand* DC_DummyTelecommand_new(void)
{
    Object *obj = object_new(TYPE_DC_DUMMYTELECOMMAND);
    return (DC_DummyTelecommand*)obj;
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

    TelecommandClass *tc = TELECOMMAND_CLASS(oc);
    tc->canExecute = canExecute;
    tc->isValid = isValid;
    tc->getValidityCheckCode = getValidityCheckCode;
    tc->getExecutionCheckCode = getExecutionCheckCode;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_DUMMYTELECOMMAND,
    .parent = TYPE_TELECOMMAND,
    .instance_size = sizeof(DC_DummyTelecommand),
    .abstract = false,
    .class_size = sizeof(DC_DummyTelecommandClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_DummyTelecommand_register(void)
{
    type_register_static(&type_info);
}
