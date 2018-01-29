//
//
// Tracer.h
//

#ifndef TRACER_H
#define TRACER_H

#include "../Base/CC_RootObject.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Qom/object.h"
#include <stdbool.h>

/**
 * Base class from which all tracer classes are derived.
 * A tracer is a component that can send trace signals to an external test
 * set-up.
 * A trace signal is made up of one or more <i>trace items</i>. A trace item
 * is an elementary item of trace information that is sent to the test set-up
 * in one single operation.
 * <p>
 * Two types of trace signals are recognized: a <i>Synch Trace</i>, and a
 * <i>Packet Trace</i>. A synch trace consists of one single trace item. A
 * packet trace consists of a sequence of trace items.
 * <p>
 * The tracer can be enabled or disabled.
 * Calls to the services to send trace signals in a tracer that is disabled
 * have no effect.
 * <p>
 * This class is abstract because the implementation of the services that
 * send the trace signals
 * must be specified in the derived classes that implement concrete tracers.
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */

#define TYPE_TRACER "tracer"

void Tracer_register(void);

///////////////////////////////////////////////////////////////////////////////
//
//                         class and struct 
//
///////////////////////////////////////////////////////////////////////////////

struct Tracer {
   CC_RootObject parent;

   bool enabledStatus;
};


struct TracerClass {
   CC_RootObjectClass parent_class;

   void (*setEnabled)(void *obj, bool isEnabled);
   void (*sendRawTrace)(const void *obj, TD_TraceItem rawItem);
};



#define TRACER_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TracerClass, obj, TYPE_TRACER) 

#define TRACER_CLASS(klass) \
        OBJECT_CLASS_CHECK(TracerClass, klass, TYPE_TRACER)

#define TRACER(obj) \
        OBJECT_CHECK(Tracer, obj, TYPE_TRACER)


Tracer* Tracer_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Send a Synch trace signal if the tracer is enabled.
 * If the tracer is disabled, the method call has no effect.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *    Tracer_if( Tracer_isEnabled(void) )
 *    {  Tracer_sendRawTrac e(Tracer *This, traceId);
 *    } </PRE>
 * The <CODE>Tracer_sendRawTrace(void)</CODE> method is abstract and encapsulates
 * the implementation of the raw trace signal
 * sending.
 * Thus, this class enforces the management of the enabled status but
 * delegates implementation of
 * the sending mechanism to
 * derived classes implementing concrete tracers.
 * @param traceId the trace identifier
 */
void Tracer_sendSynchTrace(const Tracer *This, TD_TraceItem traceId);

/**
 * Send a packet trace signal if the tracer is enabled.
 * If the tracer is disabled, the method call has no effect.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *    Tracer_if( Tracer_isEnabled(void) )
 *    {  Tracer_for(int i=0; i smaller than number of items in packet; i++)
 *       {  TD_TraceItem b = . . .  // form i-th item of the packet trace
 *          Tracer_sendRawTrac e(Tracer *This, b);
 *       }
 *    } </PRE>
 * The <CODE>Tracer_sendRawTrace(void)</CODE> method is abstract and encapsulates
 * the implementation of the raw trace signal
 * sending.
 * Thus, this class enforces the management of the enabled status and
 * transform the sequence of trace
 * data into elementary trace item to be sent to the test set-up in sequence
 * but delegates
 * implementation of the sending mechanism to
 * derived classes implementing concrete tracers.
 * @param n number of trace data elements
 * @param traceData array of trace data
 */
void Tracer_sendPacketTrace
(
    const Tracer *This,
    unsigned int n,
    TD_TraceItem traceData[]
);

/**
 * Check the enable status of the tracer.
 * <p>
 * @return true if the profile is enabled, false otherwise
 */
bool Tracer_isEnabled(const Tracer *This);


#endif
