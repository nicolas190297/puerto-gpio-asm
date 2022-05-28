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

.set Pin__puerto,0
.set Pin__numero,4

defun Pin_init
    // R0: self, R1: puerto, R2: numPin
    str R1,[R0,#Pin__puerto] //guardo R1 en la estructura R0 con el offset
    str R2,[R0,#Pin__numero] 
    bx lr
endfun Pin_init

.set CRL,0x00
.set CRH,0x04
.set IDR,0x08
.set ODR,0x0C
.set BSRR,0x10
.set BRR,0x14
.set MASCARA_BITS_CONFIG, 0xF
.set CNF_PULL_UP_O_DN, 0x08

defun Pin_configura
    // R0: self, R1: config
    push {R4-R7,LR}
    ldr R2,[R0,#Pin__puerto] 
    ldr R3,[R0,#Pin__numero] //R3 es el valor guardado en la direccion de memoria
    cmp R3,#8
    bhs 0f
    movs R6,#CRL
    b 1f

0:
    movs R6,#CRH
    subs R3,#8
1:

    ldr R4,[R2,R6]
    movs R5,#MASCARA_BITS_CONFIG //cargo en R5 la mascara con 1
    lsls R3,#2 //moverlo 2 a la izquierda q es multiplicarlo por 4 
    lsls R5,R3
    bics R4,R5
    movs R12,R1 
    ands R1,#MASCARA_BITS_CONFIG //selecciono
    lsls R1,R3  //desplazo
    orrs R4,R1 //pongo en su posiscion los bits de R1
    str R4,[R2,R6]
    mov R1,R12 //restauro
    ands R4,R1,#MASCARA_BITS_CONFIG
    cmp R4,#CNF_PULL_UP_O_DN
    bne 0f
    ubfx R1,R1,#4,#1 //extrae el 1 q esta en el pin 5 y pone en 0 el resto de los pines
    bl Pin_escribe
0:                  //si no es config pull up o pull down directamente salgo
    pop {R4-R7,PC}

endfun Pin_configura



defun Pin_escribe
    // R0: self, R1: valor
    //recupero puerto y pin
    ldr R2,[R0,#Pin__puerto] 
    ldr R3,[R0,#Pin__numero]
    movs R0,#1
    lsls R0,R3
    cmp R1,#0
    bne 0f
    str R0,[R2,#BRR]
    b 1f
0:
    str R0,[R2,#BSRR]
1:
    bx lr
endfun Pin_escribe

defun Pin_lee
    // R0: self
    ldr R1,[R0,#Pin__puerto] 
    ldr R2,[R0,#Pin__numero]
    lsrs R0,R2
    ands R0,#1
    bx lr
    // R0: valor
endfun Pin_lee
defun Pin_leeSalida
    // R0: self
    ldr R1,[R0,#Pin__puerto] 
    ldr R2,[R0,#Pin__numero]
    ldr R0,[R1,#ODR]
    ands R0,R2
    ands R0,#1
    bx lr
    // R0: valor
endfun Pin_leeSalida
