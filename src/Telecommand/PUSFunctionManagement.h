//
//
// PUSFunctionManagement.h
//


#ifndef PUSFUNCTIONMANAGEMENT_H
#define PUSFUNCTIONMANAGEMENT_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "PUSTelecommand.h"
#include "../Qom/object.h"


/*
 * PUS telecommand to implementing the PUS function management service(PUS service
 * number 8). This is an abstract class since the function implementation service
 * is application specific. This class defines a PUS telecommand with type equal to
 * 8 and subtype equal to 1. No other attributes or services are added to those provided
 * by the <code>PUSTelecommand</code> superclass. 
 * <p>
 * The function management service defines a mechanism for passing parameters to the
 * function that the telecommand manages. This mechanism is already covered by the
 * <i>raw data load</i> mechanism defined by the <code>PUSTelecommand</code> superclass.
 * @todo Can a generic way be found to handle the execution of some action as a function
 * of the "function ID field" in the telecommand packet?
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_PUSFUNCTIONMANAGEMENT "pusfunctionmanagement"

void PUSFunctionManagement_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct PUSFunctionManagement {
    PUSTelecommand parent;
};


struct PUSFunctionManagementClass {
    PUSTelecommandClass parent_class;
};


#define PUSFUNCTIONMANAGEMENT_GET_CLASS(obj) \
        OBJECT_GET_CLASS(PUSFunctionManagementClass, \
                                            obj, TYPE_PUSFUNCTIONMANAGEMENT)

#define PUSFUNCTIONMANAGEMENT_CLASS(klass) \
        OBJECT_CLASS_CHECK(PUSFunctionManagementClass, \
                                          klass, TYPE_PUSFUNCTIONMANAGEMENT)

#define PUSFUNCTIONMANAGEMENT(obj) \
        OBJECT_CHECK(PUSFunctionManagement, obj, TYPE_PUSFUNCTIONMANAGEMENT)


PUSFunctionManagement* PUSFunctionManagement_new(void);

#endif
