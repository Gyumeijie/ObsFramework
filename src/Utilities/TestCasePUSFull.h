//
//
// TestCasePUSFull.h
//
//
// Change Record:


#ifndef TESTCASEPUSFULL_H
#define TESTCASEPUSFULL_H


#include "../Utilities/TestCaseWithFactories.h"
#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/TestConstants.h"
#include "../Qom/object.h"


/*
 * Base class for test cases that implement a PUS-related scenario.
 * The test set-up procedure creates and configures several PUS-related components:
 * <ul>
 * <li>Telecommand loader of type <code>DC_BasicPUSTcLoader</code></li>
 * <li>Telecommand manager</li>
 * <li>Telemetry manager</li>
 * <li>PUS Telemetry mode manager of type <code>DC_PUSTelemetryModeManager</code></li>
 * <li>Logger telemetry stream of type <code>DC_PUSTmLogger</code></li>
 * <li>PUS event repository of type <code>DC_PUSEventRepository</code></li>
 * <li>Manoeuvre manager</li>
 * <li>Dummy OBS Clock of type <code>DC_DummyObsClock</code></li>
 * </ul>
 * The event repository is loaded in the <code>CC_RootObject</code>
 * which is then unloaded in the shutdown procedure. 
 * All the above items are created as static instances and are accessible 
 * through getter methods defined by this class.
 * <p>
 * This class is especially useful for test cases that want to perform end-to-end
 * tests of PUS-related functionalities(many components they require are
 * already instantiated and configured) and generally for test cases that
 * exercise PUS-related functionalities.
 * <p>
 * In order to facilitate the task of the test developers, this class offers utility
 * methods to load the telecommand load area associated to the telecommand loader
 * with data representing instances of several types of telecommand packets.
 * The telecommand packet data are loaded in the command load area associated to the
 * telecommand loader managed by this class. This class is responsible for managing the
 * command load area. It updates its first byte that holds the number of telecommand packets
 * currently stored in the command area and it maintains a <i>command area position
 * index</i> that points to the location in the command area where the next telecommand packet
 * should be written. The position index is initialized to 1 and can be reset with method 
 * <code>resetCommandLoadArea</code>. The utility methods write both the header and the
 * application data part of the telecommand packet.  In general, except for the acknowledge 
 * field(which is specified by the caller), all other information in the telecommand packet 
 * header is given fixed default values. The header is written by method <code>writeTcHeader</code>.
 * <p>
 * If there is no space left in the command load area to store the telecommand packet specified
 * by the caller of this method, then the method returns a value of false. Otherwise, the
 * telecommand is written to the command load area and a value of true is returned.
 * @author A. Pasetti
 * @version 1.0
 * @ingroup TestCases
 */
#define TYPE_TESTCASEPUSFULL "testcasepusfull"

void TestCasePUSFull_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct TestCasePUSFull {
    TestCaseWithFactories parent;

    unsigned int tcCmdPos;
    DC_EventRepository *pOldEvtRep;
};


struct TestCasePUSFullClass {
    TestCaseWithFactoriesClass parent_class;

    void (*post_init)(TestCasePUSFull *This, int testId, char *testName);
};


#define TESTCASEPUSFULL_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCasePUSFullClass, obj, TYPE_TESTCASEPUSFULL)

#define TESTCASEPUSFULL_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCasePUSFullClass, klass, TYPE_TESTCASEPUSFULL)

#define TESTCASEPUSFULL(obj) \
        OBJECT_CHECK(TestCasePUSFull, obj, TYPE_TESTCASEPUSFULL)


TestCasePUSFull* TestCasePUSFull_new(int testId,char *testName);



///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Helper method that writes a default telecommand packet header to the
 * telecommand load. 
 * This method is called by the methods that write telecommands packets
 * to the telecommand load area. 
 * @param length the "packet length" field of the telecommand packet
 * @param packetSeqControl the packet sequence control field of the telecommand packet
 */
void TestCasePUSFull_writeTcHeader
(
    TestCasePUSFull *This, 
    unsigned short length, 
    unsigned short packetSeqControl
);

/**
 * Return the telecommand manager created by the initialization
 * procedure of this test case.
 * @return the telecommmand manager
 */
CC_TelecommandManager* TestCasePUSFull_getTelecommandManager
(
    const TestCasePUSFull *This
);

/**
 * Return the telemetry manager created by the initialization
 * procedure of this test case.
 * @return the telemetry manager
 */
CC_TelemetryManager* TestCasePUSFull_getTelemetryManager
(
    const TestCasePUSFull *This
);

/**
 * Return the telemetry mode manager created by the initialization
 * procedure of this test case.
 * @return the telemetry mode manager
 */
DC_PUSTelemetryModeManager* TestCasePUSFull_getTelemetryModeManager
(
    const TestCasePUSFull *This
);

/**
 * Return the manoeuvre manager created by the initialization
 * procedure of this test case.
 * @return the manoeuvre manager
 */
CC_ManoeuvreManager* TestCasePUSFull_getManoeuvreManager
(
    const TestCasePUSFull *This
);

/**
 * Return the telecommand loader created by the initialization
 * procedure of this test case.
 * @return the telecommand loader
 */
DC_BasicPUSTcLoader* TestCasePUSFull_getTcLoader
(
    const TestCasePUSFull *This
);

/**
 * Return the telemetry stream created by the initialization
 * procedure of this test case.
 * @return the telemetry stream
 */
DC_PUSTmLogger* TestCasePUSFull_getTmStream
(
    const TestCasePUSFull *This
);

/**
 * Return the OBS clock created by the initialization
 * procedure of this test case.
 * @return the OBS clock
 */
DC_DummyObsClock* TestCasePUSFull_getObsClock
(
    const TestCasePUSFull *This
);

/**
 * Return the PUS Event Repository created by the initialization
 * procedure of this test case.
 * @return the PUS event repository
 */
DC_PUSEventRepository* TestCasePUSFull_getEventRepository
(
    const TestCasePUSFull *This
);

/**
 * Load the <i>command load area</i> with data representing a <code>DC_TestPUSTelecommand</code> 
 * telecommand packet.
 * @see DC_TestPUSTelecommand
 * @param ackField the acknowledge field of the telecommand 
 * @param execCounter the execution counter value
 * @param execCheckVal the execution check value
 * @param valCheckVal the validity check value
 * @param execCheckCode the execution check code
 * @param valCheckCode the validity check code
 * @param execOutcome the outcome of the execution check 
 * @param packetSeqControl the packet sequence control field
 * @return true if the telecommand packet could be successfully written, false otherwise
 */
bool TestCasePUSFull_writeTestPUSTelecommand
(
    TestCasePUSFull *This, 
    unsigned char ackField, 
    unsigned int execCounter, 
    bool execCheckVal, 
    bool valCheckVal, 
    TD_CheckCode execCheckCode,
    TD_CheckCode valCheckCode, 
    bool execOutcome, 
    unsigned short packetSeqControl
);

/**
 * Load the <i>command load area</i> with data representing a <code>DC_PUSDefineDataReporting</code> 
 * telecommand packet.
 * A simple instance of the telecommand is written that includes only one parameter to be 
 * sample at every collection interval.
 * @see DC_PUSDefineDataReporting
 * @param ackField the acknowledge field of the telecommand 
 * @param collectionInterval the collection interval
 * @param sid the SID of the packet being defined
 * @param par the parameter to be sampled 
 * @param packetSeqControl the packet sequence control field
 * @param tcSubType the subtype of the telecommand packet 
 * @return true if the telecommand packet could be successfully written, false otherwise
 */
bool TestCasePUSFull_writePUSDefineDataReporting
(
    TestCasePUSFull *This, 
    unsigned char ackField, 
    TD_PUSCollectionInterval collectionInterval, 
    TD_SID sid, 
    TD_DataPoolId par, 
    unsigned short packetSeqControl,
    TD_TelecommandSubType tcSubType
);

/**
 * Load the <i>command load area</i> with data representing either a <code>DC_PUSControlDataReporting</code>, 
 * or a <code>DC_PUSClearDataReporting</code>, or a <code>DC_PUSRequestDataReporting</code>
 * telecommand packet.
 * The telecommand content is specified by its subtype and by an array that holds the SIDs of 
 * data reporting telecommands that must be controlled, cleared, or requested.
 * @see DC_PUSDefineDataReporting
 * @param ackField the acknowledge field of the telecommand 
 * @param NSID the number of SIDs in the telecommand
 * @param sid the array holding the SIDs
 * @param tcSubType the telecommand subtype
 * @param packetSeqControl the packet sequence control field
 * @return true if the telecommand packet could be successfully written, false otherwise
 */
bool TestCasePUSFull_writePUSDataReportingControl
(
    TestCasePUSFull *This, 
    unsigned char ackField, 
    unsigned char NSID, 
    TD_SID *sid, 
    TD_TelecommandSubType tcSubType, 
    unsigned short packetSeqControl
);

/**
 * Clear the <i>command load area</i>. The command load area position index is reset to 
 * one and the first byte of the command load area is reset to zero.
 */
void TestCasePUSFull_resetCommandLoadArea
(
    TestCasePUSFull *This
);


#endif
