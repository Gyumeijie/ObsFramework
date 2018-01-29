//
//
// TestCaseDummyObsClock_1.h
//


#ifndef TESTCASEDUMMYOBSCLOCK_1_H
#define TESTCASEDUMMYOBSCLOCK_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Verify the timing provision and object configuration services of class
 * <code>DC_DummyObsClock</code>.
 * The following specific tests are performed: <ol>
 * <li>A <code>DC_DummyObsClock</code> instance is created and it is verified
 * that its object configuration service reports "object configured".</li>
 * <li>The OBS time and cycle services are called on the newly created object
 * and it is verified that they report 0.</li>
 * <li>The OBS time and cycle are set with the <code>setTime</code> service and
 * it is then verified that the OBS time and cycle services report the newly
 * set values.</li>
 * <li>The Dummy OBS Clock component is reset and it is verified that its time
 * and cycle data are reset to 0.</li>
 * <li>A dummy call to method <code>synchronizeWithSystemTime</code> is done.
 * This is necessary to ensure full statement coverage of the class under test.</li>
 * </ol>
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEDUMMYOBSCLOCK_1 "testcasedummyobsclock_1"

void TestCaseDummyObsClock_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseDummyObsClock_1 {
    TestCaseGenericSetUp parent;
} TestCaseDummyObsClock_1;


typedef struct TestCaseDummyObsClock_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseDummyObsClock_1Class;


#define TESTCASEDUMMYOBSCLOCK_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseDummyObsClock_1Class, obj, TYPE_TESTCASEDUMMYOBSCLOCK_1)

#define TESTCASEDUMMYOBSCLOCK_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseDummyObsClock_1Class, klass, TYPE_TESTCASEDUMMYOBSCLOCK_1)

#define TESTCASEDUMMYOBSCLOCK_1(obj) \
        OBJECT_CHECK(TestCaseDummyObsClock_1, obj, TYPE_TESTCASEDUMMYOBSCLOCK_1)


TestCaseDummyObsClock_1* TestCaseDummyObsClock_1_new(void);

#endif
