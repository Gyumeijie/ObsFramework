//
//
// TelemetryListModeManager.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Event/DC_EventRepository.h"
#include "../Base/CC_RootObject.h"
#include "../Base/ModeManager.h"
#include "TelemetryListModeManager.h"


///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void TelemetryListModeManager_setListItem(TelemetryListModeManager *This, 
                                          unsigned int n, 
                                          unsigned int pos, 
                                          TelemetryPacket *pItem)
{
    const unsigned int nModes = ModeManager_getNumberOfModes((ModeManager*)This);

    assert(n < nModes);
    assert(This->listLength != pNULL);
    assert(This->listLength[n] > 0);
    assert(pos < This->listLength[n]);
    assert(pItem != pNULL);

    if ((pos < This->listLength[n]) && (n < nModes)) {
        This->list[n][pos] = pItem;
    } else {
        DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
        DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
        dc_erc->create(dc_er, (CC_RootObject*)This, EVT_ILLEGAL_MM);
    }
}

void TelemetryListModeManager_setListLength(TelemetryListModeManager *This,
                                            unsigned int n,
                                            unsigned int length)
{
    const unsigned int nModes = ModeManager_getNumberOfModes((ModeManager*)This);

    assert(This->listLength != pNULL);
    assert(This->list != pNULL);
    assert(length > 0);
    assert(n < nModes);

    This->listLength[n] = length;
    This->list[n] = g_malloc(length*sizeof(TelemetryPacket*));
    for (unsigned int i=0; i<length; i++) {
        This->list[n][i] = pNULL;
    }
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Allocate the memory for the lists. The newly allocated memory
 * is initialized with pNULL. Note that this method
 * cannot allocate all the memory required by a list mode manager because
 * this also depends on the number of items in each list. This number is loaded
 * with method: <code>setLength</code>.
 * <p>
 * This method is called by method <code>setNumberOfModes</code> in the
 * superclass <code>ModeManager</code>.
 * <p>
 * This is an initialization method. It should only be called once. The number
 * of modes should be greater than zero.
 * @see ModeManager#setNumberOfModes
 * @param numberOfModes the number of modes
 */
static void allocateMemory(void *obj, TD_Mode numberOfModes)
{
    TelemetryListModeManager *This = TELEMETRYLISTMODEMANAGER(obj);

    assert(numberOfModes > 0);
    assert(This->list == pNULL);

    This->list = g_malloc(numberOfModes*sizeof(TelemetryPacket**));
    for (TD_Mode i=0; i<numberOfModes; i++) {
        This->list[i] = pNULL;
    }

    This->listLength = g_malloc(sizeof(unsigned int)*numberOfModes);
    for (TD_Mode i=0; i<numberOfModes; i++) {
        This->listLength[i] = 0;
    }
}

/**
 * Retrieve the telemetry packet currently scanned by the iteration counter.
 * This method returns the counter-th item in the iteration list where
 * "counter" is the iteration counter.
 * This method should only be used within an iteration cycle. However, it is
 * guaranteed to return a reference to a list item at all times.
 * @see #first
 * @return the item currently scanned by the iteration counter
 */
static TelemetryPacket* getIterationTelemetryPacket(void *obj)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    TelemetryListModeManager *This = TELEMETRYLISTMODEMANAGER(obj);

    assert(cc_roc->isObjectConfigured(obj));

    if (This->counter >= This->listLength[This->iterationListIndex]) {
        This->counter = This->listLength[This->iterationListIndex] - 1;
    }

    return This->list[This->iterationListIndex][This->counter];
}

/**
 * Iteration method to iterate through the telemetry packets in the current
 * list. This method should be used jointly with methods: <code>next</code>, 
 * <code>isIterationFinished</code> and <code>getIterationTelemetryPacket</code>. 
 * Taken together, 
 * these methods allow all the items in a list to be scanned. The list
 * that is thus iterated through is called the <i>iteration list</i>.
 * The iteration list is the current list at the time method <code>first</code>
 * is called. This list is
 * guaranteed to remain unchanged in between successive calls to
 * method <code>first</code>. Thus, even if the current mode changes
 * during the iteration(for instance, following a call to method
 * <code>update</code>), the iterators will continue processing the
 * list that was active when <code>first</code> was called.
 * <p>
 * This class internally maintains an <i>iteration
 * counter</i>. During an iteration cycle, the iteration counter is
 * incremented from zero to(N-1) where N is number of items in the
 * iteration list. Method <code>first</code> resets the iteration counter
 * to 0. A call to method <code>next</code> causes the iteration counter
 * to be incremented by 1 up to the value of(N-1). Method <code>isIterationFinished</code>
 * returns true when the counter has reached the value(N-1).
 * The item currently pointed at by the iteration counter can be retrieved
 * through method <code>getIterationTelemetryPacket</code>.
 * <p>
 * Thus, a typical iteration cycle might be organized as follows: <PRE>
 *      for(first(void); !isIterationFinished(void); next(void)) {
 *          pItem = getIterationTelemetryPacket(void);
 *          . . .    // process pItem
 *      }  </PRE>
 */
static void first(void *obj)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    TelemetryListModeManager *This = TELEMETRYLISTMODEMANAGER(obj);

    assert(cc_roc->isObjectConfigured(obj));
    This->counter = 0;
    This->iterationListIndex = ModeManager_getCurrentMode(obj);
}

/**
 * Iteration method to be used in conjunction with methods <code>first</code>
 * and <code>isIterationFinished</code>.
 * @see #first
 */
static void next(void *obj)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_GET_CLASS(obj);
    TelemetryListModeManager *This = TELEMETRYLISTMODEMANAGER(obj);

    assert(cc_roc->isObjectConfigured(obj));
    This->counter++;
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
    TelemetryListModeManager *This = TELEMETRYLISTMODEMANAGER(obj);

    assert(cc_roc->isObjectConfigured(obj));
    return(This->counter == This->listLength[This->iterationListIndex]);
}

/**
 * Perform a class-specific configuration check on a telemetry list mode
 * manager: verify that all the lists have been initialized
 * and that all the items have been loaded.
 * @return true if the list mode manager is configured, false
 * otherwise.
 */
static bool isObjectConfigured(void *obj)
{
    TelemetryModeManagerClass *tmmc = GET_CLASS(TYPE_TELEMETRYMODEMANAGER);  
    TelemetryListModeManager *This = TELEMETRYLISTMODEMANAGER(obj);
    const TD_Mode nModes = ModeManager_getNumberOfModes(obj);

    if (!(CC_ROOTOBJECT_CLASS(tmmc)->isObjectConfigured(obj)) || 
         (This->list == pNULL) || 
         (This->listLength == pNULL)) {
        return NOT_CONFIGURED;
    }

    for (TD_Mode i=0; i<nModes; i++) {
        if (This->listLength[i] == pNULL) {
            return NOT_CONFIGURED;
        }
    }

    for (TD_Mode i=0; i<nModes; i++) {
        for (unsigned int j=0; j<This->listLength[i]; j++) {
            if (This->list[i][j] == pNULL) {
                return NOT_CONFIGURED;
            }
        }
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
    TelemetryListModeManager *This = TELEMETRYLISTMODEMANAGER(obj);

    This->counter = 0;
	This->list = pNULL;
	This->listLength = pNULL;
    This->iterationListIndex = 0;
}

TelemetryListModeManager* TelemetryListModeManager_new(void)
{
    Object *obj = object_new(TYPE_TELEMETRYLISTMODEMANAGER);
    return (TelemetryListModeManager*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    ModeManagerClass *mmc = MODEMANAGER_CLASS(oc);
    mmc->allocateMemory = allocateMemory;

    TelemetryModeManagerClass *tmmc = TELEMETRYMODEMANAGER_CLASS(oc);
    tmmc->getIterationTelemetryPacket = getIterationTelemetryPacket;
    tmmc->first = first;
    tmmc->next = next;
    tmmc->isIterationFinished = isIterationFinished;

    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_TELEMETRYLISTMODEMANAGER,
    .parent = TYPE_TELEMETRYMODEMANAGER,
    .instance_size = sizeof(TelemetryListModeManager),
    .abstract = false,
    .class_size = sizeof(TelemetryListModeManagerClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void TelemetryListModeManager_register(void)
{
    type_register_static(&type_info);
}
