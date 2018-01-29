//
//
// PUSTelemetryPacket.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../System/ObsClock.h"
#include "TelemetryPacket.h"
#include "PUSTelemetryPacket.h"




///////////////////////////////////////////////////////////////////////////////
//
//                            class data
//
///////////////////////////////////////////////////////////////////////////////

static TD_TelemetryDestination defaultDestination = 0;

static TD_PUSPacketId packetId = 0;

static ObsClock *pObsClock = pNULL;



///////////////////////////////////////////////////////////////////////////////
//
//                            class  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void PUSTelemetryPacket_setApplicationId(TD_APID apid)
{
    assert(apid < (TD_APID)2048);
    packetId = 2048;
    packetId = packetId + apid;
}

TD_PUSPacketId PUSTelemetryPacket_getPacketId(void)
{
    return packetId;
}

TD_TelemetryDestination PUSTelemetryPacket_getDefaultDestination(void)
{
    return defaultDestination;
}

void PUSTelemetryPacket_setDefaultDestination(TD_TelemetryDestination defDest)
{
    assert(defDest > 0);
    defaultDestination = defDest;
}

void PUSTelemetryPacket_setObsClock(ObsClock* pClock)
{
   assert (pClock != pNULL);
   pObsClock = pClock;
}

ObsClock* PUSTelemetryPacket_getObsClock(void)
{
   assert (pObsClock != pNULL);
   return pObsClock;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Setter method for the telemetry packet type.
 * @param tmType the telemetry packet type
 */
static void setType(void *obj, TD_TelemetryType type)
{
    PUSTelemetryPacket *This = PUSTELEMETRYPACKET(obj);
    
    assert(type > 0);
    This->type = type;
}

/**
 * Setter method for the telemetry packet sub-type.
 * @param tmSubType the telemetry packet sub-type
 */
static void setSubType(void *obj, TD_TelemetrySubType subType)
{
    PUSTelemetryPacket *This = PUSTELEMETRYPACKET(obj);

    assert(subType > 0);
    This->subType = subType;
}

/**
 * Setter method for the telemetry packet destination.
 * @param tmDest telemetry packet destination
 */
static void setDestination(void *obj, TD_TelemetryDestination dest)
{
    PUSTelemetryPacket *This = PUSTELEMETRYPACKET(obj);

    assert(dest > 0);
    This->dest = dest;
}

/**
 * Getter method for the telemetry type.
 * @return the telemetry sub-type
 */
static TD_TelemetryType getType(const void *obj)
{
    PUSTelemetryPacket *This = PUSTELEMETRYPACKET(obj);
    
    assert(This->type > 0);
    return This->type;
}

/**
 * Getter method for the telemetry sub-type.
 * @return the telemetry sub-type
 */
static TD_TelemetrySubType getSubType(const void *obj)
{
    PUSTelemetryPacket *This = PUSTELEMETRYPACKET(obj);

    assert(This->subType > 0);
    return This->subType;
}

/**
 * Getter method for the telemetry packet time tag.
 * @return the telemetry packet time
 */
static TD_ObsTime getTimeTag(const void *obj)
{
    PUSTelemetryPacket *This = PUSTELEMETRYPACKET(obj);

    assert(This->timeTag >= 0);
    return This->timeTag;
}

/**
 * Setter method for the telemetry packet time tag.
 * @param timeTag the telemetry packet time tag
 */
static void setTimeTag(void *obj, TD_ObsTime timeTag)
{
    PUSTelemetryPacket *This = PUSTELEMETRYPACKET(obj);

    assert(timeTag >= 0);
    This->timeTag = timeTag;
}

/**
 * Getter method for the telemetry packet destination.
 * @return the telemetry packet destination
 */
static TD_TelemetryDestination getDestination(const void *obj)
{
    PUSTelemetryPacket *This = PUSTELEMETRYPACKET(obj);

    assert(This->dest > 0);
    return This->dest;
}

/**
 * Perform a class-specific configuration check on the telemetry packet:
 * verify that the type, the
 * sub type, the destination, the time tag, and the packet identifier have a legal value.
 * @return true if the component is configured, false otherwise.
 */
static bool isObjectConfigured(void *obj)
{
   TelemetryPacketClass *tpc = GET_CLASS(TYPE_TELEMETRYPACKET);
   PUSTelemetryPacket *This = PUSTELEMETRYPACKET(obj);

   return ((CC_ROOTOBJECT_CLASS(tpc)->isObjectConfigured(obj)) &&
           (This->type > 0) &&
           (This->subType > 0) &&
           (This->dest > 0) &&
           (This->timeTag >= 0) &&
           (packetId > 0) &&
           (pObsClock != pNULL));
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    PUSTelemetryPacket *This = PUSTELEMETRYPACKET(obj);

    This->type = 0;
    This->subType = 0;
    This->timeTag = -1;
    This->dest = defaultDestination;
}

PUSTelemetryPacket* PUSTelemetryPacket_new(void)
{
    Object *obj = object_new(TYPE_PUSTELEMETRYPACKET);
    return (PUSTelemetryPacket*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    TelemetryPacketClass *tpc = TELEMETRYPACKET_CLASS(oc);
    tpc->setType = setType;
    tpc->setSubType = setSubType;
    tpc->setDestination = setDestination;
    tpc->getType = getType;
    tpc->getSubType = getSubType;
    tpc->getTimeTag = getTimeTag;
    tpc->setTimeTag = setTimeTag;
    tpc->getDestination = getDestination;

    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_PUSTELEMETRYPACKET,
    .parent = TYPE_TELEMETRYPACKET,
    .instance_size = sizeof(PUSTelemetryPacket),
    .abstract = false,
    .class_size = sizeof(PUSTelemetryPacketClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void PUSTelemetryPacket_register(void)
{
    type_register_static(&type_info);
}
