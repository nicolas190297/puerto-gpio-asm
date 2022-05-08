/**
 * @file main.c
 * @author Fernando A. Miranda Bonomi (fmirandabonomi@herrera.unt.edu.ar)
 * @brief Esqueleto de aplicación con una función de configuración y un lazo infinito.
 */
#include <timer_systick.h>
#include <parpadeo.h>
#include <pin_gpio.h>
#include <stm32f1xx.h>

static Pin pinLed;
int main(void)
{
    __disable_irq();
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    __enable_irq();
    Pin_init(&pinLed,GPIOC,13);
    Parpadeo_init(&pinLed);
    for(;;)Parpadeo_actualiza();
    return 0;
}
