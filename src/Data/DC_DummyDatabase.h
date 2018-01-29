//
//
// DC_DummyDatabase.h
//


#ifndef DC_DUMMYDATABASE_H
#define DC_DUMMYDATABASE_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "DC_BasicDatabase.h"
#include "../Qom/object.h"


/*
 * Default component implementing a dummy parameter database.
 * A <i>dummy parameter database</i> is a parameter database with a length of
 * of one byte and with default and operational tables that coincide.
 * It is useful for testing purposes as a placeholder for a component of type
 * <code>ParameterDatabase</code>.
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_DUMMYDATABASE "dc_dummydatabase"

void DC_DummyDatabase_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_DummyDatabase {
    DC_BasicDatabase parent;

    char table;
};


struct DC_DummyDatabaseClass {
    DC_BasicDatabaseClass parent_class;
};


#define DC_DUMMYDATABASE_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_DummyDatabaseClass, obj, TYPE_DC_DUMMYDATABASE)

#define DC_DUMMYDATABASE_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_DummyDatabaseClass, klass, TYPE_DC_DUMMYDATABASE)

#define DC_DUMMYDATABASE(obj) \
        OBJECT_CHECK(DC_DummyDatabase, obj, TYPE_DC_DUMMYDATABASE)


DC_DummyDatabase* DC_DummyDatabase_new(void);

#endif
