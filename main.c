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
    app_setup( );

    os_task_create( app_task_heartBit, "bit", 128u, NULL, 2u, NULL );
    
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
    led_struct.pin   = _app_heart_bit_pin;
    hal_gpio_init( _app_heart_bit_port, &led_struct );

    for( ; ; )
    {
        hal_gpio_togglePin( _app_heart_bit_port, _app_heart_bit_pin );
        os_task_delay( 1000u );
    }
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
