#include "ManoeuvreTypeRegister.h"
#include "Manoeuvre.h" 
#include "DC_DummyManoeuvre.h"
#include "DC_DummyConfigurableManoeuvre.h" 

void manoeuvre_type_register(void)
{
    Manoeuvre_register(); 
    DC_DummyManoeuvre_register();
    DC_DummyConfigurableManoeuvre_register();
}
