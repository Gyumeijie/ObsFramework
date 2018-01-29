//
//
// TestCasePUSClearDataReporting_1.h
//


#ifndef TESTCASEPUSCLEARDATAREPORTING_1_H
#define TESTCASEPUSCLEARDATAREPORTING_1_H


#include "../Utilities/TestCasePUSFull.h"
#include "../Qom/object.h"


/*
 * Check the functionality of the <code>DC_PUSClearDataReporting</code>. 
 * One instance of this class is created. Two data 
 * reporting telemetry packets are retrieved from the telemetry packet factory and
 * configured 
 * with SIDs equal to SID_A and SID_B. The SID_B packet is loaded in the PUS 
 * Telemetry Mode Manager. 
 * The following specific tests are then performed:<ol>
 * <li>The correctness of the class identifier is checked.</li>
 * <li>It is checked that the telecommand component is initially not configured.</li>
 * <li>The maximum number of SIDs is set to 2 and its value is read back. The correctness of the read-back value is 
 * checked.</li>
 * <li>The telemetry manager is loaded and the correctness of the load operation
 * is checked.</li>
 * <li>The PUS telemetry mode manager is loaded and the correctness of the load operation
 * is checked.</li>
 * <li>It is checked that the component is now configured.</li>
 * <li>The telecommand is loaded with raw data representing a request to clear two 
 * telemetry packet with SID equal to SID_A and SID_B. It is checked that the validity check of the
 * telecommand returns: "telecommand is valid".</li>
 * <li>The telecommand is executed and it is checked that the two telemetry
 * packets are now marked as "not in use" and that the SID_B packet has been 
 * unloaded from the PUS Telemetry Mode Manager.</li>
 * <li>The telecommand is executed again and it is checked that this time it returns
 * ACTION_FAILURE".</li>
 * <li>Non-nominal behaviour check: an attempt is made to load the telecommand with too many SIDs and the
 * correctness of the validity check code is checked.</li>
 * <li>Non-nominal behaviour check: an attempt is made to load the telecommand with too many raw data and the
 * correctness of the validity check code is checked.</li>
 * <li>Non-nominal behaviour check: an attempt is made to load the telecommand with an inconsistent number of raw data and the
 * correctness of the validity check code is checked.</li>
 * </ol>
 * Note that this test case uses the telemetry packet factory. It assumes that the structure
 * of the factory is such as to allow two packets of type <code>DC_PUSDataReportingPacket</code>
 * to be loaded in the factory.
 * @see DC_PUSControlDataReporting
 * @see CC_TelemetryPacketFactory
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEPUSCLEARDATAREPORTING_1 "testcasepuscleardatareporting_1"

void TestCasePUSClearDataReporting_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCasePUSClearDataReporting_1 {
    TestCasePUSFull parent;
} TestCasePUSClearDataReporting_1;


typedef struct TestCasePUSClearDataReporting_1Class {
    TestCasePUSFullClass parent_class;
} TestCasePUSClearDataReporting_1Class;


#define TESTCASEPUSCLEARDATAREPORTING_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCasePUSClearDataReporting_1Class, \
                                     obj, TYPE_TESTCASEPUSCLEARDATAREPORTING_1)

#define TESTCASEPUSCLEARDATAREPORTING_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCasePUSClearDataReporting_1Class, \
                                   klass, TYPE_TESTCASEPUSCLEARDATAREPORTING_1)

#define TESTCASEPUSCLEARDATAREPORTING_1(obj) \
        OBJECT_CHECK(TestCasePUSClearDataReporting_1, \
                                     obj, TYPE_TESTCASEPUSCLEARDATAREPORTING_1)


TestCasePUSClearDataReporting_1* TestCasePUSClearDataReporting_1_new(void);

#endif
