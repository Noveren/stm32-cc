#pragma once

#include <stdint.h>

#include "meta.hh"

#include "stm32f103xb.hh"
namespace svd  = stm32f103xb;
namespace core = core_cm3;


namespace LL {
    namespace bus {
        #define PRCC reinterpret_cast<svd::RCC::TypeDef *>(svd::BASE::RCC)

        using AHB  = svd::RCC::AHBENR::Msk;
        using APB2 = svd::RCC::APB2ENR::Msk;
        using APB1 = svd::RCC::APB1ENR::Msk;

        template <typename T,
            typename = typename meta::enable_if<
               meta::is_same<T, AHB >::value
            || meta::is_same<T, APB2>::value
            || meta::is_same<T, APB1>::value
        >::type>
        struct API {
            template <T... Periphs>
            static inline void EnableClock(void) {
                constexpr uint32_t val = (... | static_cast<uint32_t>(Periphs));
                volatile uint32_t tempreg;
                if constexpr (meta::is_same<T, AHB>::value) {
                    SET_BIT(PRCC->AHBENR , val);
                    tempreg = READ_BIT(PRCC->APB2ENR, val);
                } else if constexpr (meta::is_same<T, APB2>::value) {
                    SET_BIT(PRCC->APB2ENR, val);
                    tempreg = READ_BIT(PRCC->APB2ENR, val);
                } else if constexpr (meta::is_same<T, APB1>::value) {
                    SET_BIT(PRCC->APB1ENR, val);
                    tempreg = READ_BIT(PRCC->APB1ENR, val);
                }
                (void)tempreg;
            }

            template <T... Periphs>
            static inline void DisableClock(void) {
                constexpr uint32_t val = (... | static_cast<uint32_t>(Periphs));
                if constexpr (meta::is_same<T, AHB>::value) {
                    CLEAR_BIT(PRCC->AHBENR , val);
                } else if constexpr (meta::is_same<T, APB2>::value) {
                    CLEAR_BIT(PRCC->APB2ENR, val);
                } else if constexpr (meta::is_same<T, APB1>::value) {
                    CLEAR_BIT(PRCC->APB1ENR, val);
                }
            }
        };

        #undef PRCC
    }
    
    namespace cortex {
        namespace NVIC {
            #define PSCB  reinterpret_cast<core::SCB::TypeDef*>(core::BASE::SCB )
            #define PNVIC reinterpret_cast<core::NVIC::TypeDef*>(core::BASE::NVIC)

            using IRQn = svd::IRQn;

            constexpr uint32_t PriorityBits = 4U;
            enum class PriorityGroup: uint32_t {
                Zero  = 0x00000007U,
                One   = 0x00000006U,
                Two   = 0x00000005U,
                Three = 0x00000004U,
                Four  = 0x00000003U,
            };

            template <PriorityGroup PriorityGroup>
            struct API {            
                static inline void SetPriorityGrouping(void) {
                    constexpr uint32_t grp = (static_cast<uint32_t>(PriorityGroup) & (uint32_t)0x07UL);
                    constexpr uint32_t msk =
                        static_cast<uint32_t>(core::SCB::AIRSR::Msk::VECTKEY) |
                        static_cast<uint32_t>(core::SCB::AIRSR::Msk::PRIGROUP);
                    constexpr uint32_t val =
                        (static_cast<uint32_t>(0x5FAUL) << core::SCB::AIRSR::Pos_VECTKEY) |
                        (                           grp << core::SCB::AIRSR::Pos_PRIGROUP);
                    uint32_t reg = ((PSCB->AIRCR & ~msk) | val);
                    PSCB->AIRCR = reg;
                }

                template <IRQn N, uint32_t PreemptPriority, uint32_t SubPriority>
                static inline void SetPriority(void) {
                    // EncodePriority
                    constexpr uint32_t grp = (static_cast<uint32_t>(PriorityGroup) & (uint32_t)0x07UL);
                    constexpr uint32_t PreemptPriorityBits =
                        ((7UL - grp) > static_cast<uint32_t>(PriorityBits))
                        ? static_cast<uint32_t>(PriorityBits)
                        : static_cast<uint32_t>(7UL - grp);
                    constexpr uint32_t SubPriorityBits =
                        ((grp + static_cast<uint32_t>(PriorityBits)) < static_cast<uint32_t>(7UL))
                        ? static_cast<uint32_t>(0UL)
                        : static_cast<uint32_t>((grp - 7UL) + static_cast<uint32_t>(PriorityBits));
                    constexpr uint32_t priority = (
                          ((PreemptPriority & static_cast<uint32_t>((1UL << (PreemptPriorityBits)) - 1UL)) << SubPriorityBits)
                        | ((SubPriority     & static_cast<uint32_t>((1UL << (SubPriorityBits    )) - 1UL))                   )
                    );
                    // SetPriority
                    if constexpr (static_cast<int32_t>(N) >= 0) {
                        PNVIC->IP[static_cast<uint32_t>(N)] = static_cast<uint8_t>(
                            (priority << (8U - PriorityBits)) & static_cast<uint32_t>(0xFFUL)
                        );
                    } else {
                        PSCB->SHP[(static_cast<uint32_t>(N) & 0xFUL) - 4UL] = static_cast<uint8_t>(
                            (priority << (8U - PriorityBits)) & static_cast<uint32_t>(0xFFUL)
                        );
                    }
                }
            };

            #undef PSCB
            #undef PNVIC
        }




    }

    // namespace io {
    //     namespace af {
    //         static inline void Remap_SWJ_NOJTAG(void)
    //         {
    //             MODIFY_REG(AFIO->MAPR, AFIO_MAPR_SWJ_CFG, AFIO_MAPR_SWJ_CFG_JTAGDISABLE);
    //         }
    //     }

    //     template <uint8_t Pin>
    //     struct Gpio {

    //     };

    // }
}