set_config("plat", "cortex-m3")
set_config("arch", "thumbv7")

set_config("cross", "arm-none-eabi-")
set_config("target_os", "none")
set_config("sdk", "$(env GCC_ARM_NONE_EABI_ROOT)")

set_languages("c99", "cxx17")
set_targetdir("$(buildir)")

target("hal") do
    set_kind("static")
    on_load(function(target)
        import("stm32f103c8t6").config(target)
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
        import("stm32f103c8t6").config(target)
    end)

    add_includedirs("./inc")
    add_files("./example/blinky.cc")

    after_build(function(target)
        import("core.base.task").run("project", { kind="compile_commands" })
        os.exec("arm-none-eabi-size %s", target:targetfile())
        local bin = path.join(target:targetdir(), target:basename() .. ".bin")
        os.run(
            "arm-none-eabi-objcopy %s %s -O binary",
            target:targetfile(),
            bin
        )
        print("The size of bin is " .. os.filesize(bin) .." bytes")
    end)

    on_install(function(target)
        local bin = path.join(target:targetdir(), target:basename() .. ".bin")
        os.exec("st-info --probe")
        os.exec("st-flash write %s 0x08000000", bin)
    end)
end