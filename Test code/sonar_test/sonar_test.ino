
int trig=5;
int echo=6;
int led = 3;

long timeInMicro;

long distanceInCm;

void setup() 
{
  Serial.begin(9600);
  pinMode(trig ,OUTPUT); 
  pinMode(echo ,INPUT);
  pinMode(led, OUTPUT);
}

void loop()  
{
 digitalWrite(trig,LOW);
 delayMicroseconds(2);
 digitalWrite(trig,HIGH);
 delayMicroseconds(10);
 digitalWrite(trig,LOW);

 timeInMicro= pulseIn(echo,HIGH);

 distanceInCm = ((timeInMicro/29)/2);

 Serial.println(distanceInCm);
 
}
