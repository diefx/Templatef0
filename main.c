/**------------------------------------------------------------------------------------------------
  * @author  Diego Perez
  * @version V1.0.0
  * @date    06-June-2020
  * @brief   Template
-------------------------------------------------------------------------------------------------*/

/* Includes -------------------------------------------------------------------------------------*/
#include "hal.h"
#include "rtos.h"
#include "globals.h"
/* Private typedef ------------------------------------------------------------------------------*/
/* Private define -------------------------------------------------------------------------------*/
/* Private macro --------------------------------------------------------------------------------*/
/* Private variables ----------------------------------------------------------------------------*/
/* Private function prototypes ------------------------------------------------------------------*/
static void app_setup( void );
static void app_task_heartBit( void *params );


/**------------------------------------------------------------------------------------------------
  * @brief  Aplication entry point
  * ---------------------------------------------------------------------------------------------*/
int main ( void )
{
    /* Call the basic initializations like clock configuration */
    app_setup( );

    /* Place as many task need to registered to run */
    os_task_create( app_task_heartBit, "bit", _app_heartbit_task_stack, NULL, _app_heartbit_task_priority, NULL );

    /* Run the freertos scheduler */   
    os_kernel_startScheduler( );
    /* Program never reach this point */
    __sys_assert( 0u );
}


/**------------------------------------------------------------------------------------------------
 * @brief   General Initializations, the function will be exceuted before the rtos scheduler 
 *          start to run
 * ----------------------------------------------------------------------------------------------*/
static void app_setup( void ) 
{
    hal_init( );
}


/**------------------------------------------------------------------------------------------------
 * @brief   General Initializations
 * @param   void pointer to wherever user want to send to this task
 * ----------------------------------------------------------------------------------------------*/
static void app_task_heartBit( void *params )
{
    hal_gpio_init_t led_struct;
    
    __hal_rcc_gpioa_clk_enable( );

    led_struct.mode  = _hal_gpio_mode_output_pp;
    led_struct.pull  = _hal_gpio_pullup;
    led_struct.speed = _hal_gpio_speed_freq_low;
    led_struct.pin   = _app_heartbit_pin;
    hal_gpio_init( _app_heartbit_port, &led_struct );

    for( ; ; )
    {
        hal_gpio_togglePin( _app_heartbit_port, _app_heartbit_pin );
        os_task_delay( 1000u );
    }
}


/**------------------------------------------------------------------------------------------------
 * @brief   This fucntion is called whenever there is no other task running, user can add code
 *          to be excuted in the background or could be a good idea to call a sleep instruction
 * ----------------------------------------------------------------------------------------------*/
void os_kernel_idleTask( void )
{

}


/**------------------------------------------------------------------------------------------------
 * @brief   Function called every time a context switch ocurres
 * ----------------------------------------------------------------------------------------------*/
void os_kernel_tickHook( void )
{
    /*TO DO: find a better place to kick the dog*/
    hal_wwdg_refresh( &wwdg_handle_struct );
}


/**------------------------------------------------------------------------------------------------
 * @brief   the kernel will jump here when for any reason an object was trying to be created and 
 *          failed because there wasn't left memory set in configTOTAL_HEAP_SIZE
 * ----------------------------------------------------------------------------------------------*/
void os_kernel_mallocFailedHook( void )
{
    __sys_assert( 0u );
}


/**------------------------------------------------------------------------------------------------
  * @brief  Reports the name of the source file and the source line number where the assert_param
  *         error has occurred. aplication rah here throuhg macro __sys_assert
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * ----------------------------------------------------------------------------------------------*/
void assert_failed( char * file, int line )
{
    /*disable all interrupts to prevent rtos from running again*/
    __os_disable_interrupts( );

    #ifndef NDEBUG
         printf( "Suspected error on file: %s, line %d\r\n", file, line );
    #endif
    /* Infinite loop */
    while( 1 )
    {
        /* MISRA */
    }
}
