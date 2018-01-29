//
//
// DC_FileTelemetryStream.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "TelemetryPacket.h"
#include "DC_FileTelemetryStream.h"
#include <stdio.h>
#include <time.h>



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_FileTelemetryStream_setOutputStream(DC_FileTelemetryStream *This, 
                                            FILE *outputStream)
{
    This->out = outputStream;
#ifdef MS_HOST
    time_t ltime;
    time(&ltime);
    if (This->out != pNULL) {
        fprintf(This->out, "File-Oriented Output Stream -- Data Written on %s \n", ctime(&ltime));
    } else {
        printf("File-Oriented Output Stream -- Data Written on %s \n", ctime(&ltime));
    }
#endif
}

FILE* DC_FileTelemetryStream_getOutputStream(DC_FileTelemetryStream *This)
{
    return This->out;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Write an "end-of-TM-frame" message to the output stream and flush it.
 * The "end-of-TM-frame" message consists of a single straight line. If the output
 * stream is the standard output, no action is taken.
 */
static void flush(void *obj)
{
    DC_FileTelemetryStream *This = DC_FILETELEMETRYSTREAM(obj);

    if (This->out != pNULL) {
        fprintf(This->out, "-----------------------------------------------\n");
        fflush(This->out);
    } else {
        printf("-----------------------------------------------\n");
    }
}

/**
 * Write the full content of the telemetry packet to the output stream.
 * First, the value of all the attributes(the telemetry time tag, the
 * telemetry type and subtype, the telemetry destination) are written.
 * Then the telemetry packet data are written as a sequence of bytes.
 * @param tmItem the telemetry packet to be written to the output
 * stream.
 */
static void write(void *obj, TelemetryPacket *tmItem)
{
    DC_FileTelemetryStream *This = DC_FILETELEMETRYSTREAM(obj);
    TelemetryPacketClass *tpc = TELEMETRYPACKET_GET_CLASS(tmItem);

    assert(tmItem != pNULL);

    FILE *out = This->out;
    if (out!=pNULL) {
        fprintf(out, "Telemetry Item Type (hex):  %8x \n", tpc->getType(tmItem));
        fprintf(out, "Telemetry Item Subtype (hex):  %8x \n", tpc->getSubType(tmItem));
        fprintf(out, "Telemetry Item Destination (hex):  %8x \n", tpc->getDestination(tmItem));
        fprintf(out, "Telemetry Item Time Tag (hex):  %8x \n", tpc->getTimeTag(tmItem));

        const unsigned int nBytes = tpc->getNumberOfBytes(tmItem);
        for (unsigned int i=0; i<nBytes; i++){ 
            fprintf(out, "Byte %8x (hex):  %8x \n", i, tpc->getUnsignedByte(tmItem, i));
        }
    } else {
        printf("Telemetry Item Type (hex):  %8x \n", tpc->getType(tmItem));
        printf("Telemetry Item Subtype (hex):  %8x \n", tpc->getSubType(tmItem));
        printf("Telemetry Item Destination (hex):  %8x \n", tpc->getDestination(tmItem));
        printf("Telemetry Item Time Tag (hex):  %8x \n", tpc->getTimeTag(tmItem));
       
        const unsigned int nBytes = tpc->getNumberOfBytes(tmItem);
        for (unsigned int i=0; i<nBytes; i++) {
            printf("Byte %8x (hex):  %8x \n", i, tpc->getUnsignedByte(tmItem, i));
        }
    }
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    DC_FileTelemetryStream *This = DC_FILETELEMETRYSTREAM(obj);
    This->out = pNULL;

    CC_RootObject_setClassId((CC_RootObject*)obj, ID_FILETELEMETRYSTREAM);
}

DC_FileTelemetryStream* DC_FileTelemetryStream_new(void)
{
    Object *obj = object_new(TYPE_DC_FILETELEMETRYSTREAM);
    return (DC_FileTelemetryStream*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    TelemetryStreamClass *tsc = TELEMETRYSTREAM_CLASS(oc);

    tsc->flush = flush;
    tsc->write = write;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_FILETELEMETRYSTREAM,
    .parent = TYPE_TELEMETRYSTREAM,
    .instance_size = sizeof(DC_FileTelemetryStream),
    .abstract = false,
    .class_size = sizeof(DC_FileTelemetryStreamClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_FileTelemetryStream_register(void)
{
    type_register_static(&type_info);
}
