//
//
// DC_DummyTelemetryPacket.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "DC_DummyTelemetryPacket.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_DummyTelemetryPacket_setValidStatus(DC_DummyTelemetryPacket *This, 
                                            bool validStatus)
{
	This->validStatus = validStatus;
}

void DC_DummyTelemetryPacket_setValue(DC_DummyTelemetryPacket *This, 
                                      unsigned int n, 
                                      unsigned char value)
{
    assert((This->item!=pNULL) && (n<This->nOfBytes));
    This->item[n] = value;
}

void DC_DummyTelemetryPacket_setNumberOfBytes(DC_DummyTelemetryPacket *This, 
                                              unsigned int nOfBytes)
{
    assert(This->item==pNULL);
    This->nOfBytes = nOfBytes;
    This->item = g_malloc(sizeof(unsigned char)*nOfBytes);
    for (unsigned int i=0; i<This->nOfBytes; i++) {
        This->item[i] = 0;
    }
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * This method always returns the number of telemetry bytes.
 * @return the number of telemetry bytes
 */
static unsigned int getNumberOfBytes(void *obj)
{
    DC_DummyTelemetryPacket *This = DC_DUMMYTELEMETRYPACKET(obj);
    return This->nOfBytes;
}

/**
 * Return the n-th encapsulated byte.
 * @return the value of the n-th encapsulated byte
 * @param n the byte index
 */
static unsigned char getUnsignedByte(void *obj, unsigned int n)
{
    DC_DummyTelemetryPacket *This = DC_DUMMYTELEMETRYPACKET(obj);

    assert((This->item!=pNULL) && (n<This->nOfBytes));
	return This->item[n];
}

/**
 * Increment the value of each encapsulated byte by one. Wrap around to 0
 * when the value of 255 is reached.
 */
static void update(void *obj)
{
    DC_DummyTelemetryPacket *This = DC_DUMMYTELEMETRYPACKET(obj);

    assert(This->item != pNULL);

    for (unsigned int i=0; i<This->nOfBytes; i++) {
        if (This->item[i] < 255) {
            This->item[i]++;
        } else {
            This->item[i] = 0;
        }
    }
}

/**
 * Return the validity status set with method <code>setValidStatus</code>.
 * @see #setValidStatus
 * @return the validity status
 */
static bool isValid(void *obj)
{
    DC_DummyTelemetryPacket *This = DC_DUMMYTELEMETRYPACKET(obj);
	return This->validStatus;
}

/**
 * Perform a class-specific configuration check on the component:
 * verify that the number of encapsulated bytes has been set.
 * @return true if the component is configured, false otherwise.
 */
static bool isObjectConfigured(void *obj)
{
    TelemetryPacketClass *tpc = GET_CLASS(TYPE_TELEMETRYPACKET);
    DC_DummyTelemetryPacket *This = DC_DUMMYTELEMETRYPACKET(obj);

    return (CC_ROOTOBJECT_CLASS(tpc)->isObjectConfigured(obj) && 
            (This->item != pNULL));
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    DC_DummyTelemetryPacket *This = DC_DUMMYTELEMETRYPACKET(obj);
    This->item = pNULL;
    This->nOfBytes = 0;
    This->validStatus = VALID;

    // Dummy calls to setter methods
    TelemetryPacketClass *tpc = TELEMETRYPACKET_GET_CLASS(obj);
    tpc->setDestination(obj, (TD_TelemetryDestination)1);
    tpc->setTimeTag(obj, (TD_ObsTime)1);
    tpc->setType(obj, (TD_TelemetryType)1);
    tpc->setSubType(obj, (TD_TelemetrySubType)1);

    CC_RootObject_setClassId((CC_RootObject*)obj, ID_DUMMYTELEMETRYITEM);
}

DC_DummyTelemetryPacket* DC_DummyTelemetryPacket_new(void)
{
    return (DC_DummyTelemetryPacket*)object_new(TYPE_DC_DUMMYTELEMETRYPACKET);
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    TelemetryPacketClass *tpc = TELEMETRYPACKET_CLASS(oc);
    tpc->getNumberOfBytes = getNumberOfBytes;
    tpc->getUnsignedByte = getUnsignedByte;
    tpc->update = update;
    tpc->isValid = isValid;


    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_DUMMYTELEMETRYPACKET,
    .parent = TYPE_TELEMETRYPACKET,
    .instance_size = sizeof(DC_DummyTelemetryPacket),
    .abstract = false,
    .class_size = sizeof(DC_DummyTelemetryPacketClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_DummyTelemetryPacket_register(void)
{
    type_register_static(&type_info);
}
