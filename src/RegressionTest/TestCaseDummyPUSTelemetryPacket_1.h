//
//
// TestCaseDummyPUSTelemetryPacket_1.h
//


#ifndef TESTCASEDUMMYPUSTELEMETRYPACKET_1_H
#define TESTCASEDUMMYPUSTELEMETRYPACKET_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Check the functionalities implemented by class <code>PUSTelemetryPacket</code>.
 * Since this class is abstract, the checks are carried out on its concrete subclass
 * <code>DC_DummyPUSTelemetryPacket</code>.
 * An instance of this class is created and the following specific
 * checks are carried out: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>The value of the encapsulated byte is set and read out with
 * the data acquisition service and its correctness is verified.</li>
 * <li>It is verified that the default value returned by the
 * data acquisitions service is 0.</li>
 * <li>The implementation of the update service is verified.</li>
 * <li>The value of the encapsulated byte is set to 255 and an
 * update request is made. It is verified that the value of the
 * encapsulated byte is correctly wrapped around to 0..</li>
 * <li>The telemetry packet time tag is set and then read back and its correctness
 * is checked.</li>
 * <li>The telemetry packet type is set and then read back and its correctness
 * is checked.</li>
 * <li>The telemetry packet sub type is set and then read back and its correctness
 * is checked.</li>
 * <li>The telemetry packet identifier is read and the correctness of its value is
 * checked.</li>
 * <li>The default value of the telemetry packet destination is checked.</li>
 * <li>The telemetry packet destination is modified and then read back and its correctness
 * is checked.</li>
 * <li>The value of the OBS Clock is read and it is checkes that it is different from NULL.</li>
 * </ol>
 * @see DC_PUSTelemetryPacket
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEDUMMYPUSTELEMETRYPACKET_1 "testcasedummypustelemetrypacket_1"

void TestCaseDummyPUSTelemetryPacket_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseDummyPUSTelemetryPacket_1 {
    TestCaseGenericSetUp parent;
} TestCaseDummyPUSTelemetryPacket_1;


typedef struct TestCaseDummyPUSTelemetryPacket_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseDummyPUSTelemetryPacket_1Class;


#define TESTCASEDUMMYPUSTELEMETRYPACKET_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseDummyPUSTelemetryPacket_1Class,\
                                   obj, TYPE_TESTCASEDUMMYPUSTELEMETRYPACKET_1)

#define TESTCASEDUMMYPUSTELEMETRYPACKET_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseDummyPUSTelemetryPacket_1Class,\
                                 klass, TYPE_TESTCASEDUMMYPUSTELEMETRYPACKET_1)

#define TESTCASEDUMMYPUSTELEMETRYPACKET_1(obj) \
        OBJECT_CHECK(TestCaseDummyPUSTelemetryPacket_1,\
                                   obj, TYPE_TESTCASEDUMMYPUSTELEMETRYPACKET_1)


TestCaseDummyPUSTelemetryPacket_1* TestCaseDummyPUSTelemetryPacket_1_new(void);

#endif
