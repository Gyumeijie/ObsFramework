//
//
// PUSTelecommand.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "PUSTelecommand.h"


static const TD_TelecommandAck acceptanceAck = 1;
static const TD_TelecommandAck startAck = 2;
static const TD_TelecommandAck progressAck = 4;
static const TD_TelecommandAck completionAck = 8;



///////////////////////////////////////////////////////////////////////////////
//
//                            class data
//
///////////////////////////////////////////////////////////////////////////////

static TD_PUSPacketId packetId = 0;



///////////////////////////////////////////////////////////////////////////////
//
//                            class  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

TD_PUSPacketId PUSTelecommand_getPacketId(void)
{
    return packetId;
}

void PUSTelecommand_setApplicationId(TD_APID apid)
{
    assert(apid < (TD_APID)2048);
    packetId = 2048 + 4096;
    packetId = packetId + apid;
}



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void PUSTelecommand_setValidityCheckCode(PUSTelecommand *This, 
                                         TD_CheckCode valCheckCode)
{
    This->validityCheckCode = valCheckCode;
}

bool PUSTelecommand_isAcceptanceAckRequired(const PUSTelecommand *This)
{
    return ((This->ackLevel & acceptanceAck) > 0);
}

bool PUSTelecommand_isStartAckRequired(const PUSTelecommand *This)
{
    return ((This->ackLevel & startAck) > 0);
}

bool PUSTelecommand_isProgressAckRequired(const PUSTelecommand *This)
{
    return ((This->ackLevel & progressAck) > 0);
}

bool PUSTelecommand_isCompletionAckRequired(const PUSTelecommand *This)
{
    return ((This->ackLevel & completionAck) > 0);
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Execute the validity check on the telecommand.
 * This method returns "telecommand valid" if the validity check code
 * is equal to zero. The validity check code is computed in method 
 * <code>setRawData</code>.
 * @see #setValidityCheckCode
 * @return true if the telecommand is valid, false otherwise
 */
static bool isValid(void *obj)
{
    PUSTelecommand *This = PUSTELECOMMAND(obj);
    return (This->validityCheckCode == 0);
}

/**
 * Return the validity check code for the telecommand.
 * @see #setValidityCheckCode
 * @return the validity check code
 */
static TD_CheckCode getValidityCheckCode(const void *obj)
{
    PUSTelecommand *This = PUSTELECOMMAND(obj);
    return This->validityCheckCode;
}

/**
 * Getter method for the telecommand identifier. In this class, the
 * telecommand identifier is identified with the <i>packet sequence
 * control</i> PUS attribute.
 * @return the telecommand identifier
 */
static TD_TelecommandId getTelecommandId(const void *obj)
{
    PUSTelecommand *This = PUSTELECOMMAND(obj);

    assert(This->tcId > 0);
    return This->tcId;
}

/**
 * Setter method for the telecommand identifier.
 * @see #getTelecommandId
 * @param tcIdentifier the telecommand identifier
 */
static void setTelecommandId(void *obj, TD_TelecommandId tcIdentifier)
{
    PUSTelecommand *This = PUSTELECOMMAND(obj);

    assert(tcIdentifier > 0);
    This->tcId = tcIdentifier;
}

/**
 * Getter method for the telecommand type. In this class, the
 * telecommand type is identifed with the <i>telecommand service
 * type</i> PUS attribute.
 * @return the telecommand type
 */
static TD_TelecommandType getType(const void *obj)
{
    PUSTelecommand *This = PUSTELECOMMAND(obj);
    
    assert(This->tcType > 0);
    return This->tcType;
}

/**
 * Setter method for the telecommand type.
 * @see #getType
 * @param tcType the telecommand type
 */
static void setType(void *obj, TD_TelecommandType tcType)
{
    PUSTelecommand *This = PUSTELECOMMAND(obj);

    assert(tcType > 0);
    This->tcType = tcType;
}

/**
 * Getter method for the telecommand type. In this class, the
 * telecommand subtype is identifed with the <i>telecommand service
 * subtype</i> PUS attribute.
 * @return the telecommand subtype
 */
static TD_TelecommandSubType getSubType(const void *obj)
{
    PUSTelecommand *This = PUSTELECOMMAND(obj);

    assert(This->tcSubType>0);
    return This->tcSubType;
}

/**
 * Setter method for the telecommand subtype.
 * @see #getSubType
 * @param tcSubType the telecommand subtype
 */
static void setSubType(void *obj, TD_TelecommandSubType tcSubType)
{
    PUSTelecommand *This = PUSTELECOMMAND(obj);

    assert(tcSubType > 0);
    This->tcSubType = tcSubType;
}

/**
 * Getter method for the telecommand source.
 * @return the telecommand source
 */
static TD_TelecommandSource getSource(const void *obj)
{
    PUSTelecommand *This = PUSTELECOMMAND(obj);

    assert(This->tcSource > 0);
    return This->tcSource;
}

/**
 * Setter method for the telecommand source.
 * @see #getSource
 * @param tcSource the telecommand source
 */
static void setSource(void *obj, TD_TelecommandSource tcSrc)
{
    PUSTelecommand *This = PUSTELECOMMAND(obj);

    assert(tcSrc > 0);
    This->tcSource = tcSrc;
}

/**
 * Set the value of the acknowledge level for this telecommand.
 * The acknowledge level implements the PUS acknowledge field as
 * follows: <ul>
 * <li>Bit 0 represents the acceptance acknowledge flag</li>
 * <li>Bit 1 represents the start acknowledge flag</li>
 * <li>Bit 2 represents the progress acknowledge flag</li>
 * <li>Bit 3 represents the completion acknowledge flag</li>
 * </ul>
 * Bit 0 is the least-significant bit.
 * @see #getAcknowledgeLevel
 * @param ackLevel the new value of the acknowledge level attribute
 */
static void setAcknowledgeLevel(void *obj, TD_TelecommandAck ackLevel)
{
    PUSTelecommand *This = PUSTELECOMMAND(obj);
    This->ackLevel = ackLevel;
}

/**
 * Return the value of the acknowledge level attribute.
 * Note that methods are also provided to return the values of the
 * individual PUS acknowledge flags.
 * @see #setAcknowledgeLevel
 * @return the value of the acknowledge level attribute
 */
static TD_TelecommandAck getAcknowledgeLevel(const void *obj)
{
    PUSTelecommand *This = PUSTELECOMMAND(obj);
    return This->ackLevel;
}

/**
 * Perform a class-specific configuration check on the telecommand:
 * verify that the telecommand identifier, telecommand type, the
 * telecommand subtype, the telecommand source, and the packet identifier have a legal value.
 * @return true if the component is configured, false otherwise.
 */
static bool isObjectConfigured(void *obj)
{
   TelecommandClass *tc = GET_CLASS(TYPE_TELECOMMAND); 
   PUSTelecommand *This = PUSTELECOMMAND(obj);

   return ((CC_ROOTOBJECT_CLASS(tc)->isObjectConfigured(obj)) &&
           (This->tcType > 0) &&
           (This->tcSubType > 0) &&
           (This->tcSource > 0) &&
           (This->tcId > 0) &&
           (packetId > 0));
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    PUSTelecommand *This = PUSTELECOMMAND(obj);

    This->tcId = 0;
    This->tcType = 0;
    This->tcSubType = 0;
    This->tcSource = 0;
    This->ackLevel = 0;       // all flags set to false
    This->validityCheckCode = 0;
}

PUSTelecommand* PUSTelecommand_new(void)
{
    Object *obj = object_new(TYPE_PUSTELECOMMAND);
    return (PUSTelecommand*)obj;
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
    tc->getTelecommandId = getTelecommandId;
    tc->setTelecommandId = setTelecommandId;
    tc->getType = getType;
    tc->setType = setType;
    tc->getSubType = getSubType;
    tc->setSubType = setSubType;
    tc->getSource = getSource;
    tc->setSource = setSource;
    tc->setAcknowledgeLevel = setAcknowledgeLevel;
    tc->getAcknowledgeLevel = getAcknowledgeLevel;

    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_PUSTELECOMMAND,
    .parent = TYPE_TELECOMMAND,
    .instance_size = sizeof(PUSTelecommand),
    .abstract = false,
    .class_size = sizeof(PUSTelecommandClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void PUSTelecommand_register(void)
{
    type_register_static(&type_info);
}
