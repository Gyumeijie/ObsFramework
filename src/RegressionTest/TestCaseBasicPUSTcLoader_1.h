//
//
// TestCaseBasicPUSTcLoader_1.h
//


#ifndef TESTCASEBASICPUSTCLOADER_1_H
#define TESTCASEBASICPUSTCLOADER_1_H


#include "../Utilities/TestCasePUSFull.h"
#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Qom/object.h"


/*
 * Check the functionality of the <code>DC_BasicPUSTcLoader</code>
 * class. The test case retrieves the following items from its super class
 * <code>TestCasePUSFull</code> or from the telecommand factory:<ul>
 * <li>An instance of the basic telecommand loader</li>
 * <li>Three instances of <code>DC_TestPUSTelecommand</code></li>
 * <li>The telecommand manager</li>
 * </ul>
 * The following specific checks are then performed:<ol>
 * <li>The correctness of the class identifier of the TC loader is checked.</li>
 * <li>The value of the maximum number of telecommands is set and read back. The correctness
 * of the read-back value is checked.</li>
 * <li>The value of the maximum length of a telecommand packet is set and read back. The correctness
 * of the read-back value is checked.</li>
 * <li>A single telecommand packet is written to the telecommand load area and the telecommand
 * loader is then activated. It is checked that the TC manager reports one telecommand loaded.</li>
 * <li>The loaded telecommand is retrieved from the telecommand manager and it is checked that
 * its configuration is as expected and that it is marked as "in use".</li>
 * <li>The telecommand manager is activated and it is checked that afterwards the telecommand 
 * is marked as "not in use".</li>
 * <li>Two telecommand packets are written to the telecommand load area of which one has a 
 * packet ID field that indicates that it should not be processed by the telecommand loader. The telecommand
 * loader is activated. It is checked that the TC manager reports only one telecommand loaded.</li>
 * <li>Three telecommand packets are written to the telecommand load area and the telecommand
 * loader is then activated. It is checked that the TC manager reports three telecommands loaded.</li>
 * <li>The loaded telecommands are retrieved from the telecommand manager and it is checked that
 * their configuration is as expected and that they are marked as "in use".</li>
 * <li>The telecommand manager is activated and it is checked that afterwards the three telecommands 
 * are marked as "not in use".</li>
 * <li>A telecommand packet is written that has a length exceeding 
 * the maximum accepted by the loader is written to the
 * telecommand load area. The TC loader is activated and it is checked that the correct event is
 * generated.</li>
 * <li>Two telecommand packets are written of which the first one has 
 * a type value not recognized by the TC loader is written to the
 * telecommand load area. The TC loader is activated and it is checked that the correct event is
 * generated.</li>
 * <li>A number of telecommands exceeding the maximum accepted by the loader are written to the
 * telecommand load area. The TC loader is activated and it is checked that the correct event is
 * generated.</li>
 * <li>Four <code>DC_BasicPUSTelecommands</code> are written to the
 * telecommand load area. The TC loader is activated and it is checked that the correct event is
 * generated. This test assumes that the telecommand fctory only manages three telecommand of
 * type <code>DC_BasicPUSTelecommands</code>.</li>
 * </ol>
 * Note that, in order to be loaded into the list of pending telecommands in the telecommand
 * manager, the test telecommands used in this test case are always configured to be valid.
 * @see DC_BasicPUSTcLoader
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEBASICPUSTCLOADER_1 "testcasebasicpustcloader_1"

void TestCaseBasicPUSTcLoader_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseBasicPUSTcLoader_1 {
    TestCasePUSFull parent;

    unsigned char *tcArea;
    DC_BasicPUSTcLoader *pTCL;
} TestCaseBasicPUSTcLoader_1;


typedef struct TestCaseBasicPUSTcLoader_1Class {
    TestCasePUSFullClass parent_class;
} TestCaseBasicPUSTcLoader_1Class;


#define TESTCASEBASICPUSTCLOADER_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseBasicPUSTcLoader_1Class, \
                                          obj, TYPE_TESTCASEBASICPUSTCLOADER_1)

#define TESTCASEBASICPUSTCLOADER_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseBasicPUSTcLoader_1Class, \
                                        klass, TYPE_TESTCASEBASICPUSTCLOADER_1)

#define TESTCASEBASICPUSTCLOADER_1(obj) \
        OBJECT_CHECK(TestCaseBasicPUSTcLoader_1, \
                                          obj, TYPE_TESTCASEBASICPUSTCLOADER_1)


TestCaseBasicPUSTcLoader_1* TestCaseBasicPUSTcLoader_1_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Write the header part of a <code>DC_TestPUSTelecommand</code> packet starting at location
 * <code>start</code> with a configuration as defined by the method parameters.
 * Both the packet header and the header part of the packet data field are written.
 * @see DC_TestPUSTelecommand
 * @param start the location in the telecommand loader where the TC header is to be written
 * @param packetID the packet ID
 * @param packetSeqControl the packet sequence control
 * @param packetLength the packet length
 * @param ackField the acknowledge field
 * @param tcType the TC type
 * @param tcSubType the TC subtype
 * @param tcSource the TC source
 */
void TestCaseBasicPUSTcLoader_1_writeTcHeader
(
    TestCaseBasicPUSTcLoader_1 *This,
    unsigned int start, 
    unsigned short packetId, 
    unsigned short packetSeqControl,
    unsigned short packetLength, 
    unsigned char ackField, 
    unsigned char tcType,
    unsigned char tcSubType, 
    TD_TelecommandSource tcSource
);

/**
 * Write the data part of a <code>DC_TestPUSTelecommand</code> packet starting at location
 * <code>start</code> with a configuration as defined by the method parameters.
 * @see DC_TestPUSTelecommand
 * @param start the location in the telecommand loader where the TC data are to be written
 * @param execCounter the execution counter value
 * @param execCheckVal the execution check value
 * @param valCheckVal the validity check value
 * @param execCheckCode the execution check code
 * @param valCheckCode the validity check code
 * @param execOutcome the outcome of the execution check 
 */
void TestCaseBasicPUSTcLoader_1_writeTcData
(
    TestCaseBasicPUSTcLoader_1 *This,
    unsigned int start, 
    unsigned int execCounter, 
    bool execCheckVal,
    bool valCheckVal, 
    TD_CheckCode execCheckCode,
    TD_CheckCode valCheckCode, 
    bool execOutcome
);
/**
 * Check that the argument <code>DC_TestPUSTelecommand</code> telecommand is configured as specified by the
 * method parameters. Note that in order to check the execution outcome, the method "executes"
 * the telecommand and therefore causes its execution counter to be incremented by one.
 * @see DC_TestPUSTelecommand
 * @param pTC the telecommand to be checked
 * @param packetID the packet ID
 * @param packetSeqControl the packet sequence control
 * @param ackField the acknowledge field
 * @param tcSource the TC source
 * @param execCounter the execution counter value
 * @param execCheckVal the execution check value
 * @param valCheckVal the validity check value
 * @param execCheckCode the execution check code
 * @param valCheckCode the validity check code
 * @param execOutcome the outcome of the execution check 
 * @return true if the telecommand is configured as specified
 */
bool TestCaseBasicPUSTcLoader_1_checkTcConfig
(
    TestCaseBasicPUSTcLoader_1 *This,
    DC_TestPUSTelecommand *pTC, 
    unsigned short packetID, 
    unsigned short packetSeqControl,
    unsigned char ackField, 
    TD_TelecommandSource tcSource,
    unsigned int execCounter, 
    bool execCheckVal,
    bool valCheckVal, 
    TD_CheckCode execCheckCode,
    TD_CheckCode valCheckCode, 
    bool execOutcome
);

#endif
