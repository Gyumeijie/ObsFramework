//
//
// RegressionTest.cpp
//

#include "../Utilities/TestSuite.h"
#include "../Utilities/TestUtilities.h"

#include "../ApplicationTypeRegister/ApplicationTypeRegister.h"
#include "./RegressionTestTypeRegister.h"

#include "TestCaseRootObject_3.h"
#include "TestCaseRootObject_1.h"
#include "TestCaseRootObject_2.h" 
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
#include "TestCasePUSDataReportingPacket_1.h"
#include "TestCasePUSDataReportingPacket_2.h"
#include "TestCasePUSDataReportingPacket_3.h"
#include "TestCaseChecksum_1.h"
#include "TestCasePUSMemoryDumpOffset_1.h" 
#include "TestCaseDataItem16TmWord_1.h"
#include "TestCaseByteArrayTelemetryStream_1.h"  
#include "TestCaseDummyTelemetryStream_1.h"
#include "TestCaseCycleDataItem16TmStream_1.h"
#include "TestCaseFileTelemetryStream_1.h"
#include "TestCaseFileTelemetryStream_2.h"
#include "TestCaseSimpleTelemetryModeManager_1.h"
#include "TestCaseCyclingTelemetryModeManager_1.h"
#include "TestCaseTelemetryManager_1.h"
#include "TestCaseTelemetryManager_2.h"
#include "TestCaseDummyTelecommand_1.h" 
#include "TestCaseDummyCriticalTelecommand_1.h" 
#include "TestCaseDummyCriticalTelecommand_2.h"
#include "TestCaseDummyPUSTelecommand_1.h"
#include "TestCaseDummyManoeuvre_1.h"
#include "TestCaseDummyConfigurableManoeuvre_1.h"
#include "TestCaseTestPUSConfigurableManoeuvre_1.h"
#include "TestCaseManoeuvreManager_1.h"
#include "TestCaseManoeuvreManager_3.h"
#include "TestCaseManoeuvrePunctualAction_1.h"
#include "TestCaseSampleFullDataPool_1.h"
#include "TestCasePUSMemoryLoadAbsolute_1.h"
#include "TestCasePUSMemoryLoadOffset_1.h"
#include "TestCasePUSMemoryLoadOffset_2.h"
#include "TestCaseTelecommandManager_1.h"
#include "TestCaseTelecommandManager_2.h"
#include "TestCaseTelecommandManager_3.h"
#include "TestCaseDummyTelecommandLoader_1.h"
#include "TestCaseBasicPUSTmStream_1.h"
#include "TestCaseIntStack_1.h"
#include "TestCaseRootObjectStack_1.h"
#include "TestCasePUSTelemetryModeManager_1.h"
#include "TestCaseBasicPUSTcLoader_1.h"
#include "TestCasePUSEventRepository_1.h" 
#include "TestCasePUSClearDataReporting_1.h"
#include "TestCasePUSControlDataReporting_1.h"
#include "TestCaseBasicReconfigurer_1.h"
#include "TestCasePunctualActionManager_1.h"
#include "TestCaseSimpleChangeProfile_1.h"
#include "TestCaseControlAction_1.h"
#include "TestCaseControlList_1.h"
#include "TestCaseDataPoolMonitor_1.h"

#include "../GeneralInclude/TestCompilerSwitches.h"                             
#include "../GeneralInclude/CompilerSwitches.h"                                 
#include "../GeneralInclude/Constants.h"

Error *error_fatal; 
Error *error_abort;
int errno;

int main(int argc, char* argv[]) {

    application_type_register(); 
    regression_test_type_register();
    
    // Open output file (only on MS_HOST)
	FILE* out = pNULL;

#ifdef MS_HOST
    if((out = fopen("RegressionTestReport.html", "w")) == pNULL){
       printf( "\nThe file 'RegressionTestReport.html' could not be opened\n" );
    } else {
       printf( "\nThe file 'RegressionTestReport.html' was successfully opened\n" );
    }
#endif

    printf( "\nBegin regression test ...\n" );

    // Create and load a test suite (NB: The TestCaseRootObject_3 must be the
    // the first test case to run because it tests the system configuration
    // service)
    TestSuite* ts = TestSuite_new(out);

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseRootObject_3_new());
    TestSuite_loadTestCase(ts, (TestCase*)TestCaseRootObject_2_new());
    TestSuite_loadTestCase(ts, (TestCase*)TestCaseRootObject_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseDummyTracer_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseEventRepository_1_new());
    TestSuite_loadTestCase(ts, (TestCase*)TestCaseEventRepository_2_new());
    TestSuite_loadTestCase(ts, (TestCase*)TestCaseEventRepository_3_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseDummyObsClock_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseEvent_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseDummyPunctualAction_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseDummyConditionalPunctualAction_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseRecoveryAction_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseFdirCheck_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseNullProfile_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseForbiddenValueProfile_1_new());
    
    TestSuite_loadTestCase(ts, (TestCase*)TestCaseDeltaProfile_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseStuckDataProfile_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseInRangeProfile_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseOutOfRangeProfile_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseProfileList_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseBasicDatabase_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseDummyDatabase_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseDataItem_1_new());
    
    TestSuite_loadTestCase(ts, (TestCase*)TestCaseRawDataItem_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseBasicDataPool_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseDummyDataPool_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseDummyCopyControlBlock_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseDummyDataItemControlBlock_1_new());
    
    TestSuite_loadTestCase(ts, (TestCase*)TestCaseDummyDataPoolControlBlock_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseDummyPointerControlBlock_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseDummyFsmState_1_new());
    
    TestSuite_loadTestCase(ts, (TestCase*)TestCaseFSM_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseFSM_2_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseFSM_3_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseFsmEvent_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseFromFsmEvent_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseUnstableFsmState_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseNestedFsmActivator_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseNestedFsmActivatorWithEndState_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseNestedFsmActivatorWithExitCheck_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseDummyModeManager_1_new());
    
    TestSuite_loadTestCase(ts, (TestCase*)TestCaseCyclingPunctualActionModeManager_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseSimplePunctualActionModeManager_1_new());
    
    TestSuite_loadTestCase(ts, (TestCase*)TestCaseDummyTelemetryPacket_1_new());
    
    TestSuite_loadTestCase(ts, (TestCase*)TestCaseDummyPUSTelemetryPacket_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCasePUSDataReportingPacket_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCasePUSDataReportingPacket_2_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCasePUSDataReportingPacket_3_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseChecksum_1_new());
    
    TestSuite_loadTestCase(ts, (TestCase*)TestCasePUSMemoryDumpOffset_1_new());
    
    TestSuite_loadTestCase(ts, (TestCase*)TestCaseDataItem16TmWord_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseByteArrayTelemetryStream_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseDummyTelemetryStream_1_new());
    
    TestSuite_loadTestCase(ts, (TestCase*)TestCaseCycleDataItem16TmStream_1_new());
#ifdef MS_HOST
    TestSuite_loadTestCase(ts, (TestCase*)TestCaseFileTelemetryStream_1_new());
#endif
    TestSuite_loadTestCase(ts, (TestCase*)TestCaseFileTelemetryStream_2_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseSimpleTelemetryModeManager_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseCyclingTelemetryModeManager_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseTelemetryManager_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseTelemetryManager_2_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseDummyTelecommand_1_new());
    
    TestSuite_loadTestCase(ts, (TestCase*)TestCaseDummyCriticalTelecommand_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseDummyCriticalTelecommand_2_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseDummyPUSTelecommand_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseDummyManoeuvre_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseDummyConfigurableManoeuvre_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseTestPUSConfigurableManoeuvre_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseManoeuvreManager_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseManoeuvreManager_3_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseManoeuvrePunctualAction_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseSampleFullDataPool_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCasePUSMemoryLoadAbsolute_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCasePUSMemoryLoadOffset_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCasePUSMemoryLoadOffset_2_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseTelecommandManager_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseTelecommandManager_2_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseTelecommandManager_3_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseDummyTelecommandLoader_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseBasicPUSTmStream_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseIntStack_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseRootObjectStack_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCasePUSTelemetryModeManager_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseBasicPUSTcLoader_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCasePUSEventRepository_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCasePUSClearDataReporting_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCasePUSControlDataReporting_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseBasicReconfigurer_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCasePunctualActionManager_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseSimpleChangeProfile_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseControlAction_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseControlList_1_new());

    TestSuite_loadTestCase(ts, (TestCase*)TestCaseDataPoolMonitor_1_new());


    // Run the test suite -- this causes all test cases in
    // the test suite to be run in sequence
    TestSuite_runTestSuite(ts);

    printf( "\nRegression test ended... \n" );


    // close output file
#ifdef MS_HOST
    fclose(out);
#endif
	return 0;
}

