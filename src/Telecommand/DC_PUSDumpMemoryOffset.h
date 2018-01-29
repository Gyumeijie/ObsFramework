//
//
// DC_PUSDumpMemoryOffset.h
//


#ifndef DC_PUSDUMPMEMORYOFFSET_H
#define DC_PUSDUMPMEMORYOFFSET_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "PUSDumpMemory.h"
#include "../Qom/object.h"


/*
 * PUS telecommand to set up a memory dump with base plus offset.
 * This class encapsulates the PUS service type 6, subtype 3.
 * This class adds to its base class the implementation of the execution
 * action. Execution of this telecommand consists in retrieving a free telemetry packet
 * of type <code>DC_PUSMemoryDumpOffset</code> from the telemetry packet factory, 
 * configuring it with the application
 * data and sending it to the telemetry manager for immediate dispatch. The telemetry 
 * manager is loaded as a plug-in component at configuration time. Execution can have 
 * two outcomes. 
 * The telecommand
 * can have a successful outcome(the return value of <code>doAction</code>
 * is ACTION_SUCCESS) or it can fail for the following reasons:
 * <ul>
 * <li>No free packet could be found in the
 * telemetry packet factory(the return value of <code>doAction</code>
 * is PACKET_NOT_FOUND)   </li>
 * <li>The packet could not be loaded in the
 * telemetry manager(the return value of <code>doAction</code>
 * is TM_MAN_QUEUE_FULL)   </li>
 * <li>The internal structure of the application data was found to be 
 * inconsistent(the return value of <code>doAction</code>
 * is APP_DATA_INCONSISTENT)   </li>
 * </ul> . 
 * No event reports are generated in case of failure as it is assumed that
 * this is done by the calling client.
 * @see DC_PUSMemoryDumpOffset
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_PUSDUMPMEMORYOFFSET "dc_pusdumpmemoryoffset"

void DC_PUSDumpMemoryOffset_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_PUSDumpMemoryOffset {
    PUSDumpMemory parent;
};


struct DC_PUSDumpMemoryOffsetClass {
    PUSDumpMemoryClass parent_class;
};


#define DC_PUSDUMPMEMORYOFFSET_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_PUSDumpMemoryOffsetClass, \
                                             obj, TYPE_DC_PUSDUMPMEMORYOFFSET)

#define DC_PUSDUMPMEMORYOFFSET_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_PUSDumpMemoryOffsetClass, \
                                           klass, TYPE_DC_PUSDUMPMEMORYOFFSET)

#define DC_PUSDUMPMEMORYOFFSET(obj) \
        OBJECT_CHECK(DC_PUSDumpMemoryOffset, obj, TYPE_DC_PUSDUMPMEMORYOFFSET)


DC_PUSDumpMemoryOffset* DC_PUSDumpMemoryOffset_new(void);

#endif
