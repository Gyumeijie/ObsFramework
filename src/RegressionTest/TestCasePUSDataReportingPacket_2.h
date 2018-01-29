//
//
// TestCasePUSDataReportingPacket_2.h
//


#ifndef TESTCASEPUSDATAREPORTINGPACKET_2_H
#define TESTCASEPUSDATAREPORTINGPACKET_2_H


#include "../Utilities/TestCaseWithEvtCheck.h"
#include "../Qom/object.h"


/*
 * Check the functionality of the <code>DC_PUSDataReportingPacket</code>
 * class for the case of a packet that contains one single fixed-length
 * array of oversampled parameters. The test starts with the creation
 * of one data pool to serve as the source of the data to be collected.
 * This data pool is loaded into <code>CC_RootObject</code> as <i>system
 * data pool</i>.
 * Then, a data reporting packet instance is created and configured to
 * have a collection interval equal to 6 and one fixed-length array with
 * two parameters and repetition count equal to 2 (ie. two samples per
 * collection interval). The data reporting packet is configured and
 * enabled and the following
 * specific checks are performed upon it:<ol>
 * <li>Three consecutive update requests are sent to the packet each followed by a data
 * acquisition request. It is checked that in both cases the data acquisition service
 * reports: "no telemetry data".</li>
 * <li>The values of the data items in the data pool are updated and then two more update
 * requests are sent to the packet followed by a data
 * acquisition request. It is checked that the data acqusition service
 * reports: "no telemetry data".</li>
 * <li>A sixth update request is sent to the packet followed by a data acquisition
 * request. The correctness of the data returned by the data acqusition service
 * is checked.</li>
 * <li>The values of the data pool items are updated and six update-acquisition cycles
 * are executed. The correctness of the data returned by the data acqusition service
 * is then checked.</li>
 * <li>Non-nominal behaviour check: it is attempted to load a packet definition whose
 * number of fixed-length arrays exceeds the allowed maximum and it is checked
 * that the correct event is generated.</li>
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
#define TYPE_TESTCASEPUSDATAREPORTINGPACKET_2 "testcasepusdatareportingpacket_2"

void TestCasePUSDataReportingPacket_2_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCasePUSDataReportingPacket_2 {
    TestCaseWithEvtCheck parent;
} TestCasePUSDataReportingPacket_2;


typedef struct TestCasePUSDataReportingPacket_2Class {
    TestCaseWithEvtCheckClass parent_class;
} TestCasePUSDataReportingPacket_2Class;


#define TESTCASEPUSDATAREPORTINGPACKET_2_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCasePUSDataReportingPacket_2Class, \
                                    obj, TYPE_TESTCASEPUSDATAREPORTINGPACKET_2)

#define TESTCASEPUSDATAREPORTINGPACKET_2_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCasePUSDataReportingPacket_2Class, \
                                  klass, TYPE_TESTCASEPUSDATAREPORTINGPACKET_2)

#define TESTCASEPUSDATAREPORTINGPACKET_2(obj) \
        OBJECT_CHECK(TestCasePUSDataReportingPacket_2, \
                                    obj, TYPE_TESTCASEPUSDATAREPORTINGPACKET_2)


TestCasePUSDataReportingPacket_2* TestCasePUSDataReportingPacket_2_new(void);

#endif
