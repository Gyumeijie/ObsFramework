//
//
// TestCaseDummyTelecommand_1.h
//


#ifndef TESTCASEDUMMYTELECOMMAND_1_H
#define TESTCASEDUMMYTELECOMMAND_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Verify the basic services offered by telecommands as implemented
 * by the <code>DC_DummyTelecommand</code> class.
 * An instance of this class is created and the following specific
 * tests are performed: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified that the telecommand is not configured.</li>
 * <li>It is verified that the default value of the "time tag" attribute
 * is: 0.</li>
 * <li>It is verified that the telecommand identifier is equal to the
 * instance identifier.</li>
 * <li>It is verified that the telecommand type is equal to the
 * class identifier.</li>
 * <li>It is verified that the telecommand sub-type is equal to zero.</li>
 * <li>It is verified that the telecommand acknowledge level is equal to zero.</li>
 * <li>The time tag value is set and read back and it is checked that
 * the read-back value is correct.</li>
 * <li>It is verified that the configuration service of the telecommand
 * now reports "telecommand is configured".</li>
 * <li>The value of the "in use" attribute is changed to "telecommand
 * is in use" and it is verified that this operation is correctly performed.</li>
 * <li>It is verified that the initial value of the execution counter
 * is equal to zero.</li>
 * <li>It is verified that the number of raw data is zero.</li>
 * <li>It is verified that the telecommand execution check returns
 * "telecommand can execute".</li>
 * <li>It is verified that the telecommand validity check returns
 * "telecommand is valid".</li>
 * <li>Two execution requests are sent to the telecommand and it is
 * verified that the execution counter is incremented by two.</li>
 * <li>The execution check return value is forced to "telecommand
 * cannot execute" and it is verified that this is reflected
 * in the return value of the execution check.</li>
 * <li>The validity check return value is forced to "telecommand
 * is not valid" and it is verified that this is reflected
 * in the return value of the validity check.</li>
 * <li>The validity check code is set and then read back and it is verified
 * that the read-back value is correct.</li>
 * <li>The execution check code is set and then read back and it is verified
 * that the read-back value is correct.</li>
 * <li>The setter methods for the telecommand identifier, the telecommand
 * type, the telecommand subtype, the telecommand source, and the
 * telecommand acknowledge level are called. These are dummy
 * calls that are only useful to ensure a high degree of statement coverage
 * for the class under test.</li>
 * </ol>
 * @see DC_DummyTelecommand
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEDUMMYTELECOMMAND_1 "testcasedummytelecommand_1"

void TestCaseDummyTelecommand_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseDummyTelecommand_1 {
    TestCaseGenericSetUp parent;
} TestCaseDummyTelecommand_1;


typedef struct TestCaseDummyTelecommand_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseDummyTelecommand_1Class;


#define TESTCASEDUMMYTELECOMMAND_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseDummyTelecommand_1Class, \
                                          obj, TYPE_TESTCASEDUMMYTELECOMMAND_1)

#define TESTCASEDUMMYTELECOMMAND_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseDummyTelecommand_1Class, \
                                        klass, TYPE_TESTCASEDUMMYTELECOMMAND_1)

#define TESTCASEDUMMYTELECOMMAND_1(obj) \
        OBJECT_CHECK(TestCaseDummyTelecommand_1, \
                                          obj, TYPE_TESTCASEDUMMYTELECOMMAND_1)


TestCaseDummyTelecommand_1* TestCaseDummyTelecommand_1_new(void);

#endif
