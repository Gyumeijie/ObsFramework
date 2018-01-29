//
//
// DC_DummyTracer.h
//


#ifndef DC_DUMMYTRACER_H
#define DC_DUMMYTRACER_H


#include "Tracer.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Qom/object.h"


/*
 * any external test set up. The dummy tracer can be useful either in a test
 * context or in an application where trace signals are not used. Note that
 * the <code>CC_RootObject</code> class requires a tracer component as one
 * of its plug-in components. This dummy tracer can be used where no physical
 * tracer component is available.
 * @see CC_RootObject
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_DUMMYTRACER "dc_dummytracer"

void DC_DummyTracer_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_DummyTracer {
    Tracer parent;
};


struct DC_DummyTracerClass {
    TracerClass parent_class;
};


#define DC_DUMMYTRACER_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_DummyTracerClass, obj, TYPE_DC_DUMMYTRACER)

#define DC_DUMMYTRACER_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_DummyTracerClass, klass, TYPE_DC_DUMMYTRACER)

#define DC_DUMMYTRACER(obj) \
        OBJECT_CHECK(DC_DummyTracer, obj, TYPE_DC_DUMMYTRACER)


DC_DummyTracer* DC_DummyTracer_new(void);

#endif
