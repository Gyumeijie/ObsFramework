//
//
// Telecommand.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "Telecommand.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

TD_ObsTime Telecommand_getTimeTag(const Telecommand *This)
{
    return This->timeTag;
}

void Telecommand_setTimeTag(Telecommand *This, TD_ObsTime timeTag)
{
    This->timeTag = timeTag;
}

void Telecommand_setInUse(Telecommand *This, bool newInUse)
{
    This->inUse = newInUse;
}

bool Telecommand_isInUse(const Telecommand *This)
{
    return This->inUse;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Execute the validity check on the telecommand.
 * This class provides a default implementation that returns "telecommand is
 * valid".
 * Subclasses may introduce more complex validity checks(e.g. checksum checks).
 * @see CC_TelecommandManager#activate
 * @return true if the telecommand is valid, false otherwise
 */
static bool isValid(void *obj)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);

    assert(cc_roc->isObjectConfigured(obj));
    return VALID;
}

/**
 * Return the validity check code for the telecommand.
 * The validity check code allows a telecommand to make information available about
 * the reasons for the failure of the validity check. The return value of this
 * method is only valid if the validity check has returned "telecommand not
 * valid" (ie. if method <code>isValid</code> has returned false). This class
 * provides a default implementation that returns zero.
 * @see #isValid
 * @return the validity check code
 */
static TD_CheckCode getValidityCheckCode(const void *obj)
{
    return 0;
}

/**
 * Perform the execution check on the telecommand.
 * This class provides a default implementation that always return "telecommand
 * can execute".
 * @see CC_TelecommandManager#activate
 * @return true if the telecommand can safely execute, false otherwise
 */
static bool canExecute(void *obj)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);

    assert(cc_roc->isObjectConfigured(obj));
    return TC_CAN_EXECUTE;
}

/**
 * Return the execution check code for the telecommand.
 * The execution check code allows a telecommand to make information available about
 * the reasons for the failure of the execution check. The return value of this
 * method is only valid if the execution check has returned "telecommand cannot
 * execute" (ie. if method <code>canExecute</code> has returned false). This class
 * provides a default implementation that returns zero.
 * @see #isValid
 * @return the validity check code
 */
static TD_CheckCode getExecutionCheckCode(const void *obj)
{
    return 0;
}

/**
 * Getter method for the telecommand identifier. This class implements the
 * the telecommand identifier to coincide with the instance identifier.
 * Note that this assumes that the type of the instance identifier
 * (TD_InstanceId) is assignment-compatible with the type of the 
 * telecommand identifier(TD_TelecommandId).
 * A pseudo-code implementation of this method therefore is:<pre>
 *      return getInstanceId(void);</pre>
 * @return the telecommand identifier
 */
static TD_TelecommandId getTelecommandId(const void *obj)
{
    return CC_RootObject_getInstanceId(obj);
}

/**
 * Setter method for the telecommand identifier. Since this class
 * identifies the telecommand identifier with the instance identifier
 * (see <code>CC_RootObject</code>), this method is implemented as
 * a dummy method that returns without taking any action.
 * @see #getTelecommandId
 * @param tcIdentifier the telecommand identifier
 */
static void setTelecommandId(void *obj, TD_TelecommandId tcIdentifier)
{
    return;
}

/**
 * Getter method for the telecommand type. This class implements 
 * the telecommand type to coincide with the least significant
 * byte of the class identifier.
 * A pseudo-code implementation of this method therefore is:<pre>
 *      return(TD_TelecommandType)(getClassId(void) mod 256);</pre>
 * @return the telecommand type
 */
static TD_TelecommandType getType(const void *obj)
{
    return (TD_TelecommandType)(CC_RootObject_getClassId(obj)%256);
}

/**
 * Setter method for the telecommand type. Since this class
 * identifies the telecommand type with the class identifier
 * (see <code>CC_RootObject</code>), this method is implemented as
 * a dummy method that returns without taking any action.
 * @see #getType
 * @param tcType the telecommand type
 */
static void setType(void *obj, TD_TelecommandType tcType)
{
    return;
}

/**
 * Getter method for the telecommand sub-type. This class does not model
 * the telecommand sub-type. This method always returns zero.
 * @return the telecommand sub-type
 */
static TD_TelecommandSubType getSubType(const void *obj)
{
    return 0;
}

/**
 * Setter method for the telecommand sub-type. Since this class
 * does not model the telecommand sub-type, this method is implemented as
 * a dummy method that returns without taking any action.
 * @see #getTelecommandsubType
 * @param tcSubType the telecommand sub-type
 */
static void setSubType(void *obj, TD_TelecommandSubType tcSubType)
{
    return;
}

/**
 * Getter method for the telecommand source. This class does not model
 * the telecommand source. This method always returns zero.
 * @return the telecommand source
 */
static TD_TelecommandSource getSource(const void *obj)
{
    return 0;
}

/**
 * Setter method for the telecommand source. Since this class
 * does not model the telecommand source, this method is implemented as
 * a dummy method that returns without taking any action.
 * @see #getSource
 * @param tcSource the telecommand source
 */
static void setSource(void *obj, TD_TelecommandSource tcSource)
{
    return;
}

/**
 * Implementation of the raw data load service. This method would normally
 * be called by a telecommand loader to load the i-th byte into the
 * telecommand component. The telecommand component uses the data that it
 * receives from the telecommand loader to configure its internal data
 * structures. The index i should lie in an interval [0, N-1] where N is
 * the return value of method <code>getNumberOfRawData</code>.
 * This implementation of the raw data load service is safe(unlike
 * its alternative <code>setRawData(unsigned char*, unsigned int)</code>, 
 * it does not give access to the internal data of the
 * caller) but can be inefficient because it requires the caller to pass
 * the telecommand configuration bytes one by one through dedicated calls
 * to a virtual method.
 * <p>
 * This class provides a default implementation that does nothing and
 * should never be called.
 * @see getNumberOfRawData
 * @param i the index of the raw telecommand data
 * @param d the raw data
 */
static void setRawData(void *obj, unsigned int i, unsigned char d)
{
    assert(false);
    return;
}

/**
 * Return the number of raw data bytes that can be loaded with the
 * raw telecommand data load service <code>setRawData(unsigned int, 
 * unsigned char)</code>.
 * This class provides a default implementation that returns zero.
 * @see #setRawData
 * @return the number of raw data bytes to be loaded with the raw
 * data load service
 */
static unsigned int getNumberOfRawData(const void *obj)
{
    return 0;
}

/**
 * Implementation of the raw data load service. This method would normally
 * be called by a telecommand loader to load the configuration data for the
 * telecommand as a single array of bytes. The telecommand component uses the 
 * data in the array to configure its internal data
 * structures. 
 * This implementation of the raw data load service is efficient(unlike
 * its alternative <code>setRawData(unsigned int, unsigned char)</code>)
 * but is unsafe because it forces the caller to give access to its interal
 * data structures to the telecommand component.
 * <p>
 * This class provides a default implementation that does nothing and
 * should never be called.
 * @param i the number data in the d array
 * @param d the array holding the raw data
 */
static void setRawDataFastly(void *obj, unsigned char *d, unsigned int i)
{
	assert(false);
	return;
}

/**
 * Set the value of the acknowledge level for this telecommand.
 * This class does not implement the acknowledge level and
 * this method therefore returns without taking any action.
 * @see #getAcknowledgeLevel
 * @param ackLevel the new value of the acknowledge level attribute
 */
static void setAcknowledgeLevel(void *obj, TD_TelecommandAck ackLevel)
{
    return;
}

/**
 * Return the value of the acknowledge level.
 * This class does not implement the acknowledge level and
 * this method always returns a default and fixed value of zero.
 * @see #setAcknowledgeLevel
 * @return the value of the acknowledge level attribute
 */
static TD_TelecommandAck getAcknowledgeLevel(const void *obj)
{
    return 0;
}

/**
 * Perform a class-specific configuration check on the telecommand:
 * verify that the time tag has a legal value.
 * @return true if the component is configured, false otherwise.
 */
static bool isObjectConfigured(void *obj)
{
   PunctualActionClass *pac = GET_CLASS(TYPE_PUNCTUALACTION);
   Telecommand *This = TELECOMMAND(obj);

   return ((CC_ROOTOBJECT_CLASS(pac)->isObjectConfigured(obj)) && 
           (This->timeTag >= 0));

}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    Telecommand *This = TELECOMMAND(obj);

    This->timeTag = -1;
    This->inUse = false;
}

Telecommand* Telecommand_new(void)
{
    Object *obj = object_new(TYPE_TELECOMMAND);
    return (Telecommand*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    TelecommandClass *tc = TELECOMMAND_CLASS(oc);
    tc->isValid = isValid;
    tc->getValidityCheckCode = getValidityCheckCode;
    tc->canExecute = canExecute;
    tc->getExecutionCheckCode = getExecutionCheckCode;
    tc->getTelecommandId = getTelecommandId;
    tc->setTelecommandId = setTelecommandId;
    tc->getType = getType;
    tc->setType = setType;
    tc->getSubType = getSubType;
    tc->setSubType = setSubType;
    tc->getSource = getSource;
    tc->setSource = setSource;
    tc->setRawData = setRawData;
    tc->getNumberOfRawData = getNumberOfRawData;
    tc->setRawDataFastly = setRawDataFastly;
    tc->setAcknowledgeLevel = setAcknowledgeLevel;
    tc->getAcknowledgeLevel = getAcknowledgeLevel;

    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_TELECOMMAND,
    .parent = TYPE_PUNCTUALACTION,
    .instance_size = sizeof(Telecommand),
    .abstract = false,
    .class_size = sizeof(TelecommandClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void Telecommand_register(void)
{
    type_register_static(&type_info);
}
