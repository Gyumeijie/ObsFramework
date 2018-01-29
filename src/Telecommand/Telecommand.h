//
//
// Telecommand.h
//
//
// Change Record:


#ifndef TELECOMMAND_H
#define TELECOMMAND_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/PunctualAction.h"
#include "../Qom/object.h"


/*
 * Base class from which all telecommand classes are derived.
 * This is an abstract class. Concrete telecommands are obtained by deriving
 * this class.
 * <p>
 * A telecommand is a form of <i>punctual action</i>.
 * Telecommands add to the following attributes to those they inherit
 * from their superclass:<ul>
 * <li>A <i>time tag</i>: the time when the telecommand should be executed.
 * If the time tag is equal to zero, then the telecommand should be executed
 * immediately. Negative values of the time tag indicate a non-configured or
 * or otherwise invalid telecommand.</li>
 * <li>A <i>telecommand identifier</i>: an integer that uniquely identifies the
 * telecommand. </li>
 * <li>A <i>telecommand source</i>: an integer that uniquely identifies the
 * sender of the telecommand. </li>
 * <li>A <i>telecommand type</i>: an integer that identifies the type of
 * telecommand. </li>
 * <li>A <i>telecommand subtype</i>: an integer that identifies the subtype of
 * telecommand. This attribute is useful when the type attribute does not provide
 * sufficient granularity to represent the various categories of telecommands.</li>
 * <li>A <i>validity check code</i>: a read-only integer that conveys information about
 * the failure of the validity check(see below). </li>
 * <li>An <i>execution check code</i>: a read-only integer that conveys information about
 * the failure of the execution check(see below). </li>
 * <li>An <i>acknowledge level</i>: an integer that defines the level of acknowledgement
 * that the telecommand sender requires for the telecommand(e.g. acknowledgement upon
 * acceptance of the telecommand, acknowledgement upon execution start, acknowledgement
 * upon execution termination, etc).</li>
 * <li>An <i>in use flag</i>: a toggle attribute that can have two values:
 * "telecommand is in use" and "telecommand is not in use". This attribute
 * can be useful because telecommand components
 * are normally created dynamically and therefore their resources must be
 * managed dynamically. The "in use" attribute can then be used to discriminate
 * between telecommands that are being used(and whose resources are therefore
 * to be considered allocated) and telecommands that are not being used(and
 * whose resources can therefore be reclaimed and used to construct other
 * telecommand components). In the OBS Framework, the "in use" attribute
 * would typically be used by the <i>telecommand loader</i>.</li>
 * </ul>
 * With the exception of the "in use flag", all telecommand attributes are
 * conceptually read-only
 * attributes. However, since telecommand objects may have to be dynamically
 * configured by the <i>telecommand loader</i>, setter methods are provided
 * to dynamically set their values.
 * <p>
 * Telecommands implement the <i>raw data load service</i>. This is
 * intended to facilitate the configuration
 * of a telecommand by the <i>telecommand loader</i>. The usage scenario
 * for this service is a situation where the telecommand loader receives
 * the raw telecommand as a list of bytes. The list of bytes contain
 * the configuration data for the telecommand component. The raw data
 * load service allows the telecommand loader to load these bytes into the
 * telecommand loader in an "anonymous manner" without having to know
 * anything about their meaning for the telecommand component.
 * The raw data load service is an optional service that only some
 * concrete telecommand components will choose to implement. The choice to
 * implement it depends on the mutual relationship between the concrete
 * telecommand loader and the concrete telecommand components.
 * Two alternative implementations for the raw data load service are
 * defined. The first one is efficient but potentially unsafe(it does
 * not comply with project-specific coding rule PR3.3). The second one is
 * safe(it complies with all coding rules) but less efficient(it requires
 * a virtual method call for each byte that is loaded in the telecommand
 * component).
 * <p>
 * Telecommands can perform two checks: a <i>validity check</i> and an
 * <i>execution check</i>.
 * The validity check checks the internal validity of the telecommand
 * attributes.
 * It should normally be executed immediately after the telecommand is loaded to
 * verify its formal correctness.
 * The execution check should be performed just before the telecommand is
 * executed and should
 * verify whether conditions for the safe execution of the telecommand are
 * satisfied.
 * <p>
 * This class provides a general interface that can model telecommand concepts
 * of varying complexity but it only provides a minimal implementation.
 * Thus, of the attributes it defines, only the time tag and the "in use" flag
 * are implemented as true read/write attributes. The other attributes are
 * implemented as fixed constants. Applications are free to provide
 * subclasses that implement a larger subset of the attributes
 * defined in this class.
 * <p>
 * @todo The possibility should be considered of making Telecommand a subclass
 * of ConditionalPunctualAction. This would make sense because the Telecommand
 * class contains a conditional execution check. However, this change would
 * require delicate changes to the CC_TelecommandManager and CriticalTelecommand
 * classes(at the least). For the time being, it seems wiser to leave things
 * as they are. The advantage of the current solution is that it gives greater
 * control to the telecommand manager over the execution of the telecommand
 * and it makes it easier to implement "special" types of telecommands(such
 * as, for instance, critical telecommands).
 * @todo should new versions of method setRawData that take as argument unsigned short
 * and unsigned int be added? This would speed up execution when a large number of data have
 * to be loaded but it might make implementation of the methods in concrete subclasses
 * more complex.
 * @see TelecommandLoader
 * @see CC_TelecommandManager
 * @author Alessandro Pasetti(P&P Software GmbH)
 * @version 1.0
 * @ingroup Telecommand
 */
#define TYPE_TELECOMMAND "telecommand"

void Telecommand_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct Telecommand {
    PunctualAction parent;

    TD_ObsTime timeTag;
    bool inUse;
};


struct TelecommandClass {
    PunctualActionClass parent_class;
 
    bool (*isValid)(void *obj);
    TD_CheckCode (*getValidityCheckCode)(const void *obj);
    bool (*canExecute)(void *obj);
    TD_CheckCode (*getExecutionCheckCode)(const void *obj);
    TD_TelecommandId (*getTelecommandId)(const void *obj);
    void (*setTelecommandId)(void *obj, TD_TelecommandId tcIdentifier);
    TD_TelecommandType (*getType)(const void *obj);
    void (*setType)(void *obj, TD_TelecommandType tcType);
    TD_TelecommandSubType (*getSubType)(const void *obj);
    void (*setSubType)(void *obj, TD_TelecommandSubType tcSubType);
    TD_TelecommandSource (*getSource)(const void *obj);
    void (*setSource)(void *obj, TD_TelecommandSource tcSource);
    void (*setRawData)(void *obj, unsigned int i, unsigned char d);
    unsigned int (*getNumberOfRawData)(const void *obj);
    void (*setRawDataFastly)(void *obj, unsigned char *d, unsigned int i);
    void (*setAcknowledgeLevel)(void *obj, TD_TelecommandAck ackLevel);
    TD_TelecommandAck (*getAcknowledgeLevel)(const void *obj);
};


#define TELECOMMAND_GET_CLASS(obj) \
        OBJECT_GET_CLASS(TelecommandClass, obj, TYPE_TELECOMMAND)

#define TELECOMMAND_CLASS(klass) \
        OBJECT_CLASS_CHECK(TelecommandClass, klass, TYPE_TELECOMMAND)

#define TELECOMMAND(obj) \
        OBJECT_CHECK(Telecommand, obj, TYPE_TELECOMMAND)


Telecommand* Telecommand_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Getter method for the telecommand time tag.
 * @return the telecommand time tag
 */
TD_ObsTime Telecommand_getTimeTag(const Telecommand *This);

/**
 * Setter method for the telecommand time tag.
 * @see TelecommandLoader
 * @param timeTag the telecommand time tag
 */
void Telecommand_setTimeTag(Telecommand *This, TD_ObsTime timeTag);

/**
 * Set the value of the "in use" attribute.
 * @see #isInUse
 * @param newInUse the new value of the in use attribute
 */
void Telecommand_setInUse(Telecommand *This, bool newInUse);

/**
 * Return the value of the "in use" attribute. If the method returns true, then
 * the telecommand is in use, otherwise it is not in use.
 * @see #setInUse
 * @return the value of the "in use" attribute.
 */
bool Telecommand_isInUse(const Telecommand *This);


#endif
