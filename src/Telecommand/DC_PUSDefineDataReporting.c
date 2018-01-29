//
//
// DC_PUSDefineDataReporting.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "DC_PUSDefineDataReporting.h"
#include "../Telemetry/CC_TelemetryPacketFactory.h"
#include "../Telemetry/DC_PUSTelemetryModeManager.h"
#include "../Data/DataPool.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_PUSDefineDataReporting_setNumberOfRawData
(
    DC_PUSDefineDataReporting *This, 
    unsigned int max
)
{
    assert(max > 0);
    assert(This->data == pNULL);

    This->maxNumberData = max;
    This->data = g_malloc(sizeof(unsigned char)*max);
    for (unsigned int i=0; i<max; i++) {
        This->data[i] = 0;
    }
}

void DC_PUSDefineDataReporting_setPUSTelemetryModeManager
(
    DC_PUSDefineDataReporting *This,
    DC_PUSTelemetryModeManager *pTmModeManager
)
{
    assert(pTmModeManager != pNULL);
    This->pTmModeManager = pTmModeManager;
}

DC_PUSTelemetryModeManager* DC_PUSDefineDataReporting_getPUSTelemetryModeManager
(
    const DC_PUSDefineDataReporting *This
)
{
    return This->pTmModeManager;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Use the application data to configure and load a data reporting telemetry packet.
 * This method queries the dynamic telemetry packet factory for a new
 * data reporting packet. If it obtains it, it loads it with the application
 * data and then loads it in the PUS telemetry mode manager.
 * If either of these two operations fails, the method returns with a
 * failure code(see class comment).
 * <p>
 * In order to retrieve a free packet from the telemetry packet factory 
 * with the appropriate characteristics, this method has to extract the
 * following data from the application data: <ul>
 * <li>The number of fixed-length arrays</li>
 * <li>The size of the packet value buffer</li>
 * </ul>
 * The above figures are computed by processing the content of the application
 * data. The computation makes certain assumptions about the structure of the
 * application data. The assumptions are the same as are made in class
 * <code>DC_PUSDataReportingPacket</code>.
 * Some consistency checks are performed during the processing of the
 * application data. If these fail, then the method returns with a failure
 * code(see class comment). The consistency check will catch situations where
 * the number of fixed-length arrays or the number of parameters defined by
 * the application data is not consistent with the length of the application
 * data as defined when calling method <code>setRawData</code>.
 * @see PunctualAction#execute
 * @return action outcome code(see class comment)
 */
static TD_ActionOutcome doAction(void *obj)
{
    DC_PUSDefineDataReporting *This = DC_PUSDEFINEDATAREPORTING(obj);
    TelecommandClass *tc = TELECOMMAND_GET_CLASS(obj);
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);

    assert((tc->getSubType(obj) == PUS_ST_DATA_REP_NEW_HK) ||
           (tc->getSubType(obj) == PUS_ST_DATA_REP_NEW_DG));
    assert(cc_roc->isObjectConfigured(obj));

    CC_TelemetryPacketFactory *pFct = CC_TelemetryPacketFactory_getInstance();
    DataPool *dp = CC_RootObject_getDataPool();
    DataPoolClass *dpc = DATAPOOL_GET_CLASS(dp);
    unsigned char* const data = This->data;

    // Retrieve the number of parameters that are sampled only once per cycle
    unsigned short pos = sizeof(TD_SID) + sizeof(TD_PUSCollectionInterval);
    TD_PUSNumberOfParameters NPAR1 = *(TD_PUSNumberOfParameters*)(data+pos);
    pos += sizeof(TD_PUSNumberOfParameters);      // position of first parameter


    // Define variable to hold the length of the packet value buffer
    unsigned short val = 0;

    // Process the parameters that are sampled once per interval
    TD_DataPoolId id;
    while (pos < NPAR1*sizeof(TD_PUSNumberOfParameters)) {
          id = *(TD_PUSNumberOfParameters*)(data+pos);
          if (dpc->isFloat(dp, id)) {
               val += sizeof(TD_Float);
          } else {
               val += sizeof(TD_Integer);
          }
     }   

    // Retrieve the number of fixed-length arrays
    pos += NPAR1*sizeof(TD_DataPoolId);
    TD_PUSNumberOfParameters NFA = *(TD_PUSNumberOfParameters*)(data+pos);
    pos += sizeof(TD_PUSNumberOfParameters);

    // Process the fixed-length arrays
    TD_PUSNumberOfParameters NPAR = 0;
    for (unsigned int i=0; i<NFA; i++) {
        pos += sizeof(unsigned short);
        NPAR = *(TD_PUSNumberOfParameters*)(data+pos);
        pos += sizeof(TD_PUSNumberOfParameters);

        // Process the i-th fixed-length array
        for (unsigned int i=0; i<NPAR; i++) {
           id = *(TD_PUSNumberOfParameters*)(data+pos);
           if (dpc->isFloat(dp, id)) {
                val += sizeof(TD_Float);
           } else {
                val += sizeof(TD_Integer);
           }
        }
    }

    // Retrieve the telemetry packet from the dynamic factory
    DC_PUSDataReportingPacket *pPck;
    pPck = CC_TelemetryPacketFactory_allocatePUSDataReportingPacket(pFct, 
                                                   This->numberData, val, NFA);
    if (pPck == pNULL) {
        return PACKET_NOT_FOUND;
    }

    // Check consistency: the value of pos must be the same as the total number 
    // of application data
    if (pos != This->numberData) {
        return APP_DATA_INCONSISTENT;
    }

    // Load the application data in the telemetry packet
    for (unsigned int i=0; i<This->numberData; i++) {
        DC_PUSDataReportingPacket_setDefinitionBuffer(pPck, i, data[i]);
    }

    // Load the telemetry packet in the telemetry mode manager
    if (DC_PUSTelemetryModeManager_isFull(This->pTmModeManager)) {
        TelemetryPacket_setInUse((TelemetryPacket*)pPck, NOT_IN_USE);
        return PUS_MODE_MAN_FULL;
    } else {
        DC_PUSTelemetryModeManager_loadPacket(This->pTmModeManager, pPck);
    }
    
    return ACTION_SUCCESS;
}

/**
 * Get the maximum size(in number of bytes) of the application data array. 
 * @see #setNumberOfRawData
 * @return the maximum size of the application data in number of bytes
 */
static unsigned int getNumberOfRawData(const void *obj)
{
    DC_PUSDefineDataReporting *This = DC_PUSDEFINEDATAREPORTING(obj);
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
static void setRawDataFastly(void *obj, unsigned char *d, unsigned int n)
{
    DC_PUSDefineDataReporting *This = DC_PUSDEFINEDATAREPORTING(obj);

    assert(This->data != pNULL);

    if (n>This->maxNumberData) {
        PUSTelecommand_setValidityCheckCode(obj, VC_TOO_MANY_RAW_DATA);
        return;
    } 

    This->numberData = n;
    for (unsigned int i=0; i<n; i++) {
        This->data[i] = d[i];
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
    DC_PUSDefineDataReporting *This = DC_PUSDEFINEDATAREPORTING(obj);
    return This->numberData;
}

/**
 * Perform a class-specific configuration check on the telecommand:
 * check that the maximum number of raw data has been set and that the
 * PUS telemetry mode manager has been loaded.
 * @return true if the telecommand is configured, false otherwise
 */
static bool isObjectConfigured(void *obj)
{
    PUSTelecommandClass *ptc = GET_CLASS(TYPE_PUSTELECOMMAND);
    DC_PUSDefineDataReporting *This = DC_PUSDEFINEDATAREPORTING(obj);

    return ((CC_ROOTOBJECT_CLASS(ptc)->isObjectConfigured(obj)) && 
            (This->data != pNULL) && 
            (This->pTmModeManager != pNULL));
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    DC_PUSDefineDataReporting *This = DC_PUSDEFINEDATAREPORTING(obj);
    This->data = pNULL;
    This->maxNumberData = 0;
    This->numberData = 0;

    TelecommandClass *tc = TELECOMMAND_GET_CLASS(obj);
    tc->setType(obj, PUS_TYPE_DATA_REP);

    CC_RootObject_setClassId((CC_RootObject*)obj, ID_PUSDEFINEDATAREPORTING);
}

DC_PUSDefineDataReporting* DC_PUSDefineDataReporting_new(void)
{
    Object *obj = object_new(TYPE_DC_PUSDEFINEDATAREPORTING);
    return (DC_PUSDefineDataReporting*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    DC_PUSDefineDataReportingClass *ddrc = DC_PUSDEFINEDATAREPORTING_CLASS(oc);
    ddrc->getNumberOfApplicationData = getNumberOfApplicationData;

    PunctualActionClass *pac = PUNCTUALACTION_CLASS(oc);
    pac->doAction = doAction;

    TelecommandClass *tc = TELECOMMAND_CLASS(oc);
    tc->setRawDataFastly = setRawDataFastly;
    tc->getNumberOfRawData = getNumberOfRawData;

    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_PUSDEFINEDATAREPORTING,
    .parent = TYPE_PUSTELECOMMAND,
    .instance_size = sizeof(DC_PUSDefineDataReporting),
    .abstract = false,
    .class_size = sizeof(DC_PUSDefineDataReportingClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_PUSDefineDataReporting_register(void)
{
    type_register_static(&type_info);
}
