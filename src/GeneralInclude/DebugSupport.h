//
//
// DebugSupport.h
//
//
// Change Record:

/**
 * @file DebugSupport.h 
 * This file defines the assert macro. The definition depends on the value of
 * the preprocessor symbols USE_SYSTEM_ASSERT and NDEBUG
 * (these symbols should normally be defined in file <code>CompilerSwitches</code>).
 * If either or both of these two symbols are defined, then the standard definition
 * of assert as contained in the standard library is used. If neither of these two
 * symbols is defined, then assert is defined to output an error message whenever the
 * argument expression is true. This form of assert is useful when it is desirable
 * to be notified of assertion violation but it is also desirable to continue execution
 * after the violation in order to check how the program copes with a non-nominal 
 * situation.
 */

#ifndef DEBUGSUPPORT_H
#define DEBUGSUPPORT_H

#ifndef COMPILERSWITCHES_H
#error The "CompilerSwitches.h" header file must be included before this file.
#endif

#if defined(USE_SYSTEM_ASSERT) || defined(NDEBUG)
#include <assert.h>
#else
#include <stdio.h>
#undef assert
#define assert(expr) ((expr) || fprintf(stderr, \
        "*** WARNING ***: Assertion (%s) failed in file %s at line %d.\n", \
        #expr, __FILE__, __LINE__))
#endif

#endif
