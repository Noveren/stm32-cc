
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

#include "stm32f1xx.h"

namespace HAL {
    namespace System {
        namespace Flash {
            
        }
    }

}