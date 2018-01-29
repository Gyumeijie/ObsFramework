//
//
// CC_ManoeuvreManager.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "../Event/DC_EventRepository.h"
#include "../Base/CC_RootObject.h"
#include "CC_ManoeuvreManager.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void CC_ManoeuvreManager_reset(CC_ManoeuvreManager *This)
{
    assert(This->pManList != pNULL);

    CC_ManoeuvreManagerClass *cc_mmc = CC_MANOEUVREMANAGER_GET_CLASS(This);
    for (unsigned int i=0; i<This->manListSize; i++) {
        if (This->pManList[i] != pNULL) {
           cc_mmc->abort(This, This->pManList[i]);
        }
    }

    assert(This->manCounter == 0);
}

void CC_ManoeuvreManager_setPendingManoeuvreListSize
(
    CC_ManoeuvreManager *This, 
    const unsigned int listSize
)
{
    assert(This->manListSize == 0);  // should not be called more than once
    assert(listSize > 0);
    This->manListSize = listSize;
    This->pManList = g_malloc(listSize*sizeof(Manoeuvre*));

    for (unsigned int i=0; i<listSize; i++) {
        This->pManList[i] = pNULL;
    }
}

unsigned int CC_ManoeuvreManager_getPendingManoeuvreListSize
(
    CC_ManoeuvreManager *This
)
{
    assert(This->manListSize > 0);
    return This->manListSize;
}

unsigned int CC_ManoeuvreManager_getPendingManoeuvres(CC_ManoeuvreManager *This)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(This);

    assert(cc_roc->isObjectConfigured(This));
    return This->manCounter;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Unload a manoeuvre. The manoeuvre is removed from the list of
 * pending manoeuvres and will no longer be considered for execution.
 * The "inUse" status of the manoeuvre is changed to: "manoeuvre not in use".
 * <p>
 * A pseudo-code implementation for this method is as follows: <PRE>
 *   . . .       // remove manoeuvre from list of pending manoeuvres
 *   pManoeuvre->inUse(false)   // mark manoeuvre as "not in use"
 *   createEventReport(EVT_MAN_UNLOADED);
 *   return; </PRE>
 * The <code>manId</code> parameter in the above pseudo-code is a manoeuvre
 * identifier. This class uses the class identifier of the manoeuvre
 * component as identifier.
 * @see TD_EventType
 * @param pManoeuvre the manoeuvre that is loaded
 */
static void unload(void *obj, Manoeuvre *pManoeuvre)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    CC_ManoeuvreManager *This = CC_MANOEUVREMANAGER(obj);

    assert(cc_roc->isObjectConfigured(obj));
    assert(pManoeuvre != pNULL);
    assert(This->manCounter > 0);
    assert(Manoeuvre_isInUse(pManoeuvre));
    assert(!Manoeuvre_isExecuting(pManoeuvre));

    // Remove manoeuvre from the list of pending telecommands
    for (unsigned int i=0; i<This->manListSize; i++) {
        if (This->pManList[i] == pManoeuvre) {
            Manoeuvre_setInUse(pManoeuvre, MAN_NOT_IN_USE);
            This->pManList[i] = pNULL;
            This->manCounter--;

            DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
            DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
            dc_erc->create(dc_er, (CC_RootObject*)pManoeuvre, EVT_MAN_UNLOADED);
            return;
        }
    }

    // This point shall never be reached
    assert(false);
}

/**
 * Load a manoeuvre. When a manoeuvre is loaded, it is inserted in the list
 * of pending manoeuvres and is then considered for execution by method
 * <code>activate</code>. The manoeuvre remains loaded until it has terminated
 * execution or is aborted.
 * <p>
 * If the list of pending manoeuvres is already full, no action is taken
 * other than the creation of an event report to record the attempted
 * manoeuvre load.
 * <p>
 * The manoeuvre manager creates an event whenever a new manoeuvre is loaded.
 * <p>
 * A pseudo-code implementation for this method is as follows: <PRE>
 *   if(list of pending manoeuvres is full)    // the manoeuvre list is full
 *   {   createEventReport(EVT_MAN_LIST_FULL);
 *       return;
 *   }
 *   . . .       // insert manoeuvre in list of pending manoeuvres
 *   createEventReport(EVT_MAN_LOADED);
 *   return; </PRE>
 * The <code>manId</code> parameter in the above pseudo-code is a manoeuvre
 * identifier. This class uses the class identifier of the manoeuvre
 * component as its identifier.
 * @see TD_EventType
 * @param pManoeuvre the manoeuvre that is loaded
 */
static void load(void *obj, Manoeuvre *pManoeuvre)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    CC_ManoeuvreManager *This = CC_MANOEUVREMANAGER(obj);
    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);

    assert(cc_roc->isObjectConfigured(obj));

    // Check whether list of pending manoeuvres is full
    if (This->manCounter == This->manListSize) {
        dc_erc->create(dc_er, (CC_RootObject*)pManoeuvre, EVT_MAN_LIST_FULL);
        return;
    }

    // Insert manoeuvre in the list of pending manoeuvres
	for (unsigned int i=0; i<This->manListSize; i++) {
        if (This->pManList[i] == pNULL) {
            This->pManList[i] = pManoeuvre;
            This->manCounter++;
            dc_erc->create(dc_er, (CC_RootObject*)pManoeuvre, EVT_MAN_LOADED);
            return;
        }
	}

    // This point shall never be reached
    assert(false);
}

/**
 * Abort a manoeuvre.
 * An <CODE>abort(void)</CODE> request is sent to the manoeuvre and the
 * manoeuvre is then unloaded.
 * If the argument manoeuvre is not currently loaded, no action is taken.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *   for(all manoeuvre m in the list of pending manoeuvres)
 *     if(m==pManoeuvre) {
 *          pManoeuvre->abort(void);
 *          pManoeuvre->setInUse(false);
 *          . . . // delete pManoeuvre from list of pending manoeuvres);
 *          createEventReport(EVT_MAN_UNLOADED);
 *      }
 *   return; </PRE>
 * @see TD_EventType
 * @see Manoeuvre#abort
 * @param pManoeuvre the manoeuvre to be aborted
 */
static void not_builtin_abort(void *obj, Manoeuvre *pManoeuvre)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    CC_ManoeuvreManager *This = CC_MANOEUVREMANAGER(obj);

    assert((cc_roc->isObjectConfigured(obj)) && (pManoeuvre != pNULL));

    for (unsigned int i=0; i<This->manListSize; i++) {
        if (This->pManList[i] == pManoeuvre) {
            Manoeuvre_abort(pManoeuvre);
            Manoeuvre_setInUse(pManoeuvre, MAN_NOT_IN_USE);
            This->pManList[i] = pNULL;
            This->manCounter--;

            DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
            DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
            dc_erc->create(dc_er, (CC_RootObject*)pManoeuvre, EVT_MAN_UNLOADED);
            return;
        }
    }

    // This point shall never be reached
    assert(false);
}

/**
 * Advance execution of pending manoeuvres.
 * When this method is called, the manoeuvre manager goes through the list
 * of pending manoeuvres and processes them in sequence.
 * This method would typically be called by an external scheduler.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *   for(all manoeuvres m in the list of pending manoeuvres)
 *      if((!m->isExecuting(void)) && (m->canStart(void))) {
 *          m->initialize(void);
 *          m->doContinue(void);
 *      }
 *      else if((m->isExecuting(void)) && (m->canContinue(void)))
 *          m->doContinue(void);
 *      else if((m->isExecuting(void)) && (!m->canContinue(void)))
 *          m->abort(void);
 *
 *      if(m->isFinished(void))
 *          m->terminate(void);
 *          unload(m);
 *      } </PRE>
 */
static void activate(void *obj)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    CC_ManoeuvreManager *This = CC_MANOEUVREMANAGER(obj);
    CC_ManoeuvreManagerClass *cc_mmc = CC_MANOEUVREMANAGER_GET_CLASS(This);

    assert(cc_roc->isObjectConfigured(obj));

    for (unsigned int i=0; i<This->manListSize; i++) {
        Manoeuvre *pM = This->pManList[i];

		if (pM == pNULL) continue;

        ManoeuvreClass *mc = MANOEUVRE_GET_CLASS(pM);
	    if (!Manoeuvre_isExecuting(pM)) {
			if (mc->canStart(pM)) {
				mc->initialize(pM);
				Manoeuvre_doContinue(pM);
			}
		} else if (mc->isFinished(pM)) {
			Manoeuvre_terminate(pM);
			cc_mmc->unload(This, pM);
		} else if (mc->canContinue(pM)) {
			Manoeuvre_doContinue(pM);
		} else {
			cc_mmc->abort(This, pM);
			cc_mmc->unload(This, pM);
		}
    }
}

/**
 * Perform a class-specific configuration check: verify that the size of the
 * pending manoeuvre list has a legal value.
 * @return true if the telecommand manager is configured, false otherwise.
 */
static bool isObjectConfigured(void *obj)
{
    CC_RootObjectClass *cc_roc = GET_CLASS(TYPE_CC_ROOTOBJECT);
    CC_ManoeuvreManager *This = CC_MANOEUVREMANAGER(obj);
    
    return ((cc_roc->isObjectConfigured(obj)) && 
            (This->manListSize > 0));
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    CC_ManoeuvreManager *This = CC_MANOEUVREMANAGER(obj);
    This->pManList = pNULL;
    This->manListSize = 0;
    This->manCounter = 0;

    CC_RootObject_setClassId((CC_RootObject*)obj, ID_MANOEUVREMANAGER);
}

CC_ManoeuvreManager* CC_ManoeuvreManager_new(void)
{
    Object *obj = object_new(TYPE_CC_MANOEUVREMANAGER);
    return (CC_ManoeuvreManager*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    CC_ManoeuvreManagerClass *cc_mmc = CC_MANOEUVREMANAGER_CLASS(oc);
    cc_mmc->unload = unload;
    cc_mmc->load = load;
    // In order to remove conflicting types for built-in function ‘abort’ warining 
    cc_mmc->abort = not_builtin_abort;
    cc_mmc->activate = activate;

    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_CC_MANOEUVREMANAGER,
    .parent = TYPE_CC_ROOTOBJECT,
    .instance_size = sizeof(CC_ManoeuvreManager),
    .abstract = false,
    .class_size = sizeof(CC_ManoeuvreManagerClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void CC_ManoeuvreManager_register(void)
{
    type_register_static(&type_info);
}
