//
//
// TestCaseDummyPointerControlBlock_1.h
//
//
// Change Record:


#ifndef TESTCASEDUMMYPOINTERCONTROLBLOCK_1_H
#define TESTCASEDUMMYPOINTERCONTROLBLOCK_1_H


#include "../Utilities/TestCaseWithEvtCheck.h"
#include "../Qom/object.h"


/*
 * Check the services implemented by the <code>PointerControlBlock</code> class.
 * Since this class is abstract, the check is performed upon
 * its concrete subclass <code>DC_DummyPointerControlBlock</code>. One instance
 * of this class is created and the following checks are performed upon it: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>The number of states, inputs, outputs and parameters read
 * with the getter methods and it is checked that their values are correct.</li>
 * <li>The input and output variables are linked to the control block and it is
 * verified that the object is configured only when all the variables are linked.</li>
 * <li><code>reset(void)</code> is called and it is verified that the initial values of
 * the state variables are correctly set.</li>
 * <li>The parameter values are set and the correctness of their values is checked.</li>
 * <li>The input values are set and <code>propagate(void)</code> is invoked. It is
 * verified that both state and outputs are properly updated.</li>
 * <li>The state values are set and the correctness of their values is checked.</li>
 * <li>Non-nominal behaviour check: an attempt is made to set a state value with an illegal state index and it is
 * checked that the correct event is generated.</li>
 * <li>Non-nominal behaviour check: an attempt is made to set a parameter value with an illegal parameter index and it is
 * checked that the correct event is generated.</li>
 * </ol>
 * @see DC_DummyPointerControlBlock
 * @see PointerControlBlock
 * @author Roberto Totaro
 * @version 1.0
 */
#define TYPE_TESTCASEDUMMYPOINTERCONTROLBLOCK_1 "testcasedummypointercontrolblock_1"

void TestCaseDummyPointerControlBlock_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseDummyPointerControlBlock_1 {
    TestCaseWithEvtCheck parent;
} TestCaseDummyPointerControlBlock_1;


typedef struct TestCaseDummyPointerControlBlock_1Class {
    TestCaseWithEvtCheckClass parent_class;
} TestCaseDummyPointerControlBlock_1Class;


#define TESTCASEDUMMYPOINTERCONTROLBLOCK_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseDummyPointerControlBlock_1Class,\
                                  obj, TYPE_TESTCASEDUMMYPOINTERCONTROLBLOCK_1)

#define TESTCASEDUMMYPOINTERCONTROLBLOCK_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseDummyPointerControlBlock_1Class,\
                                klass, TYPE_TESTCASEDUMMYPOINTERCONTROLBLOCK_1)

#define TESTCASEDUMMYPOINTERCONTROLBLOCK_1(obj) \
        OBJECT_CHECK(TestCaseDummyPointerControlBlock_1,\
                                  obj, TYPE_TESTCASEDUMMYPOINTERCONTROLBLOCK_1)


TestCaseDummyPointerControlBlock_1* TestCaseDummyPointerControlBlock_1_new(void);

#endif
