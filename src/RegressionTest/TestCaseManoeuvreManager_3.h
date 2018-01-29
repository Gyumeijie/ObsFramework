//
//
// TestCaseManoeuvreManager_3.h
//


#ifndef TESTCASEMANOEUVREMANAGER_3_H
#define TESTCASEMANOEUVREMANAGER_3_H


#include "../Utilities/TestCaseWithEvtCheck.h"
#include "../Qom/object.h"


/*
 * Verify the suspend/resume operations on manoeuvres and the use of the activation
 * step counter.
 * One instance of the <code>DC_DummyConfigurableManoeuvre</code> class is created and loaded
 * in a manoeuvre manager. The following operations are then performed: <ol>
 * <li>The <code>startCheck</code>
 * and <code>continuationCheck</code> flags of the manoeuvre are set to <code>true</code>.
 * The <code>terminationCheck</code> of the manoeuvre is set to <code>false</code>.</li>
 * <li>It is verified that the initial value of the activation step counter is equal
 * to zero.</li>
 * <li><code>activate(void)</code> is invoked twice and it is verified that the continuation
 * action counter of the manoeuvre is incremented twice.</li>
 * <li>It is verified that the activation step counter now has value 2.</li>
 * <li>The manoeuvre is suspended(its isSuspended flag is set to true), the manoeuvre
 * manager is activated and it is verified that the continuation counter is not incremented.</li>
 * <li>It is verified that the activation step counter has not been incremented.</li>
 * <li>The <code>terminationCheck</code> of the manoeuvre is set to <code>true</code>, the
 * manoeuvre manager is activated(thus causing the manoeuvre to be terminated and
 * unloaded) and it is verified that the manoeuvre status is
 * "not suspended".<li>
 * <li>The manoeuvre is reloaded, it is suspended and then manoeuvre manager is
 * activated. It is verified that the activation step counter has been reset to zero.<li>
 * <li>The manoeuvre is aborted. It is verified
 * that the manoeuvre status is changed to "not suspended".<li>
 * <li><li>
 * </ol>
 * @see CC_ManoeuvreManager
 * @see DC_DummyConfigurableManoeuvre
 * @see Manoeuvre#setIsSuspended
 * @author A. Pasetti
 * @version 1.0
 */
#define TYPE_TESTCASEMANOEUVREMANAGER_3 "testcasemanoeuvremanager_3"

void TestCaseManoeuvreManager_3_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseManoeuvreManager_3 {
    TestCaseWithEvtCheck parent;
} TestCaseManoeuvreManager_3;


typedef struct TestCaseManoeuvreManager_3Class {
    TestCaseWithEvtCheckClass parent_class;
} TestCaseManoeuvreManager_3Class;


#define TESTCASEMANOEUVREMANAGER_3_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseManoeuvreManager_3Class, \
                                          obj, TYPE_TESTCASEMANOEUVREMANAGER_3)

#define TESTCASEMANOEUVREMANAGER_3_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseManoeuvreManager_3Class, \
                                        klass, TYPE_TESTCASEMANOEUVREMANAGER_3)

#define TESTCASEMANOEUVREMANAGER_3(obj) \
        OBJECT_CHECK(TestCaseManoeuvreManager_3, \
                                          obj, TYPE_TESTCASEMANOEUVREMANAGER_3)


TestCaseManoeuvreManager_3* TestCaseManoeuvreManager_3_new(void);

#endif
