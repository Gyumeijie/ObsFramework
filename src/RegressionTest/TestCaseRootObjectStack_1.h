//
//
// TestCaseRootObjectStack_1.h
//
//


#ifndef TESTCASEROOTOBJECTSTACK_1_H
#define TESTCASEROOTOBJECTSTACK_1_H


#include "../Utilities/TestCaseWithEvtCheck.h"
#include "../Qom/object.h"


/*
 * Check the functionality of the container class for items of type
 * pointer to <code>CC_RootObject*</code>.
 * One instance of the container class is created and
 * the following specific checks are performed upon it : 
 * The correctness of the class identifier is checked.
 * It is checked that the configuration check service
 * initially reports "not configured".
 * The stack size is set to 2 and it is checked that the set value
 * is correctly reported.
 * It is checked that the configuration check service reports
 * "configured".
 * An item is pushed onto the stack and it is checked that the
 * stack reports "number of items on the stack equals 1".
 * An item is popped from the stack and it is checked that the
 * correct element is returned.
 * A pop operation is performed and it is verified that pNULL
 * is returned and the correct event report is generated.
 * Three items are pushed on the stack and it is verified that
 * only 2 are actually placed on the stack and that the correct event
 * report is generated.
 * It is verified that the stack is full after the second push operation.
 * A reset operation is performed and it is verified that
 * the number of items on the stack is zero and that the stack is
 * empty.
 * 
 * This class was generated automatically by an XSLT program.
 * @see CC_RootObjectStack
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEROOTOBJECTSTACK_1 "testcaserootobjectstack_1"

void TestCaseRootObjectStack_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseRootObjectStack_1 {
    TestCaseWithEvtCheck parent;
} TestCaseRootObjectStack_1;


typedef struct TestCaseRootObjectStack_1Class {
    TestCaseWithEvtCheckClass parent_class;
} TestCaseRootObjectStack_1Class;


#define TESTCASEROOTOBJECTSTACK_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseRootObjectStack_1Class, \
                                           obj, TYPE_TESTCASEROOTOBJECTSTACK_1)

#define TESTCASEROOTOBJECTSTACK_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseRootObjectStack_1Class, \
                                         klass, TYPE_TESTCASEROOTOBJECTSTACK_1)

#define TESTCASEROOTOBJECTSTACK_1(obj) \
        OBJECT_CHECK(TestCaseRootObjectStack_1, \
                                           obj, TYPE_TESTCASEROOTOBJECTSTACK_1)


TestCaseRootObjectStack_1* TestCaseRootObjectStack_1_new(void);

#endif
