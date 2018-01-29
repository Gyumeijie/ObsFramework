//
//
// DC_DummyTelemetryStream.h
//


#ifndef DC_DUMMYTELEMETRYSTREAM_H
#define DC_DUMMYTELEMETRYSTREAM_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "TelemetryStream.h"
#include "../Qom/object.h"


/*
 * Dummy implementation of the <code>TelemetryStream</code> interface
 * useful for testing purposes.
 * This class uses the default implementations provided by the super class and provides
 * a dummy implementation of its only pure virtual method <code>write</code>.
 * @author Roberto Totaro
 * @version 1.0
 */
#define TYPE_DC_DUMMYTELEMETRYSTREAM "dc_dummytelemetrystream"

void DC_DummyTelemetryStream_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_DummyTelemetryStream {
    TelemetryStream parent;
};


struct DC_DummyTelemetryStreamClass {
    TelemetryStreamClass parent_class;
};


#define DC_DUMMYTELEMETRYSTREAM_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_DummyTelemetryStreamClass, \
                                             obj, TYPE_DC_DUMMYTELEMETRYSTREAM)

#define DC_DUMMYTELEMETRYSTREAM_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_DummyTelemetryStreamClass, \
                                           klass, TYPE_DC_DUMMYTELEMETRYSTREAM)

#define DC_DUMMYTELEMETRYSTREAM(obj) \
        OBJECT_CHECK(DC_DummyTelemetryStream, \
                                             obj, TYPE_DC_DUMMYTELEMETRYSTREAM)


DC_DummyTelemetryStream* DC_DummyTelemetryStream_new(void);

#endif
