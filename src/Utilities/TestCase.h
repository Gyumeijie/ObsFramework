//
//
// TestCase.h
//


#ifndef TESTCASE_H
#define TESTCASE_H

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/TestConstants.h"
#include "../Qom/object.h"


/*
 * Base class from which all classes encapsulating a test case are derived.
 * A <i>test case</i> is a self-contained, and usually small test, that can either
 * fail or succeed.
 * The class encapsulating a test case is completely responsible for running the test
 * from the set-up of the test conditions to the shut-down of the test and for
 * reporting its outcome.
 * A test case class is however "passive" in the sense that it has the capabilities
 * to initiate, perform and terminate a test but these capabilities must be
 * controlled by some external entity.
 * <p>
 * This class declares, and defines trivial default implementations for, four services.
 * The <i>test set-up service</i> set up the conditions for the performance of the
 * test case.
 * The <i>test execution service</i> causes the test case to be executed. This service
 * should only be called after the test set-up service was called.
 * The <i>test shut-down service</i> performs any shut-down actions that may be
 * required at the end of the test case. It should always be called at the end of a test
 * case.
 * The <i>test reporting service</i> reports the outcome of the test. The outcome
 * of the test is made up of a true/false flag(the <i>test outcome</i>)and an
 * explanatory message that
 * contains additional information about its outcome(the <i>test message</i>).
 * <p>
 * This class defines two attributes for test cases.
 * The <i>test case ID</i> is an integer acting as a numerical identifier of the test case.
 * The <i>test case name</i> is a string that represent the name of the test case.
 * <p>
 * This class is abstract because the test execution service
 * must be defined by subclasses representing concrete test cases. Default
 * implementations are instead provided for the test set up and shut down services.
 * <p>
 * A pseudo-code example of how a test case could be run is as follows:
 * <p><PRE>
 *   testCase.setUpTestCase(void);
 *   testCase.runTestCase(void);
 *   testCase.shutDownTestCase(void);
 *   bool outcome = testCase.getTestOutcome(void);
 *   char* testMessage = testCase.getTestMessage(void);
 *  </PRE>
 * IMPORTANT NOTICE: the framework classes are designed to prevent class instances
 * from ever being destroyed(this applies both to explicit object deletion and
 * to implicit deletion when an object variable goes out of scope). This presents
 * a problem for the implementation of test cases since each test case should have
 * its own set of variables in order to preserve the mutual independence of test
 * cases. The solution adopted here is that each test case creates the class
 * variables it needs dynamically on the heap but <i>does not destry them when 
 * it terminates</i>. This means that execution of a test case introduces a 
 * memory leak. The size of the memory leak should not cause any problems in a
 * desktop environment.
 * @todo reformulate comments to test cases in terms of "checks" rather than 
 * "verification".
 * @see TestSuite
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 * @ingroup TestCases
 */
#define TYPE_TESTCASE "testcase"

void TestCase_register(void);



///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct TestCase {
    Object parent;

    int testId;
    char *testName;
    bool testOutcome;
    char *testMessage;
    bool testResultFlag;	// true if setTestResult was called
};

struct TestCaseClass {
    ObjectClass parent_class;
 
    bool (*setUpTestCase)(void *obj);
    bool (*shutDownTestCase)(void *obj);
 
    void (*runTestCase)(void *obj);
 
    void (*post_init)(TestCase *This, int id, char *name);
};


#define TESTCASE_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseClass, obj, TYPE_TESTCASE)

#define TESTCASE_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseClass, klass, TYPE_TESTCASE)

#define TESTCASE(obj) \
        OBJECT_CHECK(TestCase, obj, TYPE_TESTCASE)


TestCase* TestCase_new(int id, char *name);


///////////////////////////////////////////////////////////////////////////////
//
//                      non-virtual member methods declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Method intended to be called by concrete test cases to set the
 * test outcome flag and the test message.
 * This method should only be called once in a given test case.
 * Attempts to call it more than once will result in an error message
 * being stored in the test message and in the test outcome flag having
 * an undefined value.
 * @param outcome the test outcome flag
 * @param testMessage the test message string
 */
void TestCase_setTestResult(TestCase *This, bool outcome, char* testMessage);

/**
 * Return true if non-nominal behaviour can be checked.
 * Some test cases may want to check the behaviour of the class under test
 * under non-nominal conditions. In general, this should only be done if
 * violation of an assertion check does not lead to a termination of the application.
 * This is because the non-nominal situation might be caught by an assertion check
 * which might lead to a premature termination of the test. 
 * This method returns true if violation of an assertion check does not lead
 * to termination of the application. The method is implemented in terms of the
 * pre-processor symbols NDEBUG and USE_SYSTEM_ASSERT defined in
 * the include file <code>CompilerSwitches.h</code>.
 * @return true if if violation of an assertion check does not lead to termination
 * of the application, false otherwise
 */
bool TestCase_isNonNominalCheckAllowed(const TestCase *This);

/**
 * Return the test name.
 * @return the test name.
 */
char* TestCase_getTestName(const TestCase *This);

/**
 * Return the test outcome.
 * @return the test name.
 */
bool TestCase_getTestOutcome(const TestCase *This);

/**
 * Return the test message. The test message can be an empty TestCase_string(e.g. " ")
 * but should never be the null string.
 * @return the test name.
 */
char* TestCase_getTestMessage(const TestCase *This);


#endif
