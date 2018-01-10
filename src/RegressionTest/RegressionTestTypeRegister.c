#include "RegressionTestTypeRegister.h"
#include "TestCaseRootObject_3.h"
#include "TestCaseRootObject_2.h"
#include "TestCaseRootObject_1.h"
#include "TestCaseDummyTracer_1.h"
#include "TestCaseEventRepository_1.h"
#include "TestCaseEventRepository_2.h"
#include "TestCaseEventRepository_3.h"
#include "TestCaseDummyObsClock_1.h"
#include "TestCaseEvent_1.h"
#include "TestCaseDummyPunctualAction_1.h"
#include "TestCaseDummyConditionalPunctualAction_1.h"
#include "TestCaseRecoveryAction_1.h"
#include "TestCaseFdirCheck_1.h"
#include "TestCaseNullProfile_1.h"
#include "TestCaseForbiddenValueProfile_1.h"
#include "TestCaseDeltaProfile_1.h" 
#include "TestCaseStuckDataProfile_1.h"
#include "TestCaseInRangeProfile_1.h"

void regression_test_type_register()
{
   TestCaseRootObject_3_register();
   TestCaseRootObject_2_register();
   TestCaseRootObject_1_register();

   TestCaseDummyTracer_1_register(); 

   TestCaseEventRepository_1_register();
   TestCaseEventRepository_2_register();
   TestCaseEventRepository_3_register();

   TestCaseDummyObsClock_1_register();

   TestCaseEvent_1_register();

   TestCaseDummyPunctualAction_1_register();

   TestCaseDummyConditionalPunctualAction_1_register();

   TestCaseRecoveryAction_1_register();
   
   TestCaseFdirCheck_1_register();

   TestCaseNullProfile_1_register();

   TestCaseForbiddenValueProfile_1_register();

   TestCaseDeltaProfile_1_register();

   TestCaseStuckDataProfile_1_register();

   TestCaseInRangeProfile_1_register();
}
