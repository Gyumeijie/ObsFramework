//
//
// Constants.h
//

/**
 * @file Constants.h
 * This file defines all the constants used in the operational classes
 * of the OBS Framework. Constants
 * are defined using the <code>const</code> construct provided by the
 * C++ language. They are <i>not</i> defined using the <code>#define</code>
 * construct of the C language. Constants used in the test classes
 * are defined in a dedicated header file (<code>TestConstants</code>).
 * <p>
 * Among others, this file also defines the constats representing the
 * PUS types and subtypes.
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "BasicTypes.h"
#include <stdbool.h>


#define pNULL 0     // Constant used to represent uninitialized pointers.

/**
 * Constant used to signify "object or system correctly configured".
 * This is normally used as the return value of a system or object
 * configuration check.
 */
#define CONFIGURED  true

/**
 * Constant used to signify "object or system not configured".
 * This is normally used as the return value of a system or object
 * configuration check.
 */
#define NOT_CONFIGURED  false

/**
 * Constant used to signify "disabled".
 */
#define DISABLED  false

/**
 * Constant used to signify "enabled".
 */
#define ENABLED  true

/**
 * Constant used to signify "not valid".
 */
#define NOT_VALID  false

/**
 * Constant used to signify "valid".
 */
#define VALID  true

/**
 * Constant used to signify "not critical".
 */
#define NOT_CRITICAL  false

/**
 * Constant used to signify "critical".
 */
#define CRITICAL  true

/**
 * Constant used to signify "telecommand not armed".
 */
#define NOT_ARMED  false

/**
 * Constant used to signify "telecommand armed".
 */
#define ARMED  true

/**
 * Constant used to signify "not healthy".
 */
#define NOT_HEALTHY  false

/**
 * Constant used to signify "healthy".
 */
#define HEALTHY  true

/**
 * Constant used to signify "component is in use".
 * @see CC_TelemetryPacketFactory
 * @see CC_ManoeuvreFactory
 * @see CC_TelecommandFactory
 */
#define IN_USE  true

/**
 * Constant used to signify "component is not in use".
 * @see CC_TelemetryPacketFactory
 * @see CC_ManoeuvreFactory
 * @see CC_TelecommandFactory
 */
#define NOT_IN_USE  false

/**
 * Constant used to signify "telecommand can execute".
 * @see Telecommand#canExecute
 */
#define TC_CAN_EXECUTE  true

/**
 * Constant used to signify "telecommand cannot execute".
 * @see Telecommand#canExecute
 */
#define TC_CANNOT_EXECUTE  false

// -------------------------------------------------------
/**
 * Constant used to signify "manoeuvre can start".
 * @see Manoeuvre#canStart
 */
#define MAN_CAN_START  true

/**
 * Constant used to signify "manoeuvre cannot start".
 * @see Manoeuvre#canStart
 */
#define MAN_CANNOT_START  false

/**
 * Constant used to signify "manoeuvre can continue".
 * @see Manoeuvre#canExecute
 */
#define MAN_CAN_CONTINUE  true

/**
 * Constant used to signify "manoeuvre cannot continue".
 * @see Manoeuvre#canExecute
 */
#define MAN_CANNOT_CONTINUE  false

/**
 * Constant used to signify "manoeuvre has terminated execution".
 * @see Manoeuvre#isFinished
 */
#define MAN_HAS_TERMINATED  true

/**
 * Constant used to signify "manoeuvre has not yet terminated execution".
 * @see Manoeuvre#isFinished
 */
#define MAN_HAS_NOT_TERMINATED  false

/**
 * Constant used to signify "manoeuvre is in use".
 * @see Manoeuvre
 */
#define MAN_IN_USE  true

/**
 * Constant used to signify "manoeuvre is not in use".
 * @see Manoeuvre
 */
#define MAN_NOT_IN_USE  false

/**
 * Constant used to signify "manoeuvre is executing".
 * @see Manoeuvre
 */
#define MAN_EXECUTING  true

/**
 * Constant used to signify "manoeuvre is not executing".
 * @see Manoeuvre
 */
#define MAN_NOT_EXECUTING  false

/**
 * Constant used to signify "manoeuvre is suspended".
 * @see Manoeuvre
 */
#define MAN_SUSPENDED  true

/**
 * Constant used to signify "manoeuvre is not suspended".
 * @see Manoeuvre
 */
#define MAN_NOT_SUSPENDED  false

// -------------------------------------------------------
/**
 * Constant used to signify "a monitoring profile has been detected".
 * @see MonitoringProfile#deviatesFromProfile
 */
#define MON_PROFILE_DEVIATION  true

/**
 * Constant used to signify "no monitoring profile has been detected".
 * @see MonitoringProfile#deviatesFromProfile
 */
#define NO_MON_PROFILE_DEVIATION  false

/**
 * The initialization value for variable <code>previousValue</code> in
 * a stuck data monitoring profile.
 * @see DC_StuckDataProfile#reset
 */
#define PREVIOUS_VALUE_INIT  9999

// -------------------------------------------------------
/**
 * Constant defining the maximum number of <code>CC_RootObject</code> instances
 * that can be created in an application. This constant is used to initialize
 * the size of the <i>system list</i> data structure in class <code>CC_RootObject</code>.
 * @see CC_RootObject
 */
#define MAX_N_OBJECTS  512

/**
 * The largest integer that can be represented in two's complement notation
 * using 32 bits.
 */
#define MAX_INT  0x7FFFFFFF

/**
 * The largest unsigned integer that can be represented using 32 bits.
 */
#define MAX_UNSIGNED_INT  0xFFFFFFFF

/**
 * Flag to deternmine whether the mode field should be included in telemetry data reporting
 * packets (PUS service type 3, subtypes 25 and 26). If the flag is true, then the mode
 * field is included, otherwise it is omitted.
 * @see DC_PUSDataReportingPacket
 */
#define PUS_DATA_REP_MODE  true

// -------------------------------------------------------
/**
 * Validity check code returned by a PUS telecommand when
 * the telecommand is found to be invalid because there are more raw data than can
 * fit in the telecommand component.
 * @see Telecommand#getValidityCheckCode
 */
#define VC_TOO_MANY_RAW_DATA  1

/**
 * Validity check code returned by a PUS telecommand when
 * the raw data loaded into a telecommand component are internally inconsistent.
 * @see Telecommand#getValidityCheckCode
 */
#define VC_INCONSISTENT_RAW_DATA  2

/**
 * Validity check code returned by a PUS memory block telecommand when
 * the raw data contain too many memory blocks.
 * @see DC_PUSMemoryLoadOffset
 * @see DC_PUSMemoryLoadAbsolute
 */
#define VC_TOO_MANY_MEM_BLOCK  3

/**
 * Validity check code returned by a PUS memory block telecommand when
 * the raw data contain too many memory data.
 * @see DC_PUSMemoryLoadOffset
 * @see DC_PUSMemoryLoadAbsolute
 */
#define VC_TOO_MANY_MEM_DATA  4

/**
 * Validity check code returned by a PUS telecommand when
 * the telecommand is found to be invalid because there are more SIDs than can
 * fit in the telecommand component.
 * @see DC_PUSClearDataReporting
 */
#define VC_TOO_MANY_SIDS  5

// -------------------------------------------------------
/**
 * The PUS service type for the telecommand verification service.
 * @see DC_PUSTcVerificationPacket
 */
#define PUS_TYPE_TC_VER  1

/**
 * The PUS service subtype for the "telecommand acceptance report - success" in
 * the telecommand verification service.
 * @see DC_PUSTcVerificationPacket
 */
#define PUS_ST_TC_VER_ACC_SC  1

/**
 * The PUS service subtype for the "telecommand acceptance report - failure" in
 * the telecommand verification service.
 * @see DC_PUSTcVerificationPacket
 */
#define PUS_ST_TC_VER_ACC_FL  2

/**
 * The PUS service subtype for the "telecommand execution started report - success" in
 * the telecommand verification service.
 * @see DC_PUSTcVerificationPacket
 */
#define PUS_ST_TC_EXE_STR_SC  3

/**
 * The PUS service subtype for the "telecommand execution started report - failure" in
 * the telecommand verification service.
 * @see DC_PUSTcVerificationPacket
 */
#define PUS_ST_TC_EXE_STR_FL  4

/**
 * The PUS service subtype for the "telecommand execution progress report - success" in
 * the telecommand verification service.
 * @see DC_PUSTcVerificationPacket
 */
#define PUS_ST_TC_EXE_PRO_SC  5

/**
 * The PUS service subtype for the "telecommand execution progress report - failure" in
 * the telecommand verification service.
 * @see DC_PUSTcVerificationPacket
 */
#define PUS_ST_TC_EXE_PRO_FL  6

/**
 * The PUS service subtype for the "telecommand execution completion report - success" in
 * the telecommand verification service.
 * @see DC_PUSTcVerificationPacket
 */
#define PUS_ST_TC_EXE_END_SC  7

/**
 * The PUS service subtype for the "telecommand execution completion report - failure" in
 * the telecommand verification service.
 * @see DC_PUSTcVerificationPacket
 */
#define PUS_ST_TC_EXE_END_FL  8

// -------------------------------------------------------
/**
 * The PUS service type for the housekeeping and diagnostic
 * data reporting service.
 * @see DC_PUSDataReportingPacket
 */
#define PUS_TYPE_DATA_REP  3

/**
 * The PUS service subtype for: "define new housekeeping parameter report" in
 * the housekeeping and diagnostic data reporting service.
 */
#define PUS_ST_DATA_REP_NEW_HK  1

/**
 * The PUS service subtype for: "define new diagnostic parameter report" in
 * the housekeeping and diagnostic data reporting service.
 */
#define PUS_ST_DATA_REP_NEW_DG  2

/**
 * The PUS service subtype for: "clear housekeeping parameter report definition" in
 * the housekeeping and diagnostic data reporting service.
 */
#define PUS_ST_DATA_REP_CLR_HK  3

/**
 * The PUS service subtype for: "clear diagnostic parameter report definition" in
 * the housekeeping and diagnostic data reporting service.
 */
#define PUS_ST_DATA_REP_CLR_DG  4

/**
 * The PUS service subtype for: "enable housekeeping parameter report generation" in
 * the housekeeping and diagnostic data reporting service.
 */
#define PUS_ST_DATA_REP_ENB_HK  5

/**
 * The PUS service subtype for: "disable housekeeping parameter report generation" in
 * the housekeeping and diagnostic data reporting service.
 */
#define PUS_ST_DATA_REP_DIS_HK  6

/**
 * The PUS service subtype for: "enable diagnostic parameter report generation" in
 * the housekeeping and diagnostic data reporting service.
 */
#define PUS_ST_DATA_REP_ENB_DG  7

/**
 * The PUS service subtype for: "disable diagnostic parameter report generation" in
 * the housekeeping and diagnostic data reporting service.
 */
#define PUS_ST_DATA_REP_DIS_DG  8

/**
 * The PUS service subtype for: "report housekeeping parameter report definition" in
 * the housekeeping and diagnostic data reporting service.
 */
#define PUS_ST_DATA_REP_REP_HK  9

/**
 * The PUS service subtype for: "housekeeping parameter report definition report" in
 * the housekeeping and diagnostic data reporting service.
 */
#define PUS_ST_DATA_REP_REP_HK_REP  10

/**
 * The PUS service subtype for: "report diagnostic parameter report definition" in
 * the housekeeping and diagnostic data reporting service.
 */
#define PUS_ST_DATA_REP_REP_DG  11

/**
 * The PUS service subtype for: "diagnostic parameter report definition report" in
 * the housekeeping and diagnostic data reporting service.
 */
#define PUS_ST_DATA_REP_REP_DG_REP  12

/**
 * The PUS service subtype for: "select periodic housekeeping parameter report generation mode" in
 * the housekeeping and diagnostic data reporting service.
 */
#define PUS_ST_DATA_REP_PER_HK  17

/**
 * The PUS service subtype for: "select periodic diagnostic parameter report generation mode" in
 * the housekeeping and diagnostic data reporting service.
 */
#define PUS_ST_DATA_REP_PER_DG  18

/**
 * The PUS service subtype for: "select filtered housekeeping parameter report generation mode" in
 * the housekeeping and diagnostic data reporting service.
 */
#define PUS_ST_DATA_REP_FIL_HK  19

/**
 * The PUS service subtype for: "select filtered diagnostic parameter report generation mode" in
 * the housekeeping and diagnostic data reporting service.
 */
#define PUS_ST_DATA_REP_FIL_DG  20

/**
 * The PUS service subtype for: "report unfiltered housekeeping parameters" in
 * the housekeeping and diagnostic data reporting service.
 */
#define PUS_ST_DATA_REP_UNF_HK  21

/**
 * The PUS service subtype for: "report unfiltered diagnostic parameters" in
 * the housekeeping and diagnostic data reporting service.
 */
#define PUS_ST_DATA_REP_UNF_DG  22

/**
 * The PUS service subtype for: "unfiltered housekeeping parameters report" in
 * the housekeeping and diagnostic data reporting service.
 */
#define PUS_ST_DATA_REP_UNF_HK_REP  23

/**
 * The PUS service subtype for: "unfiltered diagnostic parameters report" in
 * the housekeeping and diagnostic data reporting service.
 */
#define PUS_ST_DATA_REP_UNF_DG_REP  24

/**
 * The PUS service subtype for: "housekeeping parameters report" in
 * the housekeeping and diagnostic data reporting service.
 */
#define PUS_ST_DATA_REP_PAR_HK_REP  25

/**
 * The PUS service subtype for: "diagnostic parameters report" in
 * the housekeeping and diagnostic data reporting service.
 */
#define PUS_ST_DATA_REP_PAR_DG_REP  26

// -------------------------------------------------------
/**
 * The PUS service type for the telecommand function management service.
 * @see DC_PUSFunction
 */
#define PUS_TYPE_TC_FNC  8

/**
 * The PUS service subtype for the "perform function" service in the telecommand 
 * function management service.
 * @see DC_PUSFunction
 */
#define PUS_ST_TC_FNC_PER  1

// -------------------------------------------------------
/**
 * The PUS service type for the telecommand memory management service.
 * @see DC_PUSFunction
 */
#define PUS_TYPE_MEM  6

/**
 * The PUS service subtype for the "memory load with base plus offset" service in the telecommand 
 * memory management service.
 * @see DC_PUSFunction
 */
#define PUS_ST_TC_MEM_OFF  1

/**
 * The PUS service subtype for the "memory load with absolute addresses" service in the telecommand 
 * memory management service.
 * @see DC_PUSFunction
 */
#define PUS_ST_TC_MEM_ABS  2

/**
 * The PUS service subtype for the "memory dump with base plus offset" service in the telecommand 
 * memory management service.
 * @see DC_PUSFunction
 */
#define PUS_ST_TC_DMP_OFF  3

/**
 * The PUS service subtype for the "memory dump with base plus offset" service in the telemetry 
 * memory management service.
 * @see DC_PUSFunction
 */
#define PUS_ST_TM_DMP_OFF  4

/**
 * The PUS service subtype for the "memory dump with absolute addresses" service in the telecommand 
 * memory management service.
 * @see DC_PUSFunction
 */
#define PUS_ST_TC_DMP_ABS  5

/**
 * The PUS service subtype for the "memory dump with absolute addresses" service in the telemetry 
 * memory management service.
 * @see DC_PUSFunction
 */
#define PUS_ST_TM_DMP_ABS  6

// -------------------------------------------------------
/**
 * The PUS service type for the test PUS telecommands.
 * @see DC_TestPUSTelecommand
 */
#define PUS_TYPE_TEST  127

/**
 * The PUS service subtype for the test PUS telecommands.
 * @see DC_TestPUSTelecommand
 */
#define PUS_ST_TC_TEST  1


#endif
