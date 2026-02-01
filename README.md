# Mind Control Examples - Neurosky EEG Brain-Computer Interface

<p align="center">
  <b>Control electronic devices with your mind using Neurosky MindWave EEG headset</b>
</p>

---

## 📋 Table of Contents

- [Overview](#overview)
- [Available Examples](#available-examples)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Project Structure](#project-structure)
- [Installation Guide](#installation-guide)
- [Example 1: LED Brightness Control](#example-1-led-brightness-control)
- [Example 2: Servo Motor Control](#example-2-servo-motor-control)
- [Example 3: Stepper Motor Control](#example-3-stepper-motor-control)
- [How It Works](#how-it-works)
- [Troubleshooting](#troubleshooting)
- [Contributing](#contributing)
- [License](#license)

---

## 🧠 Overview

**Mind Control Examples** is a collection of brain-computer interface (BCI) projects that allow you to control various electronic devices using your brainwaves. By monitoring your attention level through a Neurosky MindWave EEG headset, these examples demonstrate how to:

1. **Control LED brightness** - Dim or brighten an LED based on focus
2. **Move a servo motor** - Position a servo arm with your thoughts
3. **Rotate a stepper motor** - Precise positional control with mental focus

All examples use the attention metric (0-100) from the Neurosky headset and map it to appropriate control signals.

---

## ✨ Available Examples

| Example | Description | Control Type |
|---------|-------------|--------------|
| **LED Brightness** | Control LED brightness with attention | PWM (0-255) |
| **Servo Motor** | Control servo position with attention | Angle (0-180°) |
| **Stepper Motor** | Control stepper position with attention | Steps (0-2048) |

---

## 🔧 Hardware Requirements

| Component | Description | Quantity |
|-----------|-------------|----------|
| **Neurosky MindWave** | EEG headset (Mobile or Mobile 2) | 1 |
| **Arduino Board** | Arduino Uno, Nano, or compatible | 1 |
## 🔧 Hardware Requirements

### Common Components (All Examples)

| Component | Description | Quantity |
|-----------|-------------|----------|
| **Neurosky MindWave** | EEG headset (Mobile or Mobile 2) | 1 |
| **Arduino Board** | Arduino Uno, Nano, or compatible | 1 |
| **USB Cables** | For Arduino and Neurosky dongle | 2 |
| **Jumper Wires** | Male-to-female for connections | Various |
| **Breadboard** | For prototyping | 1 |

### Example-Specific Components

| Example | Components Needed |
|---------|-------------------|
| **LED Brightness** | LED, 220Ω resistor |
| **Servo Motor** | SG90 or similar servo motor |
| **Stepper Motor** | 28BYJ-48 stepper + ULN2003 driver |

---

## 💻 Software Requirements

- **Operating System**: Windows 7/8/10/11
- **Visual Studio**: 2013 or later (for building C# application)
- **.NET Framework**: 3.5 or later
- **Arduino IDE**: 1.8.x or 2.x (for uploading Arduino sketch)
- **ThinkGear Connector**: Required for Neurosky communication (included)

---

## 📁 Project Structure

```
MindControlExamples/
├── README.md                           # This documentation file
├── Drivers/                            # USB-to-Serial drivers (CH341)
│   ├── CH341SER.SYS
│   ├── CH341SER_MW.INF
│   ├── SETUP.EXE                       # Driver installer
│   └── DRVSETUP64/                     # 64-bit driver setup
├── ThinkGearConnector/                 # Neurosky ThinkGear Connector
│   ├── win32/                          # Windows executable
│   │   └── ThinkGear Connector.exe     # Run this for headset connection
│   └── *.pdf                           # Documentation
├── ThinkGearSDK/                       # Neurosky SDK libraries
│   └── libs/                           # SDK library files
└── src/                                # Source code
    ├── LEDBrightnessControl/           # Example 1: LED Control
    │   ├── CSharpApp/
    │   │   ├── MindLEDController.sln
    │   │   ├── MindLEDController.cs
    │   │   └── neurosky/
    │   └── MindLEDArduino/
    │       └── MindLEDArduino.ino
    ├── ServoControl/                   # Example 2: Servo Control
    │   ├── CSharpApp/
    │   │   ├── MindServoController.sln
    │   │   ├── MindServoController.cs
    │   │   └── neurosky/
    │   └── MindServoArduino/
    │       └── MindServoArduino.ino
    └── StepperMotorControl/            # Example 3: Stepper Control
        ├── CSharpApp/
        │   ├── MindStepperController.sln
        │   ├── MindStepperController.cs
        │   └── neurosky/
        └── MindStepperArduino/
            └── MindStepperArduino.ino
```

---

## 🚀 Installation Guide

### Step 1: Install USB Drivers

1. Navigate to the `Drivers/` folder
2. Run `SETUP.EXE` as Administrator
3. Follow the installation wizard
4. Restart your computer if prompted

### Step 2: Install ThinkGear Connector

1. Navigate to `ThinkGearConnector/win32/`
2. Run `ThinkGear Connector.exe`
3. This software bridges your Neurosky headset to applications

### Step 3: Choose and Upload Arduino Sketch

Choose the example you want to run:

| Example | Arduino Sketch Location |
|---------|------------------------|
| LED Brightness | `src/LEDBrightnessControl/MindLEDArduino/MindLEDArduino.ino` |
| Servo Motor | `src/ServoControl/MindServoArduino/MindServoArduino.ino` |
| Stepper Motor | `src/StepperMotorControl/MindStepperArduino/MindStepperArduino.ino` |

1. Open Arduino IDE
2. Open the appropriate `.ino` file
3. Select your Arduino board: **Tools > Board > Arduino Uno**
4. Select the correct COM port: **Tools > Port > COMx**
5. Click **Upload** button
6. Note the COM port number

### Step 4: Build C# Application

| Example | Solution File Location |
|---------|----------------------|
| LED Brightness | `src/LEDBrightnessControl/CSharpApp/MindLEDController.sln` |
| Servo Motor | `src/ServoControl/CSharpApp/MindServoController.sln` |
| Stepper Motor | `src/StepperMotorControl/CSharpApp/MindStepperController.sln` |

1. Open Visual Studio
2. Open the appropriate `.sln` file
3. Build the solution: **Build > Build Solution** (or press F6)
4. The executable will be in `bin/Debug/`

---

## 💡 Example 1: LED Brightness Control

Control LED brightness with your attention level. Higher focus = brighter LED.

### Wiring Diagram

```
Arduino                      LED Circuit
┌─────────────┐             ┌──────────┐
│         GND ├─────────────┤ Cathode  │
│             │             │   (-)    │
│      Pin 9  ├──[220Ω]─────┤ Anode    │
│    (PWM)    │             │   (+)    │
└─────────────┘             └──────────┘
```

### How It Works

- Attention Level (0-100) → PWM Value (0-255)
- 0% attention = LED off
- 50% attention = LED at 50% brightness
- 100% attention = LED fully bright

### Configuration

Edit `MindLEDController.cs`:
```csharp
const string NEUROSKY_COM_PORT = "COM3";   // Your Neurosky port
const string ARDUINO_COM_PORT = "COM12";    // Your Arduino port
```

Edit `MindLEDArduino.ino`:
```cpp
const int LED_PIN = 9;  // Must be a PWM pin (3, 5, 6, 9, 10, or 11)
```

---

## 🦾 Example 2: Servo Motor Control

Control a servo motor position with your attention level.

### Wiring Diagram

```
Arduino                    Servo Motor
┌─────────────┐           ┌──────────────┐
│         GND ├───────────┤ Brown (GND)  │
│          5V ├───────────┤ Red (VCC)    │
│      Pin 9  ├───────────┤ Orange (SIG) │
└─────────────┘           └──────────────┘
```

**Note**: For larger servos, use external 5V power supply.

### How It Works

- Attention Level (0-100) → Servo Angle (0-180°)
- 0% attention = 0 degrees
- 50% attention = 90 degrees (center)
- 100% attention = 180 degrees

### Features

- Smooth movement between positions
- Visual position indicator in console

### Configuration

Edit `MindServoController.cs`:
```csharp
const string NEUROSKY_COM_PORT = "COM3";   // Your Neurosky port
const string ARDUINO_COM_PORT = "COM12";    // Your Arduino port
```

Edit `MindServoArduino.ino`:
```cpp
const int SERVO_PIN = 9;
const int SMOOTHING_DELAY = 15;  // Adjust for smoother/faster movement
```

---

## ⚙️ Example 3: Stepper Motor Control

Control a stepper motor position with your attention level.

### Wiring Diagram

```
Arduino                    ULN2003 Driver         28BYJ-48 Stepper
┌─────────────┐           ┌──────────────┐       ┌──────────────┐
│         GND ├───────────┤ GND          │       │              │
│          5V ├───────────┤ VCC          ├───────┤  Motor       │
│      Pin 8  ├───────────┤ IN1          │       │  Connector   │
│      Pin 9  ├───────────┤ IN2          │       │              │
│     Pin 10  ├───────────┤ IN3          │       │              │
│     Pin 11  ├───────────┤ IN4          │       │              │
└─────────────┘           └──────────────┘       └──────────────┘
```

### How It Works

- Attention Level (0-100) → Position (0-2048 steps / 0-360°)
- 0% attention = starting position (0°)
- 50% attention = half rotation (180°)
- 100% attention = full rotation (360°)

### Features

- Precise positional control
- Change threshold to prevent jitter
- Auto-disable coils after movement (prevents overheating)

### Configuration

Edit `MindStepperController.cs`:
```csharp
const string NEUROSKY_COM_PORT = "COM3";   // Your Neurosky port
const string ARDUINO_COM_PORT = "COM12";    // Your Arduino port
const int CHANGE_THRESHOLD = 5;             // Minimum change to trigger movement
```

Edit `MindStepperArduino.ino`:
```cpp
const int MOTOR_PIN_1 = 8;   // IN1
const int MOTOR_PIN_2 = 10;  // IN2
const int MOTOR_PIN_3 = 9;   // IN3
const int MOTOR_PIN_4 = 11;  // IN4
const int MOTOR_SPEED = 10;  // RPM
```

---

## ⚙️ Common Configuration

### Finding COM Ports

1. Open **Device Manager**
2. Expand **Ports (COM & LPT)**
3. Look for:
   - "USB Serial Port" or "CH340" → Arduino
   - "Standard Serial over Bluetooth" → Neurosky

---

## 🎮 Usage

### Starting a Session

1. **Start ThinkGear Connector:**
   - Run `ThinkGearConnector/win32/ThinkGear Connector.exe`
   - Ensure it shows "Connected" status

2. **Put on the Headset:**
   - Place the sensor on your forehead
   - Clip the ear sensor to your earlobe
   - Ensure good contact (moisten if needed)

3. **Run the Application:**

   **LED Brightness Example:**
   ```
   cd src/LEDBrightnessControl/CSharpApp/bin/Debug
   MindLEDController.exe
   ```

   **Servo Motor Example:**
   ```
   cd src/ServoControl/CSharpApp/bin/Debug
   MindServoController.exe
   ```

   **Stepper Motor Example:**
   ```
   cd src/StepperMotorControl/CSharpApp/bin/Debug
   MindStepperController.exe
   ```

4. **Example Output (LED Brightness):**
   ```
   ==============================================
     Mind Control LED - Brightness Controller
   ==============================================

   Scanning for Neurosky headset on COM3...
   [SUCCESS] Neurosky device found on: COM3

   Connecting to Arduino on COM12...
   [SUCCESS] Connected to Arduino

   ==============================================
     Monitoring attention level...
     LED brightness = Attention level (0-100%)
   ==============================================

   Attention: [████████░░░░░░░░░░░░] 40%
     Attention: 40 -> PWM: 102 (40% brightness)
   
   Attention: [████████████████░░░░] 80%
     Attention: 80 -> PWM: 204 (80% brightness)
   ```

5. **End Session:**
   - Wait for session timeout, or
   - Press Ctrl+C to terminate

---

## 🧪 How It Works

### System Architecture

```
┌─────────────────┐    Bluetooth    ┌──────────────────┐
│  Neurosky       │ ──────────────► │  ThinkGear       │
│  MindWave       │                 │  Connector       │
└─────────────────┘                 └────────┬─────────┘
                                             │ TCP/Socket
                                             ▼
                                    ┌──────────────────┐
                                    │  C# Controller   │
                                    │  Application     │
                                    └────────┬─────────┘
                                             │ Serial (USB)
                                             ▼
                                    ┌──────────────────┐
                                    │  Arduino +       │
                                    │  Output Device   │
                                    └────────┬─────────┘
                                             │ Control Signal
                                             ▼
                                    ┌──────────────────┐
                                    │  LED / Servo /   │
                                    │  Stepper Motor   │
                                    └──────────────────┘
```

### Data Flow

1. **EEG Acquisition**: Neurosky headset detects brainwaves via forehead sensor
2. **Signal Processing**: ThinkGear ASIC chip processes raw EEG into attention values
3. **Data Transmission**: Bluetooth sends data to ThinkGear Connector
4. **Application Logic**: C# app processes attention level (0-100)
5. **Serial Command**: Sends `"attentionLevel;0;"` to Arduino
6. **Physical Control**: Arduino maps attention to output (PWM/Angle/Steps)

### Attention Meter

The attention value ranges from 0 to 100:
- **0-20**: Very low focus (distracted, drowsy)
- **20-40**: Low focus
- **40-60**: Moderate focus
- **60-80**: High focus
- **80-100**: Very high focus (deep concentration)

### Mapping Table

| Example | Input Range | Output Range | Formula |
|---------|-------------|--------------|---------|
| LED Brightness | 0-100 | 0-255 PWM | `PWM = attention × 2.55` |
| Servo Motor | 0-100 | 0-180° | `Angle = attention × 1.8` |
| Stepper Motor | 0-100 | 0-2048 steps | `Steps = attention × 20.48` |

---

## 🔍 Troubleshooting

### Issue: "No devices found"

**Causes & Solutions:**
- Headset not paired → Restart headset, wait for LED to stabilize
- Wrong COM port → Check Device Manager for correct port
- ThinkGear Connector not running → Start ThinkGear Connector first
- Bluetooth driver issue → Reinstall Bluetooth drivers

### Issue: Arduino not responding

**Causes & Solutions:**
- Wrong COM port → Check Device Manager
- Wrong baud rate → Ensure both use 115200
- Arduino not powered → Check USB connection
- Sketch not uploaded → Re-upload the correct .ino file

### Issue: LED not changing brightness

**Causes & Solutions:**
- Wrong pin → Use PWM capable pins (3, 5, 6, 9, 10, 11)
- Missing resistor → Always use 220Ω resistor with LED
- LED polarity → Check anode/cathode orientation

### Issue: Servo jittering

**Causes & Solutions:**
- Power issue → Use external 5V power for servo
- Noise on signal line → Add 100µF capacitor across power
- Too fast updates → Increase SMOOTHING_DELAY

### Issue: Stepper motor not moving

**Causes & Solutions:**
- Wrong pin order → Check IN1-IN4 pin mapping
- Insufficient power → Use external power for ULN2003
- Motor getting hot → Motor coils auto-disable after movement

### Issue: Erratic attention readings

**Causes & Solutions:**
- Poor sensor contact → Clean forehead, moisten sensor
- Electrical interference → Move away from electronics
- Muscle tension → Relax facial muscles
- Loose ear clip → Ensure proper contact

### Issue: Application crashes

**Causes & Solutions:**
- Missing DLL files → Ensure neurosky folder has all DLLs
- .NET Framework → Install .NET Framework 3.5
- Run as Administrator → Right-click, Run as Administrator

---

## 🛠️ Customization Ideas

- **Combine Examples**: Control multiple devices simultaneously
- **Meditation Mode**: Use meditation value instead of attention
- **Blink Control**: Implement blink-triggered actions
- **Data Logging**: Save attention data to file for analysis
- **GUI Version**: Create Windows Forms or WPF interface
- **Game Controller**: Use attention to control game characters

---

## 📚 References

- [Neurosky Developer Portal](http://developer.neurosky.com/)
- [ThinkGear .NET SDK Documentation](./ThinkGearSDK/)
- [Arduino Servo Library](https://www.arduino.cc/reference/en/libraries/servo/)
- [Arduino Stepper Library](https://www.arduino.cc/reference/en/libraries/stepper/)
- [Arduino Serial Communication](https://www.arduino.cc/reference/en/language/functions/communication/serial/)

---

## 👨‍💻 Author

**SMIT**  
Project: Mind Control Examples  
Version: 1.0.0  
Date: 2026

---

## 📄 License

This project is provided for educational purposes. Please ensure you follow all safety guidelines when working with electrical devices and motors.

---

<p align="center">
  <b>Control the world with your mind! 🧠⚡</b>
</p>
