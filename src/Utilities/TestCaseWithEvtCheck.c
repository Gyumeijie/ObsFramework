//
//
// TestCaseWithEvtCheck.c
//
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/TestConstants.h"
#include "../GeneralInclude/Constants.h"
#include "../Event/DC_EventRepository.h"
#include "../Base/CC_RootObject.h"
#include "TestCaseWithEvtCheck.h"

#include <stdio.h>



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

unsigned int 
TestCaseWithEvtCheck_getNumberOfEvents(const TestCaseWithEvtCheck *This)
{

    DC_EventRepository* dc_er = CC_RootObject_getEventRepository();
     
    return DC_EventRepository_getCounter(dc_er);
}

unsigned int
TestCaseWithEvtCheck_getEventRepositorySize(const TestCaseWithEvtCheck *This)
{
    DC_EventRepository* dc_er = CC_RootObject_getEventRepository();
    return DC_EventRepository_getRepositorySize(dc_er);
}

bool TestCaseWithEvtCheck_verifyLatestEventHidden
(
    TestCaseWithEvtCheck *This,
    const int line, 
    const unsigned int nEvt,
    const TD_EventType eventType
)
{
    assert(eventType>0);

    char msg[512];
    DC_EventRepository* dc_er = CC_RootObject_getEventRepository();

    if (DC_EventRepository_getCounter(dc_er) != nEvt) {
        sprintf(msg, "Wrong number of events at line %d", line);
		TestCase_setTestResult((TestCase*)This, TEST_FAILURE, msg);
        return false;
	}

    DC_EventRepository_latest(dc_er);
	if (DC_EventRepository_getEventType(dc_er) != eventType) {
        sprintf(msg, "Wrong event type at line %d", line);
		TestCase_setTestResult((TestCase*)This, TEST_FAILURE, msg);
		return false;
	}

	return true;
}

bool TestCaseWithEvtCheck_verifySpecificEventHidden
(
    TestCaseWithEvtCheck *This,
    const int line,
    const unsigned int n,
    const TD_EventType eventType
)
{
    char msg[512];
    DC_EventRepository* dc_er = CC_RootObject_getEventRepository();
	const int distance=(DC_EventRepository_getCounter(dc_er)-n);

	assert(eventType>0);
	assert(distance<(int)DC_EventRepository_getRepositorySize(dc_er));

	if (distance<0) {
        sprintf(msg, "Wrong number of events at line %d", line);
		TestCase_setTestResult((TestCase*)This, TEST_FAILURE, msg);
		return false;
	}

    int i;
    DC_EventRepository_latest(dc_er);
	for (i=0; i<distance; i++) {
		DC_EventRepository_previous(dc_er);
    }

	if (DC_EventRepository_getEventType(dc_er) != eventType) {
        sprintf(msg, "Wrong event type at line %d", line);
		TestCase_setTestResult((TestCase*)This, TEST_FAILURE, msg);
		return false;
	}

	return true;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Call the test setup service of the super class.
 */
static bool setUpTestCase(void *obj)
{
    /**
     * To call setup service of class "TestCaseGenericSetUpClass", but the method
     * setUpTestCase is not originally defined in TestCaseGenericSetUpClass, 
     * so we must first get TestCaseGenericSetUpClass and then cast it to class
     * TestCaseClass.
     */
    TestCaseGenericSetUpClass* tcgsc = GET_CLASS(TYPE_TESTCASEGENERICSETUP);

    return TESTCASE_CLASS(tcgsc)->setUpTestCase(obj);
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void post_init(TestCaseWithEvtCheck *This, int id, char *name)
{
    TESTCASEGENERICSETUP_GET_CLASS(This)->post_init((TestCaseGenericSetUp*)This,
                                                     id, name);
    return;
}

TestCaseWithEvtCheck* TestCaseWithEvtCheck_new(int id, char *name)
{
   Object *obj = object_new(TYPE_TESTCASEWITHEVTCHECK);
   post_init((TestCaseWithEvtCheck*)obj, id, name);

   return (TestCaseWithEvtCheck*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    TestCaseClass *tcc = TESTCASE_CLASS(oc);
    tcc->setUpTestCase = setUpTestCase;

    TestCaseWithEvtCheckClass *tcwecc = TESTCASEWITHEVTCHECK_CLASS(oc);
    tcwecc->post_init = post_init;
}

static const TypeInfo type_info = {
    .name = TYPE_TESTCASEWITHEVTCHECK,
    .parent = TYPE_TESTCASEGENERICSETUP,
    .instance_size = sizeof(TestCaseWithEvtCheck),
    .abstract = false,
    .class_size = sizeof(TestCaseWithEvtCheckClass),
    .class_init = class_init,
};

void TestCaseWithEvtCheck_register(void)
{
    type_register_static(&type_info);
}
