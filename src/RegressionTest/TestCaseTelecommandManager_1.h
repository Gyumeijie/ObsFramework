//
//
// TestCaseTelecommandManager_1.h
//


#ifndef TESTCASETELECOMMANDMANAGER_1_H
#define TESTCASETELECOMMANDMANAGER_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Check the configuration process of a telecommand manager.
 * A telecommand manager instance is created and the following specific
 * tests are performed: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified that the configuration check service of the telecommand
 * manager initially reports "object not configured".</li>
 * <li>An OBS clock is loaded in the telecommand manager and it is verified
 * that it can be correctly read out.</li>
 * <li>A telecommand loader is loaded in the telecommand manager and it is verified
 * that it can be correctly read out.</li>
 * <li>The pending telecommand list size is set and it is verified
 * that it can be correctly read out.</li>
 * <li>It is verified that the configuration check service of the telecommand
 * manager now reports "object configured".</li>
 * <li>It is verified that the number of pending telecommands is equal to
 * zero.</li>
 * </ol>
 * @see CC_TelecommandManager
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASETELECOMMANDMANAGER_1 "testcasetelecommandmanager_1"

void TestCaseTelecommandManager_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseTelecommandManager_1 {
    TestCaseGenericSetUp parent;
} TestCaseTelecommandManager_1;


typedef struct TestCaseTelecommandManager_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseTelecommandManager_1Class;


#define TESTCASETELECOMMANDMANAGER_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseTelecommandManager_1Class, \
                                        obj, TYPE_TESTCASETELECOMMANDMANAGER_1)

#define TESTCASETELECOMMANDMANAGER_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseTelecommandManager_1Class, \
                                      klass, TYPE_TESTCASETELECOMMANDMANAGER_1)

#define TESTCASETELECOMMANDMANAGER_1(obj) \
        OBJECT_CHECK(TestCaseTelecommandManager_1, \
                                        obj, TYPE_TESTCASETELECOMMANDMANAGER_1)


TestCaseTelecommandManager_1* TestCaseTelecommandManager_1_new(void);

#endif
