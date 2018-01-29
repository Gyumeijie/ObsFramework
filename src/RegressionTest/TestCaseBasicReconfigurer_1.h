//
//
// TestCaseBasicReconfigurer_1.h
//


#ifndef TESTCASEBASICRECONFIGURER_1_H
#define TESTCASEBASICRECONFIGURER_1_H


#include "../Utilities/TestCaseWithEvtCheck.h"
#include "../Qom/object.h"


/*
 * Verify the services of the <code>DC_BasicReconfigurer</code>. One
 * <code>DC_BasicReconfigurer</code> object is created and the following
 * tests are performed upon it: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified that the newly created object is not configured
 * and is enabled.</li>
 * <li>The enable state is changed. The success of the operation is verified.</li>
 * <li><code>setNumberOfConfigurations(void)</code> is invoked and it is verified that
 * the object is now fully configured, that the number of configurations was
 * correctly set, that all the configurations are <code>HEALTHY</code> and finally
 * that the first configuration is set as the active one.</li>
 * <li>Non-nominal behaviour check: <code>setActive(void)</code> is invoked with an out-of-range configuration
 * number. It is verified that an <code>EVT_ILLEGAL_CONFIG</code> is added to
 * the event repository.</li>
 * <li><code>setActive(void)</code> is invoked with a configuration number different
 * from the currently active one. It is verified that <code>getActive(void)</code> returns
 * the right value, and that an <code>EVT_RECONFIG</code> is added to the event
 * repository.</li>
 * <li>Non-nominal behaviour check: <code>setHealthStatus(void)</code> is invoked with an out-of-range parameter.
 * It is verified that an <code>EVT_ILLEGAL_CONFIG</code> is added to
 * the event repository.</li>
 * <li><code>setHealthStatus(void)</code> is invoked with a valid configuration number.
 * It is verified that the health state of the configuration is correctly set.</li>
 * <li>Without re-enabling the reconfigurer, <code>reconfigure(void)</code> is called
 * and it is verified that an <code>EVT_RECONFIG_DISABLED</code> event is added to
 * the repository.</li>
 * <li>The reconfigurer is enabled and <code>reconfigure(void)</code> is once again
 * called. It is verified that an <code>EVT_RECONFIG</code> event is added to the
 * repository, that the previously active configuration is set to <code>NOT_HEALTHY</code>,
 * and that the currently active one is healthy.</li>
 * <li>All the configurations are set to <code>NOT_HEALTHY</code>, <code>reconfigure(void)</code>
 * is invoked and it is verified that an <code>EVT_RECONFIG_NO_HEALTHY</code> event is
 * added to the repository.</li>
 * <li> Finally, the reconfigurer is disabled and <code>reset(void)</code> is ionvoked. It is
 * verified that after the call the configurer is once again enabled, that the active
 * configuration is set to 0, and that all the configurations are again healthy.</li>
 * </ol>
 * @see DC_BasicReconfigurer
 * @author Roberto Totaro
 * @version 1.0
 */
#define TYPE_TESTCASEBASICRECONFIGURER_1 "testcasebasicreconfigurer_1"

void TestCaseBasicReconfigurer_1_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

typedef struct TestCaseBasicReconfigurer_1 {
    TestCaseWithEvtCheck parent;
} TestCaseBasicReconfigurer_1;


typedef struct TestCaseBasicReconfigurer_1Class {
    TestCaseWithEvtCheckClass parent_class;
} TestCaseBasicReconfigurer_1Class;


#define TESTCASEBASICRECONFIGURER_1_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TestCaseBasicReconfigurer_1Class, \
                                         obj, TYPE_TESTCASEBASICRECONFIGURER_1)

#define TESTCASEBASICRECONFIGURER_1_CLASS(klass) \
        OBJECT_CLASS_CHECK(TestCaseBasicReconfigurer_1Class, \
                                       klass, TYPE_TESTCASEBASICRECONFIGURER_1)

#define TESTCASEBASICRECONFIGURER_1(obj) \
        OBJECT_CHECK(TestCaseBasicReconfigurer_1, \
                                         obj, TYPE_TESTCASEBASICRECONFIGURER_1)


TestCaseBasicReconfigurer_1* TestCaseBasicReconfigurer_1_new(void);

#endif
