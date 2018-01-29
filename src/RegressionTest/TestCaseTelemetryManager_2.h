//
//
// TestCaseTelemetryManager_2.h
//


#ifndef TESTCASETELEMETRYMANAGER_2_H
#define TESTCASETELEMETRYMANAGER_2_H


#include "../Utilities/TestCaseWithEvtCheck.h"
#include "../Qom/object.h"


/*
 * Check the activation process of a telemetry manager.
 * A telemetry manager instance is created and configured as follows.
 * As source of telemetry data, two dummy telemetry packets d1 and d2
 * are used. The two telemetry packets are encapsulated in
 * two <code>DC_DummyTelemetryPacket</code>
 * components and these are then loaded in a
 * <code>DC_SimpleTelemetryModeManager</code> component. As telemetry
 * stream, a <code>DC_ByteArrayTelemetryStream</code> component is
 * used. The telemetry stream and the telemetry mode manager are loaded
 * in the telemetry manager. The immediate dispatch queue of the telemetry
 * manager is configured with a size equal to 2. The following tests are
 * then performed: <ol>
 * <li>The two telemetry packets are loaded and unloaded from the immediate dispatch
 * queue and it is checked that the load and unload operations are correctly executed.</li>
 * <li>The correctness of the "full status" of the immediate dispatch queue is checked.</li>
 * <li>The telemetry manager is activated and it is checked that
 * the values of the two telemetry packets d1 and d2 are correctly written to
 * the telemetry stream.</li>
 * <li>The two telemetry items are loaded for immediate dispatch. The telemetry
 * manager is activated again and it is checked that
 * the values of the two telemetry packets d1 and d2 are written twice to
 * the telemetry stream.</li>
 * <li>It is checked that the status of the telemetry items submitted for immediate
 * dispatch has been changed to: "not in use".</li>
 * <li>The first telemetry packet is configured to return "data not valid".
 * The telemetry manager is again activated and it is checked that
 * only the second telemetry packet is written to the telemetry stream
 * and that the correct event is generated to report the validity check
 * failure.</li>
 * <li>The size of the telemetry stream is changed to accept only three bytes
 * of telemetry data.
 * The telemetry manager is again activated and it is checked that
 * an event is generated to report the insufficient capacity of the
 * telemetry stream.</li>
 * <li>The first telemetry packet is configured to report "data not valid" and
 * it is submitted for immediate dispatch to the telemetry stream.
 * The telemetry manager is activated and it is checked that
 * the correct events are generated.</li>
 * <li>It is checked that the status of the telemetry item submitted for immediate
 * dispatch has been changed to: "not in use".</li>
 * <li>The size of the telemetry stream is changed to be insufficient to
 * accept the first telemetry packet. The telemetry packet is again submitted
 * for direct dispatch to the telemetry stream and, after activation of the
 * telemetry manager, it is checked that
 * an event is generated to report the insufficient capacity of the
 * telemetry stream.</li>
 * <li>It is checked that the status of the telemetry item submitted for immediate
 * dispatch has been changed to: "not in use".</li>
 * <li>An attempt is made to submit three packets for immediate dispatch(the capacity of the
 * immediate dispatch queue is 2) and it is checked that the correct event is generated.</li>
 * </ol>
 * @see CC_TelemetryManager
 * @see DC_SimpleTelemetryModeManager
 * @see DC_DummyTelemetryPacket
 * @see DC_ByteArrayTelemetryStream
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASETELEMETRYMANAGER_2 "testcasetelemetrymanager_2"

void TestCaseTelemetryManager_2_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseTelemetryManager_2 {
    TestCaseWithEvtCheck parent;
} TestCaseTelemetryManager_2;


typedef struct TestCaseTelemetryManager_2Class {
    TestCaseWithEvtCheckClass parent_class;
} TestCaseTelemetryManager_2Class;


#define TESTCASETELEMETRYMANAGER_2_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseTelemetryManager_2Class, \
                                          obj, TYPE_TESTCASETELEMETRYMANAGER_2)

#define TESTCASETELEMETRYMANAGER_2_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseTelemetryManager_2Class, \
                                        klass, TYPE_TESTCASETELEMETRYMANAGER_2)

#define TESTCASETELEMETRYMANAGER_2(obj) \
        OBJECT_CHECK(TestCaseTelemetryManager_2, \
                                          obj, TYPE_TESTCASETELEMETRYMANAGER_2)


TestCaseTelemetryManager_2* TestCaseTelemetryManager_2_new(void);

#endif
