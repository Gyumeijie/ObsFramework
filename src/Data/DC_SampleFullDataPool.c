  
//
//
// DC_SampleFullDataPool.c
//
// Automatically generated file

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Event/DC_EventRepository.h"
#include "../Base/CC_RootObject.h"
#include "../System/ObsClock.h"
#include "../Data/DC_SettableDataItem.h"
#include "DC_SampleFullDataPool.h"

static char const TD_FloatCode = 1;
static char const TD_IntegerCode = 2;



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_SampleFullDataPool_setObsClock
(
    DC_SampleFullDataPool *This, 
    ObsClock *pObsClock
)
{
    assert(pObsClock != pNULL);               
    This->pObsClock = pObsClock;
}

ObsClock* DC_SampleFullDataPool_getObsClock(const DC_SampleFullDataPool *This)
{
    return This->pObsClock;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Setter method for the value of a real-typed data pool item. 
 * When this method is called on a data pool item, its time stamp is
 * automatically updated.       
 * If the validity status of the data pool item is "valid", then its
 * back up value is also updated.
 * If the data pool item identifier has an illegal value, then no action is taken other
 * than generating an event of type EVT_ILLEGAL_DP_ACCESS.  
 * @param id the data identifier of the data pool item to be set
 * @param newValue the new value to be set
 */
static void setFloatValue(void *obj, TD_DataPoolId id, TD_Float newValue)
{
    DC_SampleFullDataPool *This = DC_SAMPLEFULLDATAPOOL(obj);
    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);

    assert(id <= This->maxParId);               
    assert(This->type[id] == TD_FloatCode);
 
    if (id > This->maxParId) {
        dc_erc->create(dc_er, obj, EVT_ILLEGAL_DP_ACCESS);
        return;
    }
    if (This->type[id] != TD_FloatCode) {
        dc_erc->create(dc_er, obj, EVT_ILLEGAL_DP_ACCESS);
        return;
    }

    (*(TD_Float*)This->pValue[id]) = newValue;        
    
    ObsClockClass *occ = OBSCLOCK_GET_CLASS(This->pObsClock); 
    This->timeStamp[id] = occ->getTime(This->pObsClock);        

    if (This->valid[id]) {
        (*(TD_Float*)This->pBackUpValue[id]) = newValue;          
    }
}

/**
 * Setter method for the value of an integer-typed data pool item.  
 * When this method is called on a data pool item, its time stamp is
 * automatically updated.       
 * If the validity status of the data pool item is "valid", then its
 * back up value is also updated.
 * If the data pool item identifier has an illegal value, then no action is taken other
 * than generating an event of type EVT_ILLEGAL_DP_ACCESS.  
 * @param id the data identifier of the data pool item to be set
 * @param newValue the new value to be set
 */
static void setIntegerValue(void *obj, TD_DataPoolId id, TD_Integer newValue)
{
    DC_SampleFullDataPool *This = DC_SAMPLEFULLDATAPOOL(obj);
    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);

    assert(id <= This->maxParId);           
    assert(This->type[id] == TD_IntegerCode);
 
    if (id > This->maxParId) {
        dc_erc->create(dc_er, obj, EVT_ILLEGAL_DP_ACCESS);
        return;
    }
    if (This->type[id] != TD_IntegerCode) {
        dc_erc->create(dc_er, obj, EVT_ILLEGAL_DP_ACCESS);
        return;
    }
    (*(TD_Integer*)This->pValue[id]) = newValue;      

    ObsClockClass *occ = OBSCLOCK_GET_CLASS(This->pObsClock); 
    This->timeStamp[id] = occ->getTime(This->pObsClock);        

    if (This->valid[id]) {
        (*(TD_Integer*)This->pBackUpValue[id]) = newValue;        
    }
}

/**
 * Getter method for the value of a real-typed data pool item.
 * This method implements the <i>copy link</i>
 * mechanism for real-valued data. 
 * If the validity status of the data pool item is "not valid", then the
 * back up value of the data pool item is returned.
 * @param id the data identifier of the data pool item to be read
 * @return the value of the data with identifier id
 */
static TD_Float getFloatValue(void *obj, TD_DataPoolId id)
{
    DC_SampleFullDataPool *This = DC_SAMPLEFULLDATAPOOL(obj);
    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);

    assert(id <= This->maxParId);           
    assert(This->type[id] == TD_FloatCode);
 
    if (id > This->maxParId) {
        dc_erc->create(dc_er, obj, EVT_ILLEGAL_DP_ACCESS);
        return (TD_Float)0;
    }
    if (This->type[id] != TD_FloatCode) {
        dc_erc->create(dc_er, obj, EVT_ILLEGAL_DP_ACCESS);
        return (TD_Float)0;
    }
    if (This->valid[id]) {
        return (*(TD_Float*)This->pValue[id]);
    } else {
        return (*(TD_Float*)This->pBackUpValue[id]);
    }
   
}

/**
 * Getter method for the value of an integer-typed data pool item.
 * This method implements the <i>copy link</i>
 * mechanism for integer-valued data.   
 * If the validity status of the data pool item is "not valid", then the
 * back up value of the data pool item is returned.
 * @param id the data identifier of the data pool item to be read
 * @return the value of the data with identifier id
 */
static TD_Integer getIntegerValue(void *obj, TD_DataPoolId id)
{
    DC_SampleFullDataPool *This = DC_SAMPLEFULLDATAPOOL(obj);
    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);

    assert(id <= This->maxParId);           
    assert(This->type[id] == TD_IntegerCode);
 
    if (id > This->maxParId) {
        dc_erc->create(dc_er, obj, EVT_ILLEGAL_DP_ACCESS);
        return (TD_Integer)0;
    }
    if (This->type[id] != TD_IntegerCode) {
        dc_erc->create(dc_er, obj, EVT_ILLEGAL_DP_ACCESS);
        return (TD_Integer)0;
    }
    if (This->valid[id]) {
        return (*(TD_Integer*)This->pValue[id]);
    } else {
        return (*(TD_Integer*)This->pBackUpValue[id]);
    }
   
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
    DC_SampleFullDataPool *This = DC_SAMPLEFULLDATAPOOL(obj);
    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);

    assert(id <= This->maxParId);           
    assert(This->type[id] == TD_FloatCode);
 
    if (id > This->maxParId) {
        dc_erc->create(dc_er, obj, EVT_ILLEGAL_DP_ACCESS);
        return This->pDefaultFloat;
    }
    if (This->type[id] != TD_FloatCode) {
        dc_erc->create(dc_er, obj, EVT_ILLEGAL_DP_ACCESS);
        return This->pDefaultFloat;
     }
    return ((TD_Float*)This->pValue[id]);
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
    DC_SampleFullDataPool *This = DC_SAMPLEFULLDATAPOOL(obj);
    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);

    assert(id <= This->maxParId);           
    assert(This->type[id] == TD_IntegerCode);
 
    if (id > This->maxParId) {
        dc_erc->create(dc_er, obj, EVT_ILLEGAL_DP_ACCESS);
        return This->pDefaultInt;
    }
    if (This->type[id] != TD_IntegerCode) {
         dc_erc->create(dc_er, obj, EVT_ILLEGAL_DP_ACCESS);
        return This->pDefaultInt;
    }
    return ((TD_Integer*)This->pValue[id]);
}

/**
 * Getter method for a <i>data item</i> that encapsulates a
 * data pool item. This method implements the <i>data item link</i>
 * mechanism.
 * If the validity status of the data pool item is "not valid", then the
 * data item returned by this method is dynamically reconfigured to point to
 * back up value of the data pool item.
 * @see DC_DataItem
 * @param id the data identifier of the data pool item to be read
 * @return the <code>DC_DataItem</code> item encapsulating the data
 * pool item with identifier id
 */
static DC_DataItem* getDataItem(void *obj, TD_DataPoolId id)
{
    DC_SampleFullDataPool *This = DC_SAMPLEFULLDATAPOOL(obj);
    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
    DataPoolClass *dpc = DATAPOOL_GET_CLASS(obj);

    assert(id <= This->maxParId);           
    assert(This->type[id] != -1);
 
    if (id > This->maxParId) {
        dc_erc->create(dc_er, obj, EVT_ILLEGAL_DP_ACCESS);
        return dpc->getDataItem(obj, id);
    }
    if (This->type[id] == -1) {
        dc_erc->create(dc_er, obj, EVT_ILLEGAL_DP_ACCESS);
        return dpc->getDataItem(obj, id);
    }
    return (DC_DataItem*)This->pDataItem[id];
}

/**
 * Return the time stamp of a data pool item.
 * The time stamp of a data pool item is set by the setter
 * method when the item value is updated. Note that it the data pool item is
 * accessed using its pointer or its data item, then the time stamp is not
 * updated.
 * @param id the data identifier of the data whose time stamp is sought
 * @return the time stamp of the data with identifier id
 */
static TD_ObsTime getTimeStamp(void *obj, TD_DataPoolId id)
{
    DC_SampleFullDataPool *This = DC_SAMPLEFULLDATAPOOL(obj);
    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
    DataPoolClass *dpc = DATAPOOL_GET_CLASS(obj);

    assert(id <= This->maxParId);           
    assert(This->type[id] != -1);
 
    if (id > This->maxParId) {
        dc_erc->create(dc_er, obj, EVT_ILLEGAL_DP_ACCESS);
        return dpc->getTimeStamp(obj, id);
    }
    if (This->type[id] == -1) {
        dc_erc->create(dc_er, obj, EVT_ILLEGAL_DP_ACCESS);
        return dpc->getTimeStamp(obj, id);
    }
    return This->timeStamp[id];
}

/**
 * Return the validity status of a data pool item.
 * The value that is returned is the value that is set with method
 * <code>setValidityStatus</code>. 
 * @see #setValidityStatus
 * @param id the data identifier of the data pool item
 * @return true if the data pool item is valid, false otherwise
 */
static bool isValid(void *obj, TD_DataPoolId id)
{
    DC_SampleFullDataPool *This = DC_SAMPLEFULLDATAPOOL(obj);
    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
    DataPoolClass *dpc = DATAPOOL_GET_CLASS(obj);

    assert(id <= This->maxParId);               
    assert(This->type[id] != -1);
 
    if (id > This->maxParId) {
        dc_erc->create(dc_er, obj, EVT_ILLEGAL_DP_ACCESS);
        return dpc->isValid(obj, id);
    }
    if (This->type[id] == -1) {
        dc_erc->create(dc_er, obj, EVT_ILLEGAL_DP_ACCESS);
        return dpc->isValid(obj, id);
    }
    return This->valid[id];
}

/**
 * Set the validity status of a data pool item.
 * If the data pool item identifier has an out-of-range value, then no action is taken other
 * than generating an event of type EVT_ILLEGAL_DP_ACCESS. 
 * @param id the data identifier of the data pool item
 * @param newValidityStatus the new validity status
 */
static void setValidityStatus(void *obj, TD_DataPoolId id, bool newValidityStatus)
{
    DC_SampleFullDataPool *This = DC_SAMPLEFULLDATAPOOL(obj);
    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);

    assert(id <= This->maxParId);       
    assert(This->type[id] != -1);
 
    if (id > This->maxParId) {
        dc_erc->create(dc_er, obj, EVT_ILLEGAL_DP_ACCESS);
        return;
    }

    // change from valid to not valid
    if (This->valid[id] && !newValidityStatus) {
        // make the data item point to the backup value
        DC_SettableDataItem_setIntegerVariable(This->pDataItem[id], 
                                              (TD_Integer*)This->pBackUpValue[id]);  
    }

    // change from not valid to valid
    if (!This->valid[id] && newValidityStatus) {
        // make the data item point to the primary value
        DC_SettableDataItem_setIntegerVariable(This->pDataItem[id], 
                                              (TD_Integer*)This->pValue[id]);
    }
 
    This->valid[id] = newValidityStatus;
}

/**
 * Get the monitoring profile for a data pool item.
 * The component that is returned by this method is the component that is set loaded
 * with method <code>setMonitoringProfile</code>.
 * @see #setMonitoringProfile
 * @param id the identifier of the data pool item
 * @return the monitoring profile
 */
static MonitoringProfile* getMonitoringProfile(void *obj, TD_DataPoolId id)
{
    DC_SampleFullDataPool *This = DC_SAMPLEFULLDATAPOOL(obj);
    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
    DataPoolClass *dpc = DATAPOOL_GET_CLASS(obj);

    assert(id <= This->maxParId);       
    assert(This->type[id] != -1);
 
    if (id > This->maxParId) {
        dc_erc->create(dc_er, obj, EVT_ILLEGAL_DP_ACCESS);
        return dpc->getMonitoringProfile(obj, id);
    }
    if (This->type[id] == -1) {
        dc_erc->create(dc_er, obj, EVT_ILLEGAL_DP_ACCESS);
        return dpc->getMonitoringProfile(obj, id);
    }
    return This->pMonitoringProfile[id];
}

/**
 * Set the monitoring profile for a data pool item.
 * If the data pool item identifier has an illegal value, then no action is taken other
 * than generating an event of type EVT_ILLEGAL_DP_ACCESS.  
 * @see #getMonitoringProfile
 * @param id the identifier of the data pool item
 * @param pMonitoringProfile the monitoring profile
 */
static void setMonitoringProfile(void *obj, TD_DataPoolId id,
                                 MonitoringProfile *pMonProf)
{
    DC_SampleFullDataPool *This = DC_SAMPLEFULLDATAPOOL(obj);
    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);

    assert(pMonProf != pNULL);
    assert(id <= This->maxParId);           
    assert(This->type[id] != -1);
 
    if (id > This->maxParId) {
        dc_erc->create(dc_er, obj, EVT_ILLEGAL_DP_ACCESS);
        return;
    }
    if (This->type[id] == -1) {
        dc_erc->create(dc_er, obj, EVT_ILLEGAL_DP_ACCESS);
        return;
    }

    This->pMonitoringProfile[id] = pMonProf;
}

/**
 * Get the recovery action for a data pool item.
 * The component that is returned by this method is the component that is set loaded
 * with method <code>setRecoveryAction</code>.
 * @see #setRecoveryAction
 * @param id the identifier of the data pool item
 * @return the monitoring profile
 */
static RecoveryAction* getRecoveryAction(void *obj, TD_DataPoolId id)
{
    DC_SampleFullDataPool *This = DC_SAMPLEFULLDATAPOOL(obj);
    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
    DataPoolClass *dpc = DATAPOOL_GET_CLASS(obj);

    assert(id <= This->maxParId);           
    assert(This->type[id] != -1);
 
    if (id > This->maxParId) {
        dc_erc->create(dc_er, obj, EVT_ILLEGAL_DP_ACCESS);
        return dpc->getRecoveryAction(obj, id);
    }
    if (This->type[id] == -1) {
        dc_erc->create(dc_er, obj, EVT_ILLEGAL_DP_ACCESS);
        return dpc->getRecoveryAction(obj, id);
    }
    return This->pRecoveryAction[id];
}

/**
 * Set the recovery action for a data pool item.
 * If the data pool item identifier has an illegal value, then no action is taken other
 * than generating an event of type EVT_ILLEGAL_DP_ACCESS.  
 * @see #getRecoveryAction
 * @param id the identifier of the data pool item
 * @param pRcoveryAction the recovery action
 */
static void setRecoveryAction(void *obj, TD_DataPoolId id, 
                              RecoveryAction *pRecAct)
{
    DC_SampleFullDataPool *This = DC_SAMPLEFULLDATAPOOL(obj);
    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);

    assert(pRecAct != pNULL);
    assert(id <= This->maxParId);               
    assert(This->type[id] != -1);
 
    if (id > This->maxParId) {
        dc_erc->create(dc_er, obj, EVT_ILLEGAL_DP_ACCESS);
        return;
    }
    if (This->type[id] == -1) {
        dc_erc->create(dc_er, obj, EVT_ILLEGAL_DP_ACCESS);
        return;
    }

    This->pRecoveryAction[id] = pRecAct;
}

/**
 * Iteration method that resets the iteration and returns the lowest
 * indentifier of the items in the data pool.
 * @see DataPool#firstIdentifier
 * @return the identifier of the first data pool item in the iteration
 */
static TD_DataPoolId firstIdentifier(void *obj)
{
    DC_SampleFullDataPool *This = DC_SAMPLEFULLDATAPOOL(obj);

    assert(This->pValue != pNULL);
    This->iterationCounter = 0;
    while ((This->pValue[This->iterationCounter] == pNULL) &&
           (This->iterationCounter < This->maxParId)) {
           This->iterationCounter++;
    }

    return This->iterationCounter;
}

/**
 * Iteration method that returns the next identifier in an iteration.
 * @see DataPool#firstIdentifier
 * @return the identifier of the next data pool item in the iteration
 */
static TD_DataPoolId nextIdentifier(void *obj)
{
    DC_SampleFullDataPool *This = DC_SAMPLEFULLDATAPOOL(obj);

    assert(This->pValue != pNULL);
    This->iterationCounter++;
    while ((This->pValue[This->iterationCounter] == pNULL) && 
           (This->iterationCounter < This->maxParId)) {
           This->iterationCounter++;
    }

    return This->iterationCounter;
}

/**
 * Iteration method that returns the next identifier in an iteration.
 * @see DataPool#firstIdentifier
 * @return true if the iteration has completed, false otherwise
 */
static bool isLastIdentifier(void *obj)
{ 
    DC_SampleFullDataPool *This = DC_SAMPLEFULLDATAPOOL(obj);

    assert(This->pValue != pNULL);
    return (This->iterationCounter > This->maxParId);
}

/**
 * Method implementing the type checking service to check whether a
 * data pool item is real-typed.
 * @see DataPool#isFloat
 * @see id the identifier of the data pool item
 * @return true if the id is the identifier of a real-valued data item, 
 * false otherwise
 */
static bool isFloat(void *obj, TD_DataPoolId id)
{
    DC_SampleFullDataPool *This = DC_SAMPLEFULLDATAPOOL(obj);
    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
    DataPoolClass *dpc = DATAPOOL_GET_CLASS(obj);

    assert(id <= This->maxParId);           
    assert(This->type[id] != -1);
 
    if (id > This->maxParId) {
        dc_erc->create(dc_er, obj, EVT_ILLEGAL_DP_ACCESS);
        return dpc->isFloat(obj, id);
    }
    if (This->type[id] == -1) {
        dc_erc->create(dc_er, obj, EVT_ILLEGAL_DP_ACCESS);
        return dpc->isFloat(obj, id);
    }

    return (This->type[id] == TD_FloatCode);
}

/**
 * Method implementing the type checking service to check whether a
 * data pool item is integer-typed.
 * @see DataPool#isInteger
 * @see id the identifier of the data pool item
 * @return true if the id is the identifier of a real-valued data item, 
 * false otherwise
 */
static bool isInteger(void *obj, TD_DataPoolId id)
{
    DC_SampleFullDataPool *This = DC_SAMPLEFULLDATAPOOL(obj);
    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
    DataPoolClass *dpc = DATAPOOL_GET_CLASS(obj);

    assert(id <= This->maxParId);       
    assert(This->type[id] != -1);
 
    if (id > This->maxParId) {
        dc_erc->create(dc_er, obj, EVT_ILLEGAL_DP_ACCESS);
        return dpc->isInteger(obj, id);
    }
    if (This->type[id] == -1) {
        dc_erc->create(dc_er, obj, EVT_ILLEGAL_DP_ACCESS);
        return dpc->isInteger(obj, id);
    }
    return (This->type[id] == TD_IntegerCode);
}

/**
 * Implement the data pool reset service.
 * The validity status of all data pool item is reset to the value it
 * had at the time the data pool component was created.
 * @see #isValid
 */
static void reset(void *obj)
{
    DataPoolClass *dpc = DATAPOOL_GET_CLASS(obj);

    for (TD_DataPoolId i=dpc->firstIdentifier(obj); 
             !dpc->isLastIdentifier(obj); 
                   i=dpc->nextIdentifier(obj)) {
        dpc->setValidityStatus(obj, i, true);
    }
}

/**
 * Perform a class-specific configuration check. The following checks are performed: <ul>
 * <li>All monitoring profiles have been loaded</li>
 * <li>All recovery actions have been loaded</li>
 * <li>The OBS Clock plug-in component has been loaded</li>
 * </ul>
 * @return true if the data pool object is configured, false otherwise
 */
static bool isObjectConfigured(void *obj)
{
   DataPoolClass *dpc = GET_CLASS(TYPE_DATAPOOL);
   DC_SampleFullDataPool *This = DC_SAMPLEFULLDATAPOOL(obj);

   // Check configuration of super object
   if (!CC_ROOTOBJECT_CLASS(dpc)->isObjectConfigured(obj) || 
       (This->pObsClock == pNULL)) {
       return NOT_CONFIGURED;
   }

   // Now get the obj-related DataPoolClass struct
   dpc = DATAPOOL_GET_CLASS(obj);
   for (TD_DataPoolId i=dpc->firstIdentifier(obj); 
            !dpc->isLastIdentifier(obj); 
                i=dpc->nextIdentifier(obj)) {

        if ((dpc->getMonitoringProfile(obj, i) == pNULL) || 
            (dpc->getRecoveryAction(obj, i) == pNULL)) {
            return false;
        }
   }

   return true;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
   DC_SampleFullDataPool *This = DC_SAMPLEFULLDATAPOOL(obj);

   This->pDefaultFloat = g_malloc(sizeof(TD_Float));
   *This->pDefaultFloat = (TD_Float)0;
   This->pDefaultInt = g_malloc(sizeof(TD_Integer));
   *This->pDefaultInt = (TD_Integer)0;

   This->iterationCounter = 0;
   unsigned int const numberOfRealPar = 4;
   unsigned int const numberOfIntPar = 4;
   This->size = numberOfRealPar*sizeof(TD_Float) + numberOfIntPar*sizeof(TD_Integer);
   This->maxParId = 11;
   This->value = (unsigned char*)g_malloc(sizeof(double)*((This->size/sizeof(double))+1));
   This->pValue = g_malloc((This->maxParId+1)*sizeof(unsigned char*));         
   This->backUpValue = g_malloc(sizeof(unsigned char)*This->size);
   This->pBackUpValue = g_malloc((This->maxParId+1)*sizeof(unsigned char*)); 
   This->pObsClock = pNULL;
   This->timeStamp = g_malloc(sizeof(TD_ObsTime)*(This->maxParId+1));
   This->valid = g_malloc(sizeof(bool)*(This->maxParId+1));   
   This->pDataItem = g_malloc((This->maxParId+1)*sizeof(DC_SettableDataItem*));    
   This->pMonitoringProfile = g_malloc((This->maxParId+1)*sizeof(MonitoringProfile*));       
   This->pRecoveryAction = g_malloc((This->maxParId+1)*sizeof(RecoveryAction*));       
   This->type = g_malloc(sizeof(char)*(This->maxParId+1));                 

   for (TD_DataPoolId i=0; i<This->size; i++)  {
        This->value[i] = 0;  
        This->backUpValue[i] = 0;          
   }

   for (TD_DataPoolId i=0; i<=This->maxParId; i++)  {
        This->pValue[i] = pNULL;         
        This->pBackUpValue[i] = pNULL;          
        This->timeStamp[i] = 0;               
        This->valid[i] = true;                
        This->pDataItem[i] = pNULL;   
        This->pMonitoringProfile[i] = pNULL;          
        This->pRecoveryAction[i] = pNULL;             
        This->type[i] = -1;                           
   }

 
   // In order to access variable concisely and efficiently below.
   char* const type = This->type;
   unsigned char* const value = This->value;
   DC_SettableDataItem** const pDataItem = This->pDataItem;    
   unsigned char** const pValue = This->pValue;
   unsigned char** const pBackUpValue = This->pBackUpValue;      
   const TD_DataPoolId maxParId = This->maxParId;
   unsigned char* const backUpValue = This->backUpValue;

   unsigned int offset = 0;           
   type[1] = TD_IntegerCode;  
   type[2] = TD_FloatCode;  
   type[4] = TD_IntegerCode;  
   type[5] = TD_FloatCode;  
   type[7] = TD_IntegerCode;  
   type[8] = TD_FloatCode;  
   type[10] = TD_IntegerCode;  
   type[11] = TD_FloatCode;  

   // Store the TD_Float values in the first part of the array
   for (TD_DatabaseId i=0; i<=maxParId; i++)  {
       if (type[i] == TD_FloatCode) {
          pValue[i] = value + offset;                                  
          pBackUpValue[i] = backUpValue + offset;         
          pDataItem[i] = DC_SettableDataItem_new(pValue[i], DI_FLOAT);     
          offset = offset + sizeof(TD_Float);                     
       } 
   }

   // Now ensure that offset is aligned with a TD_Integer
   unsigned int temp = (offset/sizeof(TD_Integer));
   if (temp*sizeof(TD_Integer) < offset) {
      offset = (temp+1)*sizeof(TD_Integer);
   }

   // Store the TD_Integer values in the second part of the array
   for (TD_DatabaseId i=0; i<=maxParId; i++)  {
       if (type[i] == TD_IntegerCode) {
          pValue[i] = value + offset;                                  
          pBackUpValue[i] = backUpValue + offset;         
          pDataItem[i] = DC_SettableDataItem_new(pValue[i], DI_INT);     
          offset = offset + sizeof(TD_Integer);                     
       } 
   }
       

   CC_RootObject_setClassId((CC_RootObject*)obj, ID_SAMPLEFULLDATAPOOL);
}

DC_SampleFullDataPool* DC_SampleFullDataPool_new(void)
{
    Object *obj = object_new(TYPE_DC_SAMPLEFULLDATAPOOL);
    return (DC_SampleFullDataPool*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    DC_SampleFullDataPoolClass *dc_sfdpc = DC_SAMPLEFULLDATAPOOL_CLASS(oc);
    dc_sfdpc->setRecoveryAction = setRecoveryAction;
    dc_sfdpc->setMonitoringProfile = setMonitoringProfile;

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

    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_SAMPLEFULLDATAPOOL,
    .parent = TYPE_DATAPOOL,
    .instance_size = sizeof(DC_SampleFullDataPool),
    .abstract = false,
    .class_size = sizeof(DC_SampleFullDataPoolClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_SampleFullDataPool_register(void)
{
    type_register_static(&type_info);
}
