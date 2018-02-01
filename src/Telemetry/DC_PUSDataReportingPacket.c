//
//
// DC_PUSDataReportingPacket.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../Base/CC_RootObject.h"
#include "../Data/DataPool.h"
#include "../Event/DC_EventRepository.h"
#include "../System/ObsClock.h"
#include "../Telemetry/DC_PUSDataReportingPacket.h"

#include <string.h>



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

TD_DataPoolId DC_PUSDataReportingPacket_getParameterId
(
    DC_PUSDataReportingPacket *This, 
    unsigned int faIndex, 
    unsigned int parPos
)
{
    assert(faIndex <= This->FAcounter);
    assert(parPos < This->F[faIndex].npar);

    TD_DataPoolId temp;
    void *src = (This->defBuffer + This->F[faIndex].ind + parPos*sizeof(TD_DataPoolId));
    memcpy(&temp, src, sizeof(TD_DataPoolId));

    return temp;
}

void DC_PUSDataReportingPacket_setEnabled
(
    DC_PUSDataReportingPacket *This,
    bool enabledStatus
)
{
    This->enabled = enabledStatus;
}

bool DC_PUSDataReportingPacket_isEnabled(const DC_PUSDataReportingPacket *This)
{
    return This->enabled;
}

TD_PUSCollectionInterval DC_PUSDataReportingPacket_getCollectionInterval
(
    DC_PUSDataReportingPacket *This
)
{
    assert(This->defBuffer != pNULL);

    TD_PUSCollectionInterval temp;
    void *src = This->defBuffer + This->indCollectionInterval;
    memcpy(&temp, src, sizeof(TD_PUSCollectionInterval));

    return temp;
}

TD_PUSNumberOfParameters DC_PUSDataReportingPacket_getNPAR1
(
    DC_PUSDataReportingPacket *This
)
{
    assert(This->defBuffer != pNULL);

    TD_PUSNumberOfParameters temp;
    void *src = This->defBuffer + This->indNPAR1;
    memcpy(&temp, src, sizeof(TD_PUSNumberOfParameters));

    return temp;
}

unsigned char DC_PUSDataReportingPacket_getNFA(DC_PUSDataReportingPacket *This)
{
    assert(This->defBuffer != pNULL);
    return *(unsigned char*)(This->defBuffer + This->indNFA);
}

TD_SID DC_PUSDataReportingPacket_getSID(DC_PUSDataReportingPacket *This)
{
    assert(This->defBuffer != pNULL);

    TD_SID temp;
    void *src = This->defBuffer + This->indSID;
    memcpy(&temp, src, sizeof(TD_SID));
    return temp;
}

void DC_PUSDataReportingPacket_setDefinitionBuffer
(
    DC_PUSDataReportingPacket *This, 
    unsigned int i, 
    unsigned char val
)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(This);
    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
    DataPool *dp = CC_RootObject_getDataPool();
    DataPoolClass *dpc = DATAPOOL_GET_CLASS(dp);

    assert(cc_roc->isObjectConfigured(This));
    assert(i < This->defBufferSize);

    if ((i >= This->defBufferSize) || (This->FAcounter >= This->faDescSize)) {
        dc_erc->create(dc_er, (CC_RootObject*)This, EVT_ILLEGAL_PUS_REP_PACKET);
        return;
    }

    This->defBuffer[i] = val;
    This->defBufferCounter = i;

    if (i < (This->indNPAR1 + sizeof(TD_PUSNumberOfParameters)-1)) return;

    // In order to access F concisely below.
    FaDescType* const F = This->F;
    if (i == (This->indNPAR1 + sizeof(TD_PUSNumberOfParameters)-1)) { 
        // process the NPAR1 field
        F[0].npar = DC_PUSDataReportingPacket_getNPAR1(This);
        F[0].nrep = 1;
        F[0].counter = DC_PUSDataReportingPacket_getCollectionInterval(This);
        F[0].rep = 0;
        F[0].ind = i+1;
        F[0].size = 0;
        F[0].val = 0;
        This->FAcounter = 0;
        return;
    }

    assert(i > (This->indNPAR1 + sizeof(TD_PUSNumberOfParameters)-1));
    assert(i >= F[0].ind);

    unsigned int j = i - F[0].ind; // j=0 when the first byte of the first par is processed
    if (j < DC_PUSDataReportingPacket_getNPAR1(This)*sizeof(TD_DataPoolId)) {
        if (((j+1)%sizeof(TD_DataPoolId)) == 0) {

            // process the j-th parameter that is sampled only once per collection interval
            TD_DataPoolId id;
            void *src = This->defBuffer + i - sizeof(TD_DataPoolId) + 1;
            memcpy(&id, src, sizeof(TD_DataPoolId));

            if (dpc->isFloat(dp, id)) {
                F[0].size += sizeof(TD_Float);
            } else {
                F[0].size += sizeof(TD_Integer);
            }
        }
        return;
    }

    if (i == (F[0].ind+F[0].npar*sizeof(TD_DataPoolId))) {
        This->indNFA = i;
        return;
    }

    assert(i > This->indNFA);

    
    if (i == (This->indNFA+1)) {
        This->FAcounter = 1;
        F[1].val = F[0].val + F[0].size*F[0].nrep;
        F[1].ind = i + 1 + sizeof(TD_PUSNumberOfParameters);
    } else if (i == (F[This->FAcounter].ind+F[This->FAcounter].npar*sizeof(TD_DataPoolId))) {
        This->FAcounter++;        // process the FAcounter-th FA
        assert(This->FAcounter < This->faDescSize);
        if (This->FAcounter >= This->faDescSize) {
            dc_erc->create(dc_er, (CC_RootObject*)This, EVT_ILLEGAL_PUS_REP_PACKET);
            return;
        }

        unsigned int FAcounter = This->FAcounter;   
        F[FAcounter].val = F[FAcounter-1].val + F[FAcounter-1].size*F[FAcounter-1].nrep;
        F[FAcounter].ind = i + 1 + sizeof(TD_PUSNumberOfParameters);
    }

    // In order to acess FAcounter concisely below.
    const unsigned int FAcounter = This->FAcounter;   

    assert(FAcounter > 0);

     // this is the NREP field of the FA
    if (i == (F[FAcounter].ind-1-sizeof(TD_PUSNumberOfParameters))) { 
        F[FAcounter].nrep = val;
        F[FAcounter].rep = 0;
        F[FAcounter].counter = DC_PUSDataReportingPacket_getCollectionInterval(This)/val;
        F[FAcounter].size = 0;
        return;
    }

    if (i < (F[FAcounter].ind-1)) {
        return;
    }

    if (i == (F[FAcounter].ind-1)) {   // this is end of the NPAR2 field of the FA
        void *src = This->defBuffer + i - sizeof(TD_PUSNumberOfParameters) + 1;
        memcpy(&F[FAcounter].npar, src, sizeof(TD_PUSNumberOfParameters));
        return;
    }

    j = i - F[FAcounter].ind;     // j=0 when the first byte of the first par in the FA is processed
    if (j < F[FAcounter].npar*sizeof(TD_DataPoolId)) {
        if (((j+1)%sizeof(TD_DataPoolId)) == 0) {

            // process the j-th parameter of the FAcounter-th fixed-length array
            TD_DataPoolId id;
            void *src = This->defBuffer + i - sizeof(TD_DataPoolId) + 1; 
            memcpy(&id, src, sizeof(TD_DataPoolId));

            if (dpc->isFloat(dp, id)) {
                F[FAcounter].size += sizeof(TD_Float);
            } else {
                F[FAcounter].size += sizeof(TD_Integer);
           }
        }
        return;
    }

    assert(false);
}

unsigned char DC_PUSDataReportingPacket_getDefinitionBuffer
(
    DC_PUSDataReportingPacket *This,
    unsigned int i
)
{
    assert(i < This->defBufferCounter);
    return This->defBuffer[i];
}

unsigned int DC_PUSDataReportingPacket_getDefinitionBufferLength
(
    DC_PUSDataReportingPacket *This
)
{
    assert(This->defBuffer != pNULL);
    return (This->defBufferCounter + 1);
}

void DC_PUSDataReportingPacket_reset(DC_PUSDataReportingPacket *This)
{
    // In order to access F concisely below.
    FaDescType* const F = This->F;

    assert(F != pNULL);

    for (unsigned int i=0; i<This->faDescSize; i++) {
        if (F[i].nrep != 0) {
             F[i].counter = DC_PUSDataReportingPacket_getCollectionInterval(This)/F[i].nrep;
             F[i].rep = 0;
        }
    }

    DC_PUSDataReportingPacket_setEnabled(This, DISABLED);
}

void DC_PUSDataReportingPacket_setDefinitionBufferSize
(
    DC_PUSDataReportingPacket *This, 
    unsigned int defBufferSize
)
{
    assert(defBufferSize > 0);
    assert(This->defBuffer == pNULL);     // should only be called once

    This->defBufferSize = defBufferSize ;
    This->defBuffer = g_malloc(sizeof(unsigned char)*defBufferSize);
    for (unsigned short i=0; i<defBufferSize; i++) {
        This->defBuffer[i] = 0;
    }
}

unsigned int DC_PUSDataReportingPacket_getDefinitionBufferSize
(
    DC_PUSDataReportingPacket *This
)
{
    return This->defBufferSize;
}

void DC_PUSDataReportingPacket_setMaxNumberFA
(
    DC_PUSDataReportingPacket *This, 
    unsigned int n
)
{
    assert(This->F == pNULL);     // should only be called once

    // recall F[0] is used to store information about parameters sampled once per collection interval
    This->faDescSize = (unsigned char)(n + 1);
    This->F = g_malloc(sizeof(FaDescType)*This->faDescSize);
    
    // In order to access F concisely below.
    FaDescType* const F = This->F;
    for (unsigned char i=0; i<This->faDescSize; i++) {
        F[i].counter = 0;
        F[i].ind = 0;
        F[i].npar = 0;
        F[i].nrep = 0;
        F[i].rep = 0;
        F[i].size = 0;
        F[i].val = 0;
    }
}

unsigned int DC_PUSDataReportingPacket_getMaxNumberFA
(
    DC_PUSDataReportingPacket *This
)
{
    assert(This->faDescSize > 0);
    return (This->faDescSize - 1);
}

void DC_PUSDataReportingPacket_setValueBufferSize
(
    DC_PUSDataReportingPacket *This,
    unsigned int valBufferSize
)
{
    assert(valBufferSize > 0);
    assert(This->valBuffer == pNULL);     // should only be called once

    This->valBufferSize = valBufferSize;
    This->valBuffer = g_malloc(sizeof(unsigned char)*valBufferSize);
    for (unsigned int i=0; i<valBufferSize; i++) {
        This->valBuffer[i] = 0;
    }
}

unsigned int DC_PUSDataReportingPacket_getValueBufferSize
(
    DC_PUSDataReportingPacket *This
)
{
    return This->valBufferSize;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Implement the data update service. This class maintains a <i>main counter</i> and a
 * a set of <i>FA counters</i>, one for each fixed-length array. After a reset(call
 * to method <code>reset</code>). The main counter is initialized to the value of the
 * collection interval. The FA counters are initialized to the value of the
 * repetition count of their fixed-length array.
 * If the component is enabled, then every time this method is called, the counters are
 * decremented by one. When an FA counter reaches the value of zero, the following
 * actions are performed: <ul>
 * <li>The values of the parameters in the fixed-length array are acquired from the
 * system database and are stored in the parameter buffer</li>
 * <li>The FA counter is reset to its initial value</li>
 * </ul>
 * When the main counter reaches zero, then all the parameter values are acquired.
 * In all cases, the time attribute of the telemetry packet is set to the current
 * time.
 */
static void update(void *obj)
{
    ObsClock *clock = PUSTelemetryPacket_getObsClock();
    ObsClockClass *occ = OBSCLOCK_GET_CLASS(clock);

    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    TelemetryPacketClass *tpc = TELEMETRYPACKET_GET_CLASS(obj);
    DC_PUSDataReportingPacket *This = DC_PUSDATAREPORTINGPACKET(obj);

    assert(cc_roc->isObjectConfigured(obj));
    assert((tpc->getSubType(obj) == PUS_ST_DATA_REP_PAR_HK_REP) ||
           (tpc->getSubType(obj) == PUS_ST_DATA_REP_PAR_DG_REP));

    if (!DC_PUSDataReportingPacket_isEnabled(obj)) return;

    tpc->setTimeTag(obj, occ->getTime(clock));

    // Copy SID in the first locations of the packet value buffer
    for (unsigned int i=0; i<sizeof(TD_SID); i++) {
        This->valBuffer[i] = This->defBuffer[i];
    }

    // Write mode field into packet value buffer
    // use of dummy avoids compiler warning due to PUS_DATA_REP_MODE being a constant
    bool dummy = PUS_DATA_REP_MODE;   
    if (dummy) This->valBuffer[sizeof(TD_SID)] = 0;

    // Compute initial offset in the packet value buffer (the first parameter value
    // is written at location valBufferInitialOffset)
    unsigned short valBufferInitialOffset = sizeof(TD_SID) + 
                                            (PUS_DATA_REP_MODE ? 1 : 0);

    // In order to acces F concisely below.
    FaDescType* const F = This->F;

    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
    DataPool *dp = CC_RootObject_getDataPool();
    DataPoolClass *dpc = DATAPOOL_GET_CLASS(dp);

    for (unsigned short i=0; i<=This->FAcounter; i++) {

        if (F[i].counter == 0) {
            F[i].counter = DC_PUSDataReportingPacket_getCollectionInterval(This)/F[i].nrep;
        }

        F[i].counter--;

        if (F[i].counter == 0) {
            unsigned int pos = valBufferInitialOffset + F[i].val + F[i].rep*F[i].size;

            // check if next frame fits in value buffer
            if ((pos+(F[i].rep+1)*F[i].size) >= This->valBufferSize) {
                dc_erc->create(dc_er, (CC_RootObject*)This, EVT_PUS_DATA_REP_PACKET_TOO_LARGE);
                break;
            }
            for (unsigned char j=0; j<F[i].npar; j++) {
                TD_DataPoolId id = DC_PUSDataReportingPacket_getParameterId(This, i, j);
                if (dpc->isFloat(dp, id)) {
                    TD_Float flTemp = dpc->getFloatValue(dp, id);
                    memcpy(This->valBuffer+pos, &flTemp, sizeof(TD_Float));
                    assert(pos<This->valBufferSize);
                    pos += sizeof(TD_Float);
                } else {
                    TD_Integer intTemp = dpc->getIntegerValue(dp, id);
                    memcpy(This->valBuffer+pos, &intTemp, sizeof(TD_Integer));
                    assert(pos<This->valBufferSize);
                    pos += sizeof(TD_Integer);
                }
            }

            F[i].rep++;

            if (F[i].rep == F[i].nrep) F[i].rep = 0;
        }
    }
}

/**
 * Return the number of bytes that this data reporting packet will provide at
 * the next call of the data acquisition service.
 * If this method is called at a time other than the end of a collection interval, 
 * then its return value is zero. The end of a collection interval is detected by
 * looking at the value of the main counter defined in method <code>update</code>.
 * At the end of a collection interval, this counter has value zero. A return
 * value of zero for this method indicates that the data reporting packet is not
 * providing any data for the telemetry stream. A PUS data reporting packet
 * is only intended to provide telemetry data at the end of its collection interval.
 * <p>
 * If this method is called at the end of a collection interval(i.e. at a time
 * when the main counter defined in method <code>updatey</code> is equal to zero), then
 * its return value is equal to the number of bytes in the data reporting packet. This
 * is computed as follows: <pre>
 *      n1 = sizeof(TD_SID);
 *      if(PUS_DATA_REP_MODE)
 *          n2 = 1;
 *      else
 *          n2 = 0;
 *      n3 = 0;
 *      for(all parameters p in the packet)
 *          if(p is of type TD_Float)
 *              n3 += (repetition count of p) * sizeof(TD_Float);
 *          else
 *              n3 += (repetition count of p) * sizeof(TD_Integer);
 *      return(n1+n2+n3); </pre>
 * The "repetition count" of a parameter is 1 for parameters that are collected only
 * once per cycle and it is as specified by the relevant fixed-length array for over-sampled
 * parameters.
 * <p>
 * If the packet is disabled, then this method returns zero to signify that a disabled
 * packet should not provide any telemetry data.
 * @see #update
 * @return the number of bytes in this data reporting packet at the end of
 * a collection interval or zero at other times
 */
static unsigned int getNumberOfBytes(void *obj)
{
    DC_PUSDataReportingPacket *This = DC_PUSDATAREPORTINGPACKET(obj);
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    TelemetryPacketClass *tpc = TELEMETRYPACKET_GET_CLASS(obj);

    assert(cc_roc->isObjectConfigured(obj));
    assert((tpc->getSubType(obj) == PUS_ST_DATA_REP_PAR_HK_REP) ||
           (tpc->getSubType(obj) == PUS_ST_DATA_REP_PAR_HK_REP));

    if (!DC_PUSDataReportingPacket_isEnabled(obj)) return 0;

    if (This->F[0].counter != 0) return 0;

    return ((sizeof(TD_SID)) + 
            (PUS_DATA_REP_MODE ? 1 : 0) +
            (This->F[This->FAcounter].val) +
            (This->F[This->FAcounter].size*This->F[This->FAcounter].nrep));
}

/**
 * Return the n-th byte of this data reporting packet. The image of this packet is stored
 * in the packet value buffer. This method therefore simply returns the value of the n-th element 
 * of the packet value buffer. 
 * Note that this method is independent of whether or not the packet is enabled.
 * @param n the byte to be returned
 */
static unsigned char getUnsignedByte(void *obj, unsigned int n)
{
    DC_PUSDataReportingPacket *This = DC_PUSDATAREPORTINGPACKET(obj);
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    TelemetryPacketClass *tpc = TELEMETRYPACKET_GET_CLASS(obj);

    assert(cc_roc->isObjectConfigured(obj));
    assert((tpc->getSubType(obj) == PUS_ST_DATA_REP_PAR_HK_REP) ||
           (tpc->getSubType(obj) == PUS_ST_DATA_REP_PAR_HK_REP));
    assert(n < This->valBufferSize);

    return This->valBuffer[n];
}

/**
 * Return a pointer to start address of the packet value buffer. 
 * This method implements the fast version of the data acquisition service.
 * This may be useful(if potentially unsafe) in the case of large packets.
 * @return the start address of the packet value buffer
 */
static unsigned char* getStartAddress(void *obj)
{
    DC_PUSDataReportingPacket *This = DC_PUSDATAREPORTINGPACKET(obj);

    assert(This->valBuffer != pNULL);
    return This->valBuffer;
}

/**
 * Return <code>true</code> to signify that the fast version of the data acquisition
 * service is implemented. 
 * @see #getStartAddress
 * @return this method always returns <code>true</code> 
 */
static bool isFastAcquisitionImplemented(void *obj)
{
    return true;
}

/**
 * Perform a class-specific configuration check on the telemetry packet:
 * verify that: <ul>
 * <li>The maximum size of the packet definition buffer has a legal value</li>
 * <li>The maximum size of the packet value buffer has a legal value</li>
 * <li>The maximum number of fixed-length arrays has a legal value</li>
 * </ul>
 * @return true if the component is configured, false otherwise.
 */
static bool isObjectConfigured(void *obj)
{
    PUSTelemetryPacketClass *pustpc = GET_CLASS(TYPE_PUSTELEMETRYPACKET);
    DC_PUSDataReportingPacket *This = DC_PUSDATAREPORTINGPACKET(obj);

    return ((CC_ROOTOBJECT_CLASS(pustpc)->isObjectConfigured(obj)) && 
            (This->F != pNULL) &&
            (This->valBuffer != pNULL) && 
            (This->defBuffer != pNULL));
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    DC_PUSDataReportingPacket *This = DC_PUSDATAREPORTINGPACKET(obj);
    This->enabled = false;
    This->defBuffer = pNULL;
    This->defBufferSize = 0;
    This->defBufferCounter = 0;
    This->valBuffer = pNULL;
    This->valBufferSize = 0;
    This->indSID = 0;
    This->indCollectionInterval = sizeof(TD_SID);
    This->indNPAR1 = This->indCollectionInterval + sizeof(TD_PUSCollectionInterval);
    This->indNFA = 0;
    This->F = pNULL;
    This->faDescSize = 0;
    This->FAcounter = 0;

    TelemetryPacketClass *tpc = TELEMETRYPACKET_GET_CLASS(obj);
    tpc->setType(obj, PUS_TYPE_DATA_REP);

    CC_RootObject_setClassId((CC_RootObject*)obj, ID_PUSDATAREPORTINGPACKET);
}

DC_PUSDataReportingPacket* DC_PUSDataReportingPacket_new(void)
{
    return (DC_PUSDataReportingPacket*)object_new(TYPE_DC_PUSDATAREPORTINGPACKET);
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    TelemetryPacketClass *tpc = TELEMETRYPACKET_CLASS(oc);
    tpc->update = update;
    tpc->getNumberOfBytes = getNumberOfBytes;
    tpc->getUnsignedByte = getUnsignedByte;
    tpc->getStartAddress = getStartAddress;
    tpc->isFastAcquisitionImplemented = isFastAcquisitionImplemented;

    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_PUSDATAREPORTINGPACKET,
    .parent = TYPE_PUSTELEMETRYPACKET,
    .instance_size = sizeof(DC_PUSDataReportingPacket),
    .abstract = false,
    .class_size = sizeof(DC_PUSDataReportingPacketClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_PUSDataReportingPacket_register(void)
{
    type_register_static(&type_info);
}
