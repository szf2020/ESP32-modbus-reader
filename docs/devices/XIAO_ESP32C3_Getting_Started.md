# XIAO ESP32C3 - Getting Started Guide

> **Based on Seeed Studio XIAO ESP32C3 Wiki**
> 
> Last updated: 2025-01-27

---

## Introduction

**Seeed Studio XIAO ESP32C3** is an IoT mini development board based on Espressif **ESP32-C3** WiFi/Bluetooth dual-mode chip, featuring a **32-bit RISC-V CPU** that delivers powerful computing performance with its efficient architecture. It has excellent radio frequency performance, supporting **IEEE 802.11 b/g/n WiFi**, and **Bluetooth 5 (BLE)** protocols. This board comes included with an external antenna to increase signal strength for your wireless applications. It also has a **small and exquisite form-factor** combined with a **single-sided surface-mountable design**. It is equipped with rich interfaces and has **11 digital I/O** that can be used as **PWM pins** and **4 analog I/O** that can be used as **ADC pins**. It supports four serial interfaces such as **UART, I2C and SPI**. There is also a small **reset button** and a **bootloader mode button** on the board. XIAO ESP32C3 is fully compatible with [Grove Shield for Seeeduino XIAO](https://www.seeedstudio.com/Grove-Shield-for-Seeeduino-XIAO-p-4621.html) and [Seeeduino XIAO Expansion board](https://wiki.seeedstudio.com/Seeeduino-XIAO-Expansion-Board) except for Seeeduino XIAO Expansion board, where SWD spring contacts on the board will not be compatible.

With regard to the features highlighted above, XIAO ESP32C3 is positioned as a **high-performance, low-power, cost-effective IoT mini development board**, suitable for **low-power IoT applications and wireless wearable applications**.

### Quick Links

- [Getting Started with Seeed Studio XIAO ESP32C3](https://wiki.seeedstudio.com/XIAO_ESP32C3_Getting_Started/)
- [XIAO ESP32C3 Pinout](https://wiki.seeedstudio.com/XIAO_ESP32C3_Pin_Multiplexing/)
- [XIAO ESP32C3 with NuttX(RTOS)](https://wiki.seeedstudio.com/xiao_esp32c3_nuttx/)
- [XIAO ESP32C3 with Zephyr(RTOS)](https://wiki.seeedstudio.com/XIAO-ESP32C3-Zephyr/)
- [XIAO ESP32C3 WiFi Usage](https://wiki.seeedstudio.com/XIAO_ESP32C3_WiFi_Usage/)
- [XIAO ESP32C3 with CircuitPython](https://wiki.seeedstudio.com/xiao_esp32c3_with_circuitpython/)
- [XIAO ESP32C3 esphome Application](https://wiki.seeedstudio.com/xiao_esp32c3-esphome/)

### Resources

- [XIAO ESP32C3 Getting Started Video Guide](https://www.youtube.com/watch?v=example)
- [XIAO ESP32C3 Pinout Diagrams](https://wiki.seeedstudio.com/wiki/XIAO_WiFi/)
- [Seeed Studio Support](https://www.seeedstudio.com/contacts)
- [Seeed Studio Forum](https://forum.seeedstudio.com/)

---

## Specifications

### Processor

- **Chip**: ESP32-C3 32-bit RISC-V @160MHz
- **Architecture**: RISC-V single-core processor
- **Clock Speed**: Up to 160 MHz
- **SRAM**: 400 KB
- **Flash Memory**: 4 MB onboard
- **Crypto**: Hardware accelerators supporting AES-128/256, Hash, RSA, HMAC, digital signature and secure boot

### Wireless Connectivity

- **WiFi**: IEEE 802.11b/g/n (2.4 GHz)
  - Supports Station mode, SoftAP mode, SoftAP + Station mode, and promiscuous mode
- **Bluetooth**: Bluetooth 5 (BLE) subsystem
  - Supports Bluetooth 5.0/BLE/NFC features
- **Antenna**: External RF antenna included for better signal

### Built-in Sensors

- **IMU**: 6 DOF IMU (LSM6DS3TR-C) - 3-axis accelerometer and gyroscope
- **Microphone**: PDM Microphone

### Interfaces

- **I2C**: 1x I2C (GPIO6/GPIO7)
- **UART**: 2x UART (GPIO21/GPIO20 and GPIO8/GPIO10)
- **SPI**: 1x SPI (GPIO8/GPIO10)
- **ADC**: 4x ADC (ADC1_CH2, ADC1_CH3, ADC1_CH4) on GPIO2/GPIO3/GPIO4
- **PWM**: 11x GPIO (can be configured as PWM outputs)
- **Digital I/O**: 11x GPIO (GPIO0-GPIO10)
- **JTAG**: 1x JTAG interface (GPIO5/MTDI/MTDO/MTCK/MTMS)
- **Boot Mode**: Boot mode button (U.FL-R-SMT1)

### Onboard LEDs

- **RGB LED**: Full-color 3-in-one LED
- **Charge LED**: Battery charging indicator

### Buttons

- **Reset Button**: Single reset button
- **Boot Button**: Bootloader mode button

---

## Features

- **High-performance CPU**: ESP32-C3, 32-bit RISC-V single-core processor operating at up to 160 MHz
- **Complete WiFi Subsystem**: IEEE 802.11b/g/n protocol with Station, SoftAP, SoftAP+Station, and promiscuous modes
- **Bluetooth LE Subsystem**: Supports features of Bluetooth 5 and Bluetooth mesh networking
- **Ultra-Low Power**: Deep sleep power consumption of approximately 43μA
- **Better RF Performance**: External RF antenna included
- **Battery Charging**: Supports lithium battery charge and discharge management with ETA4054S2F power management chip
- **Rich On-Chip Resources**: 400KB of SRAM, and 4MB of on-board flash memory
- **Ultra Small Size**: As small as a thumb (21×17.8mm) XIAO series classic form-factor for wearable devices and small projects
- **Reliable Security Features**: Cryptographic hardware accelerators, secure boot
- **Rich Interfaces**: 1×I2C, 1×SPI, 2×UART, 11×GPIO(PWM), 4×ADC, 1×JTAG bonding pad
- **Single-sided Components**: Surface mounting design

---

## Hardware Overview

### Pinout and GPIO Mapping

See [XIAO ESP32C3 Pin Map](https://wiki.seeedstudio.com/wiki/XIAO_WiFi/pin_map-2.png) for complete pinout diagram.

### Front Side (GPIO0-GPIO10)

| XIAO Pin | Function               | Chip Pin                                                      | Description                    |
| -------- | ---------------------- | ------------------------------------------------------------- | ------------------------------ |
| D0       | ADC1_CH2               | GPIO, ADC - ADC1 Channel 2, GPIO2                             |                                |
| D1       | ADC1_CH3               | GPIO, ADC - ADC1 Channel 3, GPIO3                             |                                |
| D2       | ADC1_CH4, FSPIHD, MTMS | GPIO, ADC - ADC1 Channel 4, SPI/Flash/Memory/Test Mode, GPIO4 |                                |
| D3       | ADC2_CH0, FSPIWP, MTDI | GPIO, ADC - ADC2 Channel 0, SPI Write Protect, GPIO5          |                                |
| D4       | SDA                    | I2C Data                                                      | I2C SDA, GPIO6                 |
| D5       | SCL                    | I2C Clock                                                     | I2C SCL, GPIO7                 |
| D6       | SCK                    | SPI Clock                                                     | SPI SCK, GPIO8                 |
| D7       | MISO                   | SPI Data In                                                   | SPI MISO, GPIO9                |
| D8       | MOSI                   | SPI Data Out                                                  | SPI MOSI, GPIO10               |
| D9       | MTDO                   | SPI Data Out                                                  | JTAG TDO, MTDO - JTAG Data Out |
| D10      | MTCK                   | JTAG Clock                                                    | JTAG TCK - JTAG Clock          |

### Back Side

| XIAO Pin | Function | Chip Pin      | Description                      |
| -------- | -------- | ------------- | -------------------------------- |
| TX       | U0TXD    | UART Transmit | UART0 TX - Data Transmit, GPIO21 |
| RX       | U0RXD    | UART Receive  | UART0 RX - Data Receive, GPIO20  |

### Power Pins

| XIAO Pin | Function | Description                                                                                    |
| -------- | -------- | ---------------------------------------------------------------------------------------------- |
| 5V       | VBUS     | Power Input/Output - 5V out from USB port. Can also use as voltage input with diode to battery |
| 3V3      | 3V3_OUT  | Power Output - Regulated 3.3V output. Can draw up to 700mA                                     |
| GND      | GND      | Power/Data/Signal Ground                                                                       |

### Strapping Pins

> **WARNING**: According to the ESP32-C3 chip manual, **GPIO2**, **GPIO8**, and **GPIO9** are Strapping Pins. High and low level configurations of these pins allow the chip to enter different Boot modes. Pay attention to this point when using these pins, otherwise it may prevent your XIAO from uploading or executing programs.

See [strapping pins diagram](https://files.seeedstudio.com/wiki/XIAO_WiFi/20.png) for details.

---

## 

## Programming Languages

XIAO ESP32C3 supports multiple development platforms:

| Platform      | Language | Notes                          |
| ------------- | -------- | ------------------------------ |
| Arduino       | C++      | Official Arduino IDE support   |
| MicroPython   | Python   | Interactive Python interpreter |
| CircuitPython | Python   | Python with hardware modules   |

---

## Documentation

- [ESP32-C3 Datasheet](https://files.seeedstudio.com/wiki/XIAO_WiFi/Resources/esp32-c3_datasheet.pdf) (PDF)
- [XIAO ESP32C3 Schematic](https://files.seeedstudio.com/wiki/XIAO_WiFi/Resources/Seeeduino-XIAO-ESP32C3-SCH.pdf) (PDF)
- [XIAO ESP32C3 KiCAD Libraries](https://files.seeedstudio.com/wiki/XIAO_WiFi/Resources/Seeeduino-XIAO-ESP32C3-KiCAD-Library.zip) (ZIP)
- [XIAO ESP32C3 Eagle Libraries](https://files.seeedstudio.com/wiki/XIAO_WiFi/Resources/XIAO-ESP32C3-v1.2_SCHPCB.zip) (ZIP)
- [XIAO ESP32C3 Factory Firmware](https://files.seeedstudio.com/wiki/XIAO_WiFi/Resources/ESP32-C3_RFTest_108_2b9b157_20211014.bin)
- [XIAO ESP32C3 Dimension in DXF](https://files.seeedstudio.com/wiki/XIAO_WiFi/Resources/XIAO-ESP32C3-DXF.zip)
- [XIAO ESP32C3 Eagle footprint](https://files.seeedstudio.com/wiki/XIAO_WiFi/Resources/Seeed-Studio-XIAO-ESP32C3-footprint-eagle.lbr)
- [XIAO ESP32C3 pinout sheet](https://files.seeedstudio.com/wiki/XIAO_WiFi/Resources/XIAO-ESP32C3-pinout_sheet.xlsx)
- [STEP format 3D Model](https://grabcad.com/library/seeed-studio-xiao-esp32-c3-1)

### Libraries and SDKs

- [MicroPython GitHub Repository](https://github.com/IcingTomato/micropython_xiao_esp32c3/)
- [PlatformIO for XIAO ESP32C3](https://docs.platformio.org/en/latest/boards/espressif32/seeed_xiao_esp32c3.html)

### External References

- [First Look at Seeed Studio XIAO ESP32C3](https://sigmdel.ca/michel/ha/xiao/xiao_esp32c3_intro_en.html)
- [XIAO: Big Power, Small Board Mastering Arduino and TinyML](https://mjrovai.github.io/XIAO_Big_Power_Small_Board-ebook/)

---

## Tips and Best Practices

1. **Use ADC1 for analog readings**: ADC2 may have false sampling signals. Use ADC1 (GPIO2/A1/A2) for reliable analog reads
2. **Respect strapping pins**: Don't use GPIO2, GPIO8, GPIO9 unless needed
3. **LED current limiting**: Always use resistors (150Ω recommended) with LEDs
4. **Serial monitor**: Use 115200 baud rate for XIAO ESP32C3
5. **Power supply**: 5V from USB can power the board and communicate simultaneously
6. **Board package**: Make sure Arduino ESP32 board package is up to date
7. **Deep sleep**: Wake-up only works on pins D0-D3

---

## Community and Support

- **Seeed Studio Forum**: [https://forum.seeedstudio.com/](https://forum.seeedstudio.com/) - Get help and share projects
- **Seeed Studio Discord**: [https://discord.gg/eWkprNDMU7](https://discord.gg/eWkprNDMU7) - Real-time chat with community
- **GitHub Discussions**: [https://github.com/Seeed-Studio/wiki-documents/discussions/69](https://github.com/Seeed-Studio/wiki-documents/discussions/69)
- **Email Support**: [support@seeedstudio.com](mailto:support@seeedstudio.com)
- **Apply for contributors**: [https://docs.google.com/forms/d/e/1FAIpQLSdiAWHmRJqgVNTJyJDkzhufc1dygFyhWFyEtUTm-mrgSKaEgg/viewform](https://docs.google.com/forms/d/e/1FAIpQLSdiAWHmRJqgVNTJyJDkzhufc1dygFyhWFyEtUTm-mrgSKaEgg/viewform)
- **Direct Assignments**: [https://github.com/orgs/Seeed-Studio/projects/6](https://github.com/orgs/Seeed-Studio/projects/6)

---

**This guide is based on the official Seeed Studio XIAO ESP32C3 Wiki**
