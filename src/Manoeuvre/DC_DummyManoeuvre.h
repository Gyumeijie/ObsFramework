//
//
// DC_DummyManoeuvre.h
//


#ifndef DC_DUMMYMANOEUVRE_H
#define DC_DUMMYMANOEUVRE_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "Manoeuvre.h"
#include "../Qom/object.h"


/*
 * Dummy implementation of the <code>Manoeuvre</code> abstract class 
 * to be used for testing purposes.
 * This class provides dummy implementation for the abstract methods
 * declared by its base class. It does not implement any behaviour 
 * beyond that which it inherits from its base class.
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_DUMMYMANOEUVRE "dc_dummymanoeuvre"

void DC_DummyManoeuvre_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_DummyManoeuvre {
    Manoeuvre parent;
};


struct DC_DummyManoeuvreClass {
    ManoeuvreClass parent_class;
};


#define DC_DUMMYMANOEUVRE_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_DummyManoeuvreClass, obj, TYPE_DC_DUMMYMANOEUVRE)

#define DC_DUMMYMANOEUVRE_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_DummyManoeuvreClass, klass, TYPE_DC_DUMMYMANOEUVRE)

#define DC_DUMMYMANOEUVRE(obj) \
        OBJECT_CHECK(DC_DummyManoeuvre, obj, TYPE_DC_DUMMYMANOEUVRE)


DC_DummyManoeuvre* DC_DummyManoeuvre_new(void);

#endif
