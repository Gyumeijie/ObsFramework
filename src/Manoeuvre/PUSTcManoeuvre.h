//
//
// PUSTcManoeuvre.h
//


#ifndef PUSTCMANOEUVRE_H
#define PUSTCMANOEUVRE_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Manoeuvre/Manoeuvre.h"
#include "../Qom/object.h"


/*
 * Base class for classes encapsulating a <i>PUS telecommand manoeuvre</i>.
 * A PUS telecommand manoeuvre models the manoeuvre-like actions associated
 * to a PUS telecommand.
 * The OBS Framework implements a telecommand as a form of <i>punctual action</i>
 * that is executed in one-shot mode(i.e. its execution terminates in the same cycle
 * in which it begins). The Packet Utilization Standard(PUS) instead
 * allows for actions to be associated to a telecommand that must be executed over
 * an interval of time. This class models this type of actions as a form of
 * <i>manoeuvre</i>. A manoeuvre of this type would normally be launched by
 * a PUS telecommand.
 * <p>
 * This class adds to its base class the following attributes that
 * describe the telecommand that launches the manoeuvre: <ul>
 * <li>The <i>telecommand identifier attribute</i> of the PUS telecommand that triggered
 * execution of the manoeuvre. In a PUS telecommand, this attribute is identical to the
 * packet sequence control attribute.</li>
 * <li>The <i>execution start acknowledge flag</i> of the PUS telecommand that triggered
 * execution of the manoeuvre. </li>
 * <li>The <i>progress acknowledge flag</i> of the PUS telecommand that triggered
 * execution of the manoeuvre. </li>
 * <li>The <i>completion acknowledge flag</i> of the PUS telecommand that triggered
 * execution of the manoeuvre. </li>
 * </ul>
 * Additionally, this class provides a <i>progress event generation service</i>. This
 * service can be called by concrete subclasses to generate an event marking the
 * advancement of the execution of the PUS telecommand mananoeuvre.
 * <p>
 * A PUS telecommand manoeuvre is normally loaded into the manoeuvre manager by
 * a PUS telecommand. The PUS telecommand should configured the PUS manoeuvre as follows:<ul>
 * <li>It should set its telecommand identifier attribute</li>
 * <li>It should set its execution start acknowledge flag</li>
 * <li>It should set its progress acknowledge flag</li>
 * <li>It should set its completion acknowledge flag</li>
 * </ul>
 * The above configuration actions can be performed in any order.
 * @see PUSTelecommand
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 * @ingroup PUS
 * @ingroup Manoeuvre
 */
#define TYPE_PUSTCMANOEUVRE "pustcmanoeuvre"

void PUSTcManoeuvre_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct PUSTcManoeuvre {
    Manoeuvre parent;

    bool startAck;
    bool progressAck;
    bool completionAck;
    TD_TelecommandId tcId;
};


struct PUSTcManoeuvreClass {
    ManoeuvreClass parent_class;
 
    void (*generateProgressEvent)(void *obj);
    TD_TelecommandId (*getTelecommandId)(const void *obj);
    void (*setTelecommandId)(void *obj, TD_TelecommandId tcIdentifier);
};


#define PUSTCMANOEUVRE_GET_CLASS(obj) \
        OBJECT_GET_CLASS(PUSTcManoeuvreClass, obj, TYPE_PUSTCMANOEUVRE)

#define PUSTCMANOEUVRE_CLASS(klass) \
        OBJECT_CLASS_CHECK(PUSTcManoeuvreClass, klass, TYPE_PUSTCMANOEUVRE)

#define PUSTCMANOEUVRE(obj) \
        OBJECT_CHECK(PUSTcManoeuvre, obj, TYPE_PUSTCMANOEUVRE)


PUSTcManoeuvre* PUSTcManoeuvre_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Return true if acknowledgement of manoeuvre execution start is
 * required. This flag should normally have the same value as the execution start 
 * acknowledgement flag of the telecommand that triggered the execution of this
 * manoeuvre.
 * @see #setStartAckFlag
 * @return the value of the execution start acknowledge flag
 */
bool PUSTcManoeuvre_isStartAckRequired(const PUSTcManoeuvre *This);

/**
 * Return true if acknowledgement of manoeuvre execution progress is
 * required. This flag should normally have the same value as the progress
 * acknowledgement flag of the telecommand that triggered the execution of this
 * manoeuvre.
 * @see #setProgressAckFlag
 * @return the value of the progress acknowledge flag
 */
bool PUSTcManoeuvre_isProgressAckRequired(const PUSTcManoeuvre *This);

/**
 * Return the true if acknowledgement of manoeuvre execution completion is
 * required. This flag should normally have the same value as the completion
 * acknowledgement flag of the telecommand that triggered the execution of this
 * manoeuvre.
 * @see #setCompletionAckFlag
 * @return the value of the completion acknowledge flag
 */
bool PUSTcManoeuvre_isCompletionAckRequired(const PUSTcManoeuvre *This);

/**
 * Set the value of the start acknowledge flag.
 * @see #isStartAckRequired
 * @param startAckFlag the value of the execution start acknowledge flag
 */
void PUSTcManoeuvre_setStartAckFlag(PUSTcManoeuvre *This, bool startAckFlag);

/**
 * Set the value of the completion acknowledge flag.
 * @see #isCompletionAckRequired
 * @param completionAckFlag the value of the completion acknowledge flag
 */
void PUSTcManoeuvre_setCompletionAckFlag(PUSTcManoeuvre *This, bool completionAckFlag);

/**
 * Set the value of the progress acknowledge flag.
 * @see #isCompletionAckRequired
 * @param progressAckFlag the value of the progress acknowledge flag
 */
void PUSTcManoeuvre_setProgressAckFlag(PUSTcManoeuvre *This, bool progressAckFlag);


#endif
