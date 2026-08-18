#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

typedef enum
{
    GPIO_INPUT = 0,
    GPIO_OUTPUT = 1
} GPIO_Mode;

void GPIO_Init(uint8_t pin, GPIO_Mode mode);
void GPIO_Write(uint8_t pin, uint8_t value);
uint8_t GPIO_Read(uint8_t pin);

#endif