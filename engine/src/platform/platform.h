#pragma once

#include "defines.h"

// Aspects of states must be maintained. Specific to Linux, Windows etc. How to decouple operating
// system functionality from engine?

typedef struct platform_state {
    void* internal_state; //Type determined in platform specific c file.
} platform_state; 

KAPI b8 platform_startup(
    platform_state* plat_state, // Basic window information
    const char* application_naame,
    i32 x,
    i32 y,
    i32 width,
    i32 height);

KAPI void platform_shutdown(platform_state* plat_state);

KAPI b8 platform_pump_messages(platform_state* plat_state);

// Memory

void* platform_allocate(u64 size, b8 aligned); //malloc equivalent for platform
void platform_free(void* block, b8 aligned); //free equivalent for platform
void* platform_zero_memory(void* block, u64 size); //zero out memory
void* platform_copy_memory(void* dest, const void* source, u64 size);
void* platform_set_memory(void* dest, i32 value, u64 size);

// Platform independant console writes
void platform_console_write(const char* message, u8 colour);
void platform_console_write_error(const char* message, u8 colour);

f64 platform_get_absolute_time();   // obtain platform clock time

void platform_sleep(u64 ms); // for frame rate fine tuning



