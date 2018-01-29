//
//
// PUSDumpMemory.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "PUSDumpMemory.h"
#include "../Telemetry/CC_TelemetryManager.h"
#include "../Telemetry/DC_PUSMemoryDumpOffset.h"
#include "../Telemetry/DC_PUSMemoryDumpAbsolute.h"
#include "../Data/DataPool.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void PUSDumpMemory_setNumberOfRawData(PUSDumpMemory *This, unsigned int max)
{
    assert(max > 0);
    assert(This->data == pNULL);

    This->maxNumberData = max;
    This->data = g_malloc(sizeof(unsigned char)*max);
    for (unsigned int i=0; i<max; i++) {
       This->data[i] = 0;
    }
}

void PUSDumpMemory_setTelemetryManager
(
    PUSDumpMemory *This, 
    CC_TelemetryManager *pTmManager
)
{
    assert(pTmManager != pNULL);
    This->pTmManager = pTmManager;
}

CC_TelemetryManager* PUSDumpMemory_getTelemetryManager(const PUSDumpMemory *This)
{
    return This->pTmManager;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Get the maximum size of the application data array. 
 * @see #setNumberOfRawData
 * @return the maximum size of the application data in number of bytes
 */
static unsigned int getNumberOfRawData(const void *obj)
{
    PUSDumpMemory *This = PUSDUMPMEMORY(obj);
    return This->maxNumberData;
}

/**
 * Implementation of the raw data load service. 
 * This method copies the argument array into an internal array. The number of
 * bytes n in the argument array must be less than the maximum value set
 * with method <code>setNumberOfRawData</code>. 
 * If an attempt is made to load a greater number of raw data, then the telecommand
 * is declared to be invalid with validity check code equal to VC_TOO_MANY_RAW_DATA. 
 * @param d the array holding the raw data
 * @param n the number of items in array d
 */
static void setRawDataFastly(void *obj, unsigned char *data, unsigned int num)
{
    PUSDumpMemory *This = PUSDUMPMEMORY(obj);

    assert(This->data != pNULL);

    if (num > This->maxNumberData) {
        PUSTelecommand_setValidityCheckCode(obj, VC_TOO_MANY_RAW_DATA);
        return;
    } 

    This->numberData = num;
    for (unsigned int i=0; i<num; i++) {
        This->data[i] = data[i];
    }

    PUSTelecommand_setValidityCheckCode(obj, 0);
    return;
}

/**
 * Return the number of application data bytes that were loaded with the
 * last call to method <code>setRawData</code>. The number returned by this
 * method is the same as the value of the argument n in the call to method
 * <code>setRawData</code>.
 * @see #setRawData
 * @return the number of application data bytes in the currently loaded packet
 */
static unsigned int getNumberOfApplicationData(const void *obj)
{
    PUSDumpMemory *This = PUSDUMPMEMORY(obj);
    return This->numberData;
}

/**
 * Perform a class-specific configuration check on the telecommand:
 * check that the maximum number of raw data has been set and that the
 * telemetry manager has been loaded.
 * @return true if the telecommand is configured, false otherwise
 */
static bool isObjectConfigured(void *obj)
{
    PUSTelecommandClass *pustc = GET_CLASS(TYPE_PUSTELECOMMAND);
    PUSDumpMemory *This = PUSDUMPMEMORY(obj);
   
    return ((CC_ROOTOBJECT_CLASS(pustc)->isObjectConfigured(obj)) &&
            (This->data != pNULL) &&
            (This->pTmManager != pNULL));
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    PUSDumpMemory *This = PUSDUMPMEMORY(obj);
    This->data = pNULL;
    This->maxNumberData = 0;
    This->numberData = 0;
    This->pTmManager = pNULL;

    TelecommandClass *tc = TELECOMMAND_GET_CLASS(obj);
    tc->setType(obj, PUS_TYPE_MEM);
}

PUSDumpMemory* PUSDumpMemory_new(void)
{
    Object *obj = object_new(TYPE_PUSDUMPMEMORY);
    return (PUSDumpMemory*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    PUSDumpMemoryClass *pusdmc = PUSDUMPMEMORY_CLASS(oc);
    pusdmc->getNumberOfApplicationData = getNumberOfApplicationData;

    TelecommandClass *tc = TELECOMMAND_CLASS(oc);
    tc->getNumberOfRawData = getNumberOfRawData;
    tc->setRawDataFastly = setRawDataFastly;

    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_PUSDUMPMEMORY,
    .parent = TYPE_PUSTELECOMMAND,
    .instance_size = sizeof(PUSDumpMemory),
    .abstract = false,
    .class_size = sizeof(PUSDumpMemoryClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void PUSDumpMemory_register(void)
{
    type_register_static(&type_info);
}
