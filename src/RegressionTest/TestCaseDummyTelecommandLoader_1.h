//
//
// TestCaseDummyTelecommandLoader_1.h
//


#ifndef TESTCASEDUMMYTELECOMMANDLOADER_1_H
#define TESTCASEDUMMYTELECOMMANDLOADER_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Verify the services offered by the <code>DC_DummyTelecommandLoader</code>
 * class.
 * An instance of this class is created and the following specific
 * tests are performed: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified that the configuration check service of the telecommand
 * loader initially reports "object not configured".</li>
 * <li>A telecommand manager and three sample telecommands are loaded
 * into the telecommand loader
 * and it is verified that the configuration check service of the telecommand
 * loader reports "object configured".</li>
 * <li>Two activation requests are sent to the telecommand loader and
 * it is verified that the allocation counter is incremented by two.</li>
 * </ol>
 * @see DC_DummyTelecommandLoader
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_TESTCASEDUMMYTELECOMMANDLOADER_1 "testcasedummytelecommandloader_1"

void TestCaseDummyTelecommandLoader_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseDummyTelecommandLoader_1 {
    TestCaseGenericSetUp parent;
} TestCaseDummyTelecommandLoader_1;


typedef struct TestCaseDummyTelecommandLoader_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseDummyTelecommandLoader_1Class;


#define TESTCASEDUMMYTELECOMMANDLOADER_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseDummyTelecommandLoader_1Class, \
                                    obj, TYPE_TESTCASEDUMMYTELECOMMANDLOADER_1)

#define TESTCASEDUMMYTELECOMMANDLOADER_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseDummyTelecommandLoader_1Class, \
                                  klass, TYPE_TESTCASEDUMMYTELECOMMANDLOADER_1)

#define TESTCASEDUMMYTELECOMMANDLOADER_1(obj) \
        OBJECT_CHECK(TestCaseDummyTelecommandLoader_1, \
                                    obj, TYPE_TESTCASEDUMMYTELECOMMANDLOADER_1)


TestCaseDummyTelecommandLoader_1* TestCaseDummyTelecommandLoader_1_new(void);

#endif
