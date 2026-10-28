// NAVIGON FINAL ARDUINO FIRMWARE (M3 & M4 Motors + Direct SER1/SERVO_2 Ultrasonic Sensor)
#define MOTORLATCH 12
#define MOTORCLK 4
#define MOTORENABLE 7
#define MOTORDATA 8
#define M3_PWM 6   // Left Motor Speed (M3)
#define M4_PWM 5   // Right Motor Speed (M4)

#define M3_A 5
#define M3_B 7
#define M4_A 0
#define M4_B 6

// Direct Ultrasonic Connection on SER1 (Pin 10) & SERVO_2 (Pin 9) top male pins!
#define TRIG_FRONT 10  // 'S' pin on SER1
#define ECHO_FRONT 9   // 'S' pin on SERVO_2

#define SAFE_DIST_CM 25  // Auto-avoid obstacles closer than 25 cm

byte latch_state = 0;
char currentMode = 'S';  // 'S'=Stop, 'F'=Forward, 'B'=Back, 'L'=Left, 'R'=Right, 'A'=Autonomous
unsigned long lastTelemetry = 0;

void updateShiftRegister() {
  digitalWrite(MOTORLATCH, LOW);
  shiftOut(MOTORDATA, MOTORCLK, MSBFIRST, latch_state);
  digitalWrite(MOTORLATCH, HIGH);
}

void setMotors(int leftDir, int rightDir, int speedVal) {
  bitWrite(latch_state, M3_A, leftDir == 1 ? HIGH : LOW);
  bitWrite(latch_state, M3_B, leftDir == -1 ? HIGH : LOW);
  bitWrite(latch_state, M4_A, rightDir == 1 ? HIGH : LOW);
  bitWrite(latch_state, M4_B, rightDir == -1 ? HIGH : LOW);
  updateShiftRegister();
  analogWrite(M3_PWM, speedVal);
  analogWrite(M4_PWM, speedVal);
}

long readUltrasonicCm(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 15000);
  if (duration == 0) return 200;
  return duration * 0.034 / 2;
}

void setup() {
  Serial.begin(115200);
  pinMode(MOTORLATCH, OUTPUT);
  pinMode(MOTORENABLE, OUTPUT);
  pinMode(MOTORDATA, OUTPUT);
  pinMode(MOTORCLK, OUTPUT);
  pinMode(M3_PWM, OUTPUT);
  pinMode(M4_PWM, OUTPUT);
  digitalWrite(MOTORENABLE, LOW);
  setMotors(0, 0, 0);

  pinMode(TRIG_FRONT, OUTPUT);
  pinMode(ECHO_FRONT, INPUT);

  Serial.println("NAVIGON HARDWARE READY");
}

void loop() {
  if (Serial.available() > 0) {
    char c = toupper(Serial.read());
    if (c == 'F' || c == 'B' || c == 'L' || c == 'R' || c == 'S' || c == 'A') {
      currentMode = c;
    }
  }

  long dFront = readUltrasonicCm(TRIG_FRONT, ECHO_FRONT);

  String actionState = "IDLE";
  if ((currentMode == 'F' || currentMode == 'A') && dFront < SAFE_DIST_CM) {
    // Obstacle ahead! Automatically steer right to avoid
    setMotors(1, -1, 200);
    actionState = "AVOIDING_OBSTACLE";
  } else {
    if (currentMode == 'F' || currentMode == 'A') { setMotors(1, 1, 190); actionState = "MOVING_FORWARD"; }
    else if (currentMode == 'B') { setMotors(-1, -1, 190); actionState = "MOVING_BACK"; }
    else if (currentMode == 'L') { setMotors(-1, 1, 190); actionState = "TURNING_LEFT"; }
    else if (currentMode == 'R') { setMotors(1, -1, 190); actionState = "TURNING_RIGHT"; }
    else { setMotors(0, 0, 0); actionState = "STOPPED"; }
  }

  // Send Live Telemetry to Laptop Dashboard every 150ms
  if (millis() - lastTelemetry > 150) {
    lastTelemetry = millis();
    Serial.print("TELEM:");
    Serial.print(dFront); Serial.print(",");
    Serial.print(dFront); Serial.print(",");
    Serial.print(dFront); Serial.print(",");
    Serial.println(actionState);
  }
}