//
//
// DC_DummyPUSTelemetryPacket.cpp
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/TestConstants.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../Telecommand/PUSTelecommand.h"
#include "../Telemetry/PUSTelemetryPacket.h"
#include "../Telemetry/DC_PUSTcVerificationPacket.h"

#include <string.h>



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

TD_CheckCode DC_PUSTcVerificationPacket_getErrorCode
(
    DC_PUSTcVerificationPacket *This
)
{
    TD_CheckCode temp;
    memcpy(&temp, This->tmByte + sizeof(TD_PUSPacketId) + sizeof(TD_TelecommandId),
           sizeof(TD_CheckCode));
    return temp;
}

void DC_PUSTcVerificationPacket_setErrorCode
(
    DC_PUSTcVerificationPacket *This, 
    TD_CheckCode errCode
)
{
    assert(errCode > 0);
    memcpy(This->tmByte + sizeof(TD_PUSPacketId) + sizeof(TD_TelecommandId),
           &errCode, sizeof(TD_CheckCode));
}

TD_TelecommandId DC_PUSTcVerificationPacket_getTelecommandId
(
    DC_PUSTcVerificationPacket *This
)
{
    TD_TelecommandId temp;
    memcpy(&temp, This->tmByte + sizeof(TD_PUSPacketId), sizeof(TD_TelecommandId));
    return temp;
}

void DC_PUSTcVerificationPacket_setTelecommandId
(
    DC_PUSTcVerificationPacket *This, 
    TD_TelecommandId tcId
)
{
    assert(tcId>0);
    memcpy(This->tmByte + sizeof(TD_PUSPacketId), &tcId, sizeof(TD_TelecommandId));
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Return the number of bytes managed by this telemetry packet.
 * The number of bytes is computed as follows. If the telemetry packet
 * is being used to report a successful telecommand execution, then its
 * number of bytes is given by: <pre>
 *      sizeof(TD_PUSPacketId)+sizeof(TD_TelecommandId) </pre>
 * If the telemetry packet
 * is being used to report a successful telecommand execution, then its
 * number of bytes is given by: <pre>
 *      sizeof(TD_PUSPacketId)+sizeof(TD_TelecommandId)+sizeof(TD_CheckCode) </pre>
 * Note that <code>TD_CheckCode</code> is the type of the error code field.
 * @see #setErrorCode
 * @return number of bytes in this telemetry packet
 */
static unsigned int getNumberOfBytes(void *obj)
{
    DC_PUSTcVerificationPacket *This = DC_PUSTCVERIFICATIONPACKET(obj);
    TelemetryPacketClass *tpc = TELEMETRYPACKET_GET_CLASS(obj);

    assert(tpc->getSubType(This) != 0);

    TD_TelecommandSubType tcSubType = tpc->getSubType(This);
    if ((tcSubType == PUS_ST_TC_VER_ACC_SC) ||
        (tcSubType == PUS_ST_TC_EXE_STR_SC) ||
        (tcSubType == PUS_ST_TC_EXE_PRO_SC) ||
        (tcSubType == PUS_ST_TC_EXE_END_SC)) {
         return This->packetLengthSuccess;
    } else {
         return This->packetLengthFailure;
    }
}

/**
 * Implement the  <i>data acquisition service</i> for the PUS telecommand verification
 * packet. The bytes associated to this telemetry packet are returned according to the
 * following algorithm: <pre>
 *      if((subtype == PUS_ST_TC_VER_ACC_SC) ||
 *           (subtype == PUS_ST_TC_EXE_STR_SC) ||
 *           (subtype == PUS_ST_TC_EXE_PRO_SC) ||
 *           (subtype == PUS_ST_TC_EXE_END_SC)) {
 *          return TC packet ID;
 *          return TC packet sequence control;
 *       } else {
 *          return TC packet ID;
 *          return TC packet sequence control;
 *          return error code;
 *       } </pre>
 * The TC packet ID, TC packet sequence control, and the error code are transferred byte
 * by byte starting from the byte with the highest address.
 * @return value of n-th telemetry byte
 * @param n the telemetry byte to be returned(starting with byte 0)
 */
static unsigned char getUnsignedByte(void *obj, unsigned int n)
{
    DC_PUSTcVerificationPacket *This = DC_PUSTCVERIFICATIONPACKET(obj);
    return This->tmByte[n];
}

/**
 * Implement the <i>data update service</i> for the PUS telecommand verification packet.
 * This type of packet is configured dynamically by the component that monitors the
 * execution status of the telecommands. Its update service is therefore implemented
 * as a dummy method that returns without taking any action.
 */
static void update(void *obj)
{
    return;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    DC_PUSTcVerificationPacket *This = DC_PUSTCVERIFICATIONPACKET(obj);
    TelemetryPacketClass *tpc = TELEMETRYPACKET_GET_CLASS(obj);

    This->packetLengthSuccess = sizeof(TD_PUSPacketId) + sizeof(TD_TelecommandId);
    This->packetLengthFailure = sizeof(TD_PUSPacketId) +
                                sizeof(TD_TelecommandId) + sizeof(TD_CheckCode);
    This->tmByte = g_malloc(sizeof(unsigned char)*This->packetLengthFailure);

    tpc->setType(obj, PUS_TYPE_TC_VER);

    // The PUS packet identifier, the telecommand identifier and the error
    // code are stored in the tmByte array

    // set the PUS packet identifier
    TD_PUSPacketId pidTemp = PUSTelecommand_getPacketId();
    memcpy(This->tmByte, &pidTemp, sizeof(TD_PUSPacketId));

    // initialize the telecommand identifier
    TD_TelecommandId tcidTemp = 0;
    memcpy(This->tmByte + sizeof(TD_PUSPacketId), &tcidTemp, sizeof(TD_TelecommandId));

    // initialize the error code
    TD_CheckCode ccTemp = 0;
    memcpy(This->tmByte + sizeof(TD_PUSPacketId) + sizeof(TD_TelecommandId),
           &ccTemp, sizeof(TD_CheckCode));


    CC_RootObject_setClassId((CC_RootObject*)obj, ID_PUSTCVERIFICATIONPACKET);
}

DC_PUSTcVerificationPacket* DC_PUSTcVerificationPacket_new(void)
{
    Object *obj = object_new(TYPE_DC_PUSTCVERIFICATIONPACKET);
    return (DC_PUSTcVerificationPacket*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    TelemetryPacketClass *tpc = TELEMETRYPACKET_CLASS(oc);

    tpc->getNumberOfBytes = getNumberOfBytes;
    tpc->getUnsignedByte = getUnsignedByte;
    tpc->update = update;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_PUSTCVERIFICATIONPACKET,
    .parent = TYPE_PUSTELEMETRYPACKET,
    .instance_size = sizeof(DC_PUSTcVerificationPacket),
    .abstract = false,
    .class_size = sizeof(DC_PUSTcVerificationPacketClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_PUSTcVerificationPacket_register(void)
{
    type_register_static(&type_info);
}
