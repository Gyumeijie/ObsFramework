#include "RegressionTestTypeRegister.h"
#include "TestCaseRootObject_3.h"
#include "TestCaseRootObject_2.h"
#include "TestCaseRootObject_1.h"
#include "TestCaseDummyTracer_1.h"

void regression_test_type_register()
{
   TestCaseRootObject_3_register();
   TestCaseRootObject_2_register();
   TestCaseRootObject_1_register();
   TestCaseDummyTracer_1_register(); 
}
