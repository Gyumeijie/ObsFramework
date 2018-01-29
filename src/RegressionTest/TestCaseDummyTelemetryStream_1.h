//
//
// TestCaseDummyTelemetryStream_1.h
//


#ifndef TESTCASEDUMMYTELEMETRYSTREAM_1_H
#define TESTCASEDUMMYTELEMETRYSTREAM_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Verify the telemetry stream services as implemented
 * by class <code>DC_DummyTelemetryStream</code>.
 * An instance of this class is created and the following specific
 * tests are performed: <ol>
 * <li>The correctness of the class identifier is checked.</li>
 * <li>The default return value of method <code>getCapacity</code> is checked.</li>
 * <li>The default return value of method <code>doesPacketFit</code> is checked.</li>
 * <li>Dummy calls are performed to methods <code>reset</code>, <code>flsuh</code>
 * and <code>write</code>.</li>
 * </ol>
 * @see DC_DummyTelemetryStream
 * @author Roberto Totaro
 * @version 1.0
 */
#define TYPE_TESTCASEDUMMYTELEMETRYSTREAM_1 "testcasedummytelemetrystream_1"

void TestCaseDummyTelemetryStream_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseDummyTelemetryStream_1 {
    TestCaseGenericSetUp parent;
} TestCaseDummyTelemetryStream_1;


typedef struct TestCaseDummyTelemetryStream_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseDummyTelemetryStream_1Class;


#define TESTCASEDUMMYTELEMETRYSTREAM_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseDummyTelemetryStream_1Class, \
                                      obj, TYPE_TESTCASEDUMMYTELEMETRYSTREAM_1)

#define TESTCASEDUMMYTELEMETRYSTREAM_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseDummyTelemetryStream_1Class, \
                                    klass, TYPE_TESTCASEDUMMYTELEMETRYSTREAM_1) 

#define TESTCASEDUMMYTELEMETRYSTREAM_1(obj) \
        OBJECT_CHECK(TestCaseDummyTelemetryStream_1, \
                                      obj, TYPE_TESTCASEDUMMYTELEMETRYSTREAM_1)


TestCaseDummyTelemetryStream_1* TestCaseDummyTelemetryStream_1_new(void);

#endif
