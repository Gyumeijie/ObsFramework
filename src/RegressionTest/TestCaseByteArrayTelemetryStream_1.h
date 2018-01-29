//
//
// TestCaseByteArrayTelemetryStream_1.h
//


#ifndef TESTCASEBYTEARRAYTELEMETRYSTREAM_1_H
#define TESTCASEBYTEARRAYTELEMETRYSTREAM_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Verify the telemetry stream services as implemented
 * by class <code>DC_ByteArrayTelemetryStream</code>.
 * An instance of this class is created and the following specific
 * tests are performed: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified that the configuration check service of the object
 * initially reports "object not configured".</li>
 * <li>The size of the byte array is set and then read out and
 * it is verified that that the read-out value is correct.</li>
 * <li>The startiing address of the byte array is loaded and then read out and
 * it is verified that that the read-out value is correct.</li>
 * <li>It is verified that the configuration check service now reports
 * "object configured".</li>
 * <li>A write request is made for a telemetry packet(an instance of class
 * <code>DC_DummyTelemetryPacket</code>) is used and it is verified that
 * the correct values are writtent to the byte array.</li>
 * <li>The <code>doesPacketFit</code> method is called twice to return
 * "item fits" in the first case and "item does not fit" in the second
 * case.</li>
 * <li>Additional write requests are made that should not be executed
 * because there is no more space in the byte array.</li>
 * <li>The telemetry stream is reset and it is verified that the
 * write requests can now be processed.</li>
 * <li>The byte array is again filled up and it is then flushed. It
 * is verified that the flush operation is successful.</li>
 * </ol>
 * @see DC_ByteArrayTelemetryStream
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEBYTEARRAYTELEMETRYSTREAM_1 "testcasebytearraytelemetrystream_1"

void TestCaseByteArrayTelemetryStream_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseByteArrayTelemetryStream_1 {
    TestCaseGenericSetUp parent;
} TestCaseByteArrayTelemetryStream_1;


typedef struct TestCaseByteArrayTelemetryStream_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseByteArrayTelemetryStream_1Class;


#define TESTCASEBYTEARRAYTELEMETRYSTREAM_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseByteArrayTelemetryStream_1Class, \
                                  obj, TYPE_TESTCASEBYTEARRAYTELEMETRYSTREAM_1)

#define TESTCASEBYTEARRAYTELEMETRYSTREAM_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseByteArrayTelemetryStream_1Class, \
                                klass, TYPE_TESTCASEBYTEARRAYTELEMETRYSTREAM_1)

#define TESTCASEBYTEARRAYTELEMETRYSTREAM_1(obj) \
        OBJECT_CHECK(TestCaseByteArrayTelemetryStream_1, \
                                  obj, TYPE_TESTCASEBYTEARRAYTELEMETRYSTREAM_1)


TestCaseByteArrayTelemetryStream_1* TestCaseByteArrayTelemetryStream_1_new(void);

#endif
