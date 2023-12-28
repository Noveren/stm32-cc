
#include "stm32f103xb.h"
#include "stm32f1xx_ll_system.h"
#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_utils.h"
#include "system_stm32f1xx.h"


void MSP_SystemClock_Config(void) {
    // latency 访问延迟的设置取决于系统运行速度
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);
    while (LL_FLASH_GetLatency() != LL_FLASH_LATENCY_2);

    LL_RCC_HSE_Enable();
    while (LL_RCC_HSE_IsReady() != 1);

    LL_RCC_HSE_EnableCSS();
    LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE_DIV_1, LL_RCC_PLL_MUL_9);
    LL_RCC_PLL_Enable();
    while (LL_RCC_PLL_IsReady() != 1);

    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
    LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
    while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL);

    SystemCoreClockUpdate();
    LL_Init1msTick(SystemCoreClock);

    // 配置 SYSTICK - 1ms 重载值、当前值，并使能
    // LL_Init1msTick(72000000);
    // LL_SetSystemCoreClock(72000000);
    // NVIC_DisableIRQ(SysTick_IRQn);
}

#define NVIC_PRIORITYGROUP_0 ((uint32_t)0x00000007)
#define NVIC_PRIORITYGROUP_1 ((uint32_t)0x00000006)
#define NVIC_PRIORITYGROUP_2 ((uint32_t)0x00000005)
#define NVIC_PRIORITYGROUP_3 ((uint32_t)0x00000004)
#define NVIC_PRIORITYGROUP_4 ((uint32_t)0x00000003)

void MSP_Init(void) {
    // Peripheral Clock
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_AFIO);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

    // NVIC
    NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
    NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(
        NVIC_GetPriorityGrouping(), 15, 0
    ));

    // Alternate Function
    LL_GPIO_AF_Remap_SWJ_NOJTAG();

    // System Clock
    MSP_SystemClock_Config();
}
