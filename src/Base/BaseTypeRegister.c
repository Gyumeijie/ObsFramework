#include "CC_RootObject.h"
#include "BaseTypeRegister.h"
#include "PunctualAction.h"
#include "DC_DummyPunctualAction.h"
#include "ConditionalPunctualAction.h"
#include "DC_DummyConditionalPunctualAction.h"

void base_type_register(void)
{
    CC_RootObject_register();

    PunctualAction_register();
    DC_DummyPunctualAction_register();

    ConditionalPunctualAction_register();
    DC_DummyConditionalPunctualAction_register();

}
