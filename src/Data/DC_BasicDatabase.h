//
//
// DC_BasicDatabase.h
//


#ifndef DC_BASICDATABASE_H
#define DC_BASICDATABASE_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "ParameterDatabase.h"
#include "../Qom/object.h"


/*
 * Default component implementing a basic parameter database.
 * The basic database implements the <i>Default Table</i> and the
 * <i>Operational Table</i> as linear arrays. The identifier of a parameter
 * is the index in the array at which the parameter is stored.
 * Syntactically, the elements of the table arrays are of char type but the
 * tables can hold elements of any type(the getter and setter operations defined
 * in this class will perform the necessary casting operations to convert
 * the raw bytes in the table arrays to the type required by the operation).
 * <p>
 * The default and operational tables are <i>not</i> defined by this class.
 * This class loads the tables using methods <code>setDefaultTable</code>
 * and <code>setOperationalTable</code>.
 * <p>
 * The configuration procedure for an instance of this class is as follows: <ol>
 * <li>Load the default table(method <code>setDefaultTable</code>)  </li>
 * <li>Load the operational table(method <code>setOperationalTable</code>)  </li>
 * <li>Set the length of the table(method <code>setTableLength</code>)  </li>
 * <li>Reset the component instance(method <code>reset</code>)  </li>
 * </ol>
 * This class is designed for efficiency. It does not perform any
 * legality checks on the access to the database. It therefore assumes that
 * the client components is using correct parameter identifiers.
 * <p>
 * The getter and setter methods are implemented to be fast and efficient but this
 * makes them vulnerable to alignement problems on some processors. For instance,
 * the setter methods for integer-valued parameters is implemened as follows:<code>
 * void DC_BasicDatabase::setParameter(TD_DatabaseId parId, int newValue) {
 *  *( (int*)(pOperationalTable+parId) ) = newValue;
 * }</code>
 * On some processors, the assignment will fail if location <code>(pOperationalTable+parId)</code> does not
 * correspond to a longword(4 bytes) boundary. There is no check to ensure that this
 * is the case and it is the responsibility of the user to ensure that the setter
 * method is called with the correct parameter values. The same applies to other
 * setter and getter methods. A more robust(but possibly slower) implementation
 * might use the <code>memcpy</code> library function to transfer the values of the
 * data between the database locations and the method variables.
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_BASICDATABASE "dc_basicdatabase"

void DC_BasicDatabase_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_BasicDatabase {
    ParameterDatabase parent;

    char *pDefaultTable;          // array of chars
    char *pOperationalTable;      // array of chars
    bool resetWasCalled;
    TD_DatabaseId tableLength;   // table length in bytes
};


struct DC_BasicDatabaseClass {
    ParameterDatabaseClass parent_class;
};


#define DC_BASICDATABASE_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_BasicDatabaseClass, obj, TYPE_DC_BASICDATABASE)

#define DC_BASICDATABASE_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_BasicDatabaseClass, klass, TYPE_DC_BASICDATABASE)

#define DC_BASICDATABASE(obj) \
        OBJECT_CHECK(DC_BasicDatabase, obj, TYPE_DC_BASICDATABASE)


DC_BasicDatabase* DC_BasicDatabase_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the length of the default and operational table in number of
 * bytes. Only non-negative values of the length are legal.
 * <p>
 * This is an initialization method.
 * @param length the number of char elements in the default and in the
 * operational table
 */
void DC_BasicDatabase_setTableLength(DC_BasicDatabase *This, TD_DatabaseId length);

/**
 * Get the length of the default and operational table in number of
 * bytes.
 * @see #setTableLength
 * @return the number of char elements in the default and in the
 * operational table
 */
TD_DatabaseId DC_BasicDatabase_getTableLength(DC_BasicDatabase *This);

/**
 * Load the default table. This method assumes that the default table has
 * been defined and initialized by the caller. The method does not perform
 * any action on the table. It simply loads its address and will use it
 * for accessing the table entries.
 * <p>
 * This is an initialization method.
 * @param pDefTable the starting address of the default table
 */
void DC_BasicDatabase_setDefaultTable(DC_BasicDatabase *This, char *pDefTable);

/**
 * Load the operational table. This method assumes that the operational table has
 * been defined and initialized by the caller. The method does not perform
 * any action on the table. It simply loads its address and will use it
 * for accessing the table entries.
 * <p>
 * This is an initialization method.
 * @param pOperTable the starting address of the default table
 */
void DC_BasicDatabase_setOperationalTable(DC_BasicDatabase *This, char *pOperTable);


#endif
