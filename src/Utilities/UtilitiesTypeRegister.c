#include "UtilitiesTypeRegister.h"
#include "TestCase.h"
#include "TestCaseGenericSetUp.h"
#include "TestSuite.h"

void utilities_type_register(void)
{
    TestCase_register();
    TestSuite_register();
    TestCaseGenericSetup_register();
}
