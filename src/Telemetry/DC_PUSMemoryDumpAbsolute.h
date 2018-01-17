//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_PUSMemoryDumpAbsolute.h
//
// Version	1.0
// Date		01.03.04
// Author	A. Pasetti(P&P Software)


#ifndef DC_PUSMEMORYDUMPABSOLUTE_H
#define DC_PUSMEMORYDUMPABSOLUTE_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Telemetry/PUSMemoryDump.h"
#include "../Qom/object.h"


/*
 * PUS telemetry packet implementing the memory dump service using absolute addresses 
 * (type 6, subtype 6).
 * This class adds to its superclass the 
 * implementation of the <i>data update service</i>.
 * @todo construct a test case for this class.
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_PUSMEMORYDUMPABSOLUTE "dc_pusmemorydumpabsolute"

void DC_PUSMemoryDumpAbsolute_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_PUSMemoryDumpAbsolute {
    PUSMemoryDump parent;
};


struct DC_PUSMemoryDumpAbsoluteClass {
    PUSMemoryDumpClass parent_class;
};


#define DC_PUSMEMORYDUMPABSOLUTE_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_PUSMemoryDumpAbsoluteClass, obj, TYPE_DC_PUSMEMORYDUMPABSOLUTE)

#define DC_PUSMEMORYDUMPABSOLUTE_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_PUSMemoryDumpAbsoluteClass, klass, TYPE_DC_PUSMEMORYDUMPABSOLUTE)

#define DC_PUSMEMORYDUMPABSOLUTE(obj) \
        OBJECT_CHECK(DC_PUSMemoryDumpAbsolute, obj, TYPE_DC_PUSMEMORYDUMPABSOLUTE)


DC_PUSMemoryDumpAbsolute* DC_PUSMemoryDumpAbsolute_new(void);

#endif
