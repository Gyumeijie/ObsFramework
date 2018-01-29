//
//
// TestCaseGenericSetUp.c
//

#include "TestCaseGenericSetUp.h"
#include "TestCase.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/TestConstants.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../Event/DC_EventRepository.h"
#include "../Data/DC_DummyDataPool.h"
#include "../Data/DC_DummyDatabase.h"
#include "../System/DC_DummyObsClock.h"
#include "../System/DC_DummyTracer.h"
#include "../Telemetry/PUSTelemetryPacket.h"
//#include "../Telemetry/CC_TelemetryPacketFactory.h"
//#include "../Telemetry/DC_PUSTcVerificationPacket.h"
//#include "../Telemetry/DC_PUSDataReportingPacket.h"
#include "../Telemetry/DC_DummyPUSTelemetryPacket.h"
#include "../Telecommand/PUSTelecommand.h"
#include "../Qom/object.h"



///////////////////////////////////////////////////////////////////////////////
//
//                            class data
//
///////////////////////////////////////////////////////////////////////////////

static bool firstActivation = true;



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual object methods definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Perform basic test initialization actions. More specifically,
 * the following actions are taken: <ul>
 * <li>The system list size is initialized</li>
 * <li>An event repository is created and initialized with a dummy OBS clock</li>
 * <li>A dummy data pool is created as an instance of <code>DC_DummyDataPool</code>
 * and is loaded in <code>CC_RootObject</code> as the system data pool</li>.
 * <li>A dummy parameter database is created as an instance of <code>DC_DummyParameterDatabase</code>
 * and is loaded in <code>CC_RootObject</code> as the system parameter database</li>.
 * <li>The event repository is plugged into the <code>CC_RootObject</code></li>
 * <li>A dummy tracer is created and loaded into the <code>CC_RootObject</code></li>
 * </ul>
 * Note that the above actions initialize the static part of framework components
 * and should therefore be performed only once(the first time the method is called).
 */
static bool setUpTestCase(void *obj)
{

   if (firstActivation) {
     // Initialize the system list size in class CC_RootObject
     CC_RootObject_setSystemListSize(MAX_N_OBJECTS);

     // Load an event repository into class CC_RootObject
     DC_EventRepository *pRep = DC_EventRepository_new(); 
     DC_DummyObsClock *pClk = DC_DummyObsClock_new();

     DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(pRep);
     DC_EventRepository_setObsClock(pRep, (ObsClock*)pClk);
     DC_EventRepository_setRepositorySize(pRep, EVT_REP_SIZE);

     // Load repository into CC_RootObject and check success
     CC_RootObject_setEventRepository(pRep);
     if (CC_RootObject_getEventRepository() != pRep){
         return INITIALIZATION_FAILURE;
     }

     // Load a dummy database into class CC_RootObject and check success
     DC_DummyDatabase *pDB = DC_DummyDatabase_new();
     CC_RootObject_setParameterDatabase((ParameterDatabase*)pDB);
     if (CC_RootObject_getParameterDatabase() != (ParameterDatabase*)pDB) {
         return INITIALIZATION_FAILURE;
     }

     // Load a dummy datapool into class CC_RootObject and check success
     DC_DummyDataPool *pDP = DC_DummyDataPool_new();
     CC_RootObject_setDataPool((DataPool*)pDP);
     if (CC_RootObject_getDataPool() != (DataPool*)pDP) {
         return INITIALIZATION_FAILURE;
     }

     // Load a tracer into class CC_RootObject and check success
     DC_DummyTracer* pTrc = DC_DummyTracer_new();
     CC_RootObject_setTracer((Tracer*)pTrc);
     if (CC_RootObject_getTracer() != (Tracer*)pTrc ){
         return INITIALIZATION_FAILURE;
     }

     // Configure the static part of PUS telecommand and telemetry classes
     PUSTelemetryPacket_setDefaultDestination(TEST_TM_DEF_DEST);
     PUSTelemetryPacket_setApplicationId(TEST_TM_APID);
     PUSTelemetryPacket_setObsClock((ObsClock*)pClk);

     PUSTelecommand_setApplicationId(TEST_TC_APID);

     firstActivation = false;
   }

	return INITIALIZATION_SUCCESS;
}

/**
 * Dummy implementation that returns without doing anything.
 * Subclasses should provide concrete test case implementations.
 */
static void runTestCase(void *obj)
{
     return;
}

/**
 * There are no shut-down actions associated to the basic initialization
 * actions performed in method <code>setUpTestCase</code>. Hence, this
 * method only returns "shut down successful" without performing any
 * actions. In order to preserve compatibility with future releases that
 * might be performing some actions in this method, implementations of
 * <code>setUpTestCase</code> in subclasses should call this method before
 * returning as in the following pseudo-code example:
 * <PRE>
 *   ConcreteTestCase::shutDownTestCase(void) {
 *     bool outcome = . . . ;  // perform class-specific shut-down
 *     if(!outcome)
 *       return outcome;
 *     else
 *       return TestCaseGenericSetUp::shutDownTestCase(void);
 * </PRE>
 */
static bool shutDownTestCase(void *obj)
{
     return SHUTDOWN_SUCCESS;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void post_init(TestCaseGenericSetUp *This, int id, char *name)
{
   TESTCASE_GET_CLASS(This)->post_init((TestCase*)This, id, name);
}

TestCaseGenericSetUp* TestCaseGenericSetup_new(int testId, char *testName)
{
    Object *obj = object_new(TYPE_TESTCASEGENERICSETUP);

    post_init((TestCaseGenericSetUp*)obj, testId, testName); 

    return (TestCaseGenericSetUp*)obj;
}


///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    TestCaseGenericSetUpClass *tcgsuc = TESTCASEGENERICSETUP_CLASS(oc);

    TestCaseClass *tcc = TESTCASE_CLASS(oc);
    tcc->setUpTestCase = setUpTestCase;
    tcc->runTestCase = runTestCase;
    tcc->shutDownTestCase = shutDownTestCase;

    tcgsuc->post_init = post_init;
}

static const TypeInfo type_info = {
    .name = TYPE_TESTCASEGENERICSETUP,
    .parent = TYPE_TESTCASE,
    .instance_size = sizeof(TestCaseGenericSetUp),
    .abstract = false,
    .class_size = sizeof(TestCaseGenericSetUpClass),
    .class_init = class_init,
};

void TestCaseGenericSetup_register(void)
{
    type_register_static(&type_info);
}
