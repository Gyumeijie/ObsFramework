//
//
// TestCaseDataPoolMonitor_1.c
//
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../System/DC_DummyObsClock.h"
#include "../FDIR/DC_OutOfRangeProfile.h"
#include "../FDIR/DC_NullRecoveryAction.h"
#include "../Data/DC_SampleFullDataPool.h"
#include "../Data/DC_DataPoolMonitor.h"
#include "TestCaseDataPoolMonitor_1.h"



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Execute the test case. See class comment for details.
 */
static void runTestCase(void *obj)
{
    const unsigned int nEvt = TestCaseWithEvtCheck_getNumberOfEvents(obj);

    // Create and initialize the data pool
    DC_SampleFullDataPool *pDP = DC_SampleFullDataPool_new();
    DC_SampleFullDataPoolClass *sfdpc = DC_SAMPLEFULLDATAPOOL_GET_CLASS(pDP);
    DataPoolClass *dpc = DATAPOOL_GET_CLASS(pDP);

    DC_SampleFullDataPool_setObsClock(pDP, (ObsClock*)DC_DummyObsClock_new());

    RecoveryAction *pAction = (RecoveryAction*)DC_NullRecoveryAction_new();
    for (TD_DataPoolId id=dpc->firstIdentifier(pDP);
             !dpc->isLastIdentifier(pDP);
                  id=dpc->nextIdentifier(pDP)) 
    {
        DC_OutOfRangeProfile *pProfile= DC_OutOfRangeProfile_new();

        RangeProfile_setLowerBound((RangeProfile*)pProfile, (TD_Float)0.0);
        RangeProfile_setUpperBound((RangeProfile*)pProfile, (TD_Float)2.0);
        sfdpc->setMonitoringProfile(pDP, id, (MonitoringProfile*)pProfile);

        sfdpc->setRecoveryAction(pDP, id, pAction);

        if (dpc->isFloat(pDP, id)) {
            dpc->setFloatValue(pDP, id, (TD_Float)1.0);
        }
        else {
            dpc->setIntegerValue(pDP, id, (TD_Integer)1);
        }
    }

    // Link the data pool to the root object
    CC_RootObject_setDataPool((DataPool*)pDP);

    // Create the object under test
    DC_DataPoolMonitor *pDPM = DC_DataPoolMonitor_new();

	// Verify correctness of the class identifier
	if (CC_RootObject_getClassId((CC_RootObject*)pDPM) != ID_DATAPOOLMONITOR)
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong class identifier");
		return;
	}

    // Execute the data pool check and verify that the data are still valid
    PunctualAction_execute((PunctualAction*)pDPM);
    for (TD_DataPoolId id=dpc->firstIdentifier(pDP);
             !dpc->isLastIdentifier(pDP);
                 id=dpc->nextIdentifier(pDP)) 
    {
        if (!dpc->isValid(pDP, id)) 
        {
		    TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                    "Wrong validity status");
		    return;
        }
    }

    // Verify that no recovery action was executed
    if (TestCaseWithEvtCheck_getNumberOfEvents(obj) != nEvt+1)
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong number of events");
		return;
    }

    // Set the values out of the allowed range and verify that their
    // validity flags are properly changed and that the recovery
    // actions are executed.
    unsigned int evtOffset = 2;

    for (TD_DataPoolId id=dpc->firstIdentifier(pDP);
              !dpc->isLastIdentifier(pDP);
                   id=dpc->nextIdentifier(pDP)) 
    {
        if (dpc->isFloat(pDP, id)) {
            dpc->setFloatValue(pDP, id, (TD_Float)3.0);
        } else {
            dpc->setIntegerValue(pDP, id, (TD_Integer)3);
        }
    }

    PunctualAction_execute((PunctualAction*)pDPM);

    // The execution of a recovery action should lead to two events being generated in
    // the event repository. It is checked that for each item in the repository, the
    // corresponding event was generated.
    for (TD_DataPoolId id=dpc->firstIdentifier(pDP);
             !dpc->isLastIdentifier(pDP);
                  id=dpc->nextIdentifier(pDP)) 
    {
        if (dpc->isValid(pDP, id)) 
        {
		    TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                    "Failed to change the validity status");
		    return;
        }

        // Terminate when the oldest event in the repository has been processed
        unsigned int nEvents = TestCaseWithEvtCheck_getNumberOfEvents(obj);
        unsigned int evtRepSize = TestCaseWithEvtCheck_getEventRepositorySize(obj);
        if ((nEvents-(nEvt+evtOffset)) >= evtRepSize) break;

        if (verifySpecificEvent(obj, nEvt+evtOffset, EVT_PUNCTUAL_ACTION_EXEC)) 
        {
		    TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                    "Recovery action not executed");
		    return;
        }

        evtOffset += 2;
    }

	TestCase_setTestResult((TestCase*)obj, TEST_SUCCESS, "Test Successful");
	return;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj){}

TestCaseDataPoolMonitor_1* TestCaseDataPoolMonitor_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEDATAPOOLMONITOR_1);

    TESTCASEWITHEVTCHECK_GET_CLASS(obj)->post_init((TestCaseWithEvtCheck*)obj,
                                                      ID_DATAPOOLMONITOR*10+1,
                                                 "TestCaseDataPoolMonitor_1");
    return (TestCaseDataPoolMonitor_1*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    TestCaseClass *tcc = TESTCASE_CLASS(oc);
    tcc->runTestCase = runTestCase;
}

static const TypeInfo type_info = {
    .name = TYPE_TESTCASEDATAPOOLMONITOR_1,
    .parent = TYPE_TESTCASEWITHEVTCHECK,
    .instance_size = sizeof(TestCaseDataPoolMonitor_1),
    .abstract = false,
    .class_size = sizeof(TestCaseDataPoolMonitor_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseDataPoolMonitor_1_register(void)
{
    type_register_static(&type_info);
}
