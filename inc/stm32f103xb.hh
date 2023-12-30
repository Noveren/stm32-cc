#pragma once

#define __Pos_to_Msk(V, NAME) NAME = (V << Pos_##NAME)

#include <stdint.h>

namespace core_cm3 {
    namespace BASE {
        constexpr uint32_t SCS       = 0xE000E000UL;
        constexpr uint32_t ITM       = 0xE0000000UL;
        constexpr uint32_t DWT       = 0xE0001000UL;
        constexpr uint32_t TPI       = 0xE0040000UL;
        constexpr uint32_t CoreDebug = 0xE000EDF0UL;
        constexpr uint32_t SysTick   = SCS +  0x0010UL;
        constexpr uint32_t NVIC      = SCS +  0x0100UL;
        constexpr uint32_t SCB       = SCS +  0x0D00UL;
    }

    namespace NVIC {
        struct TypeDef {
            volatile uint32_t ISER[8U];               /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
            uint32_t RESERVED0[24U];
            volatile uint32_t ICER[8U];               /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
            uint32_t RSERVED1[24U];
            volatile uint32_t ISPR[8U];               /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
            uint32_t RESERVED2[24U];
            volatile uint32_t ICPR[8U];               /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
            uint32_t RESERVED3[24U];
            volatile uint32_t IABR[8U];               /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register */
            uint32_t RESERVED4[56U];
            volatile uint8_t  IP[240U];               /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
            uint32_t RESERVED5[644U];
            volatile  uint32_t STIR;                  /*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register */
        };
    }

    namespace SCB {
        struct TypeDef {
            volatile const  uint32_t CPUID;                  /*!< Offset: 0x000 (R/ )  CPUID Base Register */
            volatile uint32_t ICSR;                          /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
            volatile uint32_t VTOR;                          /*!< Offset: 0x008 (R/W)  Vector Table Offset Register */
            volatile uint32_t AIRCR;                         /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
            volatile uint32_t SCR;                           /*!< Offset: 0x010 (R/W)  System Control Register */
            volatile uint32_t CCR;                           /*!< Offset: 0x014 (R/W)  Configuration Control Register */
            volatile uint8_t  SHP[12U];                      /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
            volatile uint32_t SHCSR;                         /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
            volatile uint32_t CFSR;                          /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register */
            volatile uint32_t HFSR;                          /*!< Offset: 0x02C (R/W)  HardFault Status Register */
            volatile uint32_t DFSR;                          /*!< Offset: 0x030 (R/W)  Debug Fault Status Register */
            volatile uint32_t MMFAR;                         /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register */
            volatile uint32_t BFAR;                          /*!< Offset: 0x038 (R/W)  BusFault Address Register */
            volatile uint32_t AFSR;                          /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register */
            volatile const  uint32_t PFR[2U];                /*!< Offset: 0x040 (R/ )  Processor Feature Register */
            volatile const  uint32_t DFR;                    /*!< Offset: 0x048 (R/ )  Debug Feature Register */
            volatile const  uint32_t ADR;                    /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register */
            volatile const  uint32_t MMFR[4U];               /*!< Offset: 0x050 (R/ )  Memory Model Feature Register */
            volatile const  uint32_t ISAR[5U];               /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register */
            uint32_t RESERVED0[5U];
            volatile uint32_t CPACR;                         /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register */
        };

        namespace CPUID {
            
        }

        namespace AIRSR {
            constexpr uint32_t Pos_VECTKEY       = 16U;
            constexpr uint32_t Pos_VECTKEYSTAT   = 16U;
            constexpr uint32_t Pos_ENDIANESS     = 15U;
            constexpr uint32_t Pos_PRIGROUP      =  8U;
            constexpr uint32_t Pos_SYSRESETREQ   =  2U;
            constexpr uint32_t Pos_VECTCLRACTIVE =  1U;
            constexpr uint32_t Pos_VECTRESET     =  0U;

            enum class Msk: uint32_t {
                __Pos_to_Msk(0xFFFFUL, VECTKEY       ),
                __Pos_to_Msk(0xFFFFUL, VECTKEYSTAT   ),
                __Pos_to_Msk(     1UL, ENDIANESS     ),
                __Pos_to_Msk(     1UL, PRIGROUP      ),
                __Pos_to_Msk(     1UL, SYSRESETREQ   ),
                __Pos_to_Msk(     1UL, VECTCLRACTIVE ),
                __Pos_to_Msk(     1UL, VECTRESET     ),
            };
        }
    }
}

namespace stm32f103xb {
    enum class IRQn: int32_t {
        /******  Cortex-M3 Processor Exceptions Numbers ***************************************************/
        NonMaskableInt         = -14,    /*!< 2 Non Maskable Interrupt                             */
        HardFault              = -13,    /*!< 3 Cortex-M3 Hard Fault Interrupt                     */
        MemoryManagement       = -12,    /*!< 4 Cortex-M3 Memory Management Interrupt              */
        BusFault               = -11,    /*!< 5 Cortex-M3 Bus Fault Interrupt                      */
        UsageFault             = -10,    /*!< 6 Cortex-M3 Usage Fault Interrupt                    */
        SVCall                 = -5,     /*!< 11 Cortex-M3 SV Call Interrupt                       */
        DebugMonitor           = -4,     /*!< 12 Cortex-M3 Debug Monitor Interrupt                 */
        PendSV                 = -2,     /*!< 14 Cortex-M3 Pend SV Interrupt                       */
        SysTick                = -1,     /*!< 15 Cortex-M3 System Tick Interrupt                   */

        /******  STM32 specific Interrupt Numbers *********************************************************/
        WWDG                   = 0,      /*!< Window WatchDog Interrupt                            */
        PVD                    = 1,      /*!< PVD through EXTI Line detection Interrupt            */
        TAMPER                 = 2,      /*!< Tamper Interrupt                                     */
        RTC                    = 3,      /*!< RTC global Interrupt                                 */
        FLASH                  = 4,      /*!< FLASH global Interrupt                               */
        RCC                    = 5,      /*!< RCC global Interrupt                                 */
        EXTI0                  = 6,      /*!< EXTI Line0 Interrupt                                 */
        EXTI1                  = 7,      /*!< EXTI Line1 Interrupt                                 */
        EXTI2                  = 8,      /*!< EXTI Line2 Interrupt                                 */
        EXTI3                  = 9,      /*!< EXTI Line3 Interrupt                                 */
        EXTI4                  = 10,     /*!< EXTI Line4 Interrupt                                 */
        DMA1_Channel1          = 11,     /*!< DMA1 Channel 1 global Interrupt                      */
        DMA1_Channel2          = 12,     /*!< DMA1 Channel 2 global Interrupt                      */
        DMA1_Channel3          = 13,     /*!< DMA1 Channel 3 global Interrupt                      */
        DMA1_Channel4          = 14,     /*!< DMA1 Channel 4 global Interrupt                      */
        DMA1_Channel5          = 15,     /*!< DMA1 Channel 5 global Interrupt                      */
        DMA1_Channel6          = 16,     /*!< DMA1 Channel 6 global Interrupt                      */
        DMA1_Channel7          = 17,     /*!< DMA1 Channel 7 global Interrupt                      */
        ADC1_2                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
        USB_HP_CAN1_TX         = 19,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
        USB_LP_CAN1_RX0        = 20,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
        CAN1_RX1               = 21,     /*!< CAN1 RX1 Interrupt                                   */
        CAN1_SCE               = 22,     /*!< CAN1 SCE Interrupt                                   */
        EXTI9_5                = 23,     /*!< External Line[9:5] Interrupts                        */
        TIM1_BRK               = 24,     /*!< TIM1 Break Interrupt                                 */
        TIM1_UP                = 25,     /*!< TIM1 Update Interrupt                                */
        TIM1_TRG_COM           = 26,     /*!< TIM1 Trigger and Commutation Interrupt               */
        TIM1_CC                = 27,     /*!< TIM1 Capture Compare Interrupt                       */
        TIM2                   = 28,     /*!< TIM2 global Interrupt                                */
        TIM3                   = 29,     /*!< TIM3 global Interrupt                                */
        TIM4                   = 30,     /*!< TIM4 global Interrupt                                */
        I2C1_EV                = 31,     /*!< I2C1 Event Interrupt                                 */
        I2C1_ER                = 32,     /*!< I2C1 Error Interrupt                                 */
        I2C2_EV                = 33,     /*!< I2C2 Event Interrupt                                 */
        I2C2_ER                = 34,     /*!< I2C2 Error Interrupt                                 */
        SPI1                   = 35,     /*!< SPI1 global Interrupt                                */
        SPI2                   = 36,     /*!< SPI2 global Interrupt                                */
        USART1                 = 37,     /*!< USART1 global Interrupt                              */
        USART2                 = 38,     /*!< USART2 global Interrupt                              */
        USART3                 = 39,     /*!< USART3 global Interrupt                              */
        EXTI15_10              = 40,     /*!< External Line[15:10] Interrupts                      */
        RTC_Alarm              = 41,     /*!< RTC Alarm through EXTI Line Interrupt                */
        USBWakeUp              = 42,     /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */
    };

    namespace BASE {
        constexpr uint32_t FLASH           = 0x08000000UL;
        constexpr uint32_t FLASH_BANK1_END = 0x0801FFFFUL;
        constexpr uint32_t SRAM            = 0x20000000UL;
        constexpr uint32_t PERIPH          = 0x40000000UL;

        constexpr uint32_t SRAM_BB    = 0x22000000UL;
        constexpr uint32_t PERIPH_BB  = 0x42000000UL;

        constexpr uint32_t APB1PERIPH = PERIPH;
        constexpr uint32_t APB2PERIPH = PERIPH + 0x00010000UL;
        constexpr uint32_t AHBPERIPH  = PERIPH + 0x00020000UL;

        constexpr uint32_t TIM2   = (APB1PERIPH + 0x00000000UL);
        constexpr uint32_t TIM3   = (APB1PERIPH + 0x00000400UL);
        constexpr uint32_t TIM4   = (APB1PERIPH + 0x00000800UL);
        constexpr uint32_t RTC    = (APB1PERIPH + 0x00002800UL);
        constexpr uint32_t WWDG   = (APB1PERIPH + 0x00002C00UL);
        constexpr uint32_t IWDG   = (APB1PERIPH + 0x00003000UL);
        constexpr uint32_t SPI2   = (APB1PERIPH + 0x00003800UL);
        constexpr uint32_t USART2 = (APB1PERIPH + 0x00004400UL);
        constexpr uint32_t USART3 = (APB1PERIPH + 0x00004800UL);
        constexpr uint32_t I2C1   = (APB1PERIPH + 0x00005400UL);
        constexpr uint32_t I2C2   = (APB1PERIPH + 0x00005800UL);
        constexpr uint32_t CAN1   = (APB1PERIPH + 0x00006400UL);
        constexpr uint32_t BKP    = (APB1PERIPH + 0x00006C00UL);
        constexpr uint32_t PWR    = (APB1PERIPH + 0x00007000UL);

        constexpr uint32_t AFIO   = (APB2PERIPH + 0x00000000UL);
        constexpr uint32_t EXTI   = (APB2PERIPH + 0x00000400UL);
        constexpr uint32_t GPIOA  = (APB2PERIPH + 0x00000800UL);
        constexpr uint32_t GPIOB  = (APB2PERIPH + 0x00000C00UL);
        constexpr uint32_t GPIOC  = (APB2PERIPH + 0x00001000UL);
        constexpr uint32_t GPIOD  = (APB2PERIPH + 0x00001400UL);
        constexpr uint32_t GPIOE  = (APB2PERIPH + 0x00001800UL);
        constexpr uint32_t ADC1   = (APB2PERIPH + 0x00002400UL);
        constexpr uint32_t ADC2   = (APB2PERIPH + 0x00002800UL);
        constexpr uint32_t TIM1   = (APB2PERIPH + 0x00002C00UL);
        constexpr uint32_t SPI1   = (APB2PERIPH + 0x00003000UL);
        constexpr uint32_t USART1 = (APB2PERIPH + 0x00003800UL);

        constexpr uint32_t DMA1          = (AHBPERIPH + 0x00000000UL);
        constexpr uint32_t DMA1_Channel1 = (AHBPERIPH + 0x00000008UL);
        constexpr uint32_t DMA1_Channel2 = (AHBPERIPH + 0x0000001CUL);
        constexpr uint32_t DMA1_Channel3 = (AHBPERIPH + 0x00000030UL);
        constexpr uint32_t DMA1_Channel4 = (AHBPERIPH + 0x00000044UL);
        constexpr uint32_t DMA1_Channel5 = (AHBPERIPH + 0x00000058UL);
        constexpr uint32_t DMA1_Channel6 = (AHBPERIPH + 0x0000006CUL);
        constexpr uint32_t DMA1_Channel7 = (AHBPERIPH + 0x00000080UL);
        constexpr uint32_t RCC           = (AHBPERIPH + 0x00001000UL);
        constexpr uint32_t CRC           = (AHBPERIPH + 0x00003000UL);

        constexpr uint32_t FLASH_R   = (AHBPERIPH + 0x00002000UL);
        constexpr uint32_t FLASHSIZE = 0x1FFFF7E0UL;
        constexpr uint32_t UID       = 0x1FFFF7E8UL;
        constexpr uint32_t OB        = 0x1FFFF800UL;

        constexpr uint32_t DBGMCU = 0xE0042000UL;

        constexpr uint32_t USB         = (APB1PERIPH + 0x00005C00UL);
        constexpr uint32_t USB_PMAADDR = (APB1PERIPH + 0x00006000UL);
    }

    namespace RCC {
        struct TypeDef {
            volatile uint32_t CR;
            volatile uint32_t CFGR;
            volatile uint32_t CIR;
            volatile uint32_t APB2RSTR;
            volatile uint32_t APB1RSTR;
            volatile uint32_t AHBENR;
            volatile uint32_t APB2ENR;
            volatile uint32_t APB1ENR;
            volatile uint32_t BDCR;
            volatile uint32_t CSR;
        };

        namespace AHBENR {
            constexpr uint32_t Pos_DMA1  = 0U;
            constexpr uint32_t Pos_SRAM  = 2U;
            constexpr uint32_t Pos_FLITF = 4U;
            constexpr uint32_t Pos_CRC   = 6U;
            enum class Msk {
                __Pos_to_Msk(0x1UL, DMA1),
                __Pos_to_Msk(0x1UL, SRAM),
                __Pos_to_Msk(0x1UL, FLITF),
                __Pos_to_Msk(0x1UL, CRC),
            };
        }

        namespace APB2ENR {
            constexpr uint32_t Pos_AFIO   =  0U;
            constexpr uint32_t Pos_IOPA   =  2U;
            constexpr uint32_t Pos_IOPB   =  3U;
            constexpr uint32_t Pos_IOPC   =  4U;
            constexpr uint32_t Pos_IOPD   =  5U;
            constexpr uint32_t Pos_IOPE   =  6U;
            constexpr uint32_t Pos_ADC1   =  9U;
            constexpr uint32_t Pos_ADC2   = 10U;
            constexpr uint32_t Pos_TIM1   = 11U;
            constexpr uint32_t Pos_SPI1   = 12U;
            constexpr uint32_t Pos_USART1 = 14U;

            enum class Msk {
                __Pos_to_Msk(0x1UL, AFIO),
                __Pos_to_Msk(0x1UL, IOPA),
                __Pos_to_Msk(0x1UL, IOPB),
                __Pos_to_Msk(0x1UL, IOPC),
                __Pos_to_Msk(0x1UL, IOPD),
                __Pos_to_Msk(0x1UL, IOPE),
                __Pos_to_Msk(0x1UL, ADC1),
                __Pos_to_Msk(0x1UL, ADC2),
                __Pos_to_Msk(0x1UL, TIM1),
                __Pos_to_Msk(0x1UL, SPI1),
                __Pos_to_Msk(0x1UL, USART1),
            };
        }

        namespace APB1ENR {
            constexpr uint32_t Pos_TIM2   =  0U;
            constexpr uint32_t Pos_TIM3   =  1U;
            constexpr uint32_t Pos_TIM4   =  2U;
            constexpr uint32_t Pos_WWDG   = 11U;
            constexpr uint32_t Pos_USART2 = 17U;
            constexpr uint32_t Pos_USART3 = 18U;
            constexpr uint32_t Pos_I2C1   = 21U;
            constexpr uint32_t Pos_I2C2   = 22U;
            constexpr uint32_t Pos_CAN1   = 25U;
            constexpr uint32_t Pos_BKP    = 27U;
            constexpr uint32_t Pos_PWR    = 28U;
            constexpr uint32_t Pos_SPI2   = 14U;
            constexpr uint32_t Pos_USB    = 23U;

            enum class Msk {
                __Pos_to_Msk(0x1UL, TIM2  ),
                __Pos_to_Msk(0x1UL, TIM3  ),
                __Pos_to_Msk(0x1UL, TIM4  ),
                __Pos_to_Msk(0x1UL, WWDG  ),
                __Pos_to_Msk(0x1UL, USART2),
                __Pos_to_Msk(0x1UL, USART3),
                __Pos_to_Msk(0x1UL, I2C1  ),
                __Pos_to_Msk(0x1UL, I2C2  ),
                __Pos_to_Msk(0x1UL, CAN1  ),
                __Pos_to_Msk(0x1UL, BKP   ),
                __Pos_to_Msk(0x1UL, PWR   ),
                __Pos_to_Msk(0x1UL, SPI2  ),
                __Pos_to_Msk(0x1UL, USB   ),
            };
        }
    }
}

#undef __Pos_to_Msk

#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))