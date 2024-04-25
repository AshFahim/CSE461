const int obstacleSensorPin = A2; // Analog pin for the obstacle avoidance sensor

void setup() {
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  int sensorValue = analogRead(obstacleSensorPin); // Read the sensor value
  Serial.println(sensorValue); // Print the sensor value to the serial monitor
  
  delay(500); // Delay for a short period before reading again
}
