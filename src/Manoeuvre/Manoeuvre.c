//
//
// Manoeuvre.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../Event/DC_EventRepository.h"
#include "../Base/CC_RootObject.h"
#include "Manoeuvre.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void Manoeuvre_doContinue(Manoeuvre *This)
{
   if (!This->executing) {
      This->executing = true;
      This->activationStepCounter = 0;

      DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
      DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
      dc_erc->create(dc_er, (CC_RootObject*)This, EVT_MAN_STARTED);
   }

   if (!Manoeuvre_isSuspended(This)) {
      This->activationStepCounter++;

      ManoeuvreClass *mc = MANOEUVRE_GET_CLASS(This);
      mc->doInternalContinue(This);
  }
}

void Manoeuvre_abort(Manoeuvre *This)
{
    This->suspended = false;

    if (This->executing) {
        This->executing = false;

        DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
        DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
        dc_erc->create(dc_er, (CC_RootObject*)This, EVT_MAN_ABORTED);

        ManoeuvreClass *mc = MANOEUVRE_GET_CLASS(This);
        mc->internalAbort(This);
    }
}

void Manoeuvre_terminate(Manoeuvre *This)
{
    assert(This->executing);

    This->suspended = false;
    This->executing = false;

    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
    dc_erc->create(dc_er, (CC_RootObject*)This, EVT_MAN_TERMINATED);

    ManoeuvreClass *mc = MANOEUVRE_GET_CLASS(This);
    mc->internalTerminate(This);
}

void Manoeuvre_setInUse(Manoeuvre *This, bool newInUse)
{
    This->inUse = newInUse;
}

bool Manoeuvre_isInUse(const Manoeuvre *This)
{
	return This->inUse;
}

void Manoeuvre_setIsSuspended(Manoeuvre *This, bool newIsSuspended)
{
    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);

	if (This->suspended && !newIsSuspended) {
		dc_erc->create(dc_er, (CC_RootObject*)This, EVT_MAN_RESUMED);
    } else if (!This->suspended && newIsSuspended) {
        dc_erc->create(dc_er, (CC_RootObject*)This, EVT_MAN_SUSPENDED);
    }

	This->suspended = newIsSuspended;
}

bool Manoeuvre_isSuspended(const Manoeuvre *This)
{
	return This->suspended;
}

bool Manoeuvre_isExecuting(const Manoeuvre *This)
{
	return This->executing;
}

void Manoeuvre_setEnabled(Manoeuvre *This, bool enabledStatus)
{
	This->enabled = enabledStatus;
}

bool Manoeuvre_isEnabled(const Manoeuvre *This)
{
	return This->enabled;
}

unsigned int Manoeuvre_getActivationStepCounter(const Manoeuvre *This)
{
    return This->activationStepCounter;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Encapsulate the implementation of the actions to be carried out by the
 * manoeure after it is aborted.
 * This method is called by method <CODE>abort(void)</CODE> in this same class.
 * This class offers a default implementation that returns without taking
 * any actions.
 * @see #abort
 */
static void internalAbort(void *obj)
{
    return;
}

/**
 * Encapsulate the implementation of the termination actions associated to
 * this manoeuvre.
 * This method is called by method <CODE>terminate(void)</CODE> in this same class.
 * This class offers a default implementation that returns without taking
 * any action.
 * @see #terminate
 */
static void internalTerminate(void *obj)
{
    return;
}

/**
 * Encapsulate the implementation of the start check associated to
 * this manoeuvre.
 * This method is called by method <CODE>canStart(void)</CODE> in this same class.
 * This class offers a default implementation that returns "manoeuvre
 * can start".
 * @see #canStart
 * @return true if the manoeuvre can start execution, false otherwise
 */
static bool internalCanStart(void *obj)
{
    return MAN_CAN_START;
}

/**
 * Perform the start check for the manoeuvre: return true if the manoeuvre is
 * ready to start execution.
 * This method should be called only on a manoeuvre that is already in used
 * but that is not yet executing.
 * Execution of a manoeuvre should be initiated only when this check has been
 * performed and has returned: "manoeuvre ready to start".
 * If a manoeuvre is disabled, the check always returns: "manoeuvre cannot
 * start". Otherwise, a manouvre-specific check is performed.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *   if(!isEnabled(void))
 *     return MAN_CANNOT_START;
 *   else
 *     return internalCanStart(void); </PRE>
 * The <CODE>internalCanStart(void)</CODE> method is virtual and encapsulates
 * the implementation of the manoeuvre-specific part of the start check.
 * @see CC_ManoeuvreManager#activate
 * @return true if the manoeuvre is ready to start
 */
static bool canStart(void *obj)
{
    Manoeuvre *This = MANOEUVRE(obj);

    assert(!This->executing);

    if (!Manoeuvre_isEnabled(obj)) {
      return MAN_CANNOT_START;
    } else {

      ManoeuvreClass *mc = MANOEUVRE_GET_CLASS(obj);
      return mc->internalCanStart(obj);
    }
}

/**
 * Perform the initialization action associated to this manoeuvre.
 * This method should be called on a manoeuvre that is alredy in use but
 * not yet executing. It should be called immediately before the execution of the
 * manoeuvre is initiated. It should be called only when the execution check
 * returns "manoeuvre can start".
 * This class offers a default implementation that returns without doing anything.
 * <p>
 * @see CC_ManoeuvreManager#activate
 * @see #canStart
 */
static void initialize(void *obj)
{
   Manoeuvre *This = MANOEUVRE(obj);

   assert(!This->executing);
   return;
}

/**
 * Perform the continuation check for the manoeuvre: return true if the
 * manoeuvre can safely continue execution.
 * A manoeuvre that whose continuation check returns "cannot continue
 * execution" should normally be aborted(method <code>abort</code>).
 * This class offers a default implementation that returns "manoeuvre can
 * continue".
 * <p>
 * This method should only be called on a manoeuvre that is in use and
 * that is already executing.
 * @see CC_ManoeuvreManager#activate
 * @see #abort
 * @return true if the manoeuvre can continue execution
 */
static bool canContinue(void *obj)
{
   Manoeuvre *This = MANOEUVRE(obj);

   assert(This->executing);
   return MAN_CAN_CONTINUE;
}

/**
 * Return the continuation check code for the manoeuvre.
 * The continuation check code allows a manoeuvre to make information available about
 * the reasons for the failure of the continuation check. The return value of this
 * method is only valid if the continuation check has returned "manoeuvre cannot
 * continue" (ie. if method <code>canContinue</code> has returned false). This class
 * provides a default implementation that returns zero.
 * @see #canContinue
 * @return the continuation check code
 */
static TD_CheckCode getContinuationCheckCode(const void *obj)
{
   return 0;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Encapsulate the implementation of the continuation actions to be carried
 * out by the manoeure.
 * This method is called by method <CODE>doContinue(void)</CODE> in this same class.
 * <p>
 * @see #doContinue
 */
static void doInternalContinue(void *obj)
{
    // this is automate genenrated by converter
}

/**
 * Perform the termination check for the manoeuvre: return true if the manoeuvre
 * has terminated executing its allotted actions.
 * After this method returns "manoeuvre has terminated", the termination
 * action should be executed.
 * @see CC_ManoeuvreManager#activate
 * @return true if the manoeuvre has terminated execution
 */
static bool isFinished(void *obj)
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
    Manoeuvre *This = MANOEUVRE(obj);

    This->enabled = ENABLED;
    This->inUse = MAN_NOT_IN_USE;
    This->executing = MAN_NOT_EXECUTING;
    This->suspended = MAN_NOT_SUSPENDED;
    This->activationStepCounter = 0;
}

Manoeuvre* Manoeuvre_new(void)
{
    Object *obj = object_new(TYPE_MANOEUVRE);
    return (Manoeuvre*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    ManoeuvreClass *mc = MANOEUVRE_CLASS(oc);

    mc->internalAbort = internalAbort;
    mc->internalTerminate = internalTerminate;
    mc->internalCanStart = internalCanStart;
    mc->canStart = canStart;
    mc->initialize = initialize;
    mc->canContinue = canContinue;
    mc->getContinuationCheckCode = getContinuationCheckCode;

    mc->doInternalContinue = doInternalContinue;
    mc->isFinished = isFinished;
}

static const TypeInfo type_info = {
    .name = TYPE_MANOEUVRE,
    .parent = TYPE_CC_ROOTOBJECT,
    .instance_size = sizeof(Manoeuvre),
    .abstract = true,
    .class_size = sizeof(ManoeuvreClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void Manoeuvre_register(void)
{
    type_register_static(&type_info);
}
