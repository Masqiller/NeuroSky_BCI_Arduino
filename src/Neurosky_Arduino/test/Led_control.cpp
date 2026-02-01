#include<Arduino.h>
int RValue;
int GValue;
int BValue;
String input = "";

const int LED_PIN = 7;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  if (Serial.available() > 0) {
    // Read one full line until newline to ensure complete packet
    input = Serial.readStringUntil('\n');  // e.g., "1;45;0"
    input.trim(); // remove any CR/LF or spaces

    // Optional: echo back
    Serial.println(input);

    // Find delimiters
    int ind1 = input.indexOf(';');
    int ind2 = input.indexOf(';', ind1 + 1);

    // Basic validation
    if (ind1 > 0 && ind2 > ind1) {
      // Parse values
      RValue = input.substring(0, ind1).toInt();
      GValue = input.substring(ind1 + 1, ind2).toInt();   // fixed end index
      BValue = input.substring(ind2 + 1).toInt();

      // Direct LED control on pin 7
      if (RValue == 1) {
        digitalWrite(LED_PIN, HIGH);
      } else {
        digitalWrite(LED_PIN, LOW);
      }
    } else {
      // Bad packet; ignore or handle error
      // Serial.println("Parse error");
    }
  }
}
