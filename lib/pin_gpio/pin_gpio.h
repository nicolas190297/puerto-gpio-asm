#ifndef PIN_GPIO
#define PIN_GPIO
#include <stm32f1xx.h>
#include <stdbool.h>
    typedef struct Pin
    {
        GPIO_TypeDef *puerto;
        int numero;
    }Pin;

    typedef enum ConfigPin {
        PIN_ANALOGICO = 0U,
        PIN_ENTRADA = 0b100U,
        PIN_ENTRADA_PULL_DOWN = 0b1000U,
        PIN_ENTRADA_PULL_UP = PIN_ENTRADA_PULL_DOWN | 0x10U,
        PIN_SALIDA_LENTO = 0b10U,
        PIN_SALIDA_MEDIO = 0b01U,
        PIN_SALIDA_RAPIDO = 0b11U,
        PIN_SALIDA_LENTO_OD = PIN_SALIDA_LENTO | 0b100,
        PIN_SALIDA_MEDIO_OD = PIN_SALIDA_MEDIO    | 0b100,
        PIN_SALIDA_RAPIDO_OD = PIN_SALIDA_RAPIDO  | 0b100,
    } ConfigPin;
    void Pin_init(Pin *self, GPIO_TypeDef *puerto, int numPin);
    void Pin_configura(Pin *self,ConfigPin modo);
    void Pin_escribe(Pin *self, bool valor);
    bool Pin_lee(Pin *self);
    bool Pin_leeSalida(Pin *self);

#endif
