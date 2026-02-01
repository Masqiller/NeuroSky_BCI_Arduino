/*
 * MindStepperArduino - Stepper Motor Controller for Neurosky EEG
 * 
 * This sketch receives attention level data from the C# application
 * via serial communication and controls a stepper motor.
 * The attention level (0-100) is mapped to stepper motor position/speed.
 * 
 * Hardware Setup:
 * - ULN2003 driver or similar stepper driver
 * - 28BYJ-48 stepper motor (or compatible)
 * - Pins 8, 9, 10, 11 connected to driver IN1, IN2, IN3, IN4
 * - External power supply recommended for motor
 * 
 * Command Protocol:
 * - Format: "attentionLevel;reserved;"
 * - attentionLevel: 0-100 (controls target position)
 * - reserved: Reserved for future use
 * 
 * Modes:
 * - Position Mode: Attention level sets target position (0-100 maps to 0-2048 steps)
 * - The motor moves to match your focus level
 * 
 * Author: SMIT
 * Version: 1.0.0
 * Date: 2026
 */

#include <Stepper.h>

// ============================================
// Configuration Constants
// ============================================
// Steps per revolution for 28BYJ-48 stepper motor
const int STEPS_PER_REV = 2048;

// Stepper motor pins (connected to ULN2003 driver)
const int MOTOR_PIN_1 = 8;         // IN1
const int MOTOR_PIN_2 = 10;        // IN2
const int MOTOR_PIN_3 = 9;         // IN3
const int MOTOR_PIN_4 = 11;        // IN4

const int BAUD_RATE = 115200;      // Serial communication baud rate

// Attention level boundaries
const int ATTENTION_MIN = 0;
const int ATTENTION_MAX = 100;

// Position boundaries (in steps)
const int POSITION_MIN = 0;
const int POSITION_MAX = STEPS_PER_REV;  // Full rotation

// Motor speed (RPM)
const int MOTOR_SPEED = 10;

// ============================================
// Global Variables
// ============================================
// Initialize stepper motor (Note: pin order matters for 28BYJ-48)
Stepper mindStepper(STEPS_PER_REV, MOTOR_PIN_1, MOTOR_PIN_3, MOTOR_PIN_2, MOTOR_PIN_4);

int attentionLevel = 0;            // Received attention level (0-100)
int reservedValue = 0;             // Reserved for future functionality
int targetPosition = 0;            // Target position in steps
int currentPosition = 0;           // Current position in steps
String serialInput = "";           // Buffer for incoming serial data

// ============================================
// Setup Function - Runs once at startup
// ============================================
void setup() {
    // Initialize serial communication
    Serial.begin(BAUD_RATE);
    
    // Set motor speed
    mindStepper.setSpeed(MOTOR_SPEED);
    
    // Send ready message
    Serial.println("MindStepperArduino Ready");
    Serial.println("Stepper Motor Position Control");
    Serial.println("Attention 0 = Start, Attention 100 = Full Rotation");
    
    // Initialize position
    currentPosition = 0;
}

// ============================================
// Main Loop - Runs continuously
// ============================================
void loop() {
    // Check if data is available on serial port
    if (Serial.available() > 0) {
        // Read the incoming string
        serialInput = Serial.readString();
        
        // Echo received command for debugging
        Serial.print("Received: ");
        Serial.println(serialInput);
        
        // Parse the command string
        // Format: "attentionLevel;reserved;"
        int delimiter1 = serialInput.indexOf(';');
        attentionLevel = serialInput.substring(0, delimiter1).toInt();
        
        int delimiter2 = serialInput.indexOf(';', delimiter1 + 1);
        reservedValue = serialInput.substring(delimiter1 + 1, delimiter2 + 1).toInt();

        // Constrain attention level to valid range
        attentionLevel = constrain(attentionLevel, ATTENTION_MIN, ATTENTION_MAX);
        
        // Map attention level (0-100) to position (0-STEPS_PER_REV)
        targetPosition = map(attentionLevel, ATTENTION_MIN, ATTENTION_MAX, 
                             POSITION_MIN, POSITION_MAX);
        
        // Calculate steps needed to reach target
        int stepsToMove = targetPosition - currentPosition;
        
        // Move stepper motor
        if (stepsToMove != 0) {
            Serial.print("Moving ");
            Serial.print(abs(stepsToMove));
            Serial.print(" steps ");
            Serial.println(stepsToMove > 0 ? "clockwise" : "counter-clockwise");
            
            mindStepper.step(stepsToMove);
            currentPosition = targetPosition;
        }
        
        // Send feedback
        Serial.print("Attention: ");
        Serial.print(attentionLevel);
        Serial.print("% -> Position: ");
        Serial.print(currentPosition);
        Serial.print("/");
        Serial.print(STEPS_PER_REV);
        Serial.print(" steps (");
        Serial.print((currentPosition * 360) / STEPS_PER_REV);
        Serial.println(" degrees)");
        
        // Disable motor coils after movement to prevent overheating
        disableMotor();
    }
}

// ============================================
// Disable Motor Coils
// ============================================
void disableMotor() {
    // Set all motor pins LOW to disable coils and save power
    digitalWrite(MOTOR_PIN_1, LOW);
    digitalWrite(MOTOR_PIN_2, LOW);
    digitalWrite(MOTOR_PIN_3, LOW);
    digitalWrite(MOTOR_PIN_4, LOW);
}
