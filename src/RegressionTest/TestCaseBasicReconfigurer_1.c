//
//
// TestCaseBasicReconfigurer_1.c
//

#include "TestCaseBasicReconfigurer_1.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/DC_BasicReconfigurer.h"



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
	const TD_Config nConf = 16;
    unsigned int nEvt = TestCaseWithEvtCheck_getNumberOfEvents(obj);

	DC_BasicReconfigurer *pBR = DC_BasicReconfigurer_new();
    DC_BasicReconfigurerClass *dc_brc = DC_BASICRECONFIGURER_GET_CLASS(pBR);
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pBR);

	// Verify correctness of the class identifier
	if (CC_RootObject_getClassId((CC_RootObject*)pBR) != ID_BASICRECONFIGURER) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong class identifier");
		return;
	}

	// A newly created reconfigurer shall not be configured...
	if (cc_roc->isObjectConfigured(pBR)) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Newly created reconfigurer is configured");
		return;
	}

	// ...but it should be enabled!
	if (!DC_BasicReconfigurer_isEnabled(pBR)) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Newly created reconfigurer is not enabled");
		return;
	}

	// Let's see if we can change the enable status
    DC_BasicReconfigurer_setEnabled(pBR, false);
	if (DC_BasicReconfigurer_isEnabled(pBR)) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Can't chenge enable status");
		return;
	}

	// We now set the number of possible configurations
	DC_BasicReconfigurer_setNumberOfConfigurations(pBR, nConf);

	// The reconfigurer should now be configured
	if (!cc_roc->isObjectConfigured(pBR))
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Reconfigurer not configured");
		return;
	}

	// Let's verify that the number of configuration is properly set,
	// that all the newly created configurations are healthy, and that
	// the active configuration is set to 0.
	if (DC_BasicReconfigurer_getNumberOfConfigurations(pBR) != nConf)
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong number of configurations");
		return;
	}

	for (TD_Config i=0; i<nConf; i++) {
		if (!DC_BasicReconfigurer_isConfigurationHealthy(pBR, i)) 
        {
			TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                   "Unexpected unhealthy configuration found");
			return;
		}
	}

	if (DC_BasicReconfigurer_getActive(pBR) != 0)
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong active configuration");
		return;
	}

	// We now test DC_BasicReconfigurer::setActive().
	// First we try to set an out-of-range configuration
	// and verify the event reporting.
    if (TestCase_isNonNominalCheckAllowed(obj)) {
	    DC_BasicReconfigurer_setActive(pBR, nConf);
        if (!verifyLatestEvent(obj, nEvt+1, EVT_ILLEGAL_CONFIG)) return;
        nEvt++;
    }

	// Now we set the active configuration to a legal one and
	// verify the correctness of the active configuration value
	// and, once again, the event reporting.
	DC_BasicReconfigurer_setActive(pBR, nConf-1);

	if (DC_BasicReconfigurer_getActive(pBR) != nConf-1) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong active configuration");
		return;
	}

	if (!verifyLatestEvent(obj, nEvt+1, EVT_RECONFIG)) return;
    nEvt++;

	// We now test DC_BasicReconfigurer::setHealthStatus().
	// Once again, we start by verify the error reporting, then
	// we check the nominal functionality.
    if (TestCase_isNonNominalCheckAllowed(obj)) {
    	DC_BasicReconfigurer_setHealthStatus(pBR, nConf, NOT_HEALTHY);
        if (!verifyLatestEvent(obj, nEvt+1, EVT_ILLEGAL_CONFIG)) return;
        nEvt++;
    }

	DC_BasicReconfigurer_setHealthStatus(pBR, 0, NOT_HEALTHY);
	if (DC_BasicReconfigurer_isConfigurationHealthy(pBR, 0))
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Wrong configuration health status");
		return;
	}

	// We call reconfigure(). The call should fail (the reconfigurer
	// is still disabled).
	dc_brc->reconfigure(pBR);
	if (!verifyLatestEvent(obj, nEvt+1, EVT_RECONFIG_DISABLED)) return;
    nEvt++;

	// We now enable it and try again. We also verify that the old
	// active configuration is set to NOT_HEALTHY and that the new
	// one is HEALTHY.
	DC_BasicReconfigurer_setEnabled(pBR, true);
	dc_brc->reconfigure(pBR);

	if (!verifyLatestEvent(obj, nEvt+1, EVT_RECONFIG)) return;
    nEvt++;

	if (DC_BasicReconfigurer_isConfigurationHealthy(pBR, nConf-1)) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                               "Wrong configuration health status");
		return;
	}

    TD_Config activeStatus = DC_BasicReconfigurer_getActive(pBR);
	if (!DC_BasicReconfigurer_isConfigurationHealthy(pBR, activeStatus)) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Unhealthy active configuration");
		return;
	}

	// Let's set all the configurations to NOT_HEALTHY and verify that
	// reconfigure properly reports the error
	for (TD_Config i=0; i<nConf; i++) {
		DC_BasicReconfigurer_setHealthStatus(pBR, i, NOT_HEALTHY);
    }

	dc_brc->reconfigure(pBR);

	if (!verifyLatestEvent(obj, nEvt+1, EVT_RECONFIG_NO_HEALTHY)) return;
    nEvt++;

	// We now verify the behaviour of DC_BasicReconfigurer::reset().
	// The reconfigurer is disabled and reset() is called.
	DC_BasicReconfigurer_setEnabled(pBR, false);
	DC_BasicReconfigurer_reset(pBR);

	// All the configurations should now be healhty, the active should be
	// the first and the reconfigurer should be enabled.
	if (!DC_BasicReconfigurer_isEnabled(pBR)) 
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Reset failed to enable reconfigurer");
		return;
	}

	if (DC_BasicReconfigurer_getActive(pBR) != 0)
    {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                               "Reset failed to set active configuration");
		return;
	}

	for (TD_Config i=0; i<nConf; i++) {
		if (!DC_BasicReconfigurer_isConfigurationHealthy(pBR, i)) 
        {
			TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Reset failed to set the configuration status");
			return;
		}
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

TestCaseBasicReconfigurer_1* TestCaseBasicReconfigurer_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEBASICRECONFIGURER_1);

    TESTCASEWITHEVTCHECK_GET_CLASS(obj)->post_init((TestCaseWithEvtCheck*)obj,
                                                    ID_BASICRECONFIGURER*10+1,
                                               "TestCaseBasicReconfigurer_1"); 

    return (TestCaseBasicReconfigurer_1*)obj;
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
    .name = TYPE_TESTCASEBASICRECONFIGURER_1,
    .parent = TYPE_TESTCASEWITHEVTCHECK,
    .instance_size = sizeof(TestCaseBasicReconfigurer_1),
    .abstract = false,
    .class_size = sizeof(TestCaseBasicReconfigurer_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseBasicReconfigurer_1_register(void)
{
    type_register_static(&type_info);
}
