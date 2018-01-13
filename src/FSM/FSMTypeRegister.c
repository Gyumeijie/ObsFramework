#include "FSMTypeRegister.h"
#include "FsmState.h"
#include "DC_DummyFsmState.h"
#include "CC_FSM.h"
#include "DC_FsmEvent.h"
#include "DC_FromFsmEvent.h"

void fsm_type_register(void)
{
   FsmState_register();
   DC_DummyFsmState_register();
   CC_FSM_register();   
   DC_FsmEvent_register();
   DC_FromFsmEvent_register();
}
