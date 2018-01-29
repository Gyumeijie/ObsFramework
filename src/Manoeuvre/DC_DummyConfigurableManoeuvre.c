//
//
// DC_DummyConfigurableManoeuvre.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "DC_DummyConfigurableManoeuvre.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_DummyConfigurableManoeuvre_setStartCheckStatus
(
    DC_DummyConfigurableManoeuvre *This,
    bool startCheck
)
{
    This->startCheck = startCheck;
}

void DC_DummyConfigurableManoeuvre_setContinuationCheckStatus
(
    DC_DummyConfigurableManoeuvre *This,
    bool continuationCheck
)
{
    This->continuationCheck = continuationCheck;
}

void DC_DummyConfigurableManoeuvre_setContinuationCheckCode
(
    DC_DummyConfigurableManoeuvre *This,
    TD_CheckCode continuationCheckCode
)
{
    This->continuationCheckCode = continuationCheckCode;
}

void DC_DummyConfigurableManoeuvre_setTerminationCheckStatus
(
    DC_DummyConfigurableManoeuvre *This, 
    bool terminationCheck
)
{
    This->terminationCheck = terminationCheck;
}

int DC_DummyConfigurableManoeuvre_getInitializationActionCounter
(
    DC_DummyConfigurableManoeuvre *This
)
{
    return This->initializationActionCounter;
}

int DC_DummyConfigurableManoeuvre_getContinuationActionCounter
(
    DC_DummyConfigurableManoeuvre *This
)
{
    return This->continuationActionCounter;
}

int DC_DummyConfigurableManoeuvre_getTerminationActionCounter
(
    DC_DummyConfigurableManoeuvre *This
)
{
    return This->terminationActionCounter;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Increment the continuation action counter by one.
 * @see Manoeuvre#doContinue
 */
static void doInternalContinue(void *obj)
{
    DC_DummyConfigurableManoeuvre *This = DC_DUMMYCONFIGURABLEMANOEUVRE(obj);

    assert(Manoeuvre_isExecuting(obj));
    This->continuationActionCounter++;
}

/**
 * Increment the termination action counter by one.
 * @see Manoeuvre#terminate
 */
static void internalTerminate(void *obj)
{
    DC_DummyConfigurableManoeuvre *This = DC_DUMMYCONFIGURABLEMANOEUVRE(obj);
    This->terminationActionCounter++;
}

/**
 * Return the value of the start check flag.
 * The value of the start check flag can be set by the user through method
 * <code>setCheckStatus</code>.
 * @see #setCheckStatus
 * @return true if the manoeuvre is ready to start
 */
static bool canStart(void *obj)
{
    DC_DummyConfigurableManoeuvre *This = DC_DUMMYCONFIGURABLEMANOEUVRE(obj);

    assert(!Manoeuvre_isExecuting(obj));
    return This->startCheck;
}

/**
 * Increment the initialization action counter by one.
 */
static void initialize(void *obj)
{
    DC_DummyConfigurableManoeuvre *This = DC_DUMMYCONFIGURABLEMANOEUVRE(obj);

    assert(!Manoeuvre_isExecuting(obj));
    This->initializationActionCounter++;
}

/**
 * Return the value of the continuation check flag.
 * The value of the continuation check flag can be set by the user through method
 * <code>setCheckStatus</code>.
 * @see #setCheckStatus
 * @return true if the manoeuvre can continue execution
 */
static bool canContinue(void *obj)
{
    DC_DummyConfigurableManoeuvre *This = DC_DUMMYCONFIGURABLEMANOEUVRE(obj);

    assert(Manoeuvre_isExecuting(obj));
    return This->continuationCheck;
}

/**
 * Return the value of the termination check flag.
 * The value of the termination check flag can be set by the user through method
 * <code>setCheckStatus</code>.
 * @see #setCheckStatus
 * @return true if the manoeuvre has terminated execution
 */
static bool isFinished(void *obj)
{
    DC_DummyConfigurableManoeuvre *This = DC_DUMMYCONFIGURABLEMANOEUVRE(obj);

    assert(Manoeuvre_isExecuting(obj));
    return This->terminationCheck;
}

/**
 * Get the value of the continuation check code.
 * In this class, the value of the continuation check code can be set by the user.
 * @see #setContinuationCheckCode
 * @return he return value of the continuation check
 */
static TD_CheckCode getContinuationCheckCode(const void *obj)
{
    DC_DummyConfigurableManoeuvre *This = DC_DUMMYCONFIGURABLEMANOEUVRE(obj);
    return This->continuationCheckCode;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    DC_DummyConfigurableManoeuvre *This = DC_DUMMYCONFIGURABLEMANOEUVRE(obj);
    This->initializationActionCounter = 0;
    This->continuationActionCounter = 0;
    This->terminationActionCounter = 0;
    This->startCheck = MAN_CANNOT_START;
    This->continuationCheck = MAN_CANNOT_CONTINUE;
    This->terminationCheck = MAN_HAS_NOT_TERMINATED;

    CC_RootObject_setClassId((CC_RootObject*)obj, ID_DUMMYCONFIGURABLEMANOEUVRE);
}

DC_DummyConfigurableManoeuvre* DC_DummyConfigurableManoeuvre_new(void)
{
    Object *obj = object_new(TYPE_DC_DUMMYCONFIGURABLEMANOEUVRE);
    return (DC_DummyConfigurableManoeuvre*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    ManoeuvreClass *mc = MANOEUVRE_CLASS(oc);

    mc->doInternalContinue = doInternalContinue;
    mc->internalTerminate = internalTerminate;
    mc->canStart = canStart;
    mc->initialize = initialize;
    mc->canContinue = canContinue;
    mc->isFinished = isFinished;
    mc->getContinuationCheckCode = getContinuationCheckCode;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_DUMMYCONFIGURABLEMANOEUVRE,
    .parent = TYPE_MANOEUVRE,
    .instance_size = sizeof(DC_DummyConfigurableManoeuvre),
    .abstract = false,
    .class_size = sizeof(DC_DummyConfigurableManoeuvreClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_DummyConfigurableManoeuvre_register(void)
{
    type_register_static(&type_info);
}
