//
//
// TestCasePunctualActionManager_1.h
//


#ifndef TESTCASEPUNCTUALACTIONMANAGER_1_H
#define TESTCASEPUNCTUALACTIONMANAGER_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Verify the services offered by the punctual action manager as implemented
 * by the <code>CC_PunctualActionManager</code> class.
 * An instance of this class is created and the following tests are performed:<ol>
 * <li>The correctness of the class id is verified.</li>
 * <li>It is verified that the newly created object is not configured and that
 * <code>getPunctualActionModeManager(void)</code> returns a null pointer.</li>
 * <li>The <code>setPunctualActionModeManager(void)</code> is invoked with a pointer
 * to a properly configured <code>PunctualActionModeManager</code> object. It is
 * verified that <code>getPunctualActionModeManager(void)</code> returns the correct
 * pointer and that the object is configured.</li>
 * <li>The <code>activate(void)</code> method is invoked twice and it is verified that
 * the activation counters of the <code>DC_DummyPunctualAction</code> objects in the
 * mode manager list are equal to two.</li>
 * </ol>
 * @see CC_PunctualActionManager
 * @see DC_DummyPunctualAction
 * @see DC_SimplePunctualActionModeManager
 * @author Roberto Totaro
 * @version 1.0
 */
#define TYPE_TESTCASEPUNCTUALACTIONMANAGER_1 "testcasepunctualactionmanager_1"

void TestCasePunctualActionManager_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCasePunctualActionManager_1 {
    TestCaseGenericSetUp parent;
} TestCasePunctualActionManager_1;


typedef struct TestCasePunctualActionManager_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCasePunctualActionManager_1Class;


#define TESTCASEPUNCTUALACTIONMANAGER_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCasePunctualActionManager_1Class, \
                                     obj, TYPE_TESTCASEPUNCTUALACTIONMANAGER_1)

#define TESTCASEPUNCTUALACTIONMANAGER_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCasePunctualActionManager_1Class, \
                                   klass, TYPE_TESTCASEPUNCTUALACTIONMANAGER_1)

#define TESTCASEPUNCTUALACTIONMANAGER_1(obj) \
        OBJECT_CHECK(TestCasePunctualActionManager_1, \
                                     obj, TYPE_TESTCASEPUNCTUALACTIONMANAGER_1)


TestCasePunctualActionManager_1* TestCasePunctualActionManager_1_new(void);

#endif
