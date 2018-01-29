//
//
// TestCaseSimpleTelemetryModeManager_1.h
//


#ifndef TESTCASESIMPLETELEMETRYMODEMANAGER_1_H
#define TESTCASESIMPLETELEMETRYMODEMANAGER_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Verify the services implemented
 * by class <code>DC_SimpleTelemetryModeManager</code>. An instance of
 * the class is created and
 * the following specific tests are performed upon it:<ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>The mode manager is configured and it is verified that it
 * has only one mode and that its default mode index is 0.</li>
 * <li>It is verified that calls to its <code>update</code>
 * method have no effect on the mode.</li>
 * </ol>
 * @see DC_SimpleTelemetryModeManager
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASESIMPLETELEMETRYMODEMANAGER_1 "testcasesimpletelemetrymodemanager_1"

void TestCaseSimpleTelemetryModeManager_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseSimpleTelemetryModeManager_1 {
    TestCaseGenericSetUp parent;
} TestCaseSimpleTelemetryModeManager_1;


typedef struct TestCaseSimpleTelemetryModeManager_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseSimpleTelemetryModeManager_1Class;


#define TESTCASESIMPLETELEMETRYMODEMANAGER_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseSimpleTelemetryModeManager_1Class, \
                                obj, TYPE_TESTCASESIMPLETELEMETRYMODEMANAGER_1)

#define TESTCASESIMPLETELEMETRYMODEMANAGER_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseSimpleTelemetryModeManager_1Class, \
                              klass, TYPE_TESTCASESIMPLETELEMETRYMODEMANAGER_1)

#define TESTCASESIMPLETELEMETRYMODEMANAGER_1(obj) \
        OBJECT_CHECK(TestCaseSimpleTelemetryModeManager_1, \
                                obj, TYPE_TESTCASESIMPLETELEMETRYMODEMANAGER_1)


TestCaseSimpleTelemetryModeManager_1* TestCaseSimpleTelemetryModeManager_1_new(void);

#endif
