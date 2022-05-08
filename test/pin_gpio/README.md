# Módulo PinGpio

Configura y controla un pin en un puerto GPIO.

## PinGpio_init

Inicializa una instancia de PinGpio, define el pin a controlar.

```C
void PinGpio_init(PinGpio *self, GPIO_TypeDef * puerto, int pin);
```

- self: Instancia de PinGpio (variable que contiene el estado necesario para operar sobre un pin)
- puerto: Puerto GPIO
- pin: Pin a utilizar, 0..15

## PinGpio_config

Configura un pin como entrada, salida o función alterna

```C
void PinGpio_config(PinGpio *self, ModoPin modo);
```

- self: Instancia de PinGpio inicializada anteriormente por `PinGpio_init`
- modo: Modo de operación. (Ver Tablas 20 y 21 [STM32f103xx Family Reference Manual](https://www.st.com/resource/en/reference_manual/cd00171190-stm32f101xx-stm32f102xx-stm32f103xx-stm32f105xx-and-stm32f107xx-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf))
    - PG_SALIDA_RAPIDA
    - PG_SALIDA_RAPIDA_DRENADOR_ABIERTO
    - PG_SALIDA_MEDIA
    - PG_SALIDA_MEDIA_DRENADOR_ABIERTO
    - PG_SALIDA_LENTA
    - PG_SALIDA_LENTA_DRENADOR_ABIERTO
    - PG_FUNCION_ALTERNATIVA_RAPIDA
    - PG_FN_ALT_RAPIDA_DRENADOR_ABIERTO
    - PG_FN_ALT_MEDIA
    - PG_FN_ALT_MEDIA_DRENADOR_ABIERTO
    - PG_FN_ALT_LENTA
    - PG_FN_ALT_LENTA_DRENADOR_ABIERTO
    - PG_ENTRADA_ANALOGICA
    - PG_ENTRADA_FLOTANTE
    - PG_ENTRADA_PULL_UP
    - PG_ENTRADA_PULL_DOWN

## PinGpio_lee

Lee el valor del pin en el registro de entrada

```c
bool PinGpio_lee(PinGpio *self);
```

Retorna
- false (0): Estado lógico bajo
- true (1): Estado lógico alto 

## PinGpio_escribe

Escribe el registro de salida con el valor especificado. Emplea el mecanismo de set/reset atómico.
```c
void PinGpio_escribe(PinGpio *self, bool estado);
```

Valor
- false (0): Estado lógico bajo
- true (1): Estado lógico alto 

