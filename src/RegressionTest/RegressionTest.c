//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// RegressionTest.cpp
//
// Version	1.0
// Date		13.09.02
// Author   A. Pasetti (P&P Software)

#include "../Utilities/TestSuite.h"
#include "../Utilities/TestUtilities.h"

#include "../ApplicationTypeRegister/ApplicationTypeRegister.h"
#include "./RegressionTestTypeRegister.h"

#include "TestCaseRootObject_3.h"
#include "TestCaseRootObject_1.h"
#include "TestCaseRootObject_2.h" 
#include "TestCaseDummyTracer_1.h"
#include "TestCaseEventRepository_1.h"
#include "TestCaseEventRepository_2.h"
#include "TestCaseEventRepository_3.h"

#include "../GeneralInclude/TestCompilerSwitches.h"                             
#include "../GeneralInclude/CompilerSwitches.h"                                 
#include "../GeneralInclude/Constants.h"

Error *error_fatal; 
Error *error_abort;
int errno;

int main(int argc, char* argv[]) {

    application_type_register(); 
    regression_test_type_register();
    
    // Open output file (only on MS_HOST)
	FILE* out = pNULL;

#ifdef MS_HOST
    if((out = fopen("RegressionTestReport.html", "w")) == pNULL){
       printf( "\nThe file 'RegressionTestReport.html' could not be opened\n" );
    } else {
       printf( "\nThe file 'RegressionTestReport.html' was successfully opened\n" );
    }
#endif

    printf( "\nBegin regression test ...\n" );

	// Create and load a test suite (NB: The TestCaseRootObject_3 must be the
    // the first test case to run because it tests the system configuration
    // service)
	TestSuite* ts = TestSuite_new(out);

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseRootObject_3_new());
    TestSuite_loadTestCase(ts, (TestCase*)TestCaseRootObject_2_new());
    TestSuite_loadTestCase(ts, (TestCase*)TestCaseRootObject_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseDummyTracer_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseEventRepository_1_new());
    TestSuite_loadTestCase(ts, (TestCase*)TestCaseEventRepository_2_new());
    TestSuite_loadTestCase(ts, (TestCase*)TestCaseEventRepository_3_new());



	// Run the test suite -- this causes all test cases in
	// the test suite to be run in sequence
	TestSuite_runTestSuite(ts);

    printf( "\nRegression test ended... \n" );


	// close output file
#ifdef MS_HOST
	fclose(out);
#endif
	return 0;
}

