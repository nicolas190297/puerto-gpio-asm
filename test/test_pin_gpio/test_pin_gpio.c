#include <unity.h>
#include <timer_systick.h>
#include <pin_gpio.h>

GPIO_TypeDef miPuerto;
static Pin miPinH;
static Pin miPinL;
enum MisConstantes{NUM_PIN_H=13,NUM_PIN_L=5};

void setUp(void)
{
    miPuerto = (GPIO_TypeDef){0};
    Pin_init(&miPinL,&miPuerto,NUM_PIN_L);
    Pin_init(&miPinH,&miPuerto,NUM_PIN_H);
}

static void configura_analogico(void)
{
    miPuerto.CRL = ~0UL;
    miPuerto.CRH = miPuerto.CRL;
    Pin_configura(&miPinL,PIN_ANALOGICO);
    TEST_ASSERT_EQUAL_HEX32(~(0xFUL<<(NUM_PIN_L*4)),miPuerto.CRL);
    TEST_ASSERT_EQUAL_HEX32(~0UL,miPuerto.CRH);
    TEST_ASSERT_EQUAL_HEX32(0,miPuerto.IDR | miPuerto.ODR |
                              miPuerto.BSRR | miPuerto.BRR | miPuerto.LCKR);
}
static void configura_entrada(void)
{
    Pin_configura(&miPinH,PIN_ENTRADA);
    TEST_ASSERT_EQUAL_HEX32((0b100 << ((NUM_PIN_H-8)*4)),miPuerto.CRH);
    TEST_ASSERT_EQUAL_HEX32(0,miPuerto.CRL | miPuerto.IDR | miPuerto.ODR |
                              miPuerto.BSRR | miPuerto.BRR | miPuerto.LCKR);
}
static void configura_salida(void)
{
    Pin_configura(&miPinL,PIN_SALIDA_LENTO);
    TEST_ASSERT_EQUAL_HEX32((0b10 << ((NUM_PIN_L)*4)),miPuerto.CRL);
    TEST_ASSERT_EQUAL_HEX32(0,miPuerto.CRH | miPuerto.IDR | miPuerto.ODR |
                              miPuerto.BSRR | miPuerto.BRR | miPuerto.LCKR);
}
static void configura_salida_od(void)
{
    Pin_configura(&miPinH,PIN_SALIDA_MEDIO_OD);
    TEST_ASSERT_EQUAL_HEX32((0b101 << ((NUM_PIN_H-8)*4)),miPuerto.CRH);
    TEST_ASSERT_EQUAL_HEX32(0,miPuerto.CRL | miPuerto.IDR | miPuerto.ODR |
                              miPuerto.BSRR | miPuerto.BRR | miPuerto.LCKR);
}

static void escribe_en_salida_bajo(void)
{
    Pin_configura(&miPinH,PIN_SALIDA_LENTO);
    Pin_escribe(&miPinH,0);
    TEST_ASSERT_EQUAL_HEX32(1<<NUM_PIN_H, miPuerto.BRR | (miPuerto.BSRR>>16));
    TEST_ASSERT_EQUAL_HEX32(0,miPuerto.CRL | miPuerto.IDR | miPuerto.ODR |
                              miPuerto.LCKR);
}
static void escribe_en_salida_alto(void)
{
    Pin_configura(&miPinL,PIN_SALIDA_LENTO);
    Pin_escribe(&miPinL,1);
    TEST_ASSERT_EQUAL_HEX32(1<<NUM_PIN_L, miPuerto.BSRR);
    TEST_ASSERT_EQUAL_HEX32(0,miPuerto.CRH | miPuerto.IDR | miPuerto.ODR |
                              miPuerto.BRR | miPuerto.LCKR);
}
static void configura_entrada_pullUp(void)
{
    Pin_configura(&miPinL,PIN_ENTRADA_PULL_UP);
    TEST_ASSERT_EQUAL_HEX32((0b1000 << ((NUM_PIN_L)*4)),miPuerto.CRL);
    TEST_ASSERT_EQUAL_HEX32(1<<NUM_PIN_L, miPuerto.BSRR);
    TEST_ASSERT_EQUAL_HEX32(0,miPuerto.CRH | miPuerto.IDR | miPuerto.ODR |
                              miPuerto.BRR | miPuerto.LCKR);
}
static void configura_entrada_pullDown(void)
{
    Pin_configura(&miPinH,PIN_ENTRADA_PULL_DOWN);
    TEST_ASSERT_EQUAL_HEX32((0b1000 << ((NUM_PIN_H-8)*4)),miPuerto.CRH);
    TEST_ASSERT_EQUAL_HEX32(1<<NUM_PIN_H, miPuerto.BRR | (miPuerto.BSRR>>16));
    TEST_ASSERT_EQUAL_HEX32(0,miPuerto.CRL | miPuerto.IDR | miPuerto.ODR |
                              miPuerto.LCKR);
}

static void lee_entrada(void)
{
    Pin_configura(&miPinH,PIN_ENTRADA);
    TEST_ASSERT_EQUAL_INT(0,Pin_lee(&miPinH));
    miPuerto.IDR |= (1<<NUM_PIN_H);
    TEST_ASSERT_EQUAL_INT(1,Pin_lee(&miPinH));
}

static void lee_valor_salida(void)
{
    Pin_configura(&miPinL,PIN_SALIDA_MEDIO);
    TEST_ASSERT_EQUAL_INT(0,Pin_leeSalida(&miPinL));
    miPuerto.ODR |= (1<<NUM_PIN_L);
    TEST_ASSERT_EQUAL_INT(1,Pin_leeSalida(&miPinL));
}

int main(void)
{
    TimerSysTick_init();
    TimerSysTick_esperaMilisegundos(500);
    UNITY_BEGIN();
    RUN_TEST(configura_analogico);
    RUN_TEST(configura_entrada);
   // RUN_TEST(configura_salida);
   // RUN_TEST(configura_salida_od);
   // RUN_TEST(escribe_en_salida_bajo);
   // RUN_TEST(escribe_en_salida_alto);
   // RUN_TEST(configura_entrada_pullUp);
   // RUN_TEST(configura_entrada_pullDown);
   // RUN_TEST(lee_entrada);
   // RUN_TEST(lee_valor_salida);
    return UNITY_END();   
}