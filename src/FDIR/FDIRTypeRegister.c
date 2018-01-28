#include "FDIRTypeRegister.h"
#include "RecoveryAction.h"
#include "DC_NullRecoveryAction.h"
#include "DC_DummyRecoveryAction.h"
#include "DC_FdirCheck.h"
#include "MonitoringProfile.h"
#include "DC_NullProfile.h"
#include "DC_ForbiddenValueProfile.h"
#include "DC_DeltaProfile.h"
#include "DC_StuckDataProfile.h"
#include "RangeProfile.h"
#include "DC_InRangeProfile.h"
#include "DC_OutOfRangeProfile.h"
#include "DC_ProfileList.h"
#include "DC_SimpleChangeProfile.h"

void fdir_type_register(void)
{
    RecoveryAction_register();
    DC_NullRecoveryAction_register();
    DC_DummyRecoveryAction_register();
    DC_FdirCheck_register();
    MonitoringProfile_register();
    DC_NullProfile_register();
    DC_ForbiddenValueProfile_register();
    DC_DeltaProfile_register();
    DC_StuckDataProfile_register();
    RangeProfile_register();
    DC_InRangeProfile_register();
    DC_OutOfRangeProfile_register();
    DC_ProfileList_register();
    DC_SimpleChangeProfile_register();
}
