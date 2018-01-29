//
//
// ConditionalPunctualAction.h
//


#ifndef CONDITIONALPUNCTUALACTION_H
#define CONDITIONALPUNCTUALACTION_H


#include "../GeneralInclude/BasicTypes.h"
#include "../Base/PunctualAction.h"
#include "../Qom/object.h"


/*
 * Punctual action that performs an <i>execution check</i>.
 * An execution check is a check that is performed just before the
 * action associated to the punctual action component are executed.
 * An execution check can have two outcomes: "action can be executed" or
 * "action cannot be executed".
 * This type of punctual action is useful to model punctual actions
 * which should be executed only if certain conditions are met.
 * The execution check can be implemented to verify whether these
 * conditions are met.
 * <p>
 * This is an abstract class because it leaves open the definition of the
 * actions to be performed by the punctual action component and the
 * definition of the concrete execution check.
 * This class only implements the management of the abstract execution
 * check.
 * @todo Add a getExecutionCheckCode to return a code describing the reason for
 * the failure of the execution check.
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 * @ingroup Base
 */
#define TYPE_CONDITIONALPUNCTUALACTION "conditionalpunctualaction"

void ConditionalPunctualAction_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct ConditionalPunctualAction {
    PunctualAction parent;
};


struct ConditionalPunctualActionClass {
    PunctualActionClass parent_class;
 
    bool (*canExecute)(void *obj);
    TD_ActionOutcome (*doConditionalAction)(void *obj);
};


#define CONDITIONALPUNCTUALACTION_GET_CLASS(obj) \
        OBJECT_GET_CLASS(ConditionalPunctualActionClass,\
                                           obj, TYPE_CONDITIONALPUNCTUALACTION)

#define CONDITIONALPUNCTUALACTION_CLASS(klass) \
        OBJECT_CLASS_CHECK(ConditionalPunctualActionClass,\
                                         klass, TYPE_CONDITIONALPUNCTUALACTION)

#define CONDITIONALPUNCTUALACTION(obj) \
        OBJECT_CHECK(ConditionalPunctualAction,\
                                           obj, TYPE_CONDITIONALPUNCTUALACTION)


ConditionalPunctualAction* ConditionalPunctualAction_new(void);

#endif
