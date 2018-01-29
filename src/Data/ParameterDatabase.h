//
//
// ParameterDatabase.h
//


#ifndef PARAMETERDATABASE_H
#define PARAMETERDATABASE_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "../Qom/object.h"


/*
 * Base class from which all parameter database classes are derived.
 * A parameter database object encapsulates a set of parameter values.
 * Each parameter can have two values: the <i>default value</i> and the
 * <i>current value</i>.
 * The default value is the value of the parameters immediately after the
 * database object is created or reset.
 * The current values are initialized with the default values at the time the
 * database object is created or
 * reset and they can subsequently be modified.
 * <p>
 * Parameters are identified by a <i>parameter identifier</i>.
 * Syntactically, this is a positive integer.
 * Each application instantiated from the framework would have its own set of
 * parameter identifiers.
 * <p>
 * In order to properly use the parameter database abstraction, it is
 * necessary to understand the conceptual implementation model that is
 * behind the interface defined in this class.
 * Parameter database information is stored in two tables: the <i>Default Table</i>
 * and the <i>Operational Table</i>. Each table stores a sequence of pairs.
 * The pairs have the form: (parameter value, parameter identifier).
 * Each entry in the table, in other words, contains the value of a parameter
 * and its identifier.
 * The two tables store values for the same set of parameters.
 * They differ only because the values stored in the default table are
 * intended to remain fixed whereas the values stored in the operational table
 * can be dynamically updated.
 * The operational table is initialized with a copy of the default table(this
 * is done using the <code>reset</code> operation).
 * <p>
 * In many implementations, the default table will be stored in ROM and the
 * operational table will be stored in RAM.
 * <p>
 * No methods are defined to set the default parameter values. This is because,
 * in most cases, these are defined outside the parameter database class
 * (they may, for instance, be burnt in PROM).
 * <p>
 * A parameter database is a low-level data structure whose implementation will
 * usually require use of pointers. Most implementations of this class
 * will therefore violate project specific coding rule PR3.1.
 * <p>
 * Client components can access the parameters in two ways. They can either
 * get their values using the getter methods defined in this interface. Or
 * they can <i>link</i> to the parameters using the <code>getParameterPointer</code>
 * method. This method returns a pointer to a specific parameter(as identified
 * by its identifier) which the client component can then store internally and
 * use to directly access the parameter value.
 * <p>
 * Parameters have a type.
 * The type of the parameter defines how the raw parameter value is
 * interpreted and how it is returned to the
 * external user of the database.
 * The possible types for the parameters are: unsigned int, int, unsigned short,
 * unsigned char, char, float, double.
 * For each paramete type, there is a dedicated parameter getter method.
 * Note that this interface does not mandate any protection against attempts to
 * access parameters with the wrong type.
 * Thus, for instance, if the parameter identified by identifier ID is
 * intended to represent an integer,
 * attempts to retrieve it as if it were of float type(using method
 * <CODE>getFloatParameter(ID)</CODE>) will not necessarily result
 * in an error and may produce a meaningless result.
 * Avoiding this type of errors is the responsibility of the user.
 * Subclasses, however, are free to introduce some run-time check to catch
 * this kind of error.
 * <p>
 * For similar reasons, the interface defined by this class does not mandate
 * any checks on the legality of the value of the parameter identifier in the
 * method calls. Such checks can again be added by subclasses.
 * <p>
 * The methods declared by this class allow an application component to
 * establish a link between their internal variables and the database parameters.
 * The process whereby this link is established is called <i>database linking</i>.
 * Two types of database linking are allowed by this class: <i>copy link</i>
 * and <i>pointer link</i>.
 * <p>
 * In a <i>copy link</i>, the application component holds a reference to
 * the parameter database and to the identifier of the target parameter
 * and periodically updates the value of its internal variable by copying
 * the value of the target database parameter.
 * <p>
 * In a <i>pointer link</i>, the application component internally defines
 * a pointer which is then initialized to point to the target database
 * parameter. The application component effectively uses the target database
 * parameter as its internal variable.
 * <p>
 * This is an abstract class because the internal organization of the
 * parameter database is application-dependent.
 * All the class methods are declared abstract.
 * In particular, the data structure used to represent the parameter tables
 * and the way parameters and their identifiers are associated is
 * application dependent.
 * <p>
 * @todo This class defines the setter and getter methods to be virtual. This
 * is expensive in CPU time. Given that database implementations will often
 * be generated automatically by XSL programs, and given that an application
 * would normally only have one database component, it may be wiser to 
 * have the XSL program generate an implementation for class ParameterDatabase that 
 * is defined to have only non-virtual methods. The problem with this approach
 * is that it is not possible to have multiple implementations of a database
 * in a single delivery and that therefore it is not possible to have several
 * database test cases in the same delivery(this could be alleviated by
 * generating the test case for the database as well as the database
 * implementation). 
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 * @ingroup Data
 */
#define TYPE_PARAMETERDATABASE "parameterdatabase"

void ParameterDatabase_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct ParameterDatabase {
    CC_RootObject parent;
};


struct ParameterDatabaseClass {
    CC_RootObjectClass parent_class;
 
    void (*reset)(void *obj);
    void (*setParameterUnsignedInt)(void *obj, TD_DatabaseId parId, unsigned int newValue);
    void (*setParameterInt)(void *obj, TD_DatabaseId parId, int newValue);
    void (*setParameterUnsignedShort)(void *obj, TD_DatabaseId parId, unsigned short newValue);
    void (*setParameterShort)(void *obj, TD_DatabaseId parId, short newValue);
    void (*setParameterBool)(void *obj, TD_DatabaseId parId, bool newValue);
    void (*setParameterChar)(void *obj, TD_DatabaseId parId, char newValue);
    void (*setParameterUnsignedChar)(void *obj, TD_DatabaseId parId, unsigned char newValue);
    void (*setParameterFloat)(void *obj, TD_DatabaseId parId, float newValue);
    void (*setParameterDouble)(void *obj, TD_DatabaseId parId, double newValue);
    unsigned int (*getParameterUnsignedInt)(void *obj, TD_DatabaseId parId);
    int (*getParameterInt)(void *obj, TD_DatabaseId parId);
    unsigned short (*getParameterUnsignedShort)(void *obj, TD_DatabaseId parId);
    short (*getParameterShort)(void *obj, TD_DatabaseId parId);
    bool (*getParameterBool)(void *obj, TD_DatabaseId parId);
    unsigned char (*getParameterUnsignedChar)(void *obj, TD_DatabaseId parId);
    char (*getParameterChar)(void *obj, TD_DatabaseId parId);
    float (*getParameterFloat)(void *obj, TD_DatabaseId parId);
    double (*getParameterDouble)(void *obj, TD_DatabaseId parId);
    unsigned int* (*getParameterPointerUnsignedInt)(void *obj, TD_DatabaseId parId);
    int* (*getParameterPointerInt)(void *obj, TD_DatabaseId parId);
    unsigned short* (*getParameterPointerUnsignedShort)(void *obj, TD_DatabaseId parId);
    short* (*getParameterPointerShort)(void *obj, TD_DatabaseId parId);
    unsigned char* (*getParameterPointerUnsignedChar)(void *obj, TD_DatabaseId parId);
    char* (*getParameterPointerChar)(void *obj, TD_DatabaseId parId);
    bool* (*getParameterPointerBool)(void *obj, TD_DatabaseId parId);
    float* (*getParameterPointerFloat)(void *obj, TD_DatabaseId parId);
    double* (*getParameterPointerDouble)(void *obj, TD_DatabaseId parId);
};


#define PARAMETERDATABASE_GET_CLASS(obj) \
        OBJECT_GET_CLASS(ParameterDatabaseClass, obj, TYPE_PARAMETERDATABASE)

#define PARAMETERDATABASE_CLASS(klass) \
        OBJECT_CLASS_CHECK(ParameterDatabaseClass, klass, TYPE_PARAMETERDATABASE)

#define PARAMETERDATABASE(obj) \
        OBJECT_CHECK(ParameterDatabase, obj, TYPE_PARAMETERDATABASE)


ParameterDatabase* ParameterDatabase_new(void);

#endif
