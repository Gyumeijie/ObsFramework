//
//
// DC_FileTelemetryStream.h
//


#ifndef DC_FILETELEMETRYSTREAM_H
#define DC_FILETELEMETRYSTREAM_H


#include <stdio.h>
#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "TelemetryStream.h"
#include "../Qom/object.h"


/*
 * File-oriented telemetry stream. The data written to the telemetry
 * stream are written to an output file. The output file can be either
 * a named file or the standard output. This will allow usage both
 * in a desktop environment and in many embedded environments. This
 * type of telemetry stream is primarily intended for testing purposes.
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_FILETELEMETRYSTREAM "dc_filetelemetrystream"

void DC_FileTelemetryStream_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_FileTelemetryStream {
    TelemetryStream parent;

    FILE *out;
};


struct DC_FileTelemetryStreamClass {
    TelemetryStreamClass parent_class;
};


#define DC_FILETELEMETRYSTREAM_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_FileTelemetryStreamClass, obj, TYPE_DC_FILETELEMETRYSTREAM)

#define DC_FILETELEMETRYSTREAM_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_FileTelemetryStreamClass, klass, TYPE_DC_FILETELEMETRYSTREAM)

#define DC_FILETELEMETRYSTREAM(obj) \
        OBJECT_CHECK(DC_FileTelemetryStream, obj, TYPE_DC_FILETELEMETRYSTREAM)


DC_FileTelemetryStream* DC_FileTelemetryStream_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the output stream to which the telemetry data are written and
 * write a header to the output stream. If the
 * argument is <code>pNULL</code>, then the output stream is assumed to be the standard
 * ouptut.
 * @param outputStream the ouptut file or <code>pNULL</code> if the telemetry data must be
 * written to the standard output
 */
void DC_FileTelemetryStream_setOutputStream(DC_FileTelemetryStream *This, FILE *outputStream);

/**
 * Return the output stream to which the telemetry data are written.
 * The return value can be <code>pNULL</code> to signify that the output stream is
 * the standard ouptut.
 * @return the ouptut file or <code>pNULL</code> if the telemetry data must be
 * written to the standard output
 */
FILE* DC_FileTelemetryStream_getOutputStream(DC_FileTelemetryStream *This);


#endif
