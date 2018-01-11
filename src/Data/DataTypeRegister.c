#include "DataTypeRegister.h"
#include "ParameterDatabase.h"
#include "DC_BasicDatabase.h" 
#include "DataTypeRegister.h"
#include "DC_DummyDatabase.h"
#include "DC_DataItem.h"
#include "DC_RawDataItem.h"
#include "DataPool.h"
#include "DC_BasicDataPool.h" 

void data_type_register(void)
{
    ParameterDatabase_register();
    DC_BasicDatabase_register();
    DC_DummyDatabase_register(); 
    DC_DataItem_register(); 
    DC_RawDataItem_register();
    DC_BasicDataPool_register();
    DataPool_register();
}
