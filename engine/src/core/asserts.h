#pragma once

#include "defines.h"

// Disable assertions toggle
#define KASSERTIONS_ENABLED

#ifdef KASSERTIONS_ENABLED
#if _MSC_VER // Visual Studio compiler specific
#include <intrin.h> 
#define debugBreak() __debugbreak() // Microsoft specific macro
#else
#define debugBreak() __builtin_trap() // GCC macro
#endif

// Expression code of what caused assertion failure, return message from failed assertion, name of file of assertion, line number of assertion
KAPI void report_assertion_failure(const char* expression, const char* message, const char* file, i32 line); // defined in logger.c
 //Take expor and display as string, no message, file of expresision, line in file
 // !expr may not handle all cases as in the case of double negatives 

#define KASSERT(expr)                                                   \
    {                                                                   \
        if (expr){                                                      \
        } else{                                                         \
            report_assertion_failure(#expr, "", __FILE__, __LINE__);    \
            debugBreak();                                               \
        }                                                               \
    }

// !expr may not handle all cases as in the case of double negatives 
// Take expor and display as string, no message, file of expresision, line in file
#define KASSERT_MSG(expr, message)                                        \
    {                                                                     \
        if (expr){                                                        \
        } else{                                                           \
            report_assertion_failure(#expr, message, __FILE__, __LINE__); \
            debugBreak();                                                 \
        }                                                                 \
    }

#ifdef _DEBUG // check if in debug build

#define KASSERT_DEBUG(expr)                                               \
    {                                                                     \
        if (expr){                                                        \
        } else{                                                           \
            report_assertion_failure(#expr, "", __FILE__, __LINE__);      \
            debugBreak();                                                 \
        }                                                                 \
    }

#else
#define KASSERT_DEBUG(expr)
#endif

#else // assertions not enabled

#define KASSERT(expr)
#define KASSERT_MSG(expr, message)
#define KASSERT_DEBUG(expr)

#endif