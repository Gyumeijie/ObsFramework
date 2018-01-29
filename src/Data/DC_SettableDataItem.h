//
//
// DC_SettableDataItem.h
//
//
// Change Record:


#ifndef DC_SETTABLEDATAITEM_H
#define DC_SETTABLEDATAITEM_H


#include "../GeneralInclude/BasicTypes.h"
#include "DC_DataItem.h"
#include "../Qom/object.h"


/*
 * This class encapsulates a settable data item.
 * A <i>settable data item</i> is a data item that allows the encapsulated variable
 * to be dynamically updated. Data items are used to set up permanent links between
 * a component A that needs some input data and a component B that provides the input 
 * data. In such a situation, component A can be passed a data item that encapsulates
 * access to the data from component B. Use of a settable data item(as opposed to an 
 * ordinary data item of the
 * kind that is directly instantiated from <code>DC_DataItem</code>) is useful when
 * it is desired to keep the option open of changing the input for component A.
 * This can be done by changing the variable that is encapsulated in the data item 
 * that A uses as the source for its input. 
 * @todo create a test case for this class
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_SETTABLEDATAITEM "dc_settabledataitem"

void DC_SettableDataItem_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_SettableDataItem {
    DC_DataItem parent;
};


struct DC_SettableDataItemClass {
    DC_DataItemClass parent_class;

    void (*post_init)(DC_SettableDataItem *This, void *data, TD_DataItemType type);
};


#define DC_SETTABLEDATAITEM_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_SettableDataItemClass, obj, TYPE_DC_SETTABLEDATAITEM)

#define DC_SETTABLEDATAITEM_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_SettableDataItemClass, klass, TYPE_DC_SETTABLEDATAITEM)

#define DC_SETTABLEDATAITEM(obj) \
        OBJECT_CHECK(DC_SettableDataItem, obj, TYPE_DC_SETTABLEDATAITEM)


DC_SettableDataItem* DC_SettableDataItem_new(void *data, TD_DataItemType type);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set a new integer-valued variable as the variable that is encapsulated
 * by the data item.
 * @param pNewVar the new variable encapsulated in the data item
 */
void DC_SettableDataItem_setIntegerVariable
(
    DC_SettableDataItem *This,
    TD_Integer *pNewVar
);

/**
 * Set a new real-valued variable as the variable that is encapsulated
 * by the data item.
 * @param pNewVar the new variable encapsulated in the data item
 */
void DC_SettableDataItem_setFloatVariable
(
    DC_SettableDataItem *This, 
    TD_Float *pNewVar
);


#endif
