//
//
// DC_TestTracer.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/TestCompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/TestConstants.h"
#include "../GeneralInclude/ClassId.h"
#include "DC_TestTracer.h"
#include <time.h>



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_TestTracer_closeLogFile(DC_TestTracer *This)
{
#ifdef MS_HOST
   assert(This->logFile != pNULL);
   fclose(This->logFile);
   This->logFile = pNULL;
#endif
}

const char* DC_TestTracer_getLogFileName(DC_TestTracer *This)
{
#ifdef MS_HOST
   return TEST_TRACER_LOG_FILE;
#else
   return pNULL;
#endif
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Wwrite the trace item to the log file. The trace item is written using the
 * <code>printf</code> (embedded environment) or <code>fprintf</code> (desktop
 * environment) library function with the
 * <code>%x</code> format specifier. It is assumed that the <code>TD_TraceItem</code>
 * is compatible with this this specifier.
 * This method should be called only when the log file is still open.
 * @see #closeLogFile
 * @see Tracer#sendRawTrace
 * @param traceItem the trace item to be sent to the test set-up
 */
static void sendRawTrace(const void *obj, TD_TraceItem rawItem)
{
   DC_TestTracer *This = DC_TESTTRACER(obj);
#ifdef MS_HOST
   assert(This->logFile != pNULL);
   fprintf(This->logFile, "Raw_Tracer_Item: %x\n", rawItem);
#else
   printf("Raw Tracer Item: %x\n", rawItem);
#endif
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    DC_TestTracer *This = DC_TESTTRACER(obj);
	This->logFile = pNULL;

#ifdef MS_HOST
   if((This->logFile = fopen(TEST_TRACER_LOG_FILE,"w")) == pNULL) {
       printf( "\nThe file %s could not be opened\n", TEST_TRACER_LOG_FILE);
   } else {
       printf( "\nThe file %s was successfully opened\n", TEST_TRACER_LOG_FILE);
   }

   // Write header information
   time_t ltime;
   time( &ltime );
   fprintf(This->logFile, "Test Tracer Log File\n");
   fprintf(This->logFile, "Test Run Performed on %s\n", ctime(&ltime));
#else
   printf("Test Tracer Log File\n");
   printf("\n");
#endif

   // Set the class identifer
   CC_RootObject_setClassId((CC_RootObject*)obj, ID_TESTTRACER);
}

DC_TestTracer* DC_TestTracer_new(void)
{
    return (DC_TestTracer*)object_new(TYPE_DC_TESTTRACER);
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    DC_TestTracerClass *dc_ttc = DC_TESTTRACER_CLASS(oc);

    TracerClass *tc = TRACER_CLASS(oc);
    tc->sendRawTrace = sendRawTrace;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_TESTTRACER,
    .parent = TYPE_TRACER,
    .instance_size = sizeof(DC_TestTracer),
    .abstract = false,
    .class_size = sizeof(DC_TestTracerClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_TestTracer_register(void)
{
    type_register_static(&type_info);
}
