//
//
// DC_TestPUSTelecommand.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/BasicTypes.h"
#include "PUSTelecommand.h"
#include "DC_TestPUSTelecommand.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

unsigned int DC_TestPUSTelecommand_getExecutionCounter
(
    DC_TestPUSTelecommand *This
)
{
    return This->executionCounter;
}

void DC_TestPUSTelecommand_setExecutionCheckValue 
(
    DC_TestPUSTelecommand *This, 
    bool executionCheckValue
)
{
    This->executionCheckValue = executionCheckValue;
}

void DC_TestPUSTelecommand_setValidityCheckValue
(
    DC_TestPUSTelecommand *This, 
    bool validityCheckValue)
{
    This->validityCheckValue = validityCheckValue;
}

void DC_TestPUSTelecommand_setValidityCheckCode
(
    DC_TestPUSTelecommand *This, 
    TD_CheckCode validityCheckCode
)
{
    This->validityCheckCode = validityCheckCode;
}

void DC_TestPUSTelecommand_setExecutionCheckCode
(
    DC_TestPUSTelecommand *This, 
    TD_CheckCode executionCheckCode
)
{
    This->executionCheckCode = executionCheckCode;
}

void DC_TestPUSTelecommand_setActionOutcome
(
    DC_TestPUSTelecommand *This, 
    bool executionSuccess
)
{
    This->executionSuccess = executionSuccess;
}

bool DC_TestPUSTelecommand_getActionOutcome
(
     DC_TestPUSTelecommand *This
)
{
     return This->executionSuccess;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Increment the execution counter by one and return the execution outcome code 
 * set in the application data.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *      if(exectionCounter<255)
 *          executionCounter++;
 *      else
 *          executionCounter=0;
 *      if(executionSuccess)
 *          return ACTION_SUCCESS;
 *      else
 *          return ACTION_FAILURE;</PRE>
 * The vlaue of the internal flag <code>executionSuccess</code> is read from
 * the telecommand application data. 
 * @see PunctualAction#execute
 * @return the execution outcome code(either ACTION_SUCCESS or ACTION_FAILURE
 * depending on the value byte 6 of the application data)
 */
static TD_ActionOutcome doAction(void *obj)
{
    DC_TestPUSTelecommand *This = DC_TESTPUSTELECOMMAND(obj);

    if (This->executionCounter < 255) {
         This->executionCounter++;
    } else {
         This->executionCounter = 0;
    }

    if (This->executionSuccess) {
        return ACTION_SUCCESS;
    } else {
        return ACTION_FAILURE;
    }
}

/**
 * Execute the execution check on the telecommand.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *      return executionCheckValue; </PRE>
 * The internal variable <code>executionCheckValue</code> is initialized
 * when the telecommand application data are loaded. Its value
 * can additionally be changed with method <code>setExecutionCheckValue</code>
 * @see #setExecutionCheckValue
 * @see CC_TelecommandManager#activate
 * @return the value of the internal variable <code>setExecutionCheckValue</code>
 */
static bool canExecute(void *obj)
{
    DC_TestPUSTelecommand *This = DC_TESTPUSTELECOMMAND(obj);
    return This->executionCheckValue;
}

/**
 * Execute the validity check on the telecommand.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *      return validityCheckValue; </PRE>
 * The internal variable <code>validityCheckValue</code> is initialized
 * when the telecommand application data are loaded. Its value
 * can be changed with method <code>setValidityCheckValue</code>
 * @see #setValidityCheckValue
 * @see CC_TelecommandManager#load
 * @return the value of the internal variable <code>setExecutionCheckValue</code>
 */
static bool isValid(void *obj)
{
    DC_TestPUSTelecommand *This = DC_TESTPUSTELECOMMAND(obj);
    return This->validityCheckValue;
}

/**
 * Return the validity check code for the telecommand.
 * This implementation returns a user-defined value that is initialized
 * when the telecommand application data are loaded and that can be 
 * set with method
 * <code>setValidityCheckCode</code>.
 * @see #setValidityCheckCode
 * @return the validity check code
 */
static TD_CheckCode getValidityCheckCode(const void *obj)
{
    DC_TestPUSTelecommand *This = DC_TESTPUSTELECOMMAND(obj);
    return This->validityCheckCode;
}

/**
 * Return the execution check code for the telecommand.
 * This implementation returns a user-defined value that is initialized
 * when the telecommand application data are loaded and that can be set with method
 * <code>setExecutionCheckCode</code>.
 * @see #setExecutionCheckCode
 * @return the validity check code
 */
static TD_CheckCode getExecutionCheckCode(const void *obj)
{
    DC_TestPUSTelecommand *This = DC_TESTPUSTELECOMMAND(obj);
    return This->executionCheckCode;
}

/**
 * Implementation of the raw data load service. This method would normally
 * be called by a telecommand loader to load the application data into the
 * the telecommand component. This method interprets the raw data as they are
 * loaded and uses them to initialize the internal variables of the telecommand
 * component. The expected layout of the application data is specified
 * in the class comment. 
 * @see #getNumberOfRawData
 * @param i the index of the raw telecommand data
 * @param d the raw data
 */
static void setRawData(void *obj, unsigned int i, unsigned char d)
{
    DC_TestPUSTelecommand *This = DC_TESTPUSTELECOMMAND(obj);

    assert(i < 6);
    assert((i == 0) || (i == (This->lasti+1))); // check that i argument increments by 1 in each call

    This->lasti = i;
    switch (i) {
        case 0:
            This->executionCounter = d;
            return;
        case 1:
             if (d > 0) {
                 This->executionCheckValue = true;
             } else {
                 This->executionCheckValue = false;
             }
             return;
        case 2:
             if (d > 0) {
                 This->validityCheckValue = true;
             } else {
                 This->validityCheckValue = false;
             }
             return;
        case 3:
            This->executionCheckCode = d;
            return;
        case 4:
            This->validityCheckCode = d;
            return;
        case 5:
             if (d > 0) {
                 This->executionSuccess = true;
             } else {
                 This->executionSuccess = false;
             }
             return;
    }
}

/**
 * Return the number of raw data bytes that can be loaded with the
 * raw telecommand data load service.
 * Since the size of the application data for this telecommand is fixed and equal
 * to six, 
 * this method always returns the value of six.
 * @see #setRawData
 * @return alwys returns the value 6
 */
static unsigned int getNumberOfRawData(const void *obj)
{
    return 6;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
   DC_TestPUSTelecommand *This = DC_TESTPUSTELECOMMAND(obj);
   This->executionSuccess = 0;
   This->executionCounter = 0; 
   This->executionCheckValue = TC_CAN_EXECUTE;
   This->validityCheckValue = VALID;
   This->executionCheckCode = 0;
   This->validityCheckCode = 0;
   This->lasti = 0;

   TelecommandClass *tcc = TELECOMMAND_GET_CLASS(obj);
   tcc->setType(obj, PUS_TYPE_TEST);
   tcc->setSubType(obj, PUS_ST_TC_TEST);

   CC_RootObject_setClassId((CC_RootObject*)obj, ID_TESTPUSTELECOMMAND);
}

DC_TestPUSTelecommand* DC_TestPUSTelecommand_new(void)
{
    Object *obj = object_new(TYPE_DC_TESTPUSTELECOMMAND);
    return (DC_TestPUSTelecommand*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    TelecommandClass *tcc = TELECOMMAND_CLASS(oc);
    tcc->canExecute = canExecute;
    tcc->isValid = isValid;
    tcc->getValidityCheckCode = getValidityCheckCode;
    tcc->getExecutionCheckCode = getExecutionCheckCode;
    tcc->setRawData = setRawData;
    tcc->getNumberOfRawData = getNumberOfRawData;

    PunctualActionClass *pac = PUNCTUALACTION_CLASS(oc);
    pac->doAction = doAction;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_TESTPUSTELECOMMAND,
    .parent = TYPE_PUSTELECOMMAND,
    .instance_size = sizeof(DC_TestPUSTelecommand),
    .abstract = false,
    .class_size = sizeof(DC_TestPUSTelecommandClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_TestPUSTelecommand_register(void)
{
    type_register_static(&type_info);
}
