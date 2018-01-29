//
//
// CC_RootObject.cpp
//
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../System/Tracer.h"
#include "CC_RootObject.h"


///////////////////////////////////////////////////////////////////////////////
//
//                           class data 
//
///////////////////////////////////////////////////////////////////////////////

static TD_InstanceId CC_RootObject_instanceCounter = 0;

static DC_EventRepository* CC_RootObject_pEventRepository = pNULL;

static Tracer* CC_RootObject_pTracer = pNULL;

static CC_RootObject** CC_RootObject_pSystemList = pNULL;     

static TD_InstanceId CC_RootObject_systemListSize = 0;

static DataPool* CC_RootObject_pDataPool = pNULL;

static ParameterDatabase* CC_RootObject_pParameterDatabase = pNULL;


///////////////////////////////////////////////////////////////////////////////
//
//                       class method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

bool CC_RootObject_isSystemConfigured(void) 
{
   for (TD_InstanceId i=0; i<CC_RootObject_instanceCounter; i++) {
      CC_RootObject* ro = CC_RootObject_pSystemList[i];

      if (!CC_ROOTOBJECT_GET_CLASS(ro)->isObjectConfigured(ro)) {
         return NOT_CONFIGURED;
     }
   }

   return CONFIGURED;
}


void CC_RootObject_setSystemListSize(TD_InstanceId sysListSize)
{
   assert(CC_RootObject_pSystemList == pNULL);

   CC_RootObject_systemListSize = sysListSize;
   CC_RootObject_pSystemList = g_malloc(sysListSize*sizeof(CC_RootObject*));

   for (TD_InstanceId i=0; i<CC_RootObject_systemListSize; i++) {
       CC_RootObject_pSystemList[i] = pNULL;
   }
}


TD_InstanceId CC_RootObject_getSystemListSize(void) 
{
    return CC_RootObject_systemListSize;
}


void CC_RootObject_setEventRepository(DC_EventRepository *pEventRep)
{
    assert(pEventRep != pNULL);
    CC_RootObject_pEventRepository = pEventRep;
}


DC_EventRepository* CC_RootObject_getEventRepository(void)
{
    assert(CC_RootObject_pEventRepository != pNULL);
    return CC_RootObject_pEventRepository;
}


void CC_RootObject_setParameterDatabase(ParameterDatabase *pDatabase)
{
    assert(pDatabase != pNULL);
    CC_RootObject_pParameterDatabase = pDatabase;
}


ParameterDatabase* CC_RootObject_getParameterDatabase(void)
{
    assert(CC_RootObject_pParameterDatabase != pNULL);
    return CC_RootObject_pParameterDatabase;
}


void CC_RootObject_setDataPool(DataPool *pPool)
{
    assert(pPool != pNULL);
    CC_RootObject_pDataPool = pPool;
}


DataPool* CC_RootObject_getDataPool(void) 
{
    assert(CC_RootObject_pDataPool != pNULL);
    return CC_RootObject_pDataPool;
}


void CC_RootObject_setTracer(Tracer *pTrace) 
{
    assert(pTrace != pNULL);
    CC_RootObject_pTracer = pTrace;
}


Tracer* CC_RootObject_getTracer(void) 
{
    assert(CC_RootObject_pTracer != pNULL);
    return CC_RootObject_pTracer;
}


void CC_RootObject_packetTrace(unsigned int n, TD_TraceItem traceData[]) 
{
   assert((CC_RootObject_pTracer != pNULL) && (traceData != pNULL));
   Tracer_sendPacketTrace(CC_RootObject_pTracer, n, traceData);
}


void CC_RootObject_synchTrace(TD_TraceItem traceId)
{
   assert(CC_RootObject_pTracer != pNULL);
   Tracer_sendSynchTrace(CC_RootObject_pTracer, traceId);
}


///////////////////////////////////////////////////////////////////////////////
//
//                  non-virtual member method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

TD_InstanceId CC_RootObject_getInstanceId(const CC_RootObject *This)
{
    return This->instanceId;
}

TD_ClassId CC_RootObject_getClassId(const CC_RootObject *This)
{
    return This->classId;
}

void CC_RootObject_setClassId(CC_RootObject *This, TD_ClassId classId)
{
    This->classId = classId;
}


///////////////////////////////////////////////////////////////////////////////
//
//                non-pure virtual method(s) definition
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Implement the object configuration check service.
 * The method returns true if the object is correctly configured.
 * A <CODE>RootObject</CODE> is configured if: <ul>
 * <li>the event repository has been loaded</li>
 * <li>the parameter database has been loaded</li>
 * <li>the data pool has been loaded</li>
 * <li>the tracer has been loaded</li>
 * <li>the class identifier has a legal value</li>
 * </ul>
 * The configuration check is class-specific and derived classes may have
 * to provide their own implementation.
 * Derived classes should however provide only incremental
 * implementations.
 * Consider for instance a class B that is derived from a class A.
 * The implementation of <CODE>isConfigured</CODE> for class B should be
 * as follows:<PRE>
 *   bool isConfigured() {
 *   if (!super.isConfigured())
 *           return false;
 *   . . .  // perform configuration checks specific to class A
 *   } </PRE>
 * In this way, each class benefits from the implementation of its super
 * class.
 * @return true if the object is configured, false otherwise.
 */
static bool isObjectConfigured(void* obj) 
{
    return ((CC_RootObject_pEventRepository != pNULL) && 
            (CC_RootObject_pTracer != pNULL) &&
            (CC_RootObject_pSystemList != pNULL) &&
            (CC_RootObject_pDataPool != pNULL) &&
            (CC_RootObject_pParameterDatabase != pNULL));
}


///////////////////////////////////////////////////////////////////////////////
//
//               object constructor and destuctor 
//
///////////////////////////////////////////////////////////////////////////////

static void instance_init(Object *obj) 
{
    assert(CC_RootObject_pSystemList != pNULL);
    assert(CC_RootObject_instanceCounter < CC_RootObject_getSystemListSize());

    CC_RootObject *This = CC_ROOTOBJECT(obj);
    This->instanceId = CC_RootObject_instanceCounter;
    CC_RootObject_setClassId(This, ID_ROOTOBJECT);

    // register newly created object in the system list.
    if (CC_RootObject_instanceCounter < CC_RootObject_getSystemListSize()) {
        CC_RootObject_pSystemList[CC_RootObject_instanceCounter] = This;
        CC_RootObject_instanceCounter++;
    }
}

CC_RootObject* CC_RootObject_new(void)
{
    Object *obj = object_new(TYPE_CC_ROOTOBJECT);
    return (CC_RootObject*)obj;
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
    .name = TYPE_CC_ROOTOBJECT,
    .parent = TYPE_OBJECT,
    .instance_size = sizeof(CC_RootObject),
    .abstract = false,
    .class_size = sizeof(CC_RootObjectClass),
    .instance_init = instance_init,
    .class_init = class_init,
    //.type_init_phase = TYPE_REGISTER_PHASE
};

void CC_RootObject_register(void)
{
     type_register_static(&type_info);
}
