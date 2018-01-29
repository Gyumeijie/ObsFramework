//
//
// TestCaseEventRepository_2.h
//


#ifndef TESTCASEEVENTREPOSITORY_2_H
#define TESTCASEEVENTREPOSITORY_2_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Verify the event creation and retrieval service of class
 * <code>DC_EventRepository</code>.
 * The following specific tests are performed: <ol>
 * <li>Two events are created in a configured event repository and it is
 * verified that the event counter is incremented by two. </li>
 * <li>The iteration service of the event repository is used to retrieve the
 * events in the repository and it is checked that the correct events are retrieved.</li>
 * <li>More events are added to the event repository until one is overwritten after
 * the repository size is exceeded and it is checked that the event counter has the
 * correct value and that the iterator performs as expected.</li>
 * <li>It is verified that <code>reset(void)</code> does not clear the event counter.</li>
 * </ol>
 * @see DC_EventRepository
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEEVENTREPOSITORY_2 "testcaseeventrepository_2"

void TestCaseEventRepository_2_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseEventRepository_2 {
    TestCaseGenericSetUp parent;
} TestCaseEventRepository_2;


typedef struct TestCaseEventRepository_2Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseEventRepository_2Class;


#define TESTCASEEVENTREPOSITORY_2_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseEventRepository_2Class, obj, TYPE_TESTCASEEVENTREPOSITORY_2)

#define TESTCASEEVENTREPOSITORY_2_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseEventRepository_2Class, klass, TYPE_TESTCASEEVENTREPOSITORY_2)

#define TESTCASEEVENTREPOSITORY_2(obj) \
        OBJECT_CHECK(TestCaseEventRepository_2, obj, TYPE_TESTCASEEVENTREPOSITORY_2)


TestCaseEventRepository_2* TestCaseEventRepository_2_new(void);

#endif
