//
//
// TestCaseChecksum_1.h
//


#ifndef TESTCASECHECKSUM_1_H
#define TESTCASECHECKSUM_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Check the checksum functions provided in module <code>Checksum</code>.
 * The following specific tests are performed: <ol>
 * <li>The checksum of a stream of bytes is computed and the correctness of
 * of the computed value is checked.</li>
 * <li>A checksum check is performed over a stream of bytes and the correctness
 * of the check result is verifed.</li>
 * </ol>
 * The sample stream of data are taken from section A.2.5 of the PUS standard.
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASECHECKSUM_1 "testcasechecksum_1"

void TestCaseChecksum_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseChecksum_1 {
    TestCaseGenericSetUp parent;
}TestCaseChecksum_1;


typedef struct TestCaseChecksum_1Class {
    TestCaseGenericSetUpClass parent_class;
}TestCaseChecksum_1Class;


#define TESTCASECHECKSUM_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseChecksum_1Class, obj, TYPE_TESTCASECHECKSUM_1)

#define TESTCASECHECKSUM_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseChecksum_1Class, klass, TYPE_TESTCASECHECKSUM_1)

#define TESTCASECHECKSUM_1(obj) \
        OBJECT_CHECK(TestCaseChecksum_1, obj, TYPE_TESTCASECHECKSUM_1)


TestCaseChecksum_1* TestCaseChecksum_1_new(void);

#endif
