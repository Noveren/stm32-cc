
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

#include "hal.hh"

int main(void) {
    HAL::BUS::EnableClock<HAL::BUS::APB1, HAL::BUS::APB1::pwr>();
    // HAL::BUS::EnableClock<
    //     HAL::BUS::APB2,
    //     HAL::BUS::APB2::afio, HAL::BUS::APB2::gpioa
    // >();
    return 0;
}

/*
@ link register save eliminated.
	sub	sp, sp, #8
	ldr	r3, .L17
	ldr	r2, [r3, #28]
	orr	r2, r2, #268435456
	str	r2, [r3, #28]
	ldr	r3, [r3, #28]
	and	r3, r3, #268435456
	str	r3, [sp, #4]
	ldr	r3, [sp, #4]

	movs	r0, #0
	add	sp, sp, #8
	@ sp needed
*/

/*
@ link register save eliminated.
	sub	sp, sp, #8
	ldr	r3, .L17
	ldr	r2, [r3, #28]
	orr	r2, r2, #268435456
	str	r2, [r3, #28]
	ldr	r2, [r3, #28]
	and	r2, r2, #268435456
	str	r2, [sp, #4]
	ldr	r2, [sp, #4]
    
	ldr	r2, [r3, #24]
	orr	r2, r2, #5
	str	r2, [r3, #24]
	ldr	r3, [r3, #24]
	and	r3, r3, #5
	str	r3, [sp]
	ldr	r3, [sp]

	movs	r0, #0
	add	sp, sp, #8
	@ sp needed
*/