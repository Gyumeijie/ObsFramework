//
//
// TestCaseDummyModeManager_1.h
//


#ifndef TESTCASEDUMMYMODEMANAGER_1_H
#define TESTCASEDUMMYMODEMANAGER_1_H


#include "../Utilities/TestCaseWithEvtCheck.h"
#include "../Qom/object.h"


/*
 * Verify the configuration and mode management services implemented
 * by class <code>ModeManager</code>. Since this class is abstract, the
 * verification is performed on the class <code>DummyModeManager</code>.
 * An instance of this class is created and the following tests
 * are performed upon it: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified that the mode manager is not configured at
 * creation.</li>
 * <li>The number of modes is loaded and the correctness of the
 * load operation is verified.</li>
 * <li>The default mode is loaded and it is verified that the mode
 * manager is now configured and that the current mode is
 * equal to the default mode.</li>
 * <li>noon-nominal behaviour check: an out-of-range default mode is loaded and
 * it is checked that the correct event is generated.</li>
 * <li>It is verified that all mode transitions are enabled.</li>
 * <li>An update request is performed, it is verified that it
 * results in a change of mode and that this is recorded as an
 * event.</li>
 * <li>All mode transitions are disabled and it is verified that
 * the disable request is correctly performed.</li>
 * <li>A second update request is performed, it is verified that
 * no mode change occurs, and that an event is generated to
 * report the fact that a mode transition was attempted but
 * could not be executed because the transition was disabled.</li>
 * <li>General mode transitions are again enabled and then mode
 * transitions to a particular target mode are
 * disabled and it is verified that the disable request is
 * correctly executed.</li>
 * <li>A third update request is performed that should trigger
 * the disabled mode transition and it is verified that
 * no mode transition occurs.</li>
 * <li>Non-nominal behaviour check: an attempt is made to disable mode
 * transitions to an out-of-range target mode and it is checked
 * that the correct event is generated.</li>
 * <li>A reset request is made and it is verified that the state
 * of the mode manager is brought back to where it was after
 * the component's configuration was terminated.</li>
 * </ol>
 * @see DC_DummyModeManager
 * @see ModeManager
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEDUMMYMODEMANAGER_1 "testcasedummymodemanager_1"

void TestCaseDummyModeManager_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseDummyModeManager_1 {
    TestCaseWithEvtCheck parent;
} TestCaseDummyModeManager_1;


typedef struct TestCaseDummyModeManager_1Class {
    TestCaseWithEvtCheckClass parent_class;
} TestCaseDummyModeManager_1Class;


#define TESTCASEDUMMYMODEMANAGER_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseDummyModeManager_1Class,\
                                          obj, TYPE_TESTCASEDUMMYMODEMANAGER_1)

#define TESTCASEDUMMYMODEMANAGER_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseDummyModeManager_1Class,\
                                        klass, TYPE_TESTCASEDUMMYMODEMANAGER_1)

#define TESTCASEDUMMYMODEMANAGER_1(obj) \
        OBJECT_CHECK(TestCaseDummyModeManager_1,\
                                          obj, TYPE_TESTCASEDUMMYMODEMANAGER_1)


TestCaseDummyModeManager_1* TestCaseDummyModeManager_1_new(void);

#endif
