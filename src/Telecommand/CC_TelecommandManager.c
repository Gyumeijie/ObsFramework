//
//
// CC_TelecommandManager.c
//
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "../Event/DC_EventRepository.h"
#include "../Base/CC_RootObject.h"
#include "../System/ObsClock.h"
#include "CC_TelecommandManager.h"
#include "TelecommandLoader.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void CC_TelecommandManager_reset(CC_TelecommandManager *This)
{
    assert(This->pTcList != pNULL);

    // In order access pTcList concisely below
    Telecommand** const pTcList = This->pTcList;    
    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
    TelecommandLoaderClass *tlc = TELECOMMANDLOADER_GET_CLASS(This->pTcLoader);
    for (unsigned int i=0; i<This->tcListSize; i++) {
        if (pTcList[i] != pNULL) {
            dc_erc->create(dc_er, (CC_RootObject*)pTcList[i], EVT_TC_ABORTED);
            tlc->release(This->pTcLoader, pTcList[i]);
            pTcList[i] = pNULL;
        }
    }

    This->tcCounter = 0;
}

void CC_TelecommandManager_setPendingTelecommandListSize
(
    CC_TelecommandManager *This, 
    unsigned int listSize
)
{
    assert(This->tcListSize == 0);  // should not be called more than once
    assert(listSize > 0);

    This->tcListSize = listSize;
    This->pTcList = g_malloc(listSize*sizeof(Telecommand*));

    for (unsigned int i=0; i<listSize; i++) {
        This->pTcList[i] = pNULL;
    }
}

unsigned int CC_TelecommandManager_getPendingTelecommandListSize
(
    CC_TelecommandManager *This
)
{
    assert(This->tcListSize > 0);

    return This->tcListSize;
}

unsigned int CC_TelecommandManager_getPendingTelecommands
(
    CC_TelecommandManager *This
)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(This);
    assert(cc_roc->isObjectConfigured(This));

    return This->tcCounter;
}

Telecommand* CC_TelecommandManager_getPendingTelecommand
(
    CC_TelecommandManager *This, 
    unsigned int i
)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(This);
    assert(cc_roc->isObjectConfigured(This));
    assert(i < This->tcListSize);

    return This->pTcList[i];
}

void CC_TelecommandManager_abort(CC_TelecommandManager *This, 
                                 TD_TelecommandId telecommandId)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(This);
    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);

    assert(cc_roc->isObjectConfigured(This) && (telecommandId > 0));

    // In order access pTcList concisely below
    Telecommand** const pTcList = This->pTcList;   
    TelecommandLoaderClass *tlc = TELECOMMANDLOADER_GET_CLASS(This->pTcLoader);
    for (unsigned int i=0; i<This->tcListSize; i++) {
         TelecommandClass *tc = TELECOMMAND_GET_CLASS(pTcList[i]);
         if (tc->getTelecommandId(pTcList[i]) == telecommandId) {
             dc_erc->create(dc_er, (CC_RootObject*)pTcList[i], EVT_TC_ABORTED);
             tlc->release(This->pTcLoader, pTcList[i]);
             pTcList[i] = pNULL;
             This->tcCounter--;
         }
    }
}

void CC_TelecommandManager_setTelecommandLoader(CC_TelecommandManager *This, 
                                                TelecommandLoader *pTcLoader)
{
    assert(pTcLoader != pNULL);

    This->pTcLoader = pTcLoader;
}

TelecommandLoader* CC_TelecommandManager_getTelecommandLoader
(
    CC_TelecommandManager *This
)
{
    assert(This->pTcLoader != pNULL);
    return This->pTcLoader;
}

void CC_TelecommandManager_setObsClock(CC_TelecommandManager *This, 
                                       ObsClock *pObsClock)
{
    assert(pObsClock != pNULL);
    This->pObsClock = pObsClock;
}

ObsClock* CC_TelecommandManager_getObsClock(CC_TelecommandManager *This)
{
    assert(This->pObsClock != pNULL);
    return This->pObsClock;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Load a telecommand. When a telecommand is loaded, it is inserted in
 * the list of pending telecommands and will then be considered for execution.
 * Immediately after being loaded, a validity check is performed on the
 * telecommand.
 * If the validity check fails, an event is created to record the fact and
 * the telecommand is aborted.
 * The telecommand remains loaded until it has terminated execution or is
 * aborted.
 * The telecommand manager creates an event whenever a new telecommand is
 * loaded.
 * If the list of pending telecommands is already full, an event report
 * is created to record the attempted telecommand load and the telecommand
 * is aborted.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *      if(telecommand is not valid)
 *      {   createEventReport(EVT_TC_NOT_VALID);
 *          pTcLoader->release(telecommand);  // notify telecommand loader
 *          return;
 *      }
 *      if(list of pending telecommand is full)
 *      {   createEventReport(EVT_TC_LIST_FULL);
 *          pTcLoader->release(telecommand);  // notify telecommand loader
 *          return;
 *      }
 *      createEventReport(EVT_TC_LOADED);
 *      . . .       // insert telecommand in list of pending telecommands
 *      return; </PRE>
 * The telecommand that is being loaded is passed as the
 * <i>event originator</i> to the event reporting method.
 * @param pTelecommand the telecommand that is loaded
 */
static void load(void *obj, Telecommand *pTelecommand)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
    CC_TelecommandManager *This = CC_TELECOMMANDMANAGER(obj);

    assert(cc_roc->isObjectConfigured(obj));
    assert(pTelecommand != pNULL);

    TelecommandClass *tc = TELECOMMAND_GET_CLASS(pTelecommand);
    TelecommandLoaderClass *tlc = TELECOMMANDLOADER_GET_CLASS(This->pTcLoader);

    if (!tc->isValid(pTelecommand)) {
        dc_erc->create(dc_er, (CC_RootObject*)pTelecommand, EVT_TC_NOT_VALID);
        tlc->release(This->pTcLoader, pTelecommand);
        return;
    }

    // Check whether list of pending telecommands is full
    if (This->tcCounter == This->tcListSize) {
        dc_erc->create(dc_er, (CC_RootObject*)pTelecommand, EVT_TC_LIST_FULL);
        tlc->release(This->pTcLoader, pTelecommand);
        return;
    }

    // Try to insert telecommand in the list of pending telecommands
    Telecommand** const pTcList = This->pTcList;   
    for (unsigned int i=0; i<This->tcListSize; i++) {
        if (!pTcList[i]) {
            pTcList[i] = pTelecommand;
            dc_erc->create(dc_er, (CC_RootObject*)pTelecommand, EVT_TC_LOADED);
            This->tcCounter++;
            return;
        }
    }

    assert(false);  // this should never be reached
}

/**
 * Abort a telecommand.
 * The telecomand is unloaded without being executed.
 * The telecommand loader is notified that the telecommand has been unloaded.
 * If the argument telecommand is not currently loaded, no action is
 * taken.
 * An event report is created whenever a telecommand is aborted.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *      for(all telecommands tc in pending telecommand list)
 *          if(tc eq pTelecommand)
 *          {   . . .   // delete tc from list of pending TC
 *              pTcLoader->release(tc);
 *              createEventReport(EVT_TC_ABORTED);
 *          }
 *      return; </PRE>
 * The telecommand that is being aborted is passed as the
 * <i>event originator</i> to the event reporting method.
 * @see TelecommandLoader#release
 * @param pTelecommand the telecommand to be aborted
 */
static void not_builtin_abort(void *obj, Telecommand *pTelecommand)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
    CC_TelecommandManager *This = CC_TELECOMMANDMANAGER(obj);

    assert(cc_roc->isObjectConfigured(obj) && (pTelecommand != pNULL));

    // In order access pTcList concisely below
    Telecommand** const pTcList = This->pTcList;   
    TelecommandLoaderClass *tlc = TELECOMMANDLOADER_GET_CLASS(This->pTcLoader);
    for (unsigned int i=0; i<This->tcListSize; i++) {
        if (pTcList[i] == pTelecommand) {
            dc_erc->create(dc_er, (CC_RootObject*)pTelecommand, EVT_TC_ABORTED);
            tlc->release(This->pTcLoader, pTcList[i]);
            pTcList[i] = pNULL;
            This->tcCounter--;
            return;
        }
    }
}

/**
 * Go through the list of pending telecommands and execute those that are
 * due for execution.
 * This method would typically be called by an external scheduler.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *      for(all telecommands tc in the list of pending telecommands)
 *          if( ( tc->getTimeTag(void) le currentTime ) OR( tc->getTimeTag(void) eq 0 ) )
 *          {   if( tc->canExecute(void) ) {
 *                  tcOutcome = tc->execute(void);
 *                  if(tcOutcome!=ACTION_SUCCESS)
 *                      createEventReport(EVT_TC_EXEC_FAIL);
 *                  else
 *                      createEventReport(EVT_TC_EXEC_SUCC);
 *              } else
 *                  createEventReport(EVT_TC_EXEC_CHECK_FAIL);
 *
 *              tcLoader->release(tc);
 *              . . .    // delete tc from list of pending telecommands
 *           }        </PRE>
 * The telecommand that is being processed is passed as the
 * <i>event originator</i> to the event reporting method.
 */
static void activate(void *obj)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
    CC_TelecommandManager *This = CC_TELECOMMANDMANAGER(obj);

    assert(cc_roc->isObjectConfigured(obj));
    TD_ActionOutcome tcOutcome;

    // In order access pTcList concisely below
    Telecommand** const pTcList = This->pTcList;   
    TelecommandLoaderClass *tlc = TELECOMMANDLOADER_GET_CLASS(This->pTcLoader);
    ObsClockClass *occ = OBSCLOCK_GET_CLASS(This->pObsClock);
    TelecommandClass *tc;
    for (unsigned int i=0; i<This->tcListSize; i++) {

        if (pTcList[i] == pNULL) continue;

        tc = TELECOMMAND_GET_CLASS(pTcList[i]);
        if (Telecommand_getTimeTag(pTcList[i]) <= occ->getTime(This->pObsClock)) {
            if (tc->canExecute(pTcList[i])) {
                tcOutcome = PunctualAction_execute((PunctualAction*)pTcList[i]);
                if (tcOutcome != ACTION_SUCCESS) {
                    dc_erc->create(dc_er, (CC_RootObject*)pTcList[i], EVT_TC_EXEC_FAIL);
                } else {
                    dc_erc->create(dc_er, (CC_RootObject*)pTcList[i], EVT_TC_EXEC_SUCC);
                }
            } else {
                dc_erc->create(dc_er, (CC_RootObject*)pTcList[i], EVT_TC_EXEC_CHECK_FAIL);
            }

            tlc->release(This->pTcLoader, pTcList[i]);
            pTcList[i] = pNULL;
            This->tcCounter--;
        }
    }
}

/**
 * Perform a class-specific configuration check on the telecommand
 * manager: verify that the pending telecommand list size has been set, 
 * that the OBS clock has been loaded, and that the telecommand loader has
 * been loaded.
 * @return true if the telecommand manager is configured, false otherwise.
 */
static bool isObjectConfigured(void *obj)
{
    CC_RootObjectClass *cc_roc = GET_CLASS(TYPE_CC_ROOTOBJECT);
    CC_TelecommandManager *This = CC_TELECOMMANDMANAGER(obj);
    
    return ((cc_roc->isObjectConfigured(obj)) &&
            (This->pTcLoader != pNULL) && 
            (This->pObsClock != pNULL) && 
            (This->tcListSize != pNULL));
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    CC_TelecommandManager *This = CC_TELECOMMANDMANAGER(obj);
    This->pTcList = pNULL;
    This->tcListSize = 0;
    This->pTcLoader = pNULL;
    This->tcCounter = 0;

    CC_RootObject_setClassId((CC_RootObject*)obj, ID_TELECOMMANDMANAGER);
}

CC_TelecommandManager* CC_TelecommandManager_new(void)
{
    Object *obj = object_new(TYPE_CC_TELECOMMANDMANAGER);
    return (CC_TelecommandManager*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    CC_TelecommandManagerClass *cc_tmc = CC_TELECOMMANDMANAGER_CLASS(oc);
    cc_tmc->load = load;
    // Remove warining: type confilicts with builtin abort
    cc_tmc->abort = not_builtin_abort;
    cc_tmc->activate = activate;

    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_CC_TELECOMMANDMANAGER,
    .parent = TYPE_CC_ROOTOBJECT,
    .instance_size = sizeof(CC_TelecommandManager),
    .abstract = false,
    .class_size = sizeof(CC_TelecommandManagerClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void CC_TelecommandManager_register(void)
{
    type_register_static(&type_info);
}
