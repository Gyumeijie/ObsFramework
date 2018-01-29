//
//
// DC_PUSClearDataReporting.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "DC_PUSClearDataReporting.h"
#include "../Telemetry/CC_TelemetryPacketFactory.h"
#include "../Telemetry/CC_TelemetryManager.h"
#include "../Telemetry/DC_PUSTelemetryModeManager.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_PUSClearDataReporting_setMaxNumberSID
(
    DC_PUSClearDataReporting *This, 
    unsigned char max
)
{
    assert(max > 0);
    assert(This->maxNsid == 0);   // can only be called once

    This->maxNsid = max;
    This->sid = g_malloc(sizeof(TD_SID)*max);
    This->sidOverlay = (unsigned char*)This->sid;
    for (unsigned int i=0; i<max; i++) {
        This->sid[i] = 0;
    }
}

void DC_PUSClearDataReporting_setPUSTelemetryModeManager
(
    DC_PUSClearDataReporting *This, 
    DC_PUSTelemetryModeManager *pTmModeManager
)
{
    assert(pTmModeManager != pNULL);
    This->pTmModeManager = pTmModeManager;
}

DC_PUSTelemetryModeManager* DC_PUSClearDataReporting_getPUSTelemetryModeManager
(
    const DC_PUSClearDataReporting *This
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
 * Clear the data reporting packets. A data reporting packet is cleared
 * by setting its "in use" status to "packet not in use" and by unloading it
 * from the PUS telemetry mode manager(if it is loaded). This deactivates
 * the telemetry packet and allows the telemetry packet factory to reclaim it and make it
 * available to other clients.
 * A pseudo-code implementation for this method is as follows:<pre>
 *      for(all SIDs stored in the telecommand) {
 *          retrieve data reporting packet from telemetry packet factory;
 *          if(no packet is returned by the factory)
 *              outcome=FAIL;
 *          set status of packet to "not in use"
 *          if(packet is loaded in PUS telemetry mode manager)
 *              unload packet from PUS telemetry mode manager
 *      }
 *      if(outcome==FAIL)
 *          return ACTION_FAILURE;
 *      else
 *          return ACTION_SUCCESS; </pre>
 * The telecommand is configured with a list of SIDs. The data reporting
 * packets are retrieved from the telemetry packet factory(instance of class
 * <code>CC_TelemetryPacketFactory</code>) using their SID. 
 * The "in use" status of the packets is controlled through their
 * <code>setInUse</code> method.
 * @see TelemetryPacket#setInUse
 * @see CC_TelemetryPacketFactory
 * @see DC_PUSTelemetryModeManager
 * @see PunctualAction#execute
 * @return always returns a "telecommand successfully executed" code
 */
static TD_ActionOutcome doAction(void *obj)
{
    DC_PUSClearDataReporting *This = DC_PUSCLEARDATAREPORTING(obj);
    TelecommandClass *tc = TELECOMMAND_GET_CLASS(obj);

    assert((tc->getSubType(obj) == PUS_ST_DATA_REP_CLR_HK) ||
           (tc->getSubType(obj) == PUS_ST_DATA_REP_CLR_DG));

    CC_TelemetryPacketFactory *pFct = CC_TelemetryPacketFactory_getInstance();
    TD_ActionOutcome outcome = ACTION_SUCCESS;

    DC_PUSDataReportingPacket *pPck = pNULL; 
    TD_SID* const sid = This->sid;
    DC_PUSTelemetryModeManager* const pTmModeManager = This->pTmModeManager;
    for (unsigned int i=0; i<This->nsid; i++) {
        pPck = CC_TelemetryPacketFactory_getPUSDataReportingPacket(pFct, sid[i]);
        if (pPck == pNULL) {
            outcome = ACTION_FAILURE;
        } else  {
            TelemetryPacket_setInUse((TelemetryPacket*)pPck, NOT_IN_USE);
        }

        if (DC_PUSTelemetryModeManager_isSIDLoaded(pTmModeManager, sid[i])) {
            DC_PUSTelemetryModeManager_unloadPacket(pTmModeManager, sid[i]);
        }
    }
    
    return outcome;
}

/**
 * Implementation of the raw data load service. This method would normally
 * be called by a telecommand loader to load the application data into the
 * the telecommand component. This method interprets the raw data as they are
 * loaded and uses them to construct the sequence of SIDs of the data reporting
 * packets that have to be cleared. This method assumes that the
 * raw data are loaded in sequence starting from the first one(i.e. the value 
 * of i in the first call is zero and succesive calls use values of i that 
 * are incremented by one at each call). The value of i is also constrained to 
 * lie in the range [0, N] where N is computed as follows: <pre>
 *      N = M*sizeof(TD_SID)  </pre>
 * where M is the maximum number of SIDs defined by method <code>setMaxNumberSID</code>.
 * If the number of SIDs in the telecommand packet exceeds the maximum defined
 * with method <code>setMaxNumberSID</code>, the telecommand
 * is declared to be invalid with validity check code equal to VC_TOO_MANY_SIDS. 
 * If an attempt is made to load a greater number of raw data, the telecommand
 * is declared to be invalid with validity check code equal to VC_TOO_MANY_RAW_DATA. 
 * Finally, the total number of loaded raw data T
 * must be consistent with the number of SIDs(the first byte in the telecommand
 * packet). If this
 * is not the case, then the telecommand is declared invalid with validity check code
 * equal to VC_INCONSISTENT_RAW_DATA.
 * @see #getNumberOfRawData
 * @param i the index of the raw telecommand data
 * @param d the raw data
 */
static void setRawData(void *obj, unsigned int i, unsigned char d)
{
    DC_PUSClearDataReporting *This = DC_PUSCLEARDATAREPORTING(obj);
    TelecommandClass *tc = TELECOMMAND_GET_CLASS(obj);

    assert(i <= This->maxNsid*sizeof(TD_SID));
    // check that i argument increments by 1 in each call
    assert((i == 0) || (i == (This->lasti+1)));

    This->lasti = i;
    if (i == 0) {
        PUSTelecommand_setValidityCheckCode(obj, VC_INCONSISTENT_RAW_DATA);
        This->nsid = d;
        if (This->nsid > This->maxNsid)
           PUSTelecommand_setValidityCheckCode(obj, VC_TOO_MANY_SIDS);
        return;
    }

    if ((i < This->nsid*sizeof(TD_SID)) && 
        (tc->getValidityCheckCode(obj) == VC_INCONSISTENT_RAW_DATA)) {
        This->sidOverlay[i-1] = d;
        return;
    }

    if ((i == This->nsid*sizeof(TD_SID)) && 
        (tc->getValidityCheckCode(obj) == VC_INCONSISTENT_RAW_DATA)) {
        PUSTelecommand_setValidityCheckCode(obj, 0);
        This->sidOverlay[i-1] = d;
        return;
    }

    if (i >= (This->maxNsid*sizeof(TD_SID)+1)) {
        PUSTelecommand_setValidityCheckCode(obj, VC_TOO_MANY_RAW_DATA);
        return;
    }
}

/**
 * Return the number of raw data bytes that can be loaded with the
 * raw telecommand data load service.
 * The value returned by this class is equal to: <code>M*sizeof(TD_SID)+1</code>
 * where M is the maximum number of SIDs defined by method <code>setMaxNumberSID</code>.
 * @see #setRawData
 * @return the number of raw data bytes to be loaded with the raw
 * data load service
 */
static unsigned int getNumberOfRawData(const void *obj)
{
    DC_PUSClearDataReporting *This = DC_PUSCLEARDATAREPORTING(obj);
    return This->maxNsid*sizeof(TD_SID) + 1;
}

/**
 * Perform a class-specific configuration check on the telecommand:
 * check that the maximum number of SIDs that can be processed by the telecommand 
 * has been set and that the telemetry manager and telemetry mode manager
 * have been loaded.
 * @return true if the telecommand is configured, false otherwise
 */
static bool isObjectConfigured(void *obj)
{
    PUSTelecommandClass *ptc = GET_CLASS(TYPE_PUSTELECOMMAND);
    DC_PUSClearDataReporting *This = DC_PUSCLEARDATAREPORTING(obj);
 
    return ((CC_ROOTOBJECT_CLASS(ptc)->isObjectConfigured(obj)) && 
            (This->maxNsid != 0) && 
            (This->pTmModeManager != pNULL));
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
   DC_PUSClearDataReporting *This = DC_PUSCLEARDATAREPORTING(obj);
   This->sid = pNULL;
   This->sidOverlay = pNULL;
   This->nsid = 0;
   This->maxNsid = 0;
   This->lasti = 0;
   This->pTmModeManager = pNULL;

   TelecommandClass *tc = TELECOMMAND_GET_CLASS(obj);
   tc->setType(obj, PUS_TYPE_DATA_REP);

   CC_RootObject_setClassId((CC_RootObject*)obj, ID_PUSCLEARDATAREPORTING);
}

DC_PUSClearDataReporting* DC_PUSClearDataReporting_new(void)
{
    Object *obj = object_new(TYPE_DC_PUSCLEARDATAREPORTING);
    return (DC_PUSClearDataReporting*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    PunctualActionClass *pac = PUNCTUALACTION_CLASS(oc);
    pac->doAction = doAction;

    TelecommandClass *tc = TELECOMMAND_CLASS(oc);
    tc->setRawData = setRawData;
    tc->getNumberOfRawData = getNumberOfRawData;

    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_PUSCLEARDATAREPORTING,
    .parent = TYPE_PUSTELECOMMAND,
    .instance_size = sizeof(DC_PUSClearDataReporting),
    .abstract = false,
    .class_size = sizeof(DC_PUSClearDataReportingClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_PUSClearDataReporting_register(void)
{
    type_register_static(&type_info);
}
