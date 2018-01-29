//
//
// PUSTelecommand.h
//
//
// Change Record:


#ifndef PUSTELECOMMAND_H
#define PUSTELECOMMAND_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Telecommand/Telecommand.h"
#include "../Qom/object.h"


/*
 * Base class from which all PUS telecommand classes are derived.
 * This class implements the attributes defined by the more
 * generic <code>Telecommand</code> superclass in a manner that ensures compatibility with the
 * Packet Utilization Standard(PUS). Only the PUS attributes that are relevant to an
 * application process are modelled by this class.
 * <p>
 * The mapping between the attributes defined by the <code>Telecommand</code> superclass
 * and the attributes mandated by the PUS is as follows:<ul>
 * <li>The <i>packet ID</i> PUS attribute has a fixed value for all telecommands in the same
 * application process and it is therefore implemented as a static attribute.</li>
 * <li>The <i>packet sequence control</i> PUS attribute is mapped to the
 * <i>telecommand identifier</i> attribute of the <code>Telecommand</code> superclass.</li>
 * <li>The <i>acknowledge field</i> PUS attribute is mapped to the
 * <i>acknowledge level</i> attribute of the <code>Telecommand</code> superclass.</li>
 * <li>The <i>service type</i> PUS attributes is mapped to the
 * <i>telecommand type</i> attribute of the <code>Telecommand</code> superclass.</li>
 * <li>The <i>service subtype</i> PUS attributes is mapped to the
 * <i>telecommand subtype</i> attribute of the <code>Telecommand</code> superclass.</li>
 * <li>The <i>source</i> PUS attribute is mapped to the
 * <i>telecommand source</i> attribute of the <code>Telecommand</code> superclass.</li>
 * </ul>
 * The mapping of the PUS acknowledge flags onto the acknowledge level attribute is done in
 * a manner that is completely transparent to the clients of this class.
 * <p>
 * This class defines a default structure of the <i>telecommand validity check</i>. 
 * The class defines an internal variable to hold the value of the validity check 
 * code and initializes it to zero. A protected method is offered to set the value
 * of the validity check code. The vallidty check returns "telecommand is valid" if the
 * value of the validity check code is equal to zero. The idea is that validity checking 
 * in a PUS telecommand is done when its application data are loaded(using the
 * <i>raw data load service</i>). During the load operation, the telecommand interprets 
 * the data and checks their validity. If the data are found to be invalid, then
 * the validity check code is set to a non-zero value.
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 * @ingroup PUS
 * @ingroup Telecommand
 */
#define TYPE_PUSTELECOMMAND "pustelecommand"

void PUSTelecommand_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct PUSTelecommand {
    Telecommand parent;

    TD_TelecommandId tcId;
    TD_TelecommandType tcType;
    TD_TelecommandSubType tcSubType;
    TD_TelecommandSource tcSource;
    TD_TelecommandAck ackLevel;
    TD_CheckCode validityCheckCode;
};


struct PUSTelecommandClass {
    TelecommandClass parent_class;
};


#define PUSTELECOMMAND_GET_CLASS(obj) \
        OBJECT_GET_CLASS(PUSTelecommandClass, obj, TYPE_PUSTELECOMMAND)

#define PUSTELECOMMAND_CLASS(klass) \
        OBJECT_CLASS_CHECK(PUSTelecommandClass, klass, TYPE_PUSTELECOMMAND)

#define PUSTELECOMMAND(obj) \
        OBJECT_CHECK(PUSTelecommand, obj, TYPE_PUSTELECOMMAND)


PUSTelecommand* PUSTelecommand_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Getter method for the telecommand packet identifier. The telecommand packet
 * identifier is assumed to be fixed for all telecommands in the same
 * application process. According to the PUS, the packet identifier consists
 * of the following four fields: <ul>
 * <li>The version number: this field is fixed and equal to 0</li>
 * <li>The type: this field is fixed and equal to 1</li>
 * <li>The data field header: this field is fixed and equal to 1 (indicating
 * that a telecommand packet always has a secondary header)</li>
 * <li>The application ID: this field is fixed within the application process and
 * it is equal to the application identifier</li>
 * </ul>
 * @see #setApplicationId
 * @return the packet identifier
 */
TD_PUSPacketId PUSTelecommand_getPacketId(void);

/**
 * Setter method for the application PUSTelecommand_identifier(APID). The APID is used to construct
 * the telecommand packet identifier. The APID is placed in the 11 least-significant bits
 * of the PUS packet identifier. A pseudo-code implementation for this method is as
 * follows: <pre>
 *      packetId = 2**12+2**11;     // set the fixed part of the packet ID
 *      packetId = packetId + apid; // set the APID part of the packet ID </pre>
 * The APID should be smaller than 2**11.
 * @see getPacketId
 * @param apid the identifier of the application for which the telecommand is intended
 */
void PUSTelecommand_setApplicationId(TD_APID apid);



///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Setter method for the validity check code. This method would normally be called
 * by the data load PUSTelecommand_service(method <code>setRawData</code>) when it 
 * detects an inconsistency or some other
 * problem in the data being loaded. The value of the code indicates the
 * type of problem.
 * @param valCheckCode the validity check code
 */
void PUSTelecommand_setValidityCheckCode
(
    PUSTelecommand *This, 
    TD_CheckCode valCheckCode
);

/**
 * Return the true if acknowledgement of telecommand acceptance is
 * required. The return value is read from the acknowledge level attribute.
 * @see #setAcknowledgeLevel
 * @return the value of the acceptance acknowledge flag
 */
bool PUSTelecommand_isAcceptanceAckRequired(const PUSTelecommand *This);

/**
 * Return the true if acknowledgement of telecommand execution start is
 * required. The return value is read from the acknowledge level attribute.
 * @see #setAcknowledgeLevel
 * @return the value of the start acknowledge flag
 */
bool PUSTelecommand_isStartAckRequired(const PUSTelecommand *This);

/**
 * Return the true if acknowledgement of telecommand execution progress is
 * required. The return value is read from the acknowledge level attribute.
 * @see #setAcknowledgeLevel
 * @return the value of the progress acknowledge flag
 */
bool PUSTelecommand_isProgressAckRequired(const PUSTelecommand *This);

/**
 * Return the true if acknowledgement of telecommand execution completion is
 * required. The return value is read from the acknowledge level attribute.
 * @see #setAcknowledgeLevel
 * @return the value of the completion acknowledge flag
 */
bool PUSTelecommand_isCompletionAckRequired(const PUSTelecommand *This);


#endif
