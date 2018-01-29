//
//
// DC_DataPoolMonitor.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "../FDIR/MonitoringProfile.h"
#include "../FDIR/RecoveryAction.h"
#include "DataPool.h"
#include "DC_DataPoolMonitor.h"



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Encapsulate an <i>execution check</i> that always returns
 * "can execute".
 * @see ConditionalPunctualAction#doAction
 * @return always returns true.
 */
static bool canExecute(void *obj)
{
    return true;
}

/**
 * Perform the monitoring action on all the items in the data pool.
 * The data pool is loaded from the <code>CC_RootObject</code>.
 * A pseudo-code implementation of this method is as follows: <pre>
 *   pDataPool = CC_RootObject::getDataPool(void);
 *   for(all items p in pDataPool)
 *	 {  get the value v of p
 *	    get the monitoring profile m associated to p in pDataPool
 *	    pass the value v through the monitoring profile m
 *	    if(monitoring violation detected)
 *      {    set the validity status of p to "not valid"
 *           get the recovery action r associated to p in pDataPool
 *           execute r
 *      }
 *    }	</pre>
 * This method always returns: "ACTION_SUCCESS"
 * @see ConditionalPunctualAction#doAction
 * @return the outcome code of the punctual action
 */
static TD_ActionOutcome doConditionalAction(void *obj)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    assert(cc_roc->isObjectConfigured(obj));

    DataPool *dp = CC_RootObject_getDataPool();
    DataPoolClass *dpc = DATAPOOL_GET_CLASS(dp);

    TD_DataPoolId item = dpc->firstIdentifier(dp);

    do {
         bool invalid;

         MonitoringProfile *mp = dpc->getMonitoringProfile(dp, item);

         if (dpc->isFloat(dp, item)) {
             TD_Float value = dpc->getFloatValue(dp, item);
             invalid = MonitoringProfile_floatDeviatesFromProfile(mp, value);
         } else {
             TD_Integer value = dpc->getIntegerValue(dp, item);
             invalid = MonitoringProfile_integerDeviatesFromProfile(mp, value);
         }
 
         if (invalid) {
             dpc->setValidityStatus(dp, item,NOT_VALID);
             RecoveryAction *ra = dpc->getRecoveryAction(dp, item);
             PunctualAction_execute((PunctualAction*)ra);
         }
 
         item = dpc->nextIdentifier(dp);
     } while (!dpc->isLastIdentifier(dp));

    return ACTION_SUCCESS;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    CC_RootObject_setClassId((CC_RootObject*)obj, ID_DATAPOOLMONITOR);
}

DC_DataPoolMonitor* DC_DataPoolMonitor_new(void)
{
    Object *obj = object_new(TYPE_DC_DATAPOOLMONITOR);
    return (DC_DataPoolMonitor*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    ConditionalPunctualActionClass *cpac = CONDITIONALPUNCTUALACTION_CLASS(oc);

    cpac->canExecute = canExecute;
    cpac->doConditionalAction = doConditionalAction;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_DATAPOOLMONITOR,
    .parent = TYPE_CONDITIONALPUNCTUALACTION,
    .instance_size = sizeof(DC_DataPoolMonitor),
    .abstract = false,
    .class_size = sizeof(DC_DataPoolMonitorClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_DataPoolMonitor_register(void)
{
    type_register_static(&type_info);
}
