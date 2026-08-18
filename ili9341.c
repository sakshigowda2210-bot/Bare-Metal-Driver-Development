#include "ili9341.h"
#include "spi.h"

#include <avr/io.h>
#include <stdint.h>

#define LCD_DC PD1

static void delay_short(void)
{
    for (volatile uint32_t i = 0; i < 5000; i++)
    {
    }
}

static void LCD_Command(uint8_t command)
{
    /* D/C = LOW → command */
    PORTD &= ~(1 << LCD_DC);

    SPI_Select();
    SPI_Transfer(command);
    SPI_Deselect();
}

static void LCD_Data(uint8_t data)
{
    /* D/C = HIGH → data */
    PORTD |= (1 << LCD_DC);

    SPI_Select();
    SPI_Transfer(data);
    SPI_Deselect();
}

void ILI9341_Init(void)
{
    /* D9 = DC */
    DDRD |= (1 << LCD_DC);

    /* Software reset */
    LCD_Command(0x01);

    delay_short();
    delay_short();

    /* Pixel format = 16-bit RGB565 */
    LCD_Command(0x3A);
    LCD_Data(0x55);

    /* Memory access control */
    LCD_Command(0x36);
    LCD_Data(0x48);

    /* Sleep out */
    LCD_Command(0x11);

    delay_short();
    delay_short();

    /* Display ON */
    LCD_Command(0x29);

    delay_short();
}

void ILI9341_FillScreen(uint16_t color)
{
    uint32_t pixels = 240UL * 320UL;

    /*
     * Column address: 0 to 239
     */
    LCD_Command(0x2A);

    LCD_Data(0x00);
    LCD_Data(0x00);
    LCD_Data(0x00);
    LCD_Data(0xEF);

    /*
     * Page address: 0 to 319
     */
    LCD_Command(0x2B);

    LCD_Data(0x00);
    LCD_Data(0x00);
    LCD_Data(0x01);
    LCD_Data(0x3F);

    /*
     * Start memory write
     */
    LCD_Command(0x2C);

    /*
     * D/C = HIGH → pixel data
     */
    PORTD |= (1 << LCD_DC);

    SPI_Select();

    while (pixels--)
    {
        SPI_Transfer((uint8_t)(color >> 8));
        SPI_Transfer((uint8_t)(color & 0xFF));
    }

    SPI_Deselect();
}