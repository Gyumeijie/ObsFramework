//
//
// TestCaseDummyCopyControlBlock_1.h
//
//
// Change Record:
//                to TestCaseDummyCopyControlBlock_1)


#ifndef TESTCASEDUMMYCOPYCONTROLBLOCK_1_H
#define TESTCASEDUMMYCOPYCONTROLBLOCK_1_H


#include "../Utilities/TestCaseWithEvtCheck.h"
#include "../Qom/object.h"


/*
 * Check the services implemented by the <code>CopyControlBlock</code> class.
 * Since this class is abstract, the check is performed upon
 * its concrete subclass <code>DC_DummyCopyControlBlock</code>. One instance
 * of this class is created and the following checks are performed upon it: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified that the control block is configured at creation.</li>
 * <li>The number of states, inputs, outputs and parameters is read
 * with the getter methods and it is checked that their values are correct.</li>
 * <li>It is verified that the initial values of the state and inputs are correctly set.</li>
 * <li>The parameter values are set and the correctness of their values is checked.</li>
 * <li>The input values are set and <code>propagate(void)</code> is invoked. It is
 * verified that both state and outputs are properly updated.</li>
 * <li>The output values are set and the correctness of their values is checked.</li>
 * <li>The state values are set and the correctness of their values is checked.</li>
 * <li>Non-nominal behaviour check: an attempt is made to set a state value with an illegal state index and it is
 * checked that the correct event is generated.</li>
 * <li>Non-nominal behaviour check: an  attempt is made to set an output value with an illegal output index and it is
 * checked that the correct event is generated.</li>
 * <li>Non-nominal behaviour check: an  attempt is made to set an input value with an illegal input index and it is
 * checked that the correct event is generated.</li>
 * <li>Non-nominal behaviour check: an  attempt is made to set a parameter value with an illegal parameter index and it is
 * checked that the correct event is generated.</li>
 * <li>The <code>reset(void)</code> method is invoked and it is verified that the
 * states and inputs are reset to their default values.</li>
 * </ol>
 * @see DC_DummyCopyControlBlock
 * @see CopyControlBlock
 * @author Roberto Totaro, Alessandro Pasetti
 * @version 1.2
 */
#define TYPE_TESTCASEDUMMYCOPYCONTROLBLOCK_1 "testcasedummycopycontrolblock_1"

void TestCaseDummyCopyControlBlock_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseDummyCopyControlBlock_1 {
    TestCaseWithEvtCheck parent;
} TestCaseDummyCopyControlBlock_1;


typedef struct TestCaseDummyCopyControlBlock_1Class {
    TestCaseWithEvtCheckClass parent_class;
} TestCaseDummyCopyControlBlock_1Class;


#define TESTCASEDUMMYCOPYCONTROLBLOCK_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseDummyCopyControlBlock_1Class,\
                                      obj, TYPE_TESTCASEDUMMYCOPYCONTROLBLOCK_1)

#define TESTCASEDUMMYCOPYCONTROLBLOCK_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseDummyCopyControlBlock_1Class,\
                                    klass, TYPE_TESTCASEDUMMYCOPYCONTROLBLOCK_1)

#define TESTCASEDUMMYCOPYCONTROLBLOCK_1(obj) \
        OBJECT_CHECK(TestCaseDummyCopyControlBlock_1,\
                                      obj, TYPE_TESTCASEDUMMYCOPYCONTROLBLOCK_1)


TestCaseDummyCopyControlBlock_1* TestCaseDummyCopyControlBlock_1_new(void);

#endif
