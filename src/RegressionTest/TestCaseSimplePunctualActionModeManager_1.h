//
//
// TestCaseSimplePunctualActionModeManager_1.h
//


#ifndef TESTCASESIMPLEPUNCTUALACTIONMODEMANAGER_1_H
#define TESTCASESIMPLEPUNCTUALACTIONMODEMANAGER_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Verify the services implemented
 * by class <code>DC_SimplePunctualActionModeManager</code>. An instance of
 * the class is created and
 * the following specific tests are performed upon it:<ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>The mode manager is configured and it is verified that it
 * has only one mode and that its default mode index is 0.</li>
 * <li>It is verified that calls to its <code>update</code>
 * method have no effect on the mode.</li>
 * </ol>
 * @see DC_SimplePunctualActionModeManager
 * @author Roberto Totaro
 * @version 1.0
 */
#define TYPE_TESTCASESIMPLEPUNCTUALACTIONMODEMANAGER_1 "testcasesimplepunctualactionmodemanager_1"

void TestCaseSimplePunctualActionModeManager_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseSimplePunctualActionModeManager_1 {
    TestCaseGenericSetUp parent;
} TestCaseSimplePunctualActionModeManager_1;


typedef struct TestCaseSimplePunctualActionModeManager_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseSimplePunctualActionModeManager_1Class;


#define TESTCASESIMPLEPUNCTUALACTIONMODEMANAGER_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseSimplePunctualActionModeManager_1Class,\
                           obj, TYPE_TESTCASESIMPLEPUNCTUALACTIONMODEMANAGER_1)

#define TESTCASESIMPLEPUNCTUALACTIONMODEMANAGER_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseSimplePunctualActionModeManager_1Class,\
                         klass, TYPE_TESTCASESIMPLEPUNCTUALACTIONMODEMANAGER_1)

#define TESTCASESIMPLEPUNCTUALACTIONMODEMANAGER_1(obj) \
        OBJECT_CHECK(TestCaseSimplePunctualActionModeManager_1,\
                           obj, TYPE_TESTCASESIMPLEPUNCTUALACTIONMODEMANAGER_1)


TestCaseSimplePunctualActionModeManager_1* TestCaseSimplePunctualActionModeManager_1_new(void);

#endif
