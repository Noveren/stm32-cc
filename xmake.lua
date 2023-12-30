set_config("plat", "cortex-m3")
set_config("arch", "thumbv7")

set_config("cross", "arm-none-eabi-")
set_config("target_os", "none")
set_config("sdk", "$(env GCC_ARM_NONE_EABI_ROOT)")

set_languages("c99", "cxx17")
set_targetdir("$(buildir)")

after_build(function(target)
    -- import("core.base.task").run("project", { kind="compile_commands" })
    if target:kind() == "binary" then
        os.exec("arm-none-eabi-size %s", target:targetfile())
        local bin = path.join(target:targetdir(), target:basename() .. ".bin")
        os.run(
            "arm-none-eabi-objcopy %s %s -O binary",
            target:targetfile(),
            bin
        )
        print("The size of bin is " .. os.filesize(bin) .." bytes")
    end
end)

on_install(function(target)
    if target:kind() == "binary" then
        local bin = path.join(target:targetdir(), target:basename() .. ".bin")
        os.exec("st-info --probe")
        os.exec("st-flash write %s 0x08000000", bin)
    end
end)

target("hal") do
    set_kind("static")
    on_load(function(target)
        import("stm32f103c8t6").config(target, {
            kind = "library",
            use_CMSIS = true,
        })
    end)

    add_defines(
        "HSE_VALUE=8000000",
        "HSI_VALUE=8000000",
        "LSE_VALUE=32768",
        "LSI_VALUE=40000"
    )

    add_files(
        "./src/system_stm32f1xx.c"
    )
end

target("blinky") do
    set_extension(".elf")
    add_deps("hal")

    on_load(function(target)
        import("stm32f103c8t6").config(target, {
            use_CMSIS = true
        })
    end)

    add_includedirs("./inc")
    add_files("./example/blinky.cc")
end

target("blinky-ll") do
    set_extension(".elf")
    on_load(function(target)
        import("stm32f103c8t6").config(target, {
            use_CMSIS = true
        })
    end)

    add_defines(
        "HSE_VALUE=8000000",
        "HSI_VALUE=8000000",
        "LSE_VALUE=32768",
        "LSI_VALUE=40000",
        "HSE_STARTUP_TIMEOUT=100",
        "LSE_STARTUP_TIMEOUT=100",
        "VDD_VALUE=3300",
        "PREFETCH_ENABLE=1",
        "USE_FULL_LL_DRIVER"
    )

    add_includedirs("./STM32F1xx_LL/inc")
    add_files(
        "./example/blinky.c",
        "./src/system_stm32f1xx.c",
        "./STM32F1xx_LL/src/stm32f1xx_ll_gpio.c",
        "./STM32F1xx_LL/src/stm32f1xx_ll_utils.c",
        "./STM32F1xx_LL/src/stm32f1xx_ll_rcc.c",
        "./STM32F1xx_LL/src/stm32f1xx_ll_pwr.c",
        "./STM32F1xx_LL/src/stm32f1xx_ll_exti.c"
    )
end

rule("assembly") do
    set_extensions(".c", ".cc")
    
    on_build_file(function(target, sourcefile, opt)
        -- TODO 支持语言标准设置
        print(format("Convert to Assembly: %s", sourcefile))
        local object_directory = path.directory(target:objectfile(sourcefile))
        if not os.exists(object_directory) then
            os.mkdir(object_directory)
        end
        local template = format(
            "arm-none-eabi-gcc -S -fverbose-asm %s -o %s %s %s %s",
            sourcefile,
            path.join(object_directory, path.filename(sourcefile) .. ".s"),
            table.concat(target:get("cxflags"), ' '),
            "-I" .. table.concat(target:get("includedirs"), " -I"),
            "-D" .. table.concat(target:get("defines"), " -D")
        )
        -- print(template)
        os.run(template)
    end)
end

target("assembly") do
    set_kind("object")
    add_rules("assembly")
    on_load(function(target)
        import("stm32f103c8t6").config(target, {
            kind = "library",
            use_CMSIS = true
        })
    end)
    add_defines(
        "HSE_VALUE=8000000",
        "HSI_VALUE=8000000",
        "LSE_VALUE=32768",
        "LSI_VALUE=40000",
        "HSE_STARTUP_TIMEOUT=100",
        "LSE_STARTUP_TIMEOUT=100",
        "VDD_VALUE=3300",
        "PREFETCH_ENABLE=1",
        "USE_FULL_LL_DRIVER"
    )
    add_includedirs(
        "./inc",
        "./STM32F1xx_LL/inc"
    )
    add_files(
        "./example/blinky.cc",
        "./example/blinky.c",
        "./src/system_stm32f1xx.c"
    )
end