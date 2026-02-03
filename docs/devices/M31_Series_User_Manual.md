# M31 Series Distributed I/O Master User Manual

**Version 1.1**

Chengdu Ebyte Electronic Technology Co., Ltd.  
Copyright ©2012–2025

---

## Table of Contents

- [Disclaimer](#disclaimer)
- [Chapter 1: Product Overview](#chapter-1-product-overview)
- [Chapter 2: Quick Use](#chapter-2-quick-use)
- [Chapter 3: Technical Indicators](#chapter-3-technical-indicators)
- [Chapter 4: Product Function Introduction](#chapter-4-product-function-introduction)
- [Chapter 5: Upper Computer](#chapter-5-upper-computer)
- [Chapter 6: Precautions](#chapter-6-precautions)
- [Chapter 7: About Us](#chapter-7-about-us)

---

## Disclaimer

EBYTE reserves all rights to this document and the information contained herein. Products, names, logos and designs described herein may in whole or in part be subject to intellectual property rights. Reproduction, use, modification or disclosure to third parties of this document or any part thereof without the express permission of EBYTE is strictly prohibited.

The information contained herein is provided "as is" and EBYTE assumes no liability for the use of the information. No warranty, either express or implied, is given, including but not limited, with respect to the accuracy, correctness, reliability and fitness for a particular purpose of the information. This document may be revised by EBYTE at any time. For most recent documents, visit www.cdebyte.com.

---

## Chapter 1: Product Overview

### 1.1 Product Introduction

The M31 series distributed IO host supports Modbus TCP protocol and Modbus RTU protocol for acquisition and control. The device supports 5 clients to access at the same time and supports function codes 01/02/03/04/05/06/15/16.

The product adopts an expandable design in structure. During the user's use, if it is found that some functions of the current device cannot meet the needs, the user can choose to meet the corresponding IO expansion module according to the missing functions for splicing to achieve functional satisfaction. There is no need to purchase the whole machine, which saves costs and facilitates customers to access the current on-site environment.

The module has its own status diagnosis function, which can monitor the communication status of the IO module in real time. The maximum number of IO expansion modules supported is 16.

### 1.2 Features

- Support standard Modbus RTU protocol and Modbus TCP protocol
- Support various configuration software/PLC/touch screen
- RS485 acquisition control I/O
- Network port acquisition control I/O, support 5-way host access
- Support custom Modbus address settings
- Support differential analog input, 16-bit resolution, accuracy within 1‰, with power supply isolation
- Support 8 baud rate configurations
- Support DHCP and static IP
- Support DNS function and domain name resolution
- Support positioning hole and guide rail installation
- Using distributed IO mode, up to 16 IO expansion modules can be connected

### 1.3 Product Model List

| Product Model | Product Specifications |
|---------------|------------------------|
| M31-AAAX4440G | 4DI+4AI(Single-ended current)+4DO |
| M31-AXXX8000G | 8DI |
| M31-XXAX0080G | 8DO |
| M31-AXAX4040G | 4DI+4DO |
| M31-AXXXA000G | 16DI |
| M31-XXAX00A0G | 16DO |
| M31-AXAX8080G | 8DI+8DO |
| M31-XAXX0800G | 8AI(Single-ended current) |
| M31-XXXA0008G | 8AO(Current output) |
| M31-XAXA0404G | 4AI(Single-ended current)+4AO(Current output) |
| M31-XFXX0800G | 8AI(Differential Current) |
| M31-XGXX0800G | 8AI(Differential Current) |

---

## Chapter 2: Quick Use

**Note:** This experiment needs to be carried out with the default factory parameters.

### 2.1 Equipment Preparation

The following materials are required for this test:

- M31-AAAX4440G
- 12V Switching Power Supply
- USB to RS485
- PC
- One network cable
- Several cables

### 2.2 Device Connection

#### 2.2.1 RS485 Connection

**Note:** When the 485 bus transmits high-frequency signals, the signal wavelength is shorter than the transmission line. The signal will form a reflected wave at the end of the transmission line, interfering with the original signal. Therefore, a terminal resistor needs to be added at the end of the transmission line to prevent the signal from being reflected after reaching the end of the transmission line. The terminal resistor should be the same as the impedance of the communication cable, with a typical value of 120 ohms. Its function is to match the bus impedance and improve the anti-interference and reliability of data communication.

#### 2.2.2 DI Connection

**Note:** DI is NPN or PNP active input, and the voltage range only supports 12V~24V.

#### 2.2.3 AI Connection

**Single-ended analog current acquisition:**

**Note:** AI is used together with the COM port selected by the adjacent wireframe.

**Differential analog current acquisition:**

**Differential analog voltage acquisition:**

#### 2.2.4 DO Connection

**Notes:**
1. A single relay supports a maximum of 5A.
2. The maximum total current of each group (same COM common terminal) supports 8A.

#### 2.2.5 AO Connection

#### 2.2.6 Simple Use

**Wiring:** Connect the computer to the RS485 interface of M31-AAAX4440G via USB to RS485, A to A, B to B.

**Network connection:** Plug the network cable into the RJ45 port and connect it to the PC.

**Power supply:** Use a DC-12V switching power supply (DC 9~36V) to power the M31-AAAX4440G.

### 2.3 Parameter Configuration

**Step 1:** Change the computer's IP address to be consistent with the device. Here I change it to 192.168.3.100 to ensure that it is in the same network segment as the device and the IP address is different. If you cannot connect to the device after the above steps, please turn off the firewall and try again.

**Step 2:** Open the network assistant, select TCP client, enter the remote host IP 192.168.3.7 (default parameters), enter the port number 502 (default parameters), and select HEX to send.

### 2.4 Control Testing

#### 2.4.1 Modbus TCP Control

Use the network assistant to control the first DO output of M31-AAAX4440G.

Other functions can be tested by the following instructions:

| Function (function code) | Instruction |
|--------------------------|-------------|
| The first coil is closed (0x05) | 01 00 00 00 00 06<br>01 05 00 00 FF 00 |
| Control 4-way DO full open instruction (0x0F) | 02 00 00 00 00 08<br>01 0F 00 00 00 04<br>01 0F |
| Control 4-way DO full-off instruction (0x0F) | 02 00 00 00 00 08<br>01 0F 00 00 00 04<br>01 00 |
| Read 4-channel DI status (0x02) | 01 00 00 00 00 06<br>01 02 00 00 00 04 |
| Read 4-channel DO status (0x01) | 01 00 00 00 00 06<br>01 01 00 00 00 04 |

#### 2.4.2 Modbus RTU Control

Use the serial port assistant to control the first DO output of M31-AAAX4440.

Other functions can be tested by the following instructions:

| Function (function code) | Instruction |
|--------------------------|-------------|
| The first coil is closed (0x05) | 01 05 00 00 FF 00 8C 3A |
| Control 4-way DO full open instruction (0x0F) | 01 0F 00 00 00 04 01 0F 7E 92 |
| Control 4-way DO full-off instruction (0x0F) | 01 0F 00 00 00 04 01 00 3E 96 |
| Read 4-channel DI status (0x02) | 01 02 00 00 00 04 79 C9 |
| Read 4-channel DO status (0x01) | 01 01 00 00 00 04 3D C9 |

---

## Chapter 3: Technical Indicators

### 3.1 Specifications

| Category | Name | Parameter |
|----------|------|-----------|
| **Power Supply** | Operating voltage | DC 9～36V |
| | Power indicator | PWR red LED indicator |
| **Communication** | Communication interface | RJ45, RS485 |
| | Baud rate | 9600bps (Optional) |
| | Communication Protocol | Standard Modbus TCP, Modbus RTU protocols |
| | MODBUS Device Address | Can be modified through Modbus command, host computer and hardware dial |
| **DI Input** | Input Type | NPN, PNP |
| | Input voltage | 12~24V |
| | Input Impedance | 7.2kΩ |
| | Collection frequency | Max 1K Hz |
| | Input Instructions | DI green LED indicator |
| **AI Input** | Acquisition characteristics | Single-ended input/differential input (optional) |
| | Input Type | Single-ended current: 0-20mA, 4-20mA<br>Differential Current: 0-20mA, 4-20mA, ±20mA<br>Differential Voltage: 0-5V, ±5V, 0-10V, ±10V |
| | AI Resolution | 16 bits (differential) / 12 bits (single-ended) |
| | AI Precision | 1‰ (differential) / 3‰ (single-ended) |
| | Collection frequency | Single-ended maximum 100Hz / differential maximum 40Hz |
| | Input Instructions | AI green LED indicator |
| **DO Output** | DO output type | Type A relay (normally open) |
| | DO output mode | Level output |
| | Relay contact capacity | 5A 30VDC, 5A 250VAC (the total current of the same COM common terminal supports a maximum of 8A) |
| | Output indication | DO green LED indicator |
| **AO Output** | Output Type | 0-20mA, 4-20mA |
| | AO output accuracy | 3‰ |
| | Input Instructions | AO green LED indicator |
| **Other** | Product size | 110mm × 40mm × 100mm (Length×Width×Height) |
| | Working temperature and humidity | -40 ～ +85℃, 5% ～ 95%RH (No condensation) |
| | Storage temperature and humidity | -40 ～ +105℃, 5% ～ 95%RH (No condensation) |
| | Installation | Positioning holes, guide rail installation |

### 3.2 Device Default Parameters

| Category | Name | Parameter |
|----------|------|-----------|
| **Basic parameters** | Modbus Address | 1 |
| | Baud rate | 9600bps (8 options available) |
| | Check digit | None (default), Odd, Even |
| | Data bits | 8 |
| | Stop bits | 1 |
| | DI Filter parameters | 6 |
| | AI Filter parameters | 6 |
| **Network parameters** | Working Mode | TCP server (up to 5 client connections) |
| | DHCP | closure |
| | Gateway Address | 192.168.3.1 |
| | Subnet Mask | 255.255.255.0 |
| | Local IP | 192.168.3.7 |
| | Local port | 502 |
| | Target IP | 192.168.3.3 |
| | Destination Port | 502 |
| | DNS Server | 114.114.114.114 |
| | Local MAC | Determined by chip (fixed) |

### 3.3 Dimensional Drawing

Product dimensions: 110mm × 40mm × 100mm (Length × Width × Height)

### 3.4 Ports, Buttons and LED Indicators

**Note:** Only the latest version (main unit V1.2, expansion module V2.0) has AI indicator light and engraving.

#### 3.4.1 M31-AAAX4440G

**Port and Button Description:**

| Symbol | Name | Function/Description |
|--------|------|---------------------|
| AI1 | AI1 analog input | AI1 analog input interface, used in conjunction with COMA |
| AI2 | AI2 analog input | AI2 analog input interface, used in conjunction with COMA |
| AI3 | AI3 analog input | AI3 analog input interface, used in conjunction with COMA |
| AI4 | AI4 analog input | AI4 analog input interface, used in conjunction with COMA |
| COMA | AI analog input common terminal | AI1-AI4 share the COMA public terminal |
| DI1 | DI1 switch input | DI1 switch input interface, used in conjunction with COMB |
| DI2 | DI2 switch input | DI2 switch input interface, used in conjunction with COMB |
| COMB | DI switch input common terminal | DI1-DI2 share the COMB common terminal |
| DI3 | DI3 switch input | DI3 switch input interface, used in conjunction with COMC |
| DI4 | DI4 switch input | DI4 switching input interface, used in conjunction with COMC |
| COMC | DI switch input common terminal | DI3-DI4 share the COMC common port |
| DO1 | DO1 switch output | DO1 switching output interface, used in conjunction with COM1 |
| COM1 | COM terminal of DO1 | COM terminal of DO1 |
| DO2 | DO2 switch output | DO2 switch output interface, used in conjunction with COM2 |
| COM2 | COM terminal of DO2 | COM terminal of DO2 |
| DO3 | DO3 switch output | DO3 switching output interface, used in conjunction with COM3 |
| COM3 | COM terminal of DO3 | COM terminal of DO3 |
| DO4 | DO4 switch output | DO4 switching output interface, used in conjunction with COM4 |
| COM4 | COM terminal of DO4 | COM terminal of DO4 |
| Reload | Factory reset/auto-negotiation | Press and hold for 5-10 seconds to restore factory settings; double-click within 2 seconds to automatically negotiate the expansion module |
| A(RS485) | RS485 A interface | RS485 A interface |
| B(RS485) | RS485 B interface | RS485 B interface |
| G(RS485) | RS485G interface | RS485G interface |
| PE | ground | ground |
| V-(DC9-36V) | Negative pole of power supply | DC (9-36V) power supply negative interface |
| V+(DC9-36V) | Positive pole of power supply | DC (9-36V) power supply positive interface |
| LAN1 | Network port | Standard RJ45 network cable interface |

**Indicator Light Description:**

| Symbol | Name | Function/Description |
|--------|------|---------------------|
| PWR | Power Indicator | Red LED light; on: the system power supply is normal; off: the system power supply is abnormal |
| LINK | Link indicator | Yellow LED light; on: there is a link; off: no link; flashing quickly when there is data interaction |
| STA | Status Indicator | Blue LED light; flashes alternately to indicate normal operation; always on or off indicates abnormal device status |
| DI1 | DI1 input indicator light | Green LED light; on: DI1 valid input; off: DI1 invalid input |
| DI2 | DI2 input indicator light | Green LED light; on: DI2 valid input; off: DI2 invalid input |
| DI3 | DI3 input indicator light | Green LED light; on: DI3 valid input; off: DI3 invalid input |
| DI4 | DI4 input indicator light | Green LED light; on: DI4 valid input; off: DI4 invalid input |
| DO1 | DO1 output indicator light | Green LED light; on: DO1 relay is closed; off: DO1 relay is open |
| DO2 | DO2 output indicator light | Green LED light; on: DO2 relay is closed; off: DO2 relay is open |
| DO3 | DO3 output indicator light | Green LED light; on: DO3 relay is closed; off: DO3 relay is open |
| DO4 | DO4 output indicator light | Green LED light; on: DO4 relay is closed; off: DO4 relay is off |
| AI1 | AI1 input indicator | Green LED light; On: Normal input reaches 1% or more of the range; Off: No effective access; Fast flashing: Exceeds the range by 10% |
| AI2 | AI2 input indicator | Green LED light; On: Normal input reaches 1% or more of the range; Off: No effective access; Fast flashing: Exceeds the range by 10% |
| AI3 | AI3 input indicator | Green LED light; On: Normal input reaches 1% or more of the range; Off: No effective access; Fast flashing: Exceeds the range by 10% |
| AI4 | AI4 input indicator | Green LED light; On: Normal input reaches 1% or more of the range; Off: No effective access; Fast flashing: Exceeds the range by 10% |

### 3.5 DIP Switch

**Device address composition:** hardware address + software offset address

The default device address is: 1 (hardware address 0 + software address 1 = device address 1).

**Device address setting range:** 1~255

**Hardware address:** in binary form, implemented by the DIP switch (4-digit) DIP setting (factory default is 0). For example, if DIP codes 1, 2, and 3 are set to ON, the hardware address is 1+2+4=7, and the hardware address adjustment range is (0-15).

**Software Address:** This is achieved by the Offset Address set by the Configurator software (factory default is 1). For example, if the hardware address is set to 5 and the software address is set to 113, the device address is 118 (the maximum value of the software address is 240, and the save will not take effect if the software address exceeds 240).

---

## Chapter 4: Product Function Introduction

### 4.1 IO Extensions

**Note:** During the splicing of the equipment, please do not operate with electricity, otherwise it is easy to cause damage to the equipment!

The M31 series distributed I/O host adopts an extensible structure design, in which the IO expansion module can be used for expansion with the M31 series host. Only need to dock the IO expansion module with the host slot, and then slide down the lock to firmly connect the host and the IO expansion module together.

**Installation Steps:**

1. First, ensure that the host is not powered on, ensure that the host slide buckle is dialed at UNLK, and then connect the IO expansion module to the host.

2. After the IO expansion module is connected, dial the host slider to the LOCK, then power on the host, then plug in the network cable, and use the automatic negotiation function through the host computer (or double-click the Reload button on the device within two seconds, it can also be automatically negotiated), after the negotiation is successful, the IO expansion module can be operated through the serial port or network port on the host.

**Note:** Splicing a new I/O expansion module or removing an already negotiated I/O expansion module requires automatic negotiation to ensure the order and status self-test of the overall device.

### 4.2 DI Input

#### 4.2.1 Input Filtering

When switching the input DI to collect the signal, it is necessary to maintain multiple sampling cycles before confirmation. The filter parameters can be set in the range of 1~16 (6 sampling cycles by default, 6×1kHz). It can be configured via command or host computer.

### 4.3 DO Output

The output mode of the relay.

### 4.4 AI Input

#### 4.4.1 AI Scope

**Single-Ended Analog Input AI Measurement Current Signal:**

The acquisition range is 0~20mA or 4~20mA, the accuracy is 3‰, and the resolution is 12 bits. It adopts a single-ended input, with a sampling frequency of 100Hz and an input impedance of 100Ω.

Set the sampling range for all AI channels, the valid value is 0~1 (default 0).
- Set to 0: 0~20mA
- Set to 1: 4~20mA

**Differential Analog Input AI Measurement Current Signal:**

The acquisition range is 0~20mA or 4~20mA or ±20mA, the accuracy is 1‰, and the resolution is 16 bits. Differential input with 40Hz sampling frequency.

Set the sampling range for all AI channels, the valid value is 0~2 (default 0).
- Set to 0: 0~20mA
- Set to 1: 4~20mA
- Set to 2: ±20mA

**Differential Analog Input AI Measurement Voltage Signal:**

The acquisition range is 0~5V or 0~10V or ±5V or ±10V, the accuracy is 1‰, and the resolution is 16 bits. Differential input with 40Hz sampling frequency.

Set the sampling range for all AI channels, with valid values of 3~6 (default 5).
- Set to 3: 0~5V
- Set to 4: ±5V
- Set to 5: 0~10V
- Set to 6: ±10V

**Note: AI configuration description**

1. The AI sampling range of each channel can be set. When the AI channel sampling range is configured to 4~20mA sampling, if the current signal is lower than 3.5mA, it will be displayed as 0, and when it is higher than 3.5 mA and lower than 4mA, it will be displayed as 4. There is no conversion limit for signals greater than 20mA, but not more than 25mA (there is a risk of equipment damage if the signal exceeds 25mA).

2. The starting address of the AI channel sampling range parameter is 0x0DAC, the register type is the holding register, and the function code is 0x06 and 0x10. When an AI channel sampling range parameter is written, if the value of the parameter is not within the specified range, it will not take effect, and Modbus will not return an error command.

#### 4.4.2 The Shaping Value, Floating-Point Value, and Process Quantity Input by AI

There are three ways to read the analog signal collected by the device:

1. **Read the AI quantity shaping value** and directly convert it to the input current or voltage. The start address of the AI quantity integer value register is 0x0000, the register type is the input register, and the read function code is 0x04. This method returns a value for one channel in one register.

   - **Single-ended current:** The value read is 0~20000. Current = Quantity Value / 1000 (mA)
   - **Differential Current:** The read value is -20000~20000. Current = Quantity Value / 1000 (mA)
   - **Differential voltage:** The value read is -10000~10000. Voltage = Quantity Value / 1000 (V)

2. **Read the floating-point value of the AI engineering quantity**, and use the IEEE754 conversion tool to convert the hexadecimal data to a floating-point number to get the input current or voltage. The start address of the AI quantity integer value register is 0x03E8, the register type is the input register, and the read function code is 0x04. This method returns two registers representing 1 channel.

3. **Read the amount of AI process.** The AI engineering register starts from 0x0BB8, the register type is the input register, and the read function code is 0x04. This method returns 1 register for 1 channel. That is: -27648~27648 represents -10V~+10V/-20mA~20mA

#### 4.4.3 AI Filtering Parameters

You can set the filtering parameters of the AI channel, the effective value is 1-16, and the default value is 6.

**Filter Parameters:**

1. All AI channels share a filtering parameter, and the higher the parameter value, the more stable the output value is, and the more sluggish the response.

2. The AI channel filtering parameter address is 0x0DA2, and the register type is the holding register. Function code 0x06, 0x10.

3. When the AI filter parameter is written, if the written parameter value is not within the range of 1~16, it will automatically take the nearest value and write it. If the write filter parameter is 0, the device will take 1 as the filter parameter, and Modbus will not return an error instruction.

### 4.5 AO Output

#### 4.5.1 AO Range

Analog current output, range 0~20mA or 4~20mA, accuracy 3‰, resolution 16 bits, input impedance 500Ω.

Sets the output range for a single AO channel, with valid values of 1 and 0 (default 0).
- Set to 0: 0~20mA
- Set to 1: 4~20mA

**Note: AO configuration description**

1. The AO output range of each channel can be set.

2. The AO channel output range parameter starts from 0x0DAC, the register type is the holding register, and the function code 0x06 and 0x10. If the parameter of the AI channel sampling range is not within the range of 0~1, it will automatically take the nearest value and write it. If the parameter of the writing sampling range is 2, the device will take 1 as the parameter of the sampling range, and Modbus will not return an error command.

#### 4.5.2 AO Outputs the Quantity Shaping Value, the Quantity Floating-Point Value, and the Process Quantity Register

There are three ways to read and control the size of the current signal:

1. **Read and control the AO engineering quantity shaping value**, and directly convert the output current to obtain it. The AO value register starts from 0x0000, the register type is hold, the function code is read to 0x03, and the function code is written to 0x06, 0x10. The value returned by this method represents 1 channel in one register, and the value is 0~20000. Current = Engineering Value / 1000 (mA)

2. **Read and control the floating-point value of AO engineering quantity**, and use the IEEE754 conversion tool to convert the hexadecimal data into floating-point number to obtain the current. AO quantities floating-point registers start from 0x03E8, register type is hold register, read function code is 0x03, write function code 0x06, 0x10. This method returns two registers representing 1 channel.

3. **Read and control process quantity shaping values.** The AO register starts from 0x01F4, the register type is hold, the function code is read to 0x03, and the function code is written to 0x06, 0x10. This method returns 1 register for 1 channel. That is: 0~27648 represents 0mA~20mA

### 4.6 Online Monitoring

The device can be monitored for abnormalities by means of relevant registers:

| Register | Address (Hex) | Address (Dec) | Zone | Description | Function Code |
|----------|---------------|---------------|------|-------------|---------------|
| Device exception code | 0x7587 | 4-30088 | Zone 4 | Check the exception code of the current device. 0 = no abnormality, 1 = slave does not reply, 2 = expansion module is in the wrong order | R: 0x03 |
| The extension module is incorrectly labeled | 0x7588 | 4-30089 | Zone 4 | Check which extension module has not replied. Two registers 32 bits, representing the expansion modules in order. If the bit on the corresponding serial number is 1, it means that the extension module is abnormal. | R: 0x03 |

### 4.7 Module Information

#### 4.7.1 Basic Parameters

1. **Modbus address:** The device address is set to 1 by default, and the address can be modified, and the address range is 1-247.
2. **Serial baud rate:** 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400bps (8 kinds of options)
3. **Serial port check digit:** NONE, ODD, EVEN optional
4. **DI filter parameters:** The filter parameters can be set in the range of 1~16 (default 6 sampling periods, 6×1kHz)
5. **AI Filtering Parameters:** You can set the filtering parameters of the AI channel, the effective value is 1-16, and the default value is 6.

#### 4.7.2 Network Parameters

Unless otherwise specified, the following network-related parameters default to IPv4 related parameters.

1. **Working Mode:** Toggles the working mode of the module. Server: The device is equivalent to a server, waiting for the user's client to connect, and the maximum number of connections is 5. Client: The device actively connects to the destination IP address and port set by the user.
2. **DHCP:** Configure the method for the device to obtain an IP address: static and dynamic.
3. **Gateway Address:** Gateway
4. **Subnet mask:** The address mask, which can be read and written.
5. **Local IP:** The IP address of the device, which can be read or written.
6. **Local Port:** The port number of the device, which can be read and written.
7. **Destination IP:** The destination IP address or domain name to which the device is connected when the device is working in client mode.
8. **Destination Port:** The destination port to which the device is connected when the device is working in client mode.
9. **DNS server:** The device is in client mode and resolves the domain name of the server.
10. **Network Modbus protocol:** Modbus TCP and Modbus RTU protocols can be selected on the network port.

### 4.8 MODBUS Parameter Configuration

**Notes:**

1. DI, DO, AI, AO registers are continuous. For example, an 8DI model host spliced with an 8DI model expansion module, then the DI status register of the expansion module is continued from the host 0x0000-0x0007, that is, 0x0008-0x0010.
2. 0x_ denotes hexadecimal.
3. The M31-AAAX4440G model is used as an example to demonstrate the continuity of the registers after splicing.
4. AO uses the M31-XAXA0404G model as an example to show the continuity of the registers after splicing.

#### 4.8.1 List of DI Registers

**DI Status Registers:**

| Name | Access Location | Register Address (Hex) | Register Address (Dec) | Register Area | Related Function Codes | Default State |
|------|-----------------|------------------------|------------------------|---------------|------------------------|---------------|
| DI1 | host | 0x0000 | 1-0001 | Zone 1 | R: 0x02 | 0 |
| DI2 | host | 0x0001 | 1-0002 | Zone 1 | R: 0x02 | 0 |
| DI3 | host | 0x0002 | 1-0003 | Zone 1 | R: 0x02 | 0 |
| DI4 | host | 0x0003 | 1-0004 | Zone 1 | R: 0x02 | 0 |
| DI5 | IO expansion module | 0x0004 | 1-0005 | Zone 1 | R: 0x02 | 0 |

**DI Filter Registers:**

| Name | Register Address (Hex) | Register Address (Dec) | Register Type | Data Scope/Description | Related Function Codes | Default State |
|------|------------------------|------------------------|---------------|------------------------|------------------------|---------------|
| DI channel filtering parameters | 0x0DA3 | 4-3492 | Hold registers | Filtering parameters for all DI channels, Valid values 1-16 | R: 0x03, W: 0x06, 0x10 | 6 |

#### 4.8.2 List of DO Registers

**DO Status Registers:**

| Name | Access Location | Register Address (Hex) | Register Address (Dec) | Register Area | Related Function Codes | Default State |
|------|-----------------|------------------------|------------------------|---------------|------------------------|---------------|
| DO1 | host | 0x0000 | 0-0001 | Zone 0 | R: 0x01, W: 0x05, 0x0F | 0 |
| DO2 | host | 0x0001 | 0-0002 | Zone 0 | R: 0x01, W: 0x05, 0x0F | 0 |
| DO3 | host | 0x0002 | 0-0003 | Zone 0 | R: 0x01, W: 0x05, 0x0F | 0 |
| DO4 | host | 0x0003 | 0-0004 | Zone 0 | R: 0x01, W: 0x05, 0x0F | 0 |
| DO5 | IO expansion module | 0x0004 | 0-0005 | Zone 0 | R: 0x01, W: 0x05, 0x0F | 0 |

#### 4.8.3 List of AI Registers

**AI Quantity Shaping Value Register:**

| Name | Access Location | Register Address (Hex) | Register Address (Dec) | Register Area | Data Range/Description | Related Function Codes | Default State |
|------|-----------------|------------------------|------------------------|---------------|------------------------|------------------------|---------------|
| AI1 | host | 0x0000 | 3-0001 | Zone 3 | Engineering quantity 0-20000 represents 0-20mA, 2-byte integer number in (uA) | R: 0x04 | 0 |
| AI2 | host | 0x0001 | 3-0002 | Zone 3 | Engineering quantity 0-20000 represents 0-20mA, 2-byte integer number in (uA) | R: 0x04 | 0 |
| AI3 | host | 0x0002 | 3-0003 | Zone 3 | Engineering quantity 0-20000 represents 0-20mA, 2-byte integer number in (uA) | R: 0x04 | 0 |
| AI4 | host | 0x0003 | 3-0004 | Zone 3 | Engineering quantity 0-20000 represents 0-20mA, 2-byte integer number in (uA) | R: 0x04 | 0 |
| AI5 | IO expansion module | 0x0004 | 3-0005 | Zone 3 | Engineering quantity 0-20000 represents 0-20mA, 2-byte integer number in (uA) | R: 0x04 | 0 |

**AI Floating-Point Value Registers:**

| Name | Access Location | Register Address (Hex) | Register Address (Dec) | Register Area | Data Scope/Description | Related Function Codes | Default State |
|------|-----------------|------------------------|------------------------|---------------|------------------------|------------------------|---------------|
| AI1 | host | 0x03E8 | 3-1001 | Zone 3 | Floating-point value of analog signal, 4-byte floating-point number in (mA) | R: 0x04 | 0 |
| AI2 | host | 0x03EA | 3-1003 | Zone 3 | Floating-point value of analog signal, 4-byte floating-point number in (mA) | R: 0x04 | 0 |
| AI3 | host | 0x03EC | 3-1005 | Zone 3 | Floating-point value of analog signal, 4-byte floating-point number in (mA) | R: 0x04 | 0 |
| AI4 | host | 0x03EE | 3-1007 | Zone 3 | Floating-point value of analog signal, 4-byte floating-point number in (mA) | R: 0x04 | 0 |
| AI5 | IO expansion module | 0x03F0 | 3-1009 | Zone 3 | Floating-point value of analog signal, 4-byte floating-point number in (mA) | R: 0x04 | 0 |

**AI Process Registers:**

| Name | Access Location | Register Address (Hex) | Register Address (Dec) | Register Area | Data Scope/Description | Related Function Codes | Default State |
|------|-----------------|------------------------|------------------------|---------------|------------------------|------------------------|---------------|
| AI1 | host | 0x0BB8 | 3-3001 | Zone 3 | Analog signal integer value, 2 bytes | R: 0x04 | 0 |
| AI2 | host | 0x0BB9 | 3-3002 | Zone 3 | Analog signal integer value, 2 bytes | R: 0x04 | 0 |
| AI3 | host | 0x0BBA | 3-3003 | Zone 3 | Analog signal integer value, 2 bytes | R: 0x04 | 0 |
| AI4 | host | 0x0BBB | 3-3004 | Zone 3 | Analog signal integer value, 2 bytes | R: 0x04 | 0 |
| AI5 | IO expansion module | 0x0BBC | 3-3005 | Zone 3 | Analog signal integer value, 2 bytes | R: 0x04 | 0 |

**AI Filter Registers:**

| Name | Register Address (Hex) | Register Address (Dec) | Register Area | Data Scope/Description | Related Function Codes | Default State |
|------|------------------------|------------------------|---------------|------------------------|------------------------|---------------|
| AI channel filtering parameters | 0x0DA2 | 4-3491 | Zone 4 | Filtering parameters for all AI channels, Valid values 1-16 | R: 0x03, W: 0x06, 0x10 | 6 |

**AI Sampling Range Registers:**

| Name | Access Location | Register Address (Hex) | Register Address (Dec) | Register Area | Data Scope/Description | Related Function Codes | Default State |
|------|-----------------|------------------------|------------------------|---------------|------------------------|------------------------|---------------|
| AI1 sampling range | host | 0x0DAC | 4-3501 | Zone 4 | Valid values are 0 and 1, 0 means 0-20mA, 1 means 4-20mA | R: 0x03, W: 0x06, 0x10 | 0 |
| AI2 sampling range | host | 0x0DAD | 4-3502 | Zone 4 | Valid values are 0 and 1, 0 means 0-20mA, 1 means 4-20mA | R: 0x03, W: 0x06, 0x10 | 0 |
| AI3 sampling range | host | 0x0DAE | 4-3503 | Zone 4 | Valid values are 0 and 1, 0 means 0-20mA, 1 means 4-20mA | R: 0x03, W: 0x06, 0x10 | 0 |
| AI4 sampling range | host | 0x0DAF | 4-3504 | Zone 4 | Valid values are 0 and 1, 0 means 0-20mA, 1 means 4-20mA | R: 0x03, W: 0x06, 0x10 | 0 |
| AI5 sampling range | IO expansion module | 0x0DB0 | 4-3505 | Zone 4 | Valid values are 0 and 1, 0 means 0-20mA, 1 means 4-20mA | R: 0x03, W: 0x06, 0x10 | 0 |

#### 4.8.4 List of AO Registers

**AO Integer Value Register:**

| Name | Access Location | Register Address (Hex) | Register Address (Dec) | Register Area | Data Scope/Description | Related Function Codes | Default State |
|------|-----------------|------------------------|------------------------|---------------|------------------------|------------------------|---------------|
| AO1 | host | 0x0000 | 4-0001 | Zone 4 | Engineering quantity 0-20000 represents 0-20mA, 2-byte integer number in (uA) | R: 0x03, W: 0x06, 0x10 | 0 |
| AO2 | host | 0x0001 | 4-0002 | Zone 4 | Engineering quantity 0-20000 represents 0-20mA, 2-byte integer number in (uA) | R: 0x03, W: 0x06, 0x10 | 0 |
| AO3 | host | 0x0002 | 4-0003 | Zone 4 | Engineering quantity 0-20000 represents 0-20mA, 2-byte integer number in (uA) | R: 0x03, W: 0x06, 0x10 | 0 |
| AO4 | host | 0x0003 | 4-0004 | Zone 4 | Engineering quantity 0-20000 represents 0-20mA, 2-byte integer number in (uA) | R: 0x03, W: 0x06, 0x10 | 0 |
| AO5 | IO expansion module | 0x0004 | 4-0005 | Zone 4 | Engineering quantity 0-20000 represents 0-20mA, 2-byte integer number in (uA) | R: 0x03, W: 0x06, 0x10 | 0 |

**AO Floating-Point Value Registers:**

| Name | Access Location | Register Address (Hex) | Register Address (Dec) | Register Area | Data Scope/Description | Related Function Codes | Default State |
|------|-----------------|------------------------|------------------------|---------------|------------------------|------------------------|---------------|
| AO1 | host | 0x03E8 | 4-1001 | Zone 4 | Floating-point value of analog signal, 4-byte floating-point number in (mA) | R: 0x03, W: 0x06, 0x10 | 0 |
| AO2 | host | 0x03EA | 4-1003 | Zone 4 | Floating-point value of analog signal, 4-byte floating-point number in (mA) | R: 0x03, W: 0x06, 0x10 | 0 |
| AO3 | host | 0x03EC | 4-1005 | Zone 4 | Floating-point value of analog signal, 4-byte floating-point number in (mA) | R: 0x03, W: 0x06, 0x10 | 0 |
| AO4 | host | 0x03EE | 4-1007 | Zone 4 | Floating-point value of analog signal, 4-byte floating-point number in (mA) | R: 0x03, W: 0x06, 0x10 | 0 |
| AO5 | IO expansion module | 0x03F0 | 4-1009 | Zone 4 | Floating-point value of analog signal, 4-byte floating-point number in (mA) | R: 0x03, W: 0x06, 0x10 | 0 |

**AO Process Quantity Registers:**

| Name | Access Location | Register Address (Hex) | Register Address (Dec) | Register Area | Data Scope/Description | Related Function Codes | Default State |
|------|-----------------|------------------------|------------------------|---------------|------------------------|------------------------|---------------|
| AO1 | host | 0x01F4 | 3-0501 | Zone 4 | Analog signal integer value, 2 bytes | R: 0x03, W: 0x06, 0x10 | 0 |
| AO2 | host | 0x01F5 | 3-0502 | Zone 4 | Analog signal integer value, 2 bytes | R: 0x03, W: 0x06, 0x10 | 0 |
| AO3 | host | 0x01F6 | 3-0503 | Zone 4 | Analog signal integer value, 2 bytes | R: 0x03, W: 0x06, 0x10 | 0 |
| AO4 | host | 0x01F7 | 3-0504 | Zone 4 | Analog signal integer value, 2 bytes | R: 0x03, W: 0x06, 0x10 | 0 |
| AO5 | IO expansion module | 0x01F8 | 3-0505 | Zone 4 | Analog signal integer value, 2 bytes | R: 0x03, W: 0x06, 0x10 | 0 |

**AO Output Range Registers:**

| Name | Access Location | Register Address (Hex) | Register Address (Dec) | Register Area | Data Scope/Description | Related Function Codes | Default State |
|------|-----------------|------------------------|------------------------|---------------|------------------------|------------------------|---------------|
| AO1 output range | host | 0x1194 | 4-4501 | Zone 4 | Valid values are 0 and 1, 0 means 0-20mA, 1 means 4-20mA | R: 0x03, W: 0x06, 0x10 | 0 |
| AO2 output range | host | 0x1195 | 4-4502 | Zone 4 | Valid values are 0 and 1, 0 means 0-20mA, 1 means 4-20mA | R: 0x03, W: 0x06, 0x10 | 0 |
| AO3 output range | host | 0x1196 | 4-4503 | Zone 4 | Valid values are 0 and 1, 0 means 0-20mA, 1 means 4-20mA | R: 0x03, W: 0x06, 0x10 | 0 |
| AO4 output range | host | 0x1197 | 4-4504 | Zone 4 | Valid values are 0 and 1, 0 means 0-20mA, 1 means 4-20mA | R: 0x03, W: 0x06, 0x10 | 0 |
| AO5 output range | IO expansion module | 0x1198 | 4-4505 | Zone 4 | Valid values are 0 and 1, 0 means 0-20mA, 1 means 4-20mA | R: 0x03, W: 0x06, 0x10 | 0 |

#### 4.8.5 Module-Related Registers

| Register Function | Register Address (Hex) | Register Address (Dec) | Register Area | Number | Data Range/Remarks | Related Function Codes |
|-------------------|------------------------|------------------------|---------------|--------|-------------------|------------------------|
| Serial baud rate code | 0x7530 | 4-30001 | Zone 4 | 1 | 1:2400, 2:4800, 3:9600, 4:19200, 5:38400, 6:57600, 7:115200, 8:230400 | R: 0x03, W: 0x06, 0x10 |
| Serial port check digit | 0x7531 | 4-30002 | Zone 4 | 1 | 0:NONE, 1:ODD, 2:EVEN | R: 0x03, W: 0x06, 0x10 |
| Network working mode | 0x7532 | 4-30003 | Zone 4 | 1 | 0:TCPS, 1:TCPC, 2:UDPS, 3:UDPC | R: 0x03, W: 0x06, 0x10 |
| DHCP | 0x7533 | 4-30004 | Zone 4 | 1 | 0: Off, 1: On | R: 0x03, W: 0x06, 0x10 |
| The MAC address of the device | 0x7534 | 4-30005 | Zone 4 | 3 | | R: 0x03 |
| The local IP address | 0x7537 | 4-30008 | Zone 4 | 2 | | R: 0x03, W: 0x06, 0x10 |
| Subnet mask | 0x7539 | 4-30010 | Zone 4 | 2 | | R: 0x03, W: 0x06, 0x10 |
| Gateway address | 0x753B | 4-30012 | Zone 4 | 2 | | R: 0x03, W: 0x06, 0x10 |
| DNS server address | 0x753D | 4-30014 | Zone 4 | 2 | | R: 0x03, W: 0x06, 0x10 |
| Native port | 0x7541 | 4-30018 | Zone 4 | 1 | 0-65535 | R: 0x03, W: 0x06, 0x10 |
| Destination IP/domain name | 0x7542 | 4-30019 | Zone 4 | 64 | A maximum 128-byte string, and the domain name is also represented as a string | R: 0x03, W: 0x06, 0x10 |
| Destination server port | 0x7582 | 4-30083 | Zone 4 | 1 | 1-65535 | R: 0x03, W: 0x06, 0x10 |
| Network Modbus protocol | 0x7583 | 4-30084 | Zone 4 | 1 | Set to 1 when network data is TCP data, 0 when network data is RTU data | R: 0x03, W: 0x06, 0x10 |
| Address Negotiation Write Register Protection | 0x7584 | 4-30085 | Zone 4 | 1 | This write-protected register needs to be turned on before sending the address negotiation instruction. Write 1: Write protection registers are opened | R: 0x03, W: 0x06, 0x10 |
| Address negotiation registers | 0x7585 | 4-30086 | Zone 4 | 1 | Write 1: indicates that the address negotiation begins | R: 0x03, W: 0x06, 0x10 |
| The current negotiation status register | 0x7586 | 4-30087 | Zone 4 | 1 | Check whether the negotiation is complete. 0: The negotiation has not yet been completed, 1: The negotiation is completed | R: 0x03 |
| Device exception code | 0x7587 | 4-30088 | Zone 4 | 1 | Check the exception code of the current device. 0 = no abnormality, 1 = slave does not reply, 2 = expansion module is in the wrong order | R: 0x03 |
| The extension module is incorrectly labeled | 0x7588 | 4-30089 | Zone 4 | 2 | Check which extension module has not replied, a total of two registers 32 bits, representing the expansion modules in order. If the bit on the corresponding serial number is 1, it means that the extension module is abnormal. | R: 0x03 |

**Note:** According to the usage requirements, some software (such as Configurator) 16 to 10 needs +1 to operate the register (the 10 base in the table has been +1).

---

## Chapter 5: Upper Computer

### 5.1 Connect & Control

**Step 1:** Connect the device to the host computer

1. The device can be configured by selecting the interface (serial/network port). If you select a network port, you need to select a network card before searching for a device.

2. If you select serial port, you need to select the corresponding serial number, as well as the same baud rate, data bit, stop bit, check digit and address range search range as the device, and then search.

**Step 2:** Select the corresponding device to perform operations on the corresponding I/O.

### 5.2 Parameter Configuration

1. Connecting devices refer to "Connecting and Control"

2. You can configure the basic parameters and network parameters of the device

3. After the parameters are configured, click Save Parameters, and see a prompt message in the log output that the parameters are successfully saved, and then restart the device. After the restart is completed, the modified parameters will take effect.

---

## Chapter 6: Precautions

1. **Do not splice the device with electricity**, otherwise the device is at risk of damage

2. **Host software V1.1** is incompatible with some expansion modules (GXGXX0800, GXFXX0800, GXXXA0008, GXAXA0404, GXAXX0800 (V2.0), GAAAX4440 (V2.0))

   The **host software V1.2 version** is compatible with all expansion modules. If you need to upgrade, please download the upgrade operation process document from www.cdebyte.com on the official website for the corresponding model.

A complete host contains the host firmware and the expansion module firmware version. How to check the version number:
- **Host:** Check firmware version in device information
- **Expansion Modules:** Check firmware version in module information

---

## Revision History

| Version | Date of Revision | Revision Notes | Maintainers |
|---------|------------------|----------------|-------------|
| 1.0 | 2025.5.6 | Initial release | LT |

---

## Chapter 7: About Us

**Technical support:** service@cdebyte.com

**Documents and RF Setting download link:** www.cdebyte.com

Thank you for using Ebyte products! Please contact us with any questions or suggestions: info@cdebyte.com

---

**Contact Information:**

- **Phone:** +86 4000-330-990
- **Web:** www.cdebyte.com
- **Address:** B5 Mould Park, 199# Xiqu Ave, High-tech District, Sichuan, China

---

*The final interpretation right belongs to Chengdu Yibaite Electronic Technology Co., Ltd*
