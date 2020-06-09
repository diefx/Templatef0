/**------------------------------------------------------------------------------------------------
  * @author  Diego Perez
  * @version V1.0.0
  * @date    06-June-2020
  * @brief   File to define and declare (extern) symbols to be used across the project
  *          A good example will be global variables and definitios for pin out and etc ..
-------------------------------------------------------------------------------------------------*/

#ifndef _GLOBALS_H
#define _GLOBALS_H

/* Includes -------------------------------------------------------------------------------------*/
#include "hal.h"
/* Global typedef ------------------------------------------------------------------------------*/
/* Global define -------------------------------------------------------------------------------*/
/*Pinout and hardware definitions*/
#define _app_heartbit_port                  GPIOA
#define _app_heartbit_pin                   _hal_gpio_pin_5

/*Task parameter definitions*/
#define _app_heartbit_task_stack            128u
#define _app_heartbit_task_priority           2u

/*Peripheral priority interrupts definitions*/
#define _app_wwdg_priority                  2u
#define _app_wwdg_subPriority               2u

/*Rtos configuration, these are the FreeRTOSConfig control definitions, DO NOT cast this defines*/
#define _rtos_tick_rate_hz                  1000
#define _rtos_max_priorities                7
#define _rtos_minimal_stack_size            128
#define _rtos_total_heap_size               ( 4 * 1024 )
#define _rtos_max_task_name_len             8
#define _rtos_use_preemption                1
#define _rtos_use_idle_hook                 1
#define _rtos_use_tick_hook                 1
#define _rtos_use_mutexes                   0
#define _rtos_use_counting_semaphores       0
#define _rtos_use_recursive_mutexes         0
#define _rtos_use_malloc_failed_hook        1
#define _rtos_use_trace_facility            0
#define _rtos_idle_should_yield             1
#define _rtos_queue_registry_size           4
#define _rtos_check_for_stack_overflow      0
#define _rtos_application_task_tag          0
#define _rtos_generate_run_time_stats       0
/* Global macro --------------------------------------------------------------------------------*/
/* Global variables ----------------------------------------------------------------------------*/
extern uint32_t                             SystemCoreClock;
extern hal_wwdg_handle_t                    wwdg_handle_struct;
/* Global function prototypes ------------------------------------------------------------------*/

#endif
