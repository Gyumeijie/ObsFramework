//
//
// TestUtilities.h 
//
//
// Change Record:

/**
 * @file TestUtilities.h
 * Utility functions to write various types of messages and headers to
 * an output device.
 * Depending on the value of the #define constant MS_HOST, the output
 * device is either the file 'out' or the standard output.
 * Messages to the file 'out' are written in HTML. Messages to the
 * standard output are written as plain text.
 * @ingroup TestCases
 */

#include <stdio.h>

static char charBuffer[MAX_TEST_FILE_NAME_LENGTH];

/**
 * Print the header of the regression test report.
 * This function should be called before any of the test cases are
 * executed. If this function is called, then function <code>printRegressionTestTail</code>
 * should also be called to print the close out of the regression test report.
 * <p>
 * NB: This function is intended for use in a desktop environment where a file
 * system is available. However, it can also be used in embedded environment
 * provided that the <code>printf</code> library function is available. For this
 * type of usage, the function should be recompiled after having undefined the MS_HOST
 * <code>#define</code> variable.
 * @param outFile the file to which the regression test output is written
 * @see printRegressionTestTail
 * @version 1.0
 * @author A. Pasetti
 */
void printRegressionTestHeader(FILE* outFile);

/**
 * Print the close out of the regression test report.
 * This function should be called after all the test cases have been
 * executed. This function assumes that function <code>printRegressionTestHeader</code>
 * was called at the beginning of the test run.
 * <p>
 * NB: See the 'nota bene' appended to the documentation of function
 * <code>printRegressionTestHeader</code>
 * @param outFile the file to which the regression test output is written
 * @see printRegressionTestHeader
 * @version 1.0
 * @author A. Pasetti
 */
void printRegressionTestTail(FILE* outFile);

/**
 * Print a message describing the outcome of a test case to an output file.
 * This function should only be called if function <code>printRegressionTestHeader</code>
 * was called at the beginning of the test run and if the test case was successful.
 * <p>
 * NB: See the 'nota bene' appended to the documentation of function
 * <code>printRegressionTestHeader</code>
 * @param outFile the file to which the regression test output is written
 * @param testName the name of the test case
 * @param testMsg the message describing the outcome of the test case
 * @see printRegressionTestHeader
 * @version 1.0
 * @author A. Pasetti
 */
void printTestSuccess(FILE* outFile, char* testName, char* testMsg);

/**
 * Print a message describing the outcome of a test case to an output file.
 * This function should only be called if function <code>printRegressionTestHeader</code>
 * was called at the beginning of the test run and if the test case failed.
 * <p>
 * NB: See the 'nota bene' appended to the documentation of function
 * <code>printRegressionTestHeader</code>
 * @param outFile the file to which the regression test output is written
 * @param testName the name of the test case
 * @param testMsg the message describing the outcome of the test case
 * @see printRegressionTestHeader
 * @version 1.0
 * @author A. Pasetti
 */
void printTestFailed(FILE* outFile, char* testName, char* testMsg);

/**
 * Print a message describing an error that occurred during set up or shut down of
 * a test case to an output file.
 * This function should only be called if function <code>printRegressionTestHeader</code>
 * was called at the beginning of the test.
 * <p>
 * NB: See the 'nota bene' appended to the documentation of function
 * <code>printRegressionTestHeader</code>
 * @param outFile the file to which the regression test output is written
 * @param testName the name of the test case
 * @param msg the message describing the outcome of the test case
 * @see printRegressionTestHeader
 * @version 1.0
 * @author A. Pasetti
 */
void printErrorMsg(FILE* outFile, char* testName, char* msg);

/**
 * Double any underscore characters in the input string. The input string is
 * transformed into the output string as follows:<ul>
 * <li>if the input string does not contain any underscore character ('_'), it
 * is left unchanged</li>
 * <li>if the input string contains one or more underscore character ('_'),
 * the output string replaces them with two underscore characters (for instance,
 * string "aaa_bb" is transformed into: "aaa__bb").
 * </ul>
 * This function is useful because Doxygen double underscores when creating the
 * name of the file to hold the description of a class.
 * <p>
 * This function assumes that the length of the output string is less than
 * MAX_TEST_FILE_NAME_LENGTH.
 * @param outFile the file to which the regression test output is written
 * @param testName the name of the test case
 * @see MAX_TEST_FILE_NAME_LENGTH
 */
char* doubleUnderscore(FILE* outFile, char* testName);
