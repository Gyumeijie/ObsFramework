//
//
// TestCaseControlList_1.h
//
//
// Change Record:


#ifndef TESTCASECONTROLLIST_1_H
#define TESTCASECONTROLLIST_1_H


#include "../Utilities/TestCaseWithEvtCheck.h"
#include "../Qom/object.h"


/*
 * Verify the <code>DC_ControlList</code> class.
 * An instance of this class is created and the following  tests are
 * performed on it:<ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified that the newly created object is not configured.</li>
 * <li>The control block list size is set. It is then verified that
 * <code>getListSize(void)</code> returns the correct value.</li>
 * <li>A number of pre-configured control blocks is loaded and it is verified that
 * <code>getControlBlock(void)</code> returns the correct values.</li>
 * <li>During the loading of the control blocks, it is verified that the object
 * stays in the unconfigured status until the last control block is loaded.</li>
 * <li>Non-nominal behaviour check: it is verified that an invocation of <code>setControlBlock(void)</code> with
 * an illegal index generates an error report.</li>
 * <li>The <code>execute(void)</code> method is invoked. It is verified that the return
 * code is <code>ACTION_SUCCESS</code> and that the <code>propagate(void)</code> method
 * of all the loaded control blocks is invoked.</li>
 * <li><code>reset(void)</code> is called and it is verified that the status of all
 * the loaded control blocks is reset to its default value.</li>
 * </ol>
 * @see DC_ControlList
 * @see DC_DummyControlBlock
 * @author Roberto Totaro
 * @version 1.0
 */
#define TYPE_TESTCASECONTROLLIST_1 "testcasecontrollist_1"

void TestCaseControlList_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseControlList_1 {
    TestCaseWithEvtCheck parent;
} TestCaseControlList_1;


typedef struct TestCaseControlList_1Class {
    TestCaseWithEvtCheckClass parent_class;
} TestCaseControlList_1Class;


#define TESTCASECONTROLLIST_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseControlList_1Class, \
                                            obj, TYPE_TESTCASECONTROLLIST_1)

#define TESTCASECONTROLLIST_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseControlList_1Class, \
                                          klass, TYPE_TESTCASECONTROLLIST_1)

#define TESTCASECONTROLLIST_1(obj) \
        OBJECT_CHECK(TestCaseControlList_1, obj, TYPE_TESTCASECONTROLLIST_1)


TestCaseControlList_1* TestCaseControlList_1_new(void);

#endif
