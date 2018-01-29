//
//
// TestCaseDummyDataItemControlBlock_1.h
//
//
// Change Record:


#ifndef TESTCASEDUMMYDATAITEMCONTROLBLOCK_1_H
#define TESTCASEDUMMYDATAITEMCONTROLBLOCK_1_H


#include "../Utilities/TestCaseWithEvtCheck.h"
#include "../Qom/object.h"


/*
 * Check the services implemented by the <code>DataItemControlBlock</code> class.
 * Since this class is abstract, the check is performed upon
 * its concrete subclass <code>DC_DummyDataItemControlBlock</code>. One instance
 * of this class is created and the following checks are performed upon it:<ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>The number of states, inputs, outputs and parameters read
 * with the getter methods and it is checked that their values are correct.</li>
 * <li>The control block's inputs and outputs are linked to previously created
 * <code>DC_DataItem</code> objects and it is verified that the control block
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
 * @see DC_DummyDataItemControlBlock
 * @see DataItemControlBlock
 * @author Roberto Totaro
 * @version 1.0
 */
#define TYPE_TESTCASEDUMMYDATAITEMCONTROLBLOCK_1 "testcasedummydataitemcontrolblock_1"

void TestCaseDummyDataItemControlBlock_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseDummyDataItemControlBlock_1 {
    TestCaseWithEvtCheck parent;
} TestCaseDummyDataItemControlBlock_1;


typedef struct TestCaseDummyDataItemControlBlock_1Class {
    TestCaseWithEvtCheckClass parent_class;
} TestCaseDummyDataItemControlBlock_1Class;


#define TESTCASEDUMMYDATAITEMCONTROLBLOCK_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseDummyDataItemControlBlock_1Class,\
                                  obj, TYPE_TESTCASEDUMMYDATAITEMCONTROLBLOCK_1)

#define TESTCASEDUMMYDATAITEMCONTROLBLOCK_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseDummyDataItemControlBlock_1Class,\
                                klass, TYPE_TESTCASEDUMMYDATAITEMCONTROLBLOCK_1)

#define TESTCASEDUMMYDATAITEMCONTROLBLOCK_1(obj) \
        OBJECT_CHECK(TestCaseDummyDataItemControlBlock_1,\
                                  obj, TYPE_TESTCASEDUMMYDATAITEMCONTROLBLOCK_1)


TestCaseDummyDataItemControlBlock_1* TestCaseDummyDataItemControlBlock_1_new(void);

#endif
