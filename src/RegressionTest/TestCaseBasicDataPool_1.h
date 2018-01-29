//
//
// TestCaseBasicDataPool_1.h
//


#ifndef TESTCASEBASICDATAPOOL_1_H
#define TESTCASEBASICDATAPOOL_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Check the functionalities implemented by the <code>DataPool</code> class.
 * Since this class is abstract, its functionalities are checked in the
 * implementation of its concrete subclass <code>DC_BasicDataPool_1</code>.
 * An instance of the component is created and the following
 * specific checks are performed upon it: <ol>
 * <li>It is verified that the class ID of the component has the correct value.</li>
 * <li>It is verified that, after instantiation, the configuration service
 * of the component reports "not configured".</li>
 * <li>The size of the data pool is set and read back and it is checked that the read-back
 * value is correct.</li>
 * <li>It is checked that the configuration service
 * of the component reports "configured".</li>
 * <li>It is verified that the data item attribute of a data pool item encapsulates an unsigned
 * integer with value zero.</li>
 * <li>It is verified that the time stamp attribute of a data pool item is equal to zero.</li>
 * <li>It is verified that the validity attribute of a data pool item is "valid".</li>
 * <li>It is verified that the setter method for the validity status of a data pool item can be called
 * without an exception being generated.</li>
 * <li>It is verified that both type checking services for a data pool item return "true".</li>
 * <li>It is verified that the <code>firstIdentifier</code> and <code>nextIdentifier</code> iteration
 * methods return zero and that the <code>isLastIdentifier</code> method returns "true".</li>
 * <li>It is verified that the monitoring profile attribute of a data pool item is an
 * instance of class <code>DC_NullProfile</code>.</li>
 * <li>It is verified that the recovery action attribute of a data pool item is an
 * instance of class <code>DC_NullRecoveryAction</code>.</li>
 * <li>It is verified that the reset method can be called
 * without an exception being generated.</li>
 * <li>A float value is set and then read and it is verified that the value that is read
 * back is the same as the value that was written.</li>
 * <li>An integer value is set and then read and it is verified that the value that is read
 * back is the same as the value that was written.</li>
 * <li>A float value is set and then its pointer is read and it is verified that the value that
 * was written can be correctly read from the pointer.</li>
 * <li>An integer value is set and then its pointer is read and it is verified that the value that
 * was written can be correctly read from the pointer.</li>
 * </ol>
 * @see DC_BasicDataPool
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEBASICDATAPOOL_1 "testcasebasicdatapool_1"

void TestCaseBasicDataPool_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseBasicDataPool_1 {
    TestCaseGenericSetUp parent;
}TestCaseBasicDataPool_1;


typedef struct TestCaseBasicDataPool_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseBasicDataPool_1Class;


#define TESTCASEBASICDATAPOOL_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseBasicDataPool_1Class,\
                                             obj, TYPE_TESTCASEBASICDATAPOOL_1)

#define TESTCASEBASICDATAPOOL_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseBasicDataPool_1Class,\
                                           klass, TYPE_TESTCASEBASICDATAPOOL_1)

#define TESTCASEBASICDATAPOOL_1(obj) \
        OBJECT_CHECK(TestCaseBasicDataPool_1, obj, TYPE_TESTCASEBASICDATAPOOL_1)


TestCaseBasicDataPool_1* TestCaseBasicDataPool_1_new(void);

#endif
