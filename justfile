convert:
    arm-none-eabi-gcc -S -std=c++17 -Iinc -ICMSIS/Core -ICMSIS/Device -DSTM32F1 -DSTM32F103xB -mcpu=cortex-m3 -mthumb -Wall -Og -fdata-sections -ffunction-sections -U__VFP_FP__ ./example/blinky.cc