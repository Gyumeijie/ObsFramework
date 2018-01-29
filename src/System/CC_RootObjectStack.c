//
//
// CC_RootObjectStack.h
//
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Event/DC_EventRepository.h"
#include "../Base/CC_RootObject.h"
#include "../Base/CC_RootObject.h"
#include "CC_RootObjectStack.h"



///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

void CC_RootObjectStack_push(CC_RootObjectStack *This, CC_RootObject *newItem)
{
   assert((This->pStack != pNULL));

   if (CC_RootObjectStack_isFull(This)) {
       DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
       DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
       dc_erc->create(dc_er, (CC_RootObject*)This, EVT_STACK_FULL);
   } else {
       This->pStack[This->stackPointer] = newItem;
       This->stackPointer++;
   }

   assert(This->stackPointer <= This->size);
}

CC_RootObject* CC_RootObjectStack_pop(CC_RootObjectStack *This)
{
   assert((This->pStack != pNULL));

   if (CC_RootObjectStack_isEmpty(This)) {
       DC_EventRepository *dc_er = CC_RootObject_getEventRepository();
       DC_EventRepositoryClass *dc_erc = DC_EVENTREPOSITORY_GET_CLASS(dc_er);
       dc_erc->create(dc_er, (CC_RootObject*)This, EVT_STACK_EMPTY);
       return pNULL;
   } else {
       This->stackPointer--;
       return This->pStack[This->stackPointer];
   }
}

void CC_RootObjectStack_setStackSize(CC_RootObjectStack *This, unsigned int size)
{
   assert(This->size == 0);      // should not be called more than once
   assert(size > 0);             // stack size must be greater than zero

   This->pStack = g_malloc(size*sizeof(CC_RootObject*));
   assert(This->pStack != pNULL);
   This->size = size;
   This->stackPointer = 0;
}

unsigned int CC_RootObjectStack_getStackSize(const CC_RootObjectStack *This)
{
   return This->size;
}

unsigned int CC_RootObjectStack_getNumberOfItems(const CC_RootObjectStack *This)
{
    return This->stackPointer;
}

bool CC_RootObjectStack_isEmpty(const CC_RootObjectStack *This)
{
   assert((This->pStack != pNULL));
   return (This->stackPointer == 0);
}

bool CC_RootObjectStack_isFull(const CC_RootObjectStack *This)
{
   assert((This->pStack != pNULL));
   return (This->stackPointer == This->size);
}

void CC_RootObjectStack_reset(CC_RootObjectStack *This)
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
    CC_RootObjectStack *This = CC_ROOTOBJECTSTACK(obj);

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
    CC_RootObjectStack *This = CC_ROOTOBJECTSTACK(obj);
    This->size = 0;
    This->stackPointer = 0;
    This->pStack = pNULL;

	CC_RootObject_setClassId((CC_RootObject*)obj, ID_ROOTOBJECTSTACK);
}

CC_RootObjectStack* CC_RootObjectStack_new(void)
{
    Object *obj = object_new(TYPE_CC_ROOTOBJECTSTACK);
    return (CC_RootObjectStack*)obj;
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
    .name = TYPE_CC_ROOTOBJECTSTACK,
    .parent = TYPE_CC_ROOTOBJECT,
    .instance_size = sizeof(CC_RootObjectStack),
    .abstract = false,
    .class_size = sizeof(CC_RootObjectStackClass),
    .instance_init = instance_init,
    .class_init = class_init,
};

void CC_RootObjectStack_register(void)
{
    type_register_static(&type_info);
}
