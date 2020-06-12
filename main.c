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
hal_wwdg_handle_t  wwdg_handle_struct;
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
    rtos_task_create( app_task_heartBit, "bit", _app_heartbit_task_stack, NULL, _app_heartbit_task_priority, NULL );

    /* Run the freertos scheduler */   
    rtos_kernel_startScheduler( );
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

    /*windowed watch dog configuration*/ 
    wwdg_handle_struct.instance       = WWDG;
    wwdg_handle_struct.init.prescaler = _app_wwdg_preeescaler;
    wwdg_handle_struct.init.window    = _app_wwdg_window_lower;
    wwdg_handle_struct.init.counter   = _app_wwdg_max_count;
    wwdg_handle_struct.init.ewi_mode  = _hal_wwdg_ewi_enable;
    hal_wwdg_init( &wwdg_handle_struct );

    /*configure and enable peripheral interrupts*/
    hal_nvic_setPriority( _hal_wwdg_irq, _app_wwdg_priority, _app_wwdg_subPriority );
    hal_nvic_enableIrq( _hal_wwdg_irq );
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
        rtos_task_delay( 1000u );
    }
}


/**------------------------------------------------------------------------------------------------
 * @brief   This fucntion is called whenever there is no other task running, user can add code
 *          to be excuted in the background or could be a good idea to call a sleep instruction
 * ----------------------------------------------------------------------------------------------*/
void rtos_kernel_idleTask( void )
{

}


/**------------------------------------------------------------------------------------------------
 * @brief   Function called every time a context switch ocurres
 * ----------------------------------------------------------------------------------------------*/
void rtos_kernel_tickHook( void )
{
    /*TO DO: find a better place to kick the dog*/
    static uint32_t wwdg_kick = 0;
    
    wwdg_kick++;
    if( wwdg_kick >= ( _app_wwdg_refresh_time / _rtos_tick_period_ms ) )
    {
        /*40ms has been pass, time to kick the dog */
        hal_wwdg_refresh( &wwdg_handle_struct );
        wwdg_kick = 0u;
    }
}


/**------------------------------------------------------------------------------------------------
 * @brief   the kernel will jump here when for any reason an object was trying to be created and 
 *          failed because there wasn't left memory set in configTOTAL_HEAP_SIZE
 * ----------------------------------------------------------------------------------------------*/
void rtos_kernel_mallocFailedHook( void )
{
    __sys_assert( 0u );
}


/**------------------------------------------------------------------------------------------------
 * @brief   the kernel will jump here when for any reason a task is created but is not enough stak
 *          to allocate its internal variables
 *          THIS FUCNTION SHOULD ONLY BE USED DURING DEVELOPMENT STAGE
 * @param   task: task where the stack allocation failed
 * @param   task_name: string id assigned to the task that failed do the stack allocation
 * ----------------------------------------------------------------------------------------------*/
void rtos_kernel_StackOverflowHook( rtos_task_handle_t task, signed char *task_name )
{
    #ifndef NDEBUG
         printf( "Stack allocation error on task: %s\r\n", task_name );
    #endif
    __sys_assert( 0u );
}


/**------------------------------------------------------------------------------------------------
 * @brief   The callback is called just after a wwdg event occurres and righ before a warn reset
 *          user should place the code to handle the necesary steps to reset in a safety fashion
 *          closing any pending process  
 * @param   hwwdg: pointer to wwdg descriptor structure
 * ----------------------------------------------------------------------------------------------*/
void hal_wwdg_callback_earlyWakeup( hal_wwdg_handle_t *wwdg_handler )
{
    /*To avoid compiler warnings, while the user define its own content*/
    ( void* )wwdg_handler;
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
    __rtos_disable_interrupts( );

    #ifndef NDEBUG
         printf( "Suspected error on file: %s, line %d\r\n", file, line );
    #endif
    /* Infinite loop */
    while( 1 )
    {
        /* MISRA */
    }
}
