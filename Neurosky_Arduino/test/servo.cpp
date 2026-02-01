#include <Servo.h>
#include<Arduino.h>

int RValue;
int GValue;   // use this for attention 0..100
int BValue;
String input = "";

const int SERVO_PIN = 9;
Servo sg90;

void setup() {
  Serial.begin(115200);
  sg90.attach(SERVO_PIN);
  sg90.write(90); // center
}

void loop() {
  if (Serial.available() > 0) {
    // Expect "R;G;B\n" where G is attention (0..100)
    input = Serial.readStringUntil('\n');
    input.trim();
    Serial.println(input);

    int ind1 = input.indexOf(';');
    int ind2 = input.indexOf(';', ind1 + 1);

    if (ind1 > 0 && ind2 > ind1) {
      RValue = input.substring(0, ind1).toInt();
      GValue = input.substring(ind1 + 1, ind2).toInt();   // attention
      BValue = input.substring(ind2 + 1).toInt();

      // Constrain attention and map to 0..180 degrees
      int attention = constrain(GValue, 0, 100);
      int angle = map(attention, 0, 100, 0, 180);         // 0→0°, 100→180°

      if (RValue == 1) {
        sg90.write(angle);  // move servo to mapped angle
      }
      // If RValue != 1, hold current position
    }
    // else: parse error, ignore
  }
}
