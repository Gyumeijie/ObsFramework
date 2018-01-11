#include "DataTypeRegister.h"
#include "ParameterDatabase.h"
#include "DC_BasicDatabase.h" 

void data_type_register(void)
{
    ParameterDatabase_register();
    DC_BasicDatabase_register();
}
