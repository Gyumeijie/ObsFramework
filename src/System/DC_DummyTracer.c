//
//
// DC_DummyTracer.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "DC_DummyTracer.h"



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * This is a dummy method that returns without taking any action
 * @see Tracer#sendRawTrace
 * @param traceItem the trace item to be sent to the test set-up
 */
static void sendRawTrace(const void *obj, TD_TraceItem traceItem)
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
   TRACER_GET_CLASS(obj)->setEnabled((Tracer*)obj, DISABLED);
   CC_RootObject_setClassId((CC_RootObject*)obj, ID_DUMMYTRACER);
}

DC_DummyTracer* DC_DummyTracer_new(void)
{
    return (DC_DummyTracer*)object_new(TYPE_DC_DUMMYTRACER);
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    DC_DummyTracerClass *dc_dtc = DC_DUMMYTRACER_CLASS(oc);

    TracerClass *tc = TRACER_CLASS(oc);
    tc->sendRawTrace = sendRawTrace;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_DUMMYTRACER,
    .parent = TYPE_TRACER,
    .instance_size = sizeof(DC_DummyTracer),
    .abstract = false,
    .class_size = sizeof(DC_DummyTracerClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_DummyTracer_register(void)
{
    type_register_static(&type_info);
}
