//
//
// DC_BasicReconfigurer.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "../Event/DC_EventRepository.h"
#include "../Base/CC_RootObject.h"
#include "DC_BasicReconfigurer.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_BasicReconfigurer_setNumberOfConfigurations
(
    DC_BasicReconfigurer *This, 
    TD_Config nOfConfig
)
{
   assert(This->numberOfConfig == 0);  // should be called only once
   assert(nOfConfig > 0);

   This->numberOfConfig = nOfConfig;
   This->isHealthy = g_malloc(sizeof(bool)*nOfConfig);

   This->active = 0;
   for (TD_Config i=0; i<nOfConfig; i++) {
       This->isHealthy[i] = HEALTHY;
   }
}

void DC_BasicReconfigurer_setHealthStatus(DC_BasicReconfigurer *This, 
                                          TD_Config i, bool healthStatus)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(This);
	assert(cc_roc->isObjectConfigured(This));
    assert(i < This->numberOfConfig);

	if (i < This->numberOfConfig) {
		This->isHealthy[i] = healthStatus;
    } else {
        DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
        DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
		dc_erc->create(dc_er, (CC_RootObject*)This, EVT_ILLEGAL_CONFIG);
    }
}

bool DC_BasicReconfigurer_isConfigurationHealthy
(
    const DC_BasicReconfigurer *This, 
    TD_Config i
)
{
    assert(This->isHealthy != pNULL);
    assert(i < This->numberOfConfig);

    return This->isHealthy[i];
}

void DC_BasicReconfigurer_setActive(DC_BasicReconfigurer *This, 
                                    TD_Config activeConfig)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(This);
    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);


	assert(cc_roc->isObjectConfigured(This));
    assert(activeConfig < This->numberOfConfig);

	if (activeConfig >= This->numberOfConfig) {
		dc_erc->create(dc_er, (CC_RootObject*)This, EVT_ILLEGAL_CONFIG);
	} else if (This->active != activeConfig) {
		This->active = activeConfig;
		dc_erc->create(dc_er, (CC_RootObject*)This, EVT_RECONFIG);
	}
}

void DC_BasicReconfigurer_setEnabled(DC_BasicReconfigurer *This, bool enabled)
{
    This->enableStatus = enabled;
}

bool DC_BasicReconfigurer_isEnabled(const DC_BasicReconfigurer *This)
{
    return This->enableStatus;
}

TD_Config DC_BasicReconfigurer_getActive(const DC_BasicReconfigurer *This)
{
    return This->active;
}

TD_Config DC_BasicReconfigurer_getNumberOfConfigurations
(
    const DC_BasicReconfigurer *This
)
{
    return This->numberOfConfig;
}

void DC_BasicReconfigurer_reset(DC_BasicReconfigurer *This)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(This);
    assert(cc_roc->isObjectConfigured(This));

    This->active = 0;
    This->enableStatus = ENABLED;
    for (TD_Config i=0; i<This->numberOfConfig; i++) {
        This->isHealthy[i] = HEALTHY;
    }
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Perform a reconfiguration. If reconfigurations are enabled, then
 * one of the non-active but healthy configurations is made active
 * and the originally active configuration is marked "unhealthy". If
 * there are no available healthy configurations, nothing is done
 * beyond reporting the fact as an event.
 * If reconfigurations are disabled, nothing is done
 * beyond reporting the fact as an event.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *   if(reconfigurations are enabled) {  // compute new operational mode;
 *      if(there is a healthy non-active configuration H) {
 *          temp = activeConfiguration
 *          activeConfiguration = H;
 *          createEventReport(EVT_RECONFIG);
 *          setHealthStatus(temp, UNHEALTHY);
 *      } else
 *          createEventReport(EVT_RECONFIG_NO_HEALTHY)
 *   } else
 *      createEventReport(EVT_RECONFIG_DISABLED);</PRE>
 * The <code>classId</code> in the above code that is used as an event
 * parameter is the class identifier of the reconfigurer.
 */
static void reconfigure(void *obj)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
    DC_BasicReconfigurer *This = DC_BASICRECONFIGURER(obj);

	assert(cc_roc->isObjectConfigured(obj));

	if (DC_BasicReconfigurer_isEnabled(This)) {
		for (TD_Config i=0; i<This->numberOfConfig; i++) {
			if ((i != This->active) && 
                (DC_BasicReconfigurer_isConfigurationHealthy(This, i))) 
            {
				DC_BasicReconfigurer_setHealthStatus(This, This->active, NOT_HEALTHY);
				This->active = i;
				dc_erc->create(dc_er, (CC_RootObject*)This, EVT_RECONFIG);
				return;
			}
		}

		dc_erc->create(dc_er, (CC_RootObject*)This, EVT_RECONFIG_NO_HEALTHY);
	} else {
		dc_erc->create(dc_er, (CC_RootObject*)This, EVT_RECONFIG_DISABLED);
    }
}

/**
 * Perform a class-specific configuration check on a basic reconfigurer: verify
 * that the number of configurations is greater than zero.
 * @return true if the object is configured, false otherwise
 */
static bool isObjectConfigured(void *obj)
{
   CC_RootObjectClass *cc_roc = GET_CLASS(TYPE_CC_ROOTOBJECT);   
   DC_BasicReconfigurer *This = DC_BASICRECONFIGURER(obj);

   return ((cc_roc->isObjectConfigured(obj)) && 
           (This->numberOfConfig > 0));
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
   DC_BasicReconfigurer *This = DC_BASICRECONFIGURER(obj);

   This->numberOfConfig = 0;
   This->active = 0;
   This->enableStatus = ENABLED;
   This->isHealthy = pNULL;

   CC_RootObject_setClassId((CC_RootObject*)obj, ID_BASICRECONFIGURER);
}

DC_BasicReconfigurer* DC_BasicReconfigurer_new(void)
{
    Object *obj = object_new(TYPE_DC_BASICRECONFIGURER);
    return (DC_BasicReconfigurer*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    DC_BasicReconfigurerClass *dc_brc = DC_BASICRECONFIGURER_CLASS(oc);
    dc_brc->reconfigure = reconfigure;

    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_BASICRECONFIGURER,
    .parent = TYPE_CC_ROOTOBJECT,
    .instance_size = sizeof(DC_BasicReconfigurer),
    .abstract = false,
    .class_size = sizeof(DC_BasicReconfigurerClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_BasicReconfigurer_register(void)
{
    type_register_static(&type_info);
}
