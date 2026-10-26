#include <Servo.h>

const int sensor_pin1 = A1;  
const int sensor_pin2 = A0;
const int servoPin = 9;
const int triggerPin = 2;  // Change to the appropriate pin connected to the proximity sensor trigger
const int echoPin = 3;     // Change to the appropriate pin connected to the proximity sensor echo

Servo servoMotor;

void setup() {
  Serial.begin(9600);
  servoMotor.attach(servoPin);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  float moisture_percentage1;
  int sensor_analog1;
  float moisture_percentage2;
  int sensor_analog2;

  // Read moisture levels from sensors
  sensor_analog1 = analogRead(sensor_pin1);
  moisture_percentage1 = (100 - ((sensor_analog1 / 1023.00) * 100));

  sensor_analog2 = analogRead(sensor_pin2);
  moisture_percentage2 = (100 - ((sensor_analog2 / 1023.00) * 100));

  // Read proximity sensor
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  float duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Check if metal is detected
  if (distance < 10) { // Adjust this threshold according to your sensor's specifications
    // If metal is detected, rotate the servo to 90 degrees
    servoMotor.write(90);
    Serial.println("Metal detected. Servo motor rotating to 90 degrees.");
    delay(1000); // Delay to allow servo to rotate
  } else {
    // Check if moisture percentage from any sensor exceeds 5%
    if (moisture_percentage1 > 5 || moisture_percentage2 > 5) {
      // Rotate the servo motor to 180 degrees
      servoMotor.write(180);
      Serial.println("Moisture level is too high. Servo motor rotating 180 degrees.");
      delay(1000); // Delay to allow servo to rotate
    } else {
      // Rotate the servo motor back to 0 degrees
      servoMotor.write(0);
      Serial.println("Moisture level is normal. Servo motor rotating back to 0 degrees.");
      delay(1000); // Delay to allow servo to rotate
    }
  }
}










