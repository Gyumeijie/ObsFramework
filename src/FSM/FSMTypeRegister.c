#include "FSMTypeRegister.h"
#include "FsmState.h"
#include "DC_DummyFsmState.h"

void fsm_type_register(void)
{
   FsmState_register();
   DC_DummyFsmState_register();
}
