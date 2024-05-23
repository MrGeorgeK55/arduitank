// Motor A (Tank Drive Left)
const int motorA1 = 7;
const int motorA2 = 6;
const int enableA = 9;

// Motor B (Tank Drive Right)
const int motorB1 = 5;
const int motorB2 = 4;
const int enableB = 10;

// Elevator Motor (H-Bridge BTS7960)
const int RPWM = 11;
const int LPWM = 12;

// HC - 05 Bluetooth Module
const int TX = 2;
const int RX = 3;

void setup() {
  // Set all the motor control pins to outputs
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(enableA, OUTPUT);

  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(enableB, OUTPUT);

  pinMode(RPWM, OUTPUT);
  pinMode(LPWM, OUTPUT);
  
  // Initialize serial communication for Bluetooth module
  Serial.begin(38400);
}

void loop() {
  // Check if data is available to read
  if (Serial.available()) {
    char command = Serial.read();
    executeCommand(command);
  }
}

void executeCommand(char command) {
  switch (command) {
    case 'F': // Forward
      moveForward();
      break;
    case 'B': // Backward
      moveBackward();
      break;
    case 'L': // Left
      turnLeft();
      break;
    case 'R': // Right
      turnRight();
      break;
    case 'S': // Stop
      stopMotors();
      break;
    case 'U': // Elevator Up
      elevatorUp();
      break;
    case 'D': // Elevator Down
      elevatorDown();
      break;
    case 'E': // Elevator Stop
      stopElevator();
      break;
    default:
      stopMotors();
      stopElevator();
      break;
  }
}

// Tank Movement Functions
void moveForward() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  analogWrite(enableA, 255);
  
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
  analogWrite(enableB, 255);
}

void moveBackward() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  analogWrite(enableA, 255);
  
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
  analogWrite(enableB, 255);
}

void turnLeft() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  analogWrite(enableA, 255);
  
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
  analogWrite(enableB, 255);
}

void turnRight() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  analogWrite(enableA, 255);
  
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
  analogWrite(enableB, 255);
}

void stopMotors() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  analogWrite(enableA, 0);
  
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
  analogWrite(enableB, 0);
}

// Elevator Control Functions
void elevatorUp() {
  analogWrite(RPWM, 255); // Set RPWM high to move up
  analogWrite(LPWM, 0);   // Set LPWM low
}

void elevatorDown() {
  analogWrite(RPWM, 0);   // Set RPWM low
  analogWrite(LPWM, 255); // Set LPWM high to move down
}

void stopElevator() {
  analogWrite(RPWM, 0);   // Set RPWM low
  analogWrite(LPWM, 0);   // Set LPWM low
}
