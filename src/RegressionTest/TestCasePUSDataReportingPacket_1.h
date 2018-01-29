//
//
// TestCasePUSDataReportingPacket_1.h
//


#ifndef TESTCASEPUSDATAREPORTINGPACKET_1_H
#define TESTCASEPUSDATAREPORTINGPACKET_1_H


#include "../Utilities/TestCaseWithEvtCheck.h"
#include "../Qom/object.h"


/*
 * Check the functionality of the <code>DC_PUSDataReportingPacket</code>
 * class for the case of a packet that only contains parameters to be
 * sampled once per collection interval. The test starts with the creation
 * of one data pool to serve as the source of the data to be collected.
 * This data pool is loaded into <code>CC_RootObject</code> as <i>system
 * data pool</i>.
 * Then, a data reporting packet instance is created and configured to
 * have a collection interval equal to 3 and two parameters. The following
 * specific checks are then performed:<ol>
 * <li>The correctness of the class identifier is checked.</li>
 * <li>It is checked that the component is initially not configured.</li>
 * <li>The maximum number of fixed-length array is set and the correctness of the
 * set operation is checked.</li>
 * <li>The maximum size of the packet definition buffer is set and the correctness of the
 * set operation is checked.</li>
 * <li>The maximum size of the packet value buffer is set and the correctness of the
 * set operation is checked.</li>
 * <li>It is checked that the component is now configured.</li>
 * <li>It is checked that the component is disabled.</li>
 * <li>The packet definition is loaded and the success of the load operation is checked.</li>
 * <li>Three consecutive update requests are sent to the packet each followed by a data
 * acquisition request. It is checked that in all three cases the data acquisition service
 * reports: "no telemetry data".</li>
 * <li>The component is enabled and the correctness of the new enable status is checked.</li>
 * <li>Two consecutive update requests are sent to the packet each followed by a data
 * acquisition request. It is checked that in both cases the data acquisition service
 * reports: "no telemetry data".</li>
 * <li>The values of the data items in the data pool are updated and then a third update request
 * is sent to the packet followed by a data
 * acquisition request. It is checked that the data acqusition service
 * now returns the correct values of the data pool items.</li>
 * <li>It is checked that the fast version of the data acquisition service is provided.</li>
 * <li>The data in the packet are acquired and checked again using the fast version of the
 * data acquisition service.</li>
 * <li>The values of the data pool items are updated. Three more update-acquisition cycles are executed and
 * it is checked that the data returned by the component are correct.</li>
 * <li>A new report definition packet is loaded with the following characteristics: collection
 * interval equal to 2, 1 single paramater. Two update-acqusition cycles are executed and
 * it is checked that the data returned by the component are correct.</li>
 * <li>Non-nominal behaviour check: it is attempted to load a packet definition that exceeds
 * the maximum allowed size and it is checked that the correct event is generated.</li>
 * </ol>
 * This test case uses the <code>DC_SampleFullDataPool</code> as system data pool. The
 * implementation of the test case assumes the following about this data pool:<ul>
 * <li>The data pool contains at least two data pool items with identifiers 1 and 2.</li>
 * <li>The data pool item with identifier equal to 1 is of type <code>TD_Integer</code>.</li>
 * <li>The data pool item with identifier equal to 2 is of type <code>TD_Float</code>.</li>
 * </ul>
 * @see DC_PUSDataReportingPacket
 * @see DC_SampleFullDataPool
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEPUSDATAREPORTINGPACKET_1 "testcasepusdatareportingpacket_1"

void TestCasePUSDataReportingPacket_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCasePUSDataReportingPacket_1 {
    TestCaseWithEvtCheck parent;
} TestCasePUSDataReportingPacket_1;


typedef struct TestCasePUSDataReportingPacket_1Class {
    TestCaseWithEvtCheckClass parent_class;
} TestCasePUSDataReportingPacket_1Class;


#define TESTCASEPUSDATAREPORTINGPACKET_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCasePUSDataReportingPacket_1Class, \
                                    obj, TYPE_TESTCASEPUSDATAREPORTINGPACKET_1)

#define TESTCASEPUSDATAREPORTINGPACKET_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCasePUSDataReportingPacket_1Class, \
                                  klass, TYPE_TESTCASEPUSDATAREPORTINGPACKET_1)

#define TESTCASEPUSDATAREPORTINGPACKET_1(obj) \
        OBJECT_CHECK(TestCasePUSDataReportingPacket_1, \
                                    obj, TYPE_TESTCASEPUSDATAREPORTINGPACKET_1)


TestCasePUSDataReportingPacket_1* TestCasePUSDataReportingPacket_1_new(void);

#endif
