/*
    FreeRTOS V9.0.0 - Copyright (C) 2016 Real Time Engineers Ltd.
    All rights reserved
    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.
    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that has become a de facto standard.             *
     *                                                                       *
     *    Help yourself get started quickly and support the FreeRTOS         *
     *    project by purchasing a FreeRTOS tutorial book, reference          *
     *    manual, or both from: http://www.FreeRTOS.org/Documentation        *
     *                                                                       *
     *    Thank you!                                                         *
     *                                                                       *
    ***************************************************************************
    This file is part of the FreeRTOS distribution.
    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>!AND MODIFIED BY!<< the FreeRTOS exception.
    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
    >>!   distribute a combined work that includes FreeRTOS without being   !<<
    >>!   obliged to provide the source code for proprietary components     !<<
    >>!   outside of the FreeRTOS kernel.                                   !<<
    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available from the following
    link: http://www.freertos.org/a00114.html
    1 tab == 4 spaces!
    ***************************************************************************
     *                                                                       *
     *    Having a problem?  Start by reading the FAQ "My application does   *
     *    not run, what could be wrong?"                                     *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                               *
     *                                                                       *
    ***************************************************************************
    http://www.FreeRTOS.org - Documentation, books, training, latest versions,
    license and Real Time Engineers Ltd. contact details.
    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.
    http://www.OpenRTOS.com - Real Time Engineers ltd license FreeRTOS to High
    Integrity Systems to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and middleware.
    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.
    1 tab == 4 spaces!
*/


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html.
 *----------------------------------------------------------*/

/* Ensure stdint is only used by the compiler, and not the assembler. */
#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
 #include <stdint.h>
 #include "globals.h"
 extern uint32_t SystemCoreClock;
#endif

#define configUSE_PREEMPTION                    _rtos_use_preemption
#define configUSE_IDLE_HOOK                     _rtos_use_idle_hook
#define configUSE_TICK_HOOK                     _rtos_use_tick_hook
#define configCPU_CLOCK_HZ                      ( SystemCoreClock )
#define configTICK_RATE_HZ                      ( ( TickType_t ) _rtos_tick_rate_hz )
#define configMAX_PRIORITIES                    ( _rtos_max_priorities )
#define configMINIMAL_STACK_SIZE                ( ( uint16_t ) _rtos_minimal_stack_size )
#define configTOTAL_HEAP_SIZE                   ( ( size_t ) _rtos_total_heap_size )
#define configMAX_TASK_NAME_LEN                 ( _rtos_max_task_name_len )
#define configUSE_TRACE_FACILITY                _rtos_use_trace_facility
#define configUSE_16_BIT_TICKS                  0
#define configIDLE_SHOULD_YIELD                 _rtos_idle_should_yield
#define configUSE_MUTEXES                       _rtos_use_mutexes
#define configQUEUE_REGISTRY_SIZE               _rtos_queue_registry_size
#define configCHECK_FOR_STACK_OVERFLOW          _rtos_check_for_stack_overflow
#define configUSE_RECURSIVE_MUTEXES             _rtos_use_recursive_mutexes
#define configUSE_MALLOC_FAILED_HOOK            _rtos_use_malloc_failed_hook
#define configUSE_APPLICATION_TASK_TAG          _rtos_application_task_tag
#define configUSE_COUNTING_SEMAPHORES           _rtos_use_counting_semaphores
#define configGENERATE_RUN_TIME_STATS           _rtos_generate_run_time_stats


/* Software timer definitions. */
#define configUSE_TIMERS                        0
#define configTIMER_TASK_PRIORITY               ( 2 )
#define configTIMER_QUEUE_LENGTH                10
#define configTIMER_TASK_STACK_DEPTH            ( configMINIMAL_STACK_SIZE * 2 )


/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */
#define INCLUDE_vTaskPrioritySet                1
#define INCLUDE_uxTaskPriorityGet               1
#define INCLUDE_vTaskDelete                     1
#define INCLUDE_vTaskCleanUpResources           1
#define INCLUDE_vTaskSuspend                    1
#define INCLUDE_vTaskDelayUntil                 1
#define INCLUDE_vTaskDelay                      1
#define INCLUDE_xQueueGetMutexHolder            1
#define INCLUDE_xTaskGetSchedulerState          1
#define INCLUDE_eTaskGetState                   1



/* Normal assert() semantics without relying on the provision of an assert.h
header file. */
//#define configASSERT( x ) if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ); }

/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
   standard names. */
#define vPortSVCHandler    SVC_Handler
#define xPortPendSVHandler PendSV_Handler
/* IMPORTANT: This define MUST be commented when used with STM32Cube firmware,
              to prevent overwriting SysTick_Handler defined within STM32Cube HAL */
/*#define xPortSysTickHandler SysTick_Handler*/

#endif /* FREERTOS_CONFIG_H */
