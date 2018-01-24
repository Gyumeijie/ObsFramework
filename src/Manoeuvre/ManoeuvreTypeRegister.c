#include "ManoeuvreTypeRegister.h"
#include "Manoeuvre.h" 
#include "DC_DummyManoeuvre.h"
#include "DC_DummyConfigurableManoeuvre.h" 
#include "PUSTcManoeuvre.h"
#include "DC_TestPUSConfigurableManoeuvre.h"
#include "CC_ManoeuvreManager.h"
#include "DC_ManoeuvrePunctualAction.h"
#include "CC_ManoeuvreFactory.h"

void manoeuvre_type_register(void)
{
    Manoeuvre_register(); 
    DC_DummyManoeuvre_register();
    DC_DummyConfigurableManoeuvre_register();
    PUSTcManoeuvre_register();
    DC_TestPUSConfigurableManoeuvre_register();
    DC_ManoeuvrePunctualAction_register();

    CC_ManoeuvreManager_register();

    CC_ManoeuvreFactory_register();
}
