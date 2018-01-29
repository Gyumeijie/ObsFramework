//
//
// DC_PUSTelemetryModeManager.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../Telemetry/DC_PUSTelemetryModeManager.h"
#include "../Telemetry/DC_PUSDataReportingPacket.h"
#include "../Base/ModeManager.h"
#include "../Event/DC_EventRepository.h"
#include "../Base/CC_RootObject.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void DC_PUSTelemetryModeManager_loadPacket(DC_PUSTelemetryModeManager *This, 
                                           DC_PUSDataReportingPacket *pItem)
{
    assert(This->list != pNULL);
    assert(pItem != pNULL);

    DC_PUSDataReportingPacket** const list = This->list;    
    const unsigned int listLength = This->listLength;
    for (unsigned int i=0; i<listLength; i++) {
        if (list[i] == pNULL) {
            list[i] = pItem;
            assert(This->counter < listLength);
            This->counter++;
            return;
        }
    }
    
    assert(This->counter == listLength);

    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
    dc_erc->create(dc_er, (CC_RootObject*)This, EVT_ILLEGAL_MM);
    return;
}

void DC_PUSTelemetryModeManager_unloadPacket(DC_PUSTelemetryModeManager *This, 
                                             TD_SID sid)
{
    assert(This->list != pNULL);

    DC_PUSDataReportingPacket** const list = This->list;    
    const unsigned int listLength = This->listLength;
    for (unsigned int i=0; i<listLength; i++)  {
        if (list[i] == pNULL) continue;
        if (DC_PUSDataReportingPacket_getSID(list[i]) == sid) {
            list[i] = pNULL;
            This->counter--;
            return;
        }
    }
    
    DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
    DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
    dc_erc->create(dc_er, (CC_RootObject*)This, EVT_SID_NOT_FOUND);
    return;
}

bool DC_PUSTelemetryModeManager_isFull(const DC_PUSTelemetryModeManager *This)
{
    return (This->counter == This->listLength);
}

unsigned int DC_PUSTelemetryModeManager_getNumberOfPackets
(
    const DC_PUSTelemetryModeManager *This
)
{
    return This->counter;
}

bool DC_PUSTelemetryModeManager_isSIDLoaded
(
    const DC_PUSTelemetryModeManager *This,
    TD_SID sid
)
{
    assert(This->list != pNULL);

    DC_PUSDataReportingPacket** const list = This->list;    
    const unsigned int listLength = This->listLength;
    for (unsigned int i=0; i<listLength; i++) {
        if (list[i] == pNULL) continue;
        if (DC_PUSDataReportingPacket_getSID(list[i]) == sid)  {
            return true;
        }
    }
    
    return false;
}

void DC_PUSTelemetryModeManager_setMaxNumberOfPackets
(
    DC_PUSTelemetryModeManager *This, 
    unsigned int n
)
{
    assert(This->listLength == 0);
    assert(n > 0);

    This->listLength = n;
    This->list = g_malloc(n*sizeof(DC_PUSDataReportingPacket*));
    for (unsigned int i=0; i<n; i++) {
        This->list[i] = pNULL;
    }
}

unsigned int DC_PUSTelemetryModeManager_getMaxNumberOfPackets
(
    const DC_PUSTelemetryModeManager *This
)
{
    return This->listLength;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * This method returns without taking any action.
 * This method is unnecessary in this class because no mode-dependent
 * memory data structures need to be allocated.
 * @see #setNumberOfModes
 * @param numberOfModes the number of modes
 */
static void allocateMemory(void *obj, TD_Mode numberOfModes)
{
    return;
}

/**
 * This method return without taking any action. This mode manager
 * has only one mode and therefore the <i>update</i> operation is
 * implemented to return without taking any action.
 * @see ModeManager#update
 */
static void update(void *obj)
{
    return;
}

/**
 * Retrieve the telemetry packet currently scanned by the iteration counter.
 * This method should only be used within an iteration cycle. This method
 * should only be used within an iteration cycle(i.e. while 
 * <code>isIterationFinished</code> reports <code>false</code>).
 * @see TelemetryModeManager#first
 * @return the item currently scanned by the iteration counter
 */
static TelemetryPacket* getIterationTelemetryPacket(void *obj)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj); 
    DC_PUSTelemetryModeManager *This = DC_PUSTELEMETRYMODEMANAGER(obj);

    assert(cc_roc->isObjectConfigured(obj));
    assert(This->iterationCounter < This->listLength);
    return (TelemetryPacket*)This->list[This->iterationCounter];
}

/**
 * Iteration method to iterate through the currently loaded telemetry 
 * packets. This method should be used jointly with methods: <code>next</code>, 
 * <code>isIterationFinished</code> and <code>getIterationTelemetryPacket</code>. 
 * Taken together, 
 * these methods allow all the currently loaded items to be scanned. 
 * The item currently scanned can be retrieved
 * through method <code>getIterationTelemetryPacket</code>.
 * Thus, a typical iteration cycle might be organized as follows: <PRE>
 *      for(first(void); !isIterationFinished(void); next(void)) {
 *          pItem = getIterationTelemetryPacket(void);
 *          . . .    // process pItem
 *      }  </PRE>
 */
static void first(void *obj)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj); 
    DC_PUSTelemetryModeManager *This = DC_PUSTELEMETRYMODEMANAGER(obj);

    assert(cc_roc->isObjectConfigured(obj));
    This->iterationCounter = 0;
    while ((This->iterationCounter < This->listLength) && 
           (This->list[This->iterationCounter] == pNULL))
    {
        This->iterationCounter++;
    }
}

/**
 * Iteration method to be used in conjunction with methods <code>first</code>
 * and <code>isIterationFinished</code>.
 * This method should only be called as part of an iteration cycle.
 * @see #first
 */
static void next(void *obj)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj); 
    DC_PUSTelemetryModeManager *This = DC_PUSTELEMETRYMODEMANAGER(obj);

    assert(cc_roc->isObjectConfigured(obj));
    This->iterationCounter++;
    while ((This->iterationCounter < This->listLength) && 
           (This->list[This->iterationCounter] == pNULL)) 
    {
        This->iterationCounter++;
    }
}

/**
 * Iteration method to be used in conjunction with methods <code>first</code>
 * and <code>next</code>.
 * This method should only be used as part of an iteration cycle. The result
 * of calling it before ever calling <code>first</code>
 * is undefined.
 * @see #first
 * @return true if the end of the iteration has been reached, false otherwise
 */
static bool isIterationFinished(void *obj)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj); 
    DC_PUSTelemetryModeManager *This = DC_PUSTELEMETRYMODEMANAGER(obj);

    assert(cc_roc->isObjectConfigured(obj));
    assert(This->iterationCounter <= This->listLength);
    return(This->iterationCounter == This->listLength);
}

/**
 * Perform a class-specific configuration check on a telemetry mode
 * manager: verify that the maximum number of telemetry packets that can
 * be loaded has been set
 * @return true if the mode manager is configured, false
 * otherwise.
 */
static bool isObjectConfigured(void *obj)
{
    TelemetryModeManagerClass *tmmc = GET_CLASS(TYPE_TELEMETRYMODEMANAGER);
    DC_PUSTelemetryModeManager *This = DC_PUSTELEMETRYMODEMANAGER(obj);

    if (!(CC_ROOTOBJECT_CLASS(tmmc)->isObjectConfigured(obj)) || 
         (This->list == pNULL)) 
    {
        return NOT_CONFIGURED;
    }

    return CONFIGURED;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj)
{
    DC_PUSTelemetryModeManager *This = DC_PUSTELEMETRYMODEMANAGER(obj);
    This->counter = 0;
	This->list = pNULL;
	This->listLength = 0;
    This->iterationCounter = 0;

    ModeManager_setNumberOfModes((ModeManager*)obj, 1);
    ModeManager_setDefaultMode((ModeManager*)obj, 0);

    CC_RootObject_setClassId((CC_RootObject*)obj, ID_PUSTELEMETRYMODEMANAGER);
}

DC_PUSTelemetryModeManager* DC_PUSTelemetryModeManager_new(void)
{
    Object *obj = object_new(TYPE_DC_PUSTELEMETRYMODEMANAGER);
    return (DC_PUSTelemetryModeManager*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    TelemetryModeManagerClass *tmmc = TELEMETRYMODEMANAGER_CLASS(oc);
    tmmc->getIterationTelemetryPacket = getIterationTelemetryPacket;
    tmmc->first = first;
    tmmc->next = next;
    tmmc->isIterationFinished = isIterationFinished;

    ModeManagerClass *mmc = MODEMANAGER_CLASS(oc);
    mmc->allocateMemory = allocateMemory;
    mmc->update = update;

    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_DC_PUSTELEMETRYMODEMANAGER,
    .parent = TYPE_TELEMETRYMODEMANAGER,
    .instance_size = sizeof(DC_PUSTelemetryModeManager),
    .abstract = false,
    .class_size = sizeof(DC_PUSTelemetryModeManagerClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void DC_PUSTelemetryModeManager_register(void)
{
    type_register_static(&type_info);
}
