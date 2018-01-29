//
//
// TestCaseCycleDataItem16TmStream_1.h
//


#ifndef TESTCASECYCLEDATAITEM16TMSTREAM_1_H
#define TESTCASECYCLEDATAITEM16TMSTREAM_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Verify the telemetry stream services as implemented
 * by class <code>DC_CycleDataItem16TmStream</code>.
 * An instance of this class is created and the following specific
 * tests are performed: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified that the configuration check service of the object
 * initially reports "object not configured".</li>
 * <li>The number of data items in the <code>DC_CycleDataItem16TmStream</code>
 * is set to 3 and it is verified that it is correctly returned by the
 * <code>getSize</code> service.</li>
 * <li>Three data items are loaded into the <code>DC_CycleDataItem16TmStream</code>
 * and it is verified that the configuration check service now reports
 * "object configured".</li>
 * <li>A dummy telemetry packet(instance of class <code>DC_DummyTelemetryPacket</code>) is
 * configured to hold 4 bytes. The service <code>doesPacketFit</code> is used to check whether
 * the telemetry packet fits in the telemetry stream.</li>
 * The telemetry packet is written to the telemetry stream
 * and it is verified that the write request is correctly executed.</li>
 * <li>The service <code>doesPacketFit</code> is used to check whether
 * the telemetry packet can be written a second time telemetry stream.</li>
 * <li>The telemetry packet is written again to the telemetry stream
 * and it is verified that only its first two bytes are written to the data items
 * encapsulated by the telemetry stream.</li>
 * <li>The telemetry stream is reset, the telemetry packet is written again and
 * it is verified that the write request is correctly executed.</li>
 * </ol>
 * @see DC_CycleDataItem16TmStream
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASECYCLEDATAITEM16TMSTREAM_1 "testcasecycledataitem16tmstream_1"

void TestCaseCycleDataItem16TmStream_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseCycleDataItem16TmStream_1 {
    TestCaseGenericSetUp parent;
} TestCaseCycleDataItem16TmStream_1;


typedef struct TestCaseCycleDataItem16TmStream_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseCycleDataItem16TmStream_1Class;


#define TESTCASECYCLEDATAITEM16TMSTREAM_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseCycleDataItem16TmStream_1Class, \
                                   obj, TYPE_TESTCASECYCLEDATAITEM16TMSTREAM_1)

#define TESTCASECYCLEDATAITEM16TMSTREAM_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseCycleDataItem16TmStream_1Class, \
                                 klass, TYPE_TESTCASECYCLEDATAITEM16TMSTREAM_1)

#define TESTCASECYCLEDATAITEM16TMSTREAM_1(obj) \
        OBJECT_CHECK(TestCaseCycleDataItem16TmStream_1, \
                                   obj, TYPE_TESTCASECYCLEDATAITEM16TMSTREAM_1)


TestCaseCycleDataItem16TmStream_1* TestCaseCycleDataItem16TmStream_1_new(void);

#endif
