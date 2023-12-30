
function config(target, opt)
    local opt = opt or {}

    local kind      = opt.kind      or "binary"
    local use_CMSIS = opt.use_CMSIS or false

    local optimize = opt.optimize or "-Og"
    local warnings = opt.warnings or "-Wall"

    local cpu      = "-mcpu=cortex-m3"
    local instruct = "-mthumb"
    target:add("cxflags",
        cpu, instruct, warnings, optimize,
        "-fdata-sections", "-ffunction-sections", "-U__VFP_FP__",
        { force = true }
    )

    if use_CMSIS then
        local CMSIS = opt.CMSIS or "./CMSIS"
        target:add("includedirs",
            path.join(CMSIS, "Core"),
            path.join(CMSIS, "Device")
        )
        target:add("defines",
            "STM32F1",
            "STM32F103xB"
        )
    end

    if kind == "binary"  then
        local ldscript = opt.ldscript or "./STM32F103C8T6_FLASH.ld"
        target:add("ldflags",
            cpu, instruct, "-T" .. ldscript,
            -- "-nostdlib",
            "-specs=nano.specs", "-lc", "-lm", "-lnosys", "-Wl,--gc-sections",
            { force = true }
        )

        local startup  = opt.startup  or "./startup_stm32f103c8t6.s"
        target:add("asflags",
            cpu, instruct, warnings, optimize,
            "-fdata-sections", "-ffunction-sections",
            { force = true }
        )
        target:add("files",
            startup, { rule = "asm.build" }
        )
    end
end