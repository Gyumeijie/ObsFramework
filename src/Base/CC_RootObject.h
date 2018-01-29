//
//
// CC_RootObject.h
//
//
// Change Record:

#ifndef CC_ROOTOBJECT_H
#define CC_ROOTOBJECT_H

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "../Qom/object.h"

/** 
* Base class from which most framework classes are - directly or indirectly -
* derived.
* This class defines four attributes and four services that are made available to
* its children classes.
* The attributes are: <ul>
* <li>The instance identifier,</li>
* <li>The class identifier,</li>
* <li>The system event repository,</li>
* <li>The system data pool, and</li>
* <li>The system parameter database.</li>
* </ul>
* The <i>instance identifier</i> is an integer that uniquely identifies each
* object instantiated from this class or its subclasses.
* The instance identifier is automatically assigned by the
* <code>CC_RootObject</code> constructor when a new instance of this class
* is created. It can be read but cannot be changed after an object has
* been created.
* <p>
* The <i>class identifier</i> is an integer that uniquely identifies each
* class derived from <code>CC_RootObject</code>.
* It is useful during debugging and could be used to implement a simple form of
* run-time type identification.
* The class identifier should be set during the application instantiation
* phase and it is intended never to be changed afterwards.
* Only concrete classes are endowed with a class identifier.
* <p>
* The <i>system data pool</i> is an instance of class <code>DataPool</code> that
* is implemented as a static plug-in component for class <code>CC_RootObject</code>. 
* In general, applications instantiated
* from the OBS Framework should have only one data pool component. The 
* <code>CC_RootObject</code> class makes this single data pool instance
* globally accessible to all OBS Framework classes.
* <p>
* The <i>system event repository</i> is an instance of class <code>DC_EventRepository</code> that
* is implemented as a static plug-in component for class <code>CC_RootObject</code>. 
* In general, applications instantiated
* from the OBS Framework should use only one event repository. The 
* <code>CC_RootObject</code> class makes this single event repository instance
* globally accessible to all OBS Framework classes.
* <p>
* The <i>system parameter database</i> is an instance of class <code>ParameterDatabase</code> that
* is implemented as a static plug-in component for class <code>CC_RootObject</code>. 
* In general, applications instantiated
* from the OBS Framework should have only one parameter database component. The 
* <code>CC_RootObject</code> class makes this single parameter database instance
* globally accessible to all OBS Framework classes.
* <p>
* The services implemented by the <code>CC_RootObject</code> class are: <ul>
* <li>a object configuration check service,</li>
* <li>a system configuration check service, and</li>
* <li>a tracing service.</li>
* </ul>
* The <i>object configuration check service</i> allows an external entity to
* ask an object instantiated from a class derived from 
* <CODE>CC_RootObject</CODE> to check whether it is
* configured.
* The term <i>configuration</i> is used to designate the operations that are
* performed on an object during the
* application initialization phase to prepare it to perform its allotted
* task during the application operational phase.
* Generally speaking, an object is configured if all its plug-in
* objects have been loaded and if all its internal data structures have been
* created and initialized.
* <p>
* The <i>system configuration check service</i> allows an external entity to
* verify whether all objects instantiated from a class derived from 
* <CODE>CC_RootObject</CODE> are configured.
* The <CODE>CC_RootObject</CODE> class internally defines a static data
* structure that holds references to all objects that
* have been instantiated from its subclasses.
* This data structure is called the <i>system list</i>.
* The system list data structure is loaded by the <CODE>RootObject</CODE>
* constructor: every time a new object is created, its
* reference is loaded into the data structure.
* The system configuration check service goes through the objects in the
* system list data structure and performs a
* configuration check on each one of them.
* If any of the objects in the system list reports: "not
* configured", then the system configuration
* service reports: "system not configured".
* The system configuration check should be performed at the end of the
* framework instantiation phase to
* confirm the correctness of the instantiation procedure.
* <p>
* The <i>tracing service</i> allows an object instantiated from a class derived from 
* <CODE>CC_RootObject</CODE> to ask for a trace
* signal to be generated.
* The requesting object only has to specify an identifier defining the
* content of the trace signal.
* All other operations related to the sending of the trace signal are handled 
* by a static plug-in object of type <code>Tracer</code>.
* Two types of tracing signals can be generated: synch trace and
* and packet trace.
* The presence of this service in the root class means that all framework
* objects have easy access to the tracing
* service and can easily ask for trace signals to be sent to an external
* test set-up.
* @todo change the name of isObjectConfigured to isConfigured
* @todo fix the policy for inline methods. Currently, all header files that define
* inline methods include the corresponding "_inl" file. This should make it 
* unnecessary for the "_inl" file to be included by the body files. This must be checked
* on the ERC32 simulator. If confirmed, all inclusions of "_inl" files in body
* files should be removed.
* @see DC_EventRepository
* @see DataPool
* @see ParameterDatabase
* @see Tracer
* @author Alessandro Pasetti (P&P Software GmbH)
* @version 1.0
* @ingroup Base
*/

#define TYPE_CC_ROOTOBJECT "cc_rootobject"

void CC_RootObject_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                       class and struct
//
///////////////////////////////////////////////////////////////////////////////


struct CC_RootObject {
   Object parent;

   TD_InstanceId instanceId;
   TD_ClassId classId;
}; 


struct CC_RootObjectClass {
   ObjectClass parent_class;
   
   bool (*isObjectConfigured)(void *obj); 
};


#define CC_ROOTOBJECT_GET_CLASS(obj) \
        OBJECT_GET_CLASS(CC_RootObjectClass, obj, TYPE_CC_ROOTOBJECT) 

#define CC_ROOTOBJECT_CLASS(klass) \
        OBJECT_CLASS_CHECK(CC_RootObjectClass, klass, TYPE_CC_ROOTOBJECT)

#define CC_ROOTOBJECT(obj) \
        OBJECT_CHECK(CC_RootObject, obj, TYPE_CC_ROOTOBJECT)


CC_RootObject* CC_RootObject_new(void);
  

///////////////////////////////////////////////////////////////////////////////
//
//                          class method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Implement the system configuration check service.
 * The method returns true if the system is correctly configured.
 * The system is configured if all the objects instantiated from
 * this class or its subclasses created up to
 * the time the method is called
 * are configured (i.e. if their <code>isObjectConfigured</code> 
 * method returns true).
 * Thus, a pseudo-code implementation of this method is: <PRE>
 *   for (int i=0; i smaller than NumberOfCreatedObjects; i++)
 *   if (!systemList[i].isObjectConfigured())
 *           return false;
 *   return true;   </PRE>
 * where <CODE>systemList</CODE> holds the list of framework objects
 * created to date.
 * <p>
 * This is a static method because the system list data structure upon
 * which it acts is a static structure.
 * <p>
 * @return true if the system is configured, false otherwise.
 */
bool CC_RootObject_isSystemConfigured(void);

/**
 * Set the size of the system list representing the maximum number of
 * objects that can be instantiated
 * from class <CODE>RootObject</CODE> and its derived classes.
 * The <CODE>RootObject</CODE> class maintains an internal data structure
 * - the system list - where all created
 * instances of this and derived classes are held.
 * This method causes memory for this data structure to be allocated and
 * the data structure to be
 * initialized.
 * <p>
 * This is a static method because it initializes a data structure - the
 * system list - that is static.
 * <p>
 * This is an initialization method.
 * It should be called before any object of type <CODE>RootObject</CODE>
 * is instantiated. It should not be called more than once.
 * @param systemListSize the maximum number of framework objects that can
 * be instantiated in the
 * application
 */
void CC_RootObject_setSystemListSize(TD_InstanceId systemListSize);

/**
 * Return the size of the system list representing the maximum number of
 * objects that can be instantiated
 * from class <CODE>RootObject</CODE> and its derived classes.
 * <p>
 * @see #setSystemListSize
 * @return systemListSize the system list size
 */
TD_InstanceId CC_RootObject_getSystemListSize(void);

/**
 * Setter method for the event repository plug-in component.
 * The event repository thus loaded is used to store the event reports
 * created with the event reporting service.
 * This method is static to ensure that all event reports created by
 * framework objects are sent to the
 * same event repository.
 */
void CC_RootObject_setEventRepository(DC_EventRepository *pEventRepository);

/**
 * Getter method for the event repository plug-in component.
 */
DC_EventRepository* CC_RootObject_getEventRepository(void);

/**
 * Setter method for the system parameter database.
 */
void CC_RootObject_setParameterDatabase(ParameterDatabase *pDatabase);

/**
 * Getter method for the system parameter database.
 */
ParameterDatabase* CC_RootObject_getParameterDatabase(void);

/**
 * Setter method for the system data pool.
 */
void CC_RootObject_setDataPool(DataPool *pDataPool);

/**
 * Getter method for the system data pool.
*/
DataPool* CC_RootObject_getDataPool(void);

/**
 * Load the tracer plug-in object.
 * The tracer thus loaded is used to implement the tracing service.
 * This method is static because all tracing signals are routed through
 * the same tracing interface
 */
void CC_RootObject_setTracer(Tracer *pTracer);

/**
 * Getter method for the tracer plug-in.
 */
Tracer* CC_RootObject_getTracer(void);

/**
 * Implement the synch tracing service offered by the root class to all
 * its children classes.
 * When an object needs to send a synch trace signal, it calls this
 * method and passes to it the identifier of
 * the trace signal.
 * The sending of the signal is internally handled by the tracer plug-in
 * object.
 * Thus, a pseudo-code implementation for this method is as follows:
 * <PRE>
 *   tracer.sendSynchTrace(traceId)  </PRE>
 * where <CODE>tracer</CODE> is the tracer plug-in object.
 * <p>
 * @see #setTracer
 * @see Tracer
 * @param traceId identifier of the synch trace signal
 */
void CC_RootObject_synchTrace(TD_TraceItem traceId);

/**
 * Implement the packet tracing service offered by the root class to all
 * its children classes.
 * When an object needs to send a packet trace signal, it calls this
 * method and passes to it the tracer
 * packet data.
 * The sending of the signal is internally handled by the tracer plug-in
 * object.
 * Thus, a pseudo-code implementation for this method is as follows:
 * <PRE>
 *   tracer.sendPacketTrace(n,traceData)  </PRE>
 * where <CODE>tracer</CODE> is the tracer plug-in object.
 * <p>
 * @see #setTracer
 * @see Tracer
 * @param n number of trace data elements
 * @param traceData array of trace data
 */
void CC_RootObject_packetTrace(unsigned int n, TD_TraceItem traceData[]);


///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Return the instance identifier of an object.
 * The instance identifier is defined when an object is created and
 * cannot be altered afterwards.
 */
TD_InstanceId CC_RootObject_getInstanceId(const CC_RootObject *This);

/**
 * Return the class identifier of an object.
 * The class identifier is defined when an object is initially configured 
 * and should not be altered afterwards.
 */
TD_ClassId CC_RootObject_getClassId(const CC_RootObject *This);

/**
 * Set the class identifier of an object.
 * The class identifier should be set when the application is
 * configured and never changed afterwards.
 * <p>
 * This is an initialization method.
 * <p>
 * @param classId the class identifier of the class from which the object
 * is instantiated
 */
void CC_RootObject_setClassId(CC_RootObject *This, TD_ClassId classId);


#endif
