/**------------------------------------------------------------------------------------------------
  * @author  Hotboards Team
  * @version V1.0.0
  * @date    06-June-2020
  * @brief   The file will only contains msp functions where the user will configure the pins to
  *          a given peripheral
-------------------------------------------------------------------------------------------------*/

/* Includes -------------------------------------------------------------------------------------*/
#include "hal.h"
/* Private typedef ------------------------------------------------------------------------------*/
/* Private define -------------------------------------------------------------------------------*/
/* Private macro --------------------------------------------------------------------------------*/
/* Private variables ----------------------------------------------------------------------------*/
/* Private function prototypes ------------------------------------------------------------------*/
/* Private functions ----------------------------------------------------------------------------*/

/**------------------------------------------------------------------------------------------------
  * @brief  This function will be called by the hal_init function, nad only should be contain
  *         code to be executed before the scheduler run
  -----------------------------------------------------------------------------------------------*/
void hal_mspInit( void ) 
{
    hal_rcc_clk_init_t rcc_clk_init_struct;
    hal_rcc_osc_init_t rcc_osc_init_struct;
    hal_wwdg_handle_t  wwdg_handle_struct;

    /* init semihosting through stdio functions, this only work on debug mode */
    #ifndef NDEBUG
        initialise_monitor_handles( );
    #endif

    /* Select HSI48 Oscillator as PLL source */
    rcc_osc_init_struct.oscillator_type = _hal_rcc_oscillatortype_hsi48;
    rcc_osc_init_struct.pll.pll_state   = _hal_rcc_pll_on;
    rcc_osc_init_struct.pll.pll_source  = _hal_rcc_pllsource_hsi48;
    rcc_osc_init_struct.pll.prediv      = _hal_rcc_prediv_div2;
    rcc_osc_init_struct.pll.pllmul      = _hal_rcc_pll_mul2;
    hal_rcc_oscConfig( &rcc_osc_init_struct );

    /* Select PLL as system clock source and configure the HCLK and PCLK1 clocks dividers */
    rcc_clk_init_struct.clock_type      = _hal_rcc_clocktype_sysclk | _hal_rcc_clocktype_hclk | _hal_rcc_clocktype_pclk1;
    rcc_clk_init_struct.sysclk_source   = _hal_rcc_sysclksource_pllclk;
    rcc_clk_init_struct.ahbclk_divider  = _hal_rcc_sysclk_div1;
    rcc_clk_init_struct.apb1clk_divider = _hal_rcc_hclk_div1;
    hal_rcc_clockConfig( &rcc_clk_init_struct, _hal_flash_latency_1 );

    /* Update global variable SystemCoreClock*/
    hal_system_coreClockUpdate( );

    /* WWDG clock counter = (PCLK1 (48MHz)/4096)/8) = 1464.8 Hz (~683 us)
    WWDG Window value = 80 (0x50) means that the WWDG counter should be refreshed only when the counter is 
    below 80 and greater than 64 (0x40) otherwise a reset will be generated.
    WWDG Counter value = 127 (0x7F), WWDG timeout = ~683 us * 64 = 43.7 ms
    In this case the refresh window is comprised between : ~683 * (127-80) = 32.1 ms and ~683 * 64 = 43.7 ms */
    wwdg_handle_struct.instance       = WWDG;
    wwdg_handle_struct.init.prescaler = _hal_wwdg_prescaler_8;
    wwdg_handle_struct.init.window    = 0x50;
    wwdg_handle_struct.init.counter   = 0x7F;
    wwdg_handle_struct.init.ewi_mode  = _hal_wwdg_ewi_enable;
    hal_wwdg_init( &wwdg_handle_struct );
}


/**------------------------------------------------------------------------------------------------
  * @brief  Callbacj function to be called by hal_deInit functions and should be contain only
  *         code to de-initialize what was initialized at mspInit function
  * @param  None
  * @retval None
  -----------------------------------------------------------------------------------------------*/
void hal_mspDeInit( void )
{

}

