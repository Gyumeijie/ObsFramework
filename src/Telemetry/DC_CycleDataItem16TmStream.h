//
//
// DC_CycleDataItem16TmStream.h
//
//
// Change Record:


#ifndef DC_CYCLEDATAITEM16TMSTREAM_H
#define DC_CYCLEDATAITEM16TMSTREAM_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Data/DC_RawDataItem.h"
#include "TelemetryStream.h"
#include "../Qom/object.h"


/*
 * Telemetry stream that writes the content of a telemetry packet to
 * a set of 16-bit words encapsulated in data items.
 * The data items will normally encapsulate hardware
 * registers representing the telemetry interface. The data items
 * are implemented as instances of class <code>DC_RawDataItem</code>.
 * <p>
 * This class maintains a <i>write counter</i>. The write counter has
 * a value between 0 and N-1 where N is the number of data items
 * managed by the telemetry stream. The counter is reset to 0 by
 * a call to operation <code>reset</code> or <code>flush</code>.
 * It is incremented by 1 every time a new 16-bit word is written to
 * a data item. When the write counter reaches the value of N, no
 * further items can be written and write requests remain without
 * effect until a <code>reset</code> or <code>flush</code> is performed.
 * <p>
 * The number of data items is a user-defined parameter. It must be set
 * as part of the component configuration.
 * @see DC_RawDataItem
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_CYCLEDATAITEM16TMSTREAM "dc_cycledataitem16tmstream"

void DC_CycleDataItem16TmStream_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_CycleDataItem16TmStream {
    TelemetryStream parent;

    DC_RawDataItem **pDataItem;       // array of pointers to DC_RawDataItem
    unsigned int nDataItems;          // number of data items
    unsigned int writeCounter;
};


struct DC_CycleDataItem16TmStreamClass {
    TelemetryStreamClass parent_class;
};


#define DC_CYCLEDATAITEM16TMSTREAM_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_CycleDataItem16TmStreamClass, \
                                          obj, TYPE_DC_CYCLEDATAITEM16TMSTREAM)

#define DC_CYCLEDATAITEM16TMSTREAM_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_CycleDataItem16TmStreamClass, \
                                        klass, TYPE_DC_CYCLEDATAITEM16TMSTREAM)

#define DC_CYCLEDATAITEM16TMSTREAM(obj) \
        OBJECT_CHECK(DC_CycleDataItem16TmStream, \
                                          obj, TYPE_DC_CYCLEDATAITEM16TMSTREAM)


DC_CycleDataItem16TmStream* DC_CycleDataItem16TmStream_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the number of data items managed by this telemetry stream.
 * This method causes the memory for the data structure holding the
 * data items to be allocated. After the successful allocation of the
 * memory, the telemetry stream is reset.
 * <p>
 * This is an initialization method. It should be called before the
 * telemetry stream is used the first time and it should not be called more
 * than once.
 * The number of data items should be greater than 0.
 * @see #getSize
 * @param n the number of data items
 */
void DC_CycleDataItem16TmStream_setNumberOfDataItems
(
    DC_CycleDataItem16TmStream *This,
    unsigned int n
);

/**
 * Set the n-th data item.
 * The data item are the locations to which the bytes written from the
 * telemetry packet are written.
 * The index n must lie in the interval [0, N-1] where N is the number of data
 * items managed by this telemetry DC_CycleDataItem16TmStream_stream(the return value of method
 * <code>getSize</code>). Use of an out-of-range index has no effect.
 * @see #setNumberOfDataItems
 * @param n the index of the data item to be set
 * @param pDataItem the data item to be associated to the index-th location
 * of the telemetry stream
 */
void DC_CycleDataItem16TmStream_setDataItem
(
    DC_CycleDataItem16TmStream *This, 
    unsigned int n, 
    DC_RawDataItem *pDataItem
);


#endif
