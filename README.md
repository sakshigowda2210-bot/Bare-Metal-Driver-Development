# Bare-Metal Driver Development

## Overview

A bare-metal driver development project using ESP32 and Wokwi simulation. The project focuses on implementing low-level peripheral drivers without relying on high-level driver libraries.

## Features

- GPIO driver for digital input and output
- UART driver for serial communication
- I2C driver for two-wire device communication
- SPI driver for high-speed peripheral communication
- Modular driver structure using `.c` and `.h` files
- Wokwi-based simulation and testing

## Technologies Used

- ESP32
- Embedded C
- GPIO
- UART
- I2C
- SPI
- Wokwi
- Arduino IDE

## Project Structure

| File | Description |
|---|---|
| `main.c` | Main application |
| `gpio.c` / `gpio.h` | GPIO driver |
| `uart.c` / `uart.h` | UART driver |
| `i2c.c` / `i2c.h` | I2C driver |
| `spi.c` / `spi.h` | SPI driver |
| `lcd.c` / `lcd.h` | LCD interface |
| `ili9341.c` / `ili9341.h` | ILI9341 display interface |
| `diagram.json` | Wokwi circuit configuration |
| `sketch.ino` | Wokwi/Arduino entry file |
| `wokwi-project.txt` | Wokwi project configuration |

## Simulation

The project was developed and tested using the Wokwi online simulator.

The simulation demonstrates the embedded firmware and peripheral communication without requiring physical hardware.

## Learning Outcomes

- Understanding of microcontroller peripherals
- Register-level and low-level driver concepts
- Modular embedded C programming
- Serial and peripheral communication protocols
- Firmware testing and debugging using simulation

## Author

**Sakshi**

Electronics and Communication Engineering
