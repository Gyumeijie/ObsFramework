//
//
// TestCaseDummyDataPoolControlBlock_1.h
//
//
// Change Record:


#ifndef TESTCASEDUMMYDATAPOOLCONTROLBLOCK_1_H
#define TESTCASEDUMMYDATAPOOLCONTROLBLOCK_1_H


#include "../Utilities/TestCaseWithEvtCheck.h"
#include "../Qom/object.h"


/*
 * Check the services implemented by the <code>DataPoolControlBlock</code> class.
 * Since this class is abstract, the check is performed upon
 * its concrete subclass <code>DC_DummyDataPoolControlBlock</code>. One instance
 * of this class is created and the following checks are performed upon it:<ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>The number of states, inputs, outputs and parameters read
 * with the getter methods and it is checked that their values are correct.</li>
 * <li>The control block's inputs and outputs are linked to a previously configured
 * <code>DC_BasicDataPool</code> object and it is verified that the control block
 * is configured only when all inputs and outputs are linked.</li>
 * <li><code>reset(void)</code> is called and it is verified that the initial values of
 * the state variables are correctly set.</li>
 * <li>The parameter values are set and the correctness of their values is checked.</li>
 * <li>The input values are set and <code>propagate(void)</code> is invoked. It is
 * verified that both state and outputs are properly updated.</li>
 * <li>The state values are set and the correctness of their values is checked.</li>
 * </ol>
 * The following tests are performed only if the non nominal checks are allowed:
 * <ol>
 * <li>An attempt is made to link an input with an illegal index and it is
 * checked that the correct event is generated.</li>
 * <li>An attempt is made to link an output with an illegal index and it is
 * checked that the correct event is generated.</li>
 * <li>An attempt is made to set a state value with an illegal index and it is
 * checked that the correct event is generated.</li>
 * <li>An attempt is made to set a parameter value with an illegal index and
 * it is  checked that the correct event is generated.</li>
 * </ol>
 * @see DC_DummyDataPoolControlBlock
 * @see DataPoolControlBlock
 * @author Roberto Totaro
 * @version 1.0
 */
#define TYPE_TESTCASEDUMMYDATAPOOLCONTROLBLOCK_1 "testcasedummydatapoolcontrolblock_1"

void TestCaseDummyDataPoolControlBlock_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseDummyDataPoolControlBlock_1 {
    TestCaseWithEvtCheck parent;
}TestCaseDummyDataPoolControlBlock_1;


typedef struct TestCaseDummyDataPoolControlBlock_1Class {
    TestCaseWithEvtCheckClass parent_class;
} TestCaseDummyDataPoolControlBlock_1Class;


#define TESTCASEDUMMYDATAPOOLCONTROLBLOCK_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseDummyDataPoolControlBlock_1Class,\
                                 obj, TYPE_TESTCASEDUMMYDATAPOOLCONTROLBLOCK_1)

#define TESTCASEDUMMYDATAPOOLCONTROLBLOCK_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseDummyDataPoolControlBlock_1Class,\
                               klass, TYPE_TESTCASEDUMMYDATAPOOLCONTROLBLOCK_1)

#define TESTCASEDUMMYDATAPOOLCONTROLBLOCK_1(obj) \
        OBJECT_CHECK(TestCaseDummyDataPoolControlBlock_1,\
                                 obj, TYPE_TESTCASEDUMMYDATAPOOLCONTROLBLOCK_1)


TestCaseDummyDataPoolControlBlock_1* TestCaseDummyDataPoolControlBlock_1_new(void);

#endif
