//
//
// DC_DataItem.h
//
//
// Change Record:


#ifndef DC_DATAITEM_H
#define DC_DATAITEM_H


#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "../Qom/object.h"


/*
 * This class encapsulates a data item.
 * A data item encapsulates access to a variable. The target variable is specified
 * as an address that is passed to the class constructor. The target variable
 * cannot be changed after the class is instantiated. It is however declared as a
 * <code>protected</code> variable so that subclasses may be implemented that
 * allow it to be updated.
 * <p>
 * Data item components can also be used to encapsulate references to memory-mapped
 * registers.
 * <p>
 * The variable encapsulated by a data item can be of two types: <code>TD_Float</code>
 * (a real-valued data item) or <code>TD_Integer</code> (an integer valued
 * data item). This class provides getter/setter methods to read and write
 * the underlying variable as either an instance of type <code>TD_Float</code>
 * or <code>TD_Integer</code>.
 * <p>
 * Data items are designed for efficiency.
 * There are accordingly no run-time checks on consistency of usage of the
 * getter and setter methods(e.g. there is no protection against a user accessing
 * a real-valued data item with the getter method for integer-valued data items).
 * However, when the preprocessor symbol <code>NDEBUG</code>
 * is NOT defined, additional checks are inserted in the code and their violation
 * will give rise to assertion errors.
 * <p>
 * This class deviates from the project-specific coding rule PR3.1.
 * Use of pointers to a variable of primitive type is necessary to fulfill
 * the function of the class.
 * <p>
 * This class is intended to be very light-weight because it is used
 * throughout an application and may be instantiated a large number of times.
 * For this reason, unlike most framework classes, it is a stand-alone class
 * which does not inherit from <CODE>CC_RootObject</CODE>. This is a deviation
 * from project-specific coding rule PR1.1.
 * @todo Make the constructor parameterless for consistency with the rest of the
 * framework and add a setter method for the variable encapsulated by the data item
 * In order to keep this class distinct from DC_SettableDataItem, the setter method
 * should raise an assertion exception if it is called more than once.
 * @author Alessandro Pasetti, Roberto Totaro
 * @version 1.0
 * @ingroup Data
 */
#define TYPE_DC_DATAITEM "dc_dataitem"

void DC_DataItem_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_DataItem {
    Object parent;

    /**
     * The pointer to the variable that is encapsualetd by the data item.
     * This variable cannot be updated within class <code>DC_DataItem</code>. It
     * is however defined <code>protected</code> to allow subclasses
     * to define methods that allow it to be updaetd.
     */
    void *pVar;
    /**
     * This variable is only used when assertions are enabled(i.e. when NDEBUG is
     * not defined). It is used to perform run-time checks on whether the variable
     * encapsulated by this class is accessed in a type-safe manner.
     * The use of this variable represents a violation of project-specific coding rule PR9.2.
     * The violation is justified by the difficulty of otherwise ensuring that the
     * variable encapsulated by a data item is written to or read back with the
     * correct accessor methods.
     */
    TD_DataItemType varType;
};


struct DC_DataItemClass {
    ObjectClass parent_class;

    void (*post_init)(DC_DataItem *This, void *data, TD_DataItemType type);
};


#define DC_DATAITEM_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_DataItemClass, obj, TYPE_DC_DATAITEM)

#define DC_DATAITEM_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_DataItemClass, klass, TYPE_DC_DATAITEM)

#define DC_DATAITEM(obj) \
        OBJECT_CHECK(DC_DataItem, obj, TYPE_DC_DATAITEM)


DC_DataItem* DC_DataItem_new(void *data, TD_DataItemType type);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Return the value of a real-valued data item.
 * @return the value of the variable encapsulated in the data item
 * component interpreted as a variable of type <code>TD_Float</code>
 */
TD_Float DC_DataItem_getFloatValue(const DC_DataItem *This);

/**
 * Set the value of a real-valued data item.
 * @param newValue the new value of the variable encapsulated in the data item
 */
void DC_DataItem_setFloatValue(DC_DataItem *This, TD_Float newValue);

/**
 * Return the value of an integer-valued data item.
 * @return the value of the variable encapsulated in the data item
 * component interpreted as a variable of type <code>TD_Integer</code>
 */
TD_Integer DC_DataItem_getIntegerValue(const DC_DataItem *This);

/**
 * Set the value of an integer-valued data item.
 * @param newValue the new value of the variable encapsulated in the data item
 */
void DC_DataItem_setIntegerValue(DC_DataItem *This, TD_Integer newValue);


#endif
