
function config(target, opt)
    local opt      = opt or {}
    local optimize = opt.optimize or "-Og"
    local warnings = opt.warnings or "-Wall"
    local ldscript = opt.ldscript or "./STM32F103C8T6_FLASH.ld"
    local startup  = opt.startup  or "./startup_stm32f103c8t6.s"
    local CMSIS    = opt.CMSIS    or "./CMSIS"

    local cpu      = "-mcpu=cortex-m3"
    local instruct = "-mthumb"

    target:add("asflags",
        cpu, instruct, warnings, optimize,
        "-fdata-sections", "-ffunction-sections",
        { force = true }
    )

    target:add("cxflags",
        cpu, instruct, warnings, optimize,
        "-fdata-sections", "-ffunction-sections",
        { force = true }
    )

    target:add("ldflags",
        cpu, instruct, "-T" .. ldscript,
        "-specs=nano.specs", "-lc", "-lm", "-lnosys", "-Wl,--gc-sections",
        { force = true }
    )

    target:add("includedirs",
        path.join(CMSIS, "Core"),
        path.join(CMSIS, "Device")
    )
    target:add("defines",
        "STM32F1",
        "STM32F103xB"
    )
    target:add("files",
        startup, { rule = "asm.build" }
    )
end