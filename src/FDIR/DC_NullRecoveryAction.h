//
//
// DC_NullRecoveryAction.h
//


#ifndef DC_NULLRECOVERYACTION_H
#define DC_NULLRECOVERYACTION_H


#include "../GeneralInclude/BasicTypes.h"
#include "RecoveryAction.h"
#include "../Qom/object.h"


/*
 * Recovery action that performs no action.
 * This recovery action is useful as a "placeholder" where a component
 * of type <code>RecoveryAction</code> is required but where no
 * concrete recovery actions are defined.
 * <p>
 * Note that there is no preclusion to linking non-null recovery
 * actions to a null recovery action.
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 */
#define TYPE_DC_NULLRECOVERYACTION "dc_nullrecoveryaction"

void DC_NullRecoveryAction_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_NullRecoveryAction {
    RecoveryAction parent;
};


struct DC_NullRecoveryActionClass {
    RecoveryActionClass parent_class;
};


#define DC_NULLRECOVERYACTION_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_NullRecoveryActionClass,\
                                               obj, TYPE_DC_NULLRECOVERYACTION)

#define DC_NULLRECOVERYACTION_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_NullRecoveryActionClass,\
                                             klass, TYPE_DC_NULLRECOVERYACTION)

#define DC_NULLRECOVERYACTION(obj) \
        OBJECT_CHECK(DC_NullRecoveryAction, obj, TYPE_DC_NULLRECOVERYACTION)


DC_NullRecoveryAction* DC_NullRecoveryAction_new(void);

#endif
