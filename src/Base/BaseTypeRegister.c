#include "CC_RootObject.h"
#include "BaseTypeRegister.h"
#include "PunctualAction.h"
#include "DC_DummyPunctualAction.h"
#include "ConditionalPunctualAction.h"
#include "DC_DummyConditionalPunctualAction.h"
#include "ModeManager.h" 
#include "DC_DummyModeManager.h"
#include "PunctualActionModeManager.h"
#include "PunctualActionListModeManager.h"
#include "DC_CyclingPunctualActionModeManager.h"

void base_type_register(void)
{
    CC_RootObject_register();

    PunctualAction_register();
    DC_DummyPunctualAction_register();

    ConditionalPunctualAction_register();
    DC_DummyConditionalPunctualAction_register();

    ModeManager_register();
    DC_DummyModeManager_register();
    PunctualActionModeManager_register();
    PunctualActionListModeManager_register();
    DC_CyclingPunctualActionModeManager_register();
}
