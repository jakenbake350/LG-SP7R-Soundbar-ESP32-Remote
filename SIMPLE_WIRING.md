# 6-Button LG SP7R Remote - Simple Wiring Guide

## What You Need

### Electronics
- ESP32 Dev Board (your spare one)
- IR LED (950nm, 5mm)
- NPN transistor (2N2222A or similar)
- 100Ω resistor (IR LED current limit)
- 1kΩ resistor (transistor base)
- 6x Tactile push buttons
- Breadboard and jumper wires (for testing)
- Optional: 500mAh LiPo + TP4056 charger (for battery power)

---

## IR LED Wiring

The ESP32's GPIO pins can only safely supply ~12mA, but IR LEDs need 20-50mA for good range. A transistor lets GPIO 4 switch higher current without stressing the pin.

```
3.3V ──[ 100Ω ]──── IR LED (+) long leg
                    IR LED (-) short leg ──── NPN Collector
GPIO 4 ──[ 1kΩ ]── NPN Base
                    NPN Emitter ──────────── GND
```

**IR LED Polarity:**
- Long leg = + (Anode) → 100Ω → 3.3V
- Short leg = - (Cathode) → NPN Collector

**2N2222A Pinout** (flat side facing you, pins down):
- Left = Emitter → GND
- Middle = Base → 1kΩ → GPIO 4
- Right = Collector → IR LED (-)

---

## Button Wiring

Each button connects between a GPIO pin and GND (no resistors needed - using internal pull-ups).

### Pin Assignments

| Button        | ESP32 GPIO | Function                          |
|---------------|------------|-----------------------------------|
| Power         | 13         | Turn soundbar on/off              |
| Input         | 12         | Switch HDMI/ARC/Optical/etc       |
| Speaker Level | 27         | Cycle through and adjust individual speaker levels |
| EQ Setting    | 26         | Cycle through sound modes         |
| Menu          | 25         | Open 3 dots menu                  |
| Settings      | 33         | Open settings menu                |

### Breadboard Layout (Top View)
```
ESP32 Board
┌─────────────────┐
│                 │
│  [3.3V]  [GND]  │───┐
│   [13]          │   │
│   [12]          │   │  All buttons share
│   [27]          │   │  common GND
│   [26]          │   │
│   [25]          │   │
│   [33]          │   │
│   [4]───────────│───┼─── [1kΩ] ── NPN Base
│  [3.3V]         │   │             NPN Collector ── IR LED (-)
│                 │   │    3.3V ──[ 100Ω ]── IR LED (+)
│                 │   │             NPN Emitter ──── GND
└─────────────────┘   │
                      │
  [BTN1]──────────────┤
  Power (13 to GND)   │
                      │
  [BTN2]──────────────┤
  Input (12 to GND)   │
                      │
  [BTN3]──────────────┤
  Speaker Level       │
  (27 to GND)         │
                      │
  [BTN4]──────────────┤
  EQ (26 to GND)      │
                      │
  [BTN5]──────────────┤
  Menu (25 to GND)    │
                      │
  [BTN6]──────────────┤
  Settings (33 to GND)│
                      │
                    [GND]
```

---

## Step-by-Step Breadboard Test

### 1. Insert ESP32 into breadboard
- Make sure USB port is accessible

### 2. Wire the IR LED (with transistor)
```
3.3V → 100Ω resistor → IR LED long leg (+)
IR LED short leg (-) → NPN Collector (right pin, flat side facing you)
GPIO 4 → 1kΩ resistor → NPN Base (middle pin)
NPN Emitter (left pin) → GND
```

### 3. Wire the buttons
For each button:
- One leg → GPIO pin (13, 12, 27, 26, 25, or 33)
- Other leg → GND rail

### 4. Upload the code
- Open this project in PlatformIO
- `src/main.cpp` is already the 6-button remote — just upload
- Click Upload (or `pio run -t upload`)

### 5. Test!
- Open Serial Monitor (115200 baud)
- Point IR LED at soundbar
- Press each button and verify:
  - Serial shows "Sending: [Button Name]"
  - Soundbar responds correctly

---

## Testing Checklist

- [ ] Power button turns soundbar on/off
- [ ] Input button cycles through sources
- [ ] EQ button changes sound mode (Standard/Bass Blast/etc)
- [ ] Speaker Level button opens speaker menu
- [ ] Deep sleep activates after 10 seconds
- [ ] Power button wakes from sleep

---

## Quick Commands

**Upload code:**
```bash
pio run -t upload
```

**Monitor serial output:**
```bash
pio device monitor
```

**If COM port is locked:**
```bash
taskkill /F /IM python.exe
taskkill /F /IM pio.exe
```

---

## Battery Power (Optional)

If you want to make it portable:

**Components:**
- 500mAh 3.7V LiPo battery
- TP4056 USB-C charging module

**Wiring:**
```
Battery (+) ─── TP4056 B+
Battery (-) ─── TP4056 B-

TP4056 OUT+ ─── ESP32 3.3V or VIN
TP4056 OUT- ─── ESP32 GND
```

**Battery Life:** 3-6 months per charge with deep sleep enabled

---

## Troubleshooting

**Buttons don't work:**
- Check button is wired between GPIO and GND
- Verify button isn't broken (test continuity with multimeter)
- Try pressing harder (some buttons need firm press)

**IR LED not working:**
- Check polarity (long leg to 100Ω/3.3V, short leg to Collector)
- Verify transistor orientation (flat side facing you: E-B-C left to right)
- Test with phone camera (you should see purple light when button pressed)

**Soundbar doesn't respond:**
- Point LED directly at soundbar IR sensor (usually front panel)
- Move closer (test from 1 foot away)
- Make sure soundbar is on

**Won't wake from sleep:**
- Power button MUST be on GPIO 13
- Check GND connection is solid
- Try holding Power button for 1 second

---

## Next Steps

Once breadboard testing works:
1. Solder everything onto a perfboard or custom PCB
2. Add battery and charging module
3. Design/3D print a small case
4. Enjoy your custom mini remote!

**Estimated build time:** 30 minutes on breadboard, 2-3 hours for permanent build
