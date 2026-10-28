#include <AFMotor.h>

AF_DCMotor motorLeft(3);   // Motor connected to M3
AF_DCMotor motorRight(4);  // Motor connected to M4

void setup() {
  Serial.begin(9600);

  motorLeft.setSpeed(150);
  motorRight.setSpeed(150);

  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);

  Serial.println("SaarthiAI Motor Control Ready");
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();

    switch (command) {
      case 'F':
        motorLeft.run(FORWARD);
        motorRight.run(FORWARD);
        break;

      case 'B':
        motorLeft.run(BACKWARD);
        motorRight.run(BACKWARD);
        break;

      case 'L':
        motorLeft.run(BACKWARD);
        motorRight.run(FORWARD);
        break;

      case 'R':
        motorLeft.run(FORWARD);
        motorRight.run(BACKWARD);
        break;

      case 'S':
        motorLeft.run(RELEASE);
        motorRight.run(RELEASE);
        break;
    }
  }
}