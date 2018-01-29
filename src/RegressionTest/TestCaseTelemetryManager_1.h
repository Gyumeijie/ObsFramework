//
//
// TestCaseTelemetryManager_1.h
//


#ifndef TESTCASETELEMETRYMANAGER_1_H
#define TESTCASETELEMETRYMANAGER_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Check the configuration process of a telemetry manager.
 * A telemetry manager instance is created and the following specific
 * tests are performed: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified that the configuration check service of the telemetry
 * manager initially reports "object not configured".</li>
 * <li>A telemetry mode manager is loaded in the telemetry manager and
 * it is verified that it can be correctly read out.</li>
 * <li>A telemetry stream is loaded in the telemetry manager and
 * it is verified that it can be correctly read out.</li>
 * <li>The size of the immediate dispatch queue is set equal to zero and
 * it is verified that it can be correctly read out.</li>
 * <li>It is verified that the status of immediate dispatch queue is "queue full".</li>
 * <li>It is verified that the configuration check service of the telemetry
 * manager now reports "object configured".</li>
 * </ol>
 * @see CC_TelemetryManager
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASETELEMETRYMANAGER_1 "testcasetelemetrymanager_1"

void TestCaseTelemetryManager_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseTelemetryManager_1 {
    TestCaseGenericSetUp parent;
} TestCaseTelemetryManager_1;


typedef struct TestCaseTelemetryManager_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseTelemetryManager_1Class;


#define TESTCASETELEMETRYMANAGER_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseTelemetryManager_1Class, \
                                          obj, TYPE_TESTCASETELEMETRYMANAGER_1)

#define TESTCASETELEMETRYMANAGER_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseTelemetryManager_1Class, \
                                        klass, TYPE_TESTCASETELEMETRYMANAGER_1)

#define TESTCASETELEMETRYMANAGER_1(obj) \
        OBJECT_CHECK(TestCaseTelemetryManager_1, \
                                          obj, TYPE_TESTCASETELEMETRYMANAGER_1)


TestCaseTelemetryManager_1* TestCaseTelemetryManager_1_new(void);

#endif
