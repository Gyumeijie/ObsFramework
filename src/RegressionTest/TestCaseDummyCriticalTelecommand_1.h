//
//
// TestCaseDummyCriticalTelecommand_1.h
//


#ifndef TESTCASEDUMMYCRITICALTELECOMMAND_1_H
#define TESTCASEDUMMYCRITICALTELECOMMAND_1_H


#include "../Utilities/TestCaseGenericSetUp.h"
#include "../Qom/object.h"


/*
 * Verify the basic services offered by critical telecommands as implemented
 * by the <code>DC_DummyCriticalTelecommand</code> class. The <code>canExecute(void)</code>,
 * <code>doAction(void)</code> and <code>reset(void)</code> methods are tested by
 * <code>TestCaseDummyCriticalTelecommand_2</code>. An instance of this class is created
 * and the following tests are performed:<ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>The Telecommand class(CriticalTelecommand's base class) is
 * configured by invoking <code>setTimeTag(void)</code>. It
 * is verified that the <code>DC_DummyCriticalTelecommand</code> class is not yet fully
 * configured.</li>
 * <li><code>setMaxArmedDuration(void)</code> is called. It is verified that the class is not
 * yet configured and that <code>getMaxArmedDuration</code> returns the correct value.</li>
 * <li>An <code>DC_DummyObsClock</code> object is created and it is attached to the critical
 * telecommand by calling <code>setObsClock(void)</code>. It is verified that the object is finally
 * configured and that <code>getObsClock(void)</code> returns the correct value.</li>
 * <li>It is verified that the newly created telecommand is critical and not armed.</li>
 * <li>It is verified that the criticality level can be modified.</li>
 * <li>It is verified that the image validity flag can be set and retrieved correctly.</li>
 * <li>Finally, it is verified that the "time when armed" is set to an invalid value.</li>
 * </ol>
 * @see DC_DummyCriticalTelecommand
 * @see TestCaseDummyCriticalTelecommand_2
 * @author Roberto Totaro
 * @version 1.0
 */
#define TYPE_TESTCASEDUMMYCRITICALTELECOMMAND_1 "testcasedummycriticaltelecommand_1"

void TestCaseDummyCriticalTelecommand_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseDummyCriticalTelecommand_1 {
    TestCaseGenericSetUp parent;
} TestCaseDummyCriticalTelecommand_1;


typedef struct TestCaseDummyCriticalTelecommand_1Class {
    TestCaseGenericSetUpClass parent_class;
} TestCaseDummyCriticalTelecommand_1Class;


#define TESTCASEDUMMYCRITICALTELECOMMAND_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseDummyCriticalTelecommand_1Class, \
                                  obj, TYPE_TESTCASEDUMMYCRITICALTELECOMMAND_1)

#define TESTCASEDUMMYCRITICALTELECOMMAND_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseDummyCriticalTelecommand_1Class, \
                                klass, TYPE_TESTCASEDUMMYCRITICALTELECOMMAND_1)

#define TESTCASEDUMMYCRITICALTELECOMMAND_1(obj) \
        OBJECT_CHECK(TestCaseDummyCriticalTelecommand_1, \
                                  obj, TYPE_TESTCASEDUMMYCRITICALTELECOMMAND_1)


TestCaseDummyCriticalTelecommand_1* TestCaseDummyCriticalTelecommand_1_new(void);

#endif
