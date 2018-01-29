//
//
// DataPool.h
//


#ifndef DATAPOOL_H
#define DATAPOOL_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "../Qom/object.h"


/*
 * Base class from which all data pool classes are derived.
 * A <i>data pool</i> is a component that acts as a shared data area for data
 * that must be exchanged among other components. The data pool physically
 * contains the data to be exchanged. The producers of the data deposit them into
 * the data pool and the consumers of the data retrieve them from the data pool.
 * This class implements a data pool as a collection of items with the
 * following attributes: <ul>
 * <li>Each item in the data pool has a <i>value</i>.</li>
 * <li>Each item in the data pool has a <i>time stamp</i> that represents
 * the time when the value of the item was last updated.</li>
 * <li>Each item in the data pool has a <i>type</i> that represents
 * the syntactical type of the value of the item. This interface recognizes
 * two possible types: "float" and "integer" that, at syntactical level, correspond
 * to two types defined through <code>typedef</code> declarations(<code>TD_Float</code>
 * and <code>TD_Integer</code>).</li>
 * <li>Each item in the data pool is identified by a <i>data pool item identifier</i>.
 * Access to the value of the item is exclusively through its identifier.
 * Note that this class does not mandate any checks on the legality of the data
 * identifier used by a caller. This is not done because of the potential execution
 * and memory costs of such checks. Legality checks can however be introduced by
 * some implementations if needed.</li>
 * <li>Each item in the data pool has a <i>validity status</i> that
 * can have two values: "valid" and "not valid".</li>
 * <li>Each item in the data pool has an associated <i>monitoring profile</i>
 * that represents the legal time profile that the value of the data pool item
 * can take.</li>
 * <li>Each item in the data pool has an associated <i>recovery action</i> that represents
 * the recovery action that should be performed when the value of the item violates
 * its monitoring profile.</li>
 * </ul>
 * This is an abstract class because the internal organization of the
 * data pool is application-dependent. In particular, the data structure used to
 * represent the data pool and the implementation of the attributes defined above
 * is left undefined. Full
 * implementation of all the above attributes would
 * result in a very "heavy" class that would not be suitable for applications
 * with tight memory and CPU budgets. Most concrete data pool classes will
 * only provide meaningful implementations for only a subset of the
 * above attributes.
 * <p>
 * This class defines the following service: <ul>
 * <li>The <i>iteration service</i> that allows a client to
 * iterate over all the identifiers of the items contained in the data
 * pool.</li>
 * <li>The <i>type checking service</i> that allows a client to check the type
 * of an item as a function of its identifier. The type checking service
 * can also be used to check whether a certain integer is a legal identifier.</li>
 * <li>The <i>reset service</i> that resets the validity status of all data pool
 * items to the value they had at the time the data pool component was initialized.</li>
 * </ul>
 * The purpose of a data pool is to allow client components to link to it
 * to access data which they share with other components. This data pool
 * offers three types of linking mechanism to a client component:<ul>
 * <li><i>Copy Link</i>: the client component accesses the value of the
 * shared datum through data setter and getter methods. The shared datum
 * is copied to and from the data pool.</li>
 * <li><i>Pointer Link</i>: at configuration time, the client component
 * accesses the pointer of the shared datum and then uses this pointer
 * to access the value of the datum during the operational phase.</li>
 * <li><i>Data Item Link</i>: at configuration time, the client component
 * accesses the <i>data item</i> that encapsulates the shared datum and
 * accesses its value during during the operational phase using the services
 * defined by the <i>DC_DataItem</i> class.</li>
 * </ul>
 * A data pool is a low-level data structure whose implementation will
 * usually require use of pointers. Most implementations of this class
 * will therefore violate project specific coding rule PR3.1.
 * <p>
 * @todo This class defines the setter and getter methods to be virtual. This
 * is expensive in CPU time. Given that data pool implementations will often
 * be generated automatically by XSL programs, and given that an application
 * would normally only have one data pool component, it may be wiser to 
 * have the XSL program generate an implementation for class DataPool that 
 * is defined to have only non-virtual methods. The problem with this approach
 * is that it is not possible to have multiple implementations of a data pool
 * in a single delivery and that therefore it is not possible to have several
 * data pool test cases in the same delivery(this could be alleviated by
 * generating the test case for the data pool as well as the data pool 
 * implementation). 
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 * @ingroup Data
 */
#define TYPE_DATAPOOL "datapool"

void DataPool_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DataPool {
    CC_RootObject parent;

    DC_NullProfile *pNullProfile;
    DC_NullRecoveryAction *pNullRecoveryAction;
    TD_Integer dummyInt;
    DC_DataItem *pDummyDataItem;
};


struct DataPoolClass {
    CC_RootObjectClass parent_class;
 
    DC_DataItem* (*getDataItem)(void *obj, TD_DataPoolId id);
    TD_ObsTime (*getTimeStamp)(void *obj, TD_DataPoolId id);
    bool (*isValid)(void *obj, TD_DataPoolId id);
    void (*setValidityStatus)(void *obj, TD_DataPoolId id, bool newValidityStatus);
    MonitoringProfile* (*getMonitoringProfile)(void *obj, TD_DataPoolId id);
    RecoveryAction* (*getRecoveryAction)(void *obj, TD_DataPoolId id);
    TD_DataPoolId (*firstIdentifier)(void *obj);
    TD_DataPoolId (*nextIdentifier)(void *obj);
    bool (*isLastIdentifier)(void *obj);
    bool (*isFloat)(void *obj, TD_DataPoolId id);
    bool (*isInteger)(void *obj, TD_DataPoolId id);
    void (*reset)(void *obj);
 
    void (*setFloatValue)(void *obj, TD_DataPoolId id, TD_Float newValue);
    void (*setIntegerValue)(void *obj, TD_DataPoolId id, TD_Integer newValue);
    TD_Float (*getFloatValue)(void *obj, TD_DataPoolId id);
    TD_Integer (*getIntegerValue)(void *obj, TD_DataPoolId id);
    TD_Float* (*getPointerFloatValue)(void *obj, TD_DataPoolId id);
    TD_Integer* (*getPointerIntegerValue)(void *obj, TD_DataPoolId id);
};


#define DATAPOOL_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DataPoolClass, obj, TYPE_DATAPOOL)

#define DATAPOOL_CLASS(klass) \
        OBJECT_CLASS_CHECK(DataPoolClass, klass, TYPE_DATAPOOL)

#define DATAPOOL(obj) \
        OBJECT_CHECK(DataPool, obj, TYPE_DATAPOOL)


DataPool* DataPool_new(void);

#endif
