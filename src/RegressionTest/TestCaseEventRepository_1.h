//
//
// TestCaseEventRepository_1.h
//


#ifndef TESTCASEEVENTREPOSITORY_1_H
#define TESTCASEEVENTREPOSITORY_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Verify the attribute default values and the object configuration service of class
 * <code>DC_EventRepository</code>.
 * The following specific tests are performed: <ol>
 * <li>The correctness of the class identifier for the <code>DC_EventRepository</code>
 * class is verified</li>
 * <li>A <code>DC_EventRepository</code> instance is created and it is verified
 * that its object configuration service reports "object not configured".</li>
 * <li>The initial(un-configured) values of the event repository attributes are
 * read out and the correctness of their values is verified.</li>
 * <li>A dummy OBS Clock component is loaded and it is verified that <code>getObsClock(void)</code>
 * returns the correct value.</li>
 * <li>The event repository size is set
 * and it is then verified that the object configuration service correctly reports
 * "object configured".</li>
 * <li>The event repository size attribute is read out and its correctness is
 * verified.</li>
 * </ol>
 * @see DC_EventRepository
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEEVENTREPOSITORY_1 "testcaseeventrepository_1"

void TestCaseEventRepository_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseEventRepository_1 {
    TestCaseGenericSetUp parent;
} TestCaseEventRepository_1;


typedef struct TestCaseEventRepository_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseEventRepository_1Class;


#define TESTCASEEVENTREPOSITORY_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseEventRepository_1Class, obj,TYPE_TESTCASEEVENTREPOSITORY_1)

#define TESTCASEEVENTREPOSITORY_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseEventRepository_1Class, klass, TYPE_TESTCASEEVENTREPOSITORY_1)

#define TESTCASEEVENTREPOSITORY_1(obj) \
        OBJECT_CHECK(TestCaseEventRepository_1, obj, TYPE_TESTCASEEVENTREPOSITORY_1)


TestCaseEventRepository_1* TestCaseEventRepository_1_new(void);

#endif
