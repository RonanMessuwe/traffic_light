# Traffic Light Controller

Arduino-based traffic light controller with 8 operating modes, compliant with French road signaling regulations (IISR).

## Features

- ✅ **8 Operating Modes** - FR/US, UK, blinking orange, fixed colors, chase sequence
- ✅ **Regulatory Compliance** - Follows IISR (French Road Signaling Regulation) Part 6
- ✅ **7-Segment Display** - Optional mode display via CD4511 BCD decoder
- ✅ **Debounced Button** - Mode selection with proper debouncing
- ✅ **LED Feedback** - Visual confirmation on mode change with button LED flash
- ✅ **Modular Architecture** - Clean separation of concerns with classes
- ✅ **Reusable Button Library** - Button, ButtonLED, ButtonMultiLED with flash, blink, and chase effects
- ✅ **Configurable Timings** - Easy configuration via `Config.h`

## Regulatory Reference

This project implements timing specifications from the **INSTRUCTION INTERMINISTÉRIELLE SUR LA SIGNALISATION ROUTIÈRE (IISR)**, Part 6: Permanent traffic lights.

**Official Document:**
[IISR 6ème partie - Feux de circulation permanents](https://equipementsdelaroute.cerema.fr/IMG/pdf/iisr_6epartie_vc_20220613_cle2a3ec5.pdf)

### Key Requirements
- **Orange duration:** 3 seconds (mandatory)
- **Green minimum:** 6 seconds (regulatory minimum)
- **Red duration:** Typically 2 minutes in standard operation

## Hardware Configuration

### Components
- Arduino board (Uno, Nano, or compatible)
- Traffic light with 3 LEDs (Red, Orange, Green)
- Push button (simple Button) or button with integrated LED (ButtonLED) for mode selection
- Optional: 7-segment display with CD4511 BCD decoder

### Pin Assignments

| Component | Pin | Notes |
|-----------|-----|-------|
| Red lamp | 2 | Digital output |
| Orange lamp | 3 | Digital output |
| Green lamp | 4 | Digital output |
| Mode button | 8 | INPUT_PULLUP |
| Button LED | 13 | Digital output (optional, for ButtonLED) |
| Display A | 9 | BCD bit 0 |
| Display B | 10 | BCD bit 1 |
| Display C | 11 | BCD bit 2 |
| Display D | 12 | BCD bit 3 |

## Operating Modes

### Mode 1: FR / US Standard
Standard French/US traffic light sequence:
1. **Red** - 120 seconds (2 minutes)
2. **Green** - 6 seconds (regulatory minimum)
3. **Orange** - 3 seconds (mandatory duration)

### Mode 2: UK Standard
British traffic light sequence with red+orange transition:
1. **Red** - 120 seconds
2. **Red + Orange** - 3 seconds (prepare to go)
3. **Green** - 6 seconds
4. **Orange** - 3 seconds

### Mode 3: Blinking Orange
Warning/caution mode:
- **Orange blinks** at 1 Hz (500ms on, 500ms off)

### Mode 4: Fixed Red
Emergency stop mode:
- **Red** continuously on

### Mode 5: Fixed Orange
Caution/warning mode:
- **Orange** continuously on

### Mode 6: Fixed Green
Free passage mode:
- **Green** continuously on

### Mode 7: All Lights On
Test mode:
- **All lights** on simultaneously

### Mode 8: Chase Sequence
Animation mode:
- Red → Orange → Green → Orange (500ms each step)

## Software Architecture

### Class Diagram

```
┌──────────────┐     ┌──────────────┐     ┌──────────────┐
│ TrafficLight │     │ TrafficState │     │    Button    │
├──────────────┤     ├──────────────┤     ├──────────────┤
│ - redPin     │     │ - currentMode│     │ - pin        │
│ - orangePin  │     │ - currentStep│     │ - debounceMs │
│ - greenPin   │     │ - stepStart  │     │ - state      │
├──────────────┤     ├──────────────┤     ├──────────────┤
│ + begin()    │     │ + setMode()  │     │ + begin()    │
│ + apply()    │     │ + nextMode() │     │ + update()   │
└──────────────┘     │ + update()   │     │ + wasPressed()│
                     │ + current()  │     └──────────────┘
                     └──────────────┘              ▲
                            ▲                      │
                            │              ┌───────┴───────┐
                     ┌──────┴──────┐       │               │
                     │    Step     │  ┌────┴─────┐  ┌──────┴───────┐
                     ├─────────────┤  │ ButtonLED│  │ButtonMultiLED│
                     │ - red       │  ├──────────┤  ├──────────────┤
                     │ - orange    │  │+ flash() │  │+ flash(idx)  │
                     │ - green     │  │+ blink() │  │+ setExclusive│
                     │ - durationMs│  └──────────┘  │+ chase()     │
                     └─────────────┘       │        └──────────────┘
                                           │              │
                                      ┌────┴──────────────┴────┐
                                      │   LEDController        │
                                      ├────────────────────────┤
                                      │ - pin                  │
                                      │ - isFlashing           │
                                      │ - isBlinking           │
                                      ├────────────────────────┤
                                      │ + set()                │
                                      │ + flash()              │
                                      │ + startBlink()         │
                                      └────────────────────────┘

┌──────────────┐
│  IDisplay    │ (interface)
├──────────────┤
│ + begin()    │
│ + show()     │
└──────────────┘
        ▲
        │
        ├──────────────────────────┐
        │                          │
┌───────┴──────────┐    ┌──────────┴────────┐
│ SevenSegment     │    │    NoDisplay      │
│ BCDDisplay       │    ├───────────────────┤
├──────────────────┤    │ (empty impl.)     │
│ - bcdPins[4]     │    └───────────────────┘
│ - latchPin       │
├──────────────────┤
│ + begin()        │
│ + show()         │
└──────────────────┘
```

## Project Structure

```
traffic_light/
├── README.md
├── .gitignore
└── src/
    └── traffic_light/
        ├── traffic_light.ino         # Main entry point
        ├── Config.h                  # Hardware & timing configuration
        ├── TrafficLight.h/cpp        # LED control
        ├── TrafficState.h/cpp        # State machine & modes
        ├── Button.h/cpp              # Button with debouncing
        ├── ButtonLED.h/cpp           # Button with single LED feedback
        ├── ButtonMultiLED.h/cpp      # Button with multiple LEDs
        ├── LEDController.h/cpp       # LED timing controller
        ├── IDisplay.h                # Display interface
        ├── SevenSegmentBCDDisplay.h/cpp  # 7-segment implementation
        └── NoDisplay.h               # Null display implementation
```

## Configuration

### Hardware Configuration (`Config.h`)

Enable/disable 7-segment display:
```cpp
#define USE_7_SEGMENT_DISPLAY 1  // 1 = enabled, 0 = disabled
```

Pin assignments:
```cpp
#define RED_LAMP_PIN 2
#define ORANGE_LAMP_PIN 3
#define GREEN_LAMP_PIN 4
#define MODE_BUTTON_PIN 8
#define MODE_BUTTON_LED_PIN 13  // For ButtonLED
```

### Timing Configuration (`Config.h`)

Regulatory durations:
```cpp
#define RED_DURATION_MS    120000  // 2 minutes
#define GREEN_DURATION_MS    6000  // 6 seconds
#define ORANGE_DURATION_MS   3000  // 3 seconds
```

Animation durations:
```cpp
#define BLINK_DURATION_MS  500  // Blink rate
#define CHASE_STEP_MS      500  // Chase animation speed
```

## Building & Installation

### Arduino IDE

1. Open `src/traffic_light/traffic_light.ino` in Arduino IDE
2. Select your board: **Tools → Board → Arduino Uno** (or your board)
3. Select the port: **Tools → Port → COM3** (or your port)
4. Click **Upload** (Ctrl+U)

### Arduino CLI

```bash
# Compile
arduino-cli compile --fqbn arduino:avr:uno src/traffic_light

# Upload
arduino-cli upload -p /dev/ttyUSB0 --fqbn arduino:avr:uno src/traffic_light
```

### PlatformIO

```bash
pio run --target upload
```

## Usage

1. **Power on** - The system starts in Mode 1 (FR/US standard)
2. **Press the button** - Cycles through modes 1→2→3→...→8→1
3. **7-segment display** (if enabled) - Shows current mode number (1-8)

### Button Behavior
- **Short press** - Switch to next mode
- **LED flash** - 250ms visual feedback on mode change (when using ButtonLED)
- **Debounce time** - 50ms (configurable in `Config.h`)

## Technical Details

### Memory Usage
Estimated RAM usage: ~200 bytes
Flash (program) usage: ~2-3 KB

### Timing Precision
- Uses `millis()` for timing (1ms resolution)
- Protected against `millis()` overflow (49-day rollover)
- Non-blocking implementation

### Key Features
- **Modular design** - Easy to add new modes or displays
- **Strategy pattern** - Display interface allows multiple implementations
- **Const correctness** - Read-only data in PROGMEM
- **Type safety** - `uint8_t` for small values, proper types throughout

## Extending the Project

### Adding a New Mode

1. Define the mode sequence in `TrafficState.cpp`:
```cpp
const Step MODE_NEW[] = {
  withDuration(RED_LIGHT, 5000),
  withDuration(GREEN_LIGHT, 3000)
};
```

2. Add to `MODES` array:
```cpp
const Mode MODES[] = {
  // ... existing modes ...
  { MODE_NEW, 2 }
};
```

3. Update `MODE_COUNT`:
```cpp
#define MODE_COUNT 9  // Was 8
```

### Adding Multiple Buttons

```cpp
ButtonLED modeButton(MODE_BUTTON_PIN, MODE_LED_PIN, DEBOUNCE_MS);
Button pauseButton(PAUSE_BUTTON_PIN, DEBOUNCE_MS);

void loop() {
  modeButton.update();
  pauseButton.update();

  if (modeButton.wasPressed()) {
    trafficState.nextMode();
    modeButton.flash(250);  // Visual feedback
  }
  if (pauseButton.wasPressed()) { /* pause logic */ }
  // ...
}
```

### Button Classes Overview

**Button** - Simple debounced button:
```cpp
Button btn(8, 50);  // pin 8, 50ms debounce
btn.begin();
btn.update();
if (btn.wasPressed()) { /* action */ }
```

**ButtonLED** - Button with single LED:
```cpp
ButtonLED btn(8, 13, 50);  // button pin 8, LED pin 13, 50ms debounce
btn.begin();
btn.update();
if (btn.wasPressed()) btn.flash(250);  // Flash on press
btn.startBlink(1000);  // Continuous blink (1 Hz)
btn.setLED(true);  // Direct control
```

**ButtonMultiLED** - Button with multiple LEDs (max 3):
```cpp
uint8_t ledPins[] = {5, 6, 7};  // RGB LEDs (max 3 LEDs supported)
ButtonMultiLED btn(8, ledPins, 3, 50);
btn.begin();
btn.update();
btn.setExclusiveLED(0);  // Turn on LED 0, turn off others
btn.flash(1, 250);  // Flash LED 1
btn.startChase(200);  // Sequential chase pattern
```

## License

This project is provided as-is for educational purposes.

## Author

Created for Arduino traffic light control with regulatory compliance.

## Acknowledgments

- IISR (French Road Signaling Regulation) for timing specifications
- CEREMA for publishing the official documentation
