# LG SPD7R Soundbar ESP32 Remote

Custom IR remote replacement for the LG SPD7R 7.1 channel soundbar using ESP32.

## Overview

This project provides a complete replacement for the LG SPD7R soundbar remote (Model: AKB76038001) using an ESP32 microcontroller and an IR LED. Perfect for when your original remote gets lost or damaged.

## Features

- **4-Button Simplified Remote** - Power, Input, EQ Setting, and Speaker Level controls
- **Deep Sleep Mode** - 3-6 months battery life on a 500mAh LiPo
- **All 15 Button Codes Captured** - Complete IR code database included
- **Battery Powered** - USB-C rechargeable with TP4056 module
- **Open Source** - Full schematics, code, and wiring guides included

## Hardware Required

- ESP32 Development Board
- IR LED (950nm, 5mm)
- 100Ω resistor
- 4x tactile push buttons
- 500mAh 3.7V LiPo battery (optional)
- TP4056 USB-C charging module (optional)
- Breadboard and jumper wires for testing

## Quick Start

### 1. Install PlatformIO
Install [PlatformIO](https://platformio.org/) or use the VS Code extension.

### 2. Clone and Upload
```bash
git clone https://github.com/jakenbake350/LG-SPD7R-ESP32-Remote.git
cd LG-SPD7R-ESP32-Remote
pio run -t upload
```

### 3. Wire the Hardware
See [SIMPLE_WIRING.md](SIMPLE_WIRING.md) for complete wiring instructions.

**Basic connections:**
- GPIO 4 → 100Ω resistor → IR LED (+)
- IR LED (-) → GND
- GPIO 13 → Power button → GND
- GPIO 12 → Input button → GND
- GPIO 26 → EQ button → GND
- GPIO 25 → Speaker Level button → GND

### 4. Test
Point the IR LED at your soundbar and press a button!

## IR Code Database

All 15 button codes for the LG SPD7R have been captured and documented:

- **Protocol:** NEC
- **Address:** 0x2C (44 decimal)
- **Remote Model:** AKB76038001
- **Soundbar Model:** LG SPD7R 7.1 Channel

### Complete Button List

| Button               | Command (Hex) | Command (Dec) |
|---------------------|---------------|---------------|
| Power               | 0x1E          | 30            |
| Mute                | 0x1F          | 31            |
| Input               | 0x8A          | 138           |
| Volume +            | 0x17          | 23            |
| Volume -            | 0x16          | 22            |
| EQ Setting          | 0x2F          | 47            |
| Bluetooth           | 0x4C          | 76            |
| Menu (3 Dots)       | 0xA3          | 163           |
| Speaker Level       | 0x98          | 152           |
| Settings            | 0xA5          | 165           |
| Up                  | 0xA7          | 167           |
| Down                | 0xA6          | 166           |
| Left                | 0xA8          | 168           |
| Right               | 0xA9          | 169           |
| Enter               | 0xAA          | 170           |

See [LG_SPD7R_IR_CODES.txt](LG_SPD7R_IR_CODES.txt) for Arduino code format.

## Project Structure

```
LG-SPD7R-ESP32-Remote/
├── src/
│   └── main.cpp              # 4-button remote code (active)
├── LG_SPD7R_IR_CODES.txt     # Complete IR code documentation
├── LG_SPD7R_IRDB.csv         # IRDB format for database submission
├── LIRC_FORMAT.conf          # LIRC configuration file
├── SIMPLE_WIRING.md          # Wiring guide for 4-button version
├── WIRING_GUIDE.md           # Full 15-button wiring guide
├── IRDB_SUBMISSION_GUIDE.md  # How to submit codes to databases
└── platformio.ini            # PlatformIO configuration
```

## Battery Life

With deep sleep enabled (10-second timeout):
- **Active:** ~80mA for 200ms per button press
- **Idle:** ~15mA
- **Deep Sleep:** ~10µA
- **Estimated battery life:** 3-6 months per charge (500mAh LiPo)

## Versions

### Simple Remote (Current)
- 4 buttons: Power, Input, EQ, Speaker Level
- Perfect for daily use
- Only controls functions not available on TV remote

### Full Remote
- All 15 buttons from original remote
- See `WIRING_GUIDE.md` for full version

## Contributing to IR Databases

Want to help others? Submit these codes to:
- [IRDB](https://github.com/probonopd/irdb) - See `IRDB_SUBMISSION_GUIDE.md`
- [LIRC](https://lirc.org/) - Use `LIRC_FORMAT.conf`

## Troubleshooting

**Buttons don't work:**
- Verify button wiring (GPIO to GND)
- Check serial monitor for "Sending: [Button Name]" messages
- Ensure buttons are pressed firmly

**IR LED not working:**
- Check polarity (long leg = +, short leg = -)
- Test with phone camera (should see purple light)
- Try moving closer to soundbar (test from 1 foot away)

**Won't wake from sleep:**
- Power button MUST be on GPIO 13
- Verify GND connection is solid
- Hold button for 1 second

## License

MIT License - Feel free to use, modify, and share!

## Credits

Built using:
- [IRremote](https://github.com/Arduino-IRremote/Arduino-IRremote) library v4.5.0
- [PlatformIO](https://platformio.org/)
- ESP32 Arduino framework

## Related Projects

Looking for other LG soundbar remotes? Check the IR code files - these codes might work on similar LG soundbar models.

---

**Note:** This project was created out of necessity when the original remote was lost. Replacement remotes cost $30+ while this DIY solution costs ~$5-10 in parts.
