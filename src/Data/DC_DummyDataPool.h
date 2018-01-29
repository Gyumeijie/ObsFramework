//
//
// DC_DummyDataPool.h
//
//


#ifndef DC_DUMMYDATAPOOL_H
#define DC_DUMMYDATAPOOL_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Data/DC_BasicDataPool.h"
#include "../Qom/object.h"


/*
 * Default component implementing a dummy data pool.
 * A dummy data pool is a <i>basic data pool</i> that can hold only one single integer-valued
 * data pool item. The value of 
 * this single data pool item is initialized to zero.
 * This data pool is useful for testing purposes as a placeholder for components of 
 * type <code>DataPool</code>.
 * @author Alessandro Pasetti(P&P Software)
 * @version 1.0
 */
#define TYPE_DC_DUMMYDATAPOOL "dc_dummydatapool"

void DC_DummyDataPool_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_DummyDataPool {
    DC_BasicDataPool parent;
};


struct DC_DummyDataPoolClass {
    DC_BasicDataPoolClass parent_class;
};


#define DC_DUMMYDATAPOOL_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_DummyDataPoolClass, obj, TYPE_DC_DUMMYDATAPOOL)

#define DC_DUMMYDATAPOOL_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_DummyDataPoolClass, klass, TYPE_DC_DUMMYDATAPOOL)

#define DC_DUMMYDATAPOOL(obj) \
        OBJECT_CHECK(DC_DummyDataPool, obj, TYPE_DC_DUMMYDATAPOOL)


DC_DummyDataPool* DC_DummyDataPool_new(void);

#endif
