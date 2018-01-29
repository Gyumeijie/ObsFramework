//
//
// TestCaseDummyTelemetryPacket_1.h
//


#ifndef TESTCASEDUMMYTELEMETRYPACKET_1_H
#define TESTCASEDUMMYTELEMETRYPACKET_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Verify the telemetry packet services as implemented
 * by class <code>DC_DummyTelemetryPacket</code>.
 * An instance of this class is created and the following specific
 * tests are performed: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified that the configuration service reports "object not configured".</li>
 * <li>The number of encapsulated bytes is set to 2 and it is verified that
 * the configuration service reports "object configured".</li>
 * <li>It is verified that the number of encapsulated bytes is correctly reported
 * to be equal to 2.</li>
 * <li>The value of the encapsulated bytes is set and read out with
 * the data acquisition service and its correctness is verified.</li>
 * <li>It is verified that the default value returned by the
 * data acquisitions service is 0 for all encapsulated bytes.</li>
 * <li>It is verified that the default value returned by the
 * the validity check is "data valid".</li>
 * <li>The validity status is set and read out and its correctness
 * is verified.</li>
 * <li>The implementation of the update service is verified.</li>
 * <li>The value of one of encapsulated bytes is set to 255 and an
 * update request is made. It is verified that the value of the
 * encapsulated byte is correctly wrapped around to 0..</li>
 * <li>The default value of the telemetry packet time tag is read out and its correctness
 * is verified.</li>
 * <li>The default value of the telemetry packet type is read out and its correctness
 * is verified.</li>
 * <li>The default value of the telemetry packet subtype is read out and its correctness
 * is verified.</li>
 * <li>The default value of the telemetry packet destination is read out and its correctness
 * is verified.</li>
 * <li>The default value of the "in use" flag is read out and its correctness is verified.</li>
 * <li>The implementation of the "in use" flag is checked.</li>
 * <li>The default implementation of the "fast data acqusition service" is checked.</li>
 * </ol>
 * @see DC_DummyTelemetryPacket
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEDUMMYTELEMETRYPACKET_1 "testcasedummytelemetrypacket_1"

void TestCaseDummyTelemetryPacket_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseDummyTelemetryPacket_1 {
    TestCaseGenericSetUp parent;
} TestCaseDummyTelemetryPacket_1;


typedef struct TestCaseDummyTelemetryPacket_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseDummyTelemetryPacket_1Class;


#define TESTCASEDUMMYTELEMETRYPACKET_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseDummyTelemetryPacket_1Class,\
                                      obj, TYPE_TESTCASEDUMMYTELEMETRYPACKET_1)

#define TESTCASEDUMMYTELEMETRYPACKET_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseDummyTelemetryPacket_1Class,\
                                    klass, TYPE_TESTCASEDUMMYTELEMETRYPACKET_1)

#define TESTCASEDUMMYTELEMETRYPACKET_1(obj) \
        OBJECT_CHECK(TestCaseDummyTelemetryPacket_1,\
                                      obj, TYPE_TESTCASEDUMMYTELEMETRYPACKET_1)


TestCaseDummyTelemetryPacket_1* TestCaseDummyTelemetryPacket_1_new(void);

#endif
