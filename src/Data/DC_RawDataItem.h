//
//
// DC_RawDataItem.h
//
//
// Change Record:


#ifndef DC_RAWDATAITEM_H
#define DC_RAWDATAITEM_H


#include "../GeneralInclude/BasicTypes.h"
#include "../Data/DC_DataItem.h"
#include "../Qom/object.h"


/*
 * This class encapsulates a raw data item.
 * A <i>raw data item</i> is a data item that encapsulates a "raw pointer",
 * namely a pointer that does not have a specific type and is defined simply 
 * as a "pointer to void". The raw data item offers accessors methods that allow
 * its underlying variable to be accessed as a variable of the following
 * types: <code>unsigned int</code>, <code>int</code>, <code>unsigned short</code>,
 * <code>short</code>, <code>unsigned char</code>, <code>char</code>,
 * <code>float</code>, and <code>double</code>. The raw data item therefore
 * essentially allows cast to be performed between types in a controlled manner.
 * This is useful when manipulating registers or other low-level variables. 
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @author Roberto Totaro
 * @version 2.0
 */
#define TYPE_DC_RAWDATAITEM "dc_rawdataitem"

void DC_RawDataItem_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_RawDataItem {
    DC_DataItem parent;
};


struct DC_RawDataItemClass {
    DC_DataItemClass parent_class;
};


#define DC_RAWDATAITEM_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_RawDataItemClass, obj, TYPE_DC_RAWDATAITEM)

#define DC_RAWDATAITEM_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_RawDataItemClass, klass, TYPE_DC_RAWDATAITEM)

#define DC_RAWDATAITEM(obj) \
        OBJECT_CHECK(DC_RawDataItem, obj, TYPE_DC_RAWDATAITEM)


DC_RawDataItem* DC_RawDataItem_new(void *data);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Return the value of the data item intepreted as a variable of
 * type <code>char</code>. The pointer that is encapsulated by the
 * data item is interpreted as a pointer to type <code>char</code>
 * and its dereferenced value is returned.
 * @return the value of the variable encapsulated in the data item
 */
char DC_RawDataItem_getChar(const DC_RawDataItem *This);

/**
 * Set the value of the data item intepreted as a variable of
 * type <code>char</code>. The pointer that is encapsulated by the
 * data item is interpreted as a pointer to type <code>char</code>.
 * @param newValue the new value of the variable encapsulated in the data item
 */
void DC_RawDataItem_setChar(DC_RawDataItem *This, char newValue);

/**
 * Return the value of the data item intepreted as a variable of
 * type <code>unsigned char</code>. The pointer that is encapsulated by the
 * data item is interpreted as a pointer to type <code>unsigned char</code>
 * and its dereferenced value is returned.
 * @return the value of the variable encapsulated in the data item
 */
unsigned char DC_RawDataItem_getUnsignedChar(const DC_RawDataItem *This);

/**
 * Set the value of the data item intepreted as a variable of
 * type <code>unsigned char</code>. The pointer that is encapsulated by the
 * data item is interpreted as a pointer to type <code>unsigned char</code>.
 * @param newValue the new value of the variable encapsulated in the data item
 */
void DC_RawDataItem_setUnsignedChar(DC_RawDataItem *This, unsigned char newValue);

/**
 * Return the value of the data item intepreted as a variable of
 * type <code>short</code>. The pointer that is encapsulated by the
 * data item is interpreted as a pointer to type <code>short</code>
 * and its dereferenced value is returned.
 * @return the value of the variable encapsulated in the data item
 */
short DC_RawDataItem_getShort(const DC_RawDataItem *This);

/**
 * Set the value of the data item intepreted as a variable of
 * type <code>short</code>. The pointer that is encapsulated by the
 * data item is interpreted as a pointer to type <code>short</code>.
 * @param newValue the new value of the variable encapsulated in the data item
 */
void DC_RawDataItem_setShort(DC_RawDataItem *This, short newValue);

/**
 * Return the value of the data item intepreted as a variable of
 * type <code>unsigned short</code>. The pointer that is encapsulated by the
 * data item is interpreted as a pointer to type <code>unsigned short</code>
 * and its dereferenced value is returned.
 * @return the value of the variable encapsulated in the data item
 */
unsigned short DC_RawDataItem_getUnsignedShort(const DC_RawDataItem *This);

/**
 * Set the value of the data item intepreted as a variable of
 * type <code>unsigned short</code>. The pointer that is encapsulated by the
 * data item is interpreted as a pointer to type <code>unsigned short</code>.
 * @param newValue the new value of the variable encapsulated in the data item
 */
void DC_RawDataItem_setUnsignedShort(DC_RawDataItem *This, unsigned short newValue);

/**
 * Return the value of the data item intepreted as a variable of
 * type <code>int</code>. The pointer that is encapsulated by the
 * data item is interpreted as a pointer to type <code>int</code>
 * and its dereferenced value is returned.
 * @return the value of the variable encapsulated in the data item
 */
int DC_RawDataItem_getInt(const DC_RawDataItem *This);

/**
 * Set the value of the data item intepreted as a variable of
 * type <code>int</code>. The pointer that is encapsulated by the
 * data item is interpreted as a pointer to type <code>int</code>.
 * @param newValue the new value of the variable encapsulated in the data item
 */
void DC_RawDataItem_setInt(DC_RawDataItem *This, int newValue);

/**
 * Return the value of the data item intepreted as a variable of
 * type <code>unsigned int</code>. The pointer that is encapsulated by the
 * data item is interpreted as a pointer to type <code>unsigned int</code>
 * and its dereferenced value is returned.
 * @return the value of the variable encapsulated in the data item
 */
unsigned int DC_RawDataItem_getUnsignedInt(const DC_RawDataItem *This);

/**
 * Set the value of the data item intepreted as a variable of
 * type <code>unsigned int</code>. The pointer that is encapsulated by the
 * data item is interpreted as a pointer to type <code>unsigned int</code>.
 * @param newValue the new value of the variable encapsulated in the data item
 */
void DC_RawDataItem_setUnsignedInt(DC_RawDataItem *This, unsigned int newValue);

/**
 * Return the value of the data item intepreted as a variable of
 * type <code>float</code>. The pointer that is encapsulated by the
 * data item is interpreted as a pointer to type <code>float</code>
 * and its dereferenced value is returned.
 * @return the value of the variable encapsulated in the data item
 */
float DC_RawDataItem_getFloat(const DC_RawDataItem *This);

/**
 * Set the value of the data item intepreted as a variable of
 * type <code>float</code>. The pointer that is encapsulated by the
 * data item is interpreted as a pointer to type <code>float</code>.
 * @param newValue the new value of the variable encapsulated in the data item
 */
void DC_RawDataItem_setFloat(DC_RawDataItem *This, float newValue);

/**
 * Return the value of the data item intepreted as a variable of
 * type <code>double</code>. The pointer that is encapsulated by the
 * data item is interpreted as a pointer to type <code>double</code>
 * and its dereferenced value is returned.
 * @return the value of the variable encapsulated in the data item
 */
double DC_RawDataItem_getDouble(const DC_RawDataItem *This);

/**
 * Set the value of the data item intepreted as a variable of
 * type <code>double</code>. The pointer that is encapsulated by the
 * data item is interpreted as a pointer to type <code>double</code>.
 * @param newValue the new value of the variable encapsulated in the data item
 */
void DC_RawDataItem_setDouble(DC_RawDataItem *This, double newValue);


#endif
