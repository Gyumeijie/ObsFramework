//
//
// TestCaseDummyCriticalTelecommand_2.h
//


#ifndef TESTCASEDUMMYCRITICALTELECOMMAND_2_H
#define TESTCASEDUMMYCRITICALTELECOMMAND_2_H


#include "../Utilities/TestCaseWithEvtCheck.h"
#include "../Qom/object.h"


/*
 * Check selected functionalities of critical telecommands. The check
 * is performed on an instance of class <code>DC_DummyCriticalTelecommand</code>.
 * The following functionalities are checked:<ol>
 * <li><code>canExecute(void)</code></li>
 * <li><code>doAction(void)</code></li>
 * <li><code>reset(void)</code></li>
 * <li><code>doCriticalAction(void)</code></li>
 * <li><code>getNumberOfExecutions(void)</code></li>
 * </ol>
 * An instance of the <code>DC_DummyCriticalTelecommand</code> class is created
 * and the following tests are performed:<ol>
 * <li>The object is initialized and its criticality level set to NOT_CRITICAL.
 * It is verified that <code>canExecute(void)</code> returns true.</li>
 * <li><code>execute(void)</code> is called and it is verified that it returns
 * <code>ACTION_SUCCESS</code> and that <code>doCriticalAction(void)</code> is called.</li>
 * <li>The TC criticality level is set to CRITICAL, <code>canExecute(void)</code> is called
 * and it is verified that it returns true.</li>
 * <li><code>execute(void)</code> is invoked and it is verified that it returns
 * <code>ACTION_SUCCESS</code>, that the TC is armed, that <code>timeWhenArmed</code> is
 * set to the current time and that an <code>EVT_CRIT_TC_ARMED</code> event is added
 * to the repository.</li>
 * <li><code>canExecute(void)</code> is invoced once again. This time it shall fail and add an
 * <code>EVT_CRIT_TC_IMG_INV</code> event to the repository(the TC image is not valid). The
 * TC shall still be armed.</li>
 * <li><code>reset(void)</code> is called and it is verified that all the state variables are
 * set to their initial values. <code>pObsClock</code> can not be accessed, however.</li>
 * <li>The TC is re-initialized, re-armed(by calling <code>execute</code>) and the image
 * validity flag is set to true. A this point it is verified that <code>canExecute(void)</code>
 * returns true.</li>
 * <li><code>execute(void)</code> is invoked and it is verified that <code>numberOfExecutions</code>
 * is incremented(meaning that <code>doCriticalAction</code> was invoked). It is also
 * verified that the TC is no longer armed and that the "time when armed" is set to an
 * invalid value.</li>
 * <li>The TC is reset, initialized and re-armed. The image validity is set to true and the
 * OBS clock is advanced to the end of the TC's armed duration interval. It is then
 * verified that a call to <code>canExecute(void)</code> returns false and that an event of type
 * <code>EVT_CRIT_TC_TIMEOUT</code> is added to the repository.</li>
 * <li>The previous step is repeated with the only difference that now the image validity
 * flag is set to false.</li>
 * </ol>
 * @see DC_DummyCriticalTelecommand
 * @see TestCaseDummyCriticalTelecommand_1
 * @author Roberto Totaro
 * @version 1.0
 */
#define TYPE_TESTCASEDUMMYCRITICALTELECOMMAND_2 "testcasedummycriticaltelecommand_2"

void TestCaseDummyCriticalTelecommand_2_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseDummyCriticalTelecommand_2 {
    TestCaseWithEvtCheck parent;
} TestCaseDummyCriticalTelecommand_2;


typedef struct TestCaseDummyCriticalTelecommand_2Class {
    TestCaseWithEvtCheckClass parent_class;
} TestCaseDummyCriticalTelecommand_2Class;


#define TESTCASEDUMMYCRITICALTELECOMMAND_2_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseDummyCriticalTelecommand_2Class, \
                                  obj, TYPE_TESTCASEDUMMYCRITICALTELECOMMAND_2)

#define TESTCASEDUMMYCRITICALTELECOMMAND_2_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseDummyCriticalTelecommand_2Class, \
                                klass, TYPE_TESTCASEDUMMYCRITICALTELECOMMAND_2)

#define TESTCASEDUMMYCRITICALTELECOMMAND_2(obj) \
        OBJECT_CHECK(TestCaseDummyCriticalTelecommand_2, \
                                  obj, TYPE_TESTCASEDUMMYCRITICALTELECOMMAND_2)


TestCaseDummyCriticalTelecommand_2* TestCaseDummyCriticalTelecommand_2_new(void);

#endif
