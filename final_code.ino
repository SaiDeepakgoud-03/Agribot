#include <Servo.h>

// Pin definitions
#define in1 2       // Motor1 L298 Pin in1
#define in2 3       // Motor1 L298 Pin in2
#define in3 4       // Motor2 L298 Pin in3
#define in4 5       // Motor2 L298 Pin in4
#define pump 8      // Pump control pin
#define servoPin 9  // Servo motor control pin
#define cutter 10   // Cutter control pin

char command;       // Variable to store Bluetooth command 
Servo ploughServo;  // Create a servo object

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  Serial.println("Grass cutter Robot with Plough and Cutter");

  // Motor control pins
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Pump and cutter control pins
  pinMode(pump, OUTPUT);
  pinMode(cutter, OUTPUT);

  // Attach servo to the defined pin
  ploughServo.attach(servoPin);

  // Set initial states
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(pump, HIGH);   // Pump OFF initially
  digitalWrite(cutter, HIGH); // Cutter OFF initially
  ploughServo.write(0);       // Initial plough position
}

void loop() {
  // Check if data is available from Bluetooth
  if (Serial.available()) {
    command = Serial.read(); // Read the Bluetooth command

    // Execute corresponding action
    switch (command) {
      case 'F': // Move forward
        forward();
        Serial.println("Moving Forward");
        break;
      case 'B': // Move backward
        backward();
        Serial.println("Moving Backward");
        break;
      case 'L': // Turn left
        left();
        Serial.println("Turning Left");
        break;
      case 'R': // Turn right
        right();
        Serial.println("Turning Right");
        break;
      case 'S': // Stop
        stopMotors();
        Serial.println("Stopping");
        break;
      case 'P': // Turn on pump
        digitalWrite(pump, LOW);
        Serial.println("Pump ON");
        break;
      case 'O': // Turn off pump
        digitalWrite(pump, HIGH);
        Serial.println("Pump OFF");
        break;
      case 'C': // Turn on cutter
        digitalWrite(cutter, LOW);
        Serial.println("Cutter ON");
        break;
      case 'X': // Turn off cutter
        digitalWrite(cutter, HIGH);
        Serial.println("Cutter OFF");
        break;
      case 'U': // Plough up (0 degrees)
        ploughServo.write(0);
        Serial.println("Plough Up (0°)");
        break;
      case 'D': // Plough down (120 degrees)
        ploughServo.write(120);
        Serial.println("Plough Down (120°)");
        break;
      default:
        Serial.println("Invalid Command");
        break;
    }
  }

  delay(100); // Small delay for stability
}

// Function to move forward
void forward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

// Function to move backward
void backward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

// Function to turn left
void left() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

// Function to turn right
void right() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

// Function to stop motors
void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}