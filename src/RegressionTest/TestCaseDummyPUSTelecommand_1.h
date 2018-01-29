//
//
// TestCaseDummyPUSTelecommand_1.h
//


#ifndef TESTCASEDUMMYPUSTELECOMMAND_1_H
#define TESTCASEDUMMYPUSTELECOMMAND_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Check the functionalities implemented in the <code>PUSTelecommand</code> class.
 * Since this class is abstract, it is tested through its concrete subclass
 * <code>DC_DummyPUSTelecommand</code>.
 * An instance of this class is created and the following specific
 * tests are performed: <ol>
 * <li>The correctness of the class identifier is checked.</li>
 * <li>It is checked that the telecommand is not configured.</li>
 * <li>The time tag is set and read back and the correctness of the read-back
 * value is checked.</li>
 * <li>The telecommand identifier is read out and its correctness is checked.</li>
 * <li>The telecommand type is read out and its correctness is checked.</li>
 * <li>The telecommand subtype read out and its correctness is checked.</li>
 * <li>The telecommand acknowledge level is read out and its correctness is checked.</li>
 * <li>The packet identifier is read and the correctness of its value is checked.</li>
 * <li>The telecommand ackowledge level is updated and it is checked that
 * the value of the acceptance flag, the start flag, the progress flag
 * and the completion flags are consistent with the value of the acknoledge level attribute.</li>
 * <li>It is verified that the configuration service of the telecommand
 * now reports "telecommand is configured".</li>
 * <li>It is verified that the initial value of the execution counter
 * is equal to zero.</li>
 * <li>Two execution requests are sent to the telecommand and it is
 * verified that the execution counter is incremented by two.</li>
 * </ol>
 * @see DC_DummyPUSTelecommand
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEDUMMYPUSTELECOMMAND_1 "testcasedummypustelecommand_1"

void TestCaseDummyPUSTelecommand_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseDummyPUSTelecommand_1 {
    TestCaseGenericSetUp parent;
} TestCaseDummyPUSTelecommand_1;


typedef struct TestCaseDummyPUSTelecommand_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseDummyPUSTelecommand_1Class;


#define TESTCASEDUMMYPUSTELECOMMAND_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseDummyPUSTelecommand_1Class, \
                                       obj, TYPE_TESTCASEDUMMYPUSTELECOMMAND_1)

#define TESTCASEDUMMYPUSTELECOMMAND_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseDummyPUSTelecommand_1Class, \
                                     klass, TYPE_TESTCASEDUMMYPUSTELECOMMAND_1)

#define TESTCASEDUMMYPUSTELECOMMAND_1(obj) \
        OBJECT_CHECK(TestCaseDummyPUSTelecommand_1, \
                                       obj, TYPE_TESTCASEDUMMYPUSTELECOMMAND_1)


TestCaseDummyPUSTelecommand_1* TestCaseDummyPUSTelecommand_1_new(void);

#endif
