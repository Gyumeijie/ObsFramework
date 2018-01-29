//
//
// TestCaseFileTelemetryStream_2.h
//


#ifndef TESTCASEFILETELEMETRYSTREAM_2_H
#define TESTCASEFILETELEMETRYSTREAM_2_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Verify the file-oriented telemetry stream as implemented
 * by class <code>DC_FileTelemetryStream</code>.
 * In this test the telemetry data are written to the standard
 * output. The success or otherwise
 * of the test should be verified by checking the standard output.
 * An instance of this class is created and the following specific
 * tests are performed: <ol>
 * <li>The telemetry stream file is set to pNULL(to signify that
 * it is desired to direct the telemetry data to the standard
 * output) and it is verified that the set operation succeeded.</li>
 * <li>A dummy PUS telemetry packet(instance of class <code>DC_DummyTelemetryPacket</code>)
 * is configured with two bytes with values of 1 and 2. The telemetry packet is written
 * to the telemetry stream
 * The success of this operation should be checked by inspecting
 * the standard output.</li>
 * <li>The value of the bytes encapsulated in the dummy telemetry packet
 * is incremented by one and the telemetry packet is again written to the
 * telemetry stream.
 * The success of this operation should be checked by inspecting
 * the standard output.</li>
 * </ol>
 * @see DC_FileTelemetryStream
 * @see DC_DummyTelemetryPacket
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEFILETELEMETRYSTREAM_2 "testcasefiletelemetrystream_2"

void TestCaseFileTelemetryStream_2_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseFileTelemetryStream_2 {
    TestCaseGenericSetUp parent;
} TestCaseFileTelemetryStream_2;


typedef struct TestCaseFileTelemetryStream_2Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseFileTelemetryStream_2Class;


#define TESTCASEFILETELEMETRYSTREAM_2_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseFileTelemetryStream_2Class, \
                                       obj, TYPE_TESTCASEFILETELEMETRYSTREAM_2)

#define TESTCASEFILETELEMETRYSTREAM_2_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseFileTelemetryStream_2Class, \
                                     klass, TYPE_TESTCASEFILETELEMETRYSTREAM_2)

#define TESTCASEFILETELEMETRYSTREAM_2(obj) \
        OBJECT_CHECK(TestCaseFileTelemetryStream_2, \
                                       obj, TYPE_TESTCASEFILETELEMETRYSTREAM_2)


TestCaseFileTelemetryStream_2* TestCaseFileTelemetryStream_2_new(void);

#endif
