# eWind Modbus Register Documentation

## Device Specifications

- **Model**: eWind
- **Protocol**: Modbus RTU
- **Connection**: RS485
- **Baudrate**: 9600, 19200, or 38400 (configurable)
- **Device ID**: 1-100 (configurable)
- **Register types**: Coil registers (0x01), Holding registers (0x03)
- **Default modbus speed**: 9600 bps (configurable via HREG_MODBUS_SPEED)
- **Default parity**: None (configurable via HREG_MODBUS_PARITY)

## Coil Registers (Function 0x01)

| Address | Symbol | Description | Type | R/W | Multiplier | Range | Description | Notes |
|---------|--------|-------------|------|------|------------|-------|-------------|--------|
| 0 | COIL_STOP | Stop the machine | uint16 | R/W | 1 | - | Stop the machine | |
| 1 | COIL_AWAY | Away mode | uint16 | R/W | 1 | - | Enable away mode | |
| 3 | COIL_OVP | Overpressure mode | uint16 | R/W | 1 | - | Enable overpressure mode | |
| 6 | COIL_MAX_H | Max heating | uint16 | R/W | 1 | - | Force the machine to heat at maximum effect | |
| 7 | COIL_MAX_C | Max cooling | uint16 | R/W | 1 | - | Force the machine to cool at maximum effect | |
| 8 | COIL_CO2_BOOST_EN | CO₂ boosting | uint16 | R/W | 1 | - | Enable or disable CO₂ boosting | When setting this coil to 1, HREG_AI1_TYPE is changed to CO2. When set to 0, AI1 type is changed to RH |
| 9 | COIL_RH_BOOST_EN | %RH boosting | uint16 | R/W | 1 | - | Enable or disable humidity boosting | |
| 10 | COIL_M_BOOST | Manual boost | uint16 | R/W | 1 | - | Boost the fanspeeds to 100% for a period of time | |
| 11 | COIL_TEMP_BOOST_EN | Temperature boost | uint16 | R/W | 1 | - | Enable or disable temperature boosting | |
| 18 | COIL_AWAY_H | Heating | uint16 | R/W | 1 | - | Supply air heating enabled or disabled in Away mode | |
| 19 | COIL_AWAY_C | Cooling | uint16 | R/W | 1 | - | Supply air cooling enabled or disabled in Away mode | |
| 30 | COIL_LTO_ON | - | uint16 | R/W | 1 | - | Heat recycler state (running=1, stopped=0) | |
| 32 | COIL_HEAT_ON | - | uint16 | R/W | 1 | - | Element status of after-heater (On=1, Off=0) | |
| 36 | COIL_TEMP_DECREASE | Decrease temperature | uint16 | R/W | 1 | - | Temperature decrease function | Temperature offset from setpoint is defined in reg 172 |
| 40 | COIL_ECO_MODE | Eco mode | uint16 | R/W | 1 | - | Eco mode | |
| 41 | COIL_ALARM_A | Alarm A | uint16 | R | 1 | - | Alarm of class A active | |
| 42 | COIL_ALARM_B | Alarm B | uint16 | R | 1 | - | Alarm of class B active | |
| 49 | COIL_SERVICE_EN | Service reminder | uint16 | R/W | 1 | - | Service reminder enabled | |

## Holding Registers (Function 0x03)

### Temperature Measurements

| Address | Symbol | Description | Type | R/W | Multiplier | Range | Unit | Description | Notes |
|---------|--------|-------------|------|------|------------|-------|------|-------------|--------|
| 6 | HREG_T_FRS | Fresh air | int16 | R | 10 | - | °C | Outside air temperature at the unit (sensor TE01) | |
| 7 | HREG_T_SPLY_LTO | Supply air after HRC | int16 | R | 10 | - | °C | Supply air temperature after heat recovery (sensor TE05) | |
| 8 | HREG_T_SPLY | Supply air | int16 | R | 10 | - | °C | Supply air temperature after supply air heater (sensor TE10) | |
| 9 | HREG_T_WST | Exhaust air | int16 | R | 10 | - | °C | Exhaust air temperature (sensor TE32) | |
| 10 | HREG_T_EXT | Extract air temperature | int16 | R | 10 | - | °C | Extract air temperature from building at the unit (sensor TE30) | |
| 12 | HREG_T_WR | Return water | int16 | R | 10 | - | °C | Return water temperature in supply air heater (sensor TE45) | |
| 134 | HREG_TE01_24H_AVG | Average outside temperature | int16 | R | 10 | - | °C | 24-hour outside temperature average | |

### Humidity and Air Quality

| Address | Symbol | Description | Type | R/W | Multiplier | Range | Unit | Description | Notes |
|---------|--------|-------------|------|------|------------|-------|------|-------------|--------|
| 13 | HREG_HUM_EXT | Air humidity | uint16 | R | 1 | - | %RH | Extract air relative humidity %RH at the unit (sensor RH30) | |
| 23 | HREG_AI1_RES | Calculated value | uint16 | R | 1 | - | - | Calculated result | Conversion depends on HREG_AIx_RL, HREG_AIx_RH, HREG_AIx_VL, HREG_AIx_VH |
| 35 | HREG_RH_MEAN | Average air humidity, 48h | uint16 | R | 1 | - | %RH | Extract air 48h mean relative humidity %RH at the unit (sensor RH30). Updated every hour | |

### Heat Recovery Efficiency

| Address | Symbol | Description | Type | R/W | Multiplier | Range | Unit | Description | Notes |
|---------|--------|-------------|------|------|------------|-------|------|-------------|--------|
| 29 | HREG_LTO_N_SPLY | Heat recovery efficiency, supply air | uint16 | R | 1 | - | % | Supply air temperature efficiency. Calculated from outside air-, supply air after heat recovery- and extract air temperature | |
| 30 | HREG_LTO_N_EXT | Heat recovery efficiency, exhaust air | uint16 | R | 1 | - | % | Extract air temperature efficiency. Calculated from extract air-, exhaust air- and outside air temperature. In HP-units calculated from HRC extract air-, exhaust air- and outside air temperature | |

### Status and Mode

| Address | Symbol | Description | Type | R/W | Multiplier | Range | Unit | Description | Notes |
|---------|--------|-------------|------|------|------------|-------|------|-------------|--------|
| 44 | HREG_MODE | Status | bitfield | R | 1 | - | - | All current states of unit, eg. Home, Central vacuum cleaner, HP/EDX defrost etc. | See enumerator "mode" |
| 45 | HREG_EXTMODE | Temperature controller | enumeration | R | 1 | - | - | Displays current state of temperature controller; cooling, heat recovery, heating or none. | See enumerator "tempstep" |
| 48 | HREG_DISPLAY_SP | - | int16 | R | 10 | - | °C | Temperature controller setpoint shown to user | |
| 49 | HREG_OUTPUT | Temperature controller output | int16 | R | 1 | - | - | -100...-1=cooling, 0=nothing, 1...100=heat recovery, 101...200=additional heating or heat pump, 201...300=additional heating in heat pump units | |
| 50 | HREG_DISPLAY_FANSPEED | Fan speed control | uint16 | R | 1 | - | - | Fan speed level 1-4 set via panel | See enumerator "escfanspeed" |

### Fan Speed Configuration

| Address | Symbol | Description | Type | R/W | Multiplier | Range | Unit | Description | Notes |
|---------|--------|-------------|------|------|------------|-------|------|-------------|--------|
| 51 | HREG_FAN_TF_BASIC | Supply air | uint16 | R/W | 1 | 20-100 | % | TF fan speed corresponding to fan speed level 2 | |
| 52 | HREG_FAN_PF_BASIC | Extract air | uint16 | R/W | 1 | 20-100 | % | PF fan speed corresponding to fan speed level 2 | |
| 54 | HREG_OVP_TF | Supply air | uint16 | R/W | 1 | 20-100 | % | Supply air fan speed in manual overpressure mode | |
| 55 | HREG_OVP_PF | Extract air | uint16 | R/W | 1 | 20-100 | % | Extract air fan speed in manual overpressure mode | |
| 56 | HREG_OVP_TIME | Overpressure duration | uint16 | R/W | 1 | 1-60 | min | Duration of manual overpressure function | The value in this register is overwritten by the default value in HREG_OVP_TIME_DEF at system startup |
| 57 | HREG_OVP_TIME_DEF | Overpressure time | uint16 | R/W | 1 | 1-60 | min | Duration of overpressure function, in minutes, default value | |

### Boost Mode Configuration

| Address | Symbol | Description | Type | R/W | Multiplier | Range | Unit | Description | Notes |
|---------|--------|-------------|------|------|------------|-------|------|-------------|--------|
| 66 | HREG_M_BOOST_TIME | Boost time | uint16 | R/W | 1 | 1-500 | min | Duration of manual boosting function | |
| 67 | HREG_M_BOOST_TF_FANSPEED | Supply air | uint16 | R/W | 1 | 20-100 | % | Supply air fan speed in manual boosting mode | |
| 68 | HREG_M_BOOST_PF_FANSPEED | Extract air | uint16 | R/W | 1 | 20-100 | % | Extract air fan speed in manual boosting mode | |
| 69 | HREG_RH_LIM | %RH boosting threshold value | uint16 | R/W | 1 | 10-100 | %RH | Boosting starts when relative humidity exceeds this limit during winter mode | |
| 70 | HREG_RH_LIM_A | Threshold 48h %RH | uint16 | R/W | 1 | 0-100 | %RH | Boosting starts when relative humidity exceeds 48h average humidity with this threshold during summer mode | |
| 72 | HREG_RH_MAX_TF_FANSPEED | TF fanspeed fanspeed for fan level 3 | uint16 | R/W | 1 | 20-100 | % | Maximum TF fanspeed for fanspeed level 3, RH and CO2 boosting | |
| 74 | HREG_RH_MAX_PF_FANSPEED | PF fanspeed for fan speed level 3 | uint16 | R/W | 1 | 20-100 | % | Maximum PF fanspeed for fanspeed level 3, RH and CO2 boosting | |
| 76 | HREG_CO2_LIM | CO₂ boosting threshold | uint16 | R/W | 1 | 400-3000 | ppm | Boosting starts when carbon dioxide levels exceed this limit | |

### Away Mode Configuration

| Address | Symbol | Description | Type | R/W | Multiplier | Range | Unit | Description | Notes |
|---------|--------|-------------|------|------|------------|-------|------|-------------|--------|
| 100 | HREG_AWAY_TF_FANSPEED | TF fan speed in fan level 1 | uint16 | R/W | 1 | 20-100 | % | Supply air fan speed in Away mode | |
| 101 | HREG_AWAY_TEMP_D | Temperature drop | int16 | R/W | 10 | 0-150 | °C | Temperature drop in Away mode | |
| 102 | HREG_AWAY_PF_FANSPEED | PF fan speed in fan level 1 | uint16 | R/W | 1 | 20-100 | % | Extract air fan speed in Away mode | |
| 103 | HREG_AWAYL_TEMP_D | Temperature drop | int16 | R/W | 10 | 0-150 | °C | Temperature drop in Away mode | |

### Analog Input Configuration

| Address | Symbol | Description | Type | R/W | Multiplier | Range | Unit | Description | Notes |
|---------|--------|-------------|------|------|------------|-------|------|-------------|--------|
| 104 | HREG_AI1_TYPE | Sensor type | uint16 | R/W | 1 | - | - | Type of external sensor in AI1 | See enumerator "analogIn" |
| 110 | HREG_AI1_VL | Voltage low | uint16 | R/W | 10 | 0-100 | V | AI1 voltage low when AI1 type is RH transmitter | |
| 114 | HREG_AI5_VL | Voltage low | uint16 | R/W | 10 | 0-100 | V | AI1 voltage low when AI1 type is CO2 transmitter | |
| 116 | HREG_AI1_VH | Voltage high | uint16 | R/W | 10 | 0-100 | V | AI1 voltage high when AI1 type is RH transmitter | |
| 120 | HREG_AI5_VH | Voltage high | uint16 | R/W | 10 | 0-100 | V | AI1 voltage high when AI1 type CO2 transmitter | |
| 122 | HREG_AI1_RL | Voltage low, effect | int16 | R/W | 1 | - | - | AI1 output value at 0V when AI1 type is RH transmitter | |
| 126 | HREG_AI5_RL | Voltage low, effect | int16 | R/W | 1 | - | - | AI1 output value at 0V when type is CO2_1 | |
| 128 | HREG_AI1_RH | Voltage high, effect | int16 | R/W | 1 | - | - | AI1 output value at 10V when AI1 type is RH transmitter | |
| 132 | HREG_AI5_RH | Voltage high, effect | int16 | R/W | 1 | - | - | AI1 output value at 10V when type is CO2_1 | |

### Temperature Control

| Address | Symbol | Description | Type | R/W | Multiplier | Range | Unit | Description | Notes |
|---------|--------|-------------|------|------|------------|-------|------|-------------|--------|
| 135 | HREG_T_SETPOINT | Supply air setpoint | int16 | R/W | 10 | 0-500 | °C | Desired setpoint set by the user | |
| 137 | HREG_TE01_SUMMER_WINTER_THRESHOLD | Summer/winter threshold temperature | int16 | R/W | 10 | -100-150 | °C | Outside air 24h average temperature; in summer mode extract air 48h average humidity, in winter mode a fixed %RH threshold | |
| 138 | HREG_TC1_SP_MIN | Minimum temperature of supply air | int16 | R/W | 10 | 100-500 | °C | Temperature controller tries to keep supply air temperature above this value in constant extract- and room temperature control modes | |
| 139 | HREG_TC1_SP_MAX | Maximum temperature of supply air | int16 | R/W | 10 | 100-500 | °C | Temperature controller tries to keep supply air temperature below this value in constant extract- and room temperature control modes | |
| 172 | HREG_TEMP_DECREASE_VAL | Temperature decrease | int16 | R/W | 10 | 0-150 | °C | Number of degrees, under which the temperature should be maintained when temperature decrease function is on | Low limit can be negative to enable temperature increase function |

### Heating and Cooling Limits

| Address | Symbol | Description | Type | R/W | Multiplier | Range | Unit | Description | Notes |
|---------|--------|-------------|------|------|------------|-------|------|-------------|--------|
| 164 | HREG_COOL_BLOCK_T | Outside temperature limit for cooling | int16 | R/W | 10 | 50-400 | °C | Active- or free cooling with heat recovery wheel is not allowed below this temperature | |
| 196 | HREG_HEAT_BLOCK_T | Outside temperature limit for heating | int16 | R/W | 10 | -50-250 | °C | Active heating of supply air is not allowed when this temperature is exceeded | |

### System Information

| Address | Symbol | Description | Type | R/W | Multiplier | Range | Unit | Description | Notes |
|---------|--------|-------------|------|------|------------|-------|------|-------------|--------|
| 343 | HREG_UPTIME | System uptime | uint16 | R/W | 1 | - | min | Number of minutes since system was started | Warning: the count is approximative, it should not be used for time-keeping purposes |
| 348 | HREG_PANEL_BUS_NUM_SLAVES | Number of active panel bus units | uint16 | R/W | 1 | - | - | The number of modbus slaves detected, updated every minute | |
| 354 | HREG_BOOTLOADER_VERSION | Bootloader version | uint16 | R/W | 1 | - | - | Bootloader version | Reserved for future use on ESC |
| 599 | HREG_SW_VERSION | ESC SW version | uint16 | R/W | 100 | - | - | ESC Software release number | |

### Circulation Air Fan (Kotilämpö, EMB and MixBox)

| Address | Symbol | Description | Type | R/W | Multiplier | Range | Unit | Description | Notes |
|---------|--------|-------------|------|------|------------|-------|------|-------------|--------|
| 649 | HREG_CIRCULATION_MIN_FANSPEED | Circulation air fan min. speed | uint16 | R/W | 1 | 20-100 | % | Minimum speed of the circulation air fan in constant or variable mode | Kotilämpö, EMB and MixBox |
| 650 | HREG_CIRCULATION_MAX_FANSPEED | Circulation air fan max. speed | uint16 | R/W | 1 | 20-100 | % | Maximum speed of the circulation air fan in variable mode | Kotilämpö, EMB and MixBox |
| 703 | HREG_CIRCULATION_FANSPEED | Circulation air fan speed | uint16 | R/W | 1 | 20-100 | % | Speed of the circulation air fan in constant mode | Kotilämpö, EMB, Mixbox, and machines with closed circulation air (Pallas KI) |
| 774 | HREG_EFFECTIVE_CIRCULATION | Fan speed, circulation air | uint16 | R | 1 | - | % | Circulation air fan's current speed | Kotilämpö, EMB, Mixbox |

### Time and Configuration

| Address | Symbol | Description | Type | R/W | Multiplier | Range | Unit | Description | Notes |
|---------|--------|-------------|------|------|------------|-------|------|-------------|--------|
| 676 | HREG_TC1_SP_AT_MINUS_20 | TC1 SP when TE01 is -20C | uint16 | R/W | 10 | - | °C | Supply air setpoint at outside temperature -20C, when using outside air temp compensated temp control | |
| 677 | HREG_TC1_SP_AT_ZERO | TC1 SP when TE01 is 0C | uint16 | R/W | 10 | - | °C | Supply air setpoint at outside temperature 0C, when using outside air temp compensated temp control | |
| 678 | HREG_TC1_SP_AT_PLUS_20 | TC1 SP when TE01 is +20C | uint16 | R/W | 10 | - | °C | Supply air setpoint at outside temperature +20C, when using outside air temp compensated temp control | |
| 710 | HREG_DAYS_RUNNING | - | uint16 | R/W | 1 | - | days | Number of days since service notification was acknowledged | |
| 726 | HREG_MB_MEASUREMENT_UPD | Modbus update interval | uint16 | R/W | 1 | 1-60 | s | Modbus measurement register update interval in seconds | |
| 733 | HREG_MODBUS_SPEED | Modbus speed | enumeration | R/W | 1 | - | - | Modbus RTU serial line speed | See enumerator "modbusspeed" |
| 734 | HREG_MODBUS_PARITY | Modbus parity | enumeration | R/W | 1 | - | - | Modbus RTU serial line parity | See enumerator "modbusparity" |

### Analog and Digital I/O

| Address | Symbol | Description | Type | R/W | Multiplier | Range | Unit | Description | Notes |
|---------|--------|-------------|------|------|------------|-------|------|-------------|--------|
| 780 | HREG_AO1_VOLT | AO1 voltage | uint16 | R | 10 | - | V | The voltage on Analog Output 1 | |
| 781 | HREG_AO2_VOLT | AO2 voltage | uint16 | R | 10 | - | V | The voltage on Analog Output 2 | |
| 783 | HREG_AO4_VOLT | AO4 voltage | uint16 | R | 10 | - | V | The voltage on Analog Output 4 | |
| 784 | HREG_AO5_VOLT | AO5 voltage | uint16 | R | 10 | - | V | The voltage on Analog Output 5 | |
| 785 | HREG_AO6_VOLT | AO6 voltage | uint16 | R | 10 | - | V | The voltage on Analog Output 6 | |
| 788 | HREG_DI9_PULSE_CNT | DI9 pulse count | uint16 | R | 1 | - | pulses | Number of pulses detected on DI9 | |
| 789 | HREG_DI_BITMAP | DI1-12 and X9-GPIO1-3 status | uint16 | R | 1 | - | - | Status bitmap of digital inputs DI1 to DI12 and GPIO pins 1-3 on connector X9 | |
| 798 | HREG_DO_BITMAP | DO1-8 status | uint16 | R | 1 | - | - | Status bitmap of digital outputs (relays) | |

### Alarms (Registers 385-524)

Each alarm entry consists of 6 registers starting at 385 (Alarm 1, newest):

| Address Offset | Symbol | Description | Type | R/W | Multiplier | Unit | Description |
|---------------|---------|-------------|------|------|------------|------|-------------|
| +0 | ALARMx_ALMTYPE | Alarm type | uint16 | R/W | 1 | - | Alarm 1 (newest) alarm type |
| +1 | ALARMx_STATECLASS | Alarm state and class | uint16 | R/W | 1 | - | This defines the status (low byte) and class of the alarm (high byte) |
| +2 | ALARMx_YY | Alarm year | uint16 | R/W | 1 | year | |
| +3 | ALARMx_MM | Alarm month | uint16 | R/W | 1 | month | |
| +4 | ALARMx_DD | Alarm day | uint16 | R/W | 1 | day | |
| +5 | ALARMx_HH | Alarm hour | uint16 | R/W | 1 | hour | |
| +6 | ALARMx_MI | Alarm minutes | uint16 | R/W | 1 | min | |

**Alarm register ranges:**
- Alarm 1: 385-391
- Alarm 2: 392-398
- Alarm 3: 399-405
- Alarm 4: 406-412
- Alarm 5: 413-419
- Alarm 6: 420-426
- Alarm 7: 427-433
- Alarm 8: 434-440
- Alarm 9: 441-447
- Alarm 10: 448-454
- Alarm 11: 455-461
- Alarm 12: 462-468
- Alarm 13: 469-475
- Alarm 14: 476-482
- Alarm 15: 483-489
- Alarm 16: 490-496
- Alarm 17: 497-503
- Alarm 18: 504-510
- Alarm 19: 511-517
- Alarm 20: 518-524

### Alarm Counters

| Address | Symbol | Description | Type | R/W | Multiplier | Unit | Description |
|---------|--------|-------------|------|------|------------|------|-------------|
| 538 | HREG_ALARM_SERVICE_TIME | Service reminder | uint16 | R/W | 1 | days | Number of days until service reminder alarm is given |
| 581 | HREG_N_O_ALARMS | Number of alarms | uint16 | R/W | 1 | - | Current number of alarms in the alarm log |

## Enumerators

### enabledisable

| Value | Label |
|-------|-------|
| 0 | Disable |
| 1 | Enable |

### alarmstate

| Value | Label |
|-------|-------|
| 0 | Off |
| 1 | Acked |
| 2 | On |

### mode

| Value | Label |
|-------|-------|
| 0 | Home |
| 1 | Max. cooling |
| 2 | Max. heating |
| 4 | Alarm A |
| 8 | Stop |
| 16 | Away mode |
| 32 | Temperature boost |
| 64 | CO₂ boosting |
| 256 | %RH boosting |
| 512 | Manual boost |
| 1024 | Overpressure mode |
| 2048 | Cooker hood on |
| 4096 | Central vacuum cleaner on |
| 8192 | Summer night cooling |
| 16384 | Defrosting |

### analogIn

| Value | Label |
|-------|-------|
| 0 | No input |
| 1 | CO₂ sensor 1 |
| 2 | CO₂ sensor 2 |
| 3 | CO₂ sensor 3 |
| 4 | %RH sensor 1 |
| 5 | %RH sensor 2 |
| 6 | %RH sensor 3 |
| 7 | Outside air temperature sensor |
| 8 | Room temperature sensor 1 |
| 9 | Room temperature sensor 2 |
| 10 | Room temperature sensor 3 |
| 11 | External deviation for temperature setpoint |
| 15 | Constant supply air duct pressure sensor PDE10 |
| 16 | Constant extract air duct pressure sensor PDE30 |
| 131 | Aqua water tank temperature TE80 |
| 132 | Aqua cool water tank temperature TE70 |
| 133 | Aqua cool return water temperature from cooling load and tank TE71 |
| 140 | RH sensor for outside air humidity |
| 141 | RH sensor for waste air humidity |

### alarmtypes

| Value | Label |
|-------|-------|
| 0 | No alarm |
| 1 | TE05 min |
| 2 | TE10 min |
| 3 | TE10 max |
| 4 | TE20 max |
| 5 | TE30 min |
| 6 | TE30 max |
| 7 | Heat pump |
| 8 | SLP |
| 9 | TE45 min |
| 10 | LTO |
| 11 | Cooling alarm (unused) |
| 12 | Emergency stop |
| 13 | External alarm |
| 14 | Service reminder |
| 15 | PDS10 |
| 16 | Supply filter high |
| 17 | Extract filter high |
| 20 | Supply fan pressure |
| 21 | Exhaust fan pressure |
| 22 | TE50 H |
| 24 | TE52 H |
| 25 | Supply air pressure |
| 26 | Extract air pressure |
| 27 | TE02 H |
| 28 | Service reminder |
| 29 | TE49 L |

### modbusspeed

| Value | Label |
|-------|-------|
| 1 | 9600 |
| 2 | 19200 |
| 3 | 115200 |

### modbusparity

| Value | Label |
|-------|-------|
| 1 | None |
| 2 | Even |

### escfanspeed

| Value | Label |
|-------|-------|
| 1 | Fanspeed level 1 (Away-mode) |
| 2 | Fanspeed level 2 (Home-mode) |
| 3 | Fanspeed level 3 (Home-mode with high fan speeds) |
| 4 | Fanspeed level 4 (Manual boost with timer) |

### tempstep

| Value | Label |
|-------|-------|
| 0 | None |
| 1 | Cooling |
| 2 | Heat recovery |
| 4 | Heating |
| 6 | Summer night cooling |
| 7 | Starting up |
| 8 | Dehumidification |

## Usage Notes

### Modbus Configuration

- Default Modbus speed is 9600 bps, configurable via HREG_MODBUS_SPEED (register 733)
- Default parity is None, configurable via HREG_MODBUS_PARITY (register 734)
- Device ID must be unique on the RS485 bus (recommended range: 1-100)
- Modbus measurement update interval can be set via HREG_MB_MEASUREMENT_UPD (register 726)

### Fan Speed Control

The device supports multiple fan speed levels controlled by various coils and registers:
- **Away mode**: Uses HREG_AWAY_TF_FANSPEED and HREG_AWAY_PF_FANSPEED
- **Home mode**: Uses HREG_FAN_TF_BASIC and HREG_FAN_PF_BASIC
- **Manual boost**: Temporarily sets fans to 100% via COIL_M_BOOST
- **Overpressure mode**: Uses HREG_OVP_TF and HREG_OVP_PF with HREG_OVP_TIME
- **Boost modes**: CO2, RH, and temperature boosting use HREG_RH_MAX_TF_FANSPEED and HREG_RH_MAX_PF_FANSPEED

### Temperature Scaling

All temperature registers use a multiplier of 10, meaning the raw value must be divided by 10 to get degrees Celsius.
- Example: Raw value 215 = 21.5°C

### Alarm System

The device maintains an alarm log with up to 20 alarms (Alarm 1 is newest, Alarm 20 is oldest).
Each alarm entry contains:
- Alarm type (see alarmtypes enumerator)
- Alarm state and class
- Timestamp (year, month, day, hour, minute)

### CO2 and RH Boosting

When CO2 or RH boosting is enabled via coils (COIL_CO2_BOOST_EN or COIL_RH_BOOST_EN), the HREG_AI1_TYPE register is automatically updated to configure the analog input for the appropriate sensor type.

### Service Reminder

The device tracks days since service acknowledgment and can trigger a service alarm:
- HREG_DAYS_RUNNING: Days since last service acknowledgment
- HREG_ALARM_SERVICE_TIME: Days until next service reminder
- COIL_SERVICE_EN: Enable/disable service reminder function

---

**Documentation source:** eWind-modbus-register-list-public-clean.csv and eWind-modbus-register-list-public-clean-enumerators.csv
**Last updated:** 2025-01-27
