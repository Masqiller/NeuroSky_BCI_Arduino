# NeuroSky BCI Arduino

Arduino firmware for NeuroSky Brain-Computer Interface (BCI) control system. This project receives commands from a host application (via serial communication) to control hardware outputs based on EEG brainwave data from NeuroSky headsets.

## Overview

This PlatformIO project provides the Arduino-side firmware that:
- Receives serial commands from a companion C# application
- Parses RGB/control values from the serial data
- Controls LED output based on brainwave-derived signals

## Hardware Requirements

- Arduino Uno (or compatible board)
- LED connected to pin 7
- USB connection to host computer running NeuroSky ThinkGear Connector

## Communication Protocol

The firmware expects serial data in the following format:
```
R;G;B\n
```

Where:
- `R` - Red/Control value (1 = LED ON, 0 = LED OFF)
- `G` - Green value (reserved for future use)
- `B` - Blue value (reserved for future use)

**Baud Rate:** 115200

## Project Structure

```
├── src/
│   └── main.cpp          # Main Arduino firmware
├── lib/
│   └── Servo/            # Servo library for motor control
├── test/
│   ├── Led_control.cpp   # LED control test
│   └── servo.cpp         # Servo control test
├── include/
└── platformio.ini        # PlatformIO configuration
```

## Building & Uploading

### Using PlatformIO CLI

```bash
# Build the project
pio run

# Upload to Arduino
pio run --target upload

# Monitor serial output
pio device monitor --baud 115200
```

### Using PlatformIO IDE (VS Code)

1. Open the project folder in VS Code with PlatformIO extension
2. Click the "Build" button (checkmark icon)
3. Click the "Upload" button (arrow icon)
4. Open Serial Monitor to view debug output

## Configuration

The project is configured for Arduino Uno in `platformio.ini`:

```ini
[env:uno]
platform = atmelavr
board = uno
framework = arduino
```

To use a different board, modify the `board` setting accordingly.

## Related Projects

This firmware works in conjunction with the NeuroSky Controller C# applications:
- **LED Brightness Control** - Control LED based on attention/meditation levels
- **Servo Control** - Control servo motors with brainwave data
- **Stepper Motor Control** - Control stepper motors with BCI

## License

This project is part of the NeuroSky Mind Control Examples collection.

## Author

Developed for Brain-Computer Interface research and experimentation.
