//
//
// DC_ControlAction.h
//


#ifndef DC_CONTROLACTION_H
#define DC_CONTROLACTION_H


#include "../GeneralInclude/BasicTypes.h"
#include "../Base/ConditionalPunctualAction.h"
#include "../Data/ControlBlock.h"
#include "../Qom/object.h"


/*
 * Encapsulation of the conditional propagation of a <i>control block</i>.
 * A control action has a settable attribute called <i>target control block</i>.
 * A control action is implemented
 * as a <i>conditional punctual action</i> whose
 * <i>execution action</i> consists in sending a propagation request to
 * the target control block. This class assumes that the target control block
 * is already fully configured.
 * <p>
 * Control actions offer a <i>reset service</i>. A call to the reset service
 * causes the target control block to be reset.
 * <p>
 * This class implements a default <i>execution check</i> that always returns
 * "can execute". This means that, if the control action is enabled, then its
 * execution will always result in the target control block receiving a propagation
 * request. Subclasses can of course implement different execution checks.
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @ingroup Data
 * @version 1.0
 */
#define TYPE_DC_CONTROLACTION "dc_controlaction"

void DC_ControlAction_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct DC_ControlAction {
    ConditionalPunctualAction parent;

    ControlBlock *pTargetControlBlock;
};


struct DC_ControlActionClass {
    ConditionalPunctualActionClass parent_class;
};


#define DC_CONTROLACTION_GET_CLASS(obj) \
        OBJECT_GET_CLASS(DC_ControlActionClass, obj, TYPE_DC_CONTROLACTION)

#define DC_CONTROLACTION_CLASS(klass) \
        OBJECT_CLASS_CHECK(DC_ControlActionClass, klass, TYPE_DC_CONTROLACTION)

#define DC_CONTROLACTION(obj) \
        OBJECT_CHECK(DC_ControlAction, obj, TYPE_DC_CONTROLACTION)


DC_ControlAction* DC_ControlAction_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Load the target control block.
 * @param pBlock the target control block to be loaded
 */
void DC_ControlAction_setTargetControlBlock
(
    DC_ControlAction *This, 
    ControlBlock *pBlock
);

/**
 * Return the currently loaded target control block.
 * @return the target control block that is currently loaded
 */
ControlBlock* DC_ControlAction_getTargetControlBlock(DC_ControlAction *This);

/**
 * Reset the target control block.
 */
void DC_ControlAction_reset(DC_ControlAction *This);


#endif
