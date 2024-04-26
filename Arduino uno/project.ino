#include <DHT.h>
#include <DHT_U.h>

#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTPIN A3     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11 // DHT 11

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
int gasIn = A0;         // analog in
int gasLed_buzz = 1;    // gas only
int gasThreshold = 500; // Modify this threshold based on your sensor calibration

// led pin
int ledPin1 = 3; // for any obstacle and high temp
int ledPin2 = 4; // when car stops
int msg = 7;     // trigger send msg

// sonar variables
long timeInMicro;
long distanceInCm;

// IR for lane
int irIn = A2;

// DHT
DHT dht(DHTPIN, DHTTYPE);

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
    Serial.begin(9600);
    dht.begin();

    // motor setup
    pinMode(ena, OUTPUT);
    pinMode(enb, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(ledPin1, OUTPUT);
    pinMode(ledPin2, OUTPUT);
    pinMode(msg, OUTPUT);
    analogWrite(ena, 255);
    analogWrite(enb, 255);

    // sonar setup
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    // gas sensor setup
    pinMode(gasIn, INPUT);
    pinMode(gasLed_buzz, OUTPUT);

    // ir
    pinMode(irIn, INPUT);

    // initialize the LCD
    lcd.begin();
    lcd.backlight(); // Turn on the blacklight and print a message.

    delay(1000);
}

void loop()
{
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

    // read IR value
    int irValue = analogRead(irIn);

    // DHT
    float t = dht.readTemperature();
    if (t > 60.00)
    {
        // warning if temparature is high
        digitalWrite(ledPin1, HIGH);
        digitalWrite(gasLed_buzz, HIGH);
    }

    // Serial.print(t);
    // Serial.print("Distance: ");
    // Serial.print(distanceInCm);
    // Serial.print(" cm | Gas Value: ");
    // Serial.println(gasValue);
    // Serial.println(irValue);

    // Check gas level and move the car accordingly
    if (gasValue > gasThreshold)
    {
        // Stop the car completely due to gas detection
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
        analogWrite(ena, 0);
        analogWrite(enb, 0);
        digitalWrite(ledPin1, HIGH); // Turn on LED 1
        digitalWrite(ledPin2, HIGH); // Turn on LED 2
        digitalWrite(msg, LOW);
        digitalWrite(gasLed_buzz, HIGH); // Turn on LED 2
        lcd.clear();
        lcd.print("GAS Detected ^_~");
        lcd.setCursor(3, 1);
        lcd.print(gasValue);
        lcd.setCursor(10, 1);
        lcd.print(t);
        lcd.print("C");
    }
    else if (irValue < 500)
    {
        // Move left Cause obstacle on right
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        analogWrite(ena, 127); // Half of 255
        analogWrite(enb, 255);
        digitalWrite(ledPin1, HIGH); // Turn on LED 1
        digitalWrite(ledPin2, LOW);  // Turn off LED 2
        digitalWrite(msg, LOW);
        digitalWrite(gasLed_buzz, LOW);
        lcd.clear();
        lcd.print("Object on Right");
        lcd.setCursor(0, 1);
        lcd.print("Moving Left..");
        lcd.setCursor(10, 1);
        lcd.print(t);
        lcd.print("C");
    }
    else if (distanceInCm > 20)
    {
        // Move forward at full speed
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        analogWrite(ena, 255);
        analogWrite(enb, 255);
        digitalWrite(ledPin1, LOW);
        digitalWrite(ledPin2, LOW);
        digitalWrite(gasLed_buzz, LOW);
        digitalWrite(msg, LOW);
        lcd.clear();
        lcd.print("All Good :)");
        lcd.setCursor(3, 1);
        lcd.print(distanceInCm);
        lcd.print("cm");
        lcd.setCursor(10, 1);
        lcd.print(t);
        lcd.print("C");
    }
    else if (distanceInCm >= 10 && distanceInCm <= 20)
    {
        // Move forward at half speed
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        int x = (2.55 * (10 * (distanceInCm - 10)));
        analogWrite(ena, x);
        analogWrite(enb, x);
        digitalWrite(ledPin1, HIGH); // Turn on LED 1
        digitalWrite(ledPin2, LOW);  // Turn off LED 2
        digitalWrite(gasLed_buzz, LOW);
        digitalWrite(msg, LOW);
        lcd.clear();
        lcd.print("Object Ahade :|");
        lcd.setCursor(0, 1);
        lcd.print(distanceInCm);
        lcd.print("cm");
        lcd.setCursor(10, 1);
        lcd.print(t);
        lcd.print("C");
    }
    else if (distanceInCm >= 3 && distanceInCm <= 10)
    {
        // Stop the car
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
        analogWrite(ena, 0);
        analogWrite(enb, 0);
        digitalWrite(ledPin1, HIGH); // Turn on LED 1
        digitalWrite(ledPin2, HIGH); // Turn on LED 2
        digitalWrite(gasLed_buzz, LOW);
        digitalWrite(msg, LOW);
        lcd.clear();
        lcd.print("STOP :(");
        lcd.setCursor(0, 1);
        lcd.print(distanceInCm);
        lcd.print("cm");
        lcd.setCursor(10, 1);
        lcd.print(t);
        lcd.print("C");
    }
    else if (distanceInCm >= 0 && distanceInCm <= 3)
    {
        // Stop the car
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
        analogWrite(ena, 0);
        analogWrite(enb, 0);
        digitalWrite(ledPin1, HIGH); // Turn on LED 1
        digitalWrite(ledPin2, HIGH); // Turn on LED 2
        digitalWrite(msg, HIGH);
        digitalWrite(gasLed_buzz, LOW);
        lcd.clear();
        lcd.print("Crashed :(");
        lcd.setCursor(0, 1);
        lcd.print(distanceInCm);
        lcd.print("cm");
        lcd.setCursor(10, 1);
        lcd.print(t);
        lcd.print("C");
    }

    // Add a delay to avoid rapid changes in motor control
    delay(100);
}