//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// CC_TelemetryPacketFactory.h
//
// This file was automatically generated by an XSL program
//


#ifndef CC_TELEMETRYPACKETFACTORY_H
#define CC_TELEMETRYPACKETFACTORY_H


#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"   
#include "../Telemetry/DC_DummyPUSTelemetryPacket.h"  
#include "../Telemetry/DC_PUSDataReportingPacket.h"  
#include "../Telemetry/DC_PUSMemoryDumpAbsolute.h"  
#include "../Telemetry/DC_PUSMemoryDumpOffset.h"  
#include "../Telemetry/DC_PUSTcVerificationPacket.h"  
#include "../Qom/object.h"


/*
 * Dynamic factory for components of type: <code>TelemetryPacket</code>.
 * A <i>dynamic factory</i> is a component that manages a pool of instances of
 * components of a certain type. Clients of the factory can require one of these
 * instances at run-time. After the factory hands over a component instance to its
 * client, the instance is marked as "in use" and cannot be given to any other
 * clients. When the requesting client has finished using the instance, it should release
 * it by marking it as "no longer in use". This will allow the factory to make it
 * available to other clients that request it. The "in use" status of the component
 * instances is controlled through method <code>setInUse</code> declared on
 * the component instances.
 * <p>
 * A dynamic factory is configured in two steps. The first step is performed
 * by the factory constructor when the internal data structures to hold the component
 * instances are created. The second step is performed during application initialization
 * when the component instances are loaded in the factory. Reconfiguration at run time
 * during normal application operation is not allowed.
 * <p>
 * Dynamic factories are implemented as singletons. They can exist in one single instance
 * that can be accessed through the <code>getInstance</code> method.
 * The one single instance of the class is created the first time that method
 * getInstance is called. In order to avoid possible disruptions of
 * real-time behaviour, applications should ensure that this method has been called
 * at least once before the application enters its operational phase.
 * <p>
 * This factory manages the following component instances:<ul>  
 * <li>Number of instances of type <code>DC_DummyPUSTelemetryPacket</code>: 2</li>    
 * <li>Number of instances of type <code>DC_PUSDataReportingPacket</code>: 2</li>    
 * <li>Number of instances of type <code>DC_PUSMemoryDumpAbsolute</code>: 1</li>    
 * <li>Number of instances of type <code>DC_PUSMemoryDumpOffset</code>: 1</li>    
 * <li>Number of instances of type <code>DC_PUSTcVerificationPacket</code>: 1</li>    
 * </ul>
 * The code for this class was automatically generated by an XSL program processing
 * the XML-based application model.    
 * @ingroup TelemetryPacket
 * @see TelemetryPacket
 * @author Automatically Generated Class
 * @version 1.0
 */
#define TYPE_CC_TELEMETRYPACKETFACTORY "cc_telemetrypacketfactory"

void CC_TelemetryPacketFactory_register(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class and struct
//
///////////////////////////////////////////////////////////////////////////////

struct CC_TelemetryPacketFactory {
    CC_RootObject parent;

    unsigned int sizeDummyPUSTelemetryPacket;
    DC_DummyPUSTelemetryPacket **poolDummyPUSTelemetryPacket;

    unsigned int sizePUSDataReportingPacket;
    DC_PUSDataReportingPacket **poolPUSDataReportingPacket;

    unsigned int sizePUSMemoryDumpAbsolute;
    DC_PUSMemoryDumpAbsolute **poolPUSMemoryDumpAbsolute;

    unsigned int sizePUSMemoryDumpOffset;
    DC_PUSMemoryDumpOffset **poolPUSMemoryDumpOffset;

    unsigned int sizePUSTcVerificationPacket;
    DC_PUSTcVerificationPacket **poolPUSTcVerificationPacket;
};


struct CC_TelemetryPacketFactoryClass {
    CC_RootObjectClass parent_class;
};


#define CC_TELEMETRYPACKETFACTORY_GET_CLASS(obj) \
        OBJECT_GET_CLASS(CC_TelemetryPacketFactoryClass, \
                                           obj, TYPE_CC_TELEMETRYPACKETFACTORY)

#define CC_TELEMETRYPACKETFACTORY_CLASS(klass) \
        OBJECT_CLASS_CHECK(CC_TelemetryPacketFactoryClass, \
                                         klass, TYPE_CC_TELEMETRYPACKETFACTORY)

#define CC_TELEMETRYPACKETFACTORY(obj) \
        OBJECT_CHECK(CC_TelemetryPacketFactory, \
                                           obj, TYPE_CC_TELEMETRYPACKETFACTORY)


CC_TelemetryPacketFactory* CC_TelemetryPacketFactory_new(void);


///////////////////////////////////////////////////////////////////////////////
//
//                            class method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * Get the single instance of this singleton class. If the instance does not
 * yet exist, it is created.
 */
CC_TelemetryPacketFactory* CC_TelemetryPacketFactory_getInstance(void);



///////////////////////////////////////////////////////////////////////////////
//
//                 non-virtual member method(s) declaration
//
///////////////////////////////////////////////////////////////////////////////

/**
 * General interface for all TelemetryPacket setter methods
 *
 * @param i the index in the internal array
 * @param pItem the component instance
 */
void CC_TelecommandFactory_setTelemetryPacket
(
    CC_TelemetryPacketFactory *This, 
    unsigned int i,
    TelemetryPacket *pItem
);

/**
 * Load one instance of type <code>DC_DummyPUSTelemetryPacket</code> in the
 * factory. The component instances managed by the factory are internally stored in an
 * array. This method loads the i-th element of the array. The argument i should lie
 * in the interval [0, N-1] where N is the number of component instances of type
 * <code>DC_DummyPUSTelemetryPacket</code>. The value of N is defined by
 * the class constructor.
 * <p>
 * The "in use" status of a newly loaded component is initialized
 * to: "component is not in use".
 * <p>
 * This is an initialization method that should only be called during the application
 * configuration phase.
 * @param i the index in the internal array
 * @param pItem the component instance
 */
static void setDummyPUSTelemetryPacket
(
    CC_TelemetryPacketFactory *This, 
    unsigned int i,
    DC_DummyPUSTelemetryPacket *pItem
);

/**
 * Return the number of component instances of type <code>DC_DummyPUSTelemetryPacket</code>
 * that are currently allocated. A component instance is allocated if its "in use" status is
 * equal to: "component is in use".
 * @return the number of allocated component instances
 */
unsigned int CC_TelemetryPacketFactory_getNumberDummyPUSTelemetryPacket
(
    CC_TelemetryPacketFactory *This
);

/**
 * Return the number of component instances of type <code>DC_DummyPUSTelemetryPacket</code>
 * that are in the factory. The value returned is the maximum number of component instances of
 * type <code>DC_DummyPUSTelemetryPacket</code> that can be allocated.
 * @return the total number of component instances in the factory of
 * type <code>DC_DummyPUSTelemetryPacket</code>
 */
unsigned int CC_TelemetryPacketFactory_getCapacityDummyPUSTelemetryPacket
(
    CC_TelemetryPacketFactory *This
);

/**
 * Allocate one instance of type <code>DC_DummyPUSTelemetryPacket</code>.
 * This method scans all the entries in the factory of type <code>DC_DummyPUSTelemetryPacket</code>
 * and returns the first one which is not in use. 
 * Before being returned to the caller, 
 * the status of the component instance is changed to: "in use". A client that receives
 * a component instance through a call to this method, should release the instance when it
 * no longer needs it. This can be done by calling
 * method <code>CC_TelemetryPacketFactory_setInUse(false)</code> on the component itself.
 * <p>
 * If no free component instances are found, then the method returns null. Note that no
 * event report is generated to record the failure to allocate a component instance. Event
 * reporting is the responsibility of the caller.      
 * @return the allocated component instance or null if no free instances were found
 */
DC_DummyPUSTelemetryPacket* CC_TelemetryPacketFactory_allocateDummyPUSTelemetryPacket
(
    CC_TelemetryPacketFactory *This
);

/**
 * Check whether a non-allocated component instance of type <code>DC_DummyPUSTelemetryPacket</code>
 * is available within the factory. If this method return true, then the corresponding
 * <code>allocate</code> method is guaranteed to return a non-null value.
 * The method parameters are used as in the corresponding <code>allocate</code> method.
 * @see #allocateDC_DummyPUSTelemetryPacket     
 * @return true if free instances of type DC_DummyPUSTelemetryPacket are available, 
 * false otherwise
 */
bool CC_TelemetryPacketFactory_isFreeDummyPUSTelemetryPacket
(
    CC_TelemetryPacketFactory *This
);

/**
 * Load one instance of type <code>DC_PUSDataReportingPacket</code> in the
 * factory. The component instances managed by the factory are internally stored in an
 * array. This method loads the i-th element of the array. The argument i should lie
 * in the interval [0, N-1] where N is the number of component instances of type
 * <code>DC_PUSDataReportingPacket</code>. The value of N is defined by
 * the class constructor.
 * <p>
 * The "in use" status of a newly loaded component is initialized
 * to: "component is not in use".
 * <p>
 * This is an initialization method that should only be called during the application
 * configuration phase.
 * @param i the index in the internal array
 * @param pItem the component instance
 */
static void setPUSDataReportingPacket
(
    CC_TelemetryPacketFactory *This,
    unsigned int i, 
    DC_PUSDataReportingPacket *pItem
);

/**
 * Return the number of component instances of type <code>DC_PUSDataReportingPacket</code>
 * that are currently allocated. A component instance is allocated if its "in use" status is
 * equal to: "component is in use".
 * @return the number of allocated component instances
 */
unsigned int CC_TelemetryPacketFactory_getNumberPUSDataReportingPacket
(
    CC_TelemetryPacketFactory *This
);

/**
 * Return the number of component instances of type <code>DC_PUSDataReportingPacket</code>
 * that are in the factory. The value returned is the maximum number of component instances of
 * type <code>DC_PUSDataReportingPacket</code> that can be allocated.
 * @return the total number of component instances in the factory of
 * type <code>DC_PUSDataReportingPacket</code>
 */
unsigned int CC_TelemetryPacketFactory_getCapacityPUSDataReportingPacket
(
    CC_TelemetryPacketFactory *This
);

/**
 * Allocate one instance of type <code>DC_PUSDataReportingPacket</code>.
 * This method scans all the entries in the factory of type <code>DC_PUSDataReportingPacket</code>
 * and returns the first one which is not in use. 
 * In addition to verifyin that the returned component is not in use, this method also performs a check
 * on the value of the component configuration parameters. The folloging configuration parameters 
 * are checked: DefinitionBufferSize, ValueBufferSize, MaxNumberFA.
 * This method has a parameter matching each component configuration parameter. A component instance is
 * returned only if the value of the component configuration parameter is greater than or equal to the method
 * parameter. 
 * Before being returned to the caller, 
 * the status of the component instance is changed to: "in use". A client that receives
 * a component instance through a call to this method, should release the instance when it
 * no longer needs it. This can be done by calling
 * method <code>CC_TelemetryPacketFactory_setInUse(false)</code> on the component itself.
 * <p>
 * If no free component instances are found, then the method returns null. Note that no
 * event report is generated to record the failure to allocate a component instance. Event
 * reporting is the responsibility of the caller. 
 * @param DefinitionBufferSize minimum value for a component configuration parameter 
 * @param ValueBufferSize minimum value for a component configuration parameter 
 * @param MaxNumberFA minimum value for a component configuration parameter      
 * @return the allocated component instance or null if no free instances were found
 */
DC_PUSDataReportingPacket* CC_TelemetryPacketFactory_allocatePUSDataReportingPacket
(
    CC_TelemetryPacketFactory *This, 
    unsigned int DefinitionBufferSize, 
    unsigned int ValueBufferSize, 
    unsigned int MaxNumberFA
);

/**
 * Check whether a non-allocated component instance of type <code>DC_PUSDataReportingPacket</code>
 * is available within the factory. If this method return true, then the corresponding
 * <code>allocate</code> method is guaranteed to return a non-null value.
 * The method parameters are used as in the corresponding <code>allocate</code> method.
 * @see #allocateDC_PUSDataReportingPacket
 * @param DefinitionBufferSize minimum value for a component configuration parameter 
 * @param ValueBufferSize minimum value for a component configuration parameter 
 * @param MaxNumberFA minimum value for a component configuration parameter      
 * @return true if free instances of type DC_PUSDataReportingPacket are available, 
 * false otherwise
 */
bool CC_TelemetryPacketFactory_isFreePUSDataReportingPacket
(
    CC_TelemetryPacketFactory *This,  
    unsigned int DefinitionBufferSize, 
    unsigned int ValueBufferSize, 
    unsigned int MaxNumberFA
);

/**
 * Return the PUS data reporting packet that is currently allocated and whose SID is
 * equal to the value of the argument <code>sid</code>.
 * This method scans all the instances of type DC_PUSDataReportingPacket in the
 * factory and, if it finds one which is CC_TelemetryPacketFactory_allocated(its status is "in use") and with the SID
 * equal to <code>sid</code>, it returns it. Otherwise, a null pointer is returned.
 * @param sid the structure CC_TelemetryPacketFactory_identifier(SID) of the PUS data reporting packet
 * @return the sought PUS data reporting packet or null if no allocated data reporting packet
 * with SID equal to <code>sid</code> is found
 */
DC_PUSDataReportingPacket* CC_TelemetryPacketFactory_getPUSDataReportingPacket
(
    CC_TelemetryPacketFactory *This, 
    TD_SID sid
);

/**
 * Load one instance of type <code>DC_PUSMemoryDumpAbsolute</code> in the
 * factory. The component instances managed by the factory are internally stored in an
 * array. This method loads the i-th element of the array. The argument i should lie
 * in the interval [0, N-1] where N is the number of component instances of type
 * <code>DC_PUSMemoryDumpAbsolute</code>. The value of N is defined by
 * the class constructor.
 * <p>
 * The "in use" status of a newly loaded component is initialized
 * to: "component is not in use".
 * <p>
 * This is an initialization method that should only be called during the application
 * configuration phase.
 * @param i the index in the internal array
 * @param pItem the component instance
 */
static void setPUSMemoryDumpAbsolute
(
    CC_TelemetryPacketFactory *This,
    unsigned int i,
    DC_PUSMemoryDumpAbsolute *pItem
);

/**
 * Return the number of component instances of type <code>DC_PUSMemoryDumpAbsolute</code>
 * that are currently allocated. A component instance is allocated if its "in use" status is
 * equal to: "component is in use".
 * @return the number of allocated component instances
 */
unsigned int CC_TelemetryPacketFactory_getNumberPUSMemoryDumpAbsolute
(
    CC_TelemetryPacketFactory *This
);

/**
 * Return the number of component instances of type <code>DC_PUSMemoryDumpAbsolute</code>
 * that are in the factory. The value returned is the maximum number of component instances of
 * type <code>DC_PUSMemoryDumpAbsolute</code> that can be allocated.
 * @return the total number of component instances in the factory of
 * type <code>DC_PUSMemoryDumpAbsolute</code>
 */
unsigned int CC_TelemetryPacketFactory_getCapacityPUSMemoryDumpAbsolute
(
    CC_TelemetryPacketFactory *This
);

/**
 * Allocate one instance of type <code>DC_PUSMemoryDumpAbsolute</code>.
 * This method scans all the entries in the factory of type <code>DC_PUSMemoryDumpAbsolute</code>
 * and returns the first one which is not in use. 
 * In addition to verifyin that the returned component is not in use, this method also performs a check
 * on the value of the component configuration parameters. The folloging configuration parameters 
 * are checked: MaxNumberBlocks, DumpBufferSize.
 * This method has a parameter matching each component configuration parameter. A component instance is
 * returned only if the value of the component configuration parameter is greater than or equal to the method
 * parameter. 
 * Before being returned to the caller, 
 * the status of the component instance is changed to: "in use". A client that receives
 * a component instance through a call to this method, should release the instance when it
 * no longer needs it. This can be done by calling
 * method <code>CC_TelemetryPacketFactory_setInUse(false)</code> on the component itself.
 * <p>
 * If no free component instances are found, then the method returns null. Note that no
 * event report is generated to record the failure to allocate a component instance. Event
 * reporting is the responsibility of the caller. 
 * @param MaxNumberBlocks minimum value for a component configuration parameter 
 * @param DumpBufferSize minimum value for a component configuration parameter      
 * @return the allocated component instance or null if no free instances were found
 */
DC_PUSMemoryDumpAbsolute* CC_TelemetryPacketFactory_allocatePUSMemoryDumpAbsolute
(
    CC_TelemetryPacketFactory *This, 
    unsigned int MaxNumberBlocks, 
    unsigned int DumpBufferSize
);

/**
 * Check whether a non-allocated component instance of type <code>DC_PUSMemoryDumpAbsolute</code>
 * is available within the factory. If this method return true, then the corresponding
 * <code>allocate</code> method is guaranteed to return a non-null value.
 * The method parameters are used as in the corresponding <code>allocate</code> method.
 * @see #allocateDC_PUSMemoryDumpAbsolute
 * @param MaxNumberBlocks minimum value for a component configuration parameter 
 * @param DumpBufferSize minimum value for a component configuration parameter      
 * @return true if free instances of type DC_PUSMemoryDumpAbsolute are available, 
 * false otherwise
 */
bool CC_TelemetryPacketFactory_isFreePUSMemoryDumpAbsolute
(
    CC_TelemetryPacketFactory *This, 
    unsigned int MaxNumberBlocks, 
    unsigned int DumpBufferSize
);

/**
 * Load one instance of type <code>DC_PUSMemoryDumpOffset</code> in the
 * factory. The component instances managed by the factory are internally stored in an
 * array. This method loads the i-th element of the array. The argument i should lie
 * in the interval [0, N-1] where N is the number of component instances of type
 * <code>DC_PUSMemoryDumpOffset</code>. The value of N is defined by
 * the class constructor.
 * <p>
 * The "in use" status of a newly loaded component is initialized
 * to: "component is not in use".
 * <p>
 * This is an initialization method that should only be called during the application
 * configuration phase.
 * @param i the index in the internal array
 * @param pItem the component instance
 */
static void setPUSMemoryDumpOffset
(
    CC_TelemetryPacketFactory *This, 
    unsigned int i, 
    DC_PUSMemoryDumpOffset *pItem
);

/**
 * Return the number of component instances of type <code>DC_PUSMemoryDumpOffset</code>
 * that are currently allocated. A component instance is allocated if its "in use" status is
 * equal to: "component is in use".
 * @return the number of allocated component instances
 */
unsigned int CC_TelemetryPacketFactory_getNumberPUSMemoryDumpOffset
(
    CC_TelemetryPacketFactory *This
);

/**
 * Return the number of component instances of type <code>DC_PUSMemoryDumpOffset</code>
 * that are in the factory. The value returned is the maximum number of component instances of
 * type <code>DC_PUSMemoryDumpOffset</code> that can be allocated.
 * @return the total number of component instances in the factory of
 * type <code>DC_PUSMemoryDumpOffset</code>
 */
unsigned int CC_TelemetryPacketFactory_getCapacityPUSMemoryDumpOffset
(
    CC_TelemetryPacketFactory *This
);

/**
 * Allocate one instance of type <code>DC_PUSMemoryDumpOffset</code>.
 * This method scans all the entries in the factory of type <code>DC_PUSMemoryDumpOffset</code>
 * and returns the first one which is not in use. 
 * In addition to verifyin that the returned component is not in use, this method also performs a check
 * on the value of the component configuration parameters. The folloging configuration parameters 
 * are checked: MaxNumberBlocks, DumpBufferSize.
 * This method has a parameter matching each component configuration parameter. A component instance is
 * returned only if the value of the component configuration parameter is greater than or equal to the method
 * parameter. 
 * Before being returned to the caller, 
 * the status of the component instance is changed to: "in use". A client that receives
 * a component instance through a call to this method, should release the instance when it
 * no longer needs it. This can be done by calling
 * method <code>CC_TelemetryPacketFactory_setInUse(false)</code> on the component itself.
 * <p>
 * If no free component instances are found, then the method returns null. Note that no
 * event report is generated to record the failure to allocate a component instance. Event
 * reporting is the responsibility of the caller. 
 * @param MaxNumberBlocks minimum value for a component configuration parameter 
 * @param DumpBufferSize minimum value for a component configuration parameter      
 * @return the allocated component instance or null if no free instances were found
 */
DC_PUSMemoryDumpOffset* CC_TelemetryPacketFactory_allocatePUSMemoryDumpOffset
(
    CC_TelemetryPacketFactory *This, 
    unsigned int MaxNumberBlocks, 
    unsigned int DumpBufferSize
);

/**
 * Check whether a non-allocated component instance of type <code>DC_PUSMemoryDumpOffset</code>
 * is available within the factory. If this method return true, then the corresponding
 * <code>allocate</code> method is guaranteed to return a non-null value.
 * The method parameters are used as in the corresponding <code>allocate</code> method.
 * @see #allocateDC_PUSMemoryDumpOffset
 * @param MaxNumberBlocks minimum value for a component configuration parameter 
 * @param DumpBufferSize minimum value for a component configuration parameter      
 * @return true if free instances of type DC_PUSMemoryDumpOffset are available, 
 * false otherwise
 */
bool CC_TelemetryPacketFactory_isFreePUSMemoryDumpOffset
(
    CC_TelemetryPacketFactory *This, 
    unsigned int MaxNumberBlocks, 
    unsigned int DumpBufferSize
);

/**
 * Load one instance of type <code>DC_PUSTcVerificationPacket</code> in the
 * factory. The component instances managed by the factory are internally stored in an
 * array. This method loads the i-th element of the array. The argument i should lie
 * in the interval [0, N-1] where N is the number of component instances of type
 * <code>DC_PUSTcVerificationPacket</code>. The value of N is defined by
 * the class constructor.
 * <p>
 * The "in use" status of a newly loaded component is initialized
 * to: "component is not in use".
 * <p>
 * This is an initialization method that should only be called during the application
 * configuration phase.
 * @param i the index in the internal array
 * @param pItem the component instance
 */
static void setPUSTcVerificationPacket
(
    CC_TelemetryPacketFactory *This, 
    unsigned int i,
    DC_PUSTcVerificationPacket *pItem
);

/**
 * Return the number of component instances of type <code>DC_PUSTcVerificationPacket</code>
 * that are currently allocated. A component instance is allocated if its "in use" status is
 * equal to: "component is in use".
 * @return the number of allocated component instances
 */
unsigned int CC_TelemetryPacketFactory_getNumberPUSTcVerificationPacket
(
    CC_TelemetryPacketFactory *This
);

/**
 * Return the number of component instances of type <code>DC_PUSTcVerificationPacket</code>
 * that are in the factory. The value returned is the maximum number of component instances of
 * type <code>DC_PUSTcVerificationPacket</code> that can be allocated.
 * @return the total number of component instances in the factory of
 * type <code>DC_PUSTcVerificationPacket</code>
 */
unsigned int CC_TelemetryPacketFactory_getCapacityPUSTcVerificationPacket
(
    CC_TelemetryPacketFactory *This
);

/**
 * Allocate one instance of type <code>DC_PUSTcVerificationPacket</code>.
 * This method scans all the entries in the factory of type <code>DC_PUSTcVerificationPacket</code>
 * and returns the first one which is not in use. 
 * Before being returned to the caller, 
 * the status of the component instance is changed to: "in use". A client that receives
 * a component instance through a call to this method, should release the instance when it
 * no longer needs it. This can be done by calling
 * method <code>CC_TelemetryPacketFactory_setInUse(false)</code> on the component itself.
 * <p>
 * If no free component instances are found, then the method returns null. Note that no
 * event report is generated to record the failure to allocate a component instance. Event
 * reporting is the responsibility of the caller.      
 * @return the allocated component instance or null if no free instances were found
 */
DC_PUSTcVerificationPacket* CC_TelemetryPacketFactory_allocatePUSTcVerificationPacket
(
    CC_TelemetryPacketFactory *This
);

/**
 * Check whether a non-allocated component instance of type <code>DC_PUSTcVerificationPacket</code>
 * is available within the factory. If this method return true, then the corresponding
 * <code>allocate</code> method is guaranteed to return a non-null value.
 * The method parameters are used as in the corresponding <code>allocate</code> method.
 * @see #allocateDC_PUSTcVerificationPacket     
 * @return true if free instances of type DC_PUSTcVerificationPacket are available, 
 * false otherwise
 */
bool CC_TelemetryPacketFactory_isFreePUSTcVerificationPacket
(
    CC_TelemetryPacketFactory *This
);


#endif
