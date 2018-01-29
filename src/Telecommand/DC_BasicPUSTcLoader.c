//
//
// DC_BasicPUSTcLoader.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "../Event/DC_EventRepository.h"
#include "CC_TelecommandFactory.h"
#include "CC_TelecommandManager.h"
#include "DC_BasicPUSTcLoader.h"
#include "DC_PUSControlDataReporting.h"
#include "DC_PUSDefineDataReporting.h"

#include <string.h>



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_BasicPUSTcLoader_setTcLoadAreaStart(DC_BasicPUSTcLoader *This,
                                            unsigned char *startAddress)
{
    assert(startAddress != pNULL);
    This->tcArea = startAddress;
}

void DC_BasicPUSTcLoader_setMaxTcLength(DC_BasicPUSTcLoader *This, 
                                        unsigned int maxTcLength)
{
    assert(maxTcLength > 6);
    This->maxTcDataPacketLength = maxTcLength - 6;
}

unsigned int DC_BasicPUSTcLoader_getMaxTcLength(const DC_BasicPUSTcLoader *This)
{
    return (This->maxTcDataPacketLength + 6);
}

void DC_BasicPUSTcLoader_setMaxNumberOfTc(DC_BasicPUSTcLoader *This,  
                                          unsigned int max)
{
    assert(max > 0);
    This->maxNumberOfTc = max;
}

unsigned int DC_BasicPUSTcLoader_getMaxNumberOfTc(const DC_BasicPUSTcLoader *This)
{
    return This->maxNumberOfTc;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Retrieve the raw telecommand packet data, create and configure a telecommand 
 * component for each telecommand packet, 
 * and load them in the telecommand manager.
 * The raw telecommand packet data are assumed to consist of an array of
 * bytes stored in the telecommand load area. Their layout is assumed to 
 * conform with the PUS telecommand packet layout.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *      pTcFct = ...    // retrieve telecommand factory
 *      for each tc packet in the tc load area {
 *          if(APID of TC telecommand does not match APID of this application)
 *              continue;
 *          tcType = ...    // read telecommand type from data in telecommand area
 *          tcSubType = ... // read telecommand subtype from data in telecommand area
 *          if(tcType=TYPE_1 and tcSubType=SUBTYPE_a) {
 *            ... // retrieve TC component of matching type and subtype from pTcFct
 *            ... // configure the TC component
 *            ... // load TC packet data into TC component
 *            getTelecommandManager(void)->load(...);  // load telecommand component
 *          }
 *          if(tcType=TYPE_2 and tcSubType=SUBTYPE_b) {
 *            ... // retrieve TC component of matching type and subtype from pTcFct
 *            ... // configure the TC component
 *            ... // load TC packet data into TC component
 *            getTelecommandManager(void)->load(...);  // load telecommand component
 *           }
 *           ...
 *       }    </PRE>
 * The loading of telecommand packet data into the TC component is done using
 * the <i>raw data load service</i>. Depending on the telecommand type, either the
 * fast or the safe version of the service is used.
 * The check on APID is performed by comparing the packet ID field in the telecommand packet
 * with the packet ID of the telecommand components as returned by method <code>getPacketId</code>.
 * If the two values do not match, it is assumed that the telecommand packet is intended for
 * some other application and it is simply ignored.
 * <p>
 * For simplicity, the pseudo-code above does not consider error cases.
 * Error cases result in the generation of an error report and in the
 * immediate return of the method.
 * The following error cases are handled: <ul>
 * <li> The number of telecommand packets in the telecommand load area is greater
 * than the maximum value set when the telecommand loader is configured
 * (event report EVT_TOO_MANY_TC_PCKT)</li>
 * <li> The telecommand factory does not return any telecommand component
 * (event report EVT_NO_TC_AVAIL)</li>
 * <li> The telecommand type has an unexpected type 
 * (event report EVT_UNKNOWN_TC_TYPE)</li>
 * <li> The telecommand length exceeds the maximum value set when the telecommand
 * loader is configured
 * (event report EVT_TC_TOO_LONG)</li>
 * </ul>
 * The current implementation can handle the following telecommands: <ul>
 * <li>PUS Test Telecommand(instance of class
 * <code>DC_TestPUSTelecommand</code>)</li>
 * <li>PUS Control Data Reporting Telecommand(instance of class
 * <code>DC_PUSControlDataReporting</code>)</li>
 * <li>PUS Define Data Reporting Telecommand(instance of class
 * <code>DC_PUSDefineDataReporting</code>)</li>
 * </ul>
 * In accordance with the PUS, this method assumes what follows:<ul>
 * <li>the packet ID is located at offset: (startAddress+0)</li>
 * <li>the packet sequence control is located at offset: (startAddress+2)</li>
 * <li>the telecommand type field is located in a telecommand packet at offset: (startAddress+7)</li>
 * <li>the acknowledge bits are located in the least significant four bits of the
 * byte at offset: (startAddress+6)</li>
 * <li>the telecommand subtype is located at offset: (startAddress+8)</li>
 * <li>the packet length field is assumed to be located at offset: (startAddress+4)</li>
 * <li>the packet source ID has a length of <code>sizeof(TD_TelecommandSource)</code></li>
 * <li>the packet error control field is assumed to be 2-byte wide but is ignored. Error checking
 * is assumed to have already been performed upstream</li>
 * </ul>
 */
static void activate(void *obj)
{
    DC_BasicPUSTcLoader *This = DC_BASICPUSTCLOADER(obj);

    assert(This->tcArea != pNULL);
    assert(This->maxTcDataPacketLength > 0);
    assert(This->maxNumberOfTc > 0);

    CC_TelecommandFactory *pFct = CC_TelecommandFactory_getInstance();
    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);

    unsigned char *startTcPacket = This->tcArea + 1;
    unsigned char numberOfTc = *(unsigned char*)This->tcArea;
    if (numberOfTc > This->maxNumberOfTc) {
        
        // dc_erc->create(dc_erc, (CC_RootObject*)This, EVT_TOO_MANY_TC_PCKT);
        dc_erc->create(dc_er, (CC_RootObject*)This, EVT_TOO_MANY_TC_PCKT);
        return;
    }

    for (unsigned char j=0; j<numberOfTc; j++) {

      assert(sizeof(TD_TelecommandType) == 1);
      assert(sizeof(TD_TelecommandSubType) == 1);

      unsigned short tcPacketID;
      unsigned short tcPacketSeqControl;
      unsigned short tcDataPacketLength;
      TD_TelecommandSource tcSource;

      memcpy(&tcPacketID, startTcPacket, 2);
      memcpy(&tcPacketSeqControl, startTcPacket+2, 2);
      memcpy(&tcDataPacketLength, startTcPacket+4, 2);
      unsigned char tcAcknowledge = *(startTcPacket+6);
      TD_TelecommandType tcType = *(TD_TelecommandType*)(startTcPacket+7);
      TD_TelecommandSubType tcSubType = *(TD_TelecommandType*)(startTcPacket+8);
      memcpy(&tcSource, startTcPacket+9, sizeof(TD_TelecommandSource));

      unsigned short appDataLength = tcDataPacketLength-5-sizeof(TD_TelecommandSource);
      unsigned char *applicationDataStart = (startTcPacket+9+sizeof(TD_TelecommandSource));
      bool fastRawDataLoad = false;

      if (tcPacketID != PUSTelecommand_getPacketId()) {
          startTcPacket = startTcPacket + tcDataPacketLength + 6;
          continue;
      }

      if (tcDataPacketLength > This->maxTcDataPacketLength) {
    
        dc_erc->create(dc_er, (CC_RootObject*)This, EVT_TC_TOO_LONG);
        return;
      }
    
      PUSTelecommand *pTC = pNULL;
      if ((tcType==PUS_TYPE_DATA_REP) && 
        ((tcSubType==PUS_ST_DATA_REP_NEW_HK)||(tcSubType==PUS_ST_DATA_REP_NEW_HK))) {
          pTC = (PUSTelecommand*)CC_TelecommandFactory_allocatePUSDefineDataReporting(pFct, 
                                                                             appDataLength);
       } else if ((tcType==PUS_TYPE_DATA_REP) && 
        ((tcSubType==PUS_ST_DATA_REP_ENB_HK)||(tcSubType==PUS_ST_DATA_REP_ENB_DG)||
         (tcSubType==PUS_ST_DATA_REP_DIS_HK)||(tcSubType==PUS_ST_DATA_REP_DIS_HK))){
          unsigned char nsid = applicationDataStart[0];
          pTC = (PUSTelecommand*)CC_TelecommandFactory_allocatePUSControlDataReporting(pFct, nsid);
          fastRawDataLoad = true;
       } else if (tcType == PUS_TYPE_TEST){
          pTC = (PUSTelecommand*)CC_TelecommandFactory_allocateTestPUSTelecommand(pFct);
       } else {
          dc_erc->create(dc_er, (CC_RootObject*)This, EVT_UNKNOWN_TC_TYPE);
          startTcPacket = startTcPacket + tcDataPacketLength + 6;
          continue;
       }

       if (pTC == pNULL) {
          dc_erc->create(dc_er, (CC_RootObject*)This, EVT_NO_TC_AVAIL);
          startTcPacket = startTcPacket + tcDataPacketLength + 6;
          continue;
       }

       TelecommandClass *tc = TELECOMMAND_GET_CLASS(pTC);

       tc->setTelecommandId(pTC, tcPacketSeqControl);
       tc->setType(pTC, tcType);
       tc->setSubType(pTC, tcSubType);
       tc->setSource(pTC, tcSource);
       tc->setAcknowledgeLevel(pTC, tcAcknowledge);

       if (fastRawDataLoad) {
          tc->setRawDataFastly(pTC, applicationDataStart, appDataLength);
       } else {
          for (unsigned int i=0; i<appDataLength; i++) {
              tc->setRawData(pTC, i, *(applicationDataStart+i));
          }
       }

       CC_TelecommandManager *cc_tm = TelecommandLoader_getTelecommandManager(obj);
       CC_TelecommandManagerClass *cc_tmc = CC_TELECOMMANDMANAGER_GET_CLASS(cc_tm);
       //cc_tmc->load(obj, (Telecommand*)pTC);
       cc_tmc->load(cc_tm, (Telecommand*)pTC);
       startTcPacket = startTcPacket + tcDataPacketLength + 6;
    }
}

/**
 * Change the status of the telecommand to "not in use".
 * A pseudo-code implementation for this method is as follows: <pre>
 *      pTelecommand->setInUse(NOT_IN_USE); </pre>
 * @param pTelecommand the telecommand whose resources must be released
 */
static void release(void *obj, Telecommand *pTelecommand)
{
    DC_BasicPUSTcLoader *This = DC_BASICPUSTCLOADER(obj);

    assert(This->tcArea != pNULL);
    assert(This->maxTcDataPacketLength > 0);
    assert(This->maxNumberOfTc > 0);
    assert(pTelecommand != pNULL);
    Telecommand_setInUse(pTelecommand, NOT_IN_USE);
}

/**
 * Perform a class-specific configuration check on the telecommand
 * loader: verify that the start address of the telecommand load area, 
 * the maximum length of the telecommand packet have been set, and
 * the maximum number of telecommand packets have been set.
 * @return true if the telecommand loader is configured, false otherwise.
 */
static bool isObjectConfigured(void *obj)
{
   TelecommandLoaderClass *tlc = GET_CLASS(TYPE_TELECOMMANDLOADER);
   DC_BasicPUSTcLoader *This = DC_BASICPUSTCLOADER(obj);

   // Check configuration of super object
   if (!CC_ROOTOBJECT_CLASS(tlc)->isObjectConfigured(obj) || 
       (This->tcArea == pNULL) || 
       (This->maxTcDataPacketLength == 0) ||
       (This->maxNumberOfTc == 0))
   {
       return NOT_CONFIGURED;

   }
   return CONFIGURED;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    DC_BasicPUSTcLoader *This = DC_BASICPUSTCLOADER(obj);
    This->tcArea = pNULL;
    This->maxTcDataPacketLength = 0;
    This->maxNumberOfTc = 0;

    CC_RootObject_setClassId((CC_RootObject*)obj, ID_BASICPUSTCLOADER);
}

DC_BasicPUSTcLoader* DC_BasicPUSTcLoader_new(void)
{
    Object *obj = object_new(TYPE_DC_BASICPUSTCLOADER);
    return (DC_BasicPUSTcLoader*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{

    TelecommandLoaderClass *tlc = TELECOMMANDLOADER_CLASS(oc);
    tlc->activate = activate;
    tlc->release = release;

    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_BASICPUSTCLOADER,
    .parent = TYPE_TELECOMMANDLOADER,
    .instance_size = sizeof(DC_BasicPUSTcLoader),
    .abstract = false,
    .class_size = sizeof(DC_BasicPUSTcLoaderClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_BasicPUSTcLoader_register(void)
{
    type_register_static(&type_info);
}
