#include <Arduino.h>

int ledPin = 2;
int x=13, y=12, z=14;
int xv=0, yv=0, zv=0;

void adxl(void);

void setup() {
  pinMode(ledPin, OUTPUT); 
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);
}

void loop() {
  adxl();
}

void adxl()
{
  xv = analogRead(x);
  yv = analogRead(y);
  zv = analogRead(z);
  Serial.println(xv);
  Serial.println(yv);
  //Serial.println(zv);
  if((xv>2050) || (xv<1530) || (yv>2070) || (yv<1450))
  {
    Serial.println("ADXL tilt happen");
    digitalWrite(ledPin, HIGH);
    delay(4000);             
  }
  else
  {
    // Serial.println("ADXL tilt not happen");
    digitalWrite(ledPin, LOW);
  }
}