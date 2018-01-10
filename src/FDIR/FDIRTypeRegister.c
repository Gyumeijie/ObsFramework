#include "FDIRTypeRegister.h"
#include "RecoveryAction.h"
#include "DC_NullRecoveryAction.h"
#include "DC_DummyRecoveryAction.h"

void fdir_type_register(void)
{
    RecoveryAction_register();
    DC_NullRecoveryAction_register();
    DC_DummyRecoveryAction_register();
}
