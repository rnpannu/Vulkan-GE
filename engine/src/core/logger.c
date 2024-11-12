#include "logger.h"
#include "asserts.h"
#include "platform/platform.h"


// TODO: temporary
#include <stdio.h>
#include <string.h>
#include <stdarg.h> // Allows us to work with variatic arguments, perform string formatting on console debug writes


b8 initialize_logging(){
    // TODO: Create log file
    return TRUE;
}

void shutdown_logging(){
    // TODO: Clean up logging/write queued entries. Eventually want to write logger output files to different threads. Display console output immediately but queue file writes.
}

void log_output(log_level level, const char* message, ...){
    const char* level_strings[6] = {"[FATAL]: ", "[ERROR]: ", "[WARN]: ", "[INFO]: ", "[DEBUG]: ", "[TRACE]: "};
    b8 is_error = level < LOG_LEVEL_WARN; // if log level is error or fatal aka severely wrong

    const i32 msg_len = 32000;
    char out_message[msg_len];
    memset(out_message, 0, sizeof(out_message)); // 0 out memory. Avoid slow dynamic memory allocation on heap using malloc

    __builtin_va_list arg_ptr; // Creates a pointer list to the argument list in log_output (the ..., essentially a character array)
    // builtin is used due to a conflict with Microsoft's headers and the standard va_list

    va_start(arg_ptr, message); // Needs to know that the last parameter before the variatics is message
    vsnprintf(out_message, msg_len, message, arg_ptr); // Outputs the formatted string to buffer
    va_end(arg_ptr); // Clean up everything

    char out_message2[msg_len]; 
    
    sprintf(out_message2, "%s%s\n", level_strings[level], out_message); //printf to a string, outmessage is both buffer output and input. output to outmessage subject to %s%s\n with first string = error level
    // TODO: Platform specific output
    if (is_error){
        platform_console_write_error(out_message2, level);
    } else{
        platform_console_write(out_message2, level);
    }

} 

void report_assertion_failure(const char* expression, const char* message, const char* file, i32 line){
    log_output(LOG_LEVEL_FATAL, "Assertion Failure: %s, message: '%s', in file %s, line %d\n", expression, message, file, line); //create fatal log due to assertion failure
}
