//
//
// DC_DummyPUSTelecommand.h
//


#ifndef DC_DUMMYPUSTELECOMMAND_H
#define DC_DUMMYPUSTELECOMMAND_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "PUSTelecommand.h"
#include "../Qom/object.h"


/*
 * Dummy PUS telecommand that increments a counter every time it is 
 * executed. This telecommand is useful for testing purposes.
 * The values of the telecommand packet attributes are initialized 
 * to: <ul>
 * <li>The telecommand identifier is set to TEST_TC_ID</li>
 * <li>The telecommand type is set to TEST_TC_TYPE</li>
 * <li>The telecommand subtype is set to TEST_TC_SUBTYPE</li>
 * <li>The telecommand source is set to TEST_TC_SOURCE</li>
 * <li>The telecommand acknowledge level is set to indicate "no acknoledge is required"</li>
 * </ul>
 * The constants are defined in file <code>TestConstants.h</code>.
 * Note that the APID of the process
 * receiving the telecommands does not need to be set because it is
 * a static field that should be set during the test set up process.
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_DUMMYPUSTELECOMMAND "dc_dummypustelecommand"

void DC_DummyPUSTelecommand_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_DummyPUSTelecommand {
    PUSTelecommand parent;

    unsigned int executionCounter; 
};


struct DC_DummyPUSTelecommandClass {
    PUSTelecommandClass parent_class;
};


#define DC_DUMMYPUSTELECOMMAND_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_DummyPUSTelecommandClass, \
                                             obj, TYPE_DC_DUMMYPUSTELECOMMAND)

#define DC_DUMMYPUSTELECOMMAND_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_DummyPUSTelecommandClass, \
                                           klass, TYPE_DC_DUMMYPUSTELECOMMAND)

#define DC_DUMMYPUSTELECOMMAND(obj) \
        OBJECT_CHECK(DC_DummyPUSTelecommand, obj, TYPE_DC_DUMMYPUSTELECOMMAND)


DC_DummyPUSTelecommand* DC_DummyPUSTelecommand_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Getter method for the execution counter.
 * @return the execution counter
 */
unsigned int DC_DummyPUSTelecommand_getExecutionCounter(DC_DummyPUSTelecommand *This);


#endif
