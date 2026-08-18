#include "i2c.h"
#include <avr/io.h>

#define F_CPU 16000000UL

#define TWI_STATUS_MASK 0xF8

#define TWI_START        0x08
#define TWI_REP_START    0x10
#define TWI_MT_SLA_ACK   0x18
#define TWI_MT_DATA_ACK  0x28
#define TWI_MR_SLA_ACK   0x40

#define I2C_TIMEOUT 100000UL


static uint8_t I2C_Wait(void)
{
    uint32_t timeout = 0;

    while (!(TWCR & (1 << TWINT)))
    {
        timeout++;

        if (timeout >= I2C_TIMEOUT)
        {
            return 0;
        }
    }

    return 1;
}


void I2C_Init(uint32_t clock)
{
    TWSR = 0;

    TWBR = (uint8_t)(((F_CPU / clock) - 16) / 2);

    TWCR = (1 << TWEN);
}


uint8_t I2C_Start(uint8_t address)
{
    TWCR =
        (1 << TWINT) |
        (1 << TWSTA) |
        (1 << TWEN);

    if (!I2C_Wait())
    {
        return 0;
    }

    uint8_t status = TWSR & TWI_STATUS_MASK;

    if (status != TWI_START &&
        status != TWI_REP_START)
    {
        return 0;
    }

    TWDR = address;

    TWCR =
        (1 << TWINT) |
        (1 << TWEN);

    if (!I2C_Wait())
    {
        return 0;
    }

    status = TWSR & TWI_STATUS_MASK;

    if (status == TWI_MT_SLA_ACK ||
        status == TWI_MR_SLA_ACK)
    {
        return 1;
    }

    return 0;
}


void I2C_Stop(void)
{
    TWCR =
        (1 << TWINT) |
        (1 << TWSTO) |
        (1 << TWEN);
}


uint8_t I2C_Write(uint8_t data)
{
    TWDR = data;

    TWCR =
        (1 << TWINT) |
        (1 << TWEN);

    if (!I2C_Wait())
    {
        return 0;
    }

    return ((TWSR & TWI_STATUS_MASK) ==
            TWI_MT_DATA_ACK);
}


uint8_t I2C_ReadAck(void)
{
    TWCR =
        (1 << TWINT) |
        (1 << TWEN) |
        (1 << TWEA);

    if (!I2C_Wait())
    {
        return 0;
    }

    return TWDR;
}


uint8_t I2C_ReadNack(void)
{
    TWCR =
        (1 << TWINT) |
        (1 << TWEN);

    if (!I2C_Wait())
    {
        return 0;
    }

    return TWDR;
}