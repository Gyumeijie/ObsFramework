//
//
// ConditionalPunctualAction.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/ConditionalPunctualAction.h"



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Execute the punctual action if the execution check is satisifed.
 * Otherwise, do nothing.
 * A pseudo-code implementation for this method is as follows: <PRE>
 *   if( canExecute(void) )
 *      return doConditionalAction(void);
 *   else
 *      return ACTION_CANNOT_EXECUTE; </PRE>
 * The <CODE>doConditionalAction(void)</CODE> and <code>canExecute(void)</code>
 * methods are abstract and encapsulate the
 * implementation of the actions associated to
 * the punctual action, and the implementation of the execution check
 * respectively.
 * Thus, this class enforces the execution check but leaves its definition
 * and the definition of the concrete actions associated to the punctual
 * action component open.
 * @see TD_ActionOutcome
 * @return the outcome code of the punctual action
 */
static TD_ActionOutcome doAction(void *obj)
{
    /**
     * The function canExecute is a virtual function and here should call
     * class-specific canExecute and so does doConditionalAction.
     */
    ConditionalPunctualActionClass *cpac = CONDITIONALPUNCTUALACTION_GET_CLASS(obj);

    if (cpac->canExecute(obj)) {
        return cpac->doConditionalAction(obj);
    } else {
        return ACTION_CANNOT_EXECUTE;
    }
}



///////////////////////////////////////////////////////////////////////////////
//
//                    pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Encapsulate implementation of the <i>execution check</i>.
 * This method is called by method <CODE>doAction(void)</CODE> in this same
 * class.
 * @see #doAction
 * @return true if the action can be executed, false if the action cannot
 * be executed.
 */
static bool canExecute(void *obj)
{
    // this is automate genenrated by converter
}

/**
 * Encapsulate implementation of the actions associated to the
 * punctual action component.
 * This method is called by method <CODE>doAction(void)</CODE> in this same
 * class.
 * Note that users of punctual actions do not see method <CODE>doAction(void)</CODE>, 
 * they only see method <CODE>execute(void)</CODE> defined by the superclass.
 * @see #doAction
 * @return the outcome code of the punctual action
 */
static TD_ActionOutcome doConditionalAction(void *obj)
{
    // this is automate genenrated by converter
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj){}

ConditionalPunctualAction* ConditionalPunctualAction_new(void)
{
    Object *obj = object_new(TYPE_CONDITIONALPUNCTUALACTION);
    return (ConditionalPunctualAction*)obj;
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

    PunctualActionClass *pac = PUNCTUALACTION_CLASS(oc);
    pac->doAction = doAction;
}

static const TypeInfo type_info = {
    .name = TYPE_CONDITIONALPUNCTUALACTION,
    .parent = TYPE_PUNCTUALACTION,
    .instance_size = sizeof(ConditionalPunctualAction),
    .abstract = true,
    .class_size = sizeof(ConditionalPunctualActionClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void ConditionalPunctualAction_register(void)
{
    type_register_static(&type_info);
}
