//
//
// TestConstants.h
//

#ifndef TESTCONSTANTS_H
#define TESTCONSTANTS_H

/**
 * @file TestConstants.h 
 * This file defines all the constants used in the test classes 
 * of the OBS Framework. Constants
 * are defined using the <code>const</code> construct provided by the
 * C++ language. They are <i>not</i> defined using the <code>#define</code>
 * construct of the C language. Constants used in the operational classes
 * are defined in a dedicated header file (<code>Constants</code>).
 */

#include "../GeneralInclude/BasicTypes.h"

// Useful symbolic constants defining success/failure conditions for
// the three stages of a test case

/**
 * Return value of a test case whose execution was successful
 * @see TestCase#runTestCase
 */
#define TEST_SUCCESS true   

/**
 * Return value of a test case whose execution failed
 * @see TestCase#runTestCase
 */
#define TEST_FAILURE false

/**
 * Return value of a test case whose set up service succeeded
 * @see TestCase#setUpTestCase
 */
#define INITIALIZATION_SUCCESS true  

/**
 * Return value of a test case whose set up service failed
 * @see TestCase#setUpTestCase
 */
#define INITIALIZATION_FAILURE false  

/**
 * Return value of a test case whose shut down service succeeded
 * @see TestCase#setUpTestCase
 */
#define SHUTDOWN_SUCCESS true  

/**
 * Return value of a test case whose shut down service failed
 * @see TestCase#setUpTestCase
 */
#define SHUTDOWN_FAILURE false  

/**
 * Max number of test cases that can be loaded in a test suite
 * @see TestSuite
 */
#define MAX_TEST_CASES_IN_SUITE   200   

/**
 * Event repository size used for the regression tests.
 * @see DC_EventRepository
 */
#define EVT_REP_SIZE   14

/**
 * A small float value used when comparing float values. For instance,
 * when comparing a and b (both float variables), the comparison is really made
 * between abs(a-b) and EPS_FLOAT. This helps prevent false triggers due to rounding and other numerical
 * precision effects.
 * @see #EPS_DOUBLE
 */
#define EPS_FLOAT   (float)0.00001

/**
 * A small float value used when comparing double values. For instance,
 * when comparing a and b (both double variables), the comparison is really made
 * between abs(a-b) and EPS_DOUBLE. This helps prevent false triggers due to rounding and other numerical
 * precision effects.
 * @see #EPS_FLOAT
 */
#define EPS_DOUBLE   (double)0.000001

/**
 * Constant string used in the construction of the name of the documentation file for
 * the test cases. The <code>RegressionTest</code> program generates a test report
 * that containts hyperlinks to the documentation file of the test cases. The
 * construction of the hyperlinks assumes the name of the test file to be:
 * "TEST_FILE_NAME_1"+"test name"+"TEST_FILE_NAME_2"+".html".
 * @see TEST_FILE_NAME_2
 */
#define TEST_FILE_NAME_1   "class"

/**
 * Constant string used in the construction of the name of the documentation file for
 * the test cases.
 * @see TEST_FILE_NAME_2
 */
#define TEST_FILE_NAME_2   ""

/**
 * Maximum length of the name of a test case.
 * @see doubleUnderscore
 */
#define MAX_TEST_FILE_NAME_LENGTH   100

/**
 * Constant string defining the name of the log file used by the test tracer component.
 * @see DC_TestTracer
 */
#define TEST_TRACER_LOG_FILE   "TestTracerLogFile.txt"

/**
 * Telemetry packet type used in the test telemetry packet defined by class
 * <code>DC_DummyPUSTelemetryPacket</code>.
 * @see DC_DummyPUSTelemetryPacket
 */
#define TEST_TM_TYPE   101

/**
 * Telecommand packet type used in the test telecommand packet defined by class
 * <code>DC_DummyPUSTelecommand</code>.
 * @see DC_DummyPUSTelecommand
 */
#define TEST_TC_TYPE   91

/**
 * Telemetry packet subtype used in the test telemetry packet defined by class
 * <code>DC_DummyPUSTelemetryPacket</code>.
 * @see DC_DummyPUSTelemetryPacket
 */
#define TEST_TM_SUBTYPE   102

/**
 * Telecommand packet subtype used in the test telecommand packet defined by class
 * <code>DC_DummyPUSTelecommand</code>.
 * @see DC_DummyPUSTelecommand
 */
#define TEST_TC_SUBTYPE   92

/**
 * Telemetry packet timetag used in the test telemetry packet defined by class
 * <code>DC_DummyPUSTelemetryPacket</code>.
 * @see DC_DummyPUSTelemetryPacket
 */
#define TEST_TM_TIMETAG   103

/**
 * Telemetry packet destination used in the test telemetry packet defined by class
 * <code>DC_DummyPUSTelemetryPacket</code>.
 * @see DC_DummyPUSTelemetryPacket
 */
#define TEST_TM_DEST   104

/**
 * Telecommand packet source used in the test telecommand packet defined by class
 * <code>DC_DummyPUSTelecommand</code>.
 * @see DC_DummyPUSTelecommand
 */
#define TEST_TC_SOURCE   94

/**
 * Telecommand identifier used in the test telecommand packet defined by class
 * <code>DC_DummyPUSTelecommand</code>.
 * @see DC_DummyPUSTelecommand
 */
#define TEST_TC_ID   95

/**
 * Telemetry packet default destination used in the test cases.
 * <code>DC_DummyPUSTelemetryPacket</code>.
 * @see DC_DummyPUSTelemetryPacket
 */
#define TEST_TM_DEF_DEST   111

/**
 * APID of the source application of the PUS telemetry packets used in the test 
 * cases.
 * @see PUSTelemetryPacket
 */
#define TEST_TM_APID   105

/**
 * APID of the destination application of the PUS telecommand packets used in the test 
 * cases.
 * @see PUSTelecommand
 */
#define TEST_TC_APID   106

/**
 * Maximum number of fixed-length array of the <code>DC_PUSDataReportingPacket</code> items
 * in the telemetry packet factory.
 * @see TestCaseGenericSetUp#setUpTestCase
 */
#define PUS_DRP_MAX_FA   4

/**
 * Large value of the definition buffer size of the <code>DC_PUSDataReportingPacket</code> items
 * in the telemetry packet factory.
 * @see TestCaseGenericSetUp#setUpTestCase
 */
#define PUS_DRP_DEF_BUF_SIZE_LARGE   100

/**
 * Small value of the definition buffer size of the <code>DC_PUSDataReportingPacket</code> items
 * in the telemetry packet factory.
 * @see TestCaseGenericSetUp#setUpTestCase
 */
#define PUS_DRP_DEF_BUF_SIZE_SMALL   50

/**
 * Large value of the value buffer size of the <code>DC_PUSDataReportingPacket</code> items
 * in the telemetry packet factory.
 * @see TestCaseGenericSetUp#setUpTestCase
 */
#define PUS_DRP_VAL_BUF_SIZE_LARGE   100

/**
 * Large value of the value buffer size of the <code>DC_PUSDataReportingPacket</code> items
 * in the telemetry packet factory.
 * @see TestCaseGenericSetUp#setUpTestCase
 */
#define PUS_DRP_VAL_BUF_SIZE_SMALL   50

/**
 * Size of the pending telecommand list in the telecommand manager.
 * @see TestCasePUSFull#setUpTestCase
 */
#define TC_MAN_PEND_TC_LIST_SIZE   5

/**
 * Size of the immediate disptach queue in the telemetry manager.
 * @see TestCasePUSFull#setUpTestCase
 */
#define TM_MAN_IMMEDIATE_QUEUE   5

/**
 * Maximum number of PUS packets that can be loaded in a PUS telemetry mode
 * manager.
 * @see TestCasePUSFull#setUpTestCase
 */
#define TM_MODE_MAN_MAX_N_PACKETS   5

/**
 * Size of the pending manoeuvre list in the manoeuvre manager.
 * @see TestCasePUSFull#setUpTestCase
 */
#define MAN_MAN_PENDING_MAN_LIST_SIZE   5

/**
 * Maximum number of telecommands for the <code>DC_BasicPUSTcLoader</code>.
 * @see TestCasePUSFull#setUpTestCase
 */
#define TC_COMMAND_AREA_MAX_N_TC   3

/**
 * Maximum length of a telecommand for the <code>DC_BasicPUSTcLoader</code>.
 * @see TestCasePUSFull#setUpTestCase
 */
#define TC_COMMAND_AREA_MAX_TC_LEN   100

/**
 * Capacity of the telemetry buffer in the <code>DC_PUSTmLogger</code>.
 * @see TestCasePUSFull#setUpTestCase
 */
#define TM_LOGGER_BUFFER_CAPACITY   10

/**
 * Maximum length of the application data of a telemetry packet in the
 * telemetry logger stream (class <code>DC_PUSTmLogger</code>).
 * @see TestCasePUSFull#setUpTestCase
 */
#define TM_LOGGER_MAX_TM_LENGTH   40

/**
 * Size of the PUS event repository (instance of class <code>DC_PUSEventRepository</code>).
 * @see TestCasePUSFull#setUpTestCase
 */
#define PUS_EVT_REP_SIZE   15

/**
 * Default value of telecommand packet source used in PUS tests.
 * @see TestCasePUSFull#setUpTestCase
 */
#define DEF_PUS_TC_SOURCE   13

/**
 * Maximum number of memory blocks that can be handled by memory management telecommands
 * and telemetry packets.
 * @see TestCasePUSFull#setUpTestCase
 */
#define PUS_NUMBER_MEM_BLOCKS   3

/**
 * Size of the internal buffer used by the memory management telecommands and telemetry packets.
 * @see TestCasePUSFull#setUpTestCase
 */
#define PUS_MEM_BUFFER_LENGTH   50

#endif
