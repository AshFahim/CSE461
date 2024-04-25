#define trigpin 4 // digital pin 4 
#define echopin 3 // digital pin 3
 
 
int ena = 5; 
int enb = 6; 
 
int in1 = 8; 
int in2 = 9; 
int in3 = 10; 
int in4 = 11; 
 
float distancem; 
void setup()
{
Serial.begin(9600);
pinMode(trigpin, OUTPUT);
pinMode(echopin, INPUT);
 
  pinMode(ena, OUTPUT); 
  pinMode(enb, OUTPUT); 
 
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
 analogWrite(ena, 0); 
 analogWrite(enb, 0);
 delay(1000); 
}
 
void loop()
{
 int duration, distance;
 digitalWrite(trigpin, HIGH);
 
delayMicroseconds(1000);  
digitalWrite(trigpin, LOW);
 
 
duration = pulseIn(echopin,HIGH);
 
distance = ( duration / 2) / 29.1;
Serial.println("inches:"); 
Serial.println(distance);
 
distance = map(distance, 0 , 197, 0 , 255 ); 
 
 
if(  (distance < 0)   ) 
{
distance = 0; 
} else
if(  (distance >= 0) && (distance <= 40)  ) 
{
  analogWrite(ena, 0); 
 analogWrite(enb, 0);
    digitalWrite(in1, LOW); 
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
} else
 
if(  distance > 40  ) 
{
  analogWrite(ena, distance); 
 analogWrite(enb, distance);
    digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
 
}
