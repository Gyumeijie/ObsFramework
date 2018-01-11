//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_ProfileList.c
//
// Version	1.3
// Date		15.08.03 (Version 1.0)
//          01.10.03 (Version 1.1)
//          08.10.03 (Version 1.2)
//          21.10.03 (Version 1.3)
// Author	R. Totaro
//
// Change Record:
//   Version 1.1: Replaced double and int with TD_Float and TD_Integer
//   Version 1.2: Fixed isObjectConfigured() it did not check that all the
//                profiles were loaded.
//   Version 1.3: loadMonitoringProfile() renamed setMonitoringProfile()

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "../Event/DC_EventRepository.h"
#include "../Base/CC_RootObject.h"
#include "DC_ProfileList.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_ProfileList_setListSize(DC_ProfileList *This, unsigned int listSize)
{

    assert(This->listSize==0 && listSize!=0);

    This->listSize = listSize;
    This->pList = g_malloc(sizeof(MonitoringProfile*)*listSize);

    unsigned int i;
    for (i=0; i<This->listSize; i++) {
        This->pList[i] = pNULL;
    }
}

unsigned int DC_ProfileList_getListSize(const DC_ProfileList *This)
{
	return This->listSize;
}

void DC_ProfileList_setMonitoringProfile
(
    DC_ProfileList *This, 
    unsigned int i,
    MonitoringProfile *item
)
{
    // Note that, being i unsigned, if i<listSize, then listSize must be >0!
	assert(i<This->listSize && item!=pNULL);

	if (i<This->listSize) {
		This->pList[i] = item;
    } else {
         DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
         DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
		 dc_erc->create(dc_er, (CC_RootObject*)This, EVT_ILLEGAL_MP);
    }
}

MonitoringProfile* DC_ProfileList_getMonitoringProfile
(
    const DC_ProfileList *This,
    unsigned int i
)
{
    // Note that, being i unsigned, if i<listSize, then listSize must be >0!
	assert(i < This->listSize);

    return This->pList[i];
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Version of method <CODE>doProfileCheck(void)</CODE> for monitored variables
 * of type TD_Integer. The logic of this method is the same as for the version
 * that takes a <code>TD_Float</code> argument.
 * @see #doProfileCheck
 */
static bool doProfileCheckForInteger(void *obj, TD_Integer value)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
	assert(cc_roc->isObjectConfigured(obj));

	bool retVal = false;
    unsigned int i;
    DC_ProfileList *This = DC_PROFILELIST(obj);
	for (i=0; i<This->listSize; i++) {
        MonitoringProfile* mp = This->pList[i];
		if (MonitoringProfile_integerDeviatesFromProfile(mp, value)) {
			retVal = true;
        }
	}

	return retVal;
}

/**
 * Pass the monitored value through all the monitoring profiles in the
 * list and report "devation from profile" if any of the profiles in
 * the list report "deviation from profile".
 * A pseudo-code implementation for this method is as follows: <PRE>
 *   flag = NO_MON_PROFILE_DEVIATION;
 *   for(all monitoring profiles p in the list)
 *   {  if( p->deviatesFromProfile(value) )
 *         flag = MON_PROFILE_DEVIATION;
 *   }
 *   return flag; </PRE>
 * Note that the monitored value is always passed through all
 * monitoring profiles in the list.
 * @param value the value of the monitored variable
 * @return true if the monitored variable deviates from the profile, 
 * false otherwise
 */
static bool doProfileCheckForFloat(void *obj, TD_Float value)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
	assert(cc_roc->isObjectConfigured(obj));

	bool retVal = false;
    unsigned int i;
    DC_ProfileList *This = DC_PROFILELIST(obj);
	for (i=0; i<This->listSize; i++) {
        MonitoringProfile* mp = This->pList[i];
		if (MonitoringProfile_floatDeviatesFromProfile(mp, value)) {
			retVal = true;
        }
	}

	return retVal;
}

/**
 * Perform a class-specific configuration check on the monitoring
 * profile: verify that the size of the list of monitoring profiles has
 * a value greater than zero and that all the entries in the list
 * have been loaded with monitoring profiles.
 * @return true if the monitoring profile is configured, false otherwise.
 */
static bool isObjectConfigured(void *obj)
{
    DC_ProfileList *This = DC_PROFILELIST(obj);

    MonitoringProfileClass *mpc = GET_CLASS(TYPE_MONITORINGPROFILE);
    if (!CC_ROOTOBJECT_CLASS(mpc)->isObjectConfigured(obj) || This->listSize==0) {
        return NOT_CONFIGURED;
    }

    unsigned int i;
    for (i=0; i<This->listSize; i++) {
        if (This->pList[i] == pNULL) {
            return NOT_CONFIGURED;
        }
    }

    return CONFIGURED;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    DC_ProfileList *This = DC_PROFILELIST(obj);

	CC_RootObject_setClassId((CC_RootObject*)obj, ID_PROFILELIST);
	This->listSize = 0;
	This->pList = pNULL;
}

DC_ProfileList* DC_ProfileList_new(void)
{
    return (DC_ProfileList*)object_new(TYPE_DC_PROFILELIST);
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    MonitoringProfileClass *mpc = MONITORINGPROFILE_CLASS(oc);
    mpc->doProfileCheckForInteger = doProfileCheckForInteger;
    mpc->doProfileCheckForFloat = doProfileCheckForFloat;

    CC_RootObjectClass *roc = CC_ROOTOBJECT_CLASS(oc);
    roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_PROFILELIST,
    .parent = TYPE_MONITORINGPROFILE,
    .instance_size = sizeof(DC_ProfileList),
    .abstract = false,
    .class_size = sizeof(DC_ProfileListClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_ProfileList_register(void)
{
    type_register_static(&type_info);
}
