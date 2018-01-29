//
//
// TestCaseManoeuvrePunctualAction_1.h
//


#ifndef TESTCASEMANOEUVREPUNCTUALACTION_1_H
#define TESTCASEMANOEUVREPUNCTUALACTION_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Verify the functionality implemented  by the <code>DC_ManoeuvrePunctualActionr</code>
 * class. An instance of this class is created and the following tests
 * are performed upon it: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified that the action is not configured at creation.</li>
 * <li>A previously created and configured <code>CC_ManoeuvreManager</code> is
 * attached to the action. It is verified that the manoeuvre manager pointer
 * can be retrieved by calling <code>getManoeuvreManager</code> and that the
 * action is not yet configured.</li>
 * <li>A previously created <code>DC_DummyManoeuvre</code> is attached to the
 * action. It is verified that the manoeuvre pointer can be retrieved by calling
 * <code>getManoeuvre</code> and that the action is now fully configured.</li>
 * <li>The inherited method <code>execute(void)</code> is invoked and it is verified
 * that the manoeuvre is loaded into the manoeuvre manager.</li>
 * </ol>
 * @see DC_ManoeuvrePunctualAction
 * @see PunctualAction
 * @see CC_ManoeuvreManager
 * @see Manoeuvre
 * @see DC_DummyManouvre
 * @author Roberto Totaro
 * @version 1.0
 */
#define TYPE_TESTCASEMANOEUVREPUNCTUALACTION_1 "testcasemanoeuvrepunctualaction_1"

void TestCaseManoeuvrePunctualAction_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseManoeuvrePunctualAction_1 {
    TestCaseGenericSetUp parent;
} TestCaseManoeuvrePunctualAction_1;


typedef struct TestCaseManoeuvrePunctualAction_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseManoeuvrePunctualAction_1Class;


#define TESTCASEMANOEUVREPUNCTUALACTION_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseManoeuvrePunctualAction_1Class, \
                                   obj, TYPE_TESTCASEMANOEUVREPUNCTUALACTION_1)

#define TESTCASEMANOEUVREPUNCTUALACTION_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseManoeuvrePunctualAction_1Class, \
                                 klass, TYPE_TESTCASEMANOEUVREPUNCTUALACTION_1)

#define TESTCASEMANOEUVREPUNCTUALACTION_1(obj) \
        OBJECT_CHECK(TestCaseManoeuvrePunctualAction_1, \
                                   obj, TYPE_TESTCASEMANOEUVREPUNCTUALACTION_1)


TestCaseManoeuvrePunctualAction_1* TestCaseManoeuvrePunctualAction_1_new(void);

#endif
