# MAX485 TTL to RS485 Module

> **Based on MicroDigisoft Tutorial**
> 
> Last updated: 2025-01-27

---

## Introduction

The **MAX485 TTL to RS485 Module** is a level shifter that converts TTL/CMOS serial signals to RS485 differential signals for long-range, high-speed communication. This module is essential for interfacing microcontrollers like ESP32 with industrial Modbus RTU devices, sensors, PLCs, and HMIs.

---

## Module Overview

### What is MAX485?

The MAX485 is a low-power transceiver for RS485 and RS422 communication. It provides full compliance with the RS485 and RS422 standards when operating from a 3.3V supply, maintaining proper differential signaling even at reduced voltages.

### Purpose

- Converts TTL (0-5V) signals to RS485 differential signals (±5V)
- Enables long-distance communication up to 1.2km
- Supports multi-drop networks with up to 32 devices
- Provides noise immunity for industrial environments

---

## Specifications

| Parameter                  | Value                        |
| -------------------------- | ---------------------------- |
| **Chip**                   | MAX485                       |
| **Supply Voltage**         | 5V (also works with 3.3V)    |
| **Communication Protocol** | RS485, RS422                 |
| **Data Rate**              | Up to 10 Mbit/s              |
| **Bus Length**             | Up to 1.2km (4000ft)         |
| **Devices on Bus**         | Up to 32 units               |
| **Operating Temperature**  | 0°C to +70°C                 |
| **Power Consumption**      | Low power, slew-rate limited |
| **Terminal Pitch**         | 5.08mm (2P terminal for A/B) |

---

## Features

1. **On-board MAX485 chip** - Low-power consumption RS485 transceiver
2. **Slew-rate limited** - Reduces EMI and reflections
3. **All pins accessible** - Full microcontroller control
4. **Multi-drop configuration** - Connect multiple devices on same bus
5. **Convenient wiring** - Terminal block for RS485 A/B lines
6. **5.08mm pitch terminal** - Easy connection to RS485 bus
7. **ESD protection** - Built-in protection for industrial environments

---

## MAX485 Module Pinout

| Pin | Name                | Description                        | Connection             |
| --- | ------------------- | ---------------------------------- | ---------------------- |
| VCC | VCC                 | Power supply (5V)                  | Connect to 5V          |
| GND | GND                 | Ground                             | Connect to GND         |
| RO  | Receiver Output     | Data output to microcontroller RX  | Connect to ESP32 RX    |
| DI  | Driver Input        | Data input from microcontroller TX | Connect to ESP32 TX    |
| DE  | Driver Enable       | Enable transmission (Active HIGH)  | Connect to GPIO        |
| RE  | Receiver Enable     | Enable reception (Active LOW)      | Connect to GPIO        |
| A   | Non-inverting Input | RS485 differential signal A        | Connect to RS485 bus A |
| B   | Inverting Input     | RS485 differential signal B        | Connect to RS485 bus B |

### DE/RE Control Pins

- **DE (Driver Enable)**: HIGH = transmit mode, LOW = receive mode
- **RE (Receiver Enable)**: LOW = receive mode, HIGH = disabled
- **Common Practice**: Connect DE and RE together for simple control
  - HIGH = Transmit
  - LOW = Receive

---

## Wiring to XIAO ESP32C3

### Recommended Pin Connections

| MAX485 Pin | XIAO ESP32C3 Pin | XIAO Label      | Description                   |
| ---------- | ---------------- | --------------- | ----------------------------- |
| VCC        | 5V               | 5V              | Power supply                  |
| GND        | GND              | GND             | Ground                        |
| RO         | GPIO20           | RX (Back side)  | UART0 RX - Data receive       |
| DI         | GPIO21           | TX (Back side)  | UART0 TX - Data transmit      |
| DE         | GPIO7            | D5 (Front side) | Driver enable                 |
| RE         | GPIO7            | D5 (Front side) | Receiver enable (tie to DE)   |
| A          | -                | -               | RS485 bus A (to slave device) |
| B          | -                | -               | RS485 bus B (to slave device) |

### Alternative Control Pin Options

If D5 (GPIO7) is unavailable, use any other GPIO (except strapping pins):

| XIAO Pin | GPIO  | Notes                       |
| -------- | ----- | --------------------------- |
| D4       | GPIO6 | I2C SDA, avoid if using I2C |
| D6       | GPIO8 | SPI SCK, strapping pin ⚠️   |
| D7       | GPIO9 | SPI MISO, strapping pin ⚠️  |
| D0       | GPIO2 | ADC1_CH2, strapping pin ⚠️  |

### ⚠️ Important Warnings

1. **Strapping Pins**: GPIO2, GPIO8, and GPIO9 are strapping pins that affect boot mode. Avoid using these unless necessary.
2. **DE/RE Connection**: Always connect DE and RE together for bidirectional communication control.
3. **A/B Polarity**: Correct polarity is essential. If communication fails, try swapping A and B lines.
4. **Termination**: Add 120Ω termination resistor between A and B at both ends of the bus for long runs (>10m).
5. **Cabling**: Use shielded twisted-pair cables for noise immunity in industrial environments.

### Wiring Diagram (ASCII)

```
MAX485 Module                XIAO ESP32C3
+-------------+             +----------------+
| VCC         |------------>| 5V             |
| GND         |------------>| GND            |
| RO          |------------>| RX (GPIO20)    |
| DI          |------------>| TX (GPIO21)    |
| DE          |----+        |                |
| RE          |----+------->| D5 (GPIO7)     |
| A           |------------>| A (to device)  |
| B           |------------>| B (to device)  |
+-------------+             +----------------+

DE and RE connected together (tie to same GPIO)
```

---

## Usage Example

### Arduino Code for Modbus RTU

```cpp
#include <SoftwareSerial.h>

// Pin Definitions
#define RX_PIN 20      // XIAO RX (back side)
#define TX_PIN 21      // XIAO TX (back side)
#define DE_RE_PIN 7    // XIAO D5 (GPIO7)

// SoftwareSerial for MAX485
SoftwareSerial modbusSerial(RX_PIN, TX_PIN);

// Modbus RTU Request Frame
// Slave ID: 1, Function: 0x03 (Read Holding Registers)
// Start Address: 0x001E (30), Quantity: 1
uint8_t requestFrame[] = {0x01, 0x03, 0x00, 0x1E, 0x00, 0x01};
uint8_t responseBuffer[8];

void setup() {
  Serial.begin(115200);      // Debug serial
  modbusSerial.begin(9600);  // Modbus serial (9600, 8N1)

  pinMode(DE_RE_PIN, OUTPUT);
  digitalWrite(DE_RE_PIN, LOW); // Start in receive mode

  Serial.println("MAX485 Modbus RTU Reader");
}

void loop() {
  sendModbusRequest();
  readModbusResponse();
  delay(2000); // Poll every 2 seconds
}

void sendModbusRequest() {
  // Calculate CRC
  uint16_t crc = calculateCRC(requestFrame, 6);
  uint8_t frame[8];
  memcpy(frame, requestFrame, 6);
  frame[6] = crc & 0xFF;      // CRC Low byte
  frame[7] = (crc >> 8) & 0xFF; // CRC High byte

  // Enable transmission
  digitalWrite(DE_RE_PIN, HIGH);

  // Send request
  modbusSerial.write(frame, 8);
  modbusSerial.flush(); // Wait for transmission complete

  // Switch to receive mode
  digitalWrite(DE_RE_PIN, LOW);
}

void readModbusResponse() {
  unsigned long startTime = millis();
  uint8_t index = 0;

  // Read response with 1 second timeout
  while (millis() - startTime < 1000 && index < 8) {
    if (modbusSerial.available()) {
      responseBuffer[index++] = modbusSerial.read();
    }
  }

  // Validate and display response
  if (index >= 5 && validateCRC(responseBuffer, index)) {
    Serial.print("Response: ");
    Serial.print("Byte1="); Serial.print(responseBuffer[1]);
    Serial.print(" Byte2="); Serial.print(responseBuffer[2]);
    Serial.print(" Byte3="); Serial.println(responseBuffer[3]);
  } else {
    Serial.println("Error: Invalid response or CRC mismatch");
  }
}

// CRC-16 calculation for Modbus RTU
uint16_t calculateCRC(uint8_t *data, uint8_t length) {
  uint16_t crc = 0xFFFF;
  for (uint8_t i = 0; i < length; i++) {
    crc ^= data[i];
    for (uint8_t j = 0; j < 8; j++) {
      if (crc & 0x0001) {
        crc >>= 1;
        crc ^= 0xA001;
      } else {
        crc >>= 1;
      }
    }
  }
  return crc;
}

bool validateCRC(uint8_t *data, uint8_t length) {
  if (length < 2) return false;
  uint16_t receivedCRC = (data[length-1] << 8) | data[length-2];
  uint16_t calculatedCRC = calculateCRC(data, length - 2);
  return receivedCRC == calculatedCRC;
}
```

### Using Hardware UART (Recommended)

For better performance, use XIAO's hardware UART:

```cpp
#define RX_PIN 20
#define TX_PIN 21
#define DE_RE_PIN 7

HardwareSerial &modbusSerial = Serial; // Use Serial0

void setup() {
  modbusSerial.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
  pinMode(DE_RE_PIN, OUTPUT);
  digitalWrite(DE_RE_PIN, LOW);
}
```

---

## Troubleshooting

### Common Issues and Solutions

| Issue                     | Possible Cause              | Solution                                               |
| ------------------------- | --------------------------- | ------------------------------------------------------ |
| **No response**           | A/B lines reversed          | Swap A and B connections                               |
| **CRC errors**            | Wrong baud rate or parity   | Match slave device settings (typically 9600, 8N1)      |
| **Garbage data**          | Electrical noise            | Use shielded twisted-pair cables, add 120Ω termination |
| **Intermittent readings** | Ground loops or long cables | Use proper grounding, termination, and cable types     |
| **Module won't transmit** | DE/RE not controlled        | Verify DE/RE is HIGH during transmission               |
| **Can't upload code**     | Using strapping pins        | Disconnect RX/TX during upload, avoid GPIO2/8/9        |

### Testing with Modbus Simulator

1. Install [QModMaster](https://sourceforge.net/projects/qmodmaster/) or similar tool
2. Configure virtual slave:
   - Baud Rate: 9600
   - Slave ID: 1
   - Register Address: 30 (0x001E)
3. Test communication before connecting to real device

---

## Advanced Configuration

### Multiple Devices on Bus

- Connect up to 32 MAX485 modules to same RS485 bus
- Each device needs unique slave address (1-247)
- Add 120Ω termination resistor at both ends of bus
- Use star or daisy-chain topology

### Best Practices

1. **Cabling**: Use twisted-pair shielded cable (e.g., CAT5 or dedicated RS485 cable)
2. **Termination**: Add 120Ω resistor between A and B at both ends for long runs
3. **Bias Resistors**: Add 560Ω resistors from A to VCC and B to GND for idle state
4. **Grounding**: Connect grounds at one point to avoid ground loops
5. **Speed vs Distance**: For 1200m, use ≤100kbps; for 100m, use up to 10Mbps

---

## References

- [Source Tutorial: ESP32 with MODBUS RTU RS485 Protocol](https://microdigisoft.com/esp32-with-modbus-rtu-rs485-protocol-using-arduino-ide/)
- [XIAO ESP32C3 Getting Started Guide](./XIAO_ESP32C3_Getting_Started.md)
- [Modbus Organization](http://www.modbus.org/)
- [MAX485 Datasheet](https://datasheets.maximintegrated.com/en/ds/MAX1487-MAX491.pdf)

---

**This guide is based on the MicroDigisoft tutorial and adapted for XIAO ESP32C3**
