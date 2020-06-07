/**------------------------------------------------------------------------------------------------
  * @author  Hotboards Team
  * @version V1.0.0
  * @date    18-June-2014
  * @brief   Template
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
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  -----------------------------------------------------------------------------------------------*/
void hal_mspInit( void ) /* {{{{ */
{
    hal_rcc_clk_init_t rcc_clk_init_struct;
    hal_rcc_osc_init_t rcc_osc_init_struct;

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
} /* }}}} */


/**------------------------------------------------------------------------------------------------
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  -----------------------------------------------------------------------------------------------*/
void hal_mspDeInit( void ) /* {{{{ */
{

} /* }}}} */

