#include <LiquidCrystal_I2C.h>

// motor controller pins
int ena = 5;
int enb = 6;

int in1 = 8;
int in2 = 9;
int in3 = 10;
int in4 = 11;

// sonar pins
int trigPin = 12; // sonar trig pin
int echoPin = 13; // sonar echo pin

// gas sensor variables
int gasIn = A0;        // analog in
int gasLed_buzz = 4;
int gasThreshold = 500; // Modify this threshold based on your sensor calibration

// led pin
int ledPin1 = 3;
int ledPin2 = 4;

// sonar variables
long timeInMicro;
long distanceInCm;

//IR for lane


// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    Serial.begin(9600);

    // motor setup
    pinMode(ena, OUTPUT);
    pinMode(enb, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(ledPin1, OUTPUT);
    pinMode(ledPin2, OUTPUT);
    analogWrite(ena, 255);
    analogWrite(enb, 255);

    // sonar setup
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    // gas sensor setup
    pinMode(gasIn, INPUT);
    pinMode(gasLed_buzz, OUTPUT);

    // initialize the LCD
    lcd.begin();
    lcd.backlight();// Turn on the blacklight and print a message.
  

    delay(1000);
}

void loop() {
    // Perform sonar measurement
    long duration, distance;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distanceInCm = (duration / 2) / 29.1;

    // Read gas sensor
    int gasValue = analogRead(gasIn);
    
    Serial.print("Distance: ");
    Serial.print(distanceInCm);
    Serial.print(" cm | Gas Value: ");
    Serial.println(gasValue);

    // Check gas level and move the car accordingly
    if (gasValue > gasThreshold) {
        // Stop the car completely due to gas detection
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
        analogWrite(ena, 0);
        analogWrite(enb, 0);
        digitalWrite(ledPin1, HIGH); // Turn on LED 1
        digitalWrite(ledPin2, HIGH); // Turn on LED 2
        lcd.clear();
        lcd.print("GAS Detected ^_~");
        lcd.setCursor(3,1);
        lcd.print(gasValue);
        
        

    } else if (distanceInCm > 15) {
        // Move forward at full speed
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        analogWrite(ena, 255);
        analogWrite(enb, 255);
        digitalWrite(ledPin1, LOW);
        digitalWrite(ledPin2, LOW);
        lcd.clear();
        lcd.print("All Good");
        lcd.setCursor(3,1);
        lcd.print(distanceInCm,"cm");
    } else if (distanceInCm >= 7 && distanceInCm <= 15) {
        // Move forward at half speed
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        analogWrite(ena, 127);  // Half of 255
        analogWrite(enb, 127);
        digitalWrite(ledPin1, HIGH); // Turn on LED 1
        digitalWrite(ledPin2, LOW);  // Turn off LED 2
        lcd.clear();
        lcd.print("Object Ahade :|");
        lcd.setCursor(3,1);
        lcd.print(distanceInCm,"cm");
    } else {
        // Stop the car
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
        analogWrite(ena, 0);
        analogWrite(enb, 0);
        digitalWrite(ledPin1, HIGH); // Turn on LED 1
        digitalWrite(ledPin2, HIGH); // Turn on LED 2
        lcd.clear();
        lcd.print("STOP :(");
        lcd.setCursor(3,1);
        lcd.print(distanceInCm,"cm");
    }

    // Add a delay to avoid rapid changes in motor control
    delay(100);
}
