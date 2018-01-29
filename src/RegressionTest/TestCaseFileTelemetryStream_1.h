//
//
// TestCaseFileTelemetryStream_1.h
//


#ifndef TESTCASEFILETELEMETRYSTREAM_1_H
#define TESTCASEFILETELEMETRYSTREAM_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Verify the file-oriented telemetry stream as implemented
 * by class <code>DC_FileTelemetryStream</code>.
 * In this test the telemetry data are written to the file
 * <code>TelemetryStream.txt</code> which should be created in the
 * directory from which the program is run. The success or otherwise
 * of the test should be verified by inspecting this file.
 * An instance of this class is created and the following specific
 * tests are performed: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>The telemetry stream file is set and it is verified that
 * the set operation succeeded.</li>
 * <li>A dummy PUS telemetry packet(instance of class <code>DC_DummyTelemetryPacket</code>)
 * is configured with two bytes with values of 1 and 2. The telemetry packet is written
 * to the telemetry stream
 * The success of this operation should be checked by inspecting
 * the telemetry output file.</li>
 * <li>The value of the bytes encapsulated in the dummy telemetry packet
 * is incremented by one and the telemetry packet is again written to the
 * telemetry stream.
 * The success of this operation should be checked by inspecting
 * the telemetry output file.</li>
 * </ol>
 * @see DC_FileTelemetryStream
 * @see DC_DummyTelemetryPacket
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEFILETELEMETRYSTREAM_1 "testcasefiletelemetrystream_1"

void TestCaseFileTelemetryStream_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseFileTelemetryStream_1 {
    TestCaseGenericSetUp parent;
} TestCaseFileTelemetryStream_1;


typedef struct TestCaseFileTelemetryStream_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseFileTelemetryStream_1Class;


#define TESTCASEFILETELEMETRYSTREAM_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseFileTelemetryStream_1Class, \
                                       obj, TYPE_TESTCASEFILETELEMETRYSTREAM_1)

#define TESTCASEFILETELEMETRYSTREAM_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseFileTelemetryStream_1Class, \
                                     klass, TYPE_TESTCASEFILETELEMETRYSTREAM_1)

#define TESTCASEFILETELEMETRYSTREAM_1(obj) \
        OBJECT_CHECK(TestCaseFileTelemetryStream_1, \
                                       obj, TYPE_TESTCASEFILETELEMETRYSTREAM_1)


TestCaseFileTelemetryStream_1* TestCaseFileTelemetryStream_1_new(void);

#endif
