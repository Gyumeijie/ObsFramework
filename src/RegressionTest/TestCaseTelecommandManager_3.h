//
//
// TestCaseTelecommandManager_3.h
//


#ifndef TESTCASETELECOMMANDMANAGER_3_H
#define TESTCASETELECOMMANDMANAGER_3_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Check the non-nominal telecommand execution implemented by the
 * telecommand manager.
 * The test uses an instance of class <code>DC_DummyTelecommandLoader</code>
 * as a telecommand loader and three instances of class
 * <code>DC_DummyTelecommand</code> as dummy telecommands.
 * All the telecommands have a time tag equal to zero(immediate execution).
 * The first telecommand is configured to have an execution check that
 * returns "cannot be executed".
 * The second telecommand is configured to have a validity check that
 * returns "telecommand not valid".
 * The telecommand manager is configured with a pending telecommand
 * list size of 2. The test begins by activating the telecommand loader
 * twice to force it to attempt to load the first two dummy telecommands
 * into the telecommand manager. The following specific tests are
 * then executed: <ol>
 * <li>It is verified that the telecommand manager rejects the second
 * telecommand because it fails its validity check.</li>
 * <li>The telecommand loader is activated two more times and it is
 * verified that the telecommand manager rejects the last load attempt
 * because its pending telecommand list is full.</li>
 * <li>The telecommand manager is activated and it is verified that
 * the first telecommand is unloaded without being executed because
 * its execution check fails.</li>
 * <li>It is checked that the allocation counter in the dummy telecommand
 * loader is back to zero.</li>
 * <li>It is verified that the second telecommand is executed.</li>
 * <li>The telecommands loader is activated three times and it is verified
 * that two telecommands are loaded in the telecommand manager(the second
 * one is rejected because it fails its validity check).</li>
 * <li>The telecommands manager is reset and it is verified that the number of
 * pending telecommands goes back to zero.</li>
 * <li>It is verified that two events EVT_TC_ABORTED have been generated
 * as a result of the reset operation.</li>
 * <li>It is checked that the allocation counter in the dummy telecommand
 * loader is back to zero.</li>
 * <li>The telecommands loader is activated three times and it is verified
 * that two telecommands are loaded in the telecommand manager(the second
 * one is rejected because it fails its validity check).</li>
 * <li>An abort request is sent to the first telecommand identified by its
 * identifier. It is verified that only one pending telecommand is left.</li>
 * <li>It is checked that the allocation counter in the dummy telecommand
 * loader is equal to 1.</li>
 * <li>It is checked that one event of type EVT_TC_ABORTED was generated.</li>
 * <li>An abort request is sent to the third telecommand identified by its
 * pointer. It is verified that there are no pending telecommand left.</li>
 * <li>It is checked that the allocation counter in the dummy telecommand
 * loader is back to zero.</li>
 * <li>It is checked that one event of type EVT_TC_ABORTED was generated.</li>
 * </ol>
 * @see CC_TelecommandManager
 * @see DC_DummyTelecommand
 * @see DC_DummyTelecommandLoader
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASETELECOMMANDMANAGER_3 "testcasetelecommandmanager_3"

void TestCaseTelecommandManager_3_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseTelecommandManager_3 {
    TestCaseGenericSetUp parent;
} TestCaseTelecommandManager_3;


typedef struct TestCaseTelecommandManager_3Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseTelecommandManager_3Class;


#define TESTCASETELECOMMANDMANAGER_3_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseTelecommandManager_3Class, \
                                        obj, TYPE_TESTCASETELECOMMANDMANAGER_3)

#define TESTCASETELECOMMANDMANAGER_3_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseTelecommandManager_3Class, \
                                      klass, TYPE_TESTCASETELECOMMANDMANAGER_3)

#define TESTCASETELECOMMANDMANAGER_3(obj) \
        OBJECT_CHECK(TestCaseTelecommandManager_3, \
                                        obj, TYPE_TESTCASETELECOMMANDMANAGER_3)


TestCaseTelecommandManager_3* TestCaseTelecommandManager_3_new(void);

#endif
