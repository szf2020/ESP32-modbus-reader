# ESP32-C3 WiFi Credentials Manager - Implementation Plan

> **Living Document** - Updated as project progresses
> 
> Last Updated: 2025-01-26

## Project Overview

Create a WiFi credentials manager for ESP32-C3 from Seeed Studio that:

- Automatically creates an Access Point (AP) when no WiFi credentials are saved
- Hosts a styled web page for entering WiFi credentials
- Saves credentials to Non-Volatile Storage (NVS)
- Connects to saved WiFi network
- Allows reconfiguration via web interface at device IP address

## Current Status

- [x] Environment check completed
- [x] ESP-IDF v5.1.6 found at `C:\Users\jaakk\esp\v5.1.6\esp-idf`
- [x] Arduino CLI with ESP32 v3.2.0 package detected
- [x] esptool available for flashing
- [x] Python 3.13.1 installed
- [x] ESP32-C3 support confirmed
- [ ] Documentation files created
- [ ] Project structure created
- [ ] ESP-IDF tools installation (if needed)
- [ ] WiFi Manager implementation
- [ ] Web Server implementation
- [ ] NVS Storage implementation
- [ ] Web UI (HTML + Styled CSS)
- [ ] Build and test on ESP32-C3
- [ ] Documentation finalization

## Hardware Requirements

- **Microcontroller**: ESP32-C3 (Seeed Studio)
- **USB Cable**: For power and programming
- **Computer**: Windows with development tools

## Software Requirements

- **ESP-IDF**: v5.1.6+ (located at `C:\Users\jaakk\esp\v5.1.6\esp-idf`)
- **Python**: 3.13.1 (installed)
- **Git**: Installed
- **CMake**: Installed
- **esptool**: Available via Arduino IDE installation

## Architecture

### System Components

```
┌─────────────────────────────────────────────────────┐
│                 ESP32-C3 Application                │
├─────────────────────────────────────────────────────┤
│                                                     │
│  ┌──────────────┐    ┌──────────────┐               │
│  │  WiFi Manager │◄──┤  NVS Storage │               │
│  └──────┬───────┘    └──────────────┘               │
│         │                                           │
│         ▼                                           │
│  ┌──────────────┐    ┌──────────────┐               │
│  │   Web Server │◄──┤  FreeRTOS     │               │
│  └──────┬───────┘    └──────────────┘               │
│         │                                           │
│         ▼                                           │
│  ┌──────────────────────┐                           │
│  │     WiFi Driver      │                           │
│  └──────────────────────┘                           │
│                                                     │
└─────────────────────────────────────────────────────┘
```

### Component Details

#### 1. WiFi Manager (`wifi_manager.c/.h`)

**Responsibilities:**

- Initialize WiFi driver and event loop
- Check NVS for saved credentials
- Manage WiFi mode (AP vs Station)
- Handle connection state transitions
- Provide status to web server

**Functions:**

- `wifi_manager_init()` - Initialize WiFi driver and event handler
- `wifi_manager_start()` - Start WiFi operations based on credentials
- `wifi_manager_connect_ap(ssid, password)` - Connect to AP
- `wifi_manager_start_ap()` - Start AP mode
- `wifi_manager_get_status()` - Get current connection status
- `wifi_manager_event_handler()` - Handle WiFi events

**State Machine:**

```
INIT → Check NVS → Credentials Found? 
                     ├── Yes → Connect to Station → Success/Monitor
                     └── No → Start AP Mode → Wait for Credentials
```

**AP Mode Configuration:**

- SSID: `ESP32-Config`
- Password: `config123`
- IP: `192.168.4.1`
- Channel: 1
- Max connections: 4

**Station Mode:**

- Auto-connect on startup
- Connection timeout: 30 seconds
- Fallback to AP mode on failure

#### 2. Web Server (`web_server.c/.h`)

**Responsibilities:**

- Initialize HTTP server on port 80
- Handle HTTP requests
- Serve static files (HTML, CSS, JS)
- Process form submissions
- Provide API endpoints

**Endpoints:**

- `GET /` - Serve WiFi configuration page
- `GET /status` - JSON: connection status, IP, SSID
- `POST /save` - Save credentials and reboot
- `POST /clear` - Clear credentials and reboot
- `GET /style.css` - Serve CSS file
- `GET /script.js` - Serve JavaScript (optional)

**Response Types:**

- HTML: `text/html`
- CSS: `text/css`
- JSON: `application/json`

**Error Handling:**

- 404 for unknown routes
- 500 for server errors
- Validation of SSID/password format

#### 3. NVS Storage (`nvs_storage.c/.h`)

**Responsibilities:**

- Initialize NVS flash storage
- Save/retrieve WiFi credentials
- Clear credentials
- Handle storage errors

**Functions:**

- `nvs_storage_init()` - Initialize NVS
- `nvs_save_wifi_credentials(ssid, password)` - Save credentials
- `nvs_load_wifi_credentials(ssid, password)` - Load credentials
- `nvs_clear_wifi_credentials()` - Delete credentials
- `nvs_has_credentials()` - Check if credentials exist

**Storage Details:**

- Namespace: `wifi_config`
- Keys: `ssid`, `password`
- Type: String
- Max length: SSID (32 chars), Password (64 chars)

#### 4. Web UI (`html/`)

**HTML Structure (`index.html`):**

```html
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 WiFi Configuration</title>
    <link rel="stylesheet" href="/style.css">
</head>
<body>
    <div class="container">
        <header>
            <h1>ESP32 WiFi Manager</h1>
            <div class="status-indicator" id="status">
                <span class="status-dot"></span>
                <span class="status-text">Disconnected</span>
            </div>
        </header>

        <main>
            <section class="card">
                <h2>WiFi Configuration</h2>
                <form id="wifi-form">
                    <div class="form-group">
                        <label for="ssid">SSID</label>
                        <input type="text" id="ssid" name="ssid" required
                               placeholder="Enter network name" maxlength="32">
                    </div>
                    <div class="form-group">
                        <label for="password">Password</label>
                        <input type="password" id="password" name="password"
                               placeholder="Enter password" maxlength="64">
                    </div>
                    <button type="submit" class="btn btn-primary">Save & Connect</button>
                    <button type="button" class="btn btn-secondary" id="clear-btn">Clear Credentials</button>
                </form>
            </section>

            <section class="card">
                <h2>Network Information</h2>
                <div class="info-item">
                    <span class="label">Current Mode:</span>
                    <span class="value" id="mode">Unknown</span>
                </div>
                <div class="info-item">
                    <span class="label">IP Address:</span>
                    <span class="value" id="ip">--</span>
                </div>
                <div class="info-item">
                    <span class="label">Connected SSID:</span>
                    <span class="value" id="current-ssid">--</span>
                </div>
            </section>
        </main>

        <footer>
            <p>ESP32-C3 WiFi Manager</p>
        </footer>
    </div>
    <script src="/script.js"></script>
</body>
</html>
```

**CSS Styling (`style.css`):**

- Modern, responsive design
- Color scheme: Blue (#2563eb), White (#ffffff), Gray (#f3f4f6)
- Card-based layout with shadows
- Smooth transitions and animations
- Mobile-first approach
- Status indicators (green/red)
- Form styling with focus states

#### 5. Main Application (`main.c`)

**Responsibilities:**

- Application entry point
- Initialize all components
- Main event loop
- Error handling

**Flow:**

1. Initialize NVS storage
2. Check for WiFi credentials
3. Initialize WiFi Manager
4. Start Web Server
5. Enter FreeRTOS main loop

## Implementation Phases

### Phase 1: Documentation & Planning (Current)

- [x] Analyze requirements
- [x] Check environment and tools
- [x] Design architecture
- [x] Create PLAN.md (this file)
- [ ] Create README.md

### Phase 2: Project Setup

- [ ] Create project structure
- [ ] Set up CMakeLists.txt files
- [ ] Create main application skeleton
- [ ] Create empty component files

### Phase 3: ESP-IDF Installation & Configuration

- [ ] Run `install.bat` for ESP32-C3 tools
- [ ] Source ESP-IDF environment
- [ ] Configure project (menuconfig if needed)
- [ ] Verify build system

### Phase 4: NVS Storage Implementation

- [ ] Implement `nvs_storage_init()`
- [ ] Implement `nvs_save_wifi_credentials()`
- [ ] Implement `nvs_load_wifi_credentials()`
- [ ] Implement `nvs_clear_wifi_credentials()`
- [ ] Add error handling
- [ ] Test NVS operations

### Phase 5: WiFi Manager Implementation

- [ ] Implement WiFi event handler
- [ ] Implement `wifi_manager_init()`
- [ ] Implement AP mode setup
- [ ] Implement Station mode setup
- [ ] Add connection retry logic
- [ ] Test WiFi operations

### Phase 6: Web Server Implementation

- [ ] Initialize HTTP server
- [ ] Implement `/` route (HTML)
- [ ] Implement `/style.css` route
- [ ] Implement `/save` POST handler
- [ ] Implement `/clear` POST handler
- [ ] Implement `/status` API endpoint
- [ ] Test web server

### Phase 7: Web UI Development

- [ ] Create HTML file
- [ ] Create CSS with styling
- [ ] Create JavaScript for form handling
- [ ] Add AJAX for status updates
- [ ] Test UI on different devices
- [ ] Refine styling and animations

### Phase 8: Integration & Testing

- [ ] Integrate all components
- [ ] Test AP mode workflow
- [ ] Test Station mode workflow
- [ ] Test credential persistence
- [ ] Test web interface functionality
- [ ] Verify error handling

### Phase 9: Build & Flash

- [ ] Build project successfully
- [ ] Flash to ESP32-C3
- [ ] Monitor serial output
- [ ] Test complete workflow

### Phase 10: Documentation Finalization

- [ ] Update PLAN.md with actual implementation details
- [ ] Update README.md with usage instructions
- [ ] Add troubleshooting section
- [ ] Create GitHub repository

## Build & Flash Instructions

### Initial Setup

1. **Install ESP-IDF Tools** (if not already installed)
   
   ```bash
   cd C:\Users\jaakk\esp\v5.1.6\esp-idf
   install.bat esp32c3
   ```
   
   This downloads compiler, flash tools, and other utilities (~2GB)

2. **Set Environment Variables**
   
   ```bash
   C:\Users\jaakk\esp\v5.1.6\esp-idf\export.bat
   ```
   
   Or add to your PATH permanently

3. **Create Project**
   
   ```bash
   cd "C:\Users\jaakk\DIY projects\Microcontroller codes\ESP32 modbus reader"
   idf.py create-project --path . wifi-manager
   ```

4. **Set Target**
   
   ```bash
   idf.py set-target esp32c3
   ```

### Building

```bash
idf.py build
```

### Flashing

1. Connect ESP32-C3 via USB

2. Identify COM port (e.g., COM3)

3. Flash and monitor:
   
   ```bash
   idf.py -p COM3 flash monitor
   ```

Or separately:

```bash
idf.py -p COM3 flash
idf.py -p COM3 monitor
```

### Configuration (Optional)

```bash
idf.py menuconfig
```

Navigate to:

- Component config → WiFi
- Component config → HTTP Server

## Usage Workflow

### First Time Setup

1. **Power on ESP32-C3**
   
   - Device starts in AP mode
   - Creates WiFi network: `ESP32-Config`
   - Password: `config123`

2. **Connect to AP**
   
   - Connect your phone/computer to `ESP32-Config`
   - Password: `config123`

3. **Access Configuration Page**
   
   - Open browser: `http://192.168.4.1`
   - See WiFi configuration page

4. **Enter WiFi Credentials**
   
   - Enter your home WiFi SSID
   - Enter password
   - Click "Save & Connect"

5. **Device Reboots**
   
   - ESP32-C3 saves credentials to NVS
   - Reboots and connects to your WiFi
   - Note the IP address in status

6. **Access Web Interface**
   
   - Connect your phone/computer to your home WiFi
   - Open browser: `http://<device-ip-address>`
   - View status, reconfigure if needed

### Reconfiguration

If you need to change WiFi credentials:

1. Access web interface at device IP
2. Click "Clear Credentials"
3. Device reboots and creates AP again
4. Follow first-time setup steps

## Troubleshooting

### Common Issues

#### ESP-IDF Tools Not Found

**Problem:** `idf.py` command not found

**Solution:**

```bash
C:\Users\jaakk\esp\v5.1.6\esp-idf\export.bat
```

#### Build Failures

**Problem:** Compilation errors

**Solutions:**

- Clean build: `idf.py fullclean && idf.py build`
- Check ESP-IDF version: `idf.py --version`
- Verify target: `idf.py show-target`

#### Flash Failures

**Problem:** Cannot flash to device

**Solutions:**

- Check COM port is correct
- Ensure USB drivers installed
- Try different USB cable
- Press BOOT button before flashing
- Check device is in bootloader mode

#### WiFi Not Connecting

**Problem:** Device fails to connect to WiFi

**Solutions:**

- Verify SSID and password are correct
- Check WiFi signal strength
- Ensure 2.4GHz band (ESP32 doesn't support 5GHz)
- Check router settings (WPA2/WPA3 compatibility)
- Review serial logs for error messages

#### Cannot Access Web Page

**Problem:** Browser cannot load configuration page

**Solutions:**

- Verify device is in AP mode or connected to WiFi
- Check IP address in serial logs
- Try different browser
- Clear browser cache
- Check firewall settings

### Debug Mode

Enable detailed logging:

```bash
idf.py menuconfig
```

Component config → Log output → Default log verbosity → Debug

## Future Enhancements

### Potential Improvements

- [ ] **Captive Portal** - Redirect all HTTP requests to config page
- [ ] **WiFi Scanning** - Display available networks on web page
- [ ] **Multiple Network Profiles** - Save up to 5 networks, try each
- [ ] **MQTT Support** - Send status to MQTT broker
- [ ] **OTA Updates** - Over-the-air firmware updates
- [ ] **Authentication** - Password protect web interface
- [ ] **Dark Mode** - Toggle dark/light theme
- [ ] **Mobile App** - Native mobile application
- [ ] **Status LED** - Visual connection indicator on device
- [ ] **WiFi Reconnect** - Auto-reconnect on connection loss
- [ ] **Network Time** - NTP time synchronization
- [ ] **WebSockets** - Real-time status updates

### Advanced Features

- [ ] **Custom SSID/Password** - Configure AP credentials via web
- [ ] **Static IP** - Option for static IP assignment
- [ ] **DNS Server** - Custom DNS settings
- [ ] **Hostname** - Set device hostname
- [ ] **WiFi Power Save** - Low power mode options
- [ ] **Statistics** - Connection quality, signal strength
- [ ] **Logs** - View device logs on web page
- [ ] **Backup/Restore** - Export/import settings

## Technical References

### ESP-IDF Documentation

- [Official ESP-IDF Docs](https://docs.espressif.com/projects/esp-idf/en/v5.1.6/esp32c3/)
- [WiFi Configuration](https://docs.espressif.com/projects/esp-idf/en/v5.1.6/esp32c3/api-guides/wifi.html)
- [HTTP Server](https://docs.espressif.com/projects/esp-idf/en/v5.1.6/esp32c3/api-reference/protocols/esp_http_server.html)
- [NVS Flash Storage](https://docs.espressif.com/projects/esp-idf/en/v5.1.6/esp32c3/api-reference/storage/nvs_flash.html)

### ESP32-C3 Datasheet

- [ESP32-C3 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32-c3_datasheet_en.pdf)
- [Seeed Studio ESP32-C3 Docs](https://wiki.seeedstudio.com/)

### Arduino vs ESP-IDF

- This project uses ESP-IDF for:
  - Full control over hardware
  - Better performance
  - Native WiFi stack
  - Complete feature access
- Benefits over Arduino:
  - Lower latency
  - More memory available
  - Better power management
  - OTA support

## Project Files

### Directory Structure

```
esp32-wifi-manager/
├── CMakeLists.txt                 # Main CMake configuration
├── docs/
│   ├── PLAN.md                    # This file
│   └── README.md                  # GitHub README
├── main/
│   ├── CMakeLists.txt             # Main component CMake
│   ├── main.c                     # Application entry point
│   ├── wifi_manager.c             # WiFi implementation
│   ├── wifi_manager.h             # WiFi header
│   ├── web_server.c               # HTTP server implementation
│   ├── web_server.h               # HTTP server header
│   ├── nvs_storage.c              # NVS implementation
│   ├── nvs_storage.h              # NVS header
│   └── html/
│       ├── index.html             # Web UI HTML
│       ├── style.css              # Web UI CSS
│       └── script.js              # Web UI JavaScript
├── sdkconfig                      # Project configuration
└── .gitignore                     # Git ignore rules
```

### Key Files

| File             | Purpose                                           |
| ---------------- | ------------------------------------------------- |
| `main.c`         | Application entry point, component initialization |
| `wifi_manager.c` | WiFi driver, AP/Station mode management           |
| `web_server.c`   | HTTP server, request handling, static files       |
| `nvs_storage.c`  | Flash storage for WiFi credentials                |
| `index.html`     | Web interface HTML                                |
| `style.css`      | Styled web interface CSS                          |
| `script.js`      | JavaScript for form handling and AJAX             |

## Development Notes

### Memory Usage Estimates

- Free Heap: ~280KB (ESP32-C3)
- WiFi Stack: ~40KB
- HTTP Server: ~20KB
- Application: ~10KB
- Free: ~210KB

### Power Consumption

- Active (WiFi ON): ~80mA
- Light Sleep: ~15mA
- Deep Sleep: ~10µA

### WiFi Performance

- Connection time: 2-5 seconds
- AP mode startup: 1-2 seconds
- HTTP request: <100ms
- Page load: <500ms

## License

[To be determined by user]

## Contributing

1. Fork repository
2. Create feature branch
3. Commit changes
4. Push to branch
5. Create Pull Request

## Contact & Support

[To be determined by user]

---

**This document will be updated as development progresses.**
**Last updated: 2025-01-26**
