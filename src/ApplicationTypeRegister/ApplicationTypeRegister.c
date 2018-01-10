#include "ApplicationTypeRegister.h"
#include "../System/SystemTypeRegister.h"
#include "../Base/BaseTypeRegister.h"
#include "../Event/EventTypeRegister.h"
#include "../Utilities/UtilitiesTypeRegister.h"
#include "../FDIR/FDIRTypeRegister.h"
#include "../Qom/object.h"

void application_type_register(void)
{
    object_type_register();
    
    base_type_register();
    system_type_register();
    event_type_register();
    utilities_type_register();
    fdir_type_register();
}


