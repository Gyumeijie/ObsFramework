//
//
// TestCaseWithEvtCheck.h
//
//
// Change Record:


#ifndef TESTCASEWITHEVTCHECK_H
#define TESTCASEWITHEVTCHECK_H


#include "../Event/DC_EventRepository.h"
#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


#define verifyLatestEvent(This, nEvt, eventType)\
       TestCaseWithEvtCheck_verifyLatestEventHidden((TestCaseWithEvtCheck*)This,\
                                                    __LINE__, nEvt, eventType)
#define verifySpecificEvent(This, n, eventType)\
       TestCaseWithEvtCheck_verifySpecificEventHidden((TestCaseWithEvtCheck*)This,\
                                                    __LINE__, n, eventType)

/*
 * Base class for test cases that need to perform checks on the
 * event repository associated to the <code>CC_RootObject</code>
 * class.
 * Two types of checks are foreseen. The <i>latest event check</i>
 * verifies the type and parameter of the latest event in the
 * repository and the total number of events in the repository.
 * The <i>specific event check</i> verifies the type and parameter
 * of a specific event in the repository.
 * @see CC_RootObject#getEventRepository
 * @author Roberto Totaro
 * @version 1.0
 * @ingroup TestCases
 */
#define TYPE_TESTCASEWITHEVTCHECK "testcasewithevtcheck"

void TestCaseWithEvtCheck_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct TestCaseWithEvtCheck {
    TestCaseGenericSetUp parent;
};


struct TestCaseWithEvtCheckClass {
    TestCaseGenericSetUpClass parent_class;

    void (*post_init)(TestCaseWithEvtCheck *This, int id, char *name);
};


#define TESTCASEWITHEVTCHECK_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseWithEvtCheckClass, obj, TYPE_TESTCASEWITHEVTCHECK)

#define TESTCASEWITHEVTCHECK_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseWithEvtCheckClass, klass, TYPE_TESTCASEWITHEVTCHECK)

#define TESTCASEWITHEVTCHECK(obj) \
        OBJECT_CHECK(TestCaseWithEvtCheck, obj, TYPE_TESTCASEWITHEVTCHECK)


TestCaseWithEvtCheck* TestCaseWithEvtCheck_new(int testId, char *testName);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Get the current number of events in the repository.
 * @return Number of events
 */
unsigned int
TestCaseWithEvtCheck_getNumberOfEvents(const TestCaseWithEvtCheck *This);

/**
 * Get the size of the event TestCaseWithEvtCheck_repository(the maximum number
 * of events it can contain).
 * @return Size of event repository
 */
unsigned int
TestCaseWithEvtCheck_getEventRepositorySize(const TestCaseWithEvtCheck *This);

/**
 * Perform a <i>latest event check</i>. More specifically, the
 * following tests are performed on the event repository associated
 * to the <code>CC_RootObject</code> class: <ul>
 * <li>Verifies that the number of events in the repository
 * is equal to <code>nEvt</code></li>
 * <li>Checks that the event type of the latest event in the
 * repository is equal to <code>eventType</code></li>
 * </ul>
 * If all the tests are passed, the method returns <code>true</code>, 
 * otherwise <code>false</code>.
 * @param line line number
 * @param nEvt the expected number of events in the repository
 * @param eventType the expected type of the latest event in the repository
 * @return true if the tests are passed, false otherwise
 */
bool TestCaseWithEvtCheck_verifyLatestEventHidden
(
    TestCaseWithEvtCheck *This,
    const int line,
    const unsigned int nEvt,
    const TD_EventType eventType
);

/**
 * Perform a <i>specific event check</i>. The event to be checked is the
 * n-th event in the buffer. The argument n must lie in the range [N-S+1, N]
 * where N is the total number of events stored in the repository since
 * it was TestCaseWithEvtCheck_created(return value of method <code>
 * TestCaseWithEvtCheck_getCounter(void)</code>) and
 * S is the repository size. If the method argument does not satisfy this
 * constraint, the test returns false. Otherwise, the following checks
 * are performed on the target event: <ul>
 * <li>Verify that the event type of the checked event in the
 * repository is equal to <code>eventType</code></li>
 * </ul>
 * If all the tests are passed, the method returns <code>true</code>, 
 * otherwise <code>false</code>.
 * @param line line number
 * @param n the identifier of the target event
 * @param eventType the expected type of the target event
 * @return true if the tests are passed, false otherwise
 */
bool TestCaseWithEvtCheck_verifySpecificEventHidden
(
    TestCaseWithEvtCheck *This,
    const int line,
    const unsigned int n,
    const TD_EventType eventType
);


#endif
