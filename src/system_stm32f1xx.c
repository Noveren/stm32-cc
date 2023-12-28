
#include "system_stm32f1xx.h"
#include "stm32f1xx.h" // IWYU pragma: export

// HCLK = SYSCLK >> n 分频表
const uint8_t AHBPrescTable[16U] = {
    0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9
};

const uint8_t APBPrescTable[8U] =  {
    0, 0, 0, 0, 1, 2, 3, 4
};

void SystemInit(void) {
    // Setup the microcontroller system
    // Initialize the Embedded Flash Interface, the PLL and update the
    // SystemCoreClock variable.
}

#if !defined (HSI_VALUE) || !defined (HSE_VALUE)
    #error "Function 'SystemCoreClockUpdate' need Macro 'HSI_VALUE' and 'HSE_VALUE'"
#endif

// HCLK
uint32_t SystemCoreClock = 16000000;

/**
 * @brief 更新全局变量 SystemCoreClock
*/
void SystemCoreClockUpdate(void) {
    uint32_t pllmull = 0U;
    switch (RCC->CFGR & RCC_CFGR_SWS) {
        case RCC_CFGR_SWS_HSE: {
            SystemCoreClock = HSE_VALUE;
            break;
        }
        case RCC_CFGR_SWS_PLL: {
            pllmull = ((RCC->CFGR & RCC_CFGR_PLLMULL) >> RCC_CFGR_PLLMULL_Pos);
            switch (pllmull) {
                case 0x0EU:
                case 0x0FU: pllmull = 16U; break;
                default   : pllmull += 2U; break;
            }
            switch ((RCC->CFGR & RCC_CFGR_PLLSRC) >> RCC_CFGR_PLLSRC_Pos) {
                case 0U:
                    SystemCoreClock = (HSI_VALUE >> (1U                           )) * pllmull; break;
                case 1U:
                    SystemCoreClock = (HSE_VALUE >> (RCC->CFGR & RCC_CFGR_PLLXTPRE)) * pllmull; break;
            }
            break;
        }
        default:
        case RCC_CFGR_SWS_HSI: {
            SystemCoreClock = HSI_VALUE;
            break;
        }
    }
    // SYSCLK -> HCLK
    SystemCoreClock >>= AHBPrescTable[
        (RCC->CFGR & RCC_CFGR_HPRE) >> RCC_CFGR_HPRE_Pos
    ];
}