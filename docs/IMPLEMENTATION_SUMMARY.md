# ESP32 Modbus Implementation Summary

**Date**: 2026-01-29

## Overview

Successfully implemented full Modbus RTU read/write functionality with web-based configuration and dashboard for the ESP32-C3.

## Components Implemented

### 1. Modbus Protocol Layer (`modbus_protocol.c/h`)
- CRC-16 calculation and validation
- Request frame building for all Modbus functions
- Response parsing with exception handling
- Support for:
  - Read Coils (0x01)
  - Read Discrete Inputs (0x02)
  - Read Holding Registers (0x03)
  - Read Input Registers (0x04)
  - Write Single Coil (0x05)
  - Write Single Register (0x06)
  - Write Multiple Coils (0x0F)
  - Write Multiple Registers (0x10)

### 2. Device Management (`modbus_devices.c/h`)
- Device configuration structure with up to 4 devices
- Register mapping (up to 50 registers per device)
- NVS storage for persistent configurations
- Register scaling and offset support
- Device status tracking (online/offline/error)
- Poll and error statistics

### 3. Modbus Manager (`modbus_manager.c/h`)
- UART1 driver for RS485 communication
- DE/RE pin control (separate GPIOs)
- Configurable baudrate (default: 9600, 19200, 38400, 115200)
- Automatic retry logic (3 attempts)
- Background polling task
- Read/write functions for all register types

### 4. Web Interface

#### Modbus Configuration Page (`modbus.html`)
- Add/remove devices
- Configure device settings (ID, name, poll interval, baudrate)
- Add/remove registers to devices
- Register configuration (address, type, name, unit, scale, offset, writable)
- Device presets for eAirMD and eWind
- Real-time device status display

#### Dashboard Page (`dashboard.html`)
- Real-time data display from all configured registers
- Value formatting with units and scaling
- Write capability for writable registers
- Auto-refresh functionality
- Device status indicators

#### REST API Endpoints
- `GET /api/modbus/devices` - List all devices
- `POST /api/modbus/devices` - Add new device
- `DELETE /api/modbus/devices/{id}` - Delete device
- `POST /api/modbus/registers` - Add register to device
- `DELETE /api/modbus/devices/{id}/registers/{addr}` - Delete register
- `POST /api/modbus/devices/{id}/write/{addr}` - Write register value

## Hardware Configuration

### XIAO ESP32C3 Pin Assignments
| Signal | GPIO | XIAO Pin | Description |
|--------|-------|------------|-------------|
| TX     | 21    | TX (Back)  | UART1 TX |
| RX     | 20    | RX (Back)  | UART1 RX |
| DE     | 7     | D5 (Front) | Driver Enable |
| RE     | 6     | D4 (Front) | Receiver Enable |

### RS485 Adapter (MAX485)
- Connect ESP32 TX → MAX485 DI
- Connect ESP32 RX → MAX485 RO
- Connect ESP32 DE (GPIO7) → MAX485 DE
- Connect ESP32 RE (GPIO6) → MAX485 RE
- Connect MAX485 A/B to RS485 bus
- Power MAX485 with 5V

## Supported Devices

### eAirMD (Enervent Pingvin)
- Device ID: 1-100
- Default Baudrate: 19200
- Preset includes common temperature and humidity registers
- Supports holding registers (0x03) only

### eWind (Kotilämpö)
- Device ID: 1-100
- Default Baudrate: 9600
- Preset includes common temperature, humidity, and control registers
- Supports coils (0x01) and holding registers (0x03)

## Usage

### Initial Setup
1. Flash firmware to ESP32-C3
2. Connect to WiFi via `/` page (or AP mode)
3. Navigate to `/modbus.html`
4. Add a device (use preset or manual configuration)
5. Add registers to monitor
6. Navigate to `/dashboard.html` to view real-time data

### Adding a Device Preset
1. Go to `/modbus.html`
2. Click "Presets" tab
3. Click "Add eAirMD" or "Add eWind"
4. Device and common registers are automatically configured

### Manual Device Configuration
1. Go to `/modbus.html`
2. Enter device details (ID, name, baudrate, etc.)
3. Click "Add Device"
4. Click "Add Register" for each register to monitor
5. Configure register (address, type, name, unit, scale, offset)
6. Save register
7. Go to `/dashboard.html` to view data

### Writing to Registers
1. On dashboard page, writable registers show input field
2. Enter new value (already scaled)
3. Click "Write"
4. Value is sent to device

## Data Flow

```
Web Dashboard
    ↓
Web Server (REST API)
    ↓
Modbus Devices Manager
    ↓ (polling)
Modbus Manager (UART1)
    ↓ (RS485)
HVAC Devices
```

## Files Created/Modified

### New Files
- `main/modbus_protocol.h` - Protocol layer header
- `main/modbus_protocol.c` - Protocol implementation
- `main/modbus_devices.h` - Device management header
- `main/modbus_devices.c` - Device management
- `main/modbus_manager.h` - Manager header
- `main/modbus_manager.c` - Manager with UART driver
- `main/html/modbus.html` - Configuration page
- `main/html/dashboard.html` - Dashboard page
- `main/html/modbus.js` - JavaScript

### Modified Files
- `main/main.c` - Initialize Modbus components
- `main/web_server.c` - Add Modbus API endpoints
- `main/CMakeLists.txt` - Include new source files
- `docs/PLAN.md` - Update implementation status
- `docs/devices/MAX485_RS485_Module.md` - Update DE/RE wiring

## Technical Details

### Communication Settings
- UART: UART_NUM_1
- Data bits: 8
- Parity: None
- Stop bits: 1
- Timeout: 1000ms
- Retry attempts: 3

### Polling
- Automatic background polling task
- Per-device configurable interval
- Individual register updates
- Statistics tracking (poll count, error count)

### Storage
- All configurations stored in NVS
- Namespace: `modbus_config`
- Automatically saved on changes
- Loaded on startup

### Error Handling
- CRC validation on all responses
- Exception detection and reporting
- Device status tracking
- Automatic retry for failed requests

## Testing Recommendations

1. **Hardware Test**
   - Verify RS485 connections
   - Check DE/RE pin control (should toggle during transmission)
   - Confirm device responds to simple read request

2. **Communication Test**
   - Add one register from device documentation
   - Verify value appears in dashboard
   - Check for CRC errors or timeouts

3. **Write Test**
   - Configure writable register (e.g., setpoint)
   - Write value via dashboard
   - Verify device accepts write

4. **Multiple Devices**
   - Add multiple devices with different IDs
   - Verify all devices are polled
   - Check for bus contention issues

5. **Long-term Test**
   - Monitor for 24+ hours
   - Check memory usage
   - Verify no memory leaks
   - Check polling reliability

## Future Enhancements

- MQTT integration for home automation
- WebSockets for real-time updates
- Historical data logging
- Graph/trend visualization
- Alarm threshold configuration
- Modbus TCP support
- User authentication
- Firmware OTA updates

## Documentation Updates

- Updated MAX485 wiring documentation (DE/RE on separate pins)
- Updated plan document with implementation status
- Created this implementation summary

## Notes

- All code follows ESP-IDF v5.1.6 conventions
- Uses FreeRTOS for task management
- Implements proper error handling throughout
- Ready for MQTT integration (data structures prepared)
- Compatible with standard Modbus RTU devices

---

**Implementation complete and ready for testing!**