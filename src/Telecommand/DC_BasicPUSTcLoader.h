//
//
// DC_BasicPUSTcLoader.h
//


#ifndef DC_BASICPUSTCLOADER_H
#define DC_BASICPUSTCLOADER_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "TelecommandLoader.h"
#include "../Qom/object.h"


/*
 * Telecommand loader for PUS telecommands that implements only basic
 * functionalities and checks.
 * This telecommand loader can handle one or more raw telecommand packets.
 * At the time it is activated, it assumes the packets to be placed in a
 * dedicated memory area(the <i>telecommand load area</i>) and assumes 
 * their layout to comply with the layout for telecommand packets stipulated
 * by the PUS. The packets are assumed to be placed in the telecommand area
 * in sequence, one after the other. The layout of the telecommand load area
 * is therefore assumed to be as follows. The first byte represents the
 * number of telecommand packets. Successive bytes represent the telecommand
 * packets stored in sequence and without gaps in between successive packets.
 * <p>
 * When the telecommand loader is 
 * activated, it accesses the telecommand load area and processes the 
 * telecommand packets one by one. For each packet, it retrieves the
 * telecommand type and subtype. It then asks the <i>telecommand 
 * factory</i> for a telecommand component of matching type, it configures 
 * it with the data in the telecommand load area, and finally loads the
 * newly configured component in the
 * telecommand manager. 
 * <p>
 * In a typical usage scenario, this component would be activated periodically
 * to process any telecommand packets that have been received in the previous
 * period. In an alternative scenario, the component is activated by an 
 * interrupt handler when reception of a new telecommand packet has been 
 * detected. Note however that the processing of a telecommand packet by
 * this component can be time-consuming and hence this alternative scenario
 * only is feasible if the time between successive telecommand interrupts
 * is sufficiently long.
 * <p>
 * This telecommand loader is configured with the starting address of
 * the telecommand load area(method <code>setTcLoadAreaStart</code>),
 * with the maximum length of a telecommand packet(method
 * <code>setMaxTcLength</code>), and with the maximum number of telecommand
 * packets that can be placed in the telecommand load area(method
 * <code>setMaxNumberOfTc</code>).
 * All configuration parameters can be changed dynamically. 
 * <p>
 * This telecommand loader does not perform any consistency or validity
 * checks on the raw telecommand data other than verifying that the length
 * of the telecommand packet is less than the maximum value set with method
 * <code>setMaxTcLength</code> and that the number of telecommands is less than
 * the maximum set with method <code>setMaxNumberOfTc</code>. 
 * @todo The implementation of method "activate" must be updated every time a new
 * PUS telecommand class is added to the framework
 * @see PUSTelecommand
 * @see CC_TelecommandManager
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_BASICPUSTCLOADER "dc_basicpustcloader"

void DC_BasicPUSTcLoader_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_BasicPUSTcLoader {
    TelecommandLoader parent;

    unsigned char *tcArea;              // start address of telecommand area
    unsigned int maxTcDataPacketLength; // max length in bytes of TC packet data field
    unsigned int maxNumberOfTc;         // max number of telecommand packets 
};


struct DC_BasicPUSTcLoaderClass {
    TelecommandLoaderClass parent_class;
};


#define DC_BASICPUSTCLOADER_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_BasicPUSTcLoaderClass, obj, TYPE_DC_BASICPUSTCLOADER)

#define DC_BASICPUSTCLOADER_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_BasicPUSTcLoaderClass, klass, TYPE_DC_BASICPUSTCLOADER)

#define DC_BASICPUSTCLOADER(obj) \
        OBJECT_CHECK(DC_BasicPUSTcLoader, obj, TYPE_DC_BASICPUSTCLOADER)


DC_BasicPUSTcLoader* DC_BasicPUSTcLoader_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the start address of the telecommand load area.
 * @param startAddress the start address
 */
void DC_BasicPUSTcLoader_setTcLoadAreaStart
(
    DC_BasicPUSTcLoader *This,
    unsigned char *startAddress
);

/**
 * Set the maximum length of a telecommand packet in number of bytes.
 * The value set here is the total length of the packet including its
 * header. Only values greater than 6 are DC_BasicPUSTcLoader_legal(a PUS header is 6 bytes
 * long).
 * @param maxTcLength the maximum length of a telecommand packet
 */
void DC_BasicPUSTcLoader_setMaxTcLength
(
    DC_BasicPUSTcLoader *This, 
    unsigned int maxTcLength
);

/**
 * Getter method for the maximum length of the a telecommand packet.
 * @return the maximum length of a telecommand packet
 */
unsigned int DC_BasicPUSTcLoader_getMaxTcLength
(
    const DC_BasicPUSTcLoader *This
);

/**
 * Set the maximum number of telecommand packets that can be handled by this
 * component in an activation cycle.
 * @param max the maximum number of telecommands
 */
void DC_BasicPUSTcLoader_setMaxNumberOfTc
(
    DC_BasicPUSTcLoader *This, 
    unsigned int max
);

/**
 * Getter method for the maximum number of telecommand packets that can be handled by this
 * component in an activation cycle.
 * @return the maximum number of telecommands
 */
unsigned int DC_BasicPUSTcLoader_getMaxNumberOfTc
(
    const DC_BasicPUSTcLoader *This
);


#endif
