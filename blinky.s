	.cpu cortex-m3
	.arch armv7-m
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 1
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"blinky.cc"
	.text
	.section	.text.NMI_Handler,"ax",%progbits
	.align	1
	.global	NMI_Handler
	.syntax unified
	.thumb
	.thumb_func
	.type	NMI_Handler, %function
NMI_Handler:
	.fnstart
.LFB0:
	@ Volatile: function does not return.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
.L2:
	b	.L2
	.cantunwind
	.fnend
	.size	NMI_Handler, .-NMI_Handler
	.section	.text.HardFault_Handler,"ax",%progbits
	.align	1
	.global	HardFault_Handler
	.syntax unified
	.thumb
	.thumb_func
	.type	HardFault_Handler, %function
HardFault_Handler:
	.fnstart
.LFB1:
	@ Volatile: function does not return.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
.L4:
	b	.L4
	.cantunwind
	.fnend
	.size	HardFault_Handler, .-HardFault_Handler
	.section	.text.MemManage_Handler,"ax",%progbits
	.align	1
	.global	MemManage_Handler
	.syntax unified
	.thumb
	.thumb_func
	.type	MemManage_Handler, %function
MemManage_Handler:
	.fnstart
.LFB2:
	@ Volatile: function does not return.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
.L6:
	b	.L6
	.cantunwind
	.fnend
	.size	MemManage_Handler, .-MemManage_Handler
	.section	.text.BusFault_Handler,"ax",%progbits
	.align	1
	.global	BusFault_Handler
	.syntax unified
	.thumb
	.thumb_func
	.type	BusFault_Handler, %function
BusFault_Handler:
	.fnstart
.LFB3:
	@ Volatile: function does not return.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
.L8:
	b	.L8
	.cantunwind
	.fnend
	.size	BusFault_Handler, .-BusFault_Handler
	.section	.text.UsageFault_Handler,"ax",%progbits
	.align	1
	.global	UsageFault_Handler
	.syntax unified
	.thumb
	.thumb_func
	.type	UsageFault_Handler, %function
UsageFault_Handler:
	.fnstart
.LFB4:
	@ Volatile: function does not return.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
.L10:
	b	.L10
	.cantunwind
	.fnend
	.size	UsageFault_Handler, .-UsageFault_Handler
	.section	.text.SVC_Handler,"ax",%progbits
	.align	1
	.global	SVC_Handler
	.syntax unified
	.thumb
	.thumb_func
	.type	SVC_Handler, %function
SVC_Handler:
	.fnstart
.LFB5:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	bx	lr
	.cantunwind
	.fnend
	.size	SVC_Handler, .-SVC_Handler
	.section	.text.DebugMon_Handler,"ax",%progbits
	.align	1
	.global	DebugMon_Handler
	.syntax unified
	.thumb
	.thumb_func
	.type	DebugMon_Handler, %function
DebugMon_Handler:
	.fnstart
.LFB6:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	bx	lr
	.cantunwind
	.fnend
	.size	DebugMon_Handler, .-DebugMon_Handler
	.section	.text.PendSV_Handler,"ax",%progbits
	.align	1
	.global	PendSV_Handler
	.syntax unified
	.thumb
	.thumb_func
	.type	PendSV_Handler, %function
PendSV_Handler:
	.fnstart
.LFB7:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	bx	lr
	.cantunwind
	.fnend
	.size	PendSV_Handler, .-PendSV_Handler
	.section	.text.SysTick_Handler,"ax",%progbits
	.align	1
	.global	SysTick_Handler
	.syntax unified
	.thumb
	.thumb_func
	.type	SysTick_Handler, %function
SysTick_Handler:
	.fnstart
.LFB8:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	bx	lr
	.cantunwind
	.fnend
	.size	SysTick_Handler, .-SysTick_Handler
	.section	.text.main,"ax",%progbits
	.align	1
	.global	main
	.syntax unified
	.thumb
	.thumb_func
	.type	main, %function
main:
	.fnstart
.LFB75:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	sub	sp, sp, #8
	ldr	r3, .L17
	ldr	r2, [r3, #28]
	orr	r2, r2, #268435456
	str	r2, [r3, #28]
	ldr	r3, [r3, #28]
	and	r3, r3, #268435456
	str	r3, [sp, #4]
	ldr	r3, [sp, #4]
	movs	r0, #0
	add	sp, sp, #8
	@ sp needed
	bx	lr
.L18:
	.align	2
.L17:
	.word	1073876992
	.cantunwind
	.fnend
	.size	main, .-main
	.ident	"GCC: (Arm GNU Toolchain 13.2.rel1 (Build arm-13.7)) 13.2.1 20231009"
