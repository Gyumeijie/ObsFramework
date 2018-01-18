//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_NullRecoveryAction.c
//
// Version	1.0
// Date		24.06.03
// Author	R. Totaro

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "DC_NullRecoveryAction.h"



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Return without taking any action.
 * @see RecoveryAction#doAction
 * @return always return the outcome code ACTION_SUCCESS
 */
static TD_ActionOutcome doRecoveryAction(void *obj)
{
	return ACTION_SUCCESS;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
	CC_RootObject_setClassId((CC_RootObject*)obj, ID_NULLRECOVERYACTION);
}

DC_NullRecoveryAction* DC_NullRecoveryAction_new(void)
{
    Object *obj = object_new(TYPE_DC_NULLRECOVERYACTION);
    return (DC_NullRecoveryAction*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    RecoveryActionClass *rac = RECOVERYACTION_CLASS(oc);
    rac->doRecoveryAction = doRecoveryAction;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_NULLRECOVERYACTION,
    .parent = TYPE_RECOVERYACTION,
    .instance_size = sizeof(DC_NullRecoveryAction),
    .abstract = false,
    .class_size = sizeof(DC_NullRecoveryActionClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_NullRecoveryAction_register(void)
{
    type_register_static(&type_info);
}
