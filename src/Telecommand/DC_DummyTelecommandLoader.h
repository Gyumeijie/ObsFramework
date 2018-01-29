//
//
// DC_DummyTelecommandLoader.h
//


#ifndef DC_DUMMYTELECOMMANDLOADER_H
#define DC_DUMMYTELECOMMANDLOADER_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "TelecommandLoader.h"
#include "../Qom/object.h"


/*
 * Dummy telecommand loader that is useful for testing purposes.
 * This telecommand loader can be used to help test the functionalities
 * of the <code>TelecommandLoader</code> class and of the telecommand
 * manager component.
 * The dummy telecommand loader manages three <i>sample telecommands</i>.
 * These telecommands must be loaded when the dummy telecommand loader is
 * configured. When the telecommand loader is <i>activated</i>, it loads
 * one sample telecommand. The telecommand loader maintains an
 * <i>allocation counter</i> that records the number of telecommands that
 * are currently loaded in the telecommand manager associated to the
 * telecommand loader. The allocation counter is incremented by one
 * every time a telecommand is loaded into the telecommand manager and
 * it is decremented by one every time the telecommand manager sends a
 * <i>release</i> request to the telecommand loader.
 * @see DC_DummyTelecommand
 * @see CC_TelecommandManager
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_DUMMYTELECOMMANDLOADER "dc_dummytelecommandloader"

void DC_DummyTelecommandLoader_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_DummyTelecommandLoader {
    TelecommandLoader parent;

    unsigned int N_SAMPLE_TC;           // number of sample telecommands
    Telecommand **pSampleTelecommand;   // array holding sample telecommands
    unsigned int allocationCounter;
};


struct DC_DummyTelecommandLoaderClass {
    TelecommandLoaderClass parent_class;
};


#define DC_DUMMYTELECOMMANDLOADER_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_DummyTelecommandLoaderClass, \
                                                obj, TYPE_DC_DUMMYTELECOMMANDLOADER)

#define DC_DUMMYTELECOMMANDLOADER_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_DummyTelecommandLoaderClass, \
                                              klass, TYPE_DC_DUMMYTELECOMMANDLOADER)

#define DC_DUMMYTELECOMMANDLOADER(obj) \
        OBJECT_CHECK(DC_DummyTelecommandLoader, obj, TYPE_DC_DUMMYTELECOMMANDLOADER)


DC_DummyTelecommandLoader* DC_DummyTelecommandLoader_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Load the i-th sample telecommand. The maximum number of sample
 * telecommands that can be loaded is 3. The index i must lie in the
 * interval [0, 2]. No check is performed on the value of the index i
 * at run time.
 * @param i the sample telecommand index
 * @param pSampleTc the sample telecommand to be loaded in the i-th position
 */
void DC_DummyTelecommandLoader_setSampleTelecommand
(
    DC_DummyTelecommandLoader *This, 
    unsigned int i, 
    Telecommand *pSampleTc
);

/**
 * Getter method for allocation counter.
 * @return the allocation counter
 */
unsigned int DC_DummyTelecommandLoader_getAllocationCounter
(
    DC_DummyTelecommandLoader *This
);


#endif
