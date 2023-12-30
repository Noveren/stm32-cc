
// 默认中断
extern "C" {
    #define ISR_INFINITY_LOOP(NAME) void NAME(void) { while (1); }
    #define ISR_UNUSED(NAME)        void NAME(void) {            }

    ISR_INFINITY_LOOP( NMI_Handler           )
    ISR_INFINITY_LOOP( HardFault_Handler     )
    ISR_INFINITY_LOOP( MemManage_Handler     )
    ISR_INFINITY_LOOP( BusFault_Handler      )
    ISR_INFINITY_LOOP( UsageFault_Handler    )

    ISR_UNUSED( SVC_Handler      )
    ISR_UNUSED( DebugMon_Handler )
    ISR_UNUSED( PendSV_Handler   )
    ISR_UNUSED( SysTick_Handler  )
}


#include "LL.hh"

using APB1_Config = LL::bus::API<LL::bus::APB1>;
using APB2_Config = LL::bus::API<LL::bus::APB2>;
using NVIC_Config = LL::cortex::NVIC::API<LL::cortex::NVIC::PriorityGroup::Four>;

void MSP_SystemClock_Config(void);

int main(void) {
    APB1_Config::EnableClock<LL::bus::APB1::PWR>();
    APB2_Config::EnableClock<LL::bus::APB2::AFIO>();

    NVIC_Config::SetPriorityGrouping();
    NVIC_Config::SetPriority<LL::cortex::NVIC::IRQn::SysTick, 15, 0>();

    // io::af::Remap_SWJ_NOJTAG();

    // // SystemClock_Config

    // APB2_Config::EnableClock<
    //     LL::bus::APB2::gpioa,
    //     bus::APB2::gpiob,
    //     bus::APB2::gpiod
    // >();

    return 0;
}