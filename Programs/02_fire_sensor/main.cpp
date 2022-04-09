#include <Arduino.h>

int fr = 15, fv = 0;
int ledPin = 2;

void fire(void);

void setup() {
  pinMode(fr, INPUT); 
  digitalWrite(fr, LOW);
  pinMode(ledPin, OUTPUT); 
  digitalWrite(ledPin, LOW);  
  Serial.begin(9600);
}

void loop() {
  fire();
}

void fire()
{
  fv=digitalRead(fr);
  //Serial.println(fv);
  //delay(2000);    
  if(fv==HIGH)
  {
    Serial.println("Fire detected");
    digitalWrite(ledPin, HIGH);
    delay(4000);
  }
  else
  {
    // Serial.println("Fire Not detected");
    digitalWrite(ledPin, LOW);    
  }
}