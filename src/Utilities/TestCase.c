//
//
// TestCase.c
//
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/TestConstants.h"
#include "TestCase.h"
#include <string.h>



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void TestCase_setTestResult(TestCase *This, bool outcome, char *msg)
{
    // Check that method is called for the first time
    if (This->testResultFlag) {
        const char *error = "INVALID TEST -- SetTestResult called more than once";

        This->testOutcome = false;
        This->testMessage = g_malloc((strlen(error)+1)*sizeof(char));
        strcpy(This->testMessage, error);
    } else {
        This->testOutcome = outcome;
        This->testMessage = g_malloc((strlen(msg)+1)*sizeof(char));
        strcpy(This->testMessage, msg);
    }
}

bool TestCase_isNonNominalCheckAllowed(const TestCase *This)
{
#if defined(NDEBUG) || !defined(USE_SYSTEM_ASSERT)
    return true;
#else
    return false;
#endif
}

char* TestCase_getTestName(const TestCase *This)
{
     return This->testName;
}

bool TestCase_getTestOutcome(const TestCase *This)
{
     return This->testOutcome;
}

char* TestCase_getTestMessage(const TestCase *This)
{
     return This->testMessage;
}


///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * This method implements the test set up service. This class
 * provides a default implementation that always returns "set up
 * was successful".
 * @return true if the test set up succeeded, false otherwise
 */
static bool setUpTestCase(void *obj)
{
	return INITIALIZATION_SUCCESS;
}

/**
 * This method implements the test shut down service. This class
 * provides a default implementation that always returns "shut down
 * was successful".
 * @return true if the test shut down succeeded, false otherwise
 */
static bool shutDownTestCase(void *obj)
{
     return SHUTDOWN_SUCCESS;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    pure virtual methods definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * This method implements the test execution service.
 */
static void runTestCase(void *obj)
{
    // this is automate genenrated by converter
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void post_init(TestCase *This, int id, char *name)
{
	This->testId = id;

	This->testName = g_malloc((strlen(name)+1)*sizeof(char));
	strcpy(This->testName, name);

	This->testResultFlag = false;
}

TestCase* TestCase_new(int id, char *name)
{
    Object *obj = object_new(TYPE_TESTCASE);
    post_init((TestCase*)obj, id, name);
    
    return (TestCase*)obj;
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

    tcc->setUpTestCase = setUpTestCase;
    tcc->shutDownTestCase = shutDownTestCase;

    tcc->post_init = post_init;
}

static const TypeInfo type_info = {
    .name = TYPE_TESTCASE,
    .parent = TYPE_OBJECT,
    .instance_size = sizeof(TestCase),
    .abstract = false,
    .class_size = sizeof(TestCaseClass),
    .class_init = class_init,
};

void TestCase_register(void)
{
    type_register_static(&type_info);
}
