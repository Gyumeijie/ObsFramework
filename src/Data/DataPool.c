//
//
// DataPool.c
//
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../FDIR/DC_NullProfile.h"
#include "../FDIR/DC_NullRecoveryAction.h"
#include "DC_DataItem.h"
#include "DataPool.h"



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Getter method for a <i>data item</i> that encapsulates a
 * data pool item. This method implements the <i>data item link</i>
 * mechanism.
 * This class provides a default implementation that returns
 * a data item that encapsulates an internal variable of type "unsigned
 * integer" and with a constant value of zero. This default
 * implementation is useful for
 * subclasses that do not wish to implement a <i>data item link</i>
 * mechanism.
 * @see DC_DataItem
 * @param id the data identifier of the data pool item to be read
 * @return the <code>DC_DataItem</code> item encapsulating the data
 * pool item with identifier id
 */
static DC_DataItem* getDataItem(void *obj, TD_DataPoolId id)
{
    DataPool *This = DATAPOOL(obj);
    return This->pDummyDataItem;
}

/**
 * Return the time stamp of a data pool item.
 * The time stamp of a data pool item is normally set by the setter
 * method when the item value is updated.
 * This class provides a default implementation that always returns zero.
 * @param id the data identifier of the data whose time stamp is sought
 * @return the time stamp of the data with identifier id
 */
static TD_ObsTime getTimeStamp(void *obj, TD_DataPoolId id)
{
   return (TD_ObsTime)0;
}

/**
 * Return the validity status of a data pool item.
 * This class provides a default implementation that always returns "data valid".
 * @param id the data identifier of the data pool item
 * @return true if the data pool item is valid, false otherwise
 */
static bool isValid(void *obj, TD_DataPoolId id)
{
    return true;
}

/**
 * Set the validity status of a data pool item.
 * This class provides a default implementation that returns without taking any action.
 * @param id the data identifier of the data pool item
 * @param newValidityStatus the new validity status
 */
static void setValidityStatus(void *obj, TD_DataPoolId id, bool newValidityStatus)
{
    return;
}

/**
 * Get the monitoring profile for a data pool item.
 * This class provides a default implementation that returns the same
 * dummy monitoring profile(an instance of <code>DC_NullMonitoringProfile</code>) for
 * all values of the parameter identifier.
 * Note that this class does not define any setter method for the monitoring
 * profile. This is because different implementations may have different policies
 * for defining the monitoring profiles. In a typical case, to each data pool
 * item a particular and fixed monitoring profile is associated. In this case, the data pool
 * class would offer a setter method for the monitoring profile. In another typical
 * case, the monitoring profiles are mode-dependent: the association between a
 * particular data pool item and its monitoring profile is a function of the
 * operational mode. In that case, the monitoring profiles are dynamically
 * loaded by a <i>mode manager</i> and the data pool class only exposes a
 * a setter method for this mode manager.
 * @param id the identifier of the data pool item
 * @return the monitoring profile
 */
static MonitoringProfile* getMonitoringProfile(void *obj, TD_DataPoolId id)
{
    return (MonitoringProfile*)DATAPOOL(obj)->pNullProfile;
}

/**
 * Get the recovery action for a data pool item.
 * This class provides a default implementation that returns the same
 * dummy recovery action(an instance of <code>DC_NullRecoveryAction</code>) for
 * all values of the parameter identifier.
 * Note that this class does not define any setter method for the recovery
 * action. This is because different implementations may have different policies
 * for defining the recovery actions. In a typical case, to each data pool
 * item a particular and fixed recovery action is associated. In this case, the data pool
 * class would offer a setter method for the recovery action. In another typical
 * case, the recovery actions are mode-dependent: the association between a
 * particular data pool item and its recovery action is a function of the
 * operational mode. In that case, the recovery actions are dynamically
 * loaded by a <i>mode manager</i> and the data pool class only exposes a
 * a setter method for this mode manager.
 * @param id the identifier of the data pool item
 * @return the recovery action
 */
static RecoveryAction* getRecoveryAction(void *obj, TD_DataPoolId id)
{
    return (RecoveryAction*)DATAPOOL(obj)->pNullRecoveryAction;
}

/**
 * Iteration method that resets the iteration and returns the lowest
 * indentifier of the items in the data pool. This method is used in
 * conjunction with the other two iteration methods <code>nextIdentifier</code>
 * and <code>isLastIdentifier</code>. These three methods are typically
 * used in a for-loop as follows: <pre>
 *		for(unsigned int i=firstIdentifier(void); !isLastIdentifier(void); i=nextIdentifier(void))
 *			... // process i-th item in the data pool  </pre>
 * The conceptual model behind the iteration methods is as follows.
 * The data pool maintains an internal <i>iteration pointer</i>. During an
 * iteration, this pointer scans all the items in the data pool in sequence.
 * When method <code>firstIdentifier</code> is called, the pointer is reset
 * to point to the lowest valued identifier in the data pool. Each call to method
 * <code>nextIdentifier</code> causes this pointer to switch to the next
 * higher valid identifier in the data pool. Users can check the progress
 * of the iteration by calling method <code>isLastIdentifier</code> which
 * returns false if(and only if) the pointer is positioned on the highest
 * valued identifier in the data pool.
 * <p>
 * This class provides a default implementation that always returns zero.
 * Note that the value of zero is not a legal identifier. This default
 * implementation is useful for the case where a data pool is unable or
 * unwilling to provide a meaningful implementation for the iteration
 * services.
 * @see #nextIdentifier
 * @see #isLastIdentifier
 * @return the identifier of the first data pool item in the iteration
 */
static TD_DataPoolId firstIdentifier(void *obj)
{
    return 0;
}

/**
 * Iteration method that returns the next identifier in an iteration.
 * This method is used in
 * conjunction with the other two iteration methods <code>firstIdentifier</code>
 * and <code>isLastIdentifier</code>.
 * This method should only be called after having called method
 * <code>firstIdentifier</code> and while method <code>isLastIdentifier</code>
 * returns false. If these conditions do not hold, the return value of this
 * method is undefined.
 * <p>
 * This class provides a default implementation that always returns zero.
 * Note that the value of zero is not a legal identifier. This default
 * implementation is useful for the case where a data pool is unable or
 * unwilling to provide a meaningful implementation for the iteration
 * services.
 * @see #firstIdentifier
 * @see #isLastIdentifier
 * @return the identifier of the next data pool item in the iteration
 */
static TD_DataPoolId nextIdentifier(void *obj)
{
    return 0;
}

/**
 * Iteration method that checks whether an iteration is finished.
 * This method is used in
 * conjunction with the other two iteration methods <code>firstIdentifier</code>
 * and <code>isLastIdentifier</code>. It returns true when the iteration
 * is finished.
 * The iteration is finished if method <code>nextIdentifier</code> has been called
 * N times since the last time method <code>isFirstIdentifier</code> was called
 * where N is the number of items in the data pool
 * <p>
 * This class provides a default implementation that always returns true.
 * This default
 * implementation is useful for the case where a data pool is unable or
 * unwilling to provide a meaningful implementation for the iteration
 * services.
 * @see #nextIdentifier
 * @see #firstIdentifier
 * @return true if the iteration has completed, false otherwise
 */
static bool isLastIdentifier(void *obj)
{
    return true;
}

/**
 * Method implementing the type checking service to check whether a
 * data pool item is real-valued.
 * A real-value item is an item with a value whose syntactical type
 * is <code>TD_Float</code>.
 * This method returns true if the argument is the identifier of a
 * data pool item that is real-typed. The method returns false if the
 * identifier is either illegal(there is no item in the data pool
 * that takes it as its identifier) or if the identifier identifies a
 * an item that is integer-valued.
 * <p>
 * This method is often used during an iteration to verify whether the
 * data item being iterated upon is real-valued. This is important because
 * it allows the client to decide which getter method to use to retrieve
 * its value.
 * Note that this class also offers a method to check whether a data pool
 * item is integer-valued(method <code>isInteger</code>). Since a
 * data item must be either real-valued or integer-valued, these two
 * methods taken together allow a client to check whether to a particular
 * identifier value there corresponds a data item or not.
 * <p>
 * This class provides a default implementation that always returns true.
 * This default
 * implementation is useful for the case where a data pool is unable or
 * unwilling to distinguish between real-valued and integer-valued items.
 * @see #isInteger
 * @see id the identifier of the data pool item
 * @return true if the id is the identifier of a floating point data pool item, 
 * false otherwise
 */
static bool isFloat(void *obj, TD_DataPoolId id)
{
    return true;
}

/**
 * Method implementing the type checking service to check whether a
 * data pool item is integer-typed.
 * This method is the counterpart of method <code>isFloat</code>.
 * This class provides a default implementation that always returns
 * true.
 * @see #isFloat
 * @see id the identifier of the data pool item
 * @return true if the id is the identifier of an integer data pool item, 
 * false otherwise
 */
static bool isInteger(void *obj, TD_DataPoolId id)
{
    return true;
}

/**
 * Implement the data pool reset service.
 * The validity status of all data pool item is reset to the value it
 * had at the time the data pool component was created. This class
 * provides a default implementation that returns without doing anything.
 * @see #isValid
 */
static void reset(void *obj)
{
    return;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Setter method for the value of a real-typed data pool item.
 * @param id the data identifier of the data pool item to be set
 * @param newValue the new value to be set
 */
static void setFloatValue(void *obj, TD_DataPoolId id, TD_Float newValue)
{
    // this is automate genenrated by converter
}

/**
 * Setter method for the value of an integer-typed data pool item.
 * @param id the data identifier of the data pool item to be set
 * @param newValue the new value to be set
 */
static void setIntegerValue(void *obj, TD_DataPoolId id, TD_Integer newValue)
{
    // this is automate genenrated by converter
}

/**
 * Getter method for the value of a real-typed data pool item.
 * This method implements the <i>copy link</i>
 * mechanism for real-valued data.
 * @param id the data identifier of the data pool item to be read
 * @return the value of the data with identifier id
 */
static TD_Float getFloatValue(void *obj, TD_DataPoolId id)
{
    // this is automate genenrated by converter
}

/**
 * Getter method for the value of an integer-typed data pool item.
 * This method implements the <i>copy link</i>
 * mechanism for integer-valued data.
 * @param id the data identifier of the data pool item to be read
 * @return the value of the data with identifier id
 */
static TD_Integer getIntegerValue(void *obj, TD_DataPoolId id)
{
    // this is automate genenrated by converter
}

/**
 * Getter method for the pointer to a real-typed data pool item.
 * This method implements the <i>pointer link</i>
 * mechanism for real-typed data.
 * @param id the data identifier of the data pool item to be read
 * @return the pointer to the data with identifier id
 */
static TD_Float* getPointerFloatValue(void *obj, TD_DataPoolId id)
{
    // this is automate genenrated by converter
}

/**
 * Getter method for the pointer to an integer-typed data pool item.
 * This method implements the <i>pointer link</i>
 * mechanism for integer-typed data.
 * @param id the data identifier of the data pool item to be read
 * @return the pointer to the data with identifier id
 */
static TD_Integer* getPointerIntegerValue(void *obj, TD_DataPoolId id)
{
    // this is automate genenrated by converter
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    DataPool *This = DATAPOOL(obj);

    This->dummyInt = 0;
    This->pNullRecoveryAction = DC_NullRecoveryAction_new();
    This->pNullProfile = DC_NullProfile_new();
    This->pDummyDataItem = DC_DataItem_new(&This->dummyInt, DI_INT);
}

DataPool* DataPool_new(void)
{
    Object *obj = object_new(TYPE_DATAPOOL);
    return (DataPool*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    DataPoolClass *dpc = DATAPOOL_CLASS(oc);

    dpc->setFloatValue = setFloatValue;
    dpc->setIntegerValue = setIntegerValue;
    dpc->getFloatValue = getFloatValue;
    dpc->getIntegerValue = getIntegerValue;
    dpc->getPointerFloatValue = getPointerFloatValue;
    dpc->getPointerIntegerValue = getPointerIntegerValue;

    dpc->getDataItem = getDataItem;
    dpc->getTimeStamp = getTimeStamp;
    dpc->isValid = isValid;
    dpc->setValidityStatus = setValidityStatus;
    dpc->getMonitoringProfile = getMonitoringProfile;
    dpc->getRecoveryAction = getRecoveryAction;
    dpc->firstIdentifier = firstIdentifier;
    dpc->nextIdentifier = nextIdentifier;
    dpc->isLastIdentifier = isLastIdentifier;
    dpc->isFloat = isFloat;
    dpc->isInteger = isInteger;
    dpc->reset = reset;
}

static const TypeInfo type_info = {
    .name = TYPE_DATAPOOL,
    .parent = TYPE_CC_ROOTOBJECT,
    .instance_size = sizeof(DataPool),
    .abstract = true,
    .class_size = sizeof(DataPoolClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DataPool_register(void)
{
    type_register_static(&type_info);
}
