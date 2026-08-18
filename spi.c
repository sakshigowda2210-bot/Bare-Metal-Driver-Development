#include "spi.h"
#include <avr/io.h>

void SPI_Init(SPI_Mode mode, SPI_DataOrder order)
{
    /* D10 = SS
       D11 = MOSI
       D12 = MISO
       D13 = SCK
    */

    DDRB |=
        (1 << PB2) |
        (1 << PB3) |
        (1 << PB5);

    DDRB &= ~(1 << PB4);

    /* CS inactive */
    PORTB |= (1 << PB2);

    SPCR = 0;

    /* Enable SPI + Master */
    SPCR |=
        (1 << SPE) |
        (1 << MSTR);

    /* Data order */
    if (order == SPI_LSB_FIRST)
    {
        SPCR |= (1 << DORD);
    }

    /* SPI mode */
    switch (mode)
    {
        case SPI_MODE_0:
            break;

        case SPI_MODE_1:
            SPCR |= (1 << CPHA);
            break;

        case SPI_MODE_2:
            SPCR |= (1 << CPOL);
            break;

        case SPI_MODE_3:
            SPCR |=
                (1 << CPOL) |
                (1 << CPHA);
            break;
    }

    /* SPI clock = F_CPU / 16 */
    SPCR |= (1 << SPR1) | (1 << SPR0);
}


void SPI_Select(void)
{
    PORTB &= ~(1 << PB2);
}


void SPI_Deselect(void)
{
    PORTB |= (1 << PB2);
}


uint8_t SPI_Transfer(uint8_t data)
{
    SPDR = data;

    while (!(SPSR & (1 << SPIF)))
    {
    }

    return SPDR;
}