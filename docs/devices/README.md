# Enervent Pingvin Documentation

This directory contains documentation for the Enervent Pingvin HVAC ventilation system.

## Register Maps

Add your Enervent Pingvin register documentation here including:

- Holding registers (read/write)
- Input registers (read-only)
- Coil registers (read/write)
- Discrete input registers (read-only)

## Example Format

```markdown
## Register Map

| Address | Type    | Name                | Unit   | Scale | Writable | Description          |
|---------|---------|---------------------|--------|-------|----------|----------------------|
| 0x100   | Holding | Supply Air Temp     | °C     | 0.1   | No       | Supply air temperature|
| 0x101   | Holding | Extract Air Temp    | °C     | 0.1   | No       | Extract air temperature|
```

## Device Specifications

- **Device ID:** Default 1 (configurable)
- **Baudrate:** 9600 (configurable: 9600, 19200, 38400)
- **Protocol:** Modbus RTU
- **Connection:** RS485

## Notes

Add any specific notes about this device's communication requirements or peculiarities.

---

**Documentation provided by:** [Your Name]
**Last updated:** [Date]
