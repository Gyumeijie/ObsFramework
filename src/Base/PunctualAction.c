//
//
// PunctualAction.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/Constants.h"
#include "../Event/DC_EventRepository.h"
#include "PunctualAction.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

TD_ActionOutcome PunctualAction_execute(PunctualAction *This)
{
    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);

    TD_ActionOutcome outcomeCode = ACTION_DISABLED;

    if (PunctualAction_isEnabled(This)) {
        // doAction is a vitual method and here should call child's doAction.
        PunctualActionClass *pac = PUNCTUALACTION_GET_CLASS(This);
        outcomeCode = pac->doAction(This);
        dc_erc->create(dc_er, (CC_RootObject*)This, EVT_PUNCTUAL_ACTION_EXEC);
    } else {
        dc_erc->create(dc_er, (CC_RootObject*)This, EVT_PUNCTUAL_ACTION_DIS);
    }

    This->lastOutcome = outcomeCode;
    return outcomeCode;
}

void PunctualAction_setEnabled(PunctualAction *This, bool isEnabled)
{
    This->enabledStatus = isEnabled;
}

bool PunctualAction_isEnabled(const PunctualAction *This)
{
    return This->enabledStatus;
}

TD_ActionOutcome PunctualAction_getLastOutcome(const PunctualAction *This)
{
    return This->lastOutcome;
}

void PunctualAction_resetLastOutcome(PunctualAction *This)
{
    This->lastOutcome = ACTION_RESET;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Encapsulate implementation of the action associated to this punctual
 * action object.
 * This method is called by method <CODE>execute(void)</CODE> in this same
 * class.
 * Users of punctual actions do not see method <CODE>doAction(void)</CODE>, 
 * they only see method <CODE>execute(void)</CODE>.
 * <p>
 * @see #execute
 * @return the outcome code of the punctual action that encodes the
 * results of the execution of the action
 * (success, failure, etc)
 */
static TD_ActionOutcome doAction(void *obj)
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
    PunctualAction *This = PUNCTUALACTION(obj);

    This->enabledStatus = ENABLED;
    This->lastOutcome = ACTION_RESET;
}

PunctualAction* PunctualAction_new(void)
{
    Object *obj = object_new(TYPE_PUNCTUALACTION);
    return (PunctualAction*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    PunctualActionClass *pac = PUNCTUALACTION_CLASS(oc);
    pac->doAction = doAction;
}

static const TypeInfo type_info = {
    .name = TYPE_PUNCTUALACTION,
    .parent = TYPE_CC_ROOTOBJECT,
    .instance_size = sizeof(PunctualAction),
    .abstract = true,
    .class_size = sizeof(PunctualActionClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void PunctualAction_register(void)
{
    type_register_static(&type_info);
}
