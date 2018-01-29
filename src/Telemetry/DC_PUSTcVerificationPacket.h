//
//
// DC_PUSTcVerificationPacket.h
//


#ifndef DC_PUSTCVERIFICATIONPACKET_H
#define DC_PUSTCVERIFICATIONPACKET_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Telemetry/PUSTelemetryPacket.h"
#include "../Qom/object.h"


/*
 * PUS telemetry packet implementing the telecommand verification service.
 * This class can model any of the telecommand verification service
 * packets. The value of the subtype attribute determines which packet is
 * being modeled.
 * <p>
 * This class is intended to be used by a component that monitors
 * the execution status of a telecommand. Upon detecting a change in
 * the execution status of a telecommand, this component configures an
 * instance of <code>PUSTcVerificationPacket</code> in accordance with the
 * detected state of the telecommand execution. The <code>PUSTcVerificationPacket</code>
 * instance should then be loaded into the <i>telementry manager</i> for immediate
 * dispatch to the telemetry channel.
 * <p>
 * A telemetry packet of type <code>PUSTcVerificationPacket</code> can contain two or
 * three fields. It contains two fields if it reports a telecommand success. It contains three fields
 * if it reports a telecommand failure. The two fields that are always present are
 * the packet identifier of the telecommand and the packet sequence control of the telecommand.
 * The third field is a single error code that conveys information about the reason of
 * the telecommand failure.
 * @todo construct a test case for this class.
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_PUSTCVERIFICATIONPACKET "dc_pustcverificationpacket"

void DC_PUSTcVerificationPacket_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_PUSTcVerificationPacket {
    PUSTelemetryPacket parent;

    unsigned int packetLengthSuccess;
    unsigned int packetLengthFailure;
    unsigned char *tmByte;
};


struct DC_PUSTcVerificationPacketClass {
    PUSTelemetryPacketClass parent_class;
};


#define DC_PUSTCVERIFICATIONPACKET_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_PUSTcVerificationPacketClass, \
                                          obj, TYPE_DC_PUSTCVERIFICATIONPACKET)

#define DC_PUSTCVERIFICATIONPACKET_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_PUSTcVerificationPacketClass, \
                                        klass, TYPE_DC_PUSTCVERIFICATIONPACKET)

#define DC_PUSTCVERIFICATIONPACKET(obj) \
        OBJECT_CHECK(DC_PUSTcVerificationPacket, \
                                          obj, TYPE_DC_PUSTCVERIFICATIONPACKET)


DC_PUSTcVerificationPacket* DC_PUSTcVerificationPacket_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Return the error code that describes the reason for the telecommand failure.
 * This field is only meaningful when the telemetry packet is being used to
 * describe a telecommand failure. The default value of the error code is zero.
 * @return the error code
 */
TD_CheckCode DC_PUSTcVerificationPacket_getErrorCode
(
    DC_PUSTcVerificationPacket *This
);

/**
 * Set the error code that describes the reason for the telecommand failure.
 * @see #getErrorCode
 * @param errCode the error code
 */
void DC_PUSTcVerificationPacket_setErrorCode
(
    DC_PUSTcVerificationPacket *This, 
    TD_CheckCode errCode
);

/**
 * Return the identifier of the telecommand for which the execution verification
 * report is constructed.
 * @return the telecommand identifier
 */
TD_TelecommandId DC_PUSTcVerificationPacket_getTelecommandId
(
    DC_PUSTcVerificationPacket *This
);

/**
 * Set the identifier of the telecommand for which the execution verification
 * report is constructed.
 * @param tcId the telecommand identifier
 */
void DC_PUSTcVerificationPacket_setTelecommandId
(
    DC_PUSTcVerificationPacket *This, TD_TelecommandId tcId
);


#endif
