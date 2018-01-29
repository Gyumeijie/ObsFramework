//
//
// TestSuite.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "TestSuite.h"
#include "TestCase.h"
#include "../Utilities/TestUtilities.h"
#include <string.h>



///////////////////////////////////////////////////////////////////////////////
//
//                    non-virtual object methods definition
//
///////////////////////////////////////////////////////////////////////////////

void TestSuite_runTestSuite(TestSuite *This)
{
    TestCase **list = This->list;
    int testCaseCounter = This->testCaseCounter;
    FILE *out = This->out;

    printRegressionTestHeader(This->out);

    int i;
	for (i=0; i<testCaseCounter; i++) {
        TestCase *tc = list[i];
        TestCaseClass *tcc = TESTCASE_GET_CLASS(tc);

        if (!tcc->setUpTestCase(tc)) {
             printErrorMsg(out, TestCase_getTestName(tc),
                           "Test set up failed ...");
             continue;
        } else {
		     tcc->runTestCase(tc);
             printf("test name %s\n", TestCase_getTestName(tc));             
        }

        if (!tcc->shutDownTestCase(tc)) {
             printErrorMsg(out, TestCase_getTestName(tc),
                             "Test shut down failed ...");
             continue;
        }

		if (TestCase_getTestOutcome(tc)) {
			printTestSuccess(out, TestCase_getTestName(tc), 
                                  TestCase_getTestMessage(tc));
        } else {
			printTestFailed(out, TestCase_getTestName(tc), 
                                 TestCase_getTestMessage(tc));

        }
	}

     printRegressionTestTail(out);
}

void TestSuite_loadTestCase(TestSuite *This, TestCase *newTestCase)
{
    TestCase **list = This->list;

	if (This->testCaseCounter < MAX_TEST_CASES_IN_SUITE) {
        list[This->testCaseCounter] = newTestCase;
		This->testCaseCounter++;
	} else {
        printf("TestSuite: Test case %s could not be loaded because \
               the list of test cases is already full ...", 
               TestCase_getTestName(newTestCase));
    }
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void post_init(TestSuite *This, FILE *outputFile)
{
	This->out = outputFile;
	This->testCaseCounter = 0;
}

TestSuite* TestSuite_new(FILE* outputFile)
{
   Object *obj = object_new(TYPE_TESTSUITE);
   post_init((TestSuite*)obj, outputFile);

   return (TestSuite*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data){}

static const TypeInfo type_info = {
    .name = TYPE_TESTSUITE,
    .parent = TYPE_OBJECT,
    .instance_size = sizeof(TestSuite),
    .abstract = false,
    .class_size = sizeof(TestSuiteClass),
    .class_init = class_init,
};

void TestSuite_register(void)
{
    type_register_static(&type_info);
}
