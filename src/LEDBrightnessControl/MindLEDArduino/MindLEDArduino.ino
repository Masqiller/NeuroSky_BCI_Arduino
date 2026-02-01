/*
 * MindLEDArduino - LED Brightness Controller for Neurosky EEG
 * 
 * This sketch receives attention level data from the C# application
 * via serial communication and controls LED brightness using PWM.
 * The attention level (0-100) is mapped to PWM values (0-255).
 * 
 * Hardware Setup:
 * - LED connected to PWM pin 9 (with appropriate resistor ~220Ω)
 * - Serial communication at 115200 baud
 * 
 * Command Protocol:
 * - Format: "attentionLevel;reserved;"
 * - attentionLevel: 0-100 (maps to PWM 0-255)
 * - reserved: Reserved for future use
 * 
 * Author: SMIT
 * Version: 1.0.0
 * Date: 2026
 */

// ============================================
// Configuration Constants
// ============================================
const int LED_PIN = 9;             // PWM pin connected to LED (must be PWM capable: 3,5,6,9,10,11)
const int BAUD_RATE = 115200;      // Serial communication baud rate

// Attention level boundaries
const int ATTENTION_MIN = 0;
const int ATTENTION_MAX = 100;

// PWM output boundaries
const int PWM_MIN = 0;
const int PWM_MAX = 255;

// ============================================
// Global Variables
// ============================================
int attentionLevel = 0;            // Received attention level (0-100)
int reservedValue = 0;             // Reserved for future functionality
int pwmValue = 0;                  // Calculated PWM value (0-255)
String serialInput = "";           // Buffer for incoming serial data

// ============================================
// Setup Function - Runs once at startup
// ============================================
void setup() {
    // Initialize serial communication
    Serial.begin(BAUD_RATE);
    
    // Configure LED pin as output
    pinMode(LED_PIN, OUTPUT);
    
    // Ensure LED starts OFF
    analogWrite(LED_PIN, 0);
    
    // Send ready message
    Serial.println("MindLEDArduino Ready");
    Serial.println("LED Brightness Control - Attention Level Mapping");
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
        
        // Map attention level (0-100) to PWM value (0-255)
        pwmValue = map(attentionLevel, ATTENTION_MIN, ATTENTION_MAX, PWM_MIN, PWM_MAX);
        
        // Set LED brightness
        analogWrite(LED_PIN, pwmValue);
        
        // Send feedback
        Serial.print("Attention: ");
        Serial.print(attentionLevel);
        Serial.print(" -> PWM: ");
        Serial.print(pwmValue);
        Serial.print(" (");
        Serial.print((pwmValue * 100) / 255);
        Serial.println("% brightness)");
    }
}
