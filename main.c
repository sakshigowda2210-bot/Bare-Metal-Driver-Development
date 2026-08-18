#include <avr/io.h>
#include "gpio.h"
#include "uart.h"
#include "i2c.h"
#include "spi.h"
#include "lcd.h"

#define LED_PIN     8
#define BUTTON_PIN  7

#define I2C_ADDRESS 0x27

int main(void)
{
    /* ================= GPIO ================= */

    GPIO_Init(LED_PIN, GPIO_OUTPUT);
    GPIO_Init(BUTTON_PIN, GPIO_INPUT);

    /* Enable internal pull-up */
    PORTD |= (1 << BUTTON_PIN);


    /* ================= UART ================= */

    UART_Init(9600);

    UART_SendString("\r\n");
    UART_SendString("====================================\r\n");
    UART_SendString(" ATMEGA328P BARE-METAL DRIVER DEMO\r\n");
    UART_SendString("====================================\r\n");


    /* ================= I2C ================= */

    I2C_Init(100000);

    LCD_Init();
    LCD_Clear();

    LCD_SetCursor(0, 0);
    LCD_Print("BARE-METAL");

    LCD_SetCursor(1, 0);
    LCD_Print("DRIVER DEMO");

    UART_SendString("I2C: Initialized\r\n");

    if (I2C_Start(I2C_ADDRESS << 1))
    {
        UART_SendString("I2C: Device detected\r\n");

        if (I2C_Write(0x00))
        {
            UART_SendString("I2C: Write ACK\r\n");
        }
        else
        {
            UART_SendString("I2C: Write NACK\r\n");
        }

        I2C_Stop();
    }
    else
    {
        UART_SendString("I2C: Device not detected\r\n");
    }


    /* ================= SPI ================= */

    SPI_Init(SPI_MODE_0, SPI_MSB_FIRST);

    UART_SendString("SPI: Initialized\r\n");

    SPI_Select();

    SPI_Transfer(0x55);
    SPI_Transfer(0xAA);

    SPI_Deselect();

    UART_SendString("SPI: Transfer 1 COMPLETE\r\n");
    UART_SendString("SPI: Transfer 2 COMPLETE\r\n");
    UART_SendString("SPI: DRIVER TEST PASSED\r\n");


    /* ================= GPIO ================= */

    UART_SendString("GPIO: Button controls LED\r\n");
    UART_SendString("------------------------------------\r\n");


    /* ================= MAIN LOOP ================= */

    while (1)
    {
        if (GPIO_Read(BUTTON_PIN) == 0)
        {
            GPIO_Write(LED_PIN, 1);
        }
        else
        {
            GPIO_Write(LED_PIN, 0);
        }
    }

    return 0;
}