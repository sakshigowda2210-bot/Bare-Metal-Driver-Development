#include "uart.h"
#include <avr/io.h>

#define F_CPU 16000000UL

void UART_Init(uint32_t baud)
{
    uint16_t ubrr;

    ubrr = (F_CPU / (16UL * baud)) - 1;

    UBRR0H = (uint8_t)(ubrr >> 8);
    UBRR0L = (uint8_t)ubrr;

    /* Enable transmitter and receiver */
    UCSR0B =
        (1 << RXEN0) |
        (1 << TXEN0);

    /* 8 data bits, 1 stop bit */
    UCSR0C =
        (1 << UCSZ01) |
        (1 << UCSZ00);
}

void UART_SendChar(char c)
{
    while (!(UCSR0A & (1 << UDRE0)))
    {
    }

    UDR0 = c;
}

void UART_SendString(const char *str)
{
    while (*str)
    {
        UART_SendChar(*str);
        str++;
    }
}

char UART_ReceiveChar(void)
{
    while (!(UCSR0A & (1 << RXC0)))
    {
    }

    return UDR0;
}