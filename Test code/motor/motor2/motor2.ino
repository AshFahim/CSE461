#define trigpin 4 // digital pin 4 
#define echopin 3 // digital pin 2


int ena = 5; 
int enb = 6; 

int in1 = 8; 
int in2 = 9; 
int in3 = 10; 
int in4 = 11; 

int led1 = A0; 
int led2 = A1; 
int led3 = A2; 
int led4 = A3; 
int led5 = A4; 

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

  pinMode(led1, OUTPUT); 
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);

  digitalWrite(led1, LOW); 
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  
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

   digitalWrite(led1, LOW); 
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
} else

if(  (distance > 40) && (distance <= 57)  ) 
{

   digitalWrite(led1, HIGH); 
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
} else

if(  (distance > 57) && (distance <= 74)  ) 
{

   digitalWrite(led1, HIGH); 
  digitalWrite(led2, HIGH);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
} else

if(  (distance > 70) && (distance <= 91)  ) 
{

   digitalWrite(led1, HIGH); 
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
} else

if(  (distance > 91) && (distance <= 108)  ) 
{

   digitalWrite(led1, HIGH); 
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, LOW);
} else

if(  (distance > 108) && (distance <= 127)  ) 
{

   digitalWrite(led1, HIGH); 
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
} else

if(  distance > 127  ) 
{

   digitalWrite(led1, HIGH); 
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
} 


}