/*
 * MindServoArduino - Servo Controller for Neurosky EEG
 * 
 * This sketch receives attention level data from the C# application
 * via serial communication and controls a servo motor position.
 * The attention level (0-100) is mapped to servo angle (0-180 degrees).
 * 
 * Hardware Setup:
 * - Servo signal wire connected to pin 9
 * - Servo power (red) to 5V or external power supply
 * - Servo ground (brown/black) to GND
 * - Serial communication at 115200 baud
 * 
 * Command Protocol:
 * - Format: "attentionLevel;reserved;"
 * - attentionLevel: 0-100 (maps to angle 0-180)
 * - reserved: Reserved for future use
 * 
 * Author: SMIT
 * Version: 1.0.0
 * Date: 2026
 */

#include <Servo.h>

// ============================================
// Configuration Constants
// ============================================
const int SERVO_PIN = 9;           // PWM pin connected to servo signal wire
const int BAUD_RATE = 115200;      // Serial communication baud rate

// Attention level boundaries
const int ATTENTION_MIN = 0;
const int ATTENTION_MAX = 100;

// Servo angle boundaries
const int SERVO_MIN_ANGLE = 0;
const int SERVO_MAX_ANGLE = 180;

// Smoothing settings
const int SMOOTHING_DELAY = 15;    // Delay between angle increments (ms)

// ============================================
// Global Variables
// ============================================
Servo mindServo;                   // Servo object
int attentionLevel = 0;            // Received attention level (0-100)
int reservedValue = 0;             // Reserved for future functionality
int targetAngle = 0;               // Target servo angle (0-180)
int currentAngle = 0;              // Current servo angle for smooth movement
String serialInput = "";           // Buffer for incoming serial data

// ============================================
// Setup Function - Runs once at startup
// ============================================
void setup() {
    // Initialize serial communication
    Serial.begin(BAUD_RATE);
    
    // Attach servo to pin
    mindServo.attach(SERVO_PIN);
    
    // Start at center position
    currentAngle = 90;
    mindServo.write(currentAngle);
    
    // Send ready message
    Serial.println("MindServoArduino Ready");
    Serial.println("Servo Position Control - Attention Level Mapping");
    Serial.println("Attention 0 = 0 degrees, Attention 100 = 180 degrees");
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
        
        // Map attention level (0-100) to servo angle (0-180)
        targetAngle = map(attentionLevel, ATTENTION_MIN, ATTENTION_MAX, 
                          SERVO_MIN_ANGLE, SERVO_MAX_ANGLE);
        
        // Move servo smoothly to target position
        moveServoSmooth(targetAngle);
        
        // Send feedback
        Serial.print("Attention: ");
        Serial.print(attentionLevel);
        Serial.print(" -> Angle: ");
        Serial.print(currentAngle);
        Serial.println(" degrees");
    }
}

// ============================================
// Smooth Servo Movement Function
// ============================================
void moveServoSmooth(int target) {
    // Move incrementally toward target for smooth motion
    while (currentAngle != target) {
        if (currentAngle < target) {
            currentAngle++;
        } else {
            currentAngle--;
        }
        mindServo.write(currentAngle);
        delay(SMOOTHING_DELAY);
    }
}
