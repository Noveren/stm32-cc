#pragma once

#include "stm32f1xx.h"
#include <stdint.h>

namespace HAL {
    namespace BUS {
        enum class Bus {
            AHB1, APB1, APB2
        };
        template<Bus bus>
        static inline void EnableClock(uint32_t RCC_Msks) {
            if constexpr(bus == Bus::AHB1) {
                SET_BIT(RCC->AHBENR, RCC_Msks);
            } else if constexpr(bus == Bus::APB1) {
                SET_BIT(RCC->APB1ENR, RCC_Msks);
            } else if constexpr(bus == Bus::APB2) {
                SET_BIT(RCC->APB2ENR, RCC_Msks);
            }
        }
    }
}