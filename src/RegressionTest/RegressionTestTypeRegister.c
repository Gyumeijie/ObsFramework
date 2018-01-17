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
#include "TestCaseOutOfRangeProfile_1.h"
#include "TestCaseProfileList_1.h"
#include "TestCaseBasicDatabase_1.h"
#include "TestCaseDummyDatabase_1.h" 
#include "TestCaseDataItem_1.h"
#include "TestCaseRawDataItem_1.h"
#include "TestCaseBasicDataPool_1.h" 
#include "TestCaseDummyDataPool_1.h"
#include "TestCaseDummyCopyControlBlock_1.h"
#include "TestCaseDummyDataItemControlBlock_1.h" 
#include "TestCaseDummyDataPoolControlBlock_1.h"
#include "TestCaseDummyPointerControlBlock_1.h"
#include "TestCaseDummyFsmState_1.h"
#include "TestCaseFSM_1.h"
#include "TestCaseFSM_2.h"
#include "TestCaseFSM_3.h"
#include "TestCaseFsmEvent_1.h" 
#include "TestCaseFromFsmEvent_1.h" 
#include "TestCaseUnstableFsmState_1.h"
#include "TestCaseNestedFsmActivator_1.h"
#include "TestCaseNestedFsmActivatorWithEndState_1.h"  
#include "TestCaseNestedFsmActivatorWithExitCheck_1.h"
#include "TestCaseDummyModeManager_1.h"
#include "TestCaseCyclingPunctualActionModeManager_1.h"
#include "TestCaseSimplePunctualActionModeManager_1.h"
#include "TestCaseDummyTelemetryPacket_1.h" 
#include "TestCaseDummyPUSTelemetryPacket_1.h" 
#include "TestCaseChecksum_1.h"
#include "TestCasePUSMemoryDumpOffset_1.h" 
#include "TestCaseDataItem16TmWord_1.h"
#include "TestCaseByteArrayTelemetryStream_1.h"  
#include "TestCaseDummyTelemetryStream_1.h"
#include "TestCaseCycleDataItem16TmStream_1.h"
#include "TestCaseFileTelemetryStream_1.h"

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
   
   TestCaseOutOfRangeProfile_1_register();
  
   TestCaseProfileList_1_register();

   TestCaseBasicDatabase_1_register();

   TestCaseDummyDatabase_1_register();

   TestCaseDataItem_1_register();

   TestCaseRawDataItem_1_register();

   TestCaseBasicDataPool_1_register();

   TestCaseDummyDataPool_1_register();
   
   TestCaseDummyCopyControlBlock_1_register();

   TestCaseDummyDataItemControlBlock_1_register();

   TestCaseDummyDataPoolControlBlock_1_register();

   TestCaseDummyPointerControlBlock_1_register();
   
   TestCaseDummyFsmState_1_register();

   TestCaseFSM_1_register();

   TestCaseFSM_2_register();

   TestCaseFSM_3_register();

   TestCaseFsmEvent_1_register();

   TestCaseFromFsmEvent_1_register();

   TestCaseUnstableFsmState_1_register();

   TestCaseNestedFsmActivator_1_register();

   TestCaseNestedFsmActivatorWithEndState_1_register();

   TestCaseNestedFsmActivatorWithExitCheck_1_register();

   TestCaseDummyModeManager_1_register(); 

   TestCaseCyclingPunctualActionModeManager_1_register();

   TestCaseSimplePunctualActionModeManager_1_register();

   TestCaseDummyTelemetryPacket_1_register();

   TestCaseDummyPUSTelemetryPacket_1_register(); 

   TestCaseChecksum_1_register();

   TestCasePUSMemoryDumpOffset_1_register();

   TestCaseDataItem16TmWord_1_register();

   TestCaseByteArrayTelemetryStream_1_register(); 
   
   TestCaseDummyTelemetryStream_1_register();

   TestCaseCycleDataItem16TmStream_1_register();

   TestCaseFileTelemetryStream_1_register();
}
