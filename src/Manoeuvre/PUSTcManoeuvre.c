//
//
// PUSTcManoeuvre.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../Event/DC_EventRepository.h"
#include "../Base/CC_RootObject.h"
#include "PUSTcManoeuvre.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

bool PUSTcManoeuvre_isStartAckRequired(const PUSTcManoeuvre *This)
{
    return This->startAck;
}

bool PUSTcManoeuvre_isProgressAckRequired(const PUSTcManoeuvre *This)
{
    return This->progressAck;
}

bool PUSTcManoeuvre_isCompletionAckRequired(const PUSTcManoeuvre *This)
{
    return This->completionAck;
}

void PUSTcManoeuvre_setStartAckFlag(PUSTcManoeuvre *This, 
                                    bool startAckFlag)
{
    This->startAck = startAckFlag;
}

void PUSTcManoeuvre_setCompletionAckFlag(PUSTcManoeuvre *This, 
                                         bool completionAckFlag)
{
    This->completionAck = completionAckFlag;
}

void PUSTcManoeuvre_setProgressAckFlag(PUSTcManoeuvre *This, 
                                       bool progressAckFlag)
{
    This->progressAck = progressAckFlag;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * This method generates an event of type EVT_MAN_PROGRESS(manoeuvre progress event report). 
 * Some applications require that telemetry packets be generated to
 * mark the advancement of the execution of the actions associated to a PUS telecommand.
 * This method is intended as a facility to be called by concrete subclasses at points
 * where generation of an execution progress report is required. It would typically be
 * called from inside the implementation of method <code>doInternalContinue</code>.
 * A pseudo-code implementation for this method is as follows:<pre>
 *          createEventReport(this, EVT_MAN_PROGRESS); </pre>
 * @see #isProgressAckRequired
 */
static void generateProgressEvent(void *obj)
{
    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
    dc_erc->create(dc_er, obj, EVT_MAN_PROGRESS);
}

/**
 * Getter method for the identifier of the telecommand that launched this
 * manoeuvre.
 * @see #setTelecommandId
 * @return the telecommand identifier
 */
static TD_TelecommandId getTelecommandId(const void *obj)
{
    PUSTcManoeuvre *This = PUSTCMANOEUVRE(obj);
    return This->tcId;
}

/**
 * Setter method for the identifier of the telecommand that launched this
 * manoeuvre.
 * @see #getTelecommandId
 * @param tcIdentifier the telecommand identifier
 */
static void setTelecommandId(void *obj, TD_TelecommandId tcIdentifier)
{
    PUSTcManoeuvre *This = PUSTCMANOEUVRE(obj);

    assert(tcIdentifier > 0);
    This->tcId = tcIdentifier;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    PUSTcManoeuvre *This = PUSTCMANOEUVRE(obj);

    This->progressAck = false;
    This->completionAck = false;
    This->startAck = false;
    This->tcId = 0;
}

PUSTcManoeuvre* PUSTcManoeuvre_new(void)
{
    Object *obj = object_new(TYPE_PUSTCMANOEUVRE);
    return (PUSTcManoeuvre*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    PUSTcManoeuvreClass *pustmc = PUSTCMANOEUVRE_CLASS(oc);

    pustmc->generateProgressEvent = generateProgressEvent;
    pustmc->getTelecommandId = getTelecommandId;
    pustmc->setTelecommandId = setTelecommandId;
}

static const TypeInfo type_info = {
    .name = TYPE_PUSTCMANOEUVRE,
    .parent = TYPE_MANOEUVRE,
    .instance_size = sizeof(PUSTcManoeuvre),
    .abstract = false,
    .class_size = sizeof(PUSTcManoeuvreClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void PUSTcManoeuvre_register(void)
{
    type_register_static(&type_info);
}
