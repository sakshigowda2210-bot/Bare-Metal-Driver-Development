#include "lcd.h"
#include "i2c.h"

#define LCD_ADDRESS 0x27

#define LCD_BACKLIGHT 0x08
#define LCD_ENABLE    0x04
#define LCD_RS        0x01

static void LCD_Delay(void)
{
    for (volatile uint32_t i = 0; i < 3000; i++)
    {
    }
}

static void LCD_WriteByte(uint8_t data)
{
    if (!I2C_Start(LCD_ADDRESS << 1))
        return;

    I2C_Write(data | LCD_BACKLIGHT);
    I2C_Stop();

    LCD_Delay();
}

static void LCD_Pulse(uint8_t data)
{
    LCD_WriteByte(data | LCD_ENABLE);
    LCD_WriteByte(data & ~LCD_ENABLE);
}

static void LCD_Send4Bits(uint8_t data)
{
    LCD_WriteByte(data);
    LCD_Pulse(data);
}

static void LCD_Send(uint8_t value, uint8_t mode)
{
    uint8_t high = value & 0xF0;
    uint8_t low  = (value << 4) & 0xF0;

    LCD_Send4Bits(high | mode);
    LCD_Send4Bits(low | mode);
}

static void LCD_Command(uint8_t command)
{
    LCD_Send(command, 0);
}

static void LCD_Data(uint8_t data)
{
    LCD_Send(data, LCD_RS);
}

void LCD_Init(void)
{
    /* Allow LCD power-up */
    for (volatile uint32_t i = 0; i < 50000; i++)
    {
    }

    /* 4-bit initialization sequence */
    LCD_Send4Bits(0x30);
    LCD_Delay();

    LCD_Send4Bits(0x30);
    LCD_Delay();

    LCD_Send4Bits(0x30);
    LCD_Delay();

    LCD_Send4Bits(0x20);
    LCD_Delay();

    /* Function set: 4-bit, 2 lines, 5x8 font */
    LCD_Command(0x28);

    /* Display ON, cursor OFF */
    LCD_Command(0x0C);

    /* Entry mode */
    LCD_Command(0x06);

    /* Clear display */
    LCD_Command(0x01);

    for (volatile uint32_t i = 0; i < 50000; i++)
    {
    }
}

void LCD_Clear(void)
{
    LCD_Command(0x01);

    for (volatile uint32_t i = 0; i < 50000; i++)
    {
    }
}

void LCD_SetCursor(uint8_t row, uint8_t column)
{
    uint8_t address;

    if (row == 0)
        address = 0x00 + column;
    else
        address = 0x40 + column;

    LCD_Command(0x80 | address);
}

void LCD_Print(const char *text)
{
    while (*text)
    {
        LCD_Data((uint8_t)*text);
        text++;
    }
}