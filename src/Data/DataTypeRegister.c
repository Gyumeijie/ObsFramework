#include "DataTypeRegister.h"
#include "ParameterDatabase.h"
#include "DC_BasicDatabase.h" 
#include "DataTypeRegister.h"
#include "DC_DummyDatabase.h"
#include "DC_DataItem.h"
#include "DC_RawDataItem.h"
#include "DC_SettableDataItem.h"
#include "DataPool.h"
#include "DC_BasicDataPool.h" 
#include "DC_DummyDataPool.h"
#include "DC_SampleFullDataPool.h"
#include "ControlBlock.h"
#include "CopyControlBlock.h"
#include "DC_DummyCopyControlBlock.h"
#include "DataItemControlBlock.h"
#include "DC_DummyDataItemControlBlock.h"
#include "DataPoolControlBlock.h"
#include "DC_DummyDataPoolControlBlock.h"
#include "PointerControlBlock.h" 
#include "DC_DummyPointerControlBlock.h"
#include "DC_ControlAction.h"
#include "DC_ControlList.h"
#include "DC_DataPoolMonitor.h"

void data_type_register(void)
{
    ParameterDatabase_register();
    DC_BasicDatabase_register();
    DC_DummyDatabase_register(); 

    DC_DataItem_register(); 
    DC_RawDataItem_register();
    DC_SettableDataItem_register(); 

    DC_BasicDataPool_register();
    DataPool_register();
    DC_DummyDataPool_register();
    DC_SampleFullDataPool_register();

    ControlBlock_register();
    CopyControlBlock_register();
    DC_DummyCopyControlBlock_register();
    DataItemControlBlock_register();
    DC_DummyDataItemControlBlock_register();
    DataPoolControlBlock_register();
    DC_DummyDataPoolControlBlock_register();
    PointerControlBlock_register();
    DC_DummyPointerControlBlock_register();
    DC_ControlAction_register();
    DC_ControlList_register();
    DC_DataPoolMonitor_register();
}
