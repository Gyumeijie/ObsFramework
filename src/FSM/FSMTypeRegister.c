#include "FSMTypeRegister.h"
#include "FsmState.h"
#include "DC_DummyFsmState.h"
#include "CC_FSM.h"

void fsm_type_register(void)
{
   FsmState_register();
   DC_DummyFsmState_register();
   CC_FSM_register();   
}
