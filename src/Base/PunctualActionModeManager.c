//
//
// PunctualActionModeManager.c
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "PunctualActionModeManager.h"



///////////////////////////////////////////////////////////////////////////////
//
//                    pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Iteration method to iterate through the items in the set of
 * punctual actions applicable to the current operational mode. 
 * This method should be used jointly with methods: <code>next</code>, 
 * <code>isIterationFinished</code> and <code>getIterationPunctualAction</code>. 
 * Taken together, 
 * these methods allow all the items in the currently applicable set 
 * of punctual actions to be scanned. 
 * During an iteration cycle, an internal pointer, the <i>iteration
 * pointer</i>, is made to scan over all the items in the currently applicable
 * set of telemetry packets.
 * The item currently pointed at by the iteration counter can be retrieved
 * through method <code>getIterationPunctualAction</code>.
 * Thus, a typical iteration cycle might be organized as follows: <PRE>
 *      for(first(void); !isIterationFinished(void); next(void)) {
 *          pItem = getIterationPunctualAction(void);
 *          . . .    // process pItem
 *      }  </PRE>
 * @see #getIterationItem
 */
static void first(void *obj)
{
    // this is automate genenrated by converter
}

/**
 * Iteration method to be used in conjunction with methods <code>first</code>
 * and <code>isIterationFinished</code>.
 * @see #first
 */
static void next(void *obj)
{
    // this is automate genenrated by converter
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
    // this is automate genenrated by converter
}

/**
 * Return the punctual action item pointed at by the iterator.
 * This method is a type-safe wrapper for method <code>getIteratorItem</code>
 * in the superclass.
 * @see ListModeManager#getIterationItem
 * @return the punctual action item pointed at by the iterator
 */
static PunctualAction* getIterationPunctualAction(void *obj)
{
    // this is automate genenrated by converter
}



///////////////////////////////////////////////////////////////////////////////
//
//                   object constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj){}

PunctualActionModeManager* PunctualActionModeManager_new(void)
{
    Object *obj = object_new(TYPE_PUNCTUALACTIONMODEMANAGER);
    return (PunctualActionModeManager*)obj;
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    PunctualActionModeManagerClass *pammc = PUNCTUALACTIONMODEMANAGER_CLASS(oc);

    pammc->first = first;
    pammc->next = next;
    pammc->isIterationFinished = isIterationFinished;
    pammc->getIterationPunctualAction = getIterationPunctualAction;
}

static const TypeInfo type_info = {
    .name = TYPE_PUNCTUALACTIONMODEMANAGER,
    .parent = TYPE_MODEMANAGER,
    .instance_size = sizeof(PunctualActionModeManager),
    .abstract = true,
    .class_size = sizeof(PunctualActionModeManagerClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void PunctualActionModeManager_register(void)
{
    type_register_static(&type_info);
}
