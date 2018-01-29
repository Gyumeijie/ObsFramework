//
//
// DC_BasicDatabase.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "DC_BasicDatabase.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_BasicDatabase_setTableLength
(
   DC_BasicDatabase *This,  
   TD_DatabaseId length
)
{
   assert(length > 0);
   This->tableLength = length;
}

TD_DatabaseId DC_BasicDatabase_getTableLength(DC_BasicDatabase *This)
{
   return This->tableLength;
}

void DC_BasicDatabase_setDefaultTable(DC_BasicDatabase *This, char *pDefTable)
{
   assert(pDefTable != pNULL);
   This->pDefaultTable = pDefTable;
}

void DC_BasicDatabase_setOperationalTable
(
   DC_BasicDatabase *This, 
   char *pOperTable)
{
   assert(pOperTable != pNULL);
   This->pOperationalTable = pOperTable;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Copy the default table array onto the operational table array.
 */
static void reset(void *obj)
{ 
   DC_BasicDatabase *This = DC_BASICDATABASE(obj);

   assert((This->pDefaultTable != pNULL) && 
          (This->pOperationalTable != pNULL));
   assert(This->tableLength > 0);

   for (TD_DatabaseId i=0; i<This->tableLength; i++) {
      This->pOperationalTable[i] = This->pDefaultTable[i];
   }
   This->resetWasCalled = true;
}

/**
 * Set the current value of a parameter interpreted as an unsigned integer.
 * @param parId the identifier of the parameter to be set
 * @param newValue the new current value of the parameter
 */
static void setParameterUnsignedInt(void *obj, 
                                    TD_DatabaseId parId, 
                                    unsigned int newValue)
{
   DC_BasicDatabase *This = DC_BASICDATABASE(obj);

   assert(This->pOperationalTable != pNULL);
   *((unsigned int*)(This->pOperationalTable + parId)) = newValue;
}

/**
 * Set the current value of a parameter interpreted as an integer.
 * @param parId the identifier of the parameter to be set
 * @param newValue the new current value of the parameter
 */
static void setParameterInt(void *obj, TD_DatabaseId parId, int newValue)
{
   DC_BasicDatabase *This = DC_BASICDATABASE(obj);

   assert(This->pOperationalTable != pNULL);
   *((int*)(This->pOperationalTable+parId)) = newValue;
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
   DC_BasicDatabase *This = DC_BASICDATABASE(obj);
   
   assert(This->pOperationalTable != pNULL);
   *((unsigned short*)(This->pOperationalTable+parId)) = newValue;
}

/**
 * Set the current value of a parameter interpreted as an short.
 * @param parId the identifier of the parameter to be set
 * @param newValue the new current value of the parameter
 */
static void setParameterShort(void *obj, TD_DatabaseId parId, short newValue)
{
   DC_BasicDatabase *This = DC_BASICDATABASE(obj);

   assert(This->pOperationalTable != pNULL);
   *((short*)(This->pOperationalTable + parId)) = newValue;
}

/**
 * Set the current value of a parameter interpreted as a boolean.
 * @param parId the identifier of the parameter to be set
 * @param newValue the new current value of the parameter
 */
static void setParameterBool(void *obj, TD_DatabaseId parId, bool newValue)
{
   DC_BasicDatabase *This = DC_BASICDATABASE(obj);

   assert(This->pOperationalTable != pNULL);
   *((bool*)(This->pOperationalTable + parId)) = newValue;
}

/**
 * Set the current value of a parameter interpreted as a char.
 * @param parId the identifier of the parameter to be set
 * @param newValue the new current value of the parameter
 */
static void setParameterChar(void *obj, TD_DatabaseId parId, char newValue)
{
   DC_BasicDatabase *This = DC_BASICDATABASE(obj);

   assert(This->pOperationalTable != pNULL);
   *((char*)(This->pOperationalTable + parId)) = newValue;
}

/**
 * Set the current value of a parameter interpreted as an unsigned char.
 * @param parId the identifier of the parameter to be set
 * @param newValue the new current value of the parameter
 */
static void setParameterUnsignedChar(void *obj, 
                                     TD_DatabaseId parId, 
                                     unsigned char newValue)
{
   DC_BasicDatabase *This = DC_BASICDATABASE(obj);

   assert(This->pOperationalTable != pNULL);
   *((unsigned char*)(This->pOperationalTable + parId)) = newValue;
}

/**
 * Set the current value of a parameter interpreted as a float.
 * @param parId the identifier of the parameter to be set
 * @param newValue the new current value of the parameter
 */
static void setParameterFloat(void *obj, TD_DatabaseId parId, float newValue)
{
   DC_BasicDatabase *This = DC_BASICDATABASE(obj);

   assert(This->pOperationalTable != pNULL);
   *((float*)(This->pOperationalTable + parId)) = newValue;
}

/**
 * Set the current value of a parameter interpreted as a double.
 * @param parId the identifier of the parameter to be set
 * @param newValue the new current value of the parameter
 */
static void setParameterDouble(void *obj, TD_DatabaseId parId, double newValue)
{
   DC_BasicDatabase *This = DC_BASICDATABASE(obj);

   assert(This->pOperationalTable != pNULL);
   *((double*)(This->pOperationalTable + parId)) = newValue;
}

/**
 * Get the current value of a parameter interpreted as an unsigned integer.
 * @param parId the identifier of the parameter to be set
 * @return the current value of the parameter
 */
static unsigned int getParameterUnsignedInt(void *obj, TD_DatabaseId parId)
{
   DC_BasicDatabase *This = DC_BASICDATABASE(obj);

   assert(This->pOperationalTable != pNULL);
   return *(unsigned int*)(This->pOperationalTable + parId);
}

/**
 * Get the current value of a parameter interpreted as an integer.
 * @param parId the identifier of the parameter to be set
 * @return the current value of the parameter
 */
static int getParameterInt(void *obj, TD_DatabaseId parId)
{
   DC_BasicDatabase *This = DC_BASICDATABASE(obj);

   assert(This->pOperationalTable != pNULL);
   return *(int*)(This->pOperationalTable + parId);
}

/**
 * Get the current value of a parameter interpreted as an unsigned short.
 * @param parId the identifier of the parameter to be set
 * @return the current value of the parameter
 */
static unsigned short getParameterUnsignedShort(void *obj, TD_DatabaseId parId)
{
   DC_BasicDatabase *This = DC_BASICDATABASE(obj);

   assert(This->pOperationalTable != pNULL);
   return *(unsigned short*)(This->pOperationalTable + parId);
}

/**
 * Get the current value of a parameter interpreted as a short.
 * @param parId the identifier of the parameter to be set
 * @return the current value of the parameter
 */
static short getParameterShort(void *obj, TD_DatabaseId parId)
{
   DC_BasicDatabase *This = DC_BASICDATABASE(obj);

   assert(This->pOperationalTable != pNULL);
   return *(short*)(This->pOperationalTable + parId);
}

/**
 * Get the current value of a parameter interpreted as a boolean.
 * @param parId the identifier of the parameter to be set
 * @return the current value of the parameter
 */
static bool getParameterBool(void *obj, TD_DatabaseId parId)
{
   DC_BasicDatabase *This = DC_BASICDATABASE(obj);

   assert(This->pOperationalTable != pNULL);
   return *(bool*)(This->pOperationalTable + parId);
}

/**
 * Get the current value of a parameter interpreted as an unsigned char.
 * @param parId the identifier of the parameter to be set
 * @return the current value of the parameter
 */
static unsigned char getParameterUnsignedChar(void *obj, TD_DatabaseId parId)
{
   DC_BasicDatabase *This = DC_BASICDATABASE(obj);

   assert(This->pOperationalTable != pNULL);
   return *(unsigned char*)(This->pOperationalTable + parId);
}

/**
 * Get the current value of a parameter interpreted as a char.
 * @param parId the identifier of the parameter to be set
 * @return the current value of the parameter
 */
static char getParameterChar(void *obj, TD_DatabaseId parId)
{
   DC_BasicDatabase *This = DC_BASICDATABASE(obj);
   
   assert(This->pOperationalTable != pNULL);
   return *(char*)(This->pOperationalTable + parId);
}

/**
 * Get the current value of a parameter interpreted as a float.
 * @param parId the identifier of the parameter to be set
 * @return the current value of the parameter
 */
static float getParameterFloat(void *obj, TD_DatabaseId parId)
{
   DC_BasicDatabase *This = DC_BASICDATABASE(obj);

   assert(This->pOperationalTable != pNULL);
   return *(float*)(This->pOperationalTable + parId);
}

/**
 * Get the current value of a parameter interpreted as a double.
 * @param parId the identifier of the parameter to be set
 * @return the current value of the parameter
 */
static double getParameterDouble(void *obj, TD_DatabaseId parId)
{
   DC_BasicDatabase *This = DC_BASICDATABASE(obj);

   assert(This->pOperationalTable != pNULL);
   return *(double*)(This->pOperationalTable + parId);
}

/**
 * Return the pointer to the variable in the operational table storing the
 * parameter identified by <code>parId</code>. The variable is interpreted
 * as of type <code>unsigned int</code>.
 * @return the parameter pointer
 * @param parId the parameter identifier
 */
static unsigned int* getParameterPointerUnsignedInt
(
   void *obj, 
   TD_DatabaseId parId
)
{
   DC_BasicDatabase *This = DC_BASICDATABASE(obj);

   assert(This->pOperationalTable != pNULL);
   return (unsigned int*)(This->pOperationalTable + parId);
}

/**
 * Return the pointer to the variable in the operational table storing the
 * parameter identified by <code>parId</code>. The variable is interpreted
 * as of type <code>int</code>.
 * @return the parameter pointer
 * @param parId the parameter identifier
 */
static int* getParameterPointerInt(void *obj, TD_DatabaseId parId)
{
   DC_BasicDatabase *This = DC_BASICDATABASE(obj);

   assert(This->pOperationalTable != pNULL);
   return (int*)(This->pOperationalTable + parId);
}

/**
 * Return the pointer to the variable in the operational table storing the
 * parameter identified by <code>parId</code>. The variable is interpreted
 * as of type <code>unsigned short</code>.
 * @return the parameter pointer
 * @param parId the parameter identifier
 */
static unsigned short* getParameterPointerUnsignedShort
(
   void *obj, 
   TD_DatabaseId parId
)
{
   DC_BasicDatabase *This = DC_BASICDATABASE(obj);

   assert(This->pOperationalTable != pNULL);
   return (unsigned short*)(This->pOperationalTable + parId);
}

/**
 * Return the pointer to the variable in the operational table storing the
 * parameter identified by <code>parId</code>. The variable is interpreted
 * as of type <code>short</code>.
 * @return the parameter pointer
 * @param parId the parameter identifier
 */
static short* getParameterPointerShort(void *obj, TD_DatabaseId parId)
{
   DC_BasicDatabase *This = DC_BASICDATABASE(obj);

   assert(This->pOperationalTable != pNULL);
   return (short*)(This->pOperationalTable + parId);
}

/**
 * Return the pointer to the variable in the operational table storing the
 * parameter identified by <code>parId</code>. The variable is interpreted
 * as of type <code>unsigned char</code>.
 * @return the parameter pointer
 * @param parId the parameter identifier
 */
static unsigned char* getParameterPointerUnsignedChar
(
   void *obj, 
   TD_DatabaseId parId
)
{
   DC_BasicDatabase *This = DC_BASICDATABASE(obj);

   assert(This->pOperationalTable != pNULL);
   return (unsigned char*)(This->pOperationalTable + parId);
}

/**
 * Return the pointer to the variable in the operational table storing the
 * parameter identified by <code>parId</code>. The variable is interpreted
 * as of type <code>char</code>.
 * @return the parameter pointer
 * @param parId the parameter identifier
 */
static char* getParameterPointerChar(void *obj, TD_DatabaseId parId)
{
   DC_BasicDatabase *This = DC_BASICDATABASE(obj);

   assert(This->pOperationalTable != pNULL);
   return (char*)(This->pOperationalTable + parId);
}

/**
 * Return the pointer to the variable in the operational table storing the
 * parameter identified by <code>parId</code>. The variable is interpreted
 * as of type <code>bool</code>.
 * @return the parameter pointer
 * @param parId the parameter identifier
 */
static bool* getParameterPointerBool(void *obj, TD_DatabaseId parId)
{
   DC_BasicDatabase *This = DC_BASICDATABASE(obj);

   assert(This->pOperationalTable != pNULL);
   return (bool*)(This->pOperationalTable + parId);
}

/**
 * Return the pointer to the variable in the operational table storing the
 * parameter identified by <code>parId</code>. The variable is interpreted
 * as of type <code>float</code>.
 * @return the parameter pointer
 * @param parId the parameter identifier
 */
static float* getParameterPointerFloat(void *obj, TD_DatabaseId parId)
{
   DC_BasicDatabase *This = DC_BASICDATABASE(obj);

   assert(This->pOperationalTable != pNULL);
   return (float*)(This->pOperationalTable + parId);
}

/**
 * Return the pointer to the variable in the operational table storing the
 * parameter identified by <code>parId</code>. The variable is interpreted
 * as of type <code>double</code>.
 * @return the parameter pointer
 * @param parId the parameter identifier
 */
static double* getParameterPointerDouble(void *obj, TD_DatabaseId parId)
{
   DC_BasicDatabase *This = DC_BASICDATABASE(obj);

   assert(This->pOperationalTable != pNULL);
   return (double*)(This->pOperationalTable + parId);
}

/**
 * Perform a class-specific configuration check on a basic database object:
 * verify that the default and operational tables have been loaded, that
 * method <code>reset</code> has been called, and that the table length
 * is greater than zero.
 * @see #reset
 * @return true if the database object is configured, false otherwise
 */
static bool isObjectConfigured(void *obj)
{
   DC_BasicDatabase *This = DC_BASICDATABASE(obj);
   CC_RootObjectClass *cc_roc = GET_CLASS(TYPE_CC_ROOTOBJECT);

   return ((cc_roc->isObjectConfigured(obj)) &&
           (This->tableLength > 0) && 
           (This->pDefaultTable != pNULL) && 
           (This->pOperationalTable != pNULL) && 
           (This->resetWasCalled));
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
   DC_BasicDatabase *This = DC_BASICDATABASE(obj);
   This->pDefaultTable = pNULL;
   This->pOperationalTable = pNULL;
   This->resetWasCalled = false;
   This->tableLength = 0;

   CC_RootObject_setClassId((CC_RootObject*)obj, ID_BASICDATABASE);
}

DC_BasicDatabase* DC_BasicDatabase_new(void)
{
    Object *obj = object_new(TYPE_DC_BASICDATABASE);
    return (DC_BasicDatabase*)obj;
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

    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_BASICDATABASE,
    .parent = TYPE_PARAMETERDATABASE,
    .instance_size = sizeof(DC_BasicDatabase),
    .abstract = false,
    .class_size = sizeof(DC_BasicDatabaseClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_BasicDatabase_register(void)
{
    type_register_static(&type_info);
}
