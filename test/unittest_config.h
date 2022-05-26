#ifndef UNITTEST_TRANSPORT_H
#define UNITTEST_TRANSPORT_H

#ifdef __cplusplus
    extern "C"{
#endif

void unittest_uart_begin(void);
void unittest_uart_putchar(char c);
void unittest_uart_flush(void);
void unittest_uart_end(void);

#define UNITY_OUTPUT_CHAR(a) unittest_uart_putchar(a)
#define UNITY_OUTPUT_FLUS() unittest_uart_flush()
#define UNITY_OUTPUT_START() unittest_uart_begin()
#define UNITY_OUTPUT_COMPLETE() unittest_uart_end()

#ifdef __cplusplus
    }
#endif

#endif
