#pragma once

#include "defines.h"


#define LOG_WARN_ENABLED 1
#define LOG_INFO_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1

#if KRELEASE == 1
#define LOG_DEBUG_ENABLED 0
#define LOG_TRACE_ENABLED 0
#endif

typedef enum log_level {
    LOG_LEVEL_FATAL = 0,
    LOG_LEVEL_ERROR = 1,
    LOG_LEVEL_WARN = 2,
    LOG_LEVEL_INFO = 3,
    LOG_LEVEL_DEBUG = 4,
    LOG_LEVEL_TRACE = 5
} log_level;


b8 initialize_logging();
void shutdown_logging();

KAPI void log_output(log_level level, const char* message, ...); // Output message similar to printf debugging


#define KFATAL(message, ...) log_output(LOG_LEVEL_FATAL, message, ##__VA_ARGS__); // Variatic arguments, compiler specific

#ifndef KERROR
#define KERROR(message, ...) log_output(LOG_LEVEL_ERROR, message, ##__VA_ARGS__) // Logs an error level message
#endif

#if LOG_WARN_ENABLED == 1
#define KWARN(message, ...) log_output(LOG_LEVEL_WARN, message, ##__VA_ARGS__) // Logs a warning level message
#else
#define KWARN(message, ...) // Removes call from compilation if not equal to 1
#endif 

#if LOG_INFO_ENABLED == 1
#define KINFO(message, ...) log_output(LOG_LEVEL_INFO, message, ##__VA_ARGS__) // Logs an info level message
#else
#define KINFO(message, ...) // Removes call from compilation if not equal to 1
#endif 

#if LOG_DEBUG_ENABLED == 1
#define KDEBUG(message, ...) log_output(LOG_LEVEL_DEBUG, message, ##__VA_ARGS__) // Logs a debug level message
#else
#define KDEBUG(message, ...) // Removes call from compilation if not equal to 1
#endif 

#if LOG_TRACE_ENABLED == 1
#define KTRACE(message, ...) log_output(LOG_LEVEL_TRACE, message, ##__VA_ARGS__) // Logs a trace level message
#else
#define KTRACE(message, ...) // Removes call from compilation if not equal to 1
#endif 
