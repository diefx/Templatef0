/**------------------------------------------------------------------------------------------------
  * Hotboards Team
  * @version V1.0.0
  * @date    06-June-2020
  * @brief   the user shall use this file only to place the interrupt vectors
-------------------------------------------------------------------------------------------------*/

/* Includes -------------------------------------------------------------------------------------*/
#include "cmsis.h"
#include "hal.h"
#include "rtos.h"
/* Private typedef ------------------------------------------------------------------------------*/
/* Private define -------------------------------------------------------------------------------*/
/* Private macro --------------------------------------------------------------------------------*/
/* Private variables ----------------------------------------------------------------------------*/
/* Private function prototypes ------------------------------------------------------------------*/
/* Private functions ----------------------------------------------------------------------------*/

/**------------------------------------------------------------------------------------------------
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  -----------------------------------------------------------------------------------------------*/
void hal_irq_nmi( void )
{
    /* Go to infinite loop when Hard Fault exception occurs */
    __sys_assert( 0u );
}


/**------------------------------------------------------------------------------------------------
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  -----------------------------------------------------------------------------------------------*/
void hal_irq_hardFault( void )
{
    /* Go to infinite loop when Hard Fault exception occurs */
    __sys_assert( 0u );
}


/**------------------------------------------------------------------------------------------------
  * @brief  This function handles SysTick Interrupt.
  * @param  None
  * @retval None
  -----------------------------------------------------------------------------------------------*/
void hal_irq_sysTick( void )
{
    /* query if the os is running */
    if( os_kernel_getSchedulerState( ) != _os_scheduler_not_started )
    {
        /* service the os tick interrupt */
        os_kernel_sysTickHandler( );
    }
    /* increment the internal tick for the hal drivers */
    hal_incTick( );
}


/**------------------------------------------------------------------------------------------------
  * @brief  This function handles windowed watchdog timer Interrupt.
  * @param  None
  * @retval None
  -----------------------------------------------------------------------------------------------*/
void hal_irq_wwdg( void )
{
    hal_wwdg_irqHandler( &wwdg_handle_struct );
}
