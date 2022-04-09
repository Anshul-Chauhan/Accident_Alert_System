#include <Arduino.h>

int pz = 4, pv = 0;
int ledPin = 2;

void piezo(void);

void setup() {
  pinMode(pz, INPUT); 
  pinMode(ledPin, OUTPUT); 
  digitalWrite(ledPin, LOW);  
  Serial.begin(9600);
}

void loop() {
  piezo();
}

void piezo()
{
  pv=analogRead(pz);
  Serial.println(pv);
  //delay(2000);
  if(pv<200)
  {
    Serial.println("pressure detected");
    digitalWrite(ledPin, HIGH);
    delay(4000);
  }
  else
  {
    //Serial.println("pressure not detected");
    digitalWrite(ledPin, LOW);
  }
}