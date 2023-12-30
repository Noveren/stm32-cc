#pragma once

#include "stm32f1xx.h"
#include "stm32f103xb.h"
#include <stdint.h>

#include "meta.hh"

namespace HAL {
    namespace BUS {

        // template <typename T>
        // constexpr

        enum class AHB: uint32_t {
            sram = RCC_AHBENR_SRAMEN,
        };

        enum class APB1: uint32_t {
            pwr = RCC_APB1ENR_PWREN,
        };

        enum class APB2: uint32_t {
            afio = RCC_APB2ENR_AFIOEN,
            gpioa = RCC_APB2ENR_IOPAEN,
        };

        template <typename T, T... Periphs>
        __STATIC_INLINE void EnableClock(void) {
            constexpr uint32_t mask = (... | static_cast<uint32_t>(Periphs));
            __IO uint32_t tempreg;
            if constexpr (meta::is_same<T, APB1>::value) {
                SET_BIT(RCC->APB1ENR, mask);
                tempreg = READ_BIT(RCC->APB1ENR, mask);
            } else if constexpr (meta::is_same<T, APB2>::value) {
                SET_BIT(RCC->APB2ENR, mask);
                tempreg = READ_BIT(RCC->APB2ENR, mask);
            } else {
                static_assert(
                       meta::is_same<T, APB1>::value
                    || meta::is_same<T, APB2>::value,
                    "Undefined Bus Enum Class"
                );
            }
            (void)tempreg;
        }
    }
}