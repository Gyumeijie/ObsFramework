//
//
// DC_TestPUSConfigurableManoeuvre.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Manoeuvre/PUSTcManoeuvre.h"
#include "DC_TestPUSConfigurableManoeuvre.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_TestPUSConfigurableManoeuvre_setStartCheckStatus
(
    DC_TestPUSConfigurableManoeuvre *This, 
    bool startCheck
)
{
    This->startCheck = startCheck;
}

void DC_TestPUSConfigurableManoeuvre_setContinuationCheckStatus
(
    DC_TestPUSConfigurableManoeuvre *This,
    bool continuationCheck
)
{
    This->continuationCheck = continuationCheck;
}

void DC_TestPUSConfigurableManoeuvre_setContinuationCheckCode
(
    DC_TestPUSConfigurableManoeuvre *This, 
    TD_CheckCode continuationCheckCode
)
{
    This->continuationCheckCode=continuationCheckCode;
}

void DC_TestPUSConfigurableManoeuvre_setTerminationCheckStatus
(
    DC_TestPUSConfigurableManoeuvre *This,
    bool terminationCheck
)
{
    This->terminationCheck = terminationCheck;
}

int DC_TestPUSConfigurableManoeuvre_getInitializationActionCounter
(
    DC_TestPUSConfigurableManoeuvre *This
)
{
    return This->initializationActionCounter;
}

int DC_TestPUSConfigurableManoeuvre_getContinuationActionCounter
(
    DC_TestPUSConfigurableManoeuvre *This
)
{
    return This->continuationActionCounter;
}

int DC_TestPUSConfigurableManoeuvre_getTerminationActionCounter
(
    DC_TestPUSConfigurableManoeuvre *This
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
 * Increment the continuation action counter by one and call the 
 * <i>progress event generation service</i>. A pseudo-code implementation
 * of this method is as follows:<pre>
 *     continuationActionCounter++;
 *     generateProgressEvent(void);</pre>
 * @see PUSManoeuvre#generateProgressEvent
 * @see Manoeuvre#doContinue
 */
static void doInternalContinue(void *obj)
{
    DC_TestPUSConfigurableManoeuvre *This = DC_TESTPUSCONFIGURABLEMANOEUVRE(obj);
    PUSTcManoeuvreClass *pustmc = PUSTCMANOEUVRE_GET_CLASS(obj);

    assert(Manoeuvre_isExecuting(obj));
    This->continuationActionCounter++;
    pustmc->generateProgressEvent(obj);
}

/**
 * Increment the termination action counter by one.
 * @see Manoeuvre#terminate
 */
static void internalTerminate(void *obj)
{
    DC_TestPUSConfigurableManoeuvre *This = DC_TESTPUSCONFIGURABLEMANOEUVRE(obj);
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
    DC_TestPUSConfigurableManoeuvre *This = DC_TESTPUSCONFIGURABLEMANOEUVRE(obj);

    assert(!Manoeuvre_isExecuting(obj));
    return This->startCheck;
}

/**
 * Increment the initialization action counter by one.
 */
static void initialize(void *obj)
{
    DC_TestPUSConfigurableManoeuvre *This = DC_TESTPUSCONFIGURABLEMANOEUVRE(obj);

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
    DC_TestPUSConfigurableManoeuvre *This = DC_TESTPUSCONFIGURABLEMANOEUVRE(obj);

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
    DC_TestPUSConfigurableManoeuvre *This = DC_TESTPUSCONFIGURABLEMANOEUVRE(obj);

    assert(Manoeuvre_isExecuting(obj));
    return This->terminationCheck;
}

/**
 * Get the value of the continuation check code.
 * In this class, the value of the continuation check code can be set by the user.
 * @see #setContinuationCheckCode
 * return the return value of the continuation check
 */
static TD_CheckCode getContinuationCheckCode(const void *obj)
{
    DC_TestPUSConfigurableManoeuvre *This = DC_TESTPUSCONFIGURABLEMANOEUVRE(obj);
    return This->continuationCheckCode;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    DC_TestPUSConfigurableManoeuvre *This = DC_TESTPUSCONFIGURABLEMANOEUVRE(obj);
    This->initializationActionCounter = 0;
    This->continuationActionCounter = 0;
    This->terminationActionCounter = 0;
    This->startCheck = MAN_CANNOT_START;
    This->continuationCheck = MAN_CANNOT_CONTINUE;
    This->terminationCheck = MAN_HAS_NOT_TERMINATED;

    CC_RootObject_setClassId((CC_RootObject*)obj, ID_TESTPUSCONFIGURABLEMANOEUVRE);
}

DC_TestPUSConfigurableManoeuvre* DC_TestPUSConfigurableManoeuvre_new(void)
{
    Object *obj = object_new(TYPE_DC_TESTPUSCONFIGURABLEMANOEUVRE);
    return (DC_TestPUSConfigurableManoeuvre*)obj;
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
    .name = TYPE_DC_TESTPUSCONFIGURABLEMANOEUVRE,
    .parent = TYPE_PUSTCMANOEUVRE,
    .instance_size = sizeof(DC_TestPUSConfigurableManoeuvre),
    .abstract = false,
    .class_size = sizeof(DC_TestPUSConfigurableManoeuvreClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_TestPUSConfigurableManoeuvre_register(void)
{
    type_register_static(&type_info);
}
