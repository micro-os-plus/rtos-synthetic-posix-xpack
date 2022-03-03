/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus/)
 * Copyright (c) 2016 Liviu Ionescu.
 *
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose is hereby granted, under the terms of the MIT license.
 *
 * If a copy of the license was not distributed with this file, it can
 * be obtained from https://opensource.org/licenses/MIT/.
 */

#ifndef MICRO_OS_PLUS_ARCHITECTURE_POSIX_RTOS_PORT_OS_C_DECLS_H_
#define MICRO_OS_PLUS_ARCHITECTURE_POSIX_RTOS_PORT_OS_C_DECLS_H_

// ----------------------------------------------------------------------------

/*
 * This file is included in `micro-os-plus/rtos/declarations-c.h` to
 * customise it with port specific declarations.
 *
 * These structures (which basically contain handlers)
 * are conditionally included in the system objects
 * when they are implemented using the port native objects.
 */

#include <stdint.h>

#if !defined(_XOPEN_SOURCE)
#error This port requires defining _XOPEN_SOURCE=700L globally
#endif
#include <ucontext.h>

#include <signal.h>
#include <stdbool.h>

// ----------------------------------------------------------------------------

// Must match port::clock::timestamp_t
typedef uint64_t micro_os_plus_port_clock_timestamp_t;

// Must match port::clock::duration_t
typedef uint32_t micro_os_plus_port_clock_duration_t;

// Must match port::clock::offset_t
typedef uint64_t micro_os_plus_port_clock_offset_t;

typedef struct
{
  ucontext_t ucontext; //
} micro_os_plus_port_thread_context_t;

typedef bool micro_os_plus_port_scheduler_state_t;

// Signal set (true if signal blocked)
typedef bool micro_os_plus_port_interrupts_state_t;

typedef uint64_t micro_os_plus_port_thread_stack_element_t;
typedef uint64_t micro_os_plus_port_thread_stack_allocation_element_t;

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_POSIX_RTOS_PORT_OS_C_DECLS_H_

// ----------------------------------------------------------------------------
