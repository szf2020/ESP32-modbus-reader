# eAirMD Modbus Register Documentation

## Device Specifications

- **Model**: eAirMD
- **Protocol**: Modbus RTU
- **Connection**: RS485
- **Software Version**: 1.14 and later
- **Baudrate**: 19200 default (configurable: 9600, 19200, 115200 bps)
- **Parity**: None default (configurable: None or Even parity)
- **Device ID**: 1-100 (configurable via HREG_MBADDR)
- **Register types**: Holding registers (0x03) only
- **Default modbus speed**: 19200 bps
- **Default parity**: None

## Holding Registers (Function 0x03)

### Temperature Measurements (Registers 1-12)

| Address | Symbol | Name | Type | Multiplier | Bounds | Description |
|---------|--------|------|------|------------|-------|-------------|
| 1 | HREG_T_OP1 | Room temperature sensor TE20 | int16 | 10 | - | Temperature at operator panel 1 |
| 2 | HREG_T_OP2 | Room temperature sensor TE21 | int16 | 10 | - | Temperature at operator panel 2 |
| 6 | HREG_T_FRS | Fresh air | int16 | 10 | - | TE01 (fresh air) temperature |
| 7 | HREG_T_SPLY_LTO | Supply air after HRC | int16 | 10 | - | TE05: Fresh (incoming) air temperature after HRC |
| 8 | HREG_T_SPLY | Supply air | int16 | 10 | - | TE10 Room supply air temperature |
| 9 | HREG_T_WST | Waste air | int16 | 10 | - | TE32 Waste air temperature |
| 10 | HREG_T_EXT | Room removed air | int16 | 10 | - | TE30 Room removed air temperature |
| 11 | HREG_T_EXT_LTO | Removed air before HRC | int16 | 10 | - | TE31 removed air before heat recycler |
| 12 | HREG_T_WR | Return water | int16 | 10 | - | TE45 heater element return water temperature |
| 16 | HREG_TE07 | HP/MDX/Dehum supply air | int16 | 10 | - | Supply air temperature after dehumidification coil, or after heat pump coil in HP-E, HP-W, MDX-E and MDX-W units (sensor TE07) |

### Fan Speed and Airflow

| Address | Symbol | Name | Type | Multiplier | Bounds | Description |
|---------|--------|------|------|------------|-------|-------------|
| 3 | HREG_EFFECTIVE_TF | Current supply fan speed | uint16 | 1 | - | The current effective TF fanspeed |
| 4 | HREG_EFFECTIVE_PF | Current exhaust fan speed | uint16 | 1 | - | The current effective PF fanspeed |

### Humidity Measurements

| Address | Symbol | Name | Type | Multiplier | Bounds | Description |
|---------|--------|------|------|------------|-------|-------------|
| 13 | HREG_HUM_EXT | Exhaust air humidity | uint16 | 1 | - | RH30 measurement, removed air relative humidity |
| 35 | HREG_RH_MEAN | 48h air humidity average | uint16 | 1 | - | Mean relative humidity, with 48 hour history, updated every hour |
| 36 | HREG_ABSHUM10 | Supply air absolute humidity | uint16 | 10 | - | Supply air absolute humidity, calculated from sensors TE10 and RH10, assuming normal atmospheric pressure |

### Pressure Measurements

| Address | Symbol | Name | Type | Multiplier | Bounds | Description |
|---------|--------|------|------|------------|-------|-------------|
| 14 | HREG_PRES_SPLYF | Pressure difference supply | uint16 | 1 | - | Pressure difference over filter, TF side |
| 15 | HREG_PRES_EXTF | Pressure difference ext | uint16 | 1 | - | Pressure difference over filter, PF side |

### Analog Inputs (Raw and Calculated)

| Address | Symbol | Name | Type | Multiplier | Bounds | Description |
|---------|--------|------|------|------------|-------|-------------|
| 17 | HREG_AI1 | Analog input voltage | uint16 | 10 | - | Raw conversion result for AI1 |
| 18 | HREG_AI2 | Analog input voltage | uint16 | 10 | - | Raw conversion result for AI2 |
| 19 | HREG_AI3 | Analog input voltage | uint16 | 10 | - | Raw conversion result for AI3 |
| 20 | HREG_AI4 | Analog input voltage | uint16 | 10 | - | Raw conversion result for AI4 |
| 21 | HREG_AI5 | Analog input voltage | uint16 | 10 | - | Raw conversion result for AI5 |
| 22 | HREG_AI6 | Analog input voltage | uint16 | 10 | - | Raw conversion result for AI6 |
| 23 | HREG_AI1_RES | Calculated value | uint16 | 1 | - | Calculated result for AI1 |
| 24 | HREG_AI2_RES | Calculated value | uint16 | 1 | - | Calculated result for AI2 |
| 25 | HREG_AI3_RES | Calculated value | uint16 | 1 | - | Calculated result for AI3 |
| 26 | HREG_AI4_RES | Calculated value | uint16 | 1 | - | Calculated result for AI4 |
| 27 | HREG_AI5_RES | Calculated value | uint16 | 1 | - | Calculated result for AI5 |
| 28 | HREG_AI6_RES | Calculated value | uint16 | 1 | - | Calculated result for AI6 |

### Heat Recovery Efficiency

| Address | Symbol | Name | Type | Multiplier | Bounds | Description |
|---------|--------|------|------|------------|-------|-------------|
| 29 | HREG_LTO_N_SPLY | Heat recovery efficiency n supply | uint16 | 1 | - | HRC efficiency ratio (supply side) |
| 30 | HREG_LTO_N_EXT | Heat recovery efficiency n exhaust | uint16 | 1 | - | HRC efficiency ratio (ext (removed air) side) |

### NTC Temperature Inputs

| Address | Symbol | Name | Type | Multiplier | Bounds | Description |
|---------|--------|------|------|------------|-------|-------------|
| 31 | HREG_NTC_X6 | Input X6 | int16 | 10 | - | Optional NTC-10 input X6 measurement |
| 32 | HREG_NTC_X7 | Input X7 | int16 | 10 | - | Optional NTC-10 input X7 measurement |

### Absolute Humidity Control

| Address | Symbol | Name | Type | Multiplier | Bounds | Description |
|---------|--------|------|------|------------|-------|-------------|
| 33 | HREG_ABS_HUM_CTRL_OUTPUT | Absolute humidity control output | int16 | 1 | - | -100...0% = dehumidifying, 0 = none, 0...100% = humidifying |

### Network Status

| Address | Symbol | Name | Type | Multiplier | Bounds | Description |
|---------|--------|------|------|------------|-------|-------------|
| 34 | HREG_NWK_STATUS | Network status | bitfield | 1 | - | Ethernet block status |

### Real-Time Clock (Read-Only)

| Address | Symbol | Name | Type | Multiplier | Bounds | Description |
|---------|--------|------|------|------------|-------|-------------|
| 37 | HREG_SEC_RTC | s | uint16 | 1 | - | RTC seconds |
| 38 | HREG_MIN_RTC | min | uint16 | 1 | - | RTC minutes |
| 39 | HREG_HOUR_RTC | h | uint16 | 1 | - | RTC hours, 24 hour format |
| 40 | HREG_DAY_RTC | day | uint16 | 1 | - | RTC day-of-month |
| 41 | HREG_MONTH_RTC | month | uint16 | 1 | - | RTC month |
| 42 | HREG_YEAR_RTC | year | uint16 | 1 | - | RTC year, expressed in years since 2000 |

### Mode and Status

| Address | Symbol | Name | Type | Multiplier | Bounds | Description |
|---------|--------|------|------|------------|-------|-------------|
| 5 | HREG_UPCOMING_TIME_PROGRAM | Next time program | uint16 | 1 | - | Indicates a time program which will start during the next two hours. Values 1-20 indicate week program slots, value 101-105 indicate year program slots |
| 44 | HREG_MODE | Status | bitfield | 1 | - | The current mode of the machine, used to display information to the user |
| 45 | HREG_EXTMODE | Temperature control step | bitfield | 1 | - | Currently active temperature control step: Cooling, Heat Recovery (LTO), or heating |
| 46 | HREG_ROOM_TEMP | Room temperature average | int16 | 10 | - | TE20 room temperature, average value calculated from op panel sensors and room temperature transmitters |
| 47 | HREG_CASCADE_SP | Setpoint for supply air | int16 | 10 | - | Setpoint for temperature controller responsible for maintaining room supply air at a constant level |
| 48 | HREG_DISPLAY_SP | - | int16 | 10 | - | Temperature controller setpoint shown to user |
| 49 | HREG_OUTPUT | Controller output | int16 | 1 | - | Output from the TC1 temperature PI controller. -200 to -100 additional cooling, -100...-1=cooling, 0=nothing, 1...100=heat recovery, 101...200=additional heating or heat pump, 201...300=additional heating in heat pump units |

### Analog Input Type Configuration

| Address | Symbol | Name | Type | Multiplier | Bounds | Description |
|---------|--------|------|------|------------|-------|-------------|
| 104 | HREG_AI1_TYPE | Sensor type | uint16 | 1 | - | Type of external sensor in AI1 |
| 105 | HREG_AI2_TYPE | Sensor type | uint16 | 1 | - | Type of external sensor in AI2 |
| 106 | HREG_AI3_TYPE | Sensor type | uint16 | 1 | - | Type of external sensor in AI3 |
| 107 | HREG_AI4_TYPE | Sensor type | uint16 | 1 | - | Type of external sensor in AI4 |
| 108 | HREG_AI5_TYPE | Sensor type | uint16 | 1 | - | Type of external sensor in AI5 |
| 109 | HREG_AI6_TYPE | Sensor type | uint16 | 1 | - | Type of external sensor in AI6 |

### Analog Input Voltage Limits

| Address | Symbol | Name | Type | Multiplier | Bounds | Description |
|---------|--------|------|------|------------|-------|-------------|
| 110 | HREG_AI1_VL | Voltage low | uint16 | 10 | 0-100 | AI1 voltage low |
| 111 | HREG_AI2_VL | Voltage low | uint16 | 10 | 0-100 | AI2 voltage low |
| 112 | HREG_AI3_VL | Voltage low | uint16 | 10 | 0-100 | AI3 voltage low |
| 113 | HREG_AI4_VL | Voltage low | uint16 | 10 | 0-100 | AI4 voltage low |
| 114 | HREG_AI5_VL | Voltage low | uint16 | 10 | 0-100 | AI5 voltage low |
| 115 | HREG_AI6_VL | Voltage low | uint16 | 10 | 0-100 | AI6 voltage low |
| 116 | HREG_AI1_VH | Voltage high | uint16 | 10 | 0-100 | AI1 voltage high |
| 117 | HREG_AI2_VH | Voltage high | uint16 | 10 | 0-100 | AI2 voltage high |
| 118 | HREG_AI3_VH | Voltage high | uint16 | 10 | 0-100 | AI3 voltage high |
| 119 | HREG_AI4_VH | Voltage high | uint16 | 10 | 0-100 | AI4 voltage high |
| 120 | HREG_AI5_VH | Voltage high | uint16 | 10 | 0-100 | AI5 voltage high |
| 121 | HREG_AI6_VH | Voltage high | uint16 | 10 | 0-100 | AI6 voltage high |

### Analog Input Result Limits

| Address | Symbol | Name | Type | Multiplier | Bounds | Description |
|---------|--------|------|------|------------|-------|-------------|
| 122 | HREG_AI1_RL | Result low | int16 | 1 | - | AI1 output value from voltage low |
| 123 | HREG_AI2_RL | Result low | int16 | 1 | - | AI2 output value from voltage low |
| 124 | HREG_AI3_RL | Result low | int16 | 1 | - | AI3 output value from voltage low |
| 125 | HREG_AI4_RL | Result low | int16 | 1 | - | AI4 output value from voltage low |
| 126 | HREG_AI5_RL | Result low | int16 | 1 | - | AI5 output value from voltage low |
| 127 | HREG_AI6_RL | Result low | int16 | 1 | - | AI6 output value from voltage low |
| 128 | HREG_AI1_RH | Result high | int16 | 1 | - | AI1 output value from voltage high |
| 129 | HREG_AI2_RH | Result high | int16 | 1 | - | AI2 output value from voltage high |
| 130 | HREG_AI3_RH | Result high | int16 | 1 | - | AI3 output value from voltage high |
| 131 | HREG_AI4_RH | Result high | int16 | 1 | - | AI4 output value from voltage high |
| 132 | HREG_AI5_RH | Result high | int16 | 1 | - | AI5 output value from voltage high |
| 133 | HREG_AI6_RH | Result high | int16 | 1 | - | AI6 output value from voltage high |

### Temperature Control Parameters

| Address | Symbol | Name | Type | Multiplier | Bounds | Description |
|---------|--------|------|------|------------|-------|-------------|
| 134 | HREG_TE01_24H_AVG | Average outside temperature | int16 | 10 | - | 24-hour outside temperature average |
| 135 | HREG_T_SETPOINT | Supply air setpoint | int16 | 10 | 0-500 | The desired setpoint set by the user |
| 137 | HREG_TE01_SUMMER_WINTER_THRESHOLD | Summer/Winter threshold | int16 | 10 | -100-150 | Summer/Winter season 24-hour average outside temperature threshold value |
| 172 | HREG_TEMP_DECREASE_VAL | Temperature decrease | int16 | 10 | 0-150 | The amount of degrees temperature should be lowered then temperature decrease function is on. Low limit can be negative to enable temperature increase function |

### Week Time Programs (WC1-WC20, Registers 210-329)

Each week program slot (WC1 through WC20) consists of 6 registers:

| Address Offset | Symbol | Name | Type | Multiplier | Bounds | Description |
|---------------|--------|------|------|------------|-------|-------------|
| +0 | DAY_WCx | Week timer slot #x | bitfield | 1 | - | Days when allowed. Bit 0: Sunday - Bit 6: Saturday |
| +1 | STA_HOUR_WCx | Start h | uint16 | 1 | - | h | WCx Start h |
| +2 | STA_MIN_WCx | Start m | uint16 | 1 | - | min | WCx Start m |
| +3 | STO_HOUR_WCx | Stop h | uint16 | 1 | - | h | WCx Stop h |
| +4 | STO_MIN_WCx | Stop m | uint16 | 1 | - | min | WCx Stop m |
| +5 | WCx | Function | enumeration | 1 | - | WCx Function |

**Week program register ranges:**
- WC1: 210-215
- WC2: 216-221
- WC3: 222-227
- WC4: 228-233
- WC5: 234-239
- WC6: 240-245
- WC7: 246-251
- WC8: 252-257
- WC9: 258-263
- WC10: 264-269
- WC11: 270-275
- WC12: 276-281
- WC13: 282-287
- WC14: 288-293
- WC15: 294-299
- WC16: 300-305
- WC17: 306-311
- WC18: 312-317
- WC19: 318-323
- WC20: 324-329

### Year Time Programs (Y1-Y5, Registers 330-384)

Each year program slot (Y1 through Y5) consists of multiple registers. The structure varies slightly:

| Address Offset | Symbol | Name | Type | Multiplier | Bounds | Description |
|---------------|--------|------|------|------------|-------|-------------|
| +0 | STA_PV_Yx | Year timer slot #x | uint16 | 1 | - | day | Year program x start day-of-month |
| +1 | STA_KK_Yx | - | uint16 | 1 | - | month | Year program x stop month |
| +2 | ACTIVE_TIMEPROGRAMS_1 | Active time programs, week slots 1-16 | uint16 | 1 | - | - | - |
| +3 | STA_HOUR_Yx | - | uint16 | 1 | - | h | Year program x start hour |
| +4 | STA_MIN_Yx | - | uint16 | 1 | - | min | Year program x start minute |
| +5 | STO_PV_Yx | - | uint16 | 1 | - | - | Year program x stop day of month |
| +6 | STO_KK_Yx | - | uint16 | 1 | - | - | Year program x stop month |
| +7 | ACTIVE_TIMEPROGRAMS_2 | Active time programs, week slots 17-20 and year slots 1-5 | uint16 | 1 | - | - | - |
| +8 | STO_HOUR_Yx | - | uint16 | 1 | - | h | Year program x stop hour |
| +9 | STO_MIN_Yx | - | uint16 | 1 | - | min | Year program x stop minute |
| +10 | Yx | Year program x action | uint16 | 1 | - | - | Year program x action |

**Year program register ranges:**
- Y1: 330-340
- Y2: 341-351
- Y3: 352-362
- Y4: 363-373
- Y5: 374-384

### System Information and Uptime

| Address | Symbol | Name | Type | Multiplier | Bounds | Description |
|---------|--------|------|------|------------|-------|-------------|
| 343 | HREG_UPTIME | System uptime | uint16 | 1 | - | Number of minutes since system was started. Note: count will reset to zero after approximately 45 days |
| 348 | Reserved | Number of active panel bus units | uint16 | 1 | - | The number of modbus slaves detected, updated every minute |
| 354 | HREG_BOOTLOADER_VERSION | Bootloader version | uint16 | 1 | - | Bootloader version |
| 597 | HREG_FAMILY_TYPE | Family | uint16 | 1 | - | Machine family type |
| 598 | HREG_HW_VERSION | Hardware version | enumeration | 1 | - | MD Hardware version. Unit motherboard hardware version. Value 1 corresponds to Rev.A, value 2 is B, value is C and so forth up to 27 which is Rev.Z |
| 599 | HREG_SW_VERSION | MD SW version | uint16 | 100 | - | MD Software release number |

### Filter Test Configuration

| Address | Symbol | Name | Type | Multiplier | Bounds | Description |
|---------|--------|------|------|------------|-------|-------------|
| 359 | HREG_FILTER_TEST_HR | Filter test hour | uint16 | 1 | - | Filter test will begin at this hour (HH:00) |
| 365 | HREG_FILTER_TEST_DAYS | Filter test day-of-week | uint16 | 1 | - | Filter test run on selected day on selected hour. Expressed as a bitfield similar to week time programs |
| 370 | HREG_FILTER_TEST_TF | Filter test TF fan speed | uint16 | 1 | - | During filter test mode TF will run at this constant fanspeed even in constant duct pressure mode. Note that if value is outside range 20-100, 100% will be used |
| 376 | HREG_FILTER_TEST_PF | Filter test PF fan speed | uint16 | 1 | - | During filter test mode PF will run at this constant fanspeed even in constant duct pressure mode. Note that if value is outside range 20-100, 100% will be used |

### Alarms (Registers 385-524)

Each alarm entry consists of 6 registers starting at 385 (Alarm 1, newest):

| Address Offset | Symbol | Name | Type | Multiplier | Bounds | Description |
|---------------|--------|------|------|------------|-------|-------------|
| +0 | ALARMx_ALMTYPE | Alarm log entry #x | uint16 | 1 | - | Alarm x alarm type |
| +1 | ALARMx_STATECLASS | - | uint16 | 1 | - | This defines status (low byte) of alarm |
| +2 | ALARMx_YY | - | uint16 | 1 | year | Alarm year |
| +3 | ALARMx_MM | - | uint16 | 1 | month | Alarm month |
| +4 | ALARMx_DD | - | uint16 | 1 | day | Alarm day |
| +5 | ALARMx_HH | - | uint16 | 1 | hour | Alarm hour |
| +6 | ALARMx_MI | - | uint16 | 1 | min | Alarm minutes |

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

### Alarm Configuration

| Address | Symbol | Name | Type | Multiplier | Bounds | Description |
|---------|--------|------|------|------------|-------|-------------|
| 538 | HREG_ALARM_SERVICE_TIME | Service reminder | uint16 | 1 | - | days | Number of days until service reminder alarm is signaled |
| 578 | HREG_B_ALARM_START | Start time | uint16 | 1 | - | h | B alarm relay signaling allowed start hour. The defined time is HH:00, where HH is register's value |
| 579 | HREG_B_ALARM_STOP | Ending time | uint16 | 1 | - | h | B alarm relay signaling allowed stop hour. The defined time is HH:00, where HH is register's value |
| 580 | HREG_B_ALARM_WEEKDAYS | Weekdays | bitfield | 1 | - | - | B alarm relay signaling allowed weekdays (bitmap, stored in low 7 bits of register). Bit 0: Sunday - Bit 6: Saturday |
| 581 | HREG_N_O_ALARMS | Number of alarms | uint16 | 1 | - | - | Current number of alarms in alarm log |

### RTC Configuration (Write-Only)

| Address | Symbol | Name | Type | Multiplier | Bounds | Description |
|---------|--------|------|------|------------|-------|-------------|
| 582 | HREG_C_MIN_RTC | - | uint16 | 1 | - | RTC interface for changing minutes field |
| 583 | HREG_C_HOUR_RTC | - | uint16 | 1 | - | RTC interface for changing hour field |
| 584 | HREG_C_DAY_RTC | - | uint16 | 1 | - | RTC interface for changing day of month field |
| 585 | HREG_C_MONTH_RTC | - | uint16 | 1 | - | RTC interface for changing month field |
| 586 | HREG_C_YEAR_RTC | - | uint16 | 1 | - | RTC interface for changing year field |

### Modbus Configuration

| Address | Symbol | Name | Type | Multiplier | Bounds | Description |
|---------|--------|------|------|------------|-------|-------------|
| 640 | HREG_MBADDR | Modbus id | uint16 | 1 | 1-100 | MD card modbus address 1 - 100 |

## Enumerators

### mode (Status Bitfield)

| Value | Label | Description |
|-------|--------|-------------|
| 0 | Home | Normal home mode |
| 1 | Max cooling | Max cooling mode |
| 2 | Max heating | Max heating mode |
| 4 | Alarm A | Machine stopped due to A alarm |
| 8 | Stop | Machine stopped by request (not due to alarm) |
| 16 | Away state | Away mode active |
| 32 | Temperature boost | Temperature boosting active |
| 64 | CO2 boosting | CO2 boosting active |
| 128 | RH boosting | %RH boosting active |
| 256 | Manual boost | Manual boosting active |
| 512 | Overpressure mode | Overpressure mode active |
| 1024 | Cooker hood mode | Cooker hood mode active |
| 2048 | Central vacuum cleaner mode | Central vacuum cleaner mode active |
| 8192 | Summer night cooling | Summer night cooling mode active |
| 16384 | Heat recovery wheel defrosting | Defrosting mode active |

### tempstep (Temperature Control Step Bitfield)

| Value | Label | Description |
|-------|--------|-------------|
| 0 | None | No active temperature control |
| 1 | Cooling | Active cooling |
| 2 | LTO | Heat recovery (LTO) active |
| 4 | Heating | Active heating |
| 6 | Summer night cooling | Summer night cooling active |
| 7 | Startup | Starting up phase |
| 8 | Dehumidification | Dehumidification active |

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

### alarmtypes

| Value | Label |
|-------|-------|
| 0 | No alarm |
| 1 | ALARM_TE05_L | TE05 minimum |
| 2 | ALARM_TE10_L | TE10 minimum |
| 3 | ALARM_TE10_H | TE10 maximum |
| 4 | ALARM_TE20_H | TE20 maximum |
| 5 | ALARM_TE30_L | TE30 minimum |
| 6 | ALARM_TE30_H | TE30 maximum |
| 7 | ALARM_HP | Heat pump (both HP and MDX) |
| 8 | ALARM_SLP | Sleep mode |
| 9 | ALARM_TE45_L | TE45 minimum |
| 10 | ALARM_LTO | Heat recovery system |
| 11 | ALARM_COOL | Cooling alarm |
| 12 | ALARM_EMERGENCY_STOP | Emergency stop activated |
| 13 | ALARM_EXTERNAL | External alarm input |
| 14 | ALARM_SERVICE | Service required |
| 15 | ALARM_PDS10 | Pressure sensor PDS10 |
| 16 | ALARM_SPLY_FILT_H | Supply filter high pressure |
| 17 | ALARM_EXT_FILT_H | Extract filter high pressure |
| 18 | ALARM_SPLY_FILT_L | Supply filter low pressure |
| 19 | ALARM_EXT_FILT_L | Extract filter low pressure |
| 20 | ALARM_TF_PRES | Supply air pressure issue |
| 21 | ALARM_PF_PRES | Exhaust air pressure issue |
| 22 | ALARM_TE50_H | TE50 high temperature |
| 24 | ALARM_TE52_H | TE52 high temperature |
| 25 | ALARM_TF_ROTATION | Supply fan rotation failure |
| 26 | ALARM_PF_ROTATION | Exhaust fan rotation failure |
| 27 | ALARM_TE02_H | TE02 high temperature |
| 28 | ALARM_SERVICE_CONSTANT_DUCT_PRES | Service alarm under constant duct pressure control |

### alarmstate

| Value | Label |
|-------|-------|
| 0 | ALARM_STATE_OFF | Alarm not active |
| 1 | ALARM_STATE_ACKED | Alarm has been acknowledged |
| 2 | ALARM_STATE_ON | Alarm is currently active |

### hw_version

| Value | Label |
|-------|-------|
| 1 | Rev.A |
| 2 | Rev.B |
| 3 | Rev.C |
| 4 | Rev.D |
| 5 | Rev.E |
| 6 | Rev.F |
| 7 | Rev.G |
| 8 | Rev.H |
| 9 | Rev.I |
| 10 | Rev.J |
| 11 | Rev.K |
| 12 | Rev.L |
| 13 | Rev.M |
| 14 | Rev.N |
| 15 | Rev.O |
| 16 | Rev.P |
| 17 | Rev.Q |
| 18 | Rev.R |
| 19 | Rev.S |
| 20 | Rev.T |
| 21 | Rev.U |
| 22 | Rev.V |
| 23 | Rev.W |
| 24 | Rev.X |
| 25 | Rev.Y |
| 26 | Rev.Z |
| 27 | Rev.AA |

### Time Program Functions

| Value | Label | Description |
|-------|--------|-------------|
| 0 | TIMER_PROGRAM_OFF | Turn off program |
| 1 | TIMER_AWAY | Activate away mode |
| 2 | TIMER_AWAY_LONG | Activate extended away mode |
| 3 | TIMER_HEAT_DIS | Disable heating |
| 4 | TIMER_COOL_DIS | Disable cooling |
| 5 | TIMER_TEMP_DECR | Activate temperature decrease |
| 6 | TIMER_MAX_H | Activate maximum heating |
| 7 | TIMER_MAX_C | Activate maximum cooling |
| 16 | TIMER_RELAY | Activate relay output |
| 17 | TIMER_BOOST | Activate boost mode |
| 18 | TIMER_CLOSED_CIRCULATION | Activate closed circulation air (Pallas only) |
| 30 | TIMER_RUNTIME | Enable machine running (OFFICE program variant) |

## Usage Notes

### Modbus Communication

- **Default settings**: 19200 bps, None parity, 8 data bits, 1 stop bit
- **Configurable speed**: 9600, 19200, or 115200 bps
- **Configurable parity**: None or Even parity
- **Device addressing**: Set via HREG_MBADDR (register 640), range 1-100
- **Register types**: Only holding registers (function 0x03) are supported on eAirMD

### Time Programs

The eAirMD supports extensive time-based automation:

**Week Programs (WC1-WC20):**
- 20 configurable weekly time slots
- Each slot can be assigned to specific days (bitmap)
- Supports start/stop time and function selection

**Year Programs (Y1-Y5):**
- 5 configurable yearly time slots
- For special dates or holidays
- Each slot can trigger specific functions

**Supported Functions:**
- Away mode, extended away mode
- Heat/cool disable
- Temperature decrease
- Max heating/cooling
- Relay activation
- Boost mode activation
- Closed circulation (Pallas variant)
- Runtime enable (OFFICE variant)

### Temperature Scaling

All temperature registers use a multiplier of 10:
- Raw value must be divided by 10 to get degrees Celsius
- Example: Raw value 215 = 21.5°C

### Alarm Management

The device maintains a detailed alarm log with up to 20 alarms:
- **Alarm 1** is the newest alarm
- **Alarm 20** is the oldest alarm
- Each alarm contains type, state, and timestamp
- Alarms can be acknowledged by writing to ALARMx_STATECLASS register (write 1 or 2)
- B alarm output can be time-restricted via registers 578-580

### Analog Input Configuration

The eAirMD supports up to 6 analog inputs (AI1-AI6):
- Each input can be configured for different sensor types
- Raw voltage readings (0-10V) available in registers 17-22
- Calculated values (scaled and offset) available in registers 23-28
- Voltage limits (VL/VH) and result limits (RL/RH) are configurable per input

### Network Status

The HREG_NWK_STATUS register (34) provides Ethernet connectivity status:
- Bitfield indicating link status, speed, duplex mode
- Can be used to verify network connectivity

### Filter Test Mode

The device includes a filter test feature:
- Configurable test time (hour and day of week)
- Separate fan speeds for supply (TF) and exhaust (PF) during test
- Runs even if in constant duct pressure mode
- Fan speed defaults to 100% if outside valid range (20-100%)

### Real-Time Clock

The device includes an RTC:
- Read current time via registers 37-42
- Set time via write-only registers 582-586
- Year is expressed as years since 2000 (e.g., 25 = 2025)

### Hardware Version Detection

- **HREG_HW_VERSION (598)**: Motherboard hardware revision
- **HREG_FAMILY_TYPE (597)**: Machine family type
- **HREG_SW_VERSION (599)**: Software version (multiplied by 100)

---

**Documentation source:** eAirMD-modbus-register-list-public-clean.csv
**Conformance:** MD software versions 1.14 and later
**Last updated:** 2025-01-27
