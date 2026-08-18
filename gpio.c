#include "gpio.h"
#include <avr/io.h>

void GPIO_Init(uint8_t pin, GPIO_Mode mode)
{
    if (pin <= 7)
    {
        if (mode == GPIO_OUTPUT)
            DDRD |= (1 << pin);
        else
            DDRD &= ~(1 << pin);
    }
    else if (pin <= 13)
    {
        uint8_t bit = pin - 8;

        if (mode == GPIO_OUTPUT)
            DDRB |= (1 << bit);
        else
            DDRB &= ~(1 << bit);
    }
    else if (pin <= 19)
    {
        uint8_t bit = pin - 14;

        if (mode == GPIO_OUTPUT)
            DDRC |= (1 << bit);
        else
            DDRC &= ~(1 << bit);
    }
}

void GPIO_Write(uint8_t pin, uint8_t value)
{
    if (pin <= 7)
    {
        if (value)
            PORTD |= (1 << pin);
        else
            PORTD &= ~(1 << pin);
    }
    else if (pin <= 13)
    {
        uint8_t bit = pin - 8;

        if (value)
            PORTB |= (1 << bit);
        else
            PORTB &= ~(1 << bit);
    }
    else if (pin <= 19)
    {
        uint8_t bit = pin - 14;

        if (value)
            PORTC |= (1 << bit);
        else
            PORTC &= ~(1 << bit);
    }
}

uint8_t GPIO_Read(uint8_t pin)
{
    if (pin <= 7)
        return (PIND & (1 << pin)) != 0;

    if (pin <= 13)
    {
        uint8_t bit = pin - 8;
        return (PINB & (1 << bit)) != 0;
    }

    if (pin <= 19)
    {
        uint8_t bit = pin - 14;
        return (PINC & (1 << bit)) != 0;
    }

    return 0;
}