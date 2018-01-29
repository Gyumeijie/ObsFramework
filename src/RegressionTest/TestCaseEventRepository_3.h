//
//
// TestCaseEventRepository_3.h
//


#ifndef TESTCASEEVENTREPOSITORY_3_H
#define TESTCASEEVENTREPOSITORY_3_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Verify the enable and disable services of the
 * <code>DC_EventRepository</code> class.
 * One instance of the class is created and the following specific tests are
 * performed upon it: <ol>
 * <li>The enable status of the repository is changed to "disabled" and it
 * it is verified that the change is correctly reported.</li>
 * <li>An "event create" request is sent to the disabled repository and it is checked that
 * the event counter and the latest event in the repository are not
 * changed(which indicates that no event was created in the repository).</li>
 * <li>The enable status of the repository is changed back to "enabled" and it
 * it is verified that "event create" requests are correctly executed and
 * results in the creation of a new event in the repository.</li>
 * <li>A "selective disable request" is made to disable collection of event reports of
 * a specific type and it is verified that the change in enable status is correctly
 * reported.</li>
 * <li>An "event create" request is sent to the repository
 * for an event of the disabled type and it
 * is checked that the event counter does not
 * change(which indicates that no event was created in the repository).</li>
 * <li>An "event create" request is sent to the repository
 * for an event that is still enabled and it
 * is checked that the event counter is incremented by 1
 * (which indicates that no event was created in the repository).</li>
 * </ol>
 * @see DC_EventRepository
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEEVENTREPOSITORY_3 "testcaseeventrepository_3"

void TestCaseEventRepository_3_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseEventRepository_3 {
    TestCaseGenericSetUp parent;
} TestCaseEventRepository_3;


typedef struct TestCaseEventRepository_3Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseEventRepository_3Class;


#define TESTCASEEVENTREPOSITORY_3_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseEventRepository_3Class, obj, TYPE_TESTCASEEVENTREPOSITORY_3)

#define TESTCASEEVENTREPOSITORY_3_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseEventRepository_3Class, klass, TYPE_TESTCASEEVENTREPOSITORY_3)

#define TESTCASEEVENTREPOSITORY_3(obj) \
        OBJECT_CHECK(TestCaseEventRepository_3, obj, TYPE_TESTCASEEVENTREPOSITORY_3)


TestCaseEventRepository_3* TestCaseEventRepository_3_new(void);

#endif
