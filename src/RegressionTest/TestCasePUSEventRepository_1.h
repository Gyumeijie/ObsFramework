//
//
// TestCasePUSEventRepository_1.h
//


#ifndef TESTCASEPUSEVENTREPOSITORY_1_H
#define TESTCASEPUSEVENTREPOSITORY_1_H


#include "../Utilities/TestCasePUSFull.h"
#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Qom/object.h"


/*
 * Check the functionality of the <code>DC_PUSEventRepository</code>
 * class. The test case retrieves the following items from its super class
 * <code>TestCasePUSFull</code> or from the telecommand factory:<ul>
 * <li>The PUS event repository</li>
 * <li>One instance of <code>DC_TestPUSTelecommand</code></li>
 * <li>One instance of <code>DC_DummyConfigurableManoeuvre</code></li>
 * </ul>
 * The following specific checks are then performed:<ol>
 * <li>The correctness of the class identifier of the event repository is checked.</li>
 * <li>The <code>create</code> method for telecommands is called repeatedly with 
 * the test telecommand as argument 
 * and with all possible event identifiers that this method can handle(see class
 * comment of class <code>DC_PUSEventRepositor</code> for the full list). It is
 * then checked that the correct telemetry package has been loaded in the immediate
 * dispatch queue of the telemetry manager.</li>
 * <li>For one of the repeated calls described at the previous bullet, it is also checked 
 * that the event counter is correctly updated and that an event of the correct type is
 * stored in the event repository.</li>
 * <li>Calls with "success events" (events that denote the successful acceptance, start, 
 * progress, or completion of a telecommand), the test is repeated twice, first with the
 * associated acknowledge flag in the telecommand set to false and then to true and it is
 * checked that telemetry packet dispatching is only performed in the latter case.</li>
 * <li>A call to the create method for telecommands is performed when there are no more
 * free <code>DC_PUSTcVerificationPackets</code> available in the telemetry factory and it is
 * checked that the correct event is generated.</li>
 * <li>The <code>create</code> method for manoeuvres is called repeatedly with 
 * the test telecommand as argument 
 * and with all possible event identifiers that this method can handle(see class
 * comment of class <code>DC_PUSEventRepositor</code> for the full list). It is
 * then checked that the correct telemetry package has been loaded in the immediate
 * dispatch queue of the telemetry manager.</li>
 * <li>For one of the repeated calls described at the previous bullet, it is also checked 
 * that the event counter is correctly updated and that an event of the correct type is
 * stored in the event repository.</li>
 * <li>Calls with "success events" (events that denote the successful acceptance, start, 
 * progress, or completion of a telecommand manoeuvre), the test is repeated twice, first with the
 * associated acknowledge flag in the manoeuvre set to false and then to true and it is
 * checked that telemetry packet dispatching is only performed in the latter case.</li>
 * <li>A call to the create method for manoeuvre is performed when there are no more
 * free <code>DC_PUSTcVerificationPackets</code> available in the telemetry factory and it is
 * checked that the correct event is generated.</li>
 * </ol>
 * @see DC_PUSEventRepository
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEPUSEVENTREPOSITORY_1 "testcasepuseventrepository_1"

void TestCasePUSEventRepository_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCasePUSEventRepository_1 {
    TestCasePUSFull parent;
} TestCasePUSEventRepository_1;


typedef struct TestCasePUSEventRepository_1Class {
    TestCasePUSFullClass parent_class;
} TestCasePUSEventRepository_1Class;


#define TESTCASEPUSEVENTREPOSITORY_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCasePUSEventRepository_1Class, \
                                        obj, TYPE_TESTCASEPUSEVENTREPOSITORY_1)

#define TESTCASEPUSEVENTREPOSITORY_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCasePUSEventRepository_1Class, \
                                      klass, TYPE_TESTCASEPUSEVENTREPOSITORY_1)

#define TESTCASEPUSEVENTREPOSITORY_1(obj) \
        OBJECT_CHECK(TestCasePUSEventRepository_1, \
                                        obj, TYPE_TESTCASEPUSEVENTREPOSITORY_1)


TestCasePUSEventRepository_1* TestCasePUSEventRepository_1_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Check that the telemetry packet loaded by the argument PUS event repository in the
 * telemetry manager is correctly configured.
 * The method retrieves the telemetry manager from the PUS event repository and then
 * retrieves the telemetry packet from the telemetry manager.
 * In addition to checking the parameters explicitly passed to the method, the type of
 * the telemetry packet is also checked.
 * @param pEvtRep the PUS event repository
 * @param tmSubType the expected subtype of the telemetry packet 
 * @param tcId the expected identified of the telecommand whose execution is being reported
 * @param tt the expected time tag of the telecommand whose execution is being reported
 * @param errCode the expected error code of the TestCasePUSEventRepository_1_telecommand(only checked for correctness
 * if different from zero)
 * @return true if the telemetry packet is configured as expected
 */
bool TestCasePUSEventRepository_1_checkTmPacket
(
    TestCasePUSEventRepository_1 *This,
    DC_PUSEventRepository *pEvtRep, 
    TD_TelemetrySubType tmSubType, 
    TD_TelecommandId tcId,
    TD_ObsTime tt, 
    TD_CheckCode errCode
);

/**
 * Check that no telemetry packets were loaded by the argument PUS event repository in the
 * telemetry manager.
 * The method retrieves the telemetry manager from the PUS event repository and then
 * checks that it does not hold any items in the immediate dispatch queue.
 * @param pEvtRep the PUS event repository
 * @return true if the no telemetry packet are found in the immediate dispatch queue of the
 * telemetry manager
 */
bool TestCasePUSEventRepository_1_checkNoTmPacket
(
    TestCasePUSEventRepository_1 *This,
    DC_PUSEventRepository *pEvtRep
);


#endif
