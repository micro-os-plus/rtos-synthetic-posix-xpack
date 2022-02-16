/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2016 Liviu Ionescu.
 *
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose is hereby granted, under the terms of the MIT license.
 *
 * If a copy of the license was not distributed with this file, it can
 * be obtained from https://opensource.org/licenses/MIT/.
 */

#ifndef MICRO_OS_PLUS_ARCHITECTURE_POSIX_RTOS_PORT_OS_DECLS_H_
#define MICRO_OS_PLUS_ARCHITECTURE_POSIX_RTOS_PORT_OS_DECLS_H_

// ----------------------------------------------------------------------------

/*
 * This file is included in `micro-os-plus/rtos.h` to customise
 * it with POSIX specific declarations.
 */

#if defined(MICRO_OS_PLUS_INCLUDE_CONFIG_H)
#include <micro-os-plus/config.h>
#endif // MICRO_OS_PLUS_INCLUDE_CONFIG_H

// ----------------------------------------------------------------------------

#include <micro-os-plus/rtos/port/declarations-c.h>

// ----------------------------------------------------------------------------

#if !defined(MICRO_OS_PLUS_INTEGER_SYSTICK_FREQUENCY_HZ)
#define MICRO_OS_PLUS_INTEGER_SYSTICK_FREQUENCY_HZ (1000)
#endif

#if !defined(MICRO_OS_PLUS_INTEGER_RTOS_MIN_STACK_SIZE_BYTES)
#define MICRO_OS_PLUS_INTEGER_RTOS_MIN_STACK_SIZE_BYTES (SIGSTKSZ)
#endif

#if !defined(MICRO_OS_PLUS_INTEGER_RTOS_DEFAULT_STACK_SIZE_BYTES)
#if defined(__linux__)
#define MICRO_OS_PLUS_INTEGER_RTOS_DEFAULT_STACK_SIZE_BYTES (2 * SIGSTKSZ)
#else
#define MICRO_OS_PLUS_INTEGER_RTOS_DEFAULT_STACK_SIZE_BYTES (SIGSTKSZ)
#endif // defined(__linux__)
#endif

#if !defined(MICRO_OS_PLUS_INTEGER_RTOS_MAIN_STACK_SIZE_BYTES)
#define MICRO_OS_PLUS_INTEGER_RTOS_MAIN_STACK_SIZE_BYTES \
  (MICRO_OS_PLUS_INTEGER_RTOS_DEFAULT_STACK_SIZE_BYTES)
#endif

#if !defined(MICRO_OS_PLUS_INTEGER_RTOS_IDLE_STACK_SIZE_BYTES)
#define MICRO_OS_PLUS_INTEGER_RTOS_IDLE_STACK_SIZE_BYTES \
  (MICRO_OS_PLUS_INTEGER_RTOS_DEFAULT_STACK_SIZE_BYTES)
#endif

// ----------------------------------------------------------------------------

#ifdef __cplusplus

// ----------------------------------------------------------------------------

#include <signal.h>
// Platform definitions
#include <sys/time.h>

#include <cstdint>
#include <cstddef>

// ----------------------------------------------------------------------------

#pragma GCC diagnostic push

#if defined(__clang__)
#pragma clang diagnostic ignored "-Wc++98-compat"
#endif

namespace micro_os_plus
{
  namespace rtos
  {
    namespace port
    {
      // ----------------------------------------------------------------------

      namespace stack
      {
        // Assume 64-bits core.
        using element_t = micro_os_plus_port_thread_stack_element_t;

        // Align stack to 8 bytes.
        using allocation_element_t
            = micro_os_plus_port_thread_stack_allocation_element_t;

        // Initial value for the minimum stack size in bytes.
        constexpr std::size_t min_size_bytes
            = MICRO_OS_PLUS_INTEGER_RTOS_MIN_STACK_SIZE_BYTES;

        // Initial value for the default stack size in bytes.
        constexpr std::size_t default_size_bytes
            = MICRO_OS_PLUS_INTEGER_RTOS_DEFAULT_STACK_SIZE_BYTES;

        constexpr element_t magic = 0xEFBEADDEEFBEADDE;
      } // namespace stack

      namespace interrupts
      {
        // True if signal blocked
        using state_t = micro_os_plus_port_interrupts_state_t;

        namespace state
        {
          constexpr state_t init = false;
        }

        extern sigset_t clock_set;

      } // namespace interrupts

      namespace scheduler
      {
        using state_t = micro_os_plus_port_scheduler_state_t;

        namespace state
        {
          constexpr state_t locked = true;
          constexpr state_t unlocked = false;
          constexpr state_t init = unlocked;
        } // namespace state

        extern state_t lock_state;

      } // namespace scheduler

      namespace clock
      {
        constexpr int signal_number = SIGALRM;
      }

      using thread_context_t = struct thread_context_s
      {
        // On POSIX, the context is saved on standard (although deprecated)
        // ucontext_t structures. It requires _XOPEN_SOURCE=700L to compile.
        ucontext_t ucontext; //
      };

      // ----------------------------------------------------------------------
    } // namespace port
  } // namespace rtos
} // namespace micro_os_plus

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------

#endif // __cplusplus

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_POSIX_RTOS_PORT_OS_DECLS_H_

// ----------------------------------------------------------------------------
