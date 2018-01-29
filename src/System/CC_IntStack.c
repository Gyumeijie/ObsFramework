//
//
// CC_IntStack.h
//
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../Event/DC_EventRepository.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"

#include "CC_IntStack.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void CC_IntStack_push(CC_IntStack *This, int newItem)
{
   assert((This->pStack != pNULL));

   if (CC_IntStack_isFull(This)) {
       DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
       DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
       dc_erc->create(dc_er, (CC_RootObject*)This, EVT_STACK_FULL);
   } else {
       This->pStack[This->stackPointer] = newItem;
       This->stackPointer++;
   }

   assert(This->stackPointer <= This->size);
}

int CC_IntStack_pop(CC_IntStack *This)
{
   assert((This->pStack != pNULL));

   if (CC_IntStack_isEmpty(This)) {
       DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
       DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
       dc_erc->create(dc_er, (CC_RootObject*)This, EVT_STACK_EMPTY);
       return pNULL;
   } else {
       This->stackPointer--;
       return This->pStack[This->stackPointer];
   }
}

void CC_IntStack_setStackSize(CC_IntStack *This, unsigned int size)
{
   assert(This->size == 0);      // should not be called more than once
   assert(size > 0);             // stack size must be greater than zero

   This->pStack = g_malloc(sizeof(int)*size);
   assert(This->pStack != pNULL);
   This->size = size;
   This->stackPointer = 0;
}

unsigned int CC_IntStack_getStackSize(const CC_IntStack *This)
{
   return This->size;
}

unsigned int CC_IntStack_getNumberOfItems(const CC_IntStack *This)
{
    return This->stackPointer;
}

bool CC_IntStack_isEmpty(const CC_IntStack *This)
{
   assert((This->pStack != pNULL));
   return (This->stackPointer == 0);
}

bool CC_IntStack_isFull(const CC_IntStack *This)
{
   assert((This->pStack != pNULL));
   return (This->stackPointer == This->size);
}

void CC_IntStack_reset(CC_IntStack *This)
{
   assert((This->pStack != pNULL));
   This->stackPointer = 0;
}



///////////////////////////////////////////////////////////////////////////////
//
//                    non-pure virtual  method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Perform a class-specific configuration check on a stack object:
 * verify that the stack size
 * has a legal value.
 * @return true if the object is configured, false otherwise
 */
static bool isObjectConfigured(void *obj)
{ 
    CC_RootObjectClass *cc_roc = GET_CLASS(TYPE_CC_ROOTOBJECT);
    CC_IntStack *This = CC_INTSTACK(obj);

    // Check configuration of super object
    if (!cc_roc->isObjectConfigured(obj)) {
        return NOT_CONFIGURED;
    }

    if ((This->pStack == pNULL)) {
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
    CC_IntStack *This = CC_INTSTACK(obj);
    This->size = 0;
    This->stackPointer = 0;
    This->pStack = pNULL;

	CC_RootObject_setClassId((CC_RootObject*)obj, ID_INTSTACK);
}

CC_IntStack* CC_IntStack_new(void)
{
    return (CC_IntStack*)object_new(TYPE_CC_INTSTACK);
}



///////////////////////////////////////////////////////////////////////////////
//
//                   binding and type registration
//
///////////////////////////////////////////////////////////////////////////////

static void class_init(ObjectClass *oc, void *data)
{
    CC_RootObjectClass *cc_roc = CC_ROOTOBJECT_CLASS(oc);
    cc_roc->isObjectConfigured = isObjectConfigured;
}

static const TypeInfo type_info = {
    .name = TYPE_CC_INTSTACK,
    .parent = TYPE_CC_ROOTOBJECT,
    .instance_size = sizeof(CC_IntStack),
    .abstract = false,
    .class_size = sizeof(CC_IntStackClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void CC_IntStack_register(void)
{
    type_register_static(&type_info);
}
