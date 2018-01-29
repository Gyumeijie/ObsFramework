//
//
// DC_TestTracer.h
//


#ifndef DC_TESTTRACER_H
#define DC_TESTTRACER_H


#include <stdio.h>
#include "Tracer.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Qom/object.h"


/*
 * The dummy tracer can be useful during a test phase
 * when no external test set-up is available. The log file simulates the
 * external test set-up.
 * Depending on the value of a compiler switch, the log file is either a proper
 * file or the standard output. The latter case may allow use of this component
 * in an embedded environment where no file system is available.
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_TESTTRACER "dc_testtracer"

void DC_TestTracer_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_TestTracer {
    Tracer parent;

    FILE *logFile;
};


struct DC_TestTracerClass {
    TracerClass parent_class;
};


#define DC_TESTTRACER_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_TestTracerClass, obj, TYPE_DC_TESTTRACER)

#define DC_TESTTRACER_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_TestTracerClass, klass, TYPE_DC_TESTTRACER)

#define DC_TESTTRACER(obj) \
        OBJECT_CHECK(DC_TestTracer, obj, TYPE_DC_TESTTRACER)


DC_TestTracer* DC_TestTracer_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * In a desktop environment, flush and close the log file. In an embedded
 * environment, no action is taken. This method should not be called more
 * than once. There is no way to open the log file after it has been closed.
 * @see #closeLogFile
 * @see TestCompilerSwitches#MS_HOST
 * @see TestConstants#TEST_TRACER_LOG_FILE
 * @see Tracer#setEnabled
 */
void DC_TestTracer_closeLogFile(DC_TestTracer *This);

/**
 * In a desktop environment, return the name of the log file. In an embedded
 * environment, return pNULL.
 * @see TEST_TRACER_LOG_FILE
 * @return the name of the log file or pNULL if the standard output is used as
 * log file
 */
const char* DC_TestTracer_getLogFileName(DC_TestTracer *This);


#endif
