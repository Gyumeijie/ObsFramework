//
//
// DC_DummyConfigurableFsmState.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "DC_DummyConfigurableFsmState.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

unsigned int DC_DummyConfigurableFsmState_getActivationCounter
(
   DC_DummyConfigurableFsmState *This
)
{
   return This->activationCounter;
}

unsigned int DC_DummyConfigurableFsmState_getInitializationCounter
(
   DC_DummyConfigurableFsmState *This
)
{
   return This->initializationCounter;
}

unsigned int DC_DummyConfigurableFsmState_getExitCounter
(
   DC_DummyConfigurableFsmState *This
)
{
   return This->exitCounter;
}

void DC_DummyConfigurableFsmState_setInitializationCheckValue
(
   DC_DummyConfigurableFsmState *This, 
   bool value
)
{
   This->initializationCheck = value;
}

void DC_DummyConfigurableFsmState_setExitCheckValue
(
   DC_DummyConfigurableFsmState *This, 
   bool value
)
{
   This->exitCheck = value;
}

void DC_DummyConfigurableFsmState_setTerminationCheckValue
(
   DC_DummyConfigurableFsmState *This, 
   bool value
)
{
   This->terminationCheck = value;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Implement dummy continued action: the method increments the activation
 * counter by 1 returns.
 * <p>
 * @see FsmState#doContinue
 */
static void doContinue(void *obj)
{
   DC_DummyConfigurableFsmState *This = DC_DUMMYCONFIGURABLEFSMSTATE(obj);

   This->activationCounter++;
   return;
}

/**
 * Return the value set by the user with the last call to
 * <code>setInitializationCheckValue</code>
 * <p>
 * @see CC_FSM#activate
 * @see setInitializationCheckValue
 * @return true if the continued action associated to this state has been
 * terminated, false otherwise
 */
static bool canEnter(void *obj)
{
   DC_DummyConfigurableFsmState *This = DC_DUMMYCONFIGURABLEFSMSTATE(obj);
   return This->initializationCheck;
}

/**
 * Implement dummy initialization action: the method increments the
 * initialization counter by 1 returns.
 * <p>
 * @see FsmState#doInit
 */
static void doInit(void *obj)
{
   DC_DummyConfigurableFsmState *This = DC_DUMMYCONFIGURABLEFSMSTATE(obj);
   
   This->initializationCounter++;
   return;
}

/**
 * Return the value set by the user with the last call to
 * <code>setExitCheckValue</code>
 * <p>
 * @see CC_FSM#activate
 * @see #setExitCheckValue
 * @return true if the continued action associated to this state has been
 * terminated, false otherwise
 */
static bool canExit(void *obj)
{
   DC_DummyConfigurableFsmState *This = DC_DUMMYCONFIGURABLEFSMSTATE(obj);
   return This->exitCheck;
}

/**
 * Implement dummy exit action: the method increments the exit
 * counter by 1 returns.
 * <p>
 * @see FsmState#doExit
 */
static void doExit(void *obj)
{
   DC_DummyConfigurableFsmState *This = DC_DUMMYCONFIGURABLEFSMSTATE(obj);

   This->exitCounter++;
   return;
}

/**
 * Return the value set by the user with the last call to
 * <code>setTerminationCheckValue</code>
 * <p>
 * @see CC_FSM#activate
 * @see #setTerminationCheckValue
 * @return true if the continued action associated to this state has been
 * terminated, false otherwise
 */
static bool isFinished(void *obj)
{
   DC_DummyConfigurableFsmState *This = DC_DUMMYCONFIGURABLEFSMSTATE(obj);
   return This->terminationCheck;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
   DC_DummyConfigurableFsmState *This = DC_DUMMYCONFIGURABLEFSMSTATE(obj);
   This->activationCounter = 0;
   This->initializationCounter = 0;
   This->exitCounter = 0;
   This->initializationCheck = true;
   This->exitCheck = true;
   This->terminationCheck = false;

   CC_RootObject_setClassId((CC_RootObject*)obj, ID_DUMMYCONFIGURABLEFSMSTATE);
}

DC_DummyConfigurableFsmState* DC_DummyConfigurableFsmState_new(void)
{
    Object *obj = object_new(TYPE_DC_DUMMYCONFIGURABLEFSMSTATE);
    return (DC_DummyConfigurableFsmState*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    FsmStateClass *fsc = FSMSTATE_CLASS(oc);

    fsc->doContinue = doContinue;
    fsc->canEnter = canEnter;
    fsc->doInit = doInit;
    fsc->canExit = canExit;
    fsc->doExit = doExit;
    fsc->isFinished = isFinished;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_DUMMYCONFIGURABLEFSMSTATE,
    .parent = TYPE_FSMSTATE,
    .instance_size = sizeof(DC_DummyConfigurableFsmState),
    .abstract = false,
    .class_size = sizeof(DC_DummyConfigurableFsmStateClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_DummyConfigurableFsmState_register(void)
{
    type_register_static(&type_info);
}
