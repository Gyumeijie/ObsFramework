//
//
// TestCasePUSTelemetryModeManager_1.h
//


#ifndef TESTCASEPUSTELEMETRYMODEMANAGER_1_H
#define TESTCASEPUSTELEMETRYMODEMANAGER_1_H


#include "../Utilities/TestCasePUSFull.h"
#include "../Qom/object.h"


/*
 * Check the functionality of the <code>DC_PUSTelemetryModeManager</code>
 * class. The test case is configured as follows:<ul>
 * <li>The telemetry packet factory is retrieved.</li>
 * <li>An instance of class <code>DC_PUSTelemetryModeManager</code> is created.</li>
 * <li>Two data reporting packet instances(instances of class
 * <code>DC_PUSDataReportingPacket</code>) are retrieved from the telemetry packet 
 * factory. The SIDs of the telemetry packets are SID_A and
 * SID_B. </li>
 * </ul>
 * The following specific tests are then performed:<ol>
 * <li>The correctness of the class identifier is checked.</li>
 * <li>It is checked that the mode manager component is initially not configured.</li>
 * <li>The maximum number of packets N allowed by the mode manager is retrieved 
 * (recall that the telemetry mode manager is a 
 * singleton class whose single instance is configured in another test case)</li>
 * <li>It is checked that the mode manager component is now configured.</li>
 * <li>The two packets are loaded in the mode manager and it is checked that 
 * the number of loaded packets is correctly reported.</li>
 * <li>The SID_B packet is loaded N-2 times(N being the capacity of the 
 * telemetry mode manager) and it is checked that the component reports: 
 * "mode manager is full". </li>
 * <li>An attempt is made to load a further packet and it is checked that this
 * results in the correct event report being generated.</li>
 * <li>The iterator service is checked.</li>
 * <li>The mode manager is asked to verify whether a packet with SID other
 * than SID_A or SID_B is loaded and it is verified that the return value is: "false".</li>
 * <li>Packet SID_A is unloaded and the success of the unload operation is checked.</li>
 * <li>It is attempted to unload a non-existent packet and it is checked that 
 * the correct event is created.</li>
 * <li>The iterator service is checked again.</li>
 * <li>Packet SID_A loaded again and then packet SID_B is unloaded 
 * and the 
 * success of the load/unload operations is checked.</li>
 * <li>The iterator service is checked again.</li>
 * <li>Packet SID_B is unloaded(the mode manager should now be empty)
 * and the 
 * success of the unload operation is checked.</li>
 * <li>The iterator service is checked again.</li>
 * </ol>
 * Note that this test case uses the telemetry packet factory. It assumes that the structure
 * of the factory is such as to allow two packets of type <code>DC_PUSDataReportingPacket</code>
 * to be loaded in the factory.
 * @see DC_PUSTelemetryModeManager
 * @see CC_TelemetryPacketFactory
 * @author Alessandro Pasetti(P&amp;P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEPUSTELEMETRYMODEMANAGER_1 "testcasepustelemetrymodemanager_1"

void TestCasePUSTelemetryModeManager_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCasePUSTelemetryModeManager_1 {
    TestCasePUSFull parent;
} TestCasePUSTelemetryModeManager_1;


typedef struct TestCasePUSTelemetryModeManager_1Class {
    TestCasePUSFullClass parent_class;
} TestCasePUSTelemetryModeManager_1Class;


#define TESTCASEPUSTELEMETRYMODEMANAGER_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCasePUSTelemetryModeManager_1Class, \
                                   obj, TYPE_TESTCASEPUSTELEMETRYMODEMANAGER_1)

#define TESTCASEPUSTELEMETRYMODEMANAGER_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCasePUSTelemetryModeManager_1Class, \
                                 klass, TYPE_TESTCASEPUSTELEMETRYMODEMANAGER_1)

#define TESTCASEPUSTELEMETRYMODEMANAGER_1(obj) \
        OBJECT_CHECK(TestCasePUSTelemetryModeManager_1, \
                                   obj, TYPE_TESTCASEPUSTELEMETRYMODEMANAGER_1)


TestCasePUSTelemetryModeManager_1* TestCasePUSTelemetryModeManager_1_new(void);

#endif
