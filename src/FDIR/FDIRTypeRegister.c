#include "FDIRTypeRegister.h"
#include "RecoveryAction.h"
#include "DC_NullRecoveryAction.h"
#include "DC_DummyRecoveryAction.h"
#include "DC_FdirCheck.h"

void fdir_type_register(void)
{
    RecoveryAction_register();
    DC_NullRecoveryAction_register();
    DC_DummyRecoveryAction_register();
    DC_FdirCheck_register();
}
