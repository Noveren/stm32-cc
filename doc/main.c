
#include "stm32f103xb.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_utils.h"

#include "msp.h"

int main(void) {
    MSP_Init();

    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOD);
    
    LL_GPIO_InitTypeDef GPIO_InitStruct = {
        .Pin        = LL_GPIO_PIN_4,
        .Mode       = LL_GPIO_MODE_OUTPUT,
        .Speed      = LL_GPIO_SPEED_FREQ_LOW,
        .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
    };
    LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_4);

    while (1) {
        LL_mDelay(1000);
        LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_4);
    }

    return 0;
}