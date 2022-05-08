// Cortex-M3 Devices Generic User Guide: https://developer.arm.com/documentation/dui0552/
// STM32f103xx Family Reference Manual: https://www.st.com/resource/en/reference_manual/cd00171190-stm32f101xx-stm32f102xx-stm32f103xx-stm32f105xx-and-stm32f107xx-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf
// STM32f103c8 Datasheet: https://www.st.com/resource/en/datasheet/stm32f103c8.pdf
// Procedure Call Standard for the Arm Architecture: https://github.com/ARM-software/abi-aa/blob/main/aapcs32/aapcs32.rst
.syntax unified
.cpu cortex-m3
.fpu softvfp
.thumb

.macro defun nombre
    .section .text.\nombre
    .global \nombre
    .type \nombre, %function
\nombre:
.endm
.macro endfun nombre
    .size \nombre, . - \nombre
.endm

.data
pinPtr: .space 4 

.set PG_SALIDA_LENTA, 0b010

defun Parpadeo_init
    push {R4,lr}
    ldr R1,=pinPtr
    str R0,[R1]
    movs R4,R0
    movs R1,#1
    bl Pin_escribe
    movs R0,R4
    movs R1,PG_SALIDA_LENTA
    bl Pin_configura
    bl TimerSysTick_init
    pop {R4,pc}
endfun Parpadeo_init

defun Parpadeo_actualiza
    push {R4,lr}
    movs R0,#500
    bl TimerSysTick_esperaMilisegundos
    ldr R0,=pinPtr
    ldr R0,[R0]
    movs R4,R0
    bl Pin_leeSalida
    eors R1,R0,#1
    movs R0,R4
    bl Pin_escribe
    pop {R4,pc}
endfun Parpadeo_actualiza