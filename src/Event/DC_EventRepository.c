//
//
// DC_EventRepository.c
//
//          03.12.03 (version 1.1)
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../System/ObsClock.h"
#include "DC_Event.h"
#include "DC_EventRepository.h"


///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_EventRepository_setRepositorySize(DC_EventRepository *This,
                                          unsigned int repositorySize)
{
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(This);

    assert((This->listSize == 0) && (repositorySize > 0));

    This->pList = g_malloc(repositorySize*sizeof(DC_Event*));
    This->listSize = repositorySize;

    for (unsigned int i=0; i<repositorySize; i++) {
        This->pList[i] = pNULL;
    }

    dc_erc->createEventDataStructure(This);
}

void DC_EventRepository_setEnabled(DC_EventRepository *This, bool isEnabled)
{
    This->globalEnabled = isEnabled;
}

void DC_EventRepository_setEnabledWithEventType
(
    DC_EventRepository *This,
    TD_EventType eventType,
    bool isEnabled
)
{
    assert((eventType > 0) && (eventType <= LAST_EVENT_TYPE));
    This->selectiveEnabled[eventType] = isEnabled;
}

bool DC_EventRepository_isEnabled(const DC_EventRepository *This)
{
    return This->globalEnabled;
}

bool DC_EventRepository_isEnabledWithEventType
(
    const DC_EventRepository *This,
    TD_EventType eventType
)
{
    assert((eventType > 0) && (eventType <= LAST_EVENT_TYPE));

    return This->selectiveEnabled[eventType];
}

void DC_EventRepository_latest(DC_EventRepository *This)
{

    This->eventPointer = ((This->counter > 0) ? (This->counter - 1) : 0);
    This->iterationCounter = ((This->counter >= This->listSize) ?
                                                This->listSize  : This->counter);
}

void DC_EventRepository_previous(DC_EventRepository *This)
{
    if (This->iterationCounter > 0) {
        This->iterationCounter--;
        This->eventPointer--;
    }
}

bool DC_EventRepository_isIterationFinished(const DC_EventRepository *This)
{
    return (This->iterationCounter == 0);
}

TD_EventType DC_EventRepository_getEventType(const DC_EventRepository *This)
{
    assert(This->pList != pNULL);

    DC_Event *event = This->pList[This->eventPointer%This->listSize];

    return DC_Event_getEventType(event);
}

TD_ObsTime DC_EventRepository_getTimeStamp(const DC_EventRepository *This)
{
    assert(This->pList != pNULL);

    DC_Event *event = This->pList[This->eventPointer%This->listSize];

    return DC_Event_getTimeStamp(event);
}

unsigned int DC_EventRepository_getCounter(const DC_EventRepository *This)
{
    return This->counter;
}

unsigned int DC_EventRepository_getRepositorySize(const DC_EventRepository *This)
{
    return This->listSize;
}

void DC_EventRepository_setObsClock
(
    DC_EventRepository *This,
    ObsClock *pObsClock
)
{
    assert(pObsClock != pNULL);
    This->pObsClock = pObsClock;
}


ObsClock* DC_EventRepository_getObsClock(const DC_EventRepository *This)
{
    assert(This->pObsClock != pNULL);
    return This->pObsClock;
}

void DC_EventRepository_reset(DC_EventRepository *This)
{
    This->eventPointer = 0;
    This->iterationCounter = 0;
}


///////////////////////////////////////////////////////////////////////////////
//
//                  virtual object methods
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Create the data structure holding the event instances in the repository.
 * This implementation creates a data structure for events of type
 * <code>DC_Event</code>. Repository subclasses that must hold different
 * kinds of events should override this method to create a data structure
 * appropriate to their type of events.
 * @see #setRepositorySize
 */
static void createEventDataStructure(void *obj)
{
    DC_EventRepository *This = DC_EVENTREPOSITORY(obj);

    assert(This->pList != pNULL);

    for (unsigned int i=0; i<This->listSize; i++) {
        This->pList[i] = DC_Event_new();
        assert(This->pList[i]);
    }
}

/**
 * Implement the event creation service.
 * A call to this method causes a new event report to be stored in the
 * repository if event creation is enabled.
 * Event creation can be disabled either globally(through method
 * <code>setEnable(boolean)</code>) or selectively(through
 * method <code>setSelectiveEnableMask(int)</code>).
 * Clients that call this method in order to report an event should pass to it a
 * reference to the originator of the event and the event type identifier.
 * The <i>originator</i> is the component that detected or triggered the event.
 * The <i>event type identifier</i> is an enumeration value that identifies the type
 * of event.
 * An event repository can use the pointer to the event originator to acquire
 * additional information about the event. This implementation however does not
 * use it. It takes the event type identifier, adds a time stamp to it and
 * stores it in a circular FIFO buffer.
 * If the buffer is already full, the oldest event report is overwritten.
 * The pseudo-code for this method is as follows:  <PRE>
 *    if(isEnabled(void))
 *         return;
 *    if(isEnabled(eventId))
 *         . . .  // add timestamp to event and store in repository
 *    else
 *         return; </PRE>
 * @see #setEnabled
 * @param originator the originator of the event
 * @param eventId the event type identifier
 */

static void create(void *obj, CC_RootObject *originator, TD_EventType eventId) 
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    DC_EventRepository *This = DC_EVENTREPOSITORY(obj);

    assert((cc_roc->isObjectConfigured(obj)) &&
           (originator != pNULL) && 
           (eventId > 0) &&
           (eventId <= LAST_EVENT_TYPE));

    // Only create event if creation is enabled
    if (DC_EventRepository_isEnabled(This) && 
        DC_EventRepository_isEnabledWithEventType(This, eventId)) {

        ObsClockClass *occ = OBSCLOCK_GET_CLASS(This->pObsClock);

        DC_Event *item = This->pList[This->counter%This->listSize];
        DC_Event_setEventType(item, eventId);
        DC_Event_setTimeStamp(item, occ->getTime(This->pObsClock));

        This->counter++;
    }
}

static bool isObjectConfigured(void *obj) 
{
    // Warning: not use CC_ROOTOBJECT_GET_CLASS(obj)
    CC_RootObjectClass *cc_roc = GET_CLASS(TYPE_CC_ROOTOBJECT);
    DC_EventRepository *This = DC_EVENTREPOSITORY(obj);

    return ((cc_roc->isObjectConfigured(This)) &&
            (This->pList != pNULL) && 
            (This->pObsClock != pNULL));
}


///////////////////////////////////////////////////////////////////////////////
//
//                 object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj) 
{
    DC_EventRepository *This = DC_EVENTREPOSITORY(obj);
    This->counter = 0;
    This->listSize = 0;
    This->pList = pNULL;
    This->pObsClock = pNULL;
    This->globalEnabled = ENABLED;

    bool *selectiveEnabled = This->selectiveEnabled;
    for (int i=0; i<=LAST_EVENT_TYPE;i++){
        selectiveEnabled[i] = ENABLED;
    }

    DC_EventRepository_reset((DC_EventRepository*)obj);

    CC_RootObject_setClassId((CC_RootObject*)obj, ID_EVENTREPOSITORY);
}

DC_EventRepository* DC_EventRepository_new(void)
{
    Object *obj = object_new(TYPE_DC_EVENTREPOSITORY);
    return (DC_EventRepository*)obj;
}

///////////////////////////////////////////////////////////////////////////////
//
//                 binding and type registration 
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{   
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_CLASS(oc);
    dc_erc->createEventDataStructure = createEventDataStructure;
    dc_erc->create = create;

    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_EVENTREPOSITORY,
    .parent = TYPE_CC_ROOTOBJECT,
    .instance_size = sizeof(DC_EventRepository),
    .abstract = false,
    .class_size = sizeof(DC_EventRepositoryClass),
    .instance_init = instance_init,
    .class_init = class_init
};

void DC_EventRepository_register(void)
{
     type_register_static(&type_info);
}
