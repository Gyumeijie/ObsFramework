//
//
// TestCaseProfileList_1.c
//
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../FDIR/DC_InRangeProfile.h"
#include "../FDIR/DC_ProfileList.h"
#include "TestCaseProfileList_1.h"



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
	DC_ProfileList    *dc_pl      = DC_ProfileList_new();
    const unsigned int nEvt       = TestCaseWithEvtCheck_getNumberOfEvents(obj);
	const unsigned int listSize   = 2;
	const TD_Float     rangeWidth = 5.0;
	DC_InRangeProfile *dc_irp[listSize];

	// Create and initialize the monitoring profiles we are using to
	// test the DC_ProfileList class.
    unsigned int i;
	for (i=0; i<listSize; i++) {
		dc_irp[i] = DC_InRangeProfile_new();
		RangeProfile_setLowerBound((RangeProfile*)dc_irp[i], (TD_Float)i);
		RangeProfile_setUpperBound((RangeProfile*)dc_irp[i], (TD_Float)i+rangeWidth);
	}

	// Verify the correctness of the class id
	if (CC_RootObject_getClassId((CC_RootObject*)dc_pl) != ID_PROFILELIST) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong class identifier");
		return;
	}

	// A new object shall not be configured
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(dc_pl);
	if (cc_roc->isObjectConfigured(dc_pl)) {
	    TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Newly created object already configured");
		return;
	}

	// Set the list size and verify it is reported correctly
	DC_ProfileList_setListSize(dc_pl, listSize);
	if (DC_ProfileList_getListSize(dc_pl) != listSize) {
	    TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "getListSize() failed");
		return;
	}

	// Load and get the monitoring profiles
	for (i=0; i<listSize; i++) {
	    // The object is fully configured only when all the profiles are loaded!
	    if (cc_roc->isObjectConfigured((CC_RootObject*)dc_pl)) {
		    TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                    "Wrong configuration status");
		    return;
	    }

		DC_ProfileList_setMonitoringProfile(dc_pl, i, (void*)dc_irp[i]);

		if (DC_ProfileList_getMonitoringProfile(dc_pl, i) != (void*)dc_irp[i]) {
		    TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                    "setMonitoringProfile() failed");
			return;
		}
	}

	// Only now it is configured. Let's check it.
	if (!cc_roc->isObjectConfigured((CC_RootObject*)dc_pl)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Object not configured");
		return;
	}

    // Verify that setMonitoringProfile() generates an error report
	// when invoked with an invalid index
    if (TestCase_isNonNominalCheckAllowed(obj)) {
	    DC_ProfileList_setMonitoringProfile(dc_pl, listSize, (void*)dc_irp[0]);
        if (!verifyLatestEvent(obj, nEvt+1, EVT_ILLEGAL_MP))
            return;
    }

	// These profile checks shall not fail
	if (MonitoringProfile_integerDeviatesFromProfile((void*)dc_pl, -1)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                              "doProfileCheck(TD_Integer): unexpected failure");
		return;
	}

	if (MonitoringProfile_floatDeviatesFromProfile((void*)dc_pl, -1.0)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "doProfileCheck(TD_Float): unexpected failure");
		return;
	}

	// These profile checks shall fail
	if (!MonitoringProfile_integerDeviatesFromProfile((void*)dc_pl, 1)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                              "doProfileCheck(TD_Integer): unexpected success");
		return;
	}

	if (!MonitoringProfile_floatDeviatesFromProfile((void*)dc_pl, 1.0)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "doProfileCheck(TD_Float): unexpected success");
		return;
	}

    TD_Integer iTmpVal = (TD_Integer)(listSize+rangeWidth-2);
	if (!MonitoringProfile_integerDeviatesFromProfile((void*)dc_pl, iTmpVal)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                              "doProfileCheck(TD_Integer): unexpected success");
		return;
	}

    TD_Float fTmpVal = (TD_Float)(listSize+rangeWidth-2.0);
	if (!MonitoringProfile_floatDeviatesFromProfile((void*)dc_pl, fTmpVal)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "doProfileCheck(TD_Float): unexpected success");
		return;
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

TestCaseProfileList_1* TestCaseProfileList_1_new(void)
{
    Object *obj = object_new(TYPE_TESTCASEPROFILELIST_1);

    TESTCASEWITHEVTCHECK_GET_CLASS(obj)->post_init((TestCaseWithEvtCheck*)obj,
                                                    ID_PROFILELIST*10+1,
                                                    "TestCaseProfileList_1"); 

    return (TestCaseProfileList_1*)obj;
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
    .name = TYPE_TESTCASEPROFILELIST_1,
    .parent = TYPE_TESTCASEWITHEVTCHECK,
    .instance_size = sizeof(TestCaseProfileList_1),
    .abstract = false,
    .class_size = sizeof(TestCaseProfileList_1Class),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TestCaseProfileList_1_register(void)
{
    type_register_static(&type_info);
}
