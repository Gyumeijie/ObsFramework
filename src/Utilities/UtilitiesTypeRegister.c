#include "UtilitiesTypeRegister.h"
#include "TestCase.h"
#include "TestCaseGenericSetUp.h"
#include "TestSuite.h"
#include "TestCaseWithEvtCheck.h"

void utilities_type_register(void)
{
    TestCase_register();
    TestSuite_register();
    TestCaseGenericSetup_register();
    TestCaseWithEvtCheck_register();
}
