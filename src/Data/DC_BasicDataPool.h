//
//
// DC_BasicDataPool.h
//
//


#ifndef DC_BASICDATAPOOL_H
#define DC_BASICDATAPOOL_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Data/DataPool.h"
#include "../Qom/object.h"


/*
 * Default component implementing a data pool with basic functionality.
 * The data pool is implemented as a linear array whose index is the identifier
 * of the data pool item. Of all the attributes for data pool items defined in 
 * the base class, the only ones to have a non-dummy implementation are the value
 * and the identifier. For all other attributes, the default implementation inherited
 * from the base class is kept. Note in particular that there are no checks on the
 * legality of the identifier values used when accessing data pool items.
 * This results in a very efficient implementation both in terms of memory
 * and run-time overheads but it also results in a low level of robustness.
 * <p>
 * This class defines one single configuration method to set the size of the data pool.
 * <p>
 * The getter and setter methods are implemented to be fast and efficient but this
 * makes them vulnerable to alignement problems on some processors. For instance,
 * the setter methods for integer-valued variables is implemened as follows:<code>
 *  void DC_BasicDataPool::setValue(TD_DataPoolId id,TD_Integer newValue) {
 *   *(TD_Integer *)(value+id)=newValue;
 *   } </code>
 * On some processors, the assignment will fail if location <code>(value+id)</code> does not
 * correspond to a longword(4 bytes) boundary. There is no check to ensure that this
 * is the case and it is the responsibility of the user to ensure that the setter
 * method is called with the correct parameter values. The same applies to other
 * setter and getter methods. A more robust(but possibly slower) implementation
 * might use the <code>memcpy</code> library function to transfer the values of the
 * data between the data pool locations and the method variables.
 * @author Alessandro Pasetti(P&P Software)
 * @version 1.0
 */
#define TYPE_DC_BASICDATAPOOL "dc_basicdatapool"

void DC_BasicDataPool_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_BasicDataPool {
    DataPool parent;

    unsigned char *value;                  
    TD_DataPoolId size;                   
};


struct DC_BasicDataPoolClass {
    DataPoolClass parent_class;
};


#define DC_BASICDATAPOOL_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_BasicDataPoolClass, obj, TYPE_DC_BASICDATAPOOL)

#define DC_BASICDATAPOOL_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_BasicDataPoolClass, klass, TYPE_DC_BASICDATAPOOL)

#define DC_BASICDATAPOOL(obj) \
        OBJECT_CHECK(DC_BasicDataPool, obj, TYPE_DC_BASICDATAPOOL)


DC_BasicDataPool* DC_BasicDataPool_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Set the size of the internal array where the data pool items are stored.
 * After this method is called, the internal data structures for the data 
 * pool component are allocated and initialized to zero. 
 * <p>
 * The data pool is internally implemented as a linear array. In order to 
 * avoid alignment DC_BasicDataPool_problems(see class comment), the array is forced to 
 * start at an 8-byte word boundary.
 * <p>
 * Only data pool size greater than zero are legal.
 * <p>
 * This is an initialization method. It should only be called once. If it is
 * called more than once, internal memory will be allocated multiple times. 
 * The memory allocated in previous calls is never reclaimed.
 * <p>
 * @param size the size of the data pool in number of bytes
 */
void DC_BasicDataPool_setDataPoolSize(DC_BasicDataPool *This, TD_DataPoolId size);

/**
 * Get the size of the data pool.
 * @see #setDataPoolSize
 * @return size of the data pool in number of bytes
 */
TD_DataPoolId DC_BasicDataPool_getDataPoolSize(DC_BasicDataPool *This);


#endif
