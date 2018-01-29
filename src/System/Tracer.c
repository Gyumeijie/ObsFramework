//
//
// Tracer.cpp
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "Tracer.h"


///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) implementation
//
///////////////////////////////////////////////////////////////////////////////

bool Tracer_isEnabled(const Tracer *This)
{
   return This->enabledStatus;
}

/**
 * Send a Synch trace signal if the tracer is enabled.
 * If the tracer is disabled, the method call has no effect.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *    if ( isEnabled() )
 *    {  sendRawTrace(traceId);
 *    } </PRE>
 * The <CODE>sendRawTrace()</CODE> method is abstract and encapsulates
 * the implementation of the raw trace signal
 * sending.
 * Thus, this class enforces the management of the enabled status but
 * delegates implementation of
 * the sending mechanism to
 * derived classes implementing concrete tracers.
 * @param traceId the trace identifier
 */
void Tracer_sendSynchTrace(const Tracer *This, TD_TraceItem traceId)
{
   if (Tracer_isEnabled(This)) {
      TRACER_GET_CLASS(This)->sendRawTrace(This, traceId);
   }
}


void Tracer_sendPacketTrace
(
   const Tracer *This,
   unsigned int n,
   TD_TraceItem traceData[]
)
{
   if (Tracer_isEnabled(This)){
      unsigned int i;
      for (i=0; i<n; i++){
        TRACER_GET_CLASS(This)->sendRawTrace(This, traceData[i]);
      }
    }
}

///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the enable status of the tracer.
 * When the tracer is disabled, a call to its trace sending methods has
 * no effect.
 * @param isEnabled if true, then the tracer is enabled; if false, then
 * the profile is disabled
 */
static void setEnabled(void *obj, bool isEnabled)
{
     TRACER(obj)->enabledStatus = isEnabled;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Encapsulate the mechanism to send one single tracer item over the trace
 * channel to the external test
 * set-up.
 * This method is called by methods <CODE>sendLedTrace(void)</CODE>, 
 * <CODE>sendSynchTrace(void)</CODE> and
 * <CODE>sendPacketTrace(void)</CODE> in this same class.
 * User of a tracer object do not see method <CODE>sendRawTrace(void)</CODE>, 
 * they only see the <CODE>sendXxxTrace(void)</CODE> methods.
 * <p>
 * @see #sendSynchTrace
 * @see #sendPacketTrace
 * @param rawItem the trace item to be sent to the test set-up
 */
static void sendRawTrace(const void *obj, TD_TraceItem rawItem)
{
    // this is automate genenrated by converter
}



///////////////////////////////////////////////////////////////////////////////
//
//                    object constructor and deconstructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
   TRACER(obj)->enabledStatus = ENABLED;
}

Tracer* Tracer_new(void)
{
    return (Tracer*)object_new(TYPE_TRACER);
}



///////////////////////////////////////////////////////////////////////////////
//
//                    binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
   TracerClass *tc = TRACER_CLASS(oc);
    
   tc->setEnabled = setEnabled;
   tc->sendRawTrace = sendRawTrace;
}

static const TypeInfo type_info = {
   .name = TYPE_TRACER,
   .parent = TYPE_CC_ROOTOBJECT,
   .instance_size = sizeof(Tracer),
   .abstract = true,
   .class_size = sizeof(TracerClass),
   .instance_init = instance_init,
   .class_init = class_init
};


void Tracer_register(void)
{
    type_register_static(&type_info);
}
