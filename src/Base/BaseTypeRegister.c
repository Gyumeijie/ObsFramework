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
#include "DC_SimplePunctualActionModeManager.h" 
#include "DC_BasicReconfigurer.h"
#include "CC_PunctualActionManager.h"

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
    DC_SimplePunctualActionModeManager_register(); 

    DC_BasicReconfigurer_register();

    CC_PunctualActionManager_register();
}
