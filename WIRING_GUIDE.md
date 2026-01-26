# LG SP7R ESP32 Remote - Wiring Guide

## Components Needed

### Electronics
- ESP32 Dev Board (30-pin version recommended)
- IR LED (950nm, 5mm)
- 100Ω resistor (for IR LED)
- 2N2222 or similar NPN transistor (optional, for stronger IR signal)
- 15x Tactile push buttons (6mm x 6mm recommended)
- 500mAh LiPo battery (flat pack, ~30mm x 20mm x 5mm)
- TP4056 USB-C charging module with protection
- Small slide switch (for power on/off)
- 22-26 AWG wire for connections

### Tools
- Soldering iron and solder
- Wire strippers
- Multimeter (for testing)
- Hot glue or electrical tape

---

## IR LED Circuit

### Simple Circuit (Basic)
```
ESP32 GPIO 4 ----[ 100Ω resistor ]----[IR LED Anode]
                                       [IR LED Cathode]---- GND
```

### Transistor Circuit (Stronger Signal - Recommended)
```
ESP32 GPIO 4 ----[ 1kΩ resistor ]---- Base (2N2222)

3.3V ----[ 100Ω resistor ]---- Collector (2N2222) ----[IR LED Anode]
                                                        [IR LED Cathode]---- GND

                               Emitter (2N2222) ---- GND
```

**IR LED Polarity:**
- Longer leg = Anode (+)
- Shorter leg = Cathode (-)
- Flat side on LED body = Cathode side

---

## Button Wiring (All 15 Buttons)

Each button uses **INPUT_PULLUP** mode, so you only need 2 wires per button:
- One side connects to ESP32 GPIO pin
- Other side connects to **GND** (common ground)

### Button Pin Assignments

| Button          | ESP32 GPIO | Wire Color Suggestion |
|-----------------|------------|-----------------------|
| Power           | 13         | Red                   |
| Mute            | 12         | Orange                |
| Input           | 27         | Yellow                |
| Volume +        | 26         | Green                 |
| Volume -        | 25         | Blue                  |
| EQ Setting      | 33         | Purple                |
| Bluetooth       | 32         | Gray                  |
| Menu (3 Dots)   | 35         | White                 |
| Speaker Level   | 34         | Brown                 |
| Settings        | 39         | Black                 |
| Up              | 36         | Pink                  |
| Down            | 15         | Teal                  |
| Left            | 2          | Lime                  |
| Right           | 0          | Magenta               |
| Enter           | 4          | Cyan                  |

**Important:** GPIO 4 is shared with IR LED. If using simple IR circuit, reassign Enter button to GPIO 16 or 17.

### Common Ground Bus
Instead of running 15 separate ground wires back to ESP32:
1. Solder all button ground pins together
2. Run ONE wire from this common point to ESP32 GND
3. This saves space and reduces wire clutter

---

## Battery and Power Circuit

### Components
- **Battery:** 500mAh 3.7V LiPo (with JST connector)
- **Charger:** TP4056 USB-C module with battery protection
- **Switch:** SPST slide switch (between battery and ESP32)

### Wiring Diagram
```
LiPo Battery (+) ---- B+ on TP4056
LiPo Battery (-) ---- B- on TP4056

TP4056 OUT+ ---- Power Switch ---- ESP32 VIN (or 3.3V pin)
TP4056 OUT- ---- ESP32 GND

USB-C port on TP4056 for charging
```

### Notes
- **VIN vs 3.3V:** If your ESP32 has a voltage regulator, use VIN. Otherwise use 3.3V directly.
- **Charging:** You can charge while using the remote (TP4056 supports pass-through)
- **LED Indicators on TP4056:**
  - Red LED = Charging
  - Blue/Green LED = Fully charged

---

## Testing Steps

### 1. Test IR LED First
1. Upload `remote_mode.cpp` to ESP32
2. Point IR LED at phone camera
3. Press Power button
4. You should see purple/white light on phone camera when button pressed

### 2. Test Each Button
1. Open Serial Monitor (115200 baud)
2. Press each button one by one
3. Serial Monitor should show "Sending: [Button Name]"
4. Verify soundbar responds correctly

### 3. Test Deep Sleep
1. Wait 5 seconds without pressing buttons
2. Serial Monitor should show "Going to deep sleep..."
3. Press Power button to wake up
4. Should show "Woke up from button press"

### 4. Test Battery Life
1. Disconnect USB
2. Use the remote normally
3. Should last several months with deep sleep enabled

---

## Current Draw Estimates

- **Active (button pressed):** ~80mA for 200ms
- **Idle (waiting for button):** ~15mA
- **Deep sleep:** ~10µA (0.01mA)

**Battery Life Calculation:**
- 500mAh battery
- Assuming 20 button presses per day (4 seconds active time)
- 23 hours 59 minutes in deep sleep
- **Estimated life: 3-6 months per charge**

---

## 3D Printed Case Design Recommendations

### Dimensions
- Internal cavity: 60mm x 40mm x 15mm (minimum)
- Button spacing: 8-10mm center-to-center
- USB-C port cutout: 10mm x 5mm
- IR LED hole: 5.5mm diameter (front face)

### Button Layout Suggestion
```
┌─────────────────────┐
│   [PWR]     [MUTE]  │
│                     │
│   [VOL+]    [VOL-]  │
│                     │
│   [INPUT]   [EQ]    │
│                     │
│   [BT]      [MENU]  │
│                     │
│       [ ↑ ]         │
│   [ ← ] [✓] [ → ]   │
│       [ ↓ ]         │
│                     │
│   [SPKR]    [SET]   │
└─────────────────────┘
```

### Features to Include
- IR LED window (clear plastic or open hole)
- USB-C charging port access
- Power switch cutout (side)
- Screw posts for securing ESP32 board
- Battery compartment
- Snap-fit or screw-together design

---

## Troubleshooting

**Remote not working:**
1. Check IR LED polarity (reversed LED won't work)
2. Verify resistor value (too high = weak signal)
3. Point LED directly at soundbar sensor

**Buttons not responding:**
1. Test with multimeter in continuity mode
2. Verify GPIO pins aren't already in use
3. Check for loose wire connections

**Won't wake from sleep:**
1. Power button (GPIO 13) must be wired correctly
2. Verify common ground connection
3. Try pressing and holding for 1 second

**Battery drains quickly:**
1. Check for short circuits
2. Verify deep sleep is activating (check serial monitor)
3. Ensure power switch is working

---

## Next Steps

1. **Test the code** - Upload `remote_mode.cpp` and verify all buttons work
2. **Wire the buttons** - Start with just Power, Mute, and Volume buttons
3. **Add battery** - Install TP4056 and LiPo battery
4. **Design/print case** - Measure your components first!
5. **Final assembly** - Secure everything with hot glue or screws

Good luck with your build! 🎵
