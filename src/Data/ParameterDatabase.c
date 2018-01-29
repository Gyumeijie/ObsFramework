//
//
// ParameterDatabase.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "ParameterDatabase.h"



///////////////////////////////////////////////////////////////////////////////
//
//                    pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Load the current values of the parameters with their default values.
 */
static void reset(void *obj)
{
    // this is automate genenrated by converter
}

/**
 * Set the current value of a parameter interpreted as an unsigned integer.
 * @param parId the identifier of the parameter to be set
 * @param newValue the new current value of the parameter
 */
static void setParameterUnsignedInt
(
    void *obj, 
    TD_DatabaseId parId, 
    unsigned int newValue
)
{
    // this is automate genenrated by converter
}

/**
 * Set the current value of a parameter interpreted as an integer.
 * @param parId the identifier of the parameter to be set
 * @param newValue the new current value of the parameter
 */
static void setParameterInt(void *obj, TD_DatabaseId parId, int newValue)
{
    // this is automate genenrated by converter
}

/**
 * Set the current value of a parameter interpreted as an unsigned short.
 * @param parId the identifier of the parameter to be set
 * @param newValue the new current value of the parameter
 */
static void setParameterUnsignedShort
(
    void *obj, 
    TD_DatabaseId parId, 
    unsigned short newValue
)
{
    // this is automate genenrated by converter
}

/**
 * Set the current value of a parameter interpreted as an short.
 * @param parId the identifier of the parameter to be set
 * @param newValue the new current value of the parameter
 */
static void setParameterShort(void *obj, TD_DatabaseId parId, short newValue)
{
    // this is automate genenrated by converter
}

/**
 * Set the current value of a parameter interpreted as a boolean.
 * @param parId the identifier of the parameter to be set
 * @param newValue the new current value of the parameter
 */
static void setParameterBool(void *obj, TD_DatabaseId parId, bool newValue)
{
    // this is automate genenrated by converter
}

/**
 * Set the current value of a parameter interpreted as a char.
 * @param parId the identifier of the parameter to be set
 * @param newValue the new current value of the parameter
 */
static void setParameterChar(void *obj, TD_DatabaseId parId, char newValue)
{
    // this is automate genenrated by converter
}

/**
 * Set the current value of a parameter interpreted as an unsigned char.
 * @param parId the identifier of the parameter to be set
 * @param newValue the new current value of the parameter
 */
static void setParameterUnsignedChar
(
    void *obj, 
    TD_DatabaseId parId, 
    unsigned char newValue
)
{
    // this is automate genenrated by converter
}

/**
 * Set the current value of a parameter interpreted as a float.
 * @param parId the identifier of the parameter to be set
 * @param newValue the new current value of the parameter
 */
static void setParameterFloat(void *obj, TD_DatabaseId parId, float newValue)
{
    // this is automate genenrated by converter
}

/**
 * Set the current value of a parameter interpreted as a double.
 * @param parId the identifier of the parameter to be set
 * @param newValue the new current value of the parameter
 */
static void setParameterDouble(void *obj, TD_DatabaseId parId, double newValue)
{
    // this is automate genenrated by converter
}

/**
 * Get the current value of a parameter interpreted as an unsigned integer.
 * @param parId the identifier of the parameter to be set
 * @return the current value of the parameter
 */
static unsigned int getParameterUnsignedInt(void *obj, TD_DatabaseId parId)
{
    // this is automate genenrated by converter
}

/**
 * Get the current value of a parameter interpreted as an integer.
 * @param parId the identifier of the parameter to be set
 * @return the current value of the parameter
 */
static int getParameterInt(void *obj, TD_DatabaseId parId)
{
    // this is automate genenrated by converter
}

/**
 * Get the current value of a parameter interpreted as an unsigned short.
 * @param parId the identifier of the parameter to be set
 * @return the current value of the parameter
 */
static unsigned short getParameterUnsignedShort(void *obj, TD_DatabaseId parId)
{
    // this is automate genenrated by converter
}

/**
 * Get the current value of a parameter interpreted as a short.
 * @param parId the identifier of the parameter to be set
 * @return the current value of the parameter
 */
static short getParameterShort(void *obj, TD_DatabaseId parId)
{
    // this is automate genenrated by converter
}

/**
 * Get the current value of a parameter interpreted as a boolean.
 * @param parId the identifier of the parameter to be set
 * @return the current value of the parameter
 */
static bool getParameterBool(void *obj, TD_DatabaseId parId)
{
    // this is automate genenrated by converter
}

/**
 * Get the current value of a parameter interpreted as an unsigned char.
 * @param parId the identifier of the parameter to be set
 * @return the current value of the parameter
 */
static unsigned char getParameterUnsignedChar(void *obj, TD_DatabaseId parId)
{
    // this is automate genenrated by converter
}

/**
 * Get the current value of a parameter interpreted as a char.
 * @param parId the identifier of the parameter to be set
 * @return the current value of the parameter
 */
static char getParameterChar(void *obj, TD_DatabaseId parId)
{
    // this is automate genenrated by converter
}

/**
 * Get the current value of a parameter interpreted as a float.
 * @param parId the identifier of the parameter to be set
 * @return the current value of the parameter
 */
static float getParameterFloat(void *obj, TD_DatabaseId parId)
{
    // this is automate genenrated by converter
}

/**
 * Get the current value of a parameter interpreted as a double.
 * @param parId the identifier of the parameter to be set
 * @return the current value of the parameter
 */
static double getParameterDouble(void *obj, TD_DatabaseId parId)
{
    // this is automate genenrated by converter
}

/**
 * Return the pointer to the variable in the operational table storing the
 * parameter identified by <code>parId</code>. The variable is interpreted
 * as of type <code>unsigned int</code>.
 * <p>
 * This and other methods returing pointers to parameters are typically
 * used to set up a <i>pointer link</i> between a
 * target database parameter and the internal variable of an application
 * component. This can be done as follows. Consider an application component
 * instantiated from class <code>Comp</code> which defines an internal
 * variable <code>var</code>. Suppose that it is desired to link this
 * variable to the parameter characterized by identifier <code>PAR_ID</code>
 * in the database <code>pDatabase</code>. The <code>Comp</code> class
 * should expose a <i>database linker method</i>:<PRE>
 *      class Comp {
 *          unsigned int* par;
 *          . . .
 *          void linkParToDatabase(TD_DatabaseId parId, ParameterDatabase* pDB) {
 *              par = pDB->getParameterPointerUnsignedInt(parId);
 *          }
 *          . . .  </PRE>
 * The application component must then be configured as follows:<PRE>
 *      Comp* comp;                 // the application component
 *      ParameterDatabase* pDB;     // the parameter database
 *      TD_DatabaseId PAR_ID;       // the parameter identifier
 *      . . .
 *      comp->linkParToDatabase(PAR_ID, pDB); </PRE>
 * The last statement sets up a permanent link between the internal
 * application component variable and the database parameter.
 * Note that use of this mechanism entails a violation of coding
 * rule PR3.1. This is inevitable if the database linking is to be
 * performed in an efficient manner.
 * @return the parameter pointer
 * @param parId the parameter identifier
 */
static unsigned int* getParameterPointerUnsignedInt
(
    void *obj, 
    TD_DatabaseId parId
)
{
    // this is automate genenrated by converter
}

/**
 * Return the pointer to the variable in the operational table storing the
 * parameter identified by <code>parId</code>. The variable is interpreted
 * as of type <code>int</code>.
 * @see #getParameterPointerUnsignedInt
 * @return the parameter pointer
 * @param parId the parameter identifier
 */
static int* getParameterPointerInt(void *obj, TD_DatabaseId parId)
{
    // this is automate genenrated by converter
}

/**
 * Return the pointer to the variable in the operational table storing the
 * parameter identified by <code>parId</code>. The variable is interpreted
 * as of type <code>unsigned short</code>.
 * @see #getParameterPointerUnsignedInt
 * @return the parameter pointer
 * @param parId the parameter identifier
 */
static unsigned short* getParameterPointerUnsignedShort
(
    void *obj,
    TD_DatabaseId parId
)
{
    // this is automate genenrated by converter
}

/**
 * Return the pointer to the variable in the operational table storing the
 * parameter identified by <code>parId</code>. The variable is interpreted
 * as of type <code>short</code>.
 * @see #getParameterPointerUnsignedInt
 * @return the parameter pointer
 * @param parId the parameter identifier
 */
static short* getParameterPointerShort(void *obj, TD_DatabaseId parId)
{
    // this is automate genenrated by converter
}

/**
 * Return the pointer to the variable in the operational table storing the
 * parameter identified by <code>parId</code>. The variable is interpreted
 * as of type <code>unsigned char</code>.
 * @see #getParameterPointerUnsignedInt
 * @return the parameter pointer
 * @param parId the parameter identifier
 */
static unsigned char* getParameterPointerUnsignedChar
(
    void *obj,
    TD_DatabaseId parId
)
{
    // this is automate genenrated by converter
}

/**
 * Return the pointer to the variable in the operational table storing the
 * parameter identified by <code>parId</code>. The variable is interpreted
 * as of type <code>char</code>.
 * @see #getParameterPointerUnsignedInt
 * @return the parameter pointer
 * @param parId the parameter identifier
 */
static char* getParameterPointerChar(void *obj, TD_DatabaseId parId)
{
    // this is automate genenrated by converter
}

/**
 * Return the pointer to the variable in the operational table storing the
 * parameter identified by <code>parId</code>. The variable is interpreted
 * as of type <code>bool</code>.
 * @see #getParameterPointerUnsignedInt
 * @return the parameter pointer
 * @param parId the parameter identifier
 */
static bool* getParameterPointerBool(void *obj, TD_DatabaseId parId)
{
    // this is automate genenrated by converter
}

/**
 * Return the pointer to the variable in the operational table storing the
 * parameter identified by <code>parId</code>. The variable is interpreted
 * as of type <code>float</code>.
 * @see #getParameterPointerUnsignedInt
 * @return the parameter pointer
 * @param parId the parameter identifier
 */
static float* getParameterPointerFloat(void *obj, TD_DatabaseId parId)
{
    // this is automate genenrated by converter
}

/**
 * Return the pointer to the variable in the operational table storing the
 * parameter identified by <code>parId</code>. The variable is interpreted
 * as of type <code>double</code>.
 * @see #getParameterPointerUnsignedInt
 * @return the parameter pointer
 * @param parId the parameter identifier
 */
static double* getParameterPointerDouble(void *obj, TD_DatabaseId parId)
{
    // this is automate genenrated by converter
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj){}

ParameterDatabase* ParameterDatabase_new(void)
{
    Object *obj = object_new(TYPE_PARAMETERDATABASE);
    return (ParameterDatabase*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    ParameterDatabaseClass *pdc = PARAMETERDATABASE_CLASS(oc);

    pdc->reset = reset;
    pdc->setParameterUnsignedInt = setParameterUnsignedInt;
    pdc->setParameterInt = setParameterInt;
    pdc->setParameterUnsignedShort = setParameterUnsignedShort;
    pdc->setParameterShort = setParameterShort;
    pdc->setParameterBool = setParameterBool;
    pdc->setParameterChar = setParameterChar;
    pdc->setParameterUnsignedChar = setParameterUnsignedChar;
    pdc->setParameterFloat = setParameterFloat;
    pdc->setParameterDouble = setParameterDouble;
    pdc->getParameterUnsignedInt = getParameterUnsignedInt;
    pdc->getParameterInt = getParameterInt;
    pdc->getParameterUnsignedShort = getParameterUnsignedShort;
    pdc->getParameterShort = getParameterShort;
    pdc->getParameterBool = getParameterBool;
    pdc->getParameterUnsignedChar = getParameterUnsignedChar;
    pdc->getParameterChar = getParameterChar;
    pdc->getParameterFloat = getParameterFloat;
    pdc->getParameterDouble = getParameterDouble;
    pdc->getParameterPointerUnsignedInt = getParameterPointerUnsignedInt;
    pdc->getParameterPointerInt = getParameterPointerInt;
    pdc->getParameterPointerUnsignedShort = getParameterPointerUnsignedShort;
    pdc->getParameterPointerShort = getParameterPointerShort;
    pdc->getParameterPointerUnsignedChar = getParameterPointerUnsignedChar;
    pdc->getParameterPointerChar = getParameterPointerChar;
    pdc->getParameterPointerBool = getParameterPointerBool;
    pdc->getParameterPointerFloat = getParameterPointerFloat;
    pdc->getParameterPointerDouble = getParameterPointerDouble;
}

static const TypeInfo type_info = {
    .name = TYPE_PARAMETERDATABASE,
    .parent = TYPE_CC_ROOTOBJECT,
    .instance_size = sizeof(ParameterDatabase),
    .abstract = true,
    .class_size = sizeof(ParameterDatabaseClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void ParameterDatabase_register(void)
{
    type_register_static(&type_info);
}
