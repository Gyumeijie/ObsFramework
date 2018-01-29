//
//
// BasicTypes.h
//

/**
 * @file BasicTypes.h
 * This file defines the <code>typedef</code> types that are used in the OBS Framework.
 */

#ifndef BASICTYPES_H
#define BASICTYPES_H

/**
 * Type for instance identifiers. The constructor of the root class
 * <code>CC_RootObject</code> assigns a unique instance identifier to
 * each newly created object. This identifier is fixed and serves to
 * identify the object instance.
 * @see CC_RootObject
 */
typedef unsigned short TD_InstanceId;

/**
 * Type for class identifiers. Each framework class derived from the
 * root class <code>CC_RootObject</code> is characterized by a
 * class identifier.
 * @see CC_RootObject
 */
typedef unsigned short TD_ClassId;

/**
 * Type for on-board time. Only values greater than zero are legal. Negative
 * values (typically -1) are allowed but should be used only to designate a
 * non-valid time.
 * @see ObsClock
 */
typedef int TD_ObsTime;

/**
 * Type for on-board cycle. Only values greater than zero are legal. Negative
 * values (typically -1) are allowed but should be used only to designate a
 * non-valid time.
 * @see ObsClock
 */
typedef int TD_ObsCycle;

/**
 * Type for elemetary trace items. Trace signals are broken up into items
 * that are sent to the external set-up in one single operation.
 * @see Tracer
 */
typedef unsigned short TD_TraceItem;

/**
 * Type for the outcome code of a punctual action. 
 * Some outcome codes are generic and are used by several classes.
 * Others are specific to a particular class and are used to convey
 * information about specific error conditions that arise within that class.
 * From a syntactical point of view, the outcome codes are 
 * enumeration whose values have the following meaning:<ol>
 * <li><code>ACTION_DISABLED</code>: outcome returned by an action that
 * received an "execute" request but was disabled.</li>
 * <li><code>ACTION_SUCCESS</code>: outcome returned by an action that
 * received an "execute" request and executed successfully.</li>
 * <li><code>ACTION_FAILURE</code>: outcome returned by an action that
 * received an "execute" request and executed unsuccessfully.</li>
 * <li><code>ACTION_CANNOT_EXECUTE</code>: outcome returned by an action that
 * received an "execute" request but could not be executed because the execution
 * check returned "action cannot execute".</li>
 * <li><code>ACTION_RESET</code>: default value used for the <i>last outcome</i>
 * of a punctual action after the punctual action has been reset or initialized.</li>
 * <li><code>MEM_LOAD_PRE_CHECKSUM_FAILED</code>: action outcome that is specific to
 * class <code>PUSMemoryLoad</code>.</li>
 * <li><code>PACKET_NOT_FOUND</code>: action outcome that is returned
 * when a telemetry packet is requested from the telemetry packet factory 
 * but the factory does not have the requested packet.</li>
 * <li><code>PUS_MODE_MAN_FULL</code>: action outcome that is returned when 
 * an attempt is made to load a telemetry packet in the PUS telemetry mode manager
 * but this fails because the mode manager is full.</li>
 * <li><code>TM_MAN_QUEUE_FULL</code>: action outcome that is returned
 * when an attempt is made to load a telemetry packet in the immediate dispatch
 * queue of the telemetry manager but the operation cannot be performed because
 * the queue is full.</li>
 * <li><code>APP_DATA_INCONSISTENT</code>: action outcome that is returned when
 * a telecommand finds that its application data are inconsistent.</li>
 * </ol>
 * @see PunctualAction#execute
 * @see PunctualAction#getLastOutcome
 * @see ConditionalPunctualAction#doAction
 * @see DC_FdirCheck#doAction
 */
typedef enum ActionOutcome {
    // OBS Framework specific outcomes
	ACTION_DISABLED=1,
	ACTION_SUCCESS,
	ACTION_FAILURE,
	ACTION_CANNOT_EXECUTE,
	ACTION_RESET,
    MEM_LOAD_PRE_CHECKSUM_FAILED,
    MEM_LOAD_POST_CHECKSUM_FAILED,
    PACKET_NOT_FOUND,
    PUS_MODE_MAN_FULL,
    APP_DATA_INCONSISTENT,
    TM_MAN_QUEUE_FULL,

    LAST_ACTION_OUTCOME=TM_MAN_QUEUE_FULL
} TD_ActionOutcome;

/**
 * Type for the index representing a state of an FSM. The FSM state is represented
 * as an index that must lie in the range
 * [0,N-1] where N is the total
 * number of states in the target FSM.
 * Negative values are allowed but represent non-legal state indices.
 * @see DC_FsmEvent
 * @see CC_FSM
 */
typedef int TD_FsmStateIndex;

/**
 * Type for the index representing the operational mode of a mode manager.
 * The mode is represented as an index that must lie in the range
 * [0,N-1] where N is the total number of modes.
 * Negative values are allowed but represent non-legal mode values.
 * @see ModeManager
 */
typedef int TD_Mode;

/**
 * Type for the index representing the configuration of a reconfiguration
 * manager.
 * The configuration is represented as an index that must lie in the range
 * [0,N-1] where N is the total number of configurations.
 * @see DC_BasicReconfigurer
 */
typedef unsigned short TD_Config;

/**
 * Type for the telecommand identifier.
 * @see Telecommand
 */
typedef unsigned short TD_TelecommandId;

/**
 * Type for the telecommand type.
 * @see Telecommand
 */
typedef unsigned char TD_TelecommandType;

/**
 * Type for the telecommand sub type.
 * @see Telecommand
 */
typedef unsigned char TD_TelecommandSubType;

/**
 * Type for the telecommand source.
 * @see Telecommand
 */
typedef unsigned short TD_TelecommandSource;

/**
 * Type for the telecommand acknowledge level attribute.
 * @see Telecommand
 */
typedef unsigned char TD_TelecommandAck;

/**
 * Type for the check code that some components can return to
 * give information about the reasons for the failure of one of
 * their checks.
 * @see Telecommand
 */
typedef unsigned int TD_CheckCode;

/**
 * Type for the identifier of a database parameter. Only non negative values
 * represent valid identifiers.
 * @see ParameterDatabase
 */
typedef short TD_DatabaseId;

/**
 * Type for a data pool identifier. Only non negative values
 * represent valid identifiers.
 * @see DataPool
 */
typedef int TD_DataPoolId;

/**
 * Generic float type that, depending on application needs, can be
 * re-defined to be either a float or a double.
 */
typedef float TD_Float;

/**
 * Generic integer type that, depending on application needs, can be
 * re-defined to be a long int, an int, or a short.
 */
typedef short TD_Integer;

/**
 * Type for the identifier of a data item variable type.
 * @see DC_DataItem
 */
typedef enum DataItemType {
	DI_CHAR,
	DI_UNSIGNED_CHAR,
	DI_SHORT,
	DI_UNSIGNED_SHORT,
	DI_INT,
	DI_UNSIGNED_INT,
	DI_FLOAT,
	DI_DOUBLE
} TD_DataItemType;

// -------------------------------------------------------------------
/**
 * Type for the PUS packet identifier.
 * @see PUSTelecommand#getPacketId
 * @see PUSTelemetryPacket#getPacketId
 */
typedef unsigned short TD_PUSPacketId;

/**
 * Type for the PUS structure identifier (SID).
 * @see DC_PUSDataReportingPacket
 */
typedef unsigned int TD_SID;

/**
 * Type for the PUS application identifier.
 * @see PUSTelecommand#setAPID
 * @see PUSTelemetryPacket#setAPID
 */
typedef TD_PUSPacketId TD_APID;

/**
 * Type for the collection interval of a PUS data reporting packet.
 * @see DC_PUSDataReportingPacket
 */
typedef unsigned short TD_PUSCollectionInterval;

/**
 * Type for the number of parameters of a PUS data reporting packet.
 * @see DC_PUSDataReportingPacket
 */
typedef unsigned char TD_PUSNumberOfParameters;

/**
 * Type for an integer expressing the length of a memory block in the PUS memory
 * management service. 
 * @see DC_PUSMemoryLoad
 * @see DC_PUSMemoryDump
 */
typedef unsigned short TD_PUSMemLength;

/**
 * Type for a single memory load data as used by the memory load service. 
 * This type also defines the single addressable unit (or SAU) for the memory
 * management service.
 * @see DC_PUSMemoryLoad
 * @see DC_PUSMemoryDump
 */
typedef unsigned char TD_PUSMemData;

/**
 * Type for the memory ID field of the memory load and memory dump telecommand
 * packets.
 * @see DC_PUSMemoryLoadOffset
 * @see DC_PUSMemoryLoadAbsolute
 * @see DC_PUSMemoryDumpOffset
 * @see DC_PUSMemoryDumpAsbolute
 */
typedef unsigned int TD_PUSMemId;

/**
 * Type for the number of blocks in a memory load and memory dump telecommand
 * packet.
 * @see DC_PUSMemoryLoadOffset
 * @see DC_PUSMemoryLoadAbsolute
 * @see DC_PUSMemoryDumpOffset
 * @see DC_PUSMemoryDumpAsbolute
 */
typedef unsigned char TD_PUSNumberMemBlocks;

/**
 * Type for the offset field in a memory load and memory dump telecommand
 * packet.
 * @see DC_PUSMemoryLoadOffset
 * @see DC_PUSMemoryLoadAbsolute
 * @see DC_PUSMemoryDumpOffset
 * @see DC_PUSMemoryDumpAsbolute
 */
typedef unsigned short TD_PUSMemOffset;

/**
 *  Type used in Telecommand/PUSMemoryLoad and Telemetry/PUSMemoryDump
 */
typedef struct MemBlockType {
    /**
     * Start address of a memory dump block
     */
    TD_PUSMemData *startAddress;         
    /**
     * The number of SAUs to be loaded
     */
    TD_PUSMemLength length;              
    /**
     * The checksum of the block
     */
    unsigned short checksum;             

} MemBlockType;


// -------------------------------------------------------------------
/**
 * Type for the telemetry packet type.
 * @see TelemetryPacket
 */
typedef unsigned char TD_TelemetryType;

/**
 * Type for the telemetry packet sub type.
 * @see TelemetryPacket
 */
typedef unsigned char TD_TelemetrySubType;

/**
 * Type for the telemetry packet destination.
 * @see TelemetryPacket
 */
typedef unsigned short TD_TelemetryDestination;

/**
 * Type for event type identifiers. Only values greater than 0 denote
 * real events. Events can be filtered when they are stored in an
 * event repository. Filtering is done by matching the event type identifiers
 * with an event mask (see method <code>create</code> in class
 * <code>DC_EventRepository</code>). For this reason, most users will
 * want to map the enumeration values to integers in order to tune
 * the masking mechanism.
 * <p>
 * The following event type identifiers are defined:<ol>
 * <li><code>EVT_NULL</code>: this value is reserved for event objects that have not yet been
 * initialized by the application.</li>
 * <li><code>EVT_PUNCTUAL_ACTION_EXEC</code>: type identifier for events created when a
 * punctual action is executed.
 * </li>
 * <li><code>EVT_PUNCTUAL_ACTION_DIS</code>: type identifier for events created when a punctual
 * action is not executed because it is disabled.
 * </li>
 * <li><code>EVT_FSM_TRANSITION</code>: type identifier for events created when an FSM performs a
 * state transition.
 * </li>
 * <li><code>EVT_FSM_TRANSITION_DISABLED</code>: type identifier for events created when an FSM
 * fails to performs a state transition because the transition into the target state is disabled.
 * </li>
 * <li><code>EVT_FSM_ENTRY_FAILED</code>: type identifier for events created when an FSM fails
 * to performs a state transition because the entry check in the target state failed.
 * </li>
 * <li><code>EVT_FSM_EXIT_FAILED</code>: type identifier for events created when an FSM fails
 * to performs a state transition because the exit check from the current state failed.
 * </li>
 * <li><code>EVT_FSM_ALL_TRANSITION_DISABLED</code>: type identifier for events created when an
 * FSM fails to performs a state transition because the state transitions is disabled.
 * </li>
 * <li><code>EVT_TC_NOT_VALID</code>: type identifier for events created when a telecommand is
 * loaded in the telecommand manager but must immediately be aborted because a validity check
 * failure.
 * </li>
 * <li><code>EVT_TC_LOADED</code>: type identifier for events created when a telecommand is
 * loaded in the telecommand manager and its validity check is successful.
 * </li>
 * <li><code>EVT_TC_EXEC_SUCC</code>: type identifier for events created when a telecommand is
 * successfully executed.
 * </li>
 * <li><code>EVT_TC_ABORTED</code>: type identifier for events created when a telecommand is
 * unloaded further to an abort request.
 * </li>
 * <li><code>EVT_TC_LIST_FULL</code>: type identifier for events created when a telecommand
 * load is attempted but cannot be executed because the list of pending telecommands in the
 * telecommand manager is full.
 * </li>
 * <li><code>EVT_TC_EXEC_CHECK_FAIL</code>: type identifier for events created when execution
 * of a telecommand is attempted by the telecommand manager but cannot be performed because
 * the telecommand execution check fails.
 * </li>
 * <li><code>EVT_TC_EXEC_FAIL</code>: type identifier for events created when a telecommand
 * is executed and returns with a action outcome other than ACTION_SUCCESS.
 * </li>
 * <li><code>EVT_MON_PROFILE_VIOLATION</code>: type identifier for events created when a
 * monitoring profile has detected a profile violation.
 * </li>
 * <li><code>EVT_MOD_TRANS_INHIBITED</code>: type identifier for events created when a mode
 * manager attempts a mode transition but cannot perform it because the transition
 * is inhibited.
 * </li>
 * <li><code>EVT_MOD_TRANS_PERFORMED</code>: type identifier for events created when a mode
 * manager performs a mode transition.
 * </li>
 * <li><code>EVT_TOO_MANY_TM_BYTES</code>: type identifier for events created when a telemetry
 * manager finds that the number of telemetry bytes to be written to the telemetry
 * stream exceeds the stream's capacity.
 * </li>
 * <li><code>EVT_TM_QUEUE_FULL</code>: type identifier for events created when an attempt is 
 * made to load a telemetry packet for immediate dispatch in the telemetry manager and the 
 * internal queue for the packets is already full.
 * </li>
 * <li><code>EVT_PUS_DATA_REP_PACKET_TOO_LARGE</code>: type identifier for events created when a
 * PUS data reporting packet (see class <code>DC_PUSDataReportingPacket</code>) does not
 * have sufficient space to store the parameter samples.
 * </li>
 * <li><code>EVT_PUS_TOO_MANY_DUMP_BLOCKS</code>: type identifier for events created when a
 * request is made to dump more memory blocks than can be accommodated by the implementation
 * of the memory dump service PUS (see class <code>DC_PUSMemoryDump</code>)
 * </li>
 * <li><code>EVT_PUS_ILLEGAL_BLOCK_INDEX</code>: type identifier for events created when an
 * attempt is made to define an illegal memory dump block (see class <code>DC_PUSMemoryDump</code>)
 * </li>
 * <li><code>EVT_PUS_TOO_MANY_MEM_DATA</code>: type identifier for events created when an
 * attempt is made to dump or load too many memory locations.
 * </li>
 * <li><code>EVT_TM_ITEM_NOT_VALID</code>: type identifier for events created when a telemetry
 * item is found to be "not valid".
 * </li>
 * <li><code>EVT_TM_WRONG_BYTE_INDEX</code>: type identifier for events created when a request
 * is made to retrieve a a non-existent telemetry byte from a telemetry packet.
 * </li>
 * <li><code>EVT_MAN_STARTED</code>: type identifier for events created when a manoeuvre starts
 * execution.
 * </li>
 * <li><code>EVT_MAN_ABORTED</code>: type identifier for events created when a manoeuvre is
 * aborted.
 * </li>
 * <li><code>EVT_MAN_TERMINATED</code>: type identifier for events created when a manoeuvre is
 * terminated.
 * </li>
 * <li><code>EVT_MAN_LOADED</code>: type identifier for events created when a manoeuvre is
 * loaded in the manoeuvre manager.
 * </li>
 * <li><code>EVT_MAN_UNLOADED</code>: type identifier for events created when a manoeuvre
 * is unloaded from the manoeuvre manager.
 * </li>
 * <li><code>EVT_MAN_PROGRESS</code>: type identifier for events created when the execution of a
 * PUS telecommand manoeuvre has advanced.
 * </li>
 * <li><code>EVT_MAN_RESUMED</code>: type identifier for events created when a manoeuvre is
 * resumed (ie when its isSuspended flag changes from "manoeuvre is suspended" to "manoeuvre is
 * not suspended").
 * </li>
 * <li><code>EVT_MAN_SUSPENDED</code>: type identifier for events created when a manoeuvre is
 * resumed (ie when its isSuspended flag changes from "manoeuvre is not suspended" to "manoeuvre is
 * suspended").
 * </li>
 * <li><code>EVT_MAN_LIST_FULL</code>: type identifier for events created when an attempt is made
 * to load a manoeuvre in the manoeuvre manager but its list of pending manoeuvres is already full.
 * </li>
 * <li><code>EVT_ILLEGAL_CB</code>: type identifier for events created when an attempt is made
 * to access a non-existent element of a control block.
 * </li>
 * <li><code>EVT_ILLEGAL_FS</code>: type identifier for events created when an attempt is made
 * to access a non-existent FsmState.
 * </li>
 * <li><code>EVT_ILLEGAL_MM</code>: type identifier for events created when an attempt is made
 * to access a non-existent mode in a mode manager.
 * </li>
 * <li><code>EVT_RECONFIG</code>: type identifier for events created when a reconfiguration
 * is performed.
 * </li>
 * <li><code>EVT_RECONFIG_NO_HEALTHY</code>: type identifier for events created when a
 * reconfiguration is attempted but cannot be performed because there are no spare healthy
 * configurations.
 * </li>
 * <li><code>EVT_RECONFIG_DISABLED</code>: type identifier for events created when a
 * reconfiguration is attempted but cannot be performed because reconfigurations are disabled.
 * </li>
 * <li><code>EVT_ILLEGAL_CONFIG</code>: type identifier for events created when an operation is
 * performed on a reconfiguration manager with an illegal configuration index (either negative
 * or equal or greater than N where N is the total number of configurations).
 * </li>
 * <li><code>EVT_CRIT_TC_TIMEOUT</code>: type identifier for events created when the "fire"
 * command for a critical telecommand is rejected because it is too far in time from its "arm" command.
 * <li><code>EVT_CRIT_TC_IMG_INV</code>: type identifier for events created when the "fire"
 * command for a critical telecommand is rejected because the image check has failed.
 * </li>
 * <li><code>EVT_CRIT_TC_ARMED</code>: type identifier for events created when a critical
 * telecommand is armed.
 * </li>
 * <li><code>EVT_STACK_FULL</code>: type identifier for events created when a push operation
 * is performed on a stack container that is already full.
 * </li>
 * <li><code>EVT_STACK_EMPTY</code>: type identifier for events created when a pop operation
 * is performed on a stack container that is empty.
 * </li>
 * <li><code>EVT_PUS_REP_POOL_FULL</code>: type identifier for events created when an attempt
 * is made to allocate a PUS data reporting packet from a data reporting packet pool
 * (see class <code>DC_PUSDataReportingPacketFactory</code>) that
 * is already full.
 * </li>
 * <li><code>EVT_ILLEGAL_MP</code>: type identifier for events created when an attempt is made
 * to load a monitoring profile in a monitoring profile list (instance of class
 * <code>DC_ProfileList</code>) at an illegal list address.
 * </li>
 * <li><code>EVT_ILLEGAL_CL</code>: type identifier for events created when an attempt is made
 * to load a control block in a control block list (instance of class
 * <code>DC_ControlList</code>) at an illegal list address.
 * </li>
 * <li><code>EVT_ILLEGAL_PUS_REP_PACKET</code>: type identifier for events created when an attempt is made
 * to access a parameter in a PUS data reporting packet with an illegal index.
 * </li>
 * <li><code>EVT_ILLEGAL_DB_ACCESS</code>: type identifier for events created when an attempt is made
 * to access a parameter in a parameter database with an illegal identifier orwith the wrong type
 * (e.g. when a parameter of
 * type <code>float</code> is accessed with a method that is intended for parameters of type
 * <code>double</code>).
 * </li>
 * <li><code>EVT_ILLEGAL_DP_ACCESS</code>: type identifier for events created when an attempt is made
 * to access a data pool item with an illegal identifier or with the wrong type (e.g. when a parameter of
 * type <code>float</code> is accessed with a method that is intended for parameters of type
 * <code>double</code>).
 * </li>
 * <li><code>EVT_TM_PCK_ALLOC_FAILURE</code>: type identifier for events created when a request
 * is made to allocate a telemetry packet from the telemetry packet factory (class
 * <code>CC_TelemetryPacketFactory</code>) and the request fails.
 * </li>
 * <li><code>EVT_MAN_ALLOC_FAILURE</code>: type identifier for events created when a request
 * is made to allocate a manoeuvre from the manoeuvre factory (class
 * <code>CC_ManoeuvreFactory</code>) and the request fails.
 * </li>
 * <li><code>EVT_TC_ALLOC_FAILURE</code>: type identifier for events created when a request
 * is made to allocate a telecommand from the telecommand factory (class
 * <code>CC_TelecommandFactory</code>) and the request fails.
 * </li>
 * <li><code>EVT_NO_TC_AVAIL</code>: type identifier for events created when a request
 * for a telecommand is made to a telecommand factory but the factory was unable to
 * return a free telecommand component (see
 * class <code>DC_BasicPUSTcLoader</code>).
 * </li>
 * <li><code>EVT_UNKNOWN_TC_TYPE</code>: type identifier for events created when a 
 * telecommand loader finds a telecommand with a type that it does know how to handle
 * (see
 * class <code>DC_BasicPUSTcLoader</code>).
 * </li>
 * <li><code>EVT_TC_TOO_LONG</code>: type identifier for events created when a 
 * telecommand loader finds a telecommand packet that is too long (see
 * class <code>DC_BasicPUSTcLoader</code>).
 * </li>
 * <li><code>EVT_TOO_MANY_TC_PCKT</code>: type identifier for events created when a telecommand
 * loader is asked to process too many telecommand packets (see
 * class <code>DC_BasicPUSTcLoader</code>).
 * </li>
 * <li><code>EVT_SID_NOT_FOUND</code>: type identifier for events created when a request
 * is made to unload a data reporting packet with a certain SID and that packet is not found (see
 * class <code>DC_PUSTelemetryModeManager</code>).
 * </li>
 * <li><code>EVT_TM_STREAM_END</code>: type identifier for events created when a telemetry
 * stream cannot complete a write request because the "end" of the stream has been reached (see
 * class <code>DC_BasicPUSTmStream</code>).
 * </li>
 * </ol>
 * @see DC_Event
 * @see DC_EventRepository
 */
typedef enum EventType {
    // OBS Framework specific event types
	EVT_NULL = 0,

    EVT_PUNCTUAL_ACTION_EXEC,
	EVT_PUNCTUAL_ACTION_DIS,

    EVT_FSM_TRANSITION,
	EVT_FSM_TRANSITION_DISABLED,
	EVT_FSM_ENTRY_FAILED,
	EVT_FSM_EXIT_FAILED,
	EVT_FSM_ALL_TRANSITION_DISABLED,

    EVT_TC_NOT_VALID,
	EVT_TC_LOADED,
	EVT_TC_EXEC_SUCC,
	EVT_TC_ABORTED,
	EVT_TC_LIST_FULL,
	EVT_TC_EXEC_CHECK_FAIL,
	EVT_TC_EXEC_FAIL,

	EVT_MON_PROFILE_VIOLATION,
	EVT_MOD_TRANS_INHIBITED,
	EVT_MOD_TRANS_PERFORMED,

	EVT_TOO_MANY_TM_BYTES,
    EVT_TM_QUEUE_FULL,
	EVT_TM_ITEM_NOT_VALID,
    EVT_TMW_WRONG_BYTE_INDEX,
    EVT_PUS_DATA_REP_PACKET_TOO_LARGE,
    EVT_PUS_TOO_MANY_DUMP_BLOCKS,
    EVT_PUS_ILLEGAL_BLOCK_INDEX,
    EVT_PUS_TOO_MANY_MEM_DATA,

	EVT_MAN_STARTED,
	EVT_MAN_ABORTED,
	EVT_MAN_TERMINATED,
    EVT_MAN_PROGRESS,
	EVT_MAN_LOADED,
	EVT_MAN_UNLOADED,
	EVT_MAN_RESUMED,
	EVT_MAN_SUSPENDED,
	EVT_MAN_LIST_FULL,

	EVT_ILLEGAL_CB,
    EVT_ILLEGAL_FS,
    EVT_ILLEGAL_MM,

	EVT_RECONFIG,
	EVT_RECONFIG_NO_HEALTHY,
	EVT_RECONFIG_DISABLED,
	EVT_ILLEGAL_CONFIG,

	EVT_CRIT_TC_TIMEOUT,
	EVT_CRIT_TC_IMG_INV,
	EVT_CRIT_TC_ARMED,

    EVT_STACK_FULL,
    EVT_STACK_EMPTY,
    EVT_PUS_REP_POOL_FULL,

    EVT_ILLEGAL_MP,
    EVT_ILLEGAL_CL,
    EVT_ILLEGAL_PUS_REP_PACKET,
    EVT_ILLEGAL_DB_ACCESS,
    EVT_ILLEGAL_DP_ACCESS,

    EVT_TM_PCK_ALLOC_FAILURE,
    EVT_MAN_ALLOC_FAILURE,
    EVT_TC_ALLOC_FAILURE,
    EVT_NO_TC_AVAIL,
    EVT_UNKNOWN_TC_TYPE,
    EVT_TC_TOO_LONG,
    EVT_TOO_MANY_TC_PCKT,
    EVT_TM_STREAM_END,

    EVT_SID_NOT_FOUND,

    LAST_EVENT_TYPE=EVT_SID_NOT_FOUND
} TD_EventType;

#endif
