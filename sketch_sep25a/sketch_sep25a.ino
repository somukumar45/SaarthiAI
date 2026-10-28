#include <AFMotor.h>

AF_DCMotor leftMotor(3);
AF_DCMotor rightMotor(4);

void setup() {
  Serial.begin(9600);

  leftMotor.setSpeed(150);
  rightMotor.setSpeed(150);

  Serial.println("SaarthiAI Motor System Ready");
}

void loop() {
  // Forward
  leftMotor.run(FORWARD);
  rightMotor.run(FORWARD);
  delay(2000);

  // Stop
  leftMotor.run(RELEASE);
  rightMotor.run(RELEASE);
  delay(2000);
}