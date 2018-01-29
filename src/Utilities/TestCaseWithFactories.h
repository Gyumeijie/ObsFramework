//
//
// TestCaseWithFactories.h
//
//
// Change Record:


#ifndef TESTCASEWITHFACTORIES_H
#define TESTCASEWITHFACTORIES_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../Event/DC_EventRepository.h"
#include "../Utilities/TestCaseWithEvtCheck.h"
#include "../Qom/object.h"


/*
 * Base class for test cases that need to access the dynamic factories.
 * In the test set-up procedure, the dynamic factories for the
 * telemetry packets, telecommands and manouvres are initialized and
 * are loaded. The type of the items that are loaded are defined by the 
 * structure of the factories. Any change in the structure of the
 * factories should be reflected by a corresponding change in this
 * class. Test cases that need to access the dynamic factories 
 * should be constructed as subclasses of this class.
 * <p/>
 * The factory initialization and loading is only done the first time the
 * test case is executed. 
 * <p/>
 * This test case also defines a shut down procedure where all items in
 * the factories have their status set to "item not in use". This ensures
 * that all test cases that inherit from this class can start with all
 * the items in the factories being available for their use.
 * @todo Use this class as base class for test cases that use items that
 * could be provided by a dynamic factory
 * @see CC_TelemetryPacketFactory
 * @see CC_TelecommandFactory
 * @see CC_ManoeuvreFactory
 * @author A. Pasetti
 * @version 1.0
 * @ingroup TestCases
 */
#define TYPE_TESTCASEWITHFACTORIES "testcasewithfactories"

void TestCaseWithFactories_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct TestCaseWithFactories {
    TestCaseWithEvtCheck parent;
};


struct TestCaseWithFactoriesClass {
    TestCaseWithEvtCheckClass parent_class;

    void (*post_init)(TestCaseWithFactories *This, int testId, char *testName);
};


#define TESTCASEWITHFACTORIES_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseWithFactoriesClass, obj, TYPE_TESTCASEWITHFACTORIES)

#define TESTCASEWITHFACTORIES_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseWithFactoriesClass, klass, TYPE_TESTCASEWITHFACTORIES)

#define TESTCASEWITHFACTORIES(obj) \
        OBJECT_CHECK(TestCaseWithFactories, obj, TYPE_TESTCASEWITHFACTORIES)


TestCaseWithFactories* TestCaseWithFactories_new(int testId, char *testName);

#endif
