//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyPUSTelemetryPacket.c
//
// Version	1.0
// Date		04.04.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/TestConstants.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "DC_DummyPUSTelemetryPacket.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_DummyPUSTelemetryPacket_setValue(DC_DummyPUSTelemetryPacket *This,
                                         unsigned char value)
{
    This->item = value;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * This method always returns 1. This telemetry packet only encapsulates
 * one single byte.
 * @return always return 1
 */
static unsigned int getNumberOfBytes(void *obj)
{
    return 1;
}

/**
 * Return the encapsulated byte. The value of the argument is ignored.
 * @return the value of the encapsulated byte
 * @param n this parameter is ignored
 */
static unsigned char getUnsignedByte(void *obj, unsigned int n)
{
    DC_DummyPUSTelemetryPacket *This = DC_DUMMYPUSTELEMETRYPACKET(obj);
	return This->item;
}

/**
 * Increment the value of the encapsulated byte by one. Wrap around to 0
 * when the value of 255 is reached.
 */
static void update(void *obj)
{
    DC_DummyPUSTelemetryPacket *This = DC_DUMMYPUSTELEMETRYPACKET(obj);

    if (This->item < 255) {
        This->item++;
    } else {
        This->item = 0;
    }
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    DC_DummyPUSTelemetryPacket *This = DC_DUMMYPUSTELEMETRYPACKET(obj);
    TelemetryPacketClass *tpc = TELEMETRYPACKET_GET_CLASS(obj);

    This->item = 0;
    tpc->setType(obj, TEST_TM_TYPE);
    tpc->setSubType(obj, TEST_TM_SUBTYPE);
    tpc->setTimeTag(obj, TEST_TM_TIMETAG);
    CC_RootObject_setClassId((CC_RootObject*)obj, ID_DUMMYPUSTELEMETRYPACKET);
}

DC_DummyPUSTelemetryPacket* DC_DummyPUSTelemetryPacket_new(void)
{
    return (DC_DummyPUSTelemetryPacket*)object_new(TYPE_DC_DUMMYPUSTELEMETRYPACKET);
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
}

static const TypeInfo type_info = {
    .name = TYPE_DC_DUMMYPUSTELEMETRYPACKET,
    .parent = TYPE_PUSTELEMETRYPACKET,
    .instance_size = sizeof(DC_DummyPUSTelemetryPacket),
    .abstract = false,
    .class_size = sizeof(DC_DummyPUSTelemetryPacketClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_DummyPUSTelemetryPacket_register(void)
{
    type_register_static(&type_info);
}
