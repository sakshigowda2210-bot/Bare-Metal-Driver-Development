#ifndef SPI_H
#define SPI_H

#include <stdint.h>

typedef enum
{
    SPI_MODE_0 = 0,
    SPI_MODE_1,
    SPI_MODE_2,
    SPI_MODE_3
} SPI_Mode;

typedef enum
{
    SPI_MSB_FIRST = 0,
    SPI_LSB_FIRST
} SPI_DataOrder;

void SPI_Init(SPI_Mode mode, SPI_DataOrder order);

void SPI_Select(void);
void SPI_Deselect(void);

uint8_t SPI_Transfer(uint8_t data);

#endif