//
//
// DC_DataItem16TmWord.h
//


#ifndef DC_DATAITEM16TMWORD_H
#define DC_DATAITEM16TMWORD_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Data/DC_RawDataItem.h"
#include "StructuredTelemetryPacket.h"
#include "../Qom/object.h"


/*
 * Telemetry item encapsulating a 16-bit integer accessed through a
 * raw data item. The raw data item is loaded as a configuration parameter.
 * @see DC_RawDataItem
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_DATAITEM16TMWORD "dc_dataitem16tmword"

void DC_DataItem16TmWord_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_DataItem16TmWord {
    StructuredTelemetryPacket parent;

    DC_RawDataItem *pDataItem;
};


struct DC_DataItem16TmWordClass {
    StructuredTelemetryPacketClass parent_class;
};


#define DC_DATAITEM16TMWORD_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_DataItem16TmWordClass, obj, TYPE_DC_DATAITEM16TMWORD)

#define DC_DATAITEM16TMWORD_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_DataItem16TmWordClass, klass, TYPE_DC_DATAITEM16TMWORD)

#define DC_DATAITEM16TMWORD(obj) \
        OBJECT_CHECK(DC_DataItem16TmWord, obj, TYPE_DC_DATAITEM16TMWORD)


DC_DataItem16TmWord* DC_DataItem16TmWord_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Load the data item that is the source of the telemetry data for this
 * telemetry packet.
 * The data item is assumed to encapsulate a 16-bit value.
 * @param pDataItem the data item acting as source of telemetry data
 */
void DC_DataItem16TmWord_setDataItem
(
    DC_DataItem16TmWord *This, 
    DC_RawDataItem *pDataItem
);


#endif
