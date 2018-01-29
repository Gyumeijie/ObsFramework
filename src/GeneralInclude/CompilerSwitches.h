//
//
// CompilerSwitches.h
//
//
// Change Record:

/**
 * @file CompilerSwitches.h 
 * This file defines the compiler switches used by the operational
 * classes of the OBS Framework. This file is <code>#included</code>
 * by all body files of the OBS Framework.
 * Note that compiler switches used by the test
 * classes are defined in a dedicated header file (<code>TestCompilerSwitches</code>)
 */

#ifndef COMPILERSWITCHES_H
#define COMPILERSWITCHES_H

/**
 * The NDEBUG symbol controls whether assertions are switched on or off
 * under the Borland C++Builder. If the variable is defined, then assertions
 * are switched off. If it is not defined, then assertions are switched on.
 */
//#undef NDEBUG      // assertions are switched on
#define NDEBUG   // assertions are switched off

/**
 * The USE_SYSTEM_ASSERT symbol controls whether the assert() macro defined in
 * the system-wide header file <code>assert.h</code> or the one defined in 
 * <code>DebugSupport.h</code> is used. If the symbol is defined, the definition 
 * in <code>assert.h</code> is taken. Otherwise the definition in 
 * <code>DebugSupport.h</code> is used.
 */
#define USE_SYSTEM_ASSERT 
//#undef USE_SYSTEM_ASSERT

// Must be defined only if Simulink(TM) is available
// #define HAVE_SIMULINK
#undef HAVE_SIMULINK

/**
 * This pragma disables warnings that are in effect when the W4 warning
 * level on the VS compiler are enabled (this is not the default)
 * The following warnings are disabled:
 * 4061: enumeration constant in switch is not explicitly handled by a case label
 * 4100: unreferenced formal parameter (this triggers whenever trivial
 *       definitions are given for methods that are to be overridden in
 *       subclasses)
 * 4511: copy constructor could not be generated (copy constructors 
 *       must not be generated in the OBS Framework)
 * 4512: assignment operator could not be generated (assignment operators 
 *       must not be generated in the OBS Framework)
 */
#pragma warning( disable : 4100 4511 4512 4061 )

#endif
