//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseProfileList_1.c
//
// Version	1.3
// Date		15.09.03 (Version 1.0)
//          01.10.03 (Version 1.1)
//          08.10.03 (Version 1.2)
//          21.10.03 (Version 1.3)
// Author	R. Totaro
//
// Change Record:
//   Version 1.1: Replaced double and int with TD_Float and TD_Integer
//   Version 1.2: Added check that isObjectConfigured() works according to specs
//   Version 1.3: Replaced all occurrences of loadMonitoringProfile() with setMonitoringProfile()

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
	DC_ProfileList    *pPL        = DC_ProfileList_new();
    const unsigned int nEvt       = TestCaseWithEvtCheck_getNumberOfEvents(obj);
	const unsigned int listSize   = 2;
	const TD_Float     rangeWidth = 5.0;
	DC_InRangeProfile *pIRP[listSize];

	// Create and initialize the monitoring profiles we are using to
	// test the DC_ProfileList class.
    unsigned int i;
	for (i=0; i<listSize; i++) {
		pIRP[i] = DC_InRangeProfile_new();
		RangeProfile_setLowerBound((RangeProfile*)pIRP[i], (TD_Float)i);
		RangeProfile_setUpperBound((RangeProfile*)pIRP[i], (TD_Float)i+rangeWidth);
	}

	// Verify the correctness of the class id
	if (CC_RootObject_getClassId((CC_RootObject*)pPL) != ID_PROFILELIST) {
        TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                "Wrong class identifier");
		return;
	}

	// A new object shall not be configured
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(pPL);
	if (cc_roc->isObjectConfigured(pPL)) {
	    TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Newly created object already configured");
		return;
	}

	// Set the list size and verify it is reported correctly
	DC_ProfileList_setListSize(pPL, listSize);
	if (DC_ProfileList_getListSize(pPL) != listSize) {
	    TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "getListSize() failed");
		return;
	}

	// Load and get the monitoring profiles
	for (i=0; i<listSize; i++) {
	    // The object is fully configured only when all the profiles are loaded!
	    if (cc_roc->isObjectConfigured((CC_RootObject*)pPL)) {
		    TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                    "Wrong configuration status");
		    return;
	    }

		DC_ProfileList_setMonitoringProfile(pPL, i, (void*)pIRP[i]);

		if (DC_ProfileList_getMonitoringProfile(pPL, i) != (void*)pIRP[i]) {
		    TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                                    "setMonitoringProfile() failed");
			return;
		}
	}

	// Only now it is configured. Let's check it.
	if (!cc_roc->isObjectConfigured((CC_RootObject*)pPL)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "Object not configured");
		return;
	}

    // Verify that setMonitoringProfile() generates an error report
	// when invoked with an invalid index
    if (TestCase_isNonNominalCheckAllowed(obj)) {
	    DC_ProfileList_setMonitoringProfile(pPL, listSize, (void*)pIRP[0]);
        if (!verifyLatestEvent(obj, nEvt+1, EVT_ILLEGAL_MP))
            return;
    }

	// These profile checks shall not fail
	if (MonitoringProfile_integerDeviatesFromProfile((void*)pPL, -1)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                              "doProfileCheck(TD_Integer): unexpected failure");
		return;
	}

	if (MonitoringProfile_floatDeviatesFromProfile((void*)pPL, -1.0)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "doProfileCheck(TD_Float): unexpected failure");
		return;
	}

	// These profile checks shall fail
	if (!MonitoringProfile_integerDeviatesFromProfile((void*)pPL, 1)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE, 
                              "doProfileCheck(TD_Integer): unexpected success");
		return;
	}

	if (!MonitoringProfile_floatDeviatesFromProfile((void*)pPL, 1.0)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                                "doProfileCheck(TD_Float): unexpected success");
		return;
	}

    TD_Integer iTmpVal = (TD_Integer)(listSize+rangeWidth-2);
	if (!MonitoringProfile_integerDeviatesFromProfile((void*)pPL, iTmpVal)) {
		TestCase_setTestResult((TestCase*)obj, TEST_FAILURE,
                              "doProfileCheck(TD_Integer): unexpected success");
		return;
	}

    TD_Float fTmpVal = (TD_Float)(listSize+rangeWidth-2.0);
	if (!MonitoringProfile_floatDeviatesFromProfile((void*)pPL, fTmpVal)) {
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
