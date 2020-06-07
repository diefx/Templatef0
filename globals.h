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
#define _app_heart_bit_port             GPIOA
#define _app_heart_bit_pin              _hal_gpio_pin_5
/* Global macro --------------------------------------------------------------------------------*/
/* Global variables ----------------------------------------------------------------------------*/
extern uint32_t         SystemCoreClock;
/* Global function prototypes ------------------------------------------------------------------*/

#endif
